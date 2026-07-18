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
#ifndef ELFMOD_STRLIST_H
#define ELFMOD_STRLIST_H

typedef struct _strlist_t {
  int nstrs;    /* Number of strings in the list */
  int strsz;    /* Size of the string list */
  char **strs;  /* Actual strings in the list */
} strlist_t;

extern strlist_t *sl_new(int numstrs);
extern void sl_free(strlist_t *sl);
extern void sl_stradd(strlist_t *lst, const char *newstr);
extern void sl_lstadd(strlist_t *sl, const strlist_t *ol);
extern void sl_splitadd(strlist_t *lst, const char *str, const char *splitcs);
extern void sl_strdel(strlist_t *lst, char *str);
extern void sl_idxdel(strlist_t *lst, int idx);
extern void sl_cmpdel(strlist_t *lst, const char *str);
extern void sl_lstdel(strlist_t *lst, const strlist_t *olst);
extern char *sl_join(const strlist_t *sl, int joinc);

#endif /* ELFMOD_STRLIST_H */

/*
 * vim: set cino=>2,e0,n0,f0,{2,}0,^0,\:2,=2,p2,t2,c1,+2,(2,u2,)20,*30,g2,h2:
 * vim: set expandtab:
 */
