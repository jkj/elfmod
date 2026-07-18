# Makefile for elfmod. So simple your grandmother could have written it.

# If you want to use large files, arrange for the correct flags here. You
# must also add -DUSING_LFS to the required flags.
LFSFLAGS=-DUSING_LFS -D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64
CC=gcc
CFLAGS=-g -W -Wall -Wextra $(LFSFLAGS)
PROGRAM=elfmod

OBJS=elfmod.o strlist.o prettyhex.o process.o proc32.o proc64.o

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

all: $(PROGRAM)

clean:
	-rm -f $(PROGRAM) *.o

# The -rpath here is intentional junk: it gives the resulting binary a
# DT_RUNPATH entry so that elfmod can be used to test itself.
$(PROGRAM): $(OBJS)
	$(CC) -o $@ $(OBJS) -Wl,-rpath,/usr/foo/bar

# Headers everything that touches ELF files depends on.
CORE_HDRS=elfmod.h elf.h strlist.h

# The per-class processors are both built from the realproc.inc template,
# which also pulls in the X-macro description tables.
PROC_DEPS=realproc.inc $(CORE_HDRS) prettyhex.h \
 dyn_dtags.h osabi.h e_machine.h p_type.h sh_type.h

elfmod.o: elfmod.c $(CORE_HDRS)
strlist.o: strlist.c strlist.h
prettyhex.o: prettyhex.c prettyhex.h
process.o: process.c $(CORE_HDRS)
proc32.o: proc32.c $(PROC_DEPS)
proc64.o: proc64.c $(PROC_DEPS)
