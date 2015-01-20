	.syntax	unified
	.arch	armv7e-m

	/*
	 * The vector table is at adress 0, pointing by hardware to
	 * the begining of flash, i.e. 0x08000000.
	 */
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
	
	.thumb_func /* Necessary for LSB to 1 in vector entry pointing here */
main:
	/*
	 * Write 8 (IO port D clock enabled) to address 0x4002 3830 (RCC AHB1
	 * peripheral clock enable register).
	 */
	ldr r0, =#0x08
	ldr r1, =#0x40023830
	strb r0, [r1]

	/*
	 * Write 0x0400 0000 (General purpose output mode for I/O 13) to address
	 * 0x4002 0c00 (GPIO D port mode register).
	 */
	ldr r0, =#0x04000000
	ldr r1, =#0x40020c00
	str r0, [r1]
	
	/*
	 * Write 0x2000 (I/O 13 1) to address 0x4002 0c14 (GPIO D port output
	 * data register).
	 */
	ldr r0, =#0x2000
	ldr r1, =#0x40020c14
	strh r0, [r1]
	
	b . /* Branch to current address */
	
	.thumb_func
default_handler:
	b .
