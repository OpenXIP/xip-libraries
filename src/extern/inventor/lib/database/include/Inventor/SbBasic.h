/*
 *
 *  Copyright (C) 2000 Silicon Graphics, Inc.  All Rights Reserved. 
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  Further, this software is distributed without any warranty that it is
 *  free of the rightful claim of any third person regarding infringement
 *  or the like.  Any license provided herein, whether implied or
 *  otherwise, applies only to this software file.  Patent licenses, if
 *  any, provided herein do not apply to combinations of this program with
 *  other software, or any other product whatsoever.
 * 
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *  Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,
 *  Mountain View, CA  94043, or:
 * 
 *  http://www.sgi.com 
 * 
 *  For further information regarding this notice, see: 
 * 
 *  http://oss.sgi.com/projects/GenInfo/NoticeExplan/
 *
 */

//  -*- C++ -*-

/*
 * Copyright (C) 1990,91   Silicon Graphics, Inc.
 *
 _______________________________________________________________________
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 |
 |   $Revision: 1.2 $
 |
 |   Description:
 |	This file contains basic SB library definitions.
 |
 |   Author(s)		: Paul S. Strauss, Nick Thompson
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SB_BASIC_
#define  _SB_BASIC_

#include <Inventor/system/SbSystem.h>
//
// These symbols can be used to determine what version of Inventor
// your application is compiling against.  These symbols were first
// added with Inventor 2.1 (SO_VERSION==2, SO_VERSION_REVISION==1);
// they were undefined in previous revisions of Inventor.
//
#define SO_VERSION 		2
#define SO_VERSION_REVISION	4
#define SO_VERSION_PATCHLEVEL	0
#define SGI_VERSION		20400

#include <inttypes.h>
#include <sys/types.h>
// C-api: end
#ifdef __sgi
#include <libc.h>
#include <sgidefs.h>
#endif /* __sgi */
// C-api: begin
#include <stdio.h>

#ifndef FALSE
#   define FALSE	0
#   define TRUE		1
#endif

typedef int	SbBool;

/////////////////////////////////////////////////////////////////////////////
//
// These symbols are used in Inventor header files to distinguish
// between varying levels of use of classes and members.
//
// Types of classes are:
//
//	"class" means a public class intended for use by all users.
//	"SoEXTENDER class" indicates a class that is used only by
//		people extending the set of Inventor classes.
//	"SoINTERNAL class" means that the class is used only by
//		Inventor developers at Silicon Graphics.
//
// Types of member variables and methods are:
//
//	"public:" members are used by everybody.
//	"SoEXTENDER public:" members are used when extending Inventor.
//	"SoINTERNAL public:" members are for SGI Inventor developers only.
//
//	"protected:" members are for people extending Inventor
//		classes. (The "SoEXTENDER" is implied.)
//	"SoINTERNAL protected:" members are for SGI use only.
//
//	"private:" members are private, dammit.
//
/////////////////////////////////////////////////////////////////////////////

#define SoEXTENDER
#define SoINTERNAL

#ifdef WIN32
#define M_E		2.7182818284590452354
#define M_LOG2E		1.4426950408889634074
#define M_LOG10E	0.43429448190325182765
#define M_LN2		0.69314718055994530942
#define M_LN10		2.30258509299404568402
#define M_PI		3.14159265358979323846
#define M_PI_2		1.57079632679489661923
#define M_PI_4		0.78539816339744830962
#define M_1_PI		0.31830988618379067154
#define M_2_PI		0.63661977236758134308
#define M_2_SQRTPI	1.12837916709551257390
#define M_SQRT2		1.41421356237309504880
#define M_SQRT1_2	0.70710678118654752440
#define MAXFLOAT	((float)3.40282346638528860e+38)
#endif

/////////////////////////////////////////////////////////////////////////////
//
// Map the single-precision math functions to the regular ones on
// machines that don't support them.
//
/////////////////////////////////////////////////////////////////////////////

#ifdef _DOUBLE_MATH_ONLY

#define acosf acos
#define asinf asin
#define atanf atan
#define atan2f atan2
#define cosf cos
#define sinf sin
#define tanf tan
#define powf pow
#define sqrtf sqrt

#endif /* _DOUBLE_MATH_ONLY */

#endif /* _SB_BASIC_ */
