@echo off
rem /*
rem  *  COPYRIGHT NOTICE.  Copyright (C) 2007 Siemens Corporate Research, 
rem  *  Inc. ("caBIG(tm) Participant"). The eXtensible Imaging Platform
rem  *  (XIP) was created with NCI funding and is part of the caBIG(tm) 
rem  *  initiative. The software subject to this notice and license 
rem  *  includes both human readable source code form and machine 
rem  *  readable, binary, object code form (the "caBIG(tm) Software").
rem  *  
rem  *  This caBIG(tm) Software License (the "License") is between 
rem  *  caBIG(tm) Participant and You.  "You (or "Your") shall mean a 
rem  *  person or an entity, and all other entities that control, are 
rem  *  controlled by, or are under common control with the entity.  
rem  *  "Control" for purposes of this definition means (i) the direct or 
rem  *  indirect power to cause the direction or management of such 
rem  *  entity, whether by contract or otherwise, or (ii) ownership of 
rem  *  fifty percent (50%) or more of the outstanding shares, or (iii) 
rem  *  beneficial ownership of such entity.
rem  *  
rem  *  LICENSE.  Provided that You agree to the conditions described 
rem  *  below, caBIG(tm) Participant grants You a non-exclusive, 
rem  *  worldwide, perpetual, fully-paid-up, no-charge, irrevocable, 
rem  *  transferable and royalty-free right and license in its rights in 
rem  *  the caBIG(tm) Software, including any copyright or patent rights 
rem  *  therein that may be infringed by the making, using, selling, 
rem  *  offering for sale, or importing of caBIG(tm) Software, to (i) 
rem  *  use, install, access, operate, execute, reproduce, copy, modify, 
rem  *  translate, market, publicly display, publicly perform, and 
rem  *  prepare derivative works of the caBIG(tm) Software; (ii) make, 
rem  *  have made, use, practice, sell, and offer for sale, and/or 
rem  *  otherwise dispose of caBIG(tm) Software (or portions thereof); 
rem  *  (iii) distribute and have distributed to and by third parties the 
rem  *  caBIG(tm) Software and any modifications and derivative works 
rem  *  thereof; and (iv) sublicense the foregoing rights set out in (i), 
rem  *  (ii) and (iii) to third parties, including the right to license 
rem  *  such rights to further third parties.  For sake of clarity, and 
rem  *  not by way of limitation, caBIG(tm) Participant shall have no 
rem  *  right of accounting or right of payment from You or Your 
rem  *  sublicensees for the rights granted under this License.  This 
rem  *  License is granted at no charge to You.  Your downloading, 
rem  *  copying, modifying, displaying, distributing or use of caBIG(tm) 
rem  *  Software constitutes acceptance of all of the terms and 
rem  *  conditions of this Agreement.  If you do not agree to such terms 
rem  *  and conditions, you have no right to download, copy, modify, 
rem  *  display, distribute or use the caBIG(tm) Software.
rem  *  
rem  *  1.	Your redistributions of the source code for the caBIG(tm) 
rem  *      Software must retain the above copyright notice, this list 
rem  *      of conditions and the disclaimer and limitation of 
rem  *      liability of Article 6 below.  Your redistributions in 
rem  *      object code form must reproduce the above copyright notice, 
rem  *      this list of conditions and the disclaimer of Article 6 in 
rem  *      the documentation and/or other materials provided with the 
rem  *      distribution, if any.
rem  *  2.	Your end-user documentation included with the 
rem  *      redistribution, if any, must include the following 
rem  *      acknowledgment: "This product includes software developed 
rem  *      by Siemens Corporate Research Inc."  If You do not include 
rem  *      such end-user documentation, You shall include this 
rem  *      acknowledgment in the caBIG(tm) Software itself, wherever 
rem  *      such third-party acknowledgments normally appear.
rem  *  3.	You may not use the names "Siemens Corporate Research, 
rem  *      Inc.", "The National Cancer Institute", "NCI", "Cancer 
rem  *      Bioinformatics Grid" or "caBIG(tm)" to endorse or promote 
rem  *      products derived from this caBIG(tm) Software.  This 
rem  *      License does not authorize You to use any trademarks, 
rem  *  	service marks, trade names, logos or product names of 
rem  *      either caBIG(tm) Participant, NCI or caBIG(tm), except as 
rem  *      required to comply with the terms of this License.
rem  *  4.	For sake of clarity, and not by way of limitation, You may 
rem  *      incorporate this caBIG(tm) Software into Your proprietary 
rem  *      programs and into any third party proprietary programs.  
rem  *      However, if You incorporate the caBIG(tm) Software into 
rem  *      third party proprietary programs, You agree that You are 
rem  *      solely responsible for obtaining any permission from such 
rem  *      third parties required to incorporate the caBIG(tm) 
rem  *      Software into such third party proprietary programs and for 
rem  *      informing Your sublicensees, including without limitation 
rem  *      Your end-users, of their obligation to secure any required 
rem  *      permissions from such third parties before incorporating 
rem  *      the caBIG(tm) Software into such third party proprietary 
rem  *      software programs.  In the event that You fail to obtain 
rem  *      such permissions, You agree to indemnify caBIG(tm) 
rem  *      Participant for any claims against caBIG(tm) Participant by 
rem  *      such third parties, except to the extent prohibited by law, 
rem  *      resulting from Your failure to obtain such permissions.
rem  *  5.	For sake of clarity, and not by way of limitation, You may 
rem  *      add Your own copyright statement to Your modifications and 
rem  *      to the derivative works, and You may provide additional or 
rem  *      different license terms and conditions in Your sublicenses 
rem  *      of modifications of the caBIG(tm) Software, or any 
rem  *      derivative works of the caBIG(tm) Software as a whole, 
rem  *      provided Your use, reproduction, and distribution of the 
rem  *      Work otherwise complies with the conditions stated in this 
rem  *      License.
rem  *  6.	THIS caBIG(tm) SOFTWARE IS PROVIDED "AS IS" AND ANY 
rem  *      EXPRESSED OR IMPLIED WARRANTIES (INCLUDING, BUT NOT LIMITED 
rem  *      TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, NON-
rem  *      INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE) ARE 
rem  *      DISCLAIMED.  IN NO EVENT SHALL SIEMENS CORPORATE RESEARCH 
rem  *      INC. OR ITS AFFILIATES BE LIABLE FOR ANY DIRECT, INDIRECT, 
rem  *      INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
rem  *      (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE 
rem  *      GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR 
rem  *      BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
rem  *      LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
rem  *      (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT 
rem  *      OF THE USE OF THIS caBIG(tm) SOFTWARE, EVEN IF ADVISED OF 
rem  *      THE POSSIBILITY OF SUCH DAMAGE.
rem  *  
rem  */


rem ### directories ###
for %%i in (bin bin\debug bin\release config groups examples) do @if not exist %%i mkdir %%i


rem ### Qt ###
echo Qt...
copy C:\Qt\4.3.4\bin\QtCored4.dll bin\debug\QtCored4.dll > nul
copy C:\Qt\4.3.4\bin\QtGuid4.dll bin\debug\QtGuid4.dll > nul
copy C:\Qt\4.3.4\bin\QtOpenGLd4.dll bin\debug\QtOpenGLd4.dll > nul
copy C:\Qt\4.3.4\bin\QtSvgd4.dll bin\debug\QtSvgd4.dll > nul
copy C:\Qt\4.3.4\bin\QtXmld4.dll bin\debug\QtXmld4.dll > nul

copy C:\Qt\4.3.4\bin\QtCore4.dll bin\release\QtCore4.dll > nul
copy C:\Qt\4.3.4\bin\QtGui4.dll bin\release\QtGui4.dll > nul
copy C:\Qt\4.3.4\bin\QtOpenGL4.dll bin\release\QtOpenGL4.dll > nul
copy C:\Qt\4.3.4\bin\QtSvg4.dll bin\release\QtSvg4.dll > nul
copy C:\Qt\4.3.4\bin\QtXml4.dll bin\release\QtXml4.dll > nul


rem ### XipBuilder ###
echo XIP...
copy ..\..\xip-build\out\debug\xipbuilder.exe bin\debug\xipbuilder.exe > nul
copy ..\..\xip-build\out\debug\xipbuilder.pdb bin\debug\xipbuilder.pdb > nul
copy ..\..\xip-build\out\debug\xipinv240d.dll bin\debug\xipinv240d.dll > nul

copy ..\..\xip-build\out\release\xipbuilder.exe bin\release\xipbuilder.exe > nul
copy ..\..\xip-build\out\release\xipinv240.dll bin\release\xipinv240.dll > nul

rem ### configuration ###
(type config_redist\config.xml | find /v "Scene Graph""") > config\config.xml
copy config_redist\extensions.xml config\extensions.xml > nul
copy config_redist\help.xml config\help.xml > nul


if "%1" == "/builder" goto :zipbuilder

rem ### libraries ###
for %%i in (xipivcore xipivcoregl xipivdicom xipivitk xipivoverlay xipivrenderer xipivvtk xipivremote) do @echo %%i... & copy ..\..\xip-build\out\debug\%%i.dll bin\debug\ > nul & copy ..\..\xip-build\out\debug\%%i.lib bin\debug\ > nul & copy ..\..\xip-build\out\debug\%%i.pdb bin\debug\ > nul & copy ..\..\xip-build\out\release\%%i.dll bin\release\ > nul & copy ..\..\xip-build\out\release\%%i.lib bin\release\ > nul

del bin\debug\xipivitk*.pdb

rem ### examples ###
echo examples...
for %%i in (rad txt glsl) do @xcopy /y /s ..\examples\*.%%i examples\ > nul
for %%i in (IMA raw png dcm img vtk bin g) do @xcopy /y /s ..\examples\data\*.%%i examples\data\ > nul


rem ### zip it up ###
echo zipping...
if exist xip-win32.zip del xip-win32.zip
zip -r -m -9 xip-win32.zip bin config groups examples

goto :end

:zipbuilder
echo zipping...
if exist xipbuilder-win32.zip del xipbuilder-win32.zip
zip -r -m -9 xipbuilder-win32.zip bin config
rmdir examples groups

:end
