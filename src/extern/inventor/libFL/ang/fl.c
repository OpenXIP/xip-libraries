/*
 * Copyright (c) 2000 Silicon Graphics, Inc.  All Rights Reserved.
 * 
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 * 
 * This program is distributed in the hope that it would be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * 
 * Further, this software is distributed without any warranty that it is
 * free of the rightful claim of any third person regarding infringement
 * or the like.  Any license provided herein, whether implied or
 * otherwise, applies only to this software file.  Patent licenses, if
 * any, provided herein do not apply to combinations of this program with
 * other software, or any other product whatsoever.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write the Free Software Foundation, Inc., 59
 * Temple Place - Suite 330, Boston MA 02111-1307, USA.
 * 
 * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,
 * Mountain View, CA  94043, or:
 * 
 * http://www.sgi.com 
 * 
 * For further information regarding this notice, see: 
 * 
 * http://oss.sgi.com/projects/GenInfo/NoticeExplan/
 */

#include <stdio.h>
#include <stdlib.h>
#ifdef WIN32
# include <windows.h>
# include <shlobj.h>
# include <io.h>
# ifndef R_OK
#  define R_OK 4
# endif
#else
# include <unistd.h>
#endif /* WIN32 */

#if defined(__APPLE__)
# include <ApplicationServices/ApplicationServices.h>
# include <CFString.h>
#endif /* __APPLE__ */

#include <string.h>
#include "fl.h"

/* Implementation headers go here */
#include "flfreetype.h"

#define INIT(impl, ret)							\
  if (! impl->init && ! _flInitialize(impl))				\
    return ret

#define CHECK(fs, impl, func, ret)					\
  INIT(impl, ret);							\
  if (! fs || ! impl->func)						\
    return ret

/* Data type */
typedef struct FLfontImpl {
  const char *		   name;		/* vendor name */
  const char *		   version;		/* version string */

  FLInitializeFunc *	   initialize;		/* initialize handler */
  FLShutdownFunc *	   shutdown;		/* shutdown handler */
  FLCreateFontFunc *	   createFont;		/* font creation handler */
  FLDestroyFontFunc *	   destroyFont;		/* font destruction handler */
  FLGetBitmapFunc *	   getBitmap;		/* get bitmap handler */
  FLGetScalableBitmapFunc *getScalableBitmap;	/* get scalable bitmap handler */
  FLGetOutlineFunc *	   getOutline;		/* get outline handler */
  FLUniGetBitmapFunc *	   getUniBitmap;	/* get Unicode bitmap handler */
  FLUniGetOutlineFunc *	   getUniOutline;	/* get Unicode outline handler */

  GLboolean		   init;		/* initialized flag */
  GLboolean		   available;		/* availability flag */
} FLfontImpl;

/* Font implementation table */
FLfontImpl freetypeImpl = {
  "FreeType", "2.0.1",
  _flFTInitialize,
  _flFTShutdown,
  _flFTCreateFont,
  _flFTDestroyFont,
  _flFTGetBitmap,
  _flFTGetScalableBitmap,
  _flFTGetOutline,
  _flFTUniGetBitmap,
  _flFTUniGetOutline,
  FALSE, TRUE
};

static FLfontImpl *fontImplTable[] = {
  &freetypeImpl,
  NULL
};

#if defined(WIN32)
static char *fontPath = NULL;
/*
 * Most Inventor font names don't exist in 
 * windows, so we'll default to a common
 * windows font.
 */
static char fontDefault[MAX_PATH] = {0};
#elif defined(__APPLE__)
/*
 * We use Apple Type Services for Fonts References on Mac OS X instead of hard-coded
 * directories if no explicit font path it set via environment variable.
 */
static char *fontPath = NULL;
#else
static char *fontPath = IVPREFIX "/share/data/fonts";
#endif

int fl_debug = FALSE;


/*
 * Initialize the given font implementation. Returns true if OK, false
 * otherwise.
 */
static GLboolean
_flInitialize(FLfontImpl *impl)
{
  GLboolean ret;
  char *ev;

#ifdef WIN32
  /* obtain Windows font path */
  static CHAR szPath[MAX_PATH] = {0};
  SHGetSpecialFolderPathA(NULL, szPath, CSIDL_FONTS, 0);
  fontPath = szPath;

  /* setup fallback font */
  strcat(strcpy(fontDefault, fontPath), "\\times.ttf");
#endif

  ev = getenv("FL_DEBUG");
  fl_debug = (ev && *ev != '0');

  ev = getenv("FL_FONT_PATH");
  if (ev && *ev) fontPath = ev;

  if (impl->initialize)
    ret = impl->initialize();

  impl->init = TRUE;

  return ret;
}

/*
 * Search for a suitable font implementation. For now, simply returns 
 * FreeType's implementation.
 */
static FLfontImpl *
_flGetFontImpl(void)
{
  return fontImplTable[0];
}

/*
 * Search the given font name in font path, returns an allocated path if
 * found, else returns NULL.
 */
char *
_flSearchFont(const GLubyte *fontName)
{
  char *path = NULL;

  if (fontPath) { /* Try to locate font in given fonts directory */
    int i;
    char buffer[1024];

    const char *fontExt[] = {
      "", ".ttf", ".pfa", ".pfb", ".otf"
    };
    
    for (i = 0; !path && (i < sizeof(fontExt)/sizeof(fontExt[0])); i++) {
      /* In the future, the fontPath could have multiple directroy entries as in "path1:path2:...",
       * For now, only one directory is supported.
       */
      sprintf(buffer, "%s/%s%s", fontPath, fontName, fontExt[i]);
      if (access(buffer, R_OK) == 0) {
        path = strdup(buffer);
      }
    }
  }

#if defined(__APPLE__)

  if (!path) { /* Use Apple Type Services to locate font by postscript name or normal naming scheme */
    CFStringRef name = CFStringCreateWithCString(kCFAllocatorDefault, (const char *)fontName, kCFStringEncodingUTF8);
    /* Try to find font by using its postscript name */
    ATSFontRef font = ATSFontFindFromPostScriptName(name, kATSOptionFlagsDefault);
    if (font == kATSFontRefUnspecified) {
      /* Try to find font by using normal naming scheme */
      font = ATSFontFindFromName(name, kATSOptionFlagsDefault);
      if (font == kATSFontRefUnspecified) {
        /* Use fallback font */
        font = ATSFontFindFromPostScriptName(CFSTR("Helvetica"), kATSOptionFlagsDefault); //Times-Roman
      }
    }
    CFRelease(name);
    
//#if defined( MAC_OS_X_VERSION_10_5 )
    if (font != kATSFontRefUnspecified) {
      //OLD DEPRECATED CODE
      //FSSpec spec;
      //if (ATSFontGetFileSpecification(font, &spec) == noErr) {
        //FSRef fsRef;
        //if (FSpMakeFSRef(&spec, &fsRef) == noErr) {
      FSRef fsRef;
      if (ATSFontGetFileReference(font, &fsRef) == noErr) {
          // Obtain posix path from file system reference
          UInt8 buffer[1024];
          if (FSRefMakePath(&fsRef, buffer, sizeof(buffer)) == noErr) {
            path = strdup((const char *)buffer);
          }
        //}
      }
    }
//#endif //defined( MAC_OS_X_VERSION_10_5 )
  }

#elif defined(WIN32)

  /*
   * If the font wasn't found, we'll try the default
   * font instead of giving up.
   */
  if (!path && access(fontDefault, R_OK) == 0) {
    path = strdup(fontDefault);
  }

#endif  // WIN32

  TRACE(("_flSearchFont: path=[%s]\n", path));

  return path;
}

/*
 * Shut everything down.
 */
void
_flShutdown(void)
{
  FLfontImpl **impl;

  for (impl = fontImplTable; *impl; impl++)
    if ((*impl)->shutdown)
      (*impl)->shutdown();
}

FLfontStruct *
_flCreateFont(const GLubyte *fontName,
	      GLfloat	     mat[2][2],
	      GLint	     charNameCount,
	      GLubyte **     charNameVector)
{
  FLfontImpl *impl = fontImplTable[0];
  FLfontStruct *fs;

  INIT(impl, NULL);
  
  fs = impl->createFont(fontName, mat, charNameCount, charNameVector);
  if (! fs)
    return NULL;

  /* Initialize font structure */
  fs->direction		= FL_FONT_LEFTTORIGHT; /* hint about direction the font is painted */
  fs->min_char_or_byte2 = 32;	/* first character */
  fs->max_char_or_byte2 = 127;	/* last character */
  fs->min_byte1		= 0;	/* first row that exists */
  fs->max_byte1		= 0;	/* last row that exists */
  fs->all_chars_exist	= FALSE;/* flag if all characters have non-zero size */
  fs->default_char	= 32;	/* char to print for undefined character */
  fs->n_properties	= 0;	/* how many properties there are */
  fs->properties	= NULL;	/* pointer to array of additional properties */
#if 0
  fs->min_bounds;		/* minimum bounds over all existing char */
  fs->max_bounds;		/* maximum bounds over all existing char */
#endif
  fs->per_char		= NULL;	/* first_char to last_char information */
  fs->ascent		= 8;	/* log. extent above baseline for spacing */
  fs->descent		= 4;	/* log. descent below baseline for spacing */

  return fs;
}

void
_flDestroyFont(FLfontStruct *fs)
{
  FLfontImpl *impl = _flGetFontImpl();

  CHECK(fs, impl, destroyFont, /* nothing to return */);

  impl->destroyFont(fs);
}

FLbitmap *
_flGetBitmap(FLfontStruct *fs, GLuint c)
{
  FLfontImpl *impl = _flGetFontImpl();

  CHECK(fs, impl, getBitmap, NULL);

  return impl->getBitmap(fs, c);
}

FLscalableBitmap *
_flGetScalableBitmap(FLfontStruct *fs, GLuint c)
{
  FLfontImpl *impl = _flGetFontImpl();

  CHECK(fs, impl, getScalableBitmap, NULL);

  return impl->getScalableBitmap(fs, c);
}

FLoutline *
_flGetOutline(FLfontStruct *fs, GLuint c)
{
  FLfontImpl *impl = _flGetFontImpl();

  CHECK(fs, impl, getOutline, NULL);

  return impl->getOutline(fs, c);
}

FLbitmap *
_flUniGetBitmap(FLfontStruct **fsList, GLubyte *UCS2)
{
  FLfontImpl *impl = _flGetFontImpl();

  CHECK(fsList, impl, getUniBitmap, NULL);

  return impl->getUniBitmap(fsList, UCS2);
}

FLoutline *
_flUniGetOutline(FLfontStruct **fsList, GLubyte *UCS2)
{
  FLfontImpl *impl = _flGetFontImpl();

  CHECK(fsList, impl, getUniOutline, NULL);

  return impl->getUniOutline(fsList, UCS2);
}

