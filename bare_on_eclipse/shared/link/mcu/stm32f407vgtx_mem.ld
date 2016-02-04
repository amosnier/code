/*
 * Originally copied from example project for STM32F4-Discovery in STM32CubeF4
 *
 * Memory Spaces Definitions.
 *
 * Need modifying for a specific board. 
 *   FLASH.ORIGIN: starting address of flash
 *   FLASH.LENGTH: length of flash
 *   RAM.ORIGIN: starting address of RAM bank 0
 *   RAM.LENGTH: length of RAM bank 0
 *
 * The values below can be addressed in further linker scripts
 * using functions like 'ORIGIN(RAM)' or 'LENGTH(RAM)'.
 */

MEMORY
{
	FLASH  (rx) : ORIGIN = 0x08000000, LENGTH = 1024K
	RAM    (xrw): ORIGIN = 0x20000000, LENGTH =  128K
	CCMRAM (rw) : ORIGIN = 0x10000000, LENGTH =   64K
}
