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

set WAIT=TRUE
set TEST_RESULT=PASSED
if exist result.xml del result.xml

if not "%1" == "-nowait" goto :start
shift
set WAIT=FALSE

rem *** time in seconds ***
:start
for /f "delims=:. tokens=1-3" %%i in ('echo %TIME%') do @set /A STARTTIME=(%%i*3600)+(%%j*60)+%%k

rem *** run tests ***
if not exist tested mkdir tested
if not exist compare mkdir compare
if exist tested\%1*.png del /Q tested\%1*.png
for /R ..\examples\ %%i IN (%1*.rad) do echo render(256,256,"tested/%%~ni.png"); | ..\out\release\xipbuilder.exe "%%i" /cmd
rem for /R expected\ %%i IN (%1*.png) do ..\out\release\imageCompare "expected/%%~ni.png" "tested/%%~ni.png" "compare/%%~ni.xml"
for /R expected\ %%i IN (%1*.png) do ..\out\release\pngCompare "expected/%%~ni.png" "tested/%%~ni.png" "compare/%%~ni.xml"


echo.
echo -------------------------

if ERRORLEVEL 1 set TEST_RESULT=FAILED

echo Result:   %TEST_RESULT%

rem if exist %TEST_RESULT%.XML copy %TEST_RESULT%.XML result.xml
rem if exist xipresult.xsl copy xipresult.xsl compare

rem *** duration in seconds ***
for /f "delims=:. tokens=1,2,3" %%i in ('echo %TIME%') do @set /A ENDTIME=(%%i*3600)+(%%j*60)+%%k
set /A TOTALTIME=%ENDTIME%-%STARTTIME%
echo Duration: %TOTALTIME% sec
for /f "tokens=1,2" %%i in ('dir /w tested\%1*.png') do @if "%%j" == "File(s)" echo %%j:  %%i
echo.

if "%WAIT%" == "TRUE" pause

