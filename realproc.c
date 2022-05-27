/*
 * Copyright (c) 2016-2022 Kean Johnston.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#undef  emfile_t
#define emfile_t                EFCT(emfile)

#undef  Elf_Ehdr
#define Elf_Ehdr                ELFT(Ehdr)

#undef  Elf_Phdr
#define Elf_Phdr                ELFT(Phdr)

#undef  Elf_Shdr
#define Elf_Shdr                ELFT(Shdr)

#undef  Elf_Dyn
#define Elf_Dyn                 ELFT(Dyn)

#undef  ecint_t
#define ecint_t                 EFCT(int)

#undef  ecuint_t
#define ecuint_t                EFCT(uint)

#undef  elfmod_setup_file
#define elfmod_setup_file       EFC(elfmod_setup_file)

#undef  section_name
#define section_name            EFC(section_name)

#undef  is_nbtls_section
#define is_nbtls_section        EFC(is_nbtls_section)

#undef  is_section_in_segment
#define is_section_in_segment   EFC(is_section_in_segment)

#undef  vma_to_offset
#define vma_to_offset           EFC(vma_to_offset)

#undef  display_header
#define display_header          EFC(display_header)

#undef  display_sections
#define display_sections        EFC(display_sections)

#undef  display_dynamic
#define display_dynamic         EFC(display_dynamic)

#undef  display_dyn_entries
#define display_dyn_entries     EFC(display_dyn_entries)

#undef  process_file
#define process_file            EFC(process_file)

#undef  add_alignment
#define add_alignment           EFC(add_alignment)

#undef  find_dynstr
#define find_dynstr             EFC(find_dynstr)

typedef struct {
  unsigned char *data;          /* Pointer to whole file memory map */
  size_t dlen;                  /* Total size of mapped file */
  Elf_Ehdr *ehdr;               /* Points to start of file (ELF header) */
  Elf_Phdr *phdr;               /* Start of program headers */
  Elf_Shdr *shdr;               /* Start of section headers */
  Elf_Dyn *dyn;                 /* Start of PT_DYNAMIC segment */
  uint32_t e_phnum;             /* Number of program headers */
  ecuint_t e_shnum;             /* Number of section headers */
  ecuint_t e_shstrndx;          /* Section index of section name string table */
  uint32_t e_dynum;             /* Number of entries in dynamic segment */
  ecuint_t e_dynoff;            /* Offset into file of dynamic segment */
  uint32_t interp_ph;           /* Program header of PT_INTERP segment */
  uint32_t dynamic_ph;          /* Program header of PT_DYNAMIC segment */
  ecuint_t interp_sh;           /* Section header of interpreter section */
  ecuint_t dynamic_sh;          /* Section header of dynamic section */
  ecuint_t dt_strtab;           /* Dynamic string table */
  ecuint_t dt_strsz;            /* Dynamic string table size */
  const char *shnstrs;          /* Pointer to start of section name string table */
  char *dynstrs;                /* Pointer to start of dynamic string table */
  ecuint_t vmoffs;              /* Base VMA offset */
} emfile_t;

static inline ecuint_t
add_alignment (ecuint_t base, ecuint_t alignment)
{
  if (alignment > 1) {
    base += (alignment - 1);
    base &= ~(alignment - 1);
  }
  return base;
}

/*
 * Given a virtual memory address (for example one of the entries from the
 * dynamic section), convert it to a file offset. This is most commonly used
 * to locate the start of a string table. This uses the program headers
 * (segments) and only looks at loadable segments, as only such segments will
 * end up in the actual process memory at runtime.
 */
static inline ecuint_t
vma_to_offset (const emfile_t *e, ecuint_t vma, ecuint_t sz)
{
  uint16_t phi;

  for (phi = 0; phi < e->e_phnum; phi++) {
    const Elf_Phdr *phe = &e->phdr[phi];
    ecuint_t vma_start, vma_end;

    if (phe->p_type != PT_LOAD) {
      continue;
    }

    vma_start = phe->p_vaddr;
    vma_end = vma_start + phe->p_filesz;

    if ((vma >= vma_start) && (vma + sz < vma_end)) {
      return vma - vma_start + phe->p_offset;
    }
  }

  return 0;
}

/*
 * Get a pointer to the given section name. By definition using a section
 * index of 0 means get a pointer to the first byte of the section name
 * string table.
 */
static inline const char *
section_name (const emfile_t *e, uint64_t sidx)
{
  return e->shnstrs + e->shdr[sidx].sh_name;
}

/*
 * Check to see if a section is of type SHT_NOBITS and is a TLS section.
 */
static inline int
is_nbtls_section (const emfile_t *e, ecuint_t si)
{
  if ((e->shdr[si].sh_flags & SHF_TLS) &&
      (e->shdr[si].sh_type == SHT_NOBITS)) {
    return 1;
  }
  return 0;
}

/*
 * Check to see if the section index is within the program segment.
 */
static inline int
is_section_in_segment (const emfile_t *e, ecuint_t si, int pi)
{
  const Elf_Shdr *sp = &e->shdr[si];
  const Elf_Phdr *pp = &e->phdr[pi];
  ecuint_t vm_start, vm_end, od_start, od_end;

  vm_start = pp->p_vaddr;
  vm_end = vm_start + pp->p_memsz;
  od_start = pp->p_offset;
  od_end = od_start + pp->p_filesz;

  /*
   * Ensure only valid segments contain SHF_TLS sections.
   */
  if (sp->sh_flags & SHF_TLS) {
    if ((pp->p_type != PT_TLS) && (pp->p_type != PT_LOAD) && (pp->p_type != PT_GNU_RELRO)) {
      return 0;
    }
  } else {
    if ((pp->p_type == PT_TLS) || (pp->p_type == PT_PHDR)) {
      return 0;
    }
  }

  /*
   * Ensure only valid segments contain SHF_ALLOC sections. Also ensure that
   * any SHF_ALLOC sections have virtual addresses in this segment.
   */
  if (sp->sh_flags & SHF_ALLOC) {
    if (!((sp->sh_addr >= vm_start) && (sp->sh_addr < vm_end))) {
      return 0;
    }
  } else {
    if ((pp->p_type != PT_LOAD) && (pp->p_type != PT_DYNAMIC) && (pp->p_type != PT_GNU_STACK) &&
        (pp->p_type != PT_GNU_EH_FRAME) && (pp->p_type != PT_GNU_RELRO)) {
      return 0;
    }
  }

  /*
   * Unless a section is of type SHT_NOBITS, the section file offset must be
   * within the bounds of the segment.
   */
  if (sp->sh_type != SHT_NOBITS) {
    if (!((sp->sh_offset >= od_start) && (sp->sh_offset < od_end))) {
      return 0;
    }
  }

  /*
   * If the segment type is PT_DYNAMIC, ensure that the section doesn't have a
   * zero size.
   */
  if ((pp->p_type == PT_DYNAMIC) && (sp->sh_size == 0)) {
    return 0;
  }

  return 1;
}

/*
 * Given a pointer to the start of a memory map of the entire file, set up an
 * internal structure holding all of the data our various functions need. This
 * bails early if the file type is incorrect and returns non-zero. If all is
 * well returns 0.
 */
static inline int
elfmod_setup_file (emfile_t *e, unsigned char *data, size_t dlen)
{
  uint32_t x;
  ecuint_t shi, stroff = 0;

  memset (e, 0, sizeof (*e));

  e->data = data;
  e->dlen = dlen;
  e->ehdr = (Elf_Ehdr *)data;

  if (e->ehdr->e_type != ET_EXEC && e->ehdr->e_type != ET_DYN) {
    fprintf (stderr, "%s warning: skipping `%s' - invalid type 0x%04"PRIx16"\n", progname, curfile, e->ehdr->e_type);
    return 1;
  }

  if (0 == e->ehdr->e_phnum) {
    fprintf (stderr, "%s warning: skipping `%s' - no program headers\n", progname, curfile);
    return 1;
  }

  e->e_phnum = e->ehdr->e_phnum;
  e->e_shnum = e->ehdr->e_shnum;
  e->e_shstrndx = e->ehdr->e_shstrndx;

  e->shdr = (Elf_Shdr *)(data + e->ehdr->e_shoff);
  e->phdr = (Elf_Phdr *)(data + e->ehdr->e_phoff);

  /*
   * The gABI is ambiguous with regards to extended section numbers. In one
   * section it explicitly states that if e_shnum is zero or e_shstrndx is
   * SHN_XINDEX, then the values are picked up from section header 0's
   * sh_size and sh_link fields, respectively. In another part of the document
   * they simply state that if those fields are non-zero, then that is the
   * actual section count or section string table index. So for right now,
   * unless it proves to be a problem, we adopt the second approach. If those
   * fields are non-zero those are the values we use.
   */
  if (e->shdr[0].sh_size != 0) {
    e->e_shnum = e->shdr[0].sh_size;
  }

  if (e->shdr[0].sh_link != 0) {
    e->e_shstrndx = e->shdr[0].sh_link;
  }

  e->shnstrs = (char *)data + e->shdr[e->e_shstrndx].sh_offset;

  /*
   * If the type is an executable, make sure we have a PT_INTERP segment.
   * For either an executable or a shared object, make sure a PT_DYNAMIC
   * segment exists.
   */
  e->vmoffs = (ecuint_t)-1;

  for (x = 0; x < e->e_phnum; x++) {
    const Elf_Phdr *phe = &e->phdr[x];

    if (phe->p_type == PT_DYNAMIC) {
      e->dynamic_ph = x;
      e->e_dynoff = phe->p_offset;
      e->dyn = (Elf_Dyn *)(data + e->e_dynoff);
    } else if (phe->p_type == PT_INTERP) {
      e->interp_ph = x;
    } else if (phe->p_type == PT_LOAD) {
      if (phe->p_vaddr < e->vmoffs) {
        e->vmoffs = phe->p_vaddr;
      }
    }
  }

  if ((e->ehdr->e_type == ET_EXEC) && (e->interp_ph == 0)) {
    fprintf (stderr, "%s warning: skipping `%s' - executable has no interpreter.\n", progname, curfile);
    return 1;
  }

  if (e->dynamic_ph == 0) {
    fprintf (stderr, "%s warning: skipping `%s' - no PT_DYNAMIC segment.\n", progname, curfile);
    return 1;
  }

  /*
   * Calculate the number of dynamic entries. It is tempting to think we can
   * just divide the dynamic section size by the size of a dynamic entry, but
   * real world examples prove that this does not work. The gABI explicitly
   * states that a NULL entry terminates the list so instead we walk the list
   * looking for that entry (and include it in the count).
   */
  while (e->dyn[e->e_dynum++].d_tag != DT_NULL) /* Do nothing */;

  for (x = 0; x < e->e_dynum; x++) {
    const Elf_Dyn *dyn = &e->dyn[x];

    if (dyn->d_tag == DT_STRTAB) {
      e->dt_strtab = dyn->d_un.d_val;
    } else if (dyn->d_tag == DT_STRSZ) {
      e->dt_strsz = dyn->d_un.d_val;
    }
  }

  if (0 == e->dt_strtab) {
    fprintf (stderr, "%s warning: skipping `%s' - no DT_STRTAB found.\n", progname, curfile);
    return 1;
  }

  if (0 == e->dt_strsz) {
    fprintf (stderr, "%s warning: skipping `%s' - no DT_STRSZ found.\n", progname, curfile);
    return 1;
  }

  stroff = vma_to_offset (e, e->dt_strtab, e->dt_strsz);
  if (0 == stroff) {
    fprintf (stderr, "%s warning: skipping `%s' - no dynamic string table found.\n", progname, curfile);
    return 1;
  }

  e->dynstrs = (char *)data + stroff;

  /*
   * If we have an interpreter program header, find the section that contains
   * the name of the interpreter. We do this by strict VMA matching rather
   * than assuming the section name is .interp, which the gABI hints at but
   * does not require.
   */
  if (e->interp_ph) {
    for (shi = 0; shi < e->e_shnum; shi++) {
      if (is_section_in_segment (e, shi, e->interp_ph)) {
        if ((e->phdr[e->interp_ph].p_vaddr == e->shdr[shi].sh_addr) &&
          (e->phdr[e->interp_ph].p_memsz == e->shdr[shi].sh_size)) {
          e->interp_sh = shi;
          break;
        }
      }
    }
  }

  /*
   * We always have a dynamic segment, so find it's backing section.
   */
  for (shi = 0; shi < e->e_shnum; shi++) {
    if (is_section_in_segment (e, shi, e->dynamic_ph)) {
      if ((e->phdr[e->dynamic_ph].p_vaddr == e->shdr[shi].sh_addr) &&
        (e->phdr[e->dynamic_ph].p_memsz == e->shdr[shi].sh_size)) {
        e->dynamic_sh = shi;
        break;
      }
    }
  }

  if (0 == e->dynamic_sh) {
    fprintf (stderr, "%s warning: skipping `%s' - no dynamic section found.\n", progname, curfile);
    return 1;
  }

  return 0;
}

static void
display_header (const emfile_t *e, int debug)
{
  uint16_t phi;
  ecuint_t shi, ph_start, ph_end, vm_start, vm_end, od_start, od_end;
  const unsigned char *data = e->data;

  printf (" ELF header:\n");

  printf ("  File name:                  %s\n", curfile);

  printf ("  File size:                  "PRIeu" byte%s\n", plural ((ecuint_t)e->dlen));

  printf ("  File range on disk:         "PRIex" - "PRIex"\n", (ecuint_t)0, (ecuint_t)e->dlen);

  printf ("  Identifier:                 ");
  prettyhex (data, EI_NIDENT, 0, 0, 0);
  putc ('\n', stdout);

  printf ("  Class:                      ELFCLASS" ELFCS "\n");

  printf ("  Data:                       ");
  switch (data[EI_DATA]) {
    case ELFDATA2LSB:
      printf ("2's complement, little endian\n"); break;
    case ELFDATA2MSB:
      printf ("2's complement, big endian\n"); break;
    default:
      printf ("0x%02"PRIx8, (int)data[EI_DATA]); break;
  }

  printf ("  Version:                    ");
  printf ("%d", data[EI_VERSION]);
  if (EV_CURRENT == data[EI_VERSION]) {
    printf (" (current)\n");
  } else {
    putc ('\n', stdout);
  }

  printf ("  OS/ABI:                     ");
  switch (data[EI_OSABI]) {
#undef OSABIENT
#define OSABIENT(name,desc)     \
    case ELF##name:             \
      printf (#name " (%s)\n", desc); break;
#include "osabi.h"

    default:
      printf ("0x%02"PRIx8" (UNKNOWN)\n", data[EI_OSABI]); break;
  }

  printf ("  ABI Version:                0x%02"PRIx8" (%"PRIu8")\n", data[EI_ABIVERSION], data[EI_ABIVERSION]);

  printf ("  Type:                       ");
  switch (e->ehdr->e_type) {
    case ET_EXEC: printf ("ET_EXEC (executable file)\n"); break;
    case ET_DYN: printf ("ET_DYN (shared object file)\n"); break;
    /* All others filtered out before we get here. */
  }

  printf ("  Machine:                    ");
  switch (e->ehdr->e_machine) {
#undef EMACHENT
#define EMACHENT(name, desc)    \
    case EM_##name:             \
      printf ("EM_" #name " (%s)\n", desc); break;
#include "e_machine.h"

    default:
      printf ("UNKNOWN (0x%04"PRIx16")\n", e->ehdr->e_machine); break;
  }

  printf ("  Flags:                      0x%08"PRIx32"\n", e->ehdr->e_flags);

  printf ("  Entry Point:                "PRIex"\n", e->ehdr->e_entry);

  printf ("  This header size:           0x%04"PRIx16" (%"PRIu16" byte%s)\n", e->ehdr->e_ehsize, plural (e->ehdr->e_ehsize));

  printf ("  Program header offset:      "PRIex" ("PRIeu" byte%s into file)\n", e->ehdr->e_phoff, plural (e->ehdr->e_phoff));

  printf ("  Section header offset:      "PRIex" ("PRIeu" byte%s into file)\n", e->ehdr->e_shoff, plural (e->ehdr->e_shoff));

  printf ("  Number of program headers:  %"PRIu16" (each %"PRIu16" byte%s long)\n", e->e_phnum, plural (e->ehdr->e_phentsize));

  printf ("  Number of section headers:  "PRIeu" (each %"PRIu16" byte%s long)\n", e->e_shnum, plural (e->ehdr->e_shentsize));

  printf ("  Program headers range:      "PRIex" - "PRIex" (on disk)\n", e->ehdr->e_phoff, e->ehdr->e_phoff + (e->ehdr->e_phnum * e->ehdr->e_phentsize));

  printf ("  Section headers range:      "PRIex" - "PRIex" (on disk)\n", e->ehdr->e_shoff, e->ehdr->e_shoff + (e->ehdr->e_shnum * e->ehdr->e_shentsize));

  printf ("  Section name string table:  section #"PRIeu" (%s)\n", e->e_shstrndx, section_name (e, e->e_shstrndx));

  printf ("  Base VM address:            "PRIex"\n", e->vmoffs);

  if (debug) {
    printf ("  Raw header bytes:\n");
    prettyhex (data, e->ehdr->e_ehsize, 0, HPP_GROUP_16 | HPP_OFFSET_16 | HPP_ASCII | HPP_LEAD_FIRST, "    ");
  }

  printf ("\n");
  printf (" Program headers:\n");

  for (phi = 0; phi < e->e_phnum; phi++) {
    const Elf_Phdr *phe = &e->phdr[phi];

    od_start = phe->p_offset;
    od_end = od_start + phe->p_filesz;
    vm_start = phe->p_vaddr;
    vm_end = vm_start + phe->p_memsz;
    ph_start = phe->p_paddr;
    ph_end = ph_start + phe->p_memsz;

    printf ("  Program segment #%"PRIu16":\n", phi);

    printf ("    Type:                    ");
    switch (phe->p_type) {
#undef PTYPEENT
#define PTYPEENT(type)          \
      case PT_##type:           \
        printf(#type); break;
#include "p_type.h"

      default:
        printf ("UNKNOWN"); break;
    }
    printf (" (0x%"PRIx32")\n", phe->p_type);

    if (PT_INTERP == phe->p_type) {
      printf ("    Interpreter:             %s\n", (const char *)data + phe->p_offset);
    }

    printf ("    Flags:                   %c%c%c (0x%"PRIx32")\n",
      phe->p_flags & PF_R ? 'r' : '-',
      phe->p_flags & PF_W ? 'w' : '-',
      phe->p_flags & PF_X ? 'x' : '-',  phe->p_flags);

    printf ("    Offset:                  "PRIex" ("PRIeu" byte%s into file)\n", phe->p_offset, plural (phe->p_offset));

    printf ("    Size on disk:            "PRIex" ("PRIeu" byte%s)\n", phe->p_filesz, plural (phe->p_filesz));

    printf ("    Size in memory:          "PRIex" ("PRIeu" byte%s)\n", phe->p_memsz, plural (phe->p_memsz));

    printf ("    Range on disk:           "PRIex" - "PRIex"\n", od_start, od_end);

    printf ("    Virtual address range:   "PRIex" - "PRIex"\n", vm_start, vm_end);

    printf ("    Physical address range:  "PRIex" - "PRIex"\n", ph_start, ph_end);

    printf ("    Alignment:               "PRIex" ("PRIeu" byte%s)\n", phe->p_align, plural (phe->p_align));

    /*
     * Print the sections that map into this segment. For this we need go
     * through each and every section and see if its addresses fall within
     * the addresses of this segment.
     */
    printf ("    Sections:               ");
    for (shi = 0; shi < e->e_shnum; shi++) {
      const Elf_Shdr *shp = &e->shdr[shi];

      if ((shp->sh_type == SHT_NULL) || is_nbtls_section (e, shi) || !is_section_in_segment (e, shi, phi)) {
        continue;
      }

      printf (" %s", section_name (e, shi));
    }
    putc ('\n', stdout);

    if (PT_NOTE == phe->p_type) {
      printf ("    Note data:\n");
      prettyhex (data + phe->p_offset, phe->p_filesz, 0, HPP_GROUP_16 | HPP_OFFSET_16 | HPP_ASCII | HPP_LEAD_FIRST, "      ");
    }
  }

  if (debug) {
    printf ("  Raw program table bytes:\n");
    prettyhex (data + e->ehdr->e_phoff, e->e_phnum * e->ehdr->e_phentsize, e->ehdr->e_phoff,
      HPP_GROUP_16 | HPP_OFFSET_32 | HPP_ASCII | HPP_LEAD_FIRST, "    ");
  }
  putc ('\n', stdout);
}

static void
display_sections (const emfile_t *e, int debug)
{
  const unsigned char *data = e->data;
  const char *shnstrs = e->shnstrs;
  uint16_t phi;
  ecuint_t shi, vm_start, vm_end, od_start, od_end;

  printf (" Section headers:\n");

  for (shi = 0; shi < e->e_shnum; shi++) {
    const Elf_Shdr *shp = &e->shdr[shi];

    od_start = shp->sh_offset;
    od_end = od_start + shp->sh_size;
    vm_start = shp->sh_addr;
    vm_end = vm_start + shp->sh_size;

    printf ("  Section header #"PRIeu":\n", shi);

    printf ("    Name:                  %s\n", shnstrs + shp->sh_name);

    printf ("    Type:                  ");
    switch (shp->sh_type) {
#undef SHTYPEENT
#define SHTYPEENT(type,desc)    \
      case SHT_##type:          \
        printf(#type "\n"); break;
#include "sh_type.h"

      default:
        printf ("0x%"PRIx32"\n", shp->sh_type); break;
    }

    printf ("    Flags:                 %c%c%c%c%c%c%c%c%c%c%c%c%c ("PRI8x")\n",
      (shp->sh_flags & SHF_WRITE) ? 'w' : '-',
      (shp->sh_flags & SHF_ALLOC) ? 'a' : '-',
      (shp->sh_flags & SHF_EXECINSTR) ? 'x' : '-',
      (shp->sh_flags & SHF_MERGE) ? 'm' : '-',
      (shp->sh_flags & SHF_STRINGS) ? 's' : '-',
      (shp->sh_flags & SHF_INFO_LINK) ? 'i' : '-',
      (shp->sh_flags & SHF_LINK_ORDER) ? 'l' : '-',
      (shp->sh_flags & SHF_OS_NONCONFORMING) ? 'o' : '-',
      (shp->sh_flags & SHF_GROUP) ? 'g' : '-',
      (shp->sh_flags & SHF_TLS) ? 't' : '-',
      (shp->sh_flags & SHF_COMPRESSED) ? 'c' : '-',
      (shp->sh_flags & SHF_ORDERED) ? 'O' : '-',
      (shp->sh_flags & SHF_EXCLUDE) ? 'e' : '-',
      shp->sh_flags);

    printf ("    Memory address:        "PRIex"\n", shp->sh_addr);

    printf ("    File offset:           "PRIex" ("PRIeu" byte%s into file)\n", shp->sh_offset, plural (shp->sh_offset));

    printf ("    Section size:          "PRIex" ("PRIeu" byte%s)\n", shp->sh_size, plural (shp->sh_size));

    printf ("    Linked section:        0x%08"PRIx32" (%"PRIu32")", shp->sh_link, shp->sh_link);
    if (shp->sh_link) {
      printf (" [%s]", section_name (e, shp->sh_link));
    }
    putc ('\n', stdout);

    printf ("    Section info:          0x%08"PRIx32" (%"PRIu32")\n", shp->sh_info, shp->sh_info);

    printf ("    Entry size:            "PRIex" ("PRIeu" byte%s)\n", shp->sh_entsize, plural (shp->sh_entsize));

    printf ("    Range on disk:         "PRIex" - "PRIex"\n", od_start, od_end);

    printf ("    Virtual address range: "PRIex" - "PRIex"\n", vm_start, vm_end);

    printf ("    Address alignment:     "PRIex" ("PRIeu" byte%s)\n", shp->sh_addralign, plural (shp->sh_addralign));

    printf ("    Program segments:     ");
    for (phi = 0; phi < e->e_phnum; phi++) {
      if ((shp->sh_type == SHT_NULL) || is_nbtls_section (e, shi) || !is_section_in_segment (e, shi, phi)) {
        continue;
      }
      printf (" #%"PRIu16, phi);
    }
    putc ('\n', stdout);
  }

  if (debug) {
    printf ("  Raw section table bytes:\n");
    prettyhex (data + e->ehdr->e_shoff, e->e_shnum * e->ehdr->e_shentsize, e->ehdr->e_shoff,
      HPP_GROUP_16 | HPP_OFFSET_32 | HPP_ASCII | HPP_LEAD_FIRST, "    ");
  }

  putc ('\n', stdout);
}

static void
display_dynamic (const emfile_t *e, int debug)
{
  uint32_t dti;

  printf (" Dynamic section at offset "PRIex" ("PRIeu") has %"PRIu32" entr%s:\n", e->e_dynoff, e->e_dynoff, pluraly(e->e_dynum));

  printf ("   Tag"EXSPACES"         Name                Value\n");

  for (dti = 0; dti < e->e_dynum; dti++) {
    const Elf_Dyn *dyn = &e->dyn[dti];

    printf ("   "PRIex"  ", dyn->d_tag);
    switch (dyn->d_tag) {
#undef  DYNTAGENT
#define DYNTAGENT(ent)                  \
      case DT_##ent:                    \
        printf ("%-20s", #ent); break;
#include "dyn_dtags.h"

      default:
        printf ("%-20s", "UNKNOWN");
        break;
    }

    switch (dyn->d_tag) {
      case DT_NEEDED:
      case DT_RPATH:
      case DT_RUNPATH:
      case DT_SONAME:
        printf ("%s\n", e->dynstrs + dyn->d_un.d_val);
        break;

      default:
        printf (PRIex"\n", dyn->d_un.d_val);
        break;
    }
  }

  if (debug) {
    putc ('\n', stdout);
    printf ("  Raw dynamic section bytes:\n");
    prettyhex (e->data + e->e_dynoff, e->e_dynum * sizeof (Elf_Dyn), e->e_dynoff,
      HPP_GROUP_16 | HPP_OFFSET_32 | HPP_ASCII | HPP_LEAD_FIRST, "    ");
    putc ('\n', stdout);
  }

  putc ('\n', stdout);
}

/*
 * Similar to the above but more suited for command line usage.
 */
static void
display_dyn_entries (const emfile_t *e, uint32_t dflags)
{
  uint32_t dti;

  if ((dflags & DISPLAY_INTERP) && (e->interp_ph != 0)) {
    const Elf_Phdr *ph = &e->phdr[e->interp_ph];
    printf ("%s\n", (const char *)e->data + ph->p_offset);
  }

  for (dti = 0; dti < e->e_dynum; dti++) {
    const Elf_Dyn *dyn = &e->dyn[dti];
    int d = 0;

    switch (dyn->d_tag) {
      case DT_NEEDED:
        if (dflags & DISPLAY_NEEDED) {
          d++;
        }
        break;

      case DT_RPATH:
        if (dflags & DISPLAY_RPATH) {
          d++;
        }
        break;

      case DT_RUNPATH:
        if (dflags & DISPLAY_RUNPATH) {
          d++;
        }
        break;

      case DT_SONAME:
        if (dflags & DISPLAY_SONAME) {
          d++;
        }
        break;
    }

    if (d) {
      printf ("%s\n", e->dynstrs + dyn->d_un.d_val);
    }
  }
}

static char *
find_dynstr (const emfile_t *e, const char *str)
{
  char *csmax = e->dynstrs + e->dt_strsz;
  char *cs = e->dynstrs;
  size_t osl = strlen (str) + 1;

  while (cs < csmax) {
    size_t sl = strlen (cs) + 1;
    if (sl == osl) {
      if (0 == memcmp (cs, str, osl)) {
        return cs;
      }
    }
    cs += sl;
  }

  return 0;
}

#define WORK_INTERPRETER        (1 << 0)        /* Need to change the interpreter */
#define WORK_SONAME             (1 << 1)        /* Need to change the shared object name */
#define WORK_NEEDED             (1 << 2)        /* Need to change DT_NEEDED entries */
#define WORK_RPATH              (1 << 3)        /* Need to change DT_RPATH entries */
#define WORK_RUNPATH            (1 << 4)        /* Need to change DT_RUNPATH entries */
#define WORK_FLAGS              (1 << 5)        /* Need to set DT_FLAGS entry */
#define WORK_ABI_COMPLIANCE     (1 << 6)        /* Need to make the object gABI compliant */

static int
process_file (unsigned char *data, size_t dlen)
{
  emfile_t e, ne;
  strlist_t *needed = 0, *rpath_s = 0, *runpath_s = 0;
  char *soname = 0, *rpath = 0, *runpath = 0, *emdstr = 0;
  uint32_t x, dti;
  ecuint_t offset = 0, newstrsz = 0, newstroff = 0, o_dt_strsz = 0, dt_flags = 0, mdt_flags = 0;
  uint32_t work = 0;
  int num_needed = 0;
  int i, dte = 0;

  if (elfmod_setup_file (&e, data, dlen)) {
    return 1;
  }

  if (arg_needed_add->nstrs || arg_needed_del->nstrs || arg_abspath->nstrs) {
    needed = sl_new (5);
  }

  if (arg_soname) {
    soname = strdup (arg_soname);
  }

  if (arg_rpath_set) {
    rpath = strdup (arg_rpath_set);
  }

  if (arg_runpath_set) {
    runpath = strdup (arg_runpath_set);
  }

  for (dti = 0; dti < e.e_dynum; dti++) {
    const Elf_Dyn *dyn = &e.dyn[dti];

    switch (dyn->d_tag) {
      case DT_SONAME:
        if (0 == soname) {
          soname = strdup (e.dynstrs + dyn->d_un.d_val);
        }
        break;

      case DT_RPATH:
        if (0 == rpath) {
          rpath = strdup (e.dynstrs + dyn->d_un.d_val);
        }
        break;

      case DT_RUNPATH:
        if (0 == runpath) {
          runpath = strdup (e.dynstrs + dyn->d_un.d_val);
        }
        if (strstr (e.dynstrs + dyn->d_un.d_val, "$ORIGIN") || strstr (e.dynstrs + dyn->d_un.d_val, "${ORIGIN}")) {
          mdt_flags |= DF_ORIGIN;
        }
        break;

      case DT_NEEDED:
        if (needed) {
          sl_stradd (needed, e.dynstrs + dyn->d_un.d_val);
        }
        if (strstr (e.dynstrs + dyn->d_un.d_val, "$ORIGIN") || strstr (e.dynstrs + dyn->d_un.d_val, "${ORIGIN}")) {
          mdt_flags |= DF_ORIGIN;
        }
        break;

      case DT_FLAGS:
        dt_flags = dyn->d_un.d_val;
        break;

      case DT_BIND_NOW:
        mdt_flags |= DF_BIND_NOW;
        break;

      case DT_SYMBOLIC:
        mdt_flags |= DF_SYMBOLIC;
        break;

      case DT_TEXTREL:
        mdt_flags |= DF_TEXTREL;
        break;
    }
  }

  if (emdisplay_before & DISPLAY_HEADERS) {
    display_header (&e, emdisplay_before & DISPLAY_DEBUG ? 1 : 0);
    display_sections (&e, emdisplay_before & DISPLAY_DEBUG ? 1 : 0);
  }

  if (emdisplay_before & DISPLAY_DYNAMIC) {
    display_dynamic (&e, emdisplay_before & DISPLAY_DEBUG ? 1 : 0);
  }

  display_dyn_entries (&e, emdisplay_before);

  sl_lstadd (needed, arg_needed_add);
  sl_lstdel (needed, arg_needed_del);

  if (rpath && rpath[0]) {
    rpath_s = sl_new (1);
    sl_splitadd (rpath_s, rpath, ":;");
    sl_lstadd (rpath_s, arg_rpath_add);
    sl_lstdel (rpath_s, arg_rpath_del);
    free (rpath);
    rpath = 0;
  }

  if (runpath && runpath[0]) {
    runpath_s = sl_new (1);
    sl_splitadd (runpath_s, runpath, ":;");
    sl_lstadd (runpath_s, arg_runpath_add);
    sl_lstdel (runpath_s, arg_runpath_del);
    free (runpath);
    runpath = 0;
  }

  /*
   * "Absolute-ise" everything if we've been asked to.
   */
  soname = make_absolute (soname);

  if (needed) {
    for (i = 0; i < needed->strsz; i++) {
      needed->strs[i] = make_absolute (needed->strs[i]);
    }
    num_needed = needed->nstrs;
  }

  /*
   * If we have either an RPATH or a RUNPATH (or both) we can convert their
   * string list to the final, colon-separated string and get rid of the
   * string list structure.
   */
  if (rpath_s) {
    rpath = sl_join (rpath_s, ':');
    sl_free (rpath_s);
    rpath_s = 0;
  }

  if (runpath_s) {
    runpath = sl_join (runpath_s, ':');
    sl_free (runpath_s);
    runpath_s = 0;
  }

  if (arg_compliance & 2) {
    if (rpath && (0 == runpath)) {
      runpath = rpath;
      rpath = 0;
    }
  }

  /*
   * We copy the old header to the new one, but the new one isn't backed by a
   * memory mapped file, it's relevant contents are in memory. Eventually we
   * write this out and map it in to display the final results if we've been
   * asked to do that, but during processing we work with the heap allocated
   * data.
   *
   * Note that we never actually add sections or segments, so we always
   * preserve the original order. Only the various offsets in the file change.
   * We calculate those offsets in memory so that by the time we come to write
   * out the modified file, everything is correct. The dynamic section on the
   * other hand, can and probably will change, which is why we over-allocate
   * that section type, as well as the dynamic string table.
   */
  memcpy (&ne, &e, sizeof (ne));
  ne.data = 0;
  ne.dlen = 0;

  ne.ehdr = (Elf_Ehdr *)malloc (e.ehdr->e_ehsize);
  ne.phdr = (Elf_Phdr *)calloc (e.e_phnum, e.ehdr->e_phentsize);
  ne.shdr = (Elf_Shdr *)calloc (e.e_shnum, e.ehdr->e_shentsize);
  ne.dyn  = (Elf_Dyn *)calloc (e.e_dynum + 3 + num_needed, sizeof (Elf_Dyn));
  ne.dynstrs = (char *)calloc (1, e.dt_strsz + 4096 + (num_needed * 1024));

  memcpy (ne.phdr, e.phdr, e.e_phnum * sizeof (e.ehdr->e_phentsize));
  memcpy (ne.shdr, e.shdr, e.e_shnum * sizeof (e.ehdr->e_shentsize));
  memcpy (ne.dynstrs, e.dynstrs, e.dt_strsz);
  newstrsz = e.dt_strsz;

  /*
   * We're now pretty much ready to do our thing. The first thing we do is to
   * set up the dynamic section's string table to contain any new strings.
   * We do not want to modify any existing strings as we do not want to scan
   * every possible string reference to see if it is used by more than just
   * the DT_NEEDED or DT_SONAME entries. So we only ever append to the string
   * list. However, we want to make sure that multiple runs of this tool, for
   * whatever reason, do not just blindly keep appending strings to this list.
   * So we add a special string ("\1ELFMOD\1") that will act as a marker to
   * any future invocations of this program as to where it started appending.
   * So we look for that string now, and record its position if it exists, or
   * add it if it doesn't.
   */
  emdstr = find_dynstr (&ne, "\1ELFMOD\1");
  if (0 == emdstr) {
    emdstr = ne.dynstrs + ne.dt_strsz;
    memcpy (emdstr, "\1ELFMOD\1\0", 9);   /* Also copy the terminating NULL */
  }
  o_dt_strsz = emdstr - ne.dynstrs;
  emdstr += 9;
  ne.dt_strsz = emdstr - ne.dynstrs;

  if (needed) {
    work |= WORK_NEEDED;

    for (i = 0; i < needed->strsz; i++) {
      char *nsp, *tsp = needed->strs[i];
      size_t sl;

      if (0 == tsp) {
        continue;
      }
      sl = strlen (tsp);

      nsp = find_dynstr (&ne, tsp);
      if (0 == nsp) {
        memcpy (emdstr, tsp, sl + 1);
        nsp = emdstr;
        emdstr += sl + 1;
        ne.dt_strsz += sl + 1;
      }
      ne.dyn[dte].d_tag = DT_NEEDED;
      ne.dyn[dte].d_un.d_val = nsp - ne.dynstrs;
      dte++;
      if (strstr (nsp, "$ORIGIN") || strstr (nsp, "${ORIGIN}")) {
        mdt_flags |= DF_ORIGIN;
      }
    }
  }

  if (soname) {
    char *ssp = find_dynstr (&ne, soname);
    size_t sl = strlen (soname);

    if (0 == ssp) {
      memcpy (emdstr, soname, sl + 1);
      ssp = emdstr;
      emdstr += sl + 1;
      ne.dt_strsz += sl + 1;
    }
    ne.dyn[dte].d_tag = DT_SONAME;
    ne.dyn[dte].d_un.d_val = ssp - ne.dynstrs;
    dte++;
    printf ("SONAME = %s\n", ssp);
    work |= WORK_SONAME;
  }

  if (runpath) {
    char *rsp = find_dynstr (&ne, runpath);
    size_t sl = strlen (runpath);

    if (0 == rsp) {
      memcpy (emdstr, runpath, sl + 1);
      rsp = emdstr;
      emdstr += sl + 1;
      ne.dt_strsz += sl + 1;
      printf ("RUNPATH = %s\n", rsp);
    }
    ne.dyn[dte].d_tag = DT_RUNPATH;
    ne.dyn[dte].d_un.d_val = rsp - ne.dynstrs;
    dte++;
    work |= WORK_RUNPATH;
    if (strstr (rsp, "$ORIGIN") || strstr (rsp, "${ORIGIN}")) {
      mdt_flags |= DF_ORIGIN;
    }
  }

  if (rpath) {
    char *rsp = find_dynstr (&ne, rpath);
    size_t sl = strlen (rpath);

    if (0 == rsp) {
      memcpy (emdstr, rpath, sl + 1);
      rsp = emdstr;
      emdstr += sl + 1;
      ne.dt_strsz += sl + 1;
      printf ("RPATH = %s\n", rsp);
    }
    ne.dyn[dte].d_tag = DT_RPATH;
    ne.dyn[dte].d_un.d_val = rsp - ne.dynstrs;
    dte++;
    work |= WORK_RPATH;
    if (strstr (rsp, "$ORIGIN") || strstr (rsp, "${ORIGIN}")) {
      mdt_flags |= DF_ORIGIN;
    }
  }

  if ((arg_compliance & 1) || (dt_flags != 0)) {
    mdt_flags |= dt_flags;
    ne.dyn[dte].d_tag = DT_FLAGS;
    ne.dyn[dte].d_un.d_val = mdt_flags;
    dte++;
    printf ("FLAGS = "PRIex"\n", mdt_flags);
    work |= WORK_FLAGS;
  }

  for (dti = 0; dti < e.e_dynum; dti++) {
    const Elf_Dyn *dyn = &e.dyn[dti];

    switch (dyn->d_tag) {
      case DT_SONAME:
      case DT_RPATH:
      case DT_RUNPATH:
      case DT_NEEDED:
        /* All taken care of above */
        break;

      case DT_FLAGS:
        if (0 == (work & WORK_FLAGS)) {
          ne.dyn[dte].d_tag = dyn->d_tag;
          ne.dyn[dte].d_un.d_val = dyn->d_un.d_val;
          dte++;
        }
        break;

      case DT_STRSZ:
        ne.dyn[dte].d_tag = dyn->d_tag;
        ne.dyn[dte].d_un.d_val = ne.dt_strsz;
        dte++;
        break;

      case DT_BIND_NOW:
      case DT_SYMBOLIC:
      case DT_TEXTREL:
        if (arg_compliance & 1) {
          work |= WORK_ABI_COMPLIANCE;
          break;
        }
        /* FALLTHROUGH */

      default:
        ne.dyn[dte].d_tag = dyn->d_tag;
        ne.dyn[dte].d_un.d_val = dyn->d_un.d_val;
        dte++;
        break;
    }
  }

  /*
   * Start the offset counter. This measures where in the output file we're at
   * so that we can produce correct values in our duplicated structures above.
   */
  offset = e.ehdr->e_ehsize;

  /*
   * Regardless of the original file order, when WE write the output file it
   * is always ELF header -> program header table -> sections -> section table.
   * Since the first word of a program header is a 4-byte word, by the gABI
   * alignment rules that is what we align the start of the program header
   * table to.
   */
  offset = add_alignment (offset, 4);
  ne.ehdr->e_phoff = offset;

  offset += (e.ehdr->e_phnum * e.ehdr->e_phentsize);
  offset = add_alignment (offset, sizeof (ecuint_t));

  /*
   * Do the actual processing we're here to do. We'll start with the
   * interpreter. We only do this if the file already has an interpreter. Any
   * executable file that was missing an interpreter has already been weeded
   * out by the time we get here. It is a-typical for shared objects to have
   * an interpreter, but the gABI does allow for it. So if the file contains
   * a PT_INTERP program header we will obey the user's desire to change it,
   * even though it has no meaning.
   */
  if ((e.interp_ph != 0) && arg_interpreter) {
    const char *ci = (const char *)data + e.phdr[e.interp_ph].p_offset;

    if (strcmp (ci, arg_interpreter)) {
      if (e.interp_sh == 0) {
        fprintf (stderr, "%s: warning: section not found - not changing interpreter for `%s'.\n", progname, curfile);
      } else {
        work |= WORK_INTERPRETER;
      }
    }
  }

  free (soname);
  free (rpath);
  free (runpath);
  free (ne.dynstrs);
  free (ne.dyn);
  free (ne.shdr);
  free (ne.phdr);
  free (ne.ehdr);
  sl_free (needed);

  return 0;
}

/*
 * vim: set cino=>2,e0,n0,f0,{2,}0,^0,\:2,=2,p2,t2,c1,+2,(2,u2,)20,*30,g2,h2:
 * vim: set expandtab:
 */
