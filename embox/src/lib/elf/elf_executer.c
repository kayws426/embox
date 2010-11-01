/**
 * @file
 * @brief ELF object file execute
 *
 * @date 15.07.2010
 * @author Avdyukhin Dmitry
 */

#include <lib/libelf.h>
#include <string.h>
#include <types.h>
#include <errno.h>
#include <stdio.h>

int elf_execve(unsigned long *file_addr, char *const argv[]) {
	int (*function_main)(int argc, char *argv[]);
	int result, counter;
	Elf32_Ehdr *EH;
	Elf32_Phdr *EPH;
	EH = (Elf32_Ehdr *)file_addr;

	if (EH->e_ident[0] != ELFMAG0 ||
	    EH->e_ident[1] != ELFMAG1 ||
	    EH->e_ident[2] != ELFMAG2 ||
	    EH->e_ident[3] != ELFMAG3) {
		return -1;
	}

	EPH = (Elf32_Phdr *)((char *)EH + EH->e_phoff);

	counter = EH->e_phnum;
	while(counter--) {
		if (EPH->p_type == PT_LOAD) {
			/* Physical address equals to virtual. */
			memcpy((void *)EPH->p_vaddr, (char *)EH + EPH->p_offset, EPH->p_memsz);
		}
		//EPH += 1;
		EPH = (Elf32_Phdr *)((unsigned char *)EPH + EH->e_phentsize);
	}

	printf("Data allocated.\n");
	printf("Trying to start at %ld(0x%x)\n", EH->e_entry, (uint32_t)EH->e_entry);

	function_main = (int (*)(int argc, char *argv[]))EH->e_entry;
	result = (*function_main) (0, argv);

	printf("\n result : %d\n", result);
	return result;
}
