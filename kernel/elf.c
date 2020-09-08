/*
Copyright (C) 2019-2020 OpenCreeck
This software is distributed under the GNU General Public License.
See the file LICENSE for details.
*/

#include "elf.h"
#include "fs.h"
#include "string.h"
#include "console.h"
#include "process.h"
#include "kernel/syscall.h"
#include "memorylayout.h"

struct elf_header {
	char ident[16];
	uint16_t type;
	uint16_t machine;
	uint32_t version;
	uint32_t entry;
	uint32_t program_offset;
	uint32_t section_offset;
	uint32_t flags;
	uint16_t header_size;
	uint16_t phentsize;
	uint16_t phnum;
	uint16_t shentsize;
	uint16_t shnum;
	uint16_t shstrndx;
};

#define ELF_HEADER_TYPE_NONE         0
#define ELF_HEADER_TYPE_OBJECT       1
#define ELF_HEADER_TYPE_EXECUTABLE   2
#define ELF_HEADER_TYPE_DYNAMIC      3
#define ELF_HEADER_TYPE_CORE         4

#define ELF_HEADER_MACHINE_I386   3
#define ELF_HEADER_MACHINE_ARM    40
#define ELF_HEADER_MACHINE_X86_64 62

#define ELF_HEADER_VERSION     1

struct elf_program {
	uint32_t type;
	uint32_t offset;
	uint32_t vaddr;
	uint32_t paddr;
	uint32_t file_size;
	uint32_t memory_size;
	uint32_t flags;
	uint32_t align;
};

#define ELF_PROGRAM_TYPE_LOADABLE 1

struct elf_section {
	uint32_t name;
	uint32_t type;
	uint32_t flags;
	uint32_t address;
	uint32_t offset;
	uint32_t size;
	uint32_t link;
	uint32_t info;
	uint32_t alignment;
	uint32_t entry_size;
};

#define ELF_SECTION_TYPE_NULL         0
#define ELF_SECTION_TYPE_PROGRAM      1
#define ELF_SECTION_TYPE_SYMBOL_TABLE 2
#define ELF_SECTION_TYPE_STRING_TABLE 3
#define ELF_SECTION_TYPE_RELA         4
#define ELF_SECTION_TYPE_HASH         5
#define ELF_SECTION_TYPE_DYNAMIC      6
#define ELF_SECTION_TYPE_NOTE         7
#define ELF_SECTION_TYPE_BSS          8

#define ELF_SECTION_FLAGS_WRITE    1
#define ELF_SECTION_FLAGS_MEMORY   2
#define ELF_SECTION_FLAGS_EXEC     8
#define ELF_SECTION_FLAGS_MERGE    16
#define ELF_SECTION_FLAGS_STRINGS  32
#define ELF_SECTION_FLAGS_INFO_LINK 64
#define ELF_SECTION_FLAGS_LINK_ORDER 128
#define ELF_SECTION_FLAGS_NONSTANDARD 256
#define ELF_SECTION_FLAGS_GROUP 512
#define ELF_SECTION_FLAGS_TLS 1024


int elf_load(struct process *p, const char *filename, addr_t * entry)
{
	struct elf_header header;
	struct elf_program program;
	struct elf_section section;
	int i;
	uint32_t actual;

	struct fs_dirent *d = fs_resolve(filename);
	if(!d)
		// We return -1 because KERROR_NOT_FOUND gives us a segmentation fault
		return -1;

	actual = fs_dirent_read(d, (char *) &header, sizeof(header), 0);
	if(actual != sizeof(header))
		goto noload;
		
	if(strncmp(header.ident, "\177ELF", 4) || header.machine != ELF_HEADER_MACHINE_I386 || header.version != ELF_HEADER_VERSION)
		goto noexec;

	actual = fs_dirent_read(d, (char *) &program, sizeof(program), header.program_offset);
	if(actual != sizeof(program))
		goto noload;

//	printf("elf: text %x bytes from offset %x at address %x length %x\n",program.file_size,program.offset,program.vaddr,program.memory_size);

	if(program.type != ELF_PROGRAM_TYPE_LOADABLE || program.vaddr < PROCESS_ENTRY_POINT || program.memory_size > 0x8000000 || program.memory_size != program.file_size)
		goto noexec;

	process_data_size_set(p, program.memory_size);

	actual = fs_dirent_read(d, (char *) program.vaddr, program.memory_size, program.offset);
	if(actual != program.memory_size)
		goto mustdie;

	for(i = 0; i < header.shnum; i++) {
		actual = fs_dirent_read(d, (char *) &section, sizeof(section), header.section_offset + i * header.shentsize);
		if(actual != sizeof(section))
			goto mustdie;

		if(section.type == ELF_SECTION_TYPE_BSS) {
			uint32_t limit = section.address + section.size - PROCESS_ENTRY_POINT;
			if(limit > p->vm_data_size) {
				process_data_size_set(p, section.address + section.size - PROCESS_ENTRY_POINT);
				memset((void *) section.address, section.size, 0);
			}
		} else {
			/* skip all other section types */
		}
	}

	*entry = header.entry;
	fs_dirent_close(d);

	return 0;

      noload:
	printf("elf: %s failed to load correctly\n", filename);
	fs_dirent_close(d);
	return KERROR_NOT_FOUND;

      noexec:
	printf("elf: %s is not a valid i386 ELF executable\n", filename);
	fs_dirent_close(d);
	return KERROR_NOT_EXECUTABLE;

      mustdie:
	printf("elf: %s did not load correctly\n", filename);
	fs_dirent_close(d);
	return KERROR_EXECUTION_FAILED;
}
uint8_t elf32_get_section_by_name(void *image, char *sect_name, elf_sect_t **sect)
{
	elf_file_t *elf = (elf_file_t *)image;
	//struct fs_dirent *d = fs_resolve(image);
	elf_sect_t /**sect_table,*/ *str_sect;
	int8_t *strings;
	uint32_t i, index;

	// str_sect contem os nomes das se��es.
	str_sect = (elf_sect_t *)(image + elf->shtab_offset + (elf->sh_size * elf->shstrtab_index));
	if (str_sect->type != SHT_STRTAB)
		return 0;
	strings = (int8_t *)(str_sect->offset + image);
	//printf("%s", strings);

	// sect_table = (elf_sect_t*)(image + elf->shtab_offset);
	for (i = 0; i < elf->num_sects; i++)
	{
		// Pega o �ndice do nome da se��o atual.
		index = ((elf_sect_t *)(image + elf->shtab_offset + (elf->sh_size * i)))->sect_name;
		if (!strcmp((char *)(strings + index), sect_name))
		{
			*sect = (elf_sect_t *)(image + elf->shtab_offset + (elf->sh_size * i));
			return 1;
		}
	}

	return 0;
}

/*
	Retorna n�mero de se��es do 'type' e 'flags' requerido.
	Se 'flags' < 0 ele ser� ignorado.
*/
int32_t elf32_get_sections(void *image, uint32_t type, int32_t flags)
{
	elf_file_t *elf = (elf_file_t *)image;
	elf_sect_t *tmp;
	uint32_t i;
	int32_t retval = 0;

	for (i = 0; i < elf->num_sects; i++)
	{
		tmp = (elf_sect_t *)(image + elf->shtab_offset + (elf->sh_size * i));
		if (tmp->type == type)
		{
			if (flags >= 0)
				if (tmp->flags != (uint32_t)(flags))
					return 0;

			retval++;
		}
	}

	return retval;
}

/*
	Atribui � 'sect' a i-�sima ocorrencia de se��o do 'type' e 'flags' requerido.
	Se 'flags' < 0 ele ser� ignorado.
*/
uint8_t elf32_get_sections_i(void *image, uint32_t index, uint32_t type, int32_t flags, elf_sect_t **sect)
{
	elf_file_t *elf = (elf_file_t *)image;
	elf_sect_t *tmp;
	uint32_t i;

	for (i = 0; i < elf->num_sects; i++)
	{
		tmp = (elf_sect_t *)(image + elf->shtab_offset + (elf->sh_size * i));
		if (tmp->type == type)
		{
			if (flags >= 0)
				if (tmp->flags != (uint32_t)(flags))
					return 0;

			if (!index)
			{
				*sect = tmp;
				return 1;
			}
			index--;
		}
	}

	return 0;
}

uint8_t elf32_get_section_i(void *image, uint32_t index, elf_sect_t **sect)
{
	elf_file_t *elf = (elf_file_t *)image;
	elf_sect_t *tmp;

	if (elf->num_sects < index)
		return 0;

	tmp = (elf_sect_t *)(image + elf->shtab_offset + elf->sh_size * index);
	if (sect != NULL)
		*sect = tmp;

	return 1;
}

uint8_t elf32_get_symbol_i(void *image, uint32_t sym_idx, elf_sect_t *symtab, elf_sym_t **symbol)
{
	if (symtab->type != SHT_SYMTAB)
		return 0;

	if (sym_idx > symtab->size / symtab->ent_size)
		return 0;

	*symbol = (elf_sym_t *)(image + symtab->offset + symtab->ent_size * sym_idx);
	return 1;
}

uint8_t elf32_get_symbol_by_name(void *image, const char *sym_name, int32_t type, elf_sect_t *symtab, elf_sect_t *strtab, elf_sym_t **symbol)
{
	elf_sym_t *sym;
	uint32_t i;
	int8_t *strings;

	/* Verifica se as se��es s�o 'Symbol Table' e 'String Table' */
	if (symtab->type != SHT_SYMTAB || strtab->type != SHT_STRTAB)
		return 0;

	strings = (int8_t *)(image + strtab->offset);

	for (i = 0; i < (symtab->size / symtab->ent_size); i++)
	{
		sym = (elf_sym_t *)(image + symtab->offset + i * symtab->ent_size);
		if (!strcmp((char *)(strings + sym->name), (char *)sym_name))
		{
			if (type > 0 && sym->type != type)
				return 0;

			if (symbol != NULL)
				*symbol = sym;

			return 1;
		}
	}

	return 0;
}

/*
	Procura por um s�mbolo percorrendo todas as tabelas de s�mbolos.
	fun��o parecida com elf32_get_symbol_by_name() por�m mais gen�rica.
*/
uint8_t elf32_search_symbol(void *image, const char *name, uint32_t type, elf_sym_t **symbol)
{
	elf_sect_t *sect, *strtab;
	uint32_t i;

	for (i = 0; i < elf32_get_sections(image, SHT_SYMTAB, -1); i++) // pesquisa em todas tabelas de s�mbolos.
	{
		if (elf32_get_sections_i(image, i, SHT_SYMTAB, -1, &sect))					   // carrega symtab #i
			if (elf32_get_section_i(image, sect->link, &strtab))					   // carrega strtab correspondente.
				if (elf32_get_symbol_by_name(image, name, type, sect, strtab, symbol)) // procura pelo s�mbolo.
					return 1;
	}
	return 0;
}

uint8_t elf32_get_name(void *image, uint32_t index, elf_sect_t *strtab, const char **name)
{
	int8_t *strings;

	if (strtab->type != SHT_STRTAB)
		return 0;

	if (index > strtab->size)
		return 0;

	strings = (int8_t *)(image + strtab->offset);

	*name = (char *)(strings + index);

	return 1;
}

// Aplica relocaliza��o referenciada por membro de se��o SHT_REL ou SHT_RELA.
uint8_t elf32_reloc_apply(void *image, elf_reloc_t *rel, uint32_t symtab_idx, uint32_t t_sect_idx)
{
	elf_sect_t *symtab, *sect, *sect2;
	elf_sym_t *symbol;
	uint32_t *rel_val, sym_val;

	if (rel->type == 0)
		return RELOC_OK;

	if (!elf32_get_section_i(image, symtab_idx, &symtab)) // carrega 'Symbol Table' associada � 'Relocation Table'.
		return RELOC_ERROR_SYMTAB;

	if (!elf32_get_section_i(image, t_sect_idx, &sect)) // carrega se��o alvo da relocaliza��o.
		return RELOC_ERROR_TARGET;

	//printf("symtab.type=%d tsect.type=%d symbol.sect=%d symidx=%d\n", symtab->type & 0xff, sect->type & 0xff, symbol->section & 0xffff, symtab_idx);

	if (rel->symtab_index == 0) // Refer�ncia: (If the index is STN_UNDEF, the undefined symbol index, the relocation uses 0 as the "symbol value.")
	{
		sym_val = 0;
		goto ignore_symbol;
	}
	else
	{
		if (!elf32_get_symbol_i(image, rel->symtab_index, symtab, &symbol)) // carrega o s�mbolo a ser relocalizado.
			return RELOC_ERROR_SYMBOL;

		//rel_retry:
		switch (symbol->section)
		{
		case SHN_COMMON:
			return RELOC_COMMON;
		case SHN_ABS:
		case SHN_SOMBRA:
			sym_val = (uint32_t)(symbol->value); // + image);
			break;

		default:
			if (!elf32_get_section_i(image, symbol->section, &sect2))
				return RELOC_ERROR_SYMBOL;
			else
				sym_val = (uint32_t)(symbol->value);
			break;
		}
	}

	if (symbol->section != 0)
	{

	ignore_symbol:
		rel_val = (uint32_t *)(image + sect->offset + rel->adr); // Endere�o da relocaliza��o
		if (symbol->section == SHN_SOMBRA)
			*rel_val = (uint32_t)sym_val + *rel_val;
		else
			*rel_val = (uint32_t)((uint32_t)(image + sym_val + sect2->offset) + *rel_val);

		switch (rel->type)
		{
		case 1:
			break;
		case 2:
			*rel_val -= (uint32_t)rel_val;
			break;

		default:
			printf("Tipo desconhecido de relocalizacao em 'ELF Relocatable'.\n");
			return RELOC_ERROR;
			break;
		}
		return RELOC_OK;
	}
	else
	{
		return RELOC_UNDEF_SYMBOL;
	}

	return RELOC_OK;
}

// retorna 1 se o arquivo for valido.
uint8_t elf32_check(void *image, uint8_t type)
{
	elf_file_t *elf = (elf_file_t *)image;

	if (elf->magic != ELF_HEADER_TYPE_EXECUTABLE)
		return 0;

	if (elf->bitness != 1 || elf->endian != 1 || elf->elf_ver_1 != ELF_HEADER_VERSION || elf->file_type != type || elf->machine != ELF_HEADER_MACHINE_I386 || elf->elf_ver_2 != 1)
		return 0;

	return 1;
}
