MEMORY
{
  flash (rx) : ORIGIN = 0x08000000, LENGTH = 0x00100000 /* 1M */
  ram (rwx) : ORIGIN = 0x20000000, LENGTH = 0x20000 /* 128K */
}

SECTIONS
{
	.text :
	{
		*(.vector_table)
		*(.text)
	} > flash

	_stack_pointer = ORIGIN(ram) + LENGTH(ram);
}
