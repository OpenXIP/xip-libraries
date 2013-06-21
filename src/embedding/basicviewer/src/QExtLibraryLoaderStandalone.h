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
#ifndef QExtLibraryLoaderStandalone_H
#define QExtLibraryLoaderStandalone_H

#include <QtCore/QMap>
class QLibrary;
class QString;
class QStringList;

//! does the work with loading the libraries and saves errors if some occurs
/*! 
  The idea behind this class is that everything is static. There only one class or modul that can load or unload libraries. If in the Qt System one QLibrary
  loads a e.g. .dll only this QLibrary can unload it.

  @author Philipp Horwath
  @date July 2007
  @todo remove the Q from the name
*/

class QExtLibraryLoaderStandalone
{
  
public:
	//! QLibrary pointers have to be saved
	static QLibrary* getQLibrary(const QString &file);

	//! load a library
	static bool loadDLL(const QString &file);
	//! unload a library
	static bool unloadDLL(const QString &file);
	//! check if library is loaded
	static bool isLoaded(const QString &file);
	//! check if libary exists physical on the drive
	static bool exists(const QString &file);
	//! saves the error messag to a library
	static bool setErrorMessage(const QString &file, const QString &message);
	//! returns the error message to a library
  /*! @return the error String that occures */
	static QString getErrorMessage(const QString &file);

private:
  //! Map which keeps Filename to QLibrary
	typedef QMap<QString, QLibrary*> QLibraryMap;
  //! Map which keeps Filename to error message
	typedef QMap<QString, QString> QErrorMap;
  //! Map of Librarys
	static QLibraryMap mLibraryMap;
  //! Map of Error Messages
	static QErrorMap mErrorMap;
};
#endif
