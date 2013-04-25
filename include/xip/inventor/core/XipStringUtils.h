#ifndef XIPSTRINGUTILS_H
#define XIPSTRINGUTILS_H

#include <xip/inventor/core/xipivcore.h>
#include <Inventor/SbString.h>

/*! \fn XipStrExpandEnv
 * \brief Expands environment variables (e.g. "$(XIP)") in a string
 */
XIPIVCORE_API SbString XipStrExpandEnv(const char *strIn);

#endif // XIPSTRINGUTILS_H