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
*/#ifndef SOXIPPLUGINLOADER_H
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

