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
#ifndef SOXIPDATAIMAGE_H
#define SOXIPDATAIMAGE_H

#include <xip/inventor/core/SoXipData.h>
#include <xip/inventor/core/SoXipSubData.h>
#include <xip/inventor/core/xipivcore.h>

class SbXipImage;


class XIPIVCORE_API SoXipDataImage : public SoXipData
{
	XIP_DATA_HEADER(SoXipDataImage);

public:
	SoXipDataImage();
	static void initClass();

	virtual SbXipImage *get() const;
	virtual void set(SbXipImage *image);

protected:
	virtual ~SoXipDataImage();

	SbXipImage *mImage;
};


#endif // SOXIPDATAIMAGE_H
