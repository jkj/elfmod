# Makefile for elfmod. So simple your grandmother could have written it.

# If you want to use large files, arrange for the correct flags here. You
# must also add -DUSING_LFS to the required flags.
LFSFLAGS=-DUSING_LFS -D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64
CC=gcc
CFLAGS=-g -W -Wall -Wextra $(LFSFLAGS)
PROGRAM=elfmod

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

all: $(PROGRAM)

clean:
	-rm -f $(PROGRAM) *.o

$(PROGRAM): elfmod.o
	$(CC) -o $@ elfmod.o -Wl,-rpath,/usr/foo/bar

elfmod.o: elfmod.c elf.h dyn_dtags.h strlist.c prettyhex.c process.c realproc.c \
 osabi.h e_machine.h p_type.h sh_type.h
