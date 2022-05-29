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

#define HPP_OFFSET_16 (1 << 0)  /* Prefix with 16 bit offset */
#define HPP_OFFSET_32 (1 << 1)  /* Prefix with 32 bit offset */
#define HPP_GROUP_8 (1 << 2)    /* Group every 8 bytes */
#define HPP_GROUP_16 (1 << 3)   /* Group every 16 bytes */
#define HPP_ASCII (1 << 4)      /* Print ASCII after bytes */
#define HPP_ASCII_ONLY (1 << 5) /* Only print ASCII dump */
#define HPP_LEAD_FIRST (1 << 6) /* Print leader first time around otherwise don't */

static const char *spaces = "                                                                                                               ";

static inline void
do_one_ascii(int c)
{
  if ((c <= ' ') || (c >= 0x7f)) {
    c = '.';
  }

  putc(c, stdout);
}

static void
prettyhex(const unsigned char *data, size_t len, uint32_t offs, uint32_t flags, const char *leader)
{
  uint32_t coffs = offs, slen;
  const unsigned char *adata;
  int first = 1;
  int numspc;

  if ((0 == data) || (0 == len)) {
    return;
  }

  if (0 == leader) {
    leader = "";
  }

  if (0 == (flags & (HPP_GROUP_8 | HPP_GROUP_16))) {
    flags &= ~HPP_ASCII;
  }

  while (len) {
    if (flags & (HPP_OFFSET_16 | HPP_OFFSET_32)) {
      if (first) {
        first = 0;
        if (flags & HPP_LEAD_FIRST) {
          printf("%s", leader);
        }
      } else {
        printf("%s", leader);
      }
    }

    if (flags & HPP_OFFSET_16) {
      printf("0x%04" PRIx32 ": ", coffs);
    } else if (flags & HPP_OFFSET_32) {
      printf("0x%08" PRIx32 ": ", coffs);
    }

    adata = data;
    slen = len;

    if (flags & HPP_GROUP_16) {
      if (len > 16) {
        slen = 16;
      }
    } else if (flags & HPP_GROUP_8) {
      if (len > 8) {
        slen = 8;
      }
    } else {
      if (flags & HPP_ASCII_ONLY) {
        do_one_ascii(*data);
      } else {
        printf("%02" PRIx8 " ", *data);
      }
      data++;
      len--;
      coffs++;
      continue;
    }

    switch (slen) {
      case 16:
        printf("%02" PRIx8 " ", *data); data++;
        /* FALLTHRU */
      case 15:
        printf("%02" PRIx8 " ", *data); data++;
        /* FALLTHRU */
      case 14:
        printf("%02" PRIx8 " ", *data); data++;
        /* FALLTHRU */
      case 13:
        printf("%02" PRIx8 " ", *data); data++;
        /* FALLTHRU */
      case 12:
        printf("%02" PRIx8 " ", *data); data++;
        /* FALLTHRU */
      case 11:
        printf("%02" PRIx8 " ", *data); data++;
        /* FALLTHRU */
      case 10:
        printf("%02" PRIx8 " ", *data); data++;
        /* FALLTHRU */
      case 9:
        printf("%02" PRIx8 "  ", *data); data++;
        /* FALLTHRU */
      case 8:
        printf("%02" PRIx8 " ", *data); data++;
        /* FALLTHRU */
      case 7:
        printf("%02" PRIx8 " ", *data); data++;
        /* FALLTHRU */
      case 6:
        printf("%02" PRIx8 " ", *data); data++;
        /* FALLTHRU */
      case 5:
        printf("%02" PRIx8 " ", *data); data++;
        /* FALLTHRU */
      case 4:
        printf("%02" PRIx8 " ", *data); data++;
        /* FALLTHRU */
      case 3:
        printf("%02" PRIx8 " ", *data); data++;
        /* FALLTHRU */
      case 2:
        printf("%02" PRIx8 " ", *data); data++;
        /* FALLTHRU */
      case 1:
        printf("%02" PRIx8 " ", *data); data++;
        /* FALLTHRU */
    }

    len -= slen;
    coffs += slen;

    if (flags & HPP_ASCII) {
      if (flags & HPP_GROUP_16) {
        numspc = (((16 - slen) + 1) * 3) - 1;
        if (slen <= 8) {
          numspc++;
        }
      } else {
        numspc = (((8 - slen) + 1) * 3) - 1;
      }
      printf("%.*s", numspc, spaces);

      switch (slen) {
        case 16:
          do_one_ascii(*adata); adata++;
          /* FALLTHRU */
        case 15:
          do_one_ascii(*adata); adata++;
          /* FALLTHRU */
        case 14:
          do_one_ascii(*adata); adata++;
          /* FALLTHRU */
        case 13:
          do_one_ascii(*adata); adata++;
          /* FALLTHRU */
        case 12:
          do_one_ascii(*adata); adata++;
          /* FALLTHRU */
        case 11:
          do_one_ascii(*adata); adata++;
          /* FALLTHRU */
        case 10:
          do_one_ascii(*adata); adata++;
          /* FALLTHRU */
        case 9:
          do_one_ascii(*adata); adata++;
          putc(' ', stdout);
          /* FALLTHRU */
        case 8:
          do_one_ascii(*adata); adata++;
          /* FALLTHRU */
        case 7:
          do_one_ascii(*adata); adata++;
          /* FALLTHRU */
        case 6:
          do_one_ascii(*adata); adata++;
          /* FALLTHRU */
        case 5:
          do_one_ascii(*adata); adata++;
          /* FALLTHRU */
        case 4:
          do_one_ascii(*adata); adata++;
          /* FALLTHRU */
        case 3:
          do_one_ascii(*adata); adata++;
          /* FALLTHRU */
        case 2:
          do_one_ascii(*adata); adata++;
          /* FALLTHRU */
        case 1:
          do_one_ascii(*adata); adata++;
          /* FALLTHRU */
      }
    }
    putc('\n', stdout);
  }
}

/*
 * vim: set cino=>2,e0,n0,f0,{2,}0,^0,\:2,=2,p2,t2,c1,+2,(2,u2,)20,*30,g2,h2:
 * vim: set expandtab:
 */
