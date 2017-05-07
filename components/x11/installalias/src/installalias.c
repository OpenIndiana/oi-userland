/*
 * Copyright (c) 1993, 2009, Oracle and/or its affiliates. All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */
/* Code copied from libXfont is:

Copyright 1991, 1998  The Open Group

Permission to use, copy, modify, distribute, and sell this software and its
documentation for any purpose is hereby granted without fee, provided that
the above copyright notice appear in all copies and that both that
copyright notice and this permission notice appear in supporting
documentation.

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
OPEN GROUP BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of The Open Group shall not be
used in advertising or otherwise to promote the sale, use or other dealings
in this Software without prior written authorization from The Open Group.

*/

/*
 * Ensure that a fonts.alias file only contains aliases for fonts that exist
 * We do this by first reading in the fonts.dir file and then for
 * each entry in the fonts.alias file we verify that the alias can
 * be resolved. Most this of this code is borrowed from
 * libXfont with minor modifications. 
 */
#include    <X11/fonts/fntfilst.h>
#include    <stdio.h>
#include    <sys/types.h>
#include    <errno.h>
#include    <sys/stat.h>
#include    <ctype.h>
#include    <limits.h>
#include    <stdarg.h>
#include    <stdlib.h>
#include    <X11/keysym.h>

#define EBadFontPath 0
#define EBadFontName 0
#define EAllocError 0
#define Success 1

pointer serverClient;
static char *programName;

static int lexc(FILE *file);

void
ErrorF (const char * f, ...)
{
    va_list args;

    va_start(args, f);
    fprintf(stderr, "%s: ", programName);
    vfprintf(stderr, f, args);
    va_end(args);
}

/* Provide pseudo renderers for font file formats we may find in fonts.dir
   files during installation, but which libXfont does not support */
/* ARGSUSED */
static int
PseudoOpenScalable (FontPathElementPtr fpe, FontPtr *ppFont, int flags,
		    FontEntryPtr entry, char *fileName, FontScalablePtr vals,
		    fsBitmapFormat format, fsBitmapFormatMask fmask,
		    FontPtr non_cachable_font)
{
    return 1;
}

/* ARGSUSED */
static int
PseudoGetInfoScalable (FontPathElementPtr fpe, FontInfoPtr info,
		       FontEntryPtr entry, FontNamePtr fontName,
		       char *fileName, FontScalablePtr vals)
{
    return 1;
}

static FontRendererRec PseudoRenderers[] = {
    { ".spd", 4, NULL, PseudoOpenScalable, NULL, PseudoGetInfoScalable, 0 }
};

static void
PseudoFontFileRegisterFpeFunctions (void)
{
    int i;

    for (i = 0; i < (sizeof(PseudoRenderers) / sizeof(FontRendererRec)); i++) {
	FontFileRegisterRenderer(&PseudoRenderers[i]);
    }
}

int
ProcessFontsDirectory (
    char		*directory,
    FontDirectoryPtr	*pdir)
{
    char        file_name[MAXFONTNAMELEN];
    char        font_name[MAXFONTNAMELEN];
    char        dir_file[MAXFONTNAMELEN];
    FILE       *file;
    int         count, i;
    struct stat	statb;

    FontDirectoryPtr	dir = NullFontDirectory;

    i = strlcpy(dir_file, directory, sizeof(dir_file));
    if (directory[i - 1] != '/')
	strlcat(dir_file, "/", sizeof(dir_file));
    strlcat(dir_file, FontDirFile, sizeof(dir_file));
    file = fopen(dir_file, "r");
    if (file) {
	if (fstat (fileno(file), &statb) == -1)
	  return EBadFontPath;
	count = fscanf(file, "%d\n", &i);
	if ((count == EOF) || (count != 1)) {
	    fclose(file);
	    return EBadFontPath;
	}
	dir = FontFileMakeDir(directory, i);
	if (dir == NULL) {
	    fclose(file);
	    return EBadFontPath;
	}
	dir->dir_mtime = statb.st_mtime;
	while ((count = fscanf(file, "%1024s %[^\n]\n", file_name, font_name)) 
	       != EOF) {
	    if (count != 2) {
		FontFileFreeDir (dir);
		fclose(file);
		return EBadFontPath;
	    }
	    if (!FontFileAddFontFile (dir, font_name, file_name))
	    {
		FontFileFreeDir (dir);
		fclose(file);
		return EBadFontPath;
	    }
	}
	fclose(file);
    } else if (errno != ENOENT) {
	return EBadFontPath;
    }
    if (!dir)
      return EBadFontPath;

    *pdir = dir;
    return Success;
}

#define NAME            0
#define NEWLINE 	1
#define DONE            2
#define EALLOC          3
#define FileClosed      4

#define QUOTE		0
#define WHITE		1
#define NORMAL		2
#define END		3
#define NL		4

static int  charClass;

static int
lexAlias(
    FILE       *file,
    char      **lexToken)
{
    int         c;
    char       *t;
    enum state {
	Begin, Normal, Quoted
    }           state;
    int         count;

    static char *tokenBuf = (char *) NULL;
    static unsigned int  tokenSize = 0;

    t = tokenBuf;
    count = 0;
    state = Begin;
    for (;;) {
	if (count == tokenSize) {
	    unsigned int nsize;
	    char       *nbuf;

	    nsize = tokenSize ? (tokenSize << 1) : 64;
	    nbuf = realloc(tokenBuf, nsize);
	    if (!nbuf)
		return EALLOC;
	    tokenBuf = nbuf;
	    tokenSize = nsize;
	    t = tokenBuf + count;
	}
	c = lexc(file);
	switch (charClass) {
	case QUOTE:
	    switch (state) {
	    case Begin:
	    case Normal:
		state = Quoted;
		break;
	    case Quoted:
		state = Normal;
		break;
	    }
	    break;
	case WHITE:
	    switch (state) {
	    case Begin:
		continue;
	    case Normal:
		*t = '\0';
		*lexToken = tokenBuf;
		return NAME;
	    case Quoted:
		break;
	    }
	    /* fall through */
	case NORMAL:
	    switch (state) {
	    case Begin:
		state = Normal;
	    }
	    *t++ = c;
	    ++count;
	    break;
	case END:
	case NL:
	    switch (state) {
	    case Begin:
		*lexToken = (char *) NULL;
		return charClass == END ? DONE : NEWLINE;
	    default:
		*t = '\0';
		*lexToken = tokenBuf;
		ungetc(c, file);
		return NAME;
	    }
	}
    }
}

static int
lexc(FILE *file)
{
    int         c;

    c = getc(file);
    switch (c) {
    case EOF:
	charClass = END;
	break;
    case '\\':
	c = getc(file);
	if (c == EOF)
	    charClass = END;
	else
	    charClass = NORMAL;
	break;
    case '"':
	charClass = QUOTE;
	break;
    case ' ':
    case '\t':
	charClass = WHITE;
	break;
    case '\n':
	charClass = NL;
	break;
    default:
	charClass = NORMAL;
	break;
    }
    return c;
}

static inline unsigned char
ISOLatin1ToLower(unsigned char source)
{
    if (source >= XK_A && source <= XK_Z)
        return source + (XK_a - XK_A);
    if (source >= XK_Agrave && source <= XK_Odiaeresis)
        return source + (XK_agrave - XK_Agrave);
    if (source >= XK_Ooblique && source <= XK_Thorn)
        return source + (XK_oslash - XK_Ooblique);
    return source;
}

static void
copyISOLatin1Lowered(char *dest, char *source, int length)
{
    int i;
    for (i = 0; i < length; i++, source++, dest++)
        *dest = ISOLatin1ToLower(*source);
    *dest = '\0';
}

static int
ReadAliases(
    FILE *file,
    char *alias,
    char *font_name)
{
  int			token;
  char		       *lexToken;
  int			status = Success;
  
  while (status == Success) {
    token = lexAlias(file, &lexToken);
    switch (token) {
    case NEWLINE:
      break;
    case DONE:
      fclose(file);
      return FileClosed;
    case EALLOC:
      status = EAllocError;
      break;
    case NAME:
      strlcpy(alias, lexToken, MAXFONTNAMELEN);
      token = lexAlias(file, &lexToken);
      switch (token) {
      case NEWLINE:
	break;
      case DONE:
	status = EBadFontPath;
	break;
      case EALLOC:
	status = EAllocError;
	break;
      case NAME:
	copyISOLatin1Lowered(alias, alias, strlen(alias));
	copyISOLatin1Lowered(font_name, lexToken, strlen(lexToken));
	return status;
      }
    }
  }
  fclose(file);
  return FileClosed;
}

#define FontAliasEntry	8

static int
OpenAndVerifyFont (
    char	       *name,
    int			namelen,
    FontDirectoryPtr	dir)
{
  char		lowerName[MAXFONTNAMELEN];
  char		*p;
  FontNameRec		tmpName;
  FontEntryPtr	entry;
  FontScalableRec	vals;
  FontBitmapEntryPtr	bitmap;
  FontBCEntryPtr	bc;
  int			ret = 0;
  Bool		isxlfd;
  Bool		scaleAlias;
    
  if (namelen >= MAXFONTNAMELEN)
    return EAllocError;
  copyISOLatin1Lowered (lowerName, name, namelen);
  lowerName[namelen] = '\0';
  tmpName.name = lowerName;
  tmpName.length = namelen;
  tmpName.ndashes = FontFileCountDashes (lowerName, namelen);
  /* Match XLFD patterns */
  if (tmpName.ndashes == 14 &&
      FontParseXLFDName (lowerName, &vals, FONT_XLFD_REPLACE_ZERO))
    {
	isxlfd = TRUE;
	tmpName.length = strlen (lowerName);
	entry = FontFileFindNameInDir (&dir->scalable, &tmpName);
	if (entry) {
	    return Success;
	}
    }
  else
    {
      isxlfd = FALSE;
    }
  /* Match non XLFD pattern */
  if (entry = FontFileFindNameInDir (&dir->nonScalable, &tmpName))
    {
	switch (entry->type) {
	case FONT_ENTRY_BITMAP:
	  bitmap = &entry->u.bitmap;
	  ret = Success;
	  break;
	case FONT_ENTRY_ALIAS:
	  if (entry->u.alias.resolved) {
	      strlcpy(name, entry->u.alias.resolved, MAXFONTNAMELEN);
	      ret = FontAliasEntry; 
	  } else {
	      ret = EBadFontName;
	  }
	  break;
	case FONT_ENTRY_BC:
	  bc = &entry->u.bc;
	  entry = bc->entry;
	  break;
	default:
	  ret = EBadFontName;
	}
      }
  else
    {
	scaleAlias = FALSE;
	if (isxlfd)
	  {
	    FontParseXLFDName(lowerName, &vals, FONT_XLFD_REPLACE_ZERO);
	    tmpName.length = strlen (lowerName);
	    scaleAlias = TRUE;
	  }
	else
	  {
	    p = lowerName + tmpName.length;
	    while (p > lowerName && isdigit(p[-1]))
	      p--;
	    if (*p)
	      {
		vals.point = atoi(p) * 10;
		if (p[-1] == '-')
		  p--;
		if (p > lowerName)
		  {
		    *p = '\0';
		    vals.pixel = 0;
		    vals.x = 0;
		    vals.y = 0;
		    vals.width = 0;
		    tmpName.length = p - lowerName;
		    scaleAlias = TRUE;
		  }
	      }
	  }
	if (scaleAlias &&
	    (entry = FontFileFindNameInDir (&dir->nonScalable, &tmpName)) &&
	    entry->type == FONT_ENTRY_ALIAS)
	  {
	    if (entry->u.alias.resolved) {
		strlcpy(name, entry->u.alias.resolved, MAXFONTNAMELEN);
		return FontAliasEntry;
	    } else {
		return EBadFontName;
	    }

	  }
	else
	  {
	    ret = EBadFontName;
	  }
      }
  return ret;
}

#define TempFileSuffix "_TMPFILE"

static void
ProcessAliasFile(
    FontDirectoryPtr dir,
    const char *aliasfilename)
{
  char	alias[MAXFONTNAMELEN];
  char	font_name[MAXFONTNAMELEN];
  char	save_font_name[MAXFONTNAMELEN];
  char aliasfile[MAXFONTNAMELEN];
  char tmpfile[MAXFONTNAMELEN];
  char outfile[MAXFONTNAMELEN];

  FILE *file, *newfile;
  int ret;
  struct stat	statb;
  int	retvalue;
  int containsSpace = 0;

  strlcpy(aliasfile, dir->directory, sizeof(aliasfile));
  strlcat(aliasfile, aliasfilename, sizeof(aliasfile));
  file = fopen(aliasfile, "r");
  if (!file)
      return; /* fail silently -- if no alias file, we're done */
  else 
    if (fstat (fileno(file), &statb) == -1)
      return;
  
  strlcpy(tmpfile, aliasfile, sizeof(tmpfile));
  strlcat(tmpfile, TempFileSuffix, sizeof(tmpfile));
  newfile = fopen(tmpfile, "w");

  if (!newfile) {
      ErrorF("Can't create new alias file %s\n", tmpfile);
      return;
  }

  while ((ret = ReadAliases(file, alias, font_name)) != FileClosed) {
    strlcpy(save_font_name, font_name, sizeof(save_font_name));
    while ((retvalue = OpenAndVerifyFont(font_name,strlen(font_name), dir)) 
				== FontAliasEntry) {
	continue;
    }
    if (strcmp(alias,save_font_name) == 0) { 
      /* 4258475: don't add if the names are the same */
#ifdef DEBUG
	fprintf(stderr,"%s\t%s aliased to itself!\n", alias, save_font_name);
#endif
    } else if (retvalue == Success) {
      /* add this alias to list of known aliases */
      if (strchr(alias, ' '))
	  containsSpace = 1;

      if (!FontFileAddFontAlias (dir, alias, save_font_name))
#ifdef DEBUG
	  fprintf(stderr, "installalias: unable to add alias to list\n");
#else 
	; /* do nothing -- fail silently */
#endif /* DEBUG */
      if (containsSpace) {
	  containsSpace = 0;
	  fprintf(newfile, "\"%s\"\t\"%s\"\n",alias, save_font_name);
      } else {
	  fprintf(newfile, "%s\t\"%s\"\n",alias, save_font_name);
      }
    }
#ifdef DEBUG
    else
      fprintf(stderr,"%s\t%s not found\n", alias, save_font_name);
#endif /* DEBUG */
  } 
  fclose(newfile);
  fclose(file);
  strlcpy(outfile, dir->directory, sizeof(outfile));
  strlcat(outfile, "fonts.alias", sizeof(outfile));
  ret = rename(tmpfile, outfile);
  if (ret < 0) {
      ErrorF("Unable to rename %s to %s.\n", tmpfile, outfile);
  }
  return;
}

int
GetDefaultPointSize (void)
{
    return 120;
}

/* ARGSUSED */
FontResolutionPtr GetClientResolutions (int *num)
{
    return 0;
}

/* ARGSUSED */
int RegisterFPEFunctions ( NameCheckFunc name_func, 
				  InitFpeFunc init_func, 
				  FreeFpeFunc free_func, 
				  ResetFpeFunc reset_func, 
				  OpenFontFunc open_func, 
				  CloseFontFunc close_func, 
				  ListFontsFunc list_func, 
				  StartLfwiFunc start_lfwi_func, 
				  NextLfwiFunc next_lfwi_func, 
				  WakeupFpeFunc wakeup_func, 
				  ClientDiedFunc client_died, 
				  LoadGlyphsFunc load_glyphs, 
				  StartLaFunc start_list_alias_func, 
				  NextLaFunc next_list_alias_func, 
				  SetPathFunc set_path_func )
{
    return 0;
}

void
InitFontFileFunctions(void)
{
    FontFileRegisterFpeFunctions();
    PseudoFontFileRegisterFpeFunctions();
    return;
}

int
main(int argc, char **argv)
{

    FontDirectoryPtr dir;
    const char *aliasFileName = "fonts.alias";
    char *defaultDirectoryList[] = { ".", NULL };
    char **directoryList = defaultDirectoryList;
    int directoryCount = 1;
    int i = 0, ret;

    programName = argv[0];
    
    InitFontFileFunctions();

    if (argc > 1) {
	aliasFileName = argv[1];
    }

    if (argc > 2) {
	directoryCount = argc;
	directoryList = argv;
	i = 2;
    }
    
    for (/* i initialized above */ ; i < directoryCount; i++) {
	ret = ProcessFontsDirectory(directoryList[i], &dir);
	if (ret == Success) {
	    ProcessAliasFile(dir, aliasFileName);
	} else {
	    char curdir[PATH_MAX];
	    const char *directory = directoryList[i];
	    if (strcmp(directory, ".") == 0) {
		getcwd(curdir, sizeof(curdir));
		directory = curdir;
	    }
	    ErrorF("failed to process fonts.dir file in %s\n", directory);
	    exit (1);
	}
    }  
    exit (0);
}
