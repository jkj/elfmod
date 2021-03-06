#ifndef SHTYPEENT
#error "SHTYPEENT must be defined before including sh_type.h"
#endif

SHTYPEENT(NULL, "Unused")
SHTYPEENT(PROGBITS, "Program defined information")
SHTYPEENT(SYMTAB, "Symbol table")
SHTYPEENT(STRTAB, "String table")
SHTYPEENT(RELA, "Relocations with addends")
SHTYPEENT(HASH, "Symbol hash table")
SHTYPEENT(DYNAMIC, "Dynamic linking info")
SHTYPEENT(NOTE, "Note")
SHTYPEENT(NOBITS, "Program space with no data")
SHTYPEENT(REL, "Relocations without addends")
SHTYPEENT(SHLIB, "Reserved")
SHTYPEENT(DYNSYM, "Dynamic symbol table")
SHTYPEENT(INIT_ARRAY, "Initialization functions array")
SHTYPEENT(FINI_ARRAY, "Termination functions array")
SHTYPEENT(PREINIT_ARRAY, "Pre-initialization functions array")
SHTYPEENT(GROUP, "Section group")
SHTYPEENT(SYMTAB_SHNDX, "Extended section info")
SHTYPEENT(GNU_ATTRIBUTES, "Object attributes")
SHTYPEENT(GNU_HASH, "GNU-style hash table")
SHTYPEENT(GNU_LIBLIST, "Prelink library list")
SHTYPEENT(CHECKSUM, "DSO checksum data")
SHTYPEENT(GNU_verdef, "Symbol version definitions")
SHTYPEENT(GNU_verneed, "Symbol versions required")
SHTYPEENT(GNU_versym, "Symbol version table")
SHTYPEENT(X86_64_UNWIND, "Unwind information")
