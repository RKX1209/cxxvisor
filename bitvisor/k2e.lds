ENTRY(entry)
virt = 0x40100000;
phys = 0x00100000;
PHDRS {
	hdrs PT_PHDR PHDRS AT (phys);
	all PT_LOAD;
}
SECTIONS {
	. = virt;
	head = .;
	. = virt + SIZEOF_HEADERS;
	.entry : AT (phys + (code - head)) {
		code = .;
		*(.entry)
		*(.entry.text)
		*(.entry.data)
	} :all
	.text : AT (phys + (text - head)) {
		text = .;
		*(.text)
		codeend = .;
	}
	.eh_frame : {
		__eh_frame_start = .;
		*(.eh_frame)
		__eh_frame_end = .;
	}
	.init_array : {
		__init_array_start = .;
		*(.init_array)
		__init_array_end = .;
	}
	.fini_array : {
		__fini_array_start = .;
		*(.fini_array)
		__fini_array_end = .;
	}
	.data : AT (phys + (data - head)) {
		data = .;
		*(.data)
		. = ALIGN (8);
                __initfunc_start = .;
                *(.initfunc)
                __initfunc_end = .;
		__process_builtin = .;
		*(.processes)
		__process_builtin_end = .;
		dataend = .;
	}
	.bss : AT (phys + (bss - head)) {
		bss = .;
		*(.bss)
		*(COMMON)
		. = ALIGN (4096);
	}
	end = .;
	/DISCARD/ : {
		*(.gomi)
	}
}
