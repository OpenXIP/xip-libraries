/*
 * Copyright (C) 2003,04   MeVis gGmbH
 *
 _______________________________________________________________________
 ______________________  M E V I S   G G M B H  ________________________
 |
 |   $Revision$
 |
 |   Description:
 |	This include file contains typedef's for standard integer types.
 |
 |   Author(s)		: Felix Ritter
 |
 ______________________  M E V I S   G G M B H  ________________________
 _______________________________________________________________________
 */

#ifndef _INT_TYPES_
#define _INT_TYPES_

#ifdef WIN32

typedef signed int int32_t;
typedef unsigned int uint32_t;

typedef signed short int int16_t;
typedef unsigned short int uint16_t;

typedef signed char int8_t;
typedef unsigned char uint8_t;

#endif

#endif  // _INT_TYPES_
