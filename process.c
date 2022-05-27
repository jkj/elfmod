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

#if 0
#define ELFCS "32"
#define ELFT(type) Elf ## 32 ## _ ## type
#define EFC(name) name ## _ ## 32
#define EFCT(name) name ## 32 ## _t
#define PRIex "0x%08"PRIx32
#define PRI8x "0x%08"PRIx32
#define PRIeu "%"PRIu32
#define PRIei "%"PRIi32
#define EXSPACES ""
#include "realproc.c"

#undef ELFCS
#undef ELFT
#undef EFC
#undef EFCT
#undef PRIex
#undef PRIeu
#undef PRIei
#undef EXSPACES
#endif

#define ELFCS "64"
#define ELFT(type) Elf ## 64 ## _ ## type
#define EFC(name) name ## _ ## 64
#define EFCT(name) name ## 64 ## _t
#define PRIex "0x%016"PRIx64
#define PRI8x "0x%08"PRIx64
#define PRIeu "%"PRIu64
#define PRIei "%"PRIi64
#define EXSPACES "        "
#include "realproc.c"

#undef process_file
static void
process_file (unsigned char *data, size_t dlen)
{
#if 0
  if (data[EI_CLASS] == ELFCLASS32) {
    process_file_32 (data, dlen);
  } else {
    process_file_64 (data, dlen);
  }
#else
  process_file_64 (data, dlen);
#endif
}

/*
 * vim: set cino=>2,e0,n0,f0,{2,}0,^0,\:2,=2,p2,t2,c1,+2,(2,u2,)20,*30,g2,h2:
 * vim: set expandtab:
 */
