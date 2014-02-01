.global enable_interrupts
enable_interrupts:
	mrs r1, cpsr
	bic r1, r1, #0x80
	msr cpsr_c, r1

	mov pc, lr

/* get_stack_pointer(cpu_mode) */
.global get_stack_pointer
get_stack_pointer:
	mov r3, r0
	mrs r1, cpsr
	bic r2, r1, #0x1F
	orr r2, r2, r3
	msr cpsr, r2
	mov r0, sp
	msr cpsr, r1

	mov pc, lr

.global read_cpsr
read_cpsr:
	mrs r0, cpsr
	mov pc, lr
