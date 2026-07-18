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
#ifndef ELFMOD_H
#define ELFMOD_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include <sys/types.h>

#include "elf.h"
#include "strlist.h"

#define plural(X) (X), (X) == 1 ? "" : "s"
#define pluraly(X) (X), (X) == 1 ? "y" : "ies"

/*
 * Set of bits that indicate what portions of the file(s) to display in a
 * human readable form.
 */
#define DISPLAY_INTERP          (1U << 0)
#define DISPLAY_SONAME          (1U << 1)
#define DISPLAY_NEEDED          (1U << 2)
#define DISPLAY_FLAGS           (1U << 3)
#define DISPLAY_RPATH           (1U << 4)
#define DISPLAY_RUNPATH         (1U << 5)
#define DISPLAY_DYNAMIC         (1U << 6)
#define DISPLAY_HEADERS         (1U << 7)
#define DISPLAY_NUMENT          8
#define DISPLAY_DEBUG           (1U << DISPLAY_NUMENT)

#define DISPLAY_EVERYTHING      ((1U << DISPLAY_NUMENT) - 1)

extern const char *progname;
extern const char *curfile;

extern uint32_t emdisplay_before;
extern uint32_t emdisplay_after;

/*
 * Options gathered from the command line, defined in elfmod.c and consumed
 * by the per-class file processors.
 */
extern const char *arg_interpreter;
extern const char *arg_soname;
extern strlist_t *arg_abspath;
extern strlist_t *arg_abs_nomatch;
extern strlist_t *arg_abs_mustmatch;
extern strlist_t *arg_needed_add;
extern strlist_t *arg_needed_del;
extern strlist_t *arg_rpath_add;
extern strlist_t *arg_rpath_del;
extern const char *arg_rpath_set;
extern strlist_t *arg_runpath_add;
extern strlist_t *arg_runpath_del;
extern const char *arg_runpath_set;
extern int arg_compliance;

extern char *make_absolute(char *path);

/*
 * process.c dispatches on the ELF class in the file being processed to one
 * of the class-specific processors built from realproc.inc (see proc32.c
 * and proc64.c).
 */
extern int process_file(unsigned char *data, size_t dlen);
extern int process_file_32(unsigned char *data, size_t dlen);
extern int process_file_64(unsigned char *data, size_t dlen);

#endif /* ELFMOD_H */

/*
 * vim: set cino=>2,e0,n0,f0,{2,}0,^0,\:2,=2,p2,t2,c1,+2,(2,u2,)20,*30,g2,h2:
 * vim: set expandtab:
 */
