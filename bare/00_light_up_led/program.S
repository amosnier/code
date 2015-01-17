	.syntax	unified
	.arch	armv7e-m

	.section .vector_table
	.int	_stack_pointer  /* Main stack pointer at reset */
	.int	main	        /* Reset handler */
	.int	default_handler /* NMI handler */
	.int	default_handler /* HardFault handler */
	.int	default_handler /* MemManage handler */
	.int	default_handler /* BusFault handler */
	.int	default_handler /* UsageFault handler */
	.int	0               /* Reserved */
	.int	0               /* Reserved */
	.int	0               /* Reserved */
	.int	0               /* Reserved */
	.int	default_handler /* SVCall handler */
	.int	default_handler /* Debug Monitor handler */
	.int	0               /* Reserved */
	.int	default_handler /* PendSV handler */
	.int	default_handler /* SysTick handler */
	.int	default_handler /* External interrupt 0 handler */

	.text
	
	.thumb_func /* Necessary for LSB to 1 in vector entry */
main:
	b .
	
	.thumb_func
default_handler:
	b .
