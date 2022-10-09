OUTPUT_FORMAT(elf32-i386)
ENTRY(start)
SECTIONS
{
	. = 0x100000;
	
	.text : {
		code = .;
		_code = .;
		__code = .;
		*( .multiboot )
		*(.text)
		. = ALIGN(4096);
		}

	.data : {
		data = .;
		_data = .;
		__data = .;
		*(.data)
		*(.rodata)
		. = ALIGN(4096);
		}

	.bss  : {
		bss = .;
		*(.bss)
		. = ALIGN(4096);
		}

	.end  : {
		end = .;
		_end = .;
		__end = .;
		*(.end)
		. = ALIGN(4096);
	}
}
