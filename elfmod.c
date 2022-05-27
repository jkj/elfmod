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
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <inttypes.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fnmatch.h>

#include "elf.h"

#define plural(X) (X), (X) == 1 ? "" : "s"
#define pluraly(X) (X), (X) == 1 ? "y" : "ies"

static const char * const version = "1.0";
static const char * const github_url = "https://github.com/jkj/elfmod";
static const char * const copyright = "(C) Copyright 2016-2022 Kean Johnston. All rights reserved.";

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

static const char *progname = 0;
static const char *curfile = 0;
static int host_byteorder = 0;

/*
 * Set of bits that indicate what portions of the file(s) to display in a
 * human readable form.
 */
static uint32_t emdisplay_before = 0;
static uint32_t emdisplay_after  = 0;

static void
display_usage (FILE *where)
{
  if (0 == progname) {
    progname = "elfmod";
  }

  fprintf (where, "Usage: %s option(s) filename(s)\n"
    "\n"
    "Options that begin with a + add values, that begin with a - remove values and\n"
    "that begin with an = set values. Some options that begin with a - will perform\n"
    "an action rather than removing a value. Upper case options display the current\n"
    "setting in the file. Display options that use a - will be shown before any\n"
    "other work is done, and those that use a + will be shown after the file is\n"
    "written and all other options have been processed.\n"
    "\n", progname);

  fprintf (where,
    "=i interpreter / -I / +I\n"
    "  Only for executables. Set / display the interpreter. You can not remove the\n"
    "  interpreter and you can not have more than one which is why there is only a\n"
    "  set option.\n"
    "\n");

  fprintf (where,
    "=s soname / -S / +S\n"
    "  Only for shared libraries. Sets or displays the shared object name. You can\n"
    "  not remove the shared object name and you can not have more than one.\n"
    "\n");

  fprintf (where,
    "+n needed / -n needed / -N / +N\n"
    "  Sets a dependency or displays them. Can be used multiple times to add or\n"
    "  remove more than 1 needed entry.\n"
    "\n");

#if 0
  fprintf (where,
    "+f flag / -f flag / -F / +F\n"
    "  Sets, removes or displays one or more of the following flags:\n"
    "    ORIGIN     - one or more of the needed dependencies makes use of $ORIGIN\n"
    "    SYMBOLIC   - search shared library for symbols first\n"
    "    TEXTREL    - writeable text relocations exist\n"
    "    BIND_NOW   - do all symbol resolution on load\n"
    "    STATIC_TLS - object uses static TLS\n"
    "\n");
#endif

  fprintf (where,
    "+p path / -p path / =p path / -P / +P\n"
    "  Sets, removes or displays the library search path(s). This works with the\n"
    "  DT_RPATH tag, which has officially been deprecated in the ELF gABI. If at all\n"
    "  possible use +r instead. See the README for a discussion. You can not use the\n"
    "  =p option alongside -p / +p. Either set the value (=p) or add or remove\n"
    "  entries with +p / -p, but not both. -p, +p and =p are mutually exclusive with\n"
    "  -r, +r and =r.\n"
    "\n");

  fprintf (where,
    "+r path / -r path / =r path / -R / +R\n"
    "  Sets, removes or displays the library search path(s). This works with the\n"
    "  DT_RUNPATH tag, which is the official new way of setting these paths in the\n"
    "  ELF gABI. See the README for a discussion. You can not use the =r option\n"
    "  along with -r / +r. Either set the value (=r) or add or remove entries with\n"
    "  -r / +r, but not both. -r, +r and =r are mutually exclusive with -p, +p and\n"
    "  =p.\n"
    "\n");

  fprintf (where,
    "-c\n"
    "  Makes the object compliant with the current draft of the ELF gABI. This\n"
    "  involes removing various DT_ tags and replacing them with a DT_FLAGS entry\n"
    "  with the appropriate flags set. If any of the DT_NEEDED entries uses $ORIGIN\n"
    "  or ${ORIGIN}, set the appropriate flag.\n"
    "\n"
    "+c\n"
    "  Makes the object compliant with the current gABI by replacing any DT_RPATH\n"
    "  dynamic entries with DT_RUNPATH. If the object already has a DT_RUNPATH entry\n"
    "  (in other words it has both DT_RPATH and DT_RUNPATH) then this option will\n"
    "  not make any additional changes to the file.\n"
    "\n");

  fprintf (where,
    "-A / +A\n"
    "  Display all of the entries above. Equivalent to -I -N -S -F -P -R.\n"
    "\n"
    "-d / +d\n"
    "  Full dump of the dynamic section and related entries.\n"
    "\n"
    "-D / +D / =D\n"
    "  Like -d but also includes a dump of the file header, the full section list\n"
    "  and section to segment map, any NOTE sections, and the .comment section, if\n"
    "  it exists. =D will enable debug output that will include a raw hex dump of\n"
    "  each section displayed. It will apply to both -D and +D. When displaying the\n"
    "  section data the flags field uses the following:\n"
    "   a=allocated w=writeable x=executable m=merge s=strings i=info l=link order\n"
    "   o=OS specific g=group t=TLS c=compressed O=ordered e=exclude\n"
    "\n");

  fprintf (where,
    "=a path\n"
    "  Makes any non-absolute names absolute, prepending the specified path to all\n"
    "  such entries. This includes shared object names and needed library names. Any\n"
    "  name that uses $ORIGIN or that is already absolute will be ignored.\n"
    "\n"
    "  Sometimes there are libraries (such as libc.so.6) that you do not want to be\n"
    "  made absolute, so this tool will only use libraries that actually exist in\n"
    "  the path. However, you may be running this on \"staged\" files that have not\n"
    "  yet been installed, so it cannot simply look in the specified path. In such\n"
    "  cases the path can be split into two parts, seperated by a colon. If this is\n"
    "  the case then the first part of the path is the root of the staging area, and\n"
    "  the second part is the absolute path to use, which must exist within that\n"
    "  root. For example suppose you have staged your installation in `/tmp/stage'\n"
    "  and the destination install path is `/usr/local/lib'. The staging directory\n"
    "  will then contain the shared objects in `/tmp/stage/usr/local/lib' and you\n"
    "  want to ensure that all shared library names are absolute. In this case you\n"
    "  would use the value `/tmp/stage:/usr/local/lib' as the argument to this\n"
    "  option.\n"
    "\n"
    "  This option can be specified multiple times if you have multiple directories\n"
    "  that contain shared libraries. Note that if all shared references are absolute\n"
    "  then the RTLD will have no need for using DT_RPATH or DT_RUNPATH entries.\n"
    "\n"
    "  Also note that this option applies to all paths, including options passed to\n"
    "  this program. So if you specify an SONAME, and it is not absolute, and can be\n"
    "  made absolute by this option, it will be.\n"
    "\n"
    "-a pattern\n"
    "  When using the =a option above, it is sometimes desirable to exclude certain\n"
    "  files from being made absolute. This option, which can be used multiple times\n"
    "  to add multiple patterns, will set a pattern against which any candidates for\n"
    "  being made absolute by the +a option are matched. If the match succeeds, then\n"
    "  the file is not made absolute. See +a below for how files are matched.\n"
    "\n"
    "+a pattern\n"
    "  The opposite of -a above. If set then any file that is a candidate for being\n"
    "  made absolute MUST match the pattern specified. These patterns are matched\n"
    "  after any -a options have had a chance to exclude files.\n"
    "\n"
    "  Files are matched using the POSIX function fnmatch(). The basic options used\n"
    "  are FNM_PATHNAME | FNM_PERIOD. If you are using a system that supports it then\n"
    "  the GNU-specific option FNM_EXTMATCH is also used. Please consult your system\n"
    "  manual pages for details.\n"
    "\n");

  fprintf (where,
    "-V\n"
    "  Display the version number and exit.\n"
    "\n");
}

#include "strlist.c"
#include "prettyhex.c"

static const char *arg_interpreter = 0;
static const char *arg_soname = 0;
static strlist_t *arg_abspath = 0;
static strlist_t *arg_abs_nomatch = 0;
static strlist_t *arg_abs_mustmatch = 0;
static strlist_t *arg_needed_add = 0;
static strlist_t *arg_needed_del = 0;
static strlist_t *arg_rpath_add = 0;
static strlist_t *arg_rpath_del = 0;
static const char *arg_rpath_set = 0;
static strlist_t *arg_runpath_add = 0;
static strlist_t *arg_runpath_del = 0;
static const char *arg_runpath_set = 0;
static int arg_compliance = 0;

static char *
make_absolute (char *path)
{
  int i, ret, amatch = 0, fmatch = 0;
  struct stat sb;
  char absroot[2048], abspath[1024], lib[1024], *s;
  int flags = FNM_PATHNAME | FNM_PERIOD;

#ifdef FNM_EXTMATCH
  flags |= FNM_EXTMATCH;
#endif

  if (0 == arg_abspath || 0 == arg_abspath->nstrs || 0 == path) {
    return path;
  }

  if (strchr (path, '/')) {
    return path;
  }

  if (strstr (path, "$ORIGIN") || strstr (path, "${ORIGIN}")) {
    return path;
  }

  for (i = 0; i < arg_abs_nomatch->strsz; i++) {
    char *nm = arg_abs_nomatch->strs[i];

    if (0 == nm) {
      continue;
    }

    if (0 == fnmatch (nm, path, flags)) {
      return path;
    }
  }

  for (i = 0; i < arg_abs_mustmatch->strsz; i++) {
    char *nm = arg_abs_mustmatch->strs[i];

    if (0 == nm) {
      continue;
    }

    amatch++;

    if (0 == fnmatch (nm, path, flags)) {
      fmatch = 1;
      break;
    }
  }

  if (amatch && (0 == fmatch)) {
    return path;
  }

  for (i = 0; i < arg_abspath->strsz; i++) {
    char *ap = arg_abspath->strs[i];

    if (0 == ap) {
      continue;
    }

    s = strchr (ap, ':');
    if (s) {
      strcpy (absroot, ap);
      absroot[s - ap] = 0;
      s++;
      strcpy (abspath, s);
    } else {
      strcpy (abspath, ap);
      absroot[0] = 0;
    }

    sprintf (lib, "%s%s/%s", absroot, abspath, path);
    ret = stat (lib, &sb);

    if (0 == ret) {
      free (path);
      return (strdup (lib));
    }
  }

  return path;
}

#include "process.c"

union msblsb{
  uint16_t ival;
  uint8_t  bval[2];
} bocheck;

int
main (int argc, const char * const argv[])
{
  int i, ret, fd;
  int files = 0, gotwork = 0;
  size_t sl;
  struct stat statbuf;
  uint32_t *emdisplay;
  void *vmaddr;
  size_t flen;
  ssize_t bytes_read;
  unsigned char ehdr[EI_NIDENT];

  sl = strlen (argv[0]);
  if (sl < 1) {
    return 1;
  }
  progname = &argv[0][sl-1];

  while (progname >= argv[0]) {
    if ((*progname == '/') || (*progname == '\\')) {
      progname++;
      break;
    }
    progname--;
  }

  bocheck.ival = 0x1234;
  if (bocheck.bval[0] == 0x34) {
    host_byteorder = ELFDATA2LSB;
  } else {
    host_byteorder = ELFDATA2MSB;
  }

  arg_abspath = sl_new (1);
  arg_abs_nomatch = sl_new (1);
  arg_abs_mustmatch = sl_new (1);
  arg_needed_add = sl_new (1);
  arg_needed_del = sl_new (1);
  arg_rpath_add = sl_new (1);
  arg_rpath_del = sl_new (1);
  arg_runpath_add = sl_new (1);
  arg_runpath_del = sl_new (1);

  for (i = 1; i < argc; i++) {
    const char *arg = argv[i];

    if ((arg[0] == '+') || (arg[0] == '-') || (arg[0] == '=')) {
      if (arg[0] == '-') {
        emdisplay = &emdisplay_before;
      } else if (arg[0] == '+') {
        emdisplay = &emdisplay_after;
      } else {
        emdisplay = 0;
      }

      switch (arg[1]) {
        case 'H':
          display_usage (stdout);
          return 0;
          break;

        case 'V':
          fprintf (stdout, "%s version %s\n", progname, version);
          fprintf (stdout, "%s\n", copyright);
          fprintf (stdout, "Please see the file LICENSE.txt for license details.\n");
          fprintf (stdout, "%s\n", github_url);
          return 0;
          break;

        case 'I':
          if (emdisplay) {
            *emdisplay |= DISPLAY_INTERP;
            gotwork = 1;
          } else {
            goto badarg;
          }
          break;

        case 'S':
          if (emdisplay) {
            *emdisplay |= DISPLAY_SONAME;
            gotwork = 1;
          } else {
            goto badarg;
          }
          break;

        case 'N':
          if (emdisplay) {
            *emdisplay |= DISPLAY_NEEDED;
            gotwork = 1;
          } else {
            goto badarg;
          }
          break;

        case 'F':
          if (emdisplay) {
            *emdisplay |= DISPLAY_FLAGS;
            gotwork = 1;
          } else {
            goto badarg;
          }
          break;

        case 'P':
          if (emdisplay) {
            *emdisplay |= DISPLAY_RPATH;
            gotwork = 1;
          } else {
            goto badarg;
          }
          break;

        case 'R':
          if (emdisplay) {
            *emdisplay |= DISPLAY_RUNPATH;
            gotwork = 1;
          } else {
            goto badarg;
          }
          break;

        case 'd':
          if (emdisplay) {
            *emdisplay |= DISPLAY_DYNAMIC;
            gotwork = 1;
          } else {
            goto badarg;
          }
          break;

        case 'D':
          if (arg[0] == '=') {
            emdisplay_before |= (DISPLAY_HEADERS | DISPLAY_DYNAMIC | DISPLAY_DEBUG);
            emdisplay_after |= (DISPLAY_HEADERS | DISPLAY_DYNAMIC | DISPLAY_DEBUG);
          } else {
            *emdisplay |= (DISPLAY_HEADERS | DISPLAY_DYNAMIC);
          }
          gotwork = 1;
          break;

        case 'A':
          if (arg[0] == '=') {
            emdisplay_before |= (DISPLAY_INTERP | DISPLAY_SONAME | DISPLAY_NEEDED);
            emdisplay_before |= (DISPLAY_FLAGS | DISPLAY_RPATH | DISPLAY_RUNPATH);
            emdisplay_after |= (DISPLAY_INTERP | DISPLAY_SONAME | DISPLAY_NEEDED);
            emdisplay_after |= (DISPLAY_FLAGS | DISPLAY_RPATH | DISPLAY_RUNPATH);
          } else {
            *emdisplay |= (DISPLAY_INTERP | DISPLAY_SONAME | DISPLAY_NEEDED);
            *emdisplay |= (DISPLAY_FLAGS | DISPLAY_RPATH | DISPLAY_RUNPATH);
          }
          gotwork = 1;
          break;

        case 'i':
          if (arg[0] != '=') {
            goto badarg;
          }
          if (i == argc - 1) {
missing:
            fprintf (stderr, "%s: option %c%c missing argument. See %s -H for usage.\n", progname, arg[0], arg[1], progname);
            return 1;
          }
          arg_interpreter = argv[++i];
          gotwork = 1;
          break;

        case 's':
          if (arg[0] != '=') {
            goto badarg;
          }
          if (i == argc - 1) {
            goto missing;
          }
          arg_soname = argv[++i];
          gotwork = 1;
          break;

        case 'a':
          if (i == argc - 1) {
            goto missing;
          }
          if (arg[0] == '=') {
            sl_stradd (arg_abspath, argv[++i]);
          } else if (arg[0] == '-') {
            sl_stradd (arg_abs_nomatch, argv[++i]);
          } else if (arg[0] == '+') {
            sl_stradd (arg_abs_mustmatch, argv[++i]);
          } else {
            goto badarg;
          }
          gotwork = 1;
          break;

        case 'n':
          if (i == argc - 1) {
            goto missing;
          }
          if (arg[0] == '+') {
            sl_stradd (arg_needed_add, argv[++i]);
          } else if (arg[0] == '-') {
            sl_stradd (arg_needed_del, argv[++i]);
          } else {
            goto badarg;
          }
          gotwork = 1;
          break;

        case 'r':
          if (i == argc - 1) {
            goto missing;
          }
          if (arg[0] == '+') {
            sl_stradd (arg_runpath_add, argv[++i]);
          } else if (arg[0] == '-') {
            sl_stradd (arg_runpath_del, argv[++i]);
          } else if (arg[0] == '=') {
            arg_runpath_set = argv[++i];
          } else {
            goto badarg;
          }
          gotwork = 1;
          break;

        case 'p':
          if (i == argc - 1) {
            goto missing;
          }
          if (arg[0] == '+') {
            sl_stradd (arg_rpath_add, argv[++i]);
          } else if (arg[0] == '-') {
            sl_stradd (arg_rpath_del, argv[++i]);
          } else if (arg[0] == '=') {
            arg_rpath_set = argv[++i];
          } else {
            goto badarg;
          }
          gotwork = 1;
          break;

        case 'c':
          if (arg[0] == '-') {
            arg_compliance |= 1;
          } else if (arg[0] == '+') {
            arg_compliance |= 2;
          } else {
            goto badarg;
          }
          gotwork = 1;
          break;

        default:
badarg:
          fprintf (stderr, "%s: unknown option `%c%c'. See %s -H for usage.\n", progname, arg[0], arg[1], progname);
          return 1;
      }
    } else {
      files = i;
      break;
    }
  }

  if (arg_rpath_set && (arg_rpath_add->nstrs + arg_rpath_del->nstrs)) {
    fprintf (stderr, "%s: error: cannot use =p and -p or +p. See %s -H for usage.\n", progname, progname);
    return 1;
  }

  if (arg_runpath_set && (arg_runpath_add->nstrs + arg_runpath_del->nstrs)) {
    fprintf (stderr, "%s: error: cannot use =r and -r or +r. See %s -H for usage.\n", progname, progname);
    return 1;
  }

  if ((arg_rpath_set || (arg_rpath_add->nstrs + arg_rpath_del->nstrs)) && (arg_runpath_set || (arg_runpath_add->nstrs + arg_runpath_del->nstrs))) {
    fprintf (stderr, "%s: error: cannot mix -p/+p/=p and -r/+r/=r. See %s -H for usage.\n", progname, progname);
    return 1;
  }

  if (0 == files) {
    fprintf (stderr, "%s error: missing file(s) to process. See %s -H for usage.\n", progname, progname);
    return 1;
  }

  if (0 == gotwork) {
    printf ("%s: nothing to do.\n", progname);
    return 0;
  }

  if (arg_soname && files > 1) {
    fprintf (stderr, "%s error: =s only makes sense with a single file. See %s -H.\n", progname, progname);
    return 1;
  }

  for (i = files; i < argc; i++) {
    curfile = argv[i];

    ret = stat (argv[i], &statbuf);

    if (ret < 0) {
      fprintf (stderr, "%s error: could not stat `%s': %s\n", progname, curfile, strerror(errno));
      return 1;
    }

    if (S_ISDIR(statbuf.st_mode) || S_ISCHR(statbuf.st_mode) || S_ISBLK(statbuf.st_mode)) {
      fprintf (stderr, "%s warning: skipping `%s' - not a regular file.\n", progname, curfile);
      continue;
    }

    fd = open (curfile, O_RDONLY);
    if (fd < 0) {
      fprintf (stderr, "%s error: could not open `%s': %s\n", progname, curfile, strerror(errno));
      return 1;
    }

    /*
     * Verify that the specified file is a valid ELF file (or the very least
     * has a valid ELF header) and that it is either a shared objected or an
     * executable. We do not process relocatable or archive objects.
     */
    bytes_read = read (fd, ehdr, EI_NIDENT);
    if (bytes_read != EI_NIDENT) {
      fprintf (stderr, "%s error: could read `%s' header: %s\n", progname, curfile, strerror(errno));
      close (fd);
      return 1;
    }

    if ((ehdr[EI_MAG0] != ELFMAG0) || (ehdr[EI_MAG1] != ELFMAG1) ||
        (ehdr[EI_MAG2] != ELFMAG2) || (ehdr[EI_MAG3] != ELFMAG3) ||
        (ehdr[EI_VERSION] != EV_CURRENT) || ((ehdr[EI_CLASS] != ELFCLASS32) &&
        (ehdr[EI_CLASS] != ELFCLASS64))) {
      fprintf (stderr, "%s warning: skipping non-ELF file `%s'\n", progname, curfile);
      close (fd);
      continue;
    }

    if (ehdr[EI_DATA] != host_byteorder) {
      fprintf (stderr, "%s warning: skipping endian-mismatched file `%s'\n", progname, curfile);
      close (fd);
      continue;
    }

    flen = (size_t)statbuf.st_size;
    vmaddr = mmap (0, flen, PROT_READ, MAP_SHARED, fd, 0);
    if (0 == vmaddr) {
      fprintf (stderr, "%s error: could not map `%s': %s\n", progname, curfile, strerror(errno));
      close (fd);
      return 1;
    }

    close (fd);
    process_file (vmaddr, flen);

    if (munmap (vmaddr, flen)) {
      fprintf (stderr, "%s error: could not unmap `%s': %s\n", progname, curfile, strerror(errno));
      return 1;
    }
  }

  return 0;
}

/*
 * vim: set cino=>2,e0,n0,f0,{2,}0,^0,\:2,=2,p2,t2,c1,+2,(2,u2,)20,*30,g2,h2:
 * vim: set expandtab:
 */
