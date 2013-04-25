#ifndef SOXIPPLUGINLOADER_H
#define SOXIPPLUGINLOADER_H

#include <xip/inventor/core/xipivcore.h>
#include <Inventor/SbString.h>

class XipPluginBase;
class xipPluginList;

class XIPIVCORE_API SoXipPluginLoader
{
public:
    static void initClass();

	static XipPluginBase *ref(const SbString plugin);
	static XipPluginBase *ref(const XipPluginBase *plugin);
	static void unref(XipPluginBase *plugin);

protected:
	SoXipPluginLoader();
	virtual ~SoXipPluginLoader();

	static SoXipPluginLoader *mPluginLoader;
	xipPluginList *mPluginList;
};


#endif // SOXIPPLUGINLOADER_H

