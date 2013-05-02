/****************************************************************************
Component: Extensions for Qt
Author: Philipp Horwath; SCR, Imaging Architecture
Date: May, 2007
Description: Class for dynamicly loading and unloading from librarys
Copyright (C) Siemens AG 2007 All Rights Reserved
****************************************************************************/

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