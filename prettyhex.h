/*-
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
#ifndef ELFMOD_PRETTYHEX_H
#define ELFMOD_PRETTYHEX_H

#include <stddef.h>
#include <stdint.h>

#define HPP_OFFSET_16 (1 << 0)  /* Prefix with 16 bit offset */
#define HPP_OFFSET_32 (1 << 1)  /* Prefix with 32 bit offset */
#define HPP_GROUP_8 (1 << 2)    /* Group every 8 bytes */
#define HPP_GROUP_16 (1 << 3)   /* Group every 16 bytes */
#define HPP_ASCII (1 << 4)      /* Print ASCII after bytes */
#define HPP_ASCII_ONLY (1 << 5) /* Only print ASCII dump */
#define HPP_LEAD_FIRST (1 << 6) /* Print leader first time around otherwise don't */

extern void prettyhex(const unsigned char *data, size_t len, uint32_t offs, uint32_t flags, const char *leader);

#endif /* ELFMOD_PRETTYHEX_H */

/*
 * vim: set cino=>2,e0,n0,f0,{2,}0,^0,\:2,=2,p2,t2,c1,+2,(2,u2,)20,*30,g2,h2:
 * vim: set expandtab:
 */
