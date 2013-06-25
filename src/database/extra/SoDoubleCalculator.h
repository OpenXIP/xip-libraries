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
//  -*- C++ -*-

/*
 * Copyright (C) 1990,91,92   Silicon Graphics, Inc.
 *
 _______________________________________________________________________
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 |
 |   $Revision: 1.1.1.1 $
 |
 |   Description:
 |	This file contains the declaration of the DoubleCalculator engine
 |
 |   Classes:
 |	SoDoubleCalculator
 |
 |   Author(s)		: Ronen Barzel
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_DOUBLE_CALCULATOR_
#define  _SO_DOUBLE_CALCULATOR_

#include <Inventor/system/SbSystem.h>
#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoMFString.h>
#include <Inventor/fields/SoMFVec3f.h>
#include <xip/inventor/extra/SoMFDouble.h>

class SoCalcParser;

// C-api: public=a,b,c,d,e,f,g,h,A,B,C,D,E,F,G,H,expression
// C-api: public=oa,ob,oc,od,oA,oB,oC,oD
// C-api: prefix=SoCalc
class XIPIVEXTRA_API SoDoubleCalculator : public SoEngine {

    SO_ENGINE_HEADER(SoDoubleCalculator);
    
  public:

    // Inputs
    SoMFDouble	a,b,c,d,e,f,g,h;
    SoMFVec3f	  A,B,C,D,E,F,G,H;
    SoMFString	expression;
    
    // Outputs
    SoEngineOutput oa,ob,oc,od;	// (SoMFDouble)
    SoEngineOutput oA,oB,oC,oD;	// (SoMFVec3f)
    
    // Constructor
    SoDoubleCalculator();

  SoINTERNAL public:

    static void initClass();

  protected:
    virtual void	inputChanged(SoField *whichInput);

  private:
    // Destructor
    ~SoDoubleCalculator();

    // Evaluation method
    virtual void evaluate();

    SoCalcParser *parser;
    SbBool       reparse;

    // working storage for the evaluation
    double	va, vb, vc, vd, ve, vf, vg, vh, ova, ovb, ovc, ovd;
    double	ta, tb, tc, td, te, tf, tg, th;
    SbVec3f	vA, vB, vC, vD, vE, vF, vG, vH, ovA, ovB, ovC, ovD;
    SbVec3f	tA, tB, tC, tD, tE, tF, tG, tH;
    static double *lookupDouble(void *, const char *);
    static SbVec3f *lookupVec3f(void *, const char *);
};

#endif  // _SO_DOUBLE_CALCULATOR_
