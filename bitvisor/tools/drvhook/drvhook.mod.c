#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x6c15661c, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x780b2e4f, __VMLINUX_SYMBOL_STR(param_ops_charp) },
	{ 0xdb7305a1, __VMLINUX_SYMBOL_STR(__stack_chk_fail) },
	{ 0x58e83f2d, __VMLINUX_SYMBOL_STR(pv_mmu_ops) },
	{ 0x8b9200fd, __VMLINUX_SYMBOL_STR(lookup_address) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x8ca05263, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x6a308af1, __VMLINUX_SYMBOL_STR(find_module) },
	{ 0x1ad241df, __VMLINUX_SYMBOL_STR(mutex_lock_interruptible) },
	{ 0xbcc3bbf5, __VMLINUX_SYMBOL_STR(module_mutex) },
	{ 0xbdfb6dbb, __VMLINUX_SYMBOL_STR(__fentry__) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "CC20B2277FE96422D9EC710");
