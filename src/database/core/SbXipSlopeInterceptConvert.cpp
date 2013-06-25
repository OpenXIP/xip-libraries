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

#include <xip/inventor/core/SbXipSlopeInterceptConvert.h>

SbXipSlopeInterceptConvert::SbXipSlopeInterceptConvert()
: mSlope(1.0f),
  mIntercept(0.0f)
{
}
SbXipSlopeInterceptConvert::~SbXipSlopeInterceptConvert()
{
}


SbXipValueConvertBase* 
SbXipSlopeInterceptConvert::clone() const
{
    SbXipSlopeInterceptConvert* newObj = new SbXipSlopeInterceptConvert;
    if (newObj)
    {
        newObj->set(mSlope, mIntercept);        
    }

    return newObj;
}

void
SbXipSlopeInterceptConvert::set(float slope, float intercept)
{
    mSlope = slope;
    mIntercept = intercept;
}

float 
SbXipSlopeInterceptConvert::getSlope() const
{
    return mSlope;
}

float 
SbXipSlopeInterceptConvert::getIntercept() const
{
    return mIntercept;
}

float 
SbXipSlopeInterceptConvert::getConvertedValue(float val_in) const
{
	return (val_in*mSlope + mIntercept);
}

float 
SbXipSlopeInterceptConvert::getConvertedScale(float scale_in) const
{
	return (scale_in*mSlope);

}
