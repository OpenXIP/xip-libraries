/*
Copyright (c) 2011, Siemens Corporate Research a Division of Siemens Corporation 
All rights reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/
#ifndef XIPINVENTORUTILS_H
#define XIPINVENTORUTILS_H

#include <xip/inventor/core/xipivcore.h>
#include <Inventor/SoType.h>
#include <Inventor/SbString.h>

#define XIP_DOACTION_HEADER()												\
	protected:																\
	virtual void doAction(SoAction * action);								\
	virtual void GLRender(SoGLRenderAction * action) { doAction(action); }	\
	virtual void callback(SoCallbackAction * action) { doAction(action); }	\
	virtual void pick(SoPickAction * action) { doAction(action); }			\
	virtual void getBoundingBox(SoGetBoundingBoxAction * action) { doAction(action); }


/*! \class XipWStringConv
 * \brief Utility class to convert string into unicode string
 */
class XIPIVCORE_API XipWStringConv
{
public:
	XipWStringConv(const char *str);
	XipWStringConv();
	virtual ~XipWStringConv();
	const wchar_t *getString() const;

protected:
	wchar_t *mStr;
};

/*! \class XipStringConv
 * \brief Utility class to convert string into unicode string
 */
class XIPIVCORE_API XipStringConv
{
public:
	XipStringConv(const wchar_t *str);
	XipStringConv();
	virtual ~XipStringConv();
	const char *getString() const;

protected:
	char *mStr;
};


class XipException;

/*! \fn XipPostException
 * \brief Utility function to convert XipException to Inventor error postings
 */
XIPIVCORE_API void XipPostException(XipException& e);


#endif // XIPINVENTORUTILS_H
