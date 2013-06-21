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
*/#ifndef SBXIPSLOPEINTERCEPTCONVERT_H
#define SBXIPSLOPEINTERCEPTCONVERT_H

#include <xip/inventor/core/xipivcore.h>
#include <xip/inventor/core/SbXipValueConvertBase.h>

/*! \class SbXipSlopeInterceptConvert 
 *  \brief A slope and intercept value converter class.
 *
 *  This class converts input intensity value or scale
 *  to output values based on the set slope and intercepts
 */
class XIPIVCORE_API SbXipSlopeInterceptConvert : public SbXipValueConvertBase
{
public:
	/// Constructor
    SbXipSlopeInterceptConvert();
    virtual ~SbXipSlopeInterceptConvert();

    SbXipValueConvertBase* clone() const;

    void set(float slope, float intercept);
    float getSlope() const;
    float getIntercept() const;

	float getConvertedValue(float val_in) const;
	float getConvertedScale(float scale_in) const;

protected:

    float mSlope;
    float mIntercept;
};


#endif // SBXIPSLOPEINTERCEPTCONVERTER_H
