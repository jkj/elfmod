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

typedef struct _strlist_t {
  int nstrs;    /* Number of strings in the list */
  int strsz;    /* Size of the string list */
  char **strs;  /* Actual strings in the list */
} strlist_t;

static inline strlist_t *
sl_new(int numstrs)
{
  strlist_t *lst = (strlist_t *)calloc(1, sizeof(strlist_t));

  lst->strsz = numstrs;
  lst->strs = (char **)calloc(numstrs, sizeof(char *));

  return lst;
}

static inline void
sl_free(strlist_t *sl)
{
  int i;

  if (0 == sl) {
    return;
  }

  for (i = 0; i < sl->strsz; i++) {
    free(sl->strs[i]);
    sl->strs[i] = 0;
  }
  free(sl->strs);
  sl->strs = 0;
  free(sl);
}

static inline void
sl_stradd(strlist_t *lst, const char *newstr)
{
  int i, avail = -1;

  for (i = 0; i < lst->strsz; i++) {
    if (0 == lst->strs[i]) {
      if (-1 == avail) {
        avail = i;
      }
      continue;
    }

    if (0 == strcmp(lst->strs[i], newstr)) {
      return;
    }
  }

  if (-1 == avail) {
    lst->strs = (char **)realloc(lst->strs, (lst->strsz + 5) * sizeof(char *));
    for (i = 0; i < 5; i++) {
      lst->strs[lst->strsz + i] = 0;
    }
    avail = lst->strsz;
    lst->strsz += 5;
  }

  lst->strs[avail] = strdup(newstr);
  lst->nstrs++;
}

static inline void
sl_lstadd(strlist_t *sl, const strlist_t *ol)
{
  int i;

  if ((0 == sl) || (0 == ol) || (0 == ol->nstrs)) {
    return;
  }

  for (i = 0; i < ol->strsz; i++) {
    if (ol->strs[i]) {
      sl_stradd(sl, ol->strs[i]);
    }
  }
}

static inline void
sl_splitadd(strlist_t *lst, const char *str, const char *splitcs)
{
  char tstr[2048];
  size_t x;

  if (0 == str[0]) {
    return;
  }

  for (;;) {
    x = strcspn(str, splitcs);
    if (x) {
      memcpy(tstr, str, x);
      tstr[x] = 0;
      sl_stradd(lst, tstr);
    }
    if (0 == str[x]) {
      return;
    }
    str += x + 1;
  }
}

static inline void
sl_strdel(strlist_t *lst, char *str)
{
  int i;

  if (0 == str) {
    return;
  }

  for (i = 0; i < lst->strsz; i++) {
    if (lst->strs[i] == str) {
      free(str);
      lst->strs[i] = 0;
      lst->nstrs--;
      return;
    }
  }
}

static inline void
sl_idxdel(strlist_t *lst, int idx)
{
  if ((idx >= lst->strsz) || (0 == lst->strs[idx])) {
    return;
  }

  free(lst->strs[idx]);
  lst->strs[idx] = 0;
  lst->nstrs--;
}

static inline void
sl_cmpdel(strlist_t *lst, const char *str)
{
  int i;

  if (0 == str) {
    return;
  }

  for (i = 0; i < lst->strsz; i++) {
    if (lst->strs[i] && (0 == strcmp(lst->strs[i], str))) {
      free(lst->strs[i]);
      lst->strs[i] = 0;
      lst->nstrs--;
      return;
    }
  }
}

static inline void
sl_lstdel(strlist_t *lst, const strlist_t *olst)
{
  int i;

  for (i = 0; i < olst->strsz; i++) {
    if (olst->strs[i]) {
      sl_cmpdel(lst, olst->strs[i]);
    }
  }
}

static inline char *
sl_join(const strlist_t *sl, int joinc)
{
  char *rs, js[2];
  int i;
  size_t tl = 0;

  if ((0 == sl) || (0 == sl->nstrs)) {
    return 0;
  }

  js[0] = joinc;
  js[1] = 0;

  for (i = 0; i < sl->strsz; i++) {
    if (sl->strs[i] && sl->strs[i][0]) {
      tl += strlen(sl->strs[i]) + 1;
    }
  }
  tl++;

  rs = (char *)calloc(tl, 1);
  tl = 0;

  for (i = 0; i < sl->strsz; i++) {
    if (sl->strs[i] && sl->strs[i][0]) {
      if (tl) {
        strcat(rs, js);
      }
      strcat(rs, sl->strs[i]);
      tl++;
    }
  }

  return rs;
}

/*
 * vim: set cino=>2,e0,n0,f0,{2,}0,^0,\:2,=2,p2,t2,c1,+2,(2,u2,)20,*30,g2,h2:
 * vim: set expandtab:
 */
