/*
 * Copyright (c) 2016 Ren Kimura
 * All rights reserved.
 *
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <asm/uaccess.h>
#include <asm/cacheflush.h>
#include <linux/syscalls.h>
#include <linux/mm.h>
#include "drvhook.h"

#define VMMCALL_TYPE_ERROR 0
#define VMMCALL_TYPE_VMCALL 1
#define VMMCALL_TYPE_VMMCALL 2

/* "get_vmmcall_number" vmmcall number is 0 */
#define GET_VMMCALL_NUMBER 0

MODULE_DESCRIPTION("guest driver hook for k2e");
MODULE_AUTHOR("rkx1209");
MODULE_LICENSE("GPL");

/* following string SYSCALL_TABLE_ADDRESS will be replaced by set_syscall_table_address.sh */
static void **syscall_table = (void *) 0xffffffff81a001c0;
asmlinkage long (*orig_sys_init_module)(void __user *umod, unsigned long len, const char __user *uargs);
asmlinkage long (*orig_sys_finit_module)(int fd, const char __user *uargs, int flags);

void
call_vmm_call_function (call_vmm_function_t *function,
                        call_vmm_arg_t *arg, call_vmm_ret_t *ret)
{
  struct call_vmm_call_function_sub_data data;
  data.function = function;
  data.arg = arg;
  data.ret = ret;
  pr_info("vmcall %d(arg=0x%lx)\n", data.function->vmmcall_number, data.arg->rbx);
  switch (data.function->vmmcall_type) {
  	case VMMCALL_TYPE_VMCALL:
  		asm volatile ("vmcall"
  			           : "=a" (data.ret->rax), "=b" (data.ret->rbx),
				             "=c" (data.ret->rcx), "=d" (data.ret->rdx),
  				           "=S" (data.ret->rsi), "=D" (data.ret->rdi)
  			           : "a" (data.function->vmmcall_number),
  				           "b" (data.arg->rbx),
  				           "c" (data.arg->rcx), "d" (data.arg->rdx),
  				           "S" (data.arg->rsi), "D" (data.arg->rdi)
  			           : "memory");
  		break;
  	case VMMCALL_TYPE_VMMCALL:
  		asm volatile ("vmmcall"
  			           : "=a" (data.ret->rax), "=b" (data.ret->rbx),
  				           "=c" (data.ret->rcx), "=d" (data.ret->rdx),
  				           "=S" (data.ret->rsi), "=D" (data.ret->rdi)
  			           : "a" (data.function->vmmcall_number),
  				           "b" (data.arg->rbx),
              			 "c" (data.arg->rcx), "d" (data.arg->rdx),
              			 "S" (data.arg->rsi), "D" (data.arg->rdi)
  			           : "memory");
  		break;
  	}
}

/* Get a entry number of specified vmmcall */
void
vmmcall_get_function(const char *vmmcall, call_vmm_function_t *res)
{
  call_vmm_function_t gf;
  call_vmm_arg_t gf_a;
  call_vmm_ret_t gf_r;

  gf.vmmcall_number = GET_VMMCALL_NUMBER;
  gf.vmmcall_type = VMMCALL_TYPE_VMCALL;
  gf_a.rbx = (long)vmmcall;
  pr_info("vmmcall_string:%p, 0x%lx, %s\n", vmmcall, gf_a.rbx, vmmcall);
  call_vmm_call_function(&gf, &gf_a, &gf_r);

  /* RAX = vmmcall number */
  res->vmmcall_number = (int)gf_r.rax;
  res->vmmcall_type = VMMCALL_TYPE_VMCALL; // XXX: should get this value too.
}

static void
vmcall_drvhook (void)
{
  call_vmm_function_t drvf;
  call_vmm_arg_t drv_a;
  call_vmm_ret_t drv_r;
  char drvhook[] = "drvhook";

  vmmcall_get_function(drvhook, &drvf);
  pr_info("drvhook number=%d\n",drvf.vmmcall_number);
  call_vmm_call_function(&drvf, &drv_a, &drv_r);
}

asmlinkage long
k2e_sys_init_module (void __user *umod, unsigned long len, const char __user *uargs)
{
  pr_info("call k2e_sys_init_module\n");
  vmcall_drvhook();
  return orig_sys_init_module (umod, len, uargs);
}

asmlinkage long
k2e_sys_finit_module (int fd, const char __user *uargs, int flags)
{
  pr_info("call k2e_sys_finit_module\n");
  vmcall_drvhook();
  return orig_sys_finit_module (fd, uargs, flags);
}

static void
save_original_syscall (void)
{
  orig_sys_init_module = syscall_table[__NR_init_module];
  orig_sys_finit_module = syscall_table[__NR_finit_module];
}

static void
change_page_attr_to_rw (pte_t *pte)
{
  set_pte_atomic(pte, pte_mkwrite(*pte));
}

static void
change_page_attr_to_ro (pte_t *pte)
{
  set_pte_atomic(pte, pte_clear_flags(*pte, _PAGE_RW));
}

static void
replace_system_call(void *new_init, void *new_finit)
{
  unsigned int level = 0;
  pte_t *pte;

  pte = lookup_address((unsigned long) syscall_table, &level);
  /* Need to set r/w to a page which syscall_table is in. */
  change_page_attr_to_rw(pte);
  syscall_table[__NR_init_module] = new_init;
  syscall_table[__NR_finit_module] = new_finit;
  /* set back to read only */
  change_page_attr_to_ro(pte);
}

static int
drvhook_init(void)
{
  pr_info("sys_call_table address is 0x%p\n", syscall_table);
  save_original_syscall();
  pr_info("original sys_init_module's address is %p\n", orig_sys_init_module);
  pr_info("original sys_finit_module's address is %p\n", orig_sys_finit_module);

  replace_system_call(k2e_sys_init_module, k2e_sys_finit_module);
  pr_info("system call replaced\n");
  vmcall_drvhook();
  return 0;
}
static void
drvhook_cleanup(void)
{
  pr_info("cleanup");
  if (orig_sys_init_module && orig_sys_finit_module)
    replace_system_call(orig_sys_init_module, orig_sys_finit_module);
}

module_init(drvhook_init);
module_exit(drvhook_cleanup);