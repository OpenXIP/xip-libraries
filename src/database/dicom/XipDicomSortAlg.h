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
#ifndef XIPDICOMSORTALG_H
#define XIPDICOMSORTALG_H


class XipDicomSortImage;


// key that distinguishes groups of images
class XipDicomSortAlg  
{
public:
	XipDicomSortAlg(const XipDicomSortImage *image);
	virtual ~XipDicomSortAlg();

	bool operator < (const XipDicomSortAlg& v) const;
	bool operator > (const XipDicomSortAlg& v) const;
	bool operator == (const XipDicomSortAlg& v) const;
	bool operator != (const XipDicomSortAlg& v) const;
	void operator = (const XipDicomSortAlg& v);

protected:
	const XipDicomSortImage *mImage;
};

#endif // XIPDICOMSORTALG_H
