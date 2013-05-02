#ifndef __flendian_h_
#define __flendian_h_

#if defined (__GLIBC__)
# include <endian.h>
# if (__BYTE_ORDER == __LITTLE_ENDIAN)
#  define FL_LITTLE_ENDIAN
# elif (__BYTE_ORDER == __BIG_ENDIAN)
#  define FL_BIG_ENDIAN
# else
#  error Unknown machine endianness detected. The file flendian.h needs to be set up for your CPU type.
# endif
# define FL_BYTE_ORDER __BYTE_ORDER
#elif defined(__sparc) || defined(__sparc__) \
   || defined(_POWER) || defined(__powerpc__) \
   || defined(__ppc__) || defined(__hppa) \
   || defined(_MIPSEB) || defined(_POWER) \
   || defined(__s390__)
# define FL_BIG_ENDIAN
#elif defined(__i386__) || defined(__alpha__) \
   || defined(__ia64) || defined(__ia64__) \
   || defined(_M_IX86) || defined(_M_IA64) \
   || defined(_M_ALPHA) || defined(_WIN64) \
   || defined(_I386__ENDIAN_H_) || defined(__x86_64)
# define FL_LITTLE_ENDIAN
#else
# error The file flendian.h needs to be set up for your CPU type.
#endif

#endif  /* __flendian_h_ */
