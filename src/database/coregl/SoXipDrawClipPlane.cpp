/*
 *  COPYRIGHT NOTICE.  Copyright (C) 2005 Siemens Corporate Research, 
 *  Inc. ("caBIG(tm) Participant"). eXtensible Imaging Platform (XIP)
 *  was created with NCI funding and is part of the caBIG(tm) 
 *  initiative. The software subject to this notice and license 
 *  includes both human readable source code form and machine 
 *  readable, binary, object code form (the "caBIG(tm) Software").
 *  
 *  This caBIG(tm) Software License (the "License") is between 
 *  caBIG(tm) Participant and You.  "You (or "Your") shall mean a 
 *  person or an entity, and all other entities that control, are 
 *  controlled by, or are under common control with the entity.  
 *  "Control" for purposes of this definition means (i) the direct or 
 *  indirect power to cause the direction or management of such 
 *  entity, whether by contract or otherwise, or (ii) ownership of 
 *  fifty percent (50%) or more of the outstanding shares, or (iii) 
 *  beneficial ownership of such entity.
 *  
 *  LICENSE.  Provided that You agree to the conditions described 
 *  below, caBIG(tm) Participant grants You a non-exclusive, 
 *  worldwide, perpetual, fully-paid-up, no-charge, irrevocable, 
 *  transferable and royalty-free right and license in its rights in 
 *  the caBIG(tm) Software, including any copyright or patent rights 
 *  therein that may be infringed by the making, using, selling, 
 *  offering for sale, or importing of caBIG(tm) Software, to (i) 
 *  use, install, access, operate, execute, reproduce, copy, modify, 
 *  translate, market, publicly display, publicly perform, and 
 *  prepare derivative works of the caBIG(tm) Software; (ii) make, 
 *  have made, use, practice, sell, and offer for sale, and/or 
 *  otherwise dispose of caBIG(tm) Software (or portions thereof); 
 *  (iii) distribute and have distributed to and by third parties the 
 *  caBIG(tm) Software and any modifications and derivative works 
 *  thereof; and (iv) sublicense the foregoing rights set out in (i), 
 *  (ii) and (iii) to third parties, including the right to license 
 *  such rights to further third parties.  For sake of clarity, and 
 *  not by way of limitation, caBIG(tm) Participant shall have no 
 *  right of accounting or right of payment from You or Your 
 *  sublicensees for the rights granted under this License.  This 
 *  License is granted at no charge to You.  Your downloading, 
 *  copying, modifying, displaying, distributing or use of caBIG(tm) 
 *  Software constitutes acceptance of all of the terms and 
 *  conditions of this Agreement.  If you do not agree to such terms 
 *  and conditions, you have no right to download, copy, modify, 
 *  display, distribute or use the caBIG(tm) Software.
 *  
 *  1.	Your redistributions of the source code for the caBIG(tm) 
 *      Software must retain the above copyright notice, this list 
 *      of conditions and the disclaimer and limitation of 
 *      liability of Article 6 below.  Your redistributions in 
 *      object code form must reproduce the above copyright notice, 
 *      this list of conditions and the disclaimer of Article 6 in 
 *      the documentation and/or other materials provided with the 
 *      distribution, if any.
 *  2.	Your end-user documentation included with the 
 *      redistribution, if any, must include the following 
 *      acknowledgment: "This product includes software developed 
 *      by Siemens Corporate Research Inc."  If You do not include 
 *      such end-user documentation, You shall include this 
 *      acknowledgment in the caBIG(tm) Software itself, wherever 
 *      such third-party acknowledgments normally appear.
 *  3.	You may not use the names "Siemens Corporate Research, 
 *      Inc.", "The National Cancer Institute", "NCI", "Cancer 
 *      Bioinformatics Grid" or "caBIG(tm)" to endorse or promote 
 *      products derived from this caBIG(tm) Software.  This 
 *      License does not authorize You to use any trademarks, 
 *  	service marks, trade names, logos or product names of 
 *      either caBIG(tm) Participant, NCI or caBIG(tm), except as 
 *      required to comply with the terms of this License.
 *  4.	For sake of clarity, and not by way of limitation, You may 
 *      incorporate this caBIG(tm) Software into Your proprietary 
 *      programs and into any third party proprietary programs.  
 *      However, if You incorporate the caBIG(tm) Software into 
 *      third party proprietary programs, You agree that You are 
 *      solely responsible for obtaining any permission from such 
 *      third parties required to incorporate the caBIG(tm) 
 *      Software into such third party proprietary programs and for 
 *      informing Your sublicensees, including without limitation 
 *      Your end-users, of their obligation to secure any required 
 *      permissions from such third parties before incorporating 
 *      the caBIG(tm) Software into such third party proprietary 
 *      software programs.  In the event that You fail to obtain 
 *      such permissions, You agree to indemnify caBIG(tm) 
 *      Participant for any claims against caBIG(tm) Participant by 
 *      such third parties, except to the extent prohibited by law, 
 *      resulting from Your failure to obtain such permissions.
 *  5.	For sake of clarity, and not by way of limitation, You may 
 *      add Your own copyright statement to Your modifications and 
 *      to the derivative works, and You may provide additional or 
 *      different license terms and conditions in Your sublicenses 
 *      of modifications of the caBIG(tm) Software, or any 
 *      derivative works of the caBIG(tm) Software as a whole, 
 *      provided Your use, reproduction, and distribution of the 
 *      Work otherwise complies with the conditions stated in this 
 *      License.
 *  6.	THIS caBIG(tm) SOFTWARE IS PROVIDED "AS IS" AND ANY 
 *      EXPRESSED OR IMPLIED WARRANTIES (INCLUDING, BUT NOT LIMITED 
 *      TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, NON-
 *      INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE) ARE 
 *      DISCLAIMED.  IN NO EVENT SHALL SIEMENS CORPORATE RESEARCH 
 *      INC. OR ITS AFFILIATES BE LIABLE FOR ANY DIRECT, INDIRECT, 
 *      INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
 *      (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE 
 *      GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR 
 *      BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
 *      LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 *      (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT 
 *      OF THE USE OF THIS caBIG(tm) SOFTWARE, EVEN IF ADVISED OF 
 *      THE POSSIBILITY OF SUCH DAMAGE.
 *  
 */


#include "SoXipDrawClipPlane.h"
#include <xip/system/GL/gl.h>


SO_NODE_SOURCE(SoXipDrawClipPlane);

SoXipDrawClipPlane::SoXipDrawClipPlane() {
	SO_NODE_CONSTRUCTOR(SoXipDrawClipPlane);

	SO_NODE_ADD_FIELD(plane, (SbPlane(SbVec3f(0, 0, 1), 0)));
  	SO_NODE_ADD_FIELD(on, (TRUE));
	SO_NODE_ADD_FIELD(boundingBox, (SbMatrix::identity()));
}

void SoXipDrawClipPlane::initClass() {
	SO_NODE_INIT_CLASS(SoXipDrawClipPlane, SoNode, "SoNode");
}

const char SoXipDrawClipPlane::indexList[256][16] = {
 {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
 {  1,  5, 11,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
 {  1,  5,  6, 10,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
 {  2,  6, 11,  8, 10, 11,  6,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
 {  1,  8,  9,  4,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
 {  2,  5,  9,  4, 11,  9,  5,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
 {  2,  6, 10,  5,  4,  8,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
 {  3,  6,  9,  4,  6, 10,  9, 10, 11,  9,  0,  0,  0,  0,  0,  0 },
 {  1,  6,  4,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
 {  2,  5, 11,  8,  6,  4,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
 {  2, 10,  4,  2,  5,  4, 10,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
 {  3,  4, 11,  8,  4,  2, 11,  2, 10, 11,  0,  0,  0,  0,  0,  0 },
 {  2,  8,  2,  6,  9,  2,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
 {  3,  5,  2,  6,  5, 11,  2, 11,  9,  2,  0,  0,  0,  0,  0,  0 },
 {  3,  8, 10,  5,  8,  9, 10,  9,  2, 10,  0,  0,  0,  0,  0,  0 },
 {  2, 10, 11,  2,  2, 11,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
 {  1,  3,  7, 11,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
 {  2,  3,  8,  5,  7,  8,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
 {  2,  5,  6, 10, 11,  3,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
 {  3,  3,  6, 10,  3,  7,  6,  7,  8,  6,  0,  0,  0,  0,  0,  0 },
 {  2, 11,  3,  7,  8,  9,  4,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
 {  3,  9,  3,  7,  9,  4,  3,  4,  5,  3,  0,  0,  0,  0,  0,  0 },
 {  3, 10,  5,  6, 11,  3,  7,  4,  8,  9,  0,  0,  0,  0,  0,  0 },
 {  4,  3,  7,  9, 10,  3,  9, 10,  9,  4, 10,  4,  6,  0,  0,  0 },
 {  2,  6,  4,  2, 11,  3,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
 {  3,  8,  3,  7,  8,  5,  3,  6,  4,  2,  0,  0,  0,  0,  0,  0 },
 {  3, 10,  4,  2, 10,  5,  4, 11,  3,  7,  0,  0,  0,  0,  0,  0 },
 {  4,  4,  2, 10,  4, 10,  7,  4,  7,  8,  7, 10,  3,  0,  0,  0 },
 {  3,  8,  2,  6,  8,  9,  2,  7, 11,  3,  0,  0,  0,  0,  0,  0 },
 {  4,  6,  9,  2,  6,  3,  9,  6,  5,  3,  7,  9,  3,  0,  0,  0 },
 {  4,  3,  7, 11, 10,  5,  9, 10,  9,  2,  9,  5,  8,  0,  0,  0 },
 {  3,  3,  7,  9,  3,  9, 10, 10,  9,  2,  0,  0,  0,  0,  0,  0 },
 {  1, 10,  1,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
 {  2, 10,  1,  3,  5, 11,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
 {  2,  5,  1,  3,  6,  1,  5,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
 {  3, 11,  1,  3, 11,  8,  1,  8,  6,  1,  0,  0,  0,  0,  0,  0 },
 {  2, 10,  1,  3,  4,  8,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
 {  3,  5,  9,  4,  5, 11,  9,  3, 10,  1,  0,  0,  0,  0,  0,  0 },
 {  3,  5,  1,  3,  5,  6,  1,  4,  8,  9,  0,  0,  0,  0,  0,  0 },
 {  4,  4,  6,  1,  4,  1, 11,  4, 11,  9,  3, 11,  1,  0,  0,  0 },
 {  2,  6,  4,  2, 10,  1,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
 {  3,  8,  5, 11,  6,  4,  2,  3, 10,  1,  0,  0,  0,  0,  0,  0 },
 {  3,  1,  4,  2,  1,  3,  4,  3,  5,  4,  0,  0,  0,  0,  0,  0 },
 {  4,  4,  2,  1,  8,  4,  1,  8,  1,  3,  8,  3, 11,  0,  0,  0 },
 {  3,  2,  8,  9,  2,  6,  8, 10,  1,  3,  0,  0,  0,  0,  0,  0 },
 {  4,  3, 10,  1,  5, 11,  6, 11,  2,  6, 11,  9,  2,  0,  0,  0 },
 {  4,  1,  3,  5,  1,  5,  9,  1,  9,  2,  9,  5,  8,  0,  0,  0 },
 {  3,  1,  3, 11,  1, 11,  2,  2, 11,  9,  0,  0,  0,  0,  0,  0 },
 {  2, 10,  7, 11,  1,  7, 10,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
 {  3, 10,  8,  5, 10,  1,  8,  1,  7,  8,  0,  0,  0,  0,  0,  0 },
 {  3,  5,  7, 11,  5,  6,  7,  6,  1,  7,  0,  0,  0,  0,  0,  0 },
 {  2,  6,  1,  8,  8,  1,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
 {  3,  7, 10,  1,  7, 11, 10,  8,  9,  4,  0,  0,  0,  0,  0,  0 },
 {  4, 10,  1,  7, 10,  7,  4, 10,  4,  5,  4,  7,  9,  0,  0,  0 },
 {  4,  4,  8,  9,  5,  6, 11,  6,  7, 11,  6,  1,  7,  0,  0,  0 },
 {  3,  9,  4,  6,  9,  6,  7,  7,  6,  1,  0,  0,  0,  0,  0,  0 },
 {  3, 10,  7, 11, 10,  1,  7,  2,  6,  4,  0,  0,  0,  0,  0,  0 },
 {  4,  2,  6,  4, 10,  1,  5,  1,  8,  5,  1,  7,  8,  0,  0,  0 },
 {  4, 11,  5,  4, 11,  4,  1, 11,  1,  7,  2,  1,  4,  0,  0,  0 },
 {  3,  4,  2,  1,  4,  1,  8,  8,  1,  7,  0,  0,  0,  0,  0,  0 },
 {  4, 10,  1, 11, 11,  1,  7,  2,  6,  8,  2,  8,  9,  0,  0,  0 },
 {  5,  1,  7,  5,  1,  5, 10,  7,  9,  5,  6,  5,  2,  9,  2,  5 },
 {  5,  9,  2,  5,  9,  5,  8,  2,  1,  5, 11,  5,  7,  1,  7,  5 },
 {  2,  9,  2,  1,  7,  9,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
 {  1,  7,  0,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
 {  2,  8,  5, 11,  9,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
 {  2,  5,  6, 10,  9,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
 {  3, 11,  6, 10, 11,  8,  6,  9,  7,  0,  0,  0,  0,  0,  0,  0 },
 {  2,  7,  4,  8,  0,  4,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
 {  3,  7,  5, 11,  7,  0,  5,  0,  4,  5,  0,  0,  0,  0,  0,  0 },
 {  3,  4,  7,  0,  4,  8,  7,  5,  6, 10,  0,  0,  0,  0,  0,  0 },
 {  4,  6,  0,  4,  6, 11,  0,  6, 10, 11, 11,  7,  0,  0,  0,  0 },
 {  2,  2,  6,  4,  0,  9,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
 {  3,  6,  4,  2,  8,  5, 11,  0,  9,  7,  0,  0,  0,  0,  0,  0 },
 {  3,  4, 10,  5,  4,  2, 10,  0,  9,  7,  0,  0,  0,  0,  0,  0 },
 {  4,  0,  9,  7,  4,  2,  8,  2, 11,  8,  2, 10, 11,  0,  0,  0 },
 {  3,  2,  7,  0,  2,  6,  7,  6,  8,  7,  0,  0,  0,  0,  0,  0 },
 {  4,  2,  7,  0,  6,  7,  2,  6, 11,  7,  6,  5, 11,  0,  0,  0 },
 {  4,  5,  8,  7,  5,  7,  2,  5,  2, 10,  0,  2,  7,  0,  0,  0 },
 {  3,  7,  0,  2,  7,  2, 11, 11,  2, 10,  0,  0,  0,  0,  0,  0 },
 {  2,  0, 11,  3,  9, 11,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
 {  3,  8,  0,  9,  8,  5,  0,  5,  3,  0,  0,  0,  0,  0,  0,  0 },
 {  3, 11,  0,  9, 11,  3,  0, 10,  5,  6,  0,  0,  0,  0,  0,  0 },
 {  4, 10,  3,  0, 10,  0,  8, 10,  8,  6,  9,  8,  0,  0,  0,  0 },
 {  3, 11,  4,  8, 11,  3,  4,  3,  0,  4,  0,  0,  0,  0,  0,  0 },
 {  2,  5,  3,  4,  3,  0,  4,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
 {  4,  6, 10,  5,  4,  8,  3,  4,  3,  0,  3,  8, 11,  0,  0,  0 },
 {  3,  6, 10,  3,  6,  3,  4,  4,  3,  0,  0,  0,  0,  0,  0,  0 },
 {  3,  0, 11,  3,  0,  9, 11,  4,  2,  6,  0,  0,  0,  0,  0,  0 },
 {  4,  6,  4,  2,  8,  5,  9,  5,  0,  9,  5,  3,  0,  0,  0,  0 },
 {  4,  3,  9, 11,  3,  0,  9,  5,  4, 10,  4,  2, 10,  0,  0,  0 },
 {  5,  2, 10,  8,  2,  8,  4, 10,  3,  8,  9,  8,  0,  3,  0,  8 },
 {  4, 11,  6,  8, 11,  0,  6, 11,  3,  0,  0,  2,  6,  0,  0,  0 },
 {  3,  2,  6,  5,  2,  5,  0,  0,  5,  3,  0,  0,  0,  0,  0,  0 },
 {  5,  3,  0,  8,  3,  8, 11,  0,  2,  8,  5,  8, 10,  2, 10,  8 },
 {  2,  2, 10,  3,  0,  2,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
 {  2,  3, 10,  1,  7,  0,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
 {  3,  5, 11,  8,  3, 10,  1,  9,  7,  0,  0,  0,  0,  0,  0,  0 },
 {  3,  1,  5,  6,  1,  3,  5,  7,  0,  9,  0,  0,  0,  0,  0,  0 },
 {  4,  9,  7,  0, 11,  8,  3,  8,  1,  3,  8,  6,  1,  0,  0,  0 },
 {  3,  7,  4,  8,  7,  0,  4,  1,  3, 10,  0,  0,  0,  0,  0,  0 },
 {  4, 10,  1,  3,  5, 11,  0,  5,  0,  4,  0, 11,  7,  0,  0,  0 },
 {  4,  8,  0,  4,  8,  7,  0,  6,  1,  5,  1,  3,  5,  0,  0,  0 },
 {  5,  0,  4, 11,  0, 11,  7,  4,  6, 11,  3, 11,  1,  6,  1, 11 },
 {  3, 10,  1,  3,  2,  6,  4,  7,  0,  9,  0,  0,  0,  0,  0,  0 },
 {  4,  0,  9,  7,  6,  4,  2,  5, 11,  8,  3, 10,  1,  0,  0,  0 },
 {  4,  7,  0,  9,  1,  3,  2,  3,  4,  2,  3,  5,  4,  0,  0,  0 },
 {  5,  8,  3, 11,  8,  1,  3,  8,  4,  1,  2,  1,  4,  9,  7,  0 },
 {  4, 10,  1,  3,  2,  6,  0,  6,  7,  0,  6,  8,  7,  0,  0,  0 },
 {  5,  6,  0,  2,  6,  7,  0,  6,  5,  7, 11,  7,  5, 10,  1,  3 },
 {  5,  3,  5,  2,  3,  2,  1,  5,  8,  2,  0,  2,  7,  8,  7,  2 },
 {  4,  7,  0,  2,  7,  2, 11,  1,  3,  2,  3, 11,  2,  0,  0,  0 },
 {  3,  0, 10,  1,  0,  9, 10,  9, 11, 10,  0,  0,  0,  0,  0,  0 },
 {  4,  8,  0,  9,  5,  0,  8,  5,  1,  0,  5, 10,  1,  0,  0,  0 },
 {  4,  5,  9, 11,  5,  1,  9,  5,  6,  1,  1,  0,  9,  0,  0,  0 },
 {  3,  0,  9,  8,  0,  8,  1,  1,  8,  6,  0,  0,  0,  0,  0,  0 },
 {  4,  1, 11, 10,  1,  4, 11,  1,  0,  4,  8, 11,  4,  0,  0,  0 },
 {  3, 10,  1,  0, 10,  0,  5,  5,  0,  4,  0,  0,  0,  0,  0,  0 },
 {  5,  6,  1, 11,  6, 11,  5,  1,  0, 11,  8, 11,  4,  0,  4, 11 },
 {  2,  6,  1,  0,  4,  6,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
 {  4,  6,  4,  2, 10,  1,  9, 10,  9, 11,  9,  1,  0,  0,  0,  0 },
 {  5,  5,  9,  8,  5,  0,  9,  5, 10,  0,  1,  0, 10,  6,  4,  2 },
 {  5,  9, 11,  1,  9,  1,  0, 11,  5,  1,  2,  1,  4,  5,  4,  1 },
 {  4,  0,  9,  8,  0,  8,  1,  4,  2,  8,  2,  1,  8,  0,  0,  0 },
 {  5,  6,  8,  0,  6,  0,  2,  8, 11,  0,  1,  0, 10, 11, 10,  0 },
 {  4,  2,  6,  5,  2,  5,  0, 10,  1,  5,  1,  0,  5,  0,  0,  0 },
 {  2,  5,  8, 11,  1,  0,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
 {  1,  2,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
 {  1,  2,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
 {  2,  5, 11,  8,  1,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
 {  2, 10,  5,  6,  1,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
 {  3,  6, 11,  8,  6, 10, 11,  1,  2,  0,  0,  0,  0,  0,  0,  0 },
 {  2,  4,  8,  9,  2,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
 {  3,  9,  5, 11,  9,  4,  5,  2,  0,  1,  0,  0,  0,  0,  0,  0 },
 {  3,  5,  6, 10,  4,  8,  9,  1,  2,  0,  0,  0,  0,  0,  0,  0 },
 {  4,  1,  2,  0,  6, 10,  4, 10,  9,  4, 10, 11,  9,  0,  0,  0 },
 {  2,  6,  0,  1,  4,  0,  6,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
 {  3,  6,  0,  1,  6,  4,  0,  8,  5, 11,  0,  0,  0,  0,  0,  0 },
 {  3, 10,  0,  1, 10,  5,  0,  5,  4,  0,  0,  0,  0,  0,  0,  0 },
 {  4,  1, 10, 11,  1, 11,  4,  1,  4,  0,  8,  4, 11,  0,  0,  0 },
 {  3,  0,  8,  9,  0,  1,  8,  1,  6,  8,  0,  0,  0,  0,  0,  0 },
 {  4,  5, 11,  9,  5,  9,  1,  5,  1,  6,  1,  9,  0,  0,  0,  0 },
 {  4,  8,  9,  0,  5,  8,  0,  5,  0,  1,  5,  1, 10,  0,  0,  0 },
 {  3,  0,  1, 10,  0, 10,  9,  9, 10, 11,  0,  0,  0,  0,  0,  0 },
 {  2,  1,  2,  0,  3,  7, 11,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
 {  3,  3,  8,  5,  3,  7,  8,  0,  1,  2,  0,  0,  0,  0,  0,  0 },
 {  3,  6, 10,  5,  1,  2,  0, 11,  3,  7,  0,  0,  0,  0,  0,  0 },
 {  4,  2,  0,  1,  6, 10,  7,  6,  7,  8,  7, 10,  3,  0,  0,  0 },
 {  3,  8,  9,  4,  7, 11,  3,  2,  0,  1,  0,  0,  0,  0,  0,  0 },
 {  4,  1,  2,  0,  3,  7,  4,  3,  4,  5,  4,  7,  9,  0,  0,  0 },
 {  4,  5,  6, 10,  3,  7, 11,  4,  8,  9,  1,  2,  0,  0,  0,  0 },
 {  5, 10,  4,  6, 10,  9,  4, 10,  3,  9,  7,  9,  3,  1,  2,  0 },
 {  3,  0,  6,  4,  0,  1,  6,  3,  7, 11,  0,  0,  0,  0,  0,  0 },
 {  4,  6,  4,  1,  1,  4,  0,  8,  5,  3,  8,  3,  7,  0,  0,  0 },
 {  4, 11,  3,  7, 10,  5,  1,  5,  0,  1,  5,  4,  0,  0,  0,  0 },
 {  5,  7,  8, 10,  7, 10,  3,  8,  4, 10,  1, 10,  0,  4,  0, 10 },
 {  4, 11,  3,  7,  8,  9,  1,  8,  1,  6,  1,  9,  0,  0,  0,  0 },
 {  5,  1,  6,  9,  1,  9,  0,  6,  5,  9,  7,  9,  3,  5,  3,  9 },
 {  5,  5,  1, 10,  5,  0,  1,  5,  8,  0,  9,  0,  8, 11,  3,  7 },
 {  4,  0,  1, 10,  0, 10,  9,  3,  7, 10,  7,  9, 10,  0,  0,  0 },
 {  2,  2,  3, 10,  0,  3,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
 {  3,  3,  2,  0,  3, 10,  2,  5, 11,  8,  0,  0,  0,  0,  0,  0 },
 {  3,  2,  5,  6,  2,  0,  5,  0,  3,  5,  0,  0,  0,  0,  0,  0 },
 {  4, 11,  8,  6, 11,  6,  0, 11,  0,  3,  0,  6,  2,  0,  0,  0 },
 {  3,  2,  3, 10,  2,  0,  3,  9,  4,  8,  0,  0,  0,  0,  0,  0 },
 {  4,  5, 11,  4,  4, 11,  9,  3, 10,  2,  3,  2,  0,  0,  0,  0 },
 {  4,  8,  9,  4,  5,  6,  0,  5,  0,  3,  0,  6,  2,  0,  0,  0 },
 {  5,  0,  3,  6,  0,  6,  2,  3, 11,  6,  4,  6,  9, 11,  9,  6 },
 {  3,  6,  3, 10,  6,  4,  3,  4,  0,  3,  0,  0,  0,  0,  0,  0 },
 {  4,  8,  5, 11,  6,  4, 10,  4,  3, 10,  4,  0,  3,  0,  0,  0 },
 {  2,  5,  4,  3,  3,  4,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
 {  3, 11,  8,  4, 11,  4,  3,  3,  4,  0,  0,  0,  0,  0,  0,  0 },
 {  4, 10,  0,  3, 10,  8,  0, 10,  6,  8,  9,  0,  8,  0,  0,  0 },
 {  5, 11,  9,  6, 11,  6,  5,  9,  0,  6, 10,  6,  3,  0,  3,  6 },
 {  3,  8,  9,  0,  8,  0,  5,  5,  0,  3,  0,  0,  0,  0,  0,  0 },
 {  2,  0,  3, 11,  9,  0, 11,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
 {  3,  7,  2,  0,  7, 11,  2, 11, 10,  2,  0,  0,  0,  0,  0,  0 },
 {  4,  5,  7,  8,  5,  2,  7,  5, 10,  2,  0,  7,  2,  0,  0,  0 },
 {  4,  2,  0,  7,  6,  2,  7,  6,  7, 11,  6, 11,  5,  0,  0,  0 },
 {  3,  2,  0,  7,  2,  7,  6,  6,  7,  8,  0,  0,  0,  0,  0,  0 },
 {  4,  4,  8,  9,  2,  0, 11,  2, 11, 10, 11,  0,  7,  0,  0,  0 },
 {  5,  4,  5,  7,  4,  7,  9,  5, 10,  7,  0,  7,  2, 10,  2,  7 },
 {  5,  6, 11,  5,  6,  7, 11,  6,  2,  7,  0,  7,  2,  4,  8,  9 },
 {  4,  9,  4,  6,  9,  6,  7,  2,  0,  6,  0,  7,  6,  0,  0,  0 },
 {  4,  6,  4,  0,  6,  0, 11,  6, 11, 10, 11,  0,  7,  0,  0,  0 },
 {  5,  4,  0, 10,  4, 10,  6,  0,  7, 10,  5, 10,  8,  7,  8, 10 },
 {  3,  7, 11,  5,  7,  5,  0,  0,  5,  4,  0,  0,  0,  0,  0,  0 },
 {  2,  7,  8,  4,  0,  7,  4,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
 {  5, 11, 10,  0, 11,  0,  7, 10,  6,  0,  9,  0,  8,  6,  8,  0 },
 {  2,  5, 10,  6,  9,  0,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
 {  4,  7, 11,  5,  7,  5,  0,  8,  9,  5,  9,  0,  5,  0,  0,  0 },
 {  1,  7,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
 {  2,  9,  1,  2,  7,  1,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
 {  3,  9,  1,  2,  9,  7,  1, 11,  8,  5,  0,  0,  0,  0,  0,  0 },
 {  3,  1,  9,  7,  1,  2,  9,  6, 10,  5,  0,  0,  0,  0,  0,  0 },
 {  4,  2,  7,  1,  2,  9,  7, 10, 11,  6, 11,  8,  6,  0,  0,  0 },
 {  3,  4,  1,  2,  4,  8,  1,  8,  7,  1,  0,  0,  0,  0,  0,  0 },
 {  4, 11,  4,  5, 11,  1,  4, 11,  7,  1,  2,  4,  1,  0,  0,  0 },
 {  4, 10,  5,  6,  1,  2,  8,  1,  8,  7,  8,  2,  4,  0,  0,  0 },
 {  5, 10, 11,  4, 10,  4,  6, 11,  7,  4,  2,  4,  1,  7,  1,  4 },
 {  3,  9,  6,  4,  9,  7,  6,  7,  1,  6,  0,  0,  0,  0,  0,  0 },
 {  4,  5, 11,  8,  6,  4,  7,  6,  7,  1,  7,  4,  9,  0,  0,  0 },
 {  4, 10,  7,  1, 10,  4,  7, 10,  5,  4,  4,  9,  7,  0,  0,  0 },
 {  5,  7,  1,  4,  7,  4,  9,  1, 10,  4,  8,  4, 11, 10, 11,  4 },
 {  2,  6,  8,  1,  8,  7,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
 {  3,  5, 11,  7,  5,  7,  6,  6,  7,  1,  0,  0,  0,  0,  0,  0 },
 {  3, 10,  5,  8, 10,  8,  1,  1,  8,  7,  0,  0,  0,  0,  0,  0 },
 {  2, 10, 11,  7,  1, 10,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
 {  3,  1, 11,  3,  1,  2, 11,  2,  9, 11,  0,  0,  0,  0,  0,  0 },
 {  4,  1,  5,  3,  1,  9,  5,  1,  2,  9,  9,  8,  5,  0,  0,  0 },
 {  4,  5,  6, 10, 11,  3,  2, 11,  2,  9,  2,  3,  1,  0,  0,  0 },
 {  5,  2,  9,  3,  2,  3,  1,  9,  8,  3, 10,  3,  6,  8,  6,  3 },
 {  4,  4,  1,  2,  8,  1,  4,  8,  3,  1,  8, 11,  3,  0,  0,  0 },
 {  3,  1,  2,  4,  1,  4,  3,  3,  4,  5,  0,  0,  0,  0,  0,  0 },
 {  5,  8,  2,  4,  8,  1,  2,  8, 11,  1,  3,  1, 11,  5,  6, 10 },
 {  4,  1,  2,  4,  1,  4,  3,  6, 10,  4, 10,  3,  4,  0,  0,  0 },
 {  4,  4,  1,  6,  4, 11,  1,  4,  9, 11,  3,  1, 11,  0,  0,  0 },
 {  5,  5,  3,  9,  5,  9,  8,  3,  1,  9,  4,  9,  6,  1,  6,  9 },
 {  5,  5,  4,  1,  5,  1, 10,  4,  9,  1,  3,  1, 11,  9, 11,  1 },
 {  2, 10,  3,  1,  4,  9,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
 {  3, 11,  3,  1, 11,  1,  8,  8,  1,  6,  0,  0,  0,  0,  0,  0 },
 {  2,  5,  3,  1,  6,  5,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
 {  4, 11,  3,  1, 11,  1,  8, 10,  5,  1,  5,  8,  1,  0,  0,  0 },
 {  1, 10,  3,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
 {  3,  3,  9,  7,  3, 10,  9, 10,  2,  9,  0,  0,  0,  0,  0,  0 },
 {  4,  5, 11,  8,  3, 10,  7, 10,  9,  7, 10,  2,  9,  0,  0,  0 },
 {  4,  6,  2,  9,  6,  9,  3,  6,  3,  5,  7,  3,  9,  0,  0,  0 },
 {  5,  8,  6,  3,  8,  3, 11,  6,  2,  3,  7,  3,  9,  2,  9,  3 },
 {  4,  4, 10,  2,  4,  7, 10,  4,  8,  7,  7,  3, 10,  0,  0,  0 },
 {  5, 10,  2,  7, 10,  7,  3,  2,  4,  7, 11,  7,  5,  4,  5,  7 },
 {  5,  8,  7,  2,  8,  2,  4,  7,  3,  2,  6,  2,  5,  3,  5,  2 },
 {  2,  6,  2,  4, 11,  7,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
 {  4,  3,  9,  7, 10,  9,  3, 10,  4,  9, 10,  6,  4,  0,  0,  0 },
 {  5, 10,  7,  3, 10,  9,  7, 10,  6,  9,  4,  9,  6,  5, 11,  8 },
 {  3,  9,  7,  3,  9,  3,  4,  4,  3,  5,  0,  0,  0,  0,  0,  0 },
 {  4,  9,  7,  3,  9,  3,  4, 11,  8,  3,  8,  4,  3,  0,  0,  0 },
 {  3,  3, 10,  6,  3,  6,  7,  7,  6,  8,  0,  0,  0,  0,  0,  0 },
 {  4,  3, 10,  6,  3,  6,  7,  5, 11,  6, 11,  7,  6,  0,  0,  0 },
 {  2,  3,  5,  8,  7,  3,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
 {  1,  3, 11,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
 {  2, 10,  2, 11,  2,  9, 11,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
 {  3,  8,  5, 10,  8, 10,  9,  9, 10,  2,  0,  0,  0,  0,  0,  0 },
 {  3,  5,  6,  2,  5,  2, 11, 11,  2,  9,  0,  0,  0,  0,  0,  0 },
 {  2,  8,  6,  2,  9,  8,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
 {  3,  4,  8, 11,  4, 11,  2,  2, 11, 10,  0,  0,  0,  0,  0,  0 },
 {  2, 10,  2,  4,  5, 10,  4,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
 {  4,  4,  8, 11,  4, 11,  2,  5,  6, 11,  6,  2, 11,  0,  0,  0 },
 {  1,  6,  2,  4,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
 {  3,  6,  4,  9,  6,  9, 10, 10,  9, 11,  0,  0,  0,  0,  0,  0 },
 {  4,  8,  5, 10,  8, 10,  9,  6,  4, 10,  4,  9, 10,  0,  0,  0 },
 {  2,  5,  4,  9, 11,  5,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
 {  1,  8,  4,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
 {  2,  6,  8, 11, 10,  6, 11,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
 {  1,  5, 10,  6,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
 {  1,  5,  8, 11,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
 {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 }
};

const char SoXipDrawClipPlane::edgeList[12][2] = {
  { 0, 1 },
  { 0, 2 },
  { 0, 4 },
  { 2, 3 },
  { 4, 5 },
  { 6, 7 },
  { 4, 6 },
  { 1, 3 },
  { 5, 7 },
  { 1, 5 },
  { 2, 6 },
  { 3, 7 },
};

void SoXipDrawClipPlane::GLRender(SoGLRenderAction* action)
{
    if (on.getValue())
    {
	    SbVec3f vertices[8] = {
		    SbVec3f(-0.25, -0.25, -0.25),
		    SbVec3f(1.25, -0.25, -0.25),
		    SbVec3f(-0.25, 1.25, -0.25),
		    SbVec3f(1.25, 1.25, -0.25),
		    SbVec3f(-0.25, -0.25, 1.25),
		    SbVec3f(1.25, -0.25, 1.25),
		    SbVec3f(-0.25, 1.25, 1.25),
		    SbVec3f(1.25, 1.25, 1.25),
	    };

	    const SbMatrix &transform = boundingBox.getValue();
	    const SbPlane &clipPlane = plane.getValue();

	    for (int i = 0; i < 8; i++) {
		    transform.multVecMatrix(vertices[i], vertices[i]);
	    }

	    float cubeValues[8];
	    for (int i = 0; i < 8; i++) {
		    cubeValues[i] = vertices[i].dot(clipPlane.getNormal()) - clipPlane.getDistanceFromOrigin();
	    }

	    unsigned char cubeIndex = 0;
	    for (int i = 0; i < 8; i++) {
		    cubeIndex <<= 1;
		    cubeIndex |= cubeValues[i] < 0;
	    }

	    SbVec3f v;
	    glBegin(GL_TRIANGLES);
	    int nTriangles = indexList[cubeIndex][0];
	    for (int iTriangle = 0; iTriangle < nTriangles; iTriangle++) {
		    for (int iEdge = 0; iEdge < 3; iEdge++) {
			    int edge = indexList[cubeIndex][3 * iTriangle + iEdge + 1];

			    int n0 = edgeList[edge][0];
			    int n1 = edgeList[edge][1];

			    float interpAmount = cubeValues[n0] / (cubeValues[n0] - cubeValues[n1]);
			    v = vertices[n0] * (1 - interpAmount) + vertices[n1] * interpAmount;
			    glVertex3fv(v.getValue());
		    }
	    }
	    glEnd();
    }
}

