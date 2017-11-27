	.syntax	unified
	.arch	armv7e-m

	/*
	 * The vector table is at adress 0, pointing by hardware to
	 * the begining of flash, i.e. 0x08000000.
	 */
	.section .vector_table
	.int	_stack_pointer  /* Main stack pointer at reset */
	.int	reset	        /* Reset handler */
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
	
	.thumb_func /* Necessary for LSB to 1 in vector entry pointing here */
reset:
	mov fp, 0 /* Initialize frame pointer to NULL. */
	b main /* Branch to main(). */
	
	.thumb_func
default_handler:
	b .
