OUTPUT_FORMAT("elf32-sparc", "elf32-sparc", "elf32-sparc")
OUTPUT_ARCH(sparc)
ENTRY(_start)

SECTIONS {
        . = 0x40000000;
        .stage2 : {
                _start = .;
                boot.o(.img.main.text)
                boot.o
        	. = ALIGN(0x2000);
		_bootloader_ph = .;
		pgt.o
	}
        . = ALIGN(0x4000);
        .vmlinux : {
                LINUXIMAGE (.text)
		_etext = .;
                PROVIDE (etext = .);
		. = ALIGN(4096);
		__start_rodata = .;
                LINUXIMAGE (.rodata)
		LINUXIMAGE (.rodata1)
		LINUXIMAGE (.pci_fixup)
		LINUXIMAGE (.rio_route)
		LINUXIMAGE (__ksymtab)
		LINUXIMAGE (__ksymtab_gpl)
		LINUXIMAGE (__ksymtab_unused)
		LINUXIMAGE (__ksymtab_unused_gpl)
		LINUXIMAGE (__ksymtab_gpl_future)
		LINUXIMAGE (__kcrctab)
		LINUXIMAGE (__kcrctab_gpl)
		LINUXIMAGE (__kcrctab_unused)
		LINUXIMAGE (__kcrctab_unused_gpl)
		LINUXIMAGE (__kcrctab_gpl_future)
		LINUXIMAGE (__ksymtab_strings)
		LINUXIMAGE (__param)
		__end_rodata = .;
		. = ALIGN(4096);
		LINUXIMAGE (.data)
		LINUXIMAGE (.data.init)
		__start_builtin_fw = .;
		LINUXIMAGE (.builtin_fw)
		__end_builtin_fw = .;
		LINUXIMAGE (.data1)
		_edata = .;
		PROVIDE (edata = .);
		__start___fixup = .;
		LINUXIMAGE (.fixup)
		__stop___fixup = .;
		__start___ex_table = .;
		LINUXIMAGE (__ex_table)
		__stop___ex_table = .;
		. = ALIGN(4096);
		__init_begin = .;
		_sinittext = .;
		LINUXIMAGE (.init.text)
		_einittext = .;
		__init_text_end = .;
		LINUXIMAGE (.init.data)
		. = ALIGN(16);
		__setup_start = .;
		LINUXIMAGE (.init.setup)
		__setup_end = .;
		__initcall_start = .;
		LINUXIMAGE (.initcall.init)
		__initcall_end = .;
  		__con_initcall_start = .;
		LINUXIMAGE (.con_initcall.init)
		__con_initcall_end = .;
		LINUXIMAGE (.security_initcall.init)
		. = ALIGN(4096);
		__initramfs_start = .;
		LINUXIMAGE (.init.ramfs)
		__initramfs_end = .;
		. = ALIGN(32);
		__per_cpu_start = .;
		LINUXIMAGE (.data.percpu)
		__per_cpu_end = .;
		. = ALIGN(4096);
  		__init_end = .;
  		. = ALIGN(32);
		LINUXIMAGE (.data.cacheline_aligned)
        }
	__bss_start = .;
	bss_start = .;
        .bss : {
                *(.bss)
        }
	bss_end = .;

        /DISCARD/ : {
                *(.exit.text)
                *(.exit.data)
                *(.exitcall.exit)
                *(.comment)
                *(.debug_aranges)
                *(.debug_pubnames)
                *(.debug_abbrev)
                *(.debug_info)
                *(.debug_line)
                *(.debug_frame)
                *(.debug_str)
                *(.debug_ranges)
        }
}
