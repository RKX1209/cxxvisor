typedef long int intptr_t;

typedef struct {
	int vmmcall_number;
	int vmmcall_type;
} call_vmm_function_t;

typedef struct {
	intptr_t rbx, rcx, rdx, rsi, rdi;
} call_vmm_arg_t;

typedef struct {
	intptr_t rax, rbx, rcx, rdx, rsi, rdi;
} call_vmm_ret_t;

struct call_vmm_call_function_sub_data {
	call_vmm_function_t *function;
	call_vmm_arg_t *arg;
	call_vmm_ret_t *ret;
};
static inline int
call_vmm_function_no_vmm (call_vmm_function_t *f)
{
	return !f->vmmcall_type;
}

static inline int
call_vmm_function_callable (call_vmm_function_t *f)
{
	return f->vmmcall_type && f->vmmcall_number;
}
