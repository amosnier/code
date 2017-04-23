/* Entry Point */
ENTRY(reset_handler)

_end_of_stack = 0x20050000;    /* end of RAM */

/* Generate a link error if heap and stack don't fit into RAM. */
_min_heap_size = 0x200;	 /* required amount of heap  */
_min_stack_size = 0x400; /* required amount of stack */

