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
#ifndef XIP_LOGGING_H
#define XIP_LOGGING_H

#include <xip/common/XipLog.h>
#include <xip/common/XipException.h>

#define XIP_LOG_FATAL_XIP_EXCN(ex, flags)  XIP_LOG_FATAL_FLF(L"An unhandled XipException occured!", ex.getMessage(),flags, e.getFunction(), e.getLine(), e.getFile())
#define XIP_LOG_ERROR_XIP_EXCN(ex, flags)  XIP_LOG_ERROR_FLF(L"An unhandled XipException occured!", ex.getMessage(),flags, e.getFunction(), e.getLine(), e.getFile())
#define XIP_LOG_WARN_XIP_EXCN(ex, flags)   XIP_LOG_WARN_FLF(L"An unhandled XipException occured!", ex.getMessage(),flags, e.getFunction(), e.getLine(), e.getFile())
#define XIP_LOG_INFO_XIP_EXCN(ex, flags)   XIP_LOG_INFO_FLF(L"An unhandled XipException occured!", ex.getMessage(),flags, e.getFunction(), e.getLine(), e.getFile())
#define XIP_LOG_DEBUG_XIP_EXCN(ex, flags)  XIP_LOG_DEBUG_FLF(L"An unhandled XipException occured!", ex.getMessage(),flags, e.getFunction(), e.getLine(), e.getFile())
#define XIP_LOG_TRACE_XIP_EXCN(ex, flags)  XIP_LOG_TRACE_FLF(L"An unhandled XipException occured!", ex.getMessage(),flags, e.getFunction(), e.getLine(), e.getFile())


#define XIP_LOG_FATAL_XIP_EXCN0(ex)  XIP_LOG_FATAL_FLF(L"An unhandled XipException occured!", ex.getMessage(),(0), e.getFunction(), e.getLine(), e.getFile())
#define XIP_LOG_ERROR_XIP_EXCN0(ex)  XIP_LOG_ERROR_FLF(L"An unhandled XipException occured!", ex.getMessage(),(0), e.getFunction(), e.getLine(), e.getFile())
#define XIP_LOG_WARN_XIP_EXCN0(ex)  XIP_LOG_WARN_FLF(L"An unhandled XipException occured!", ex.getMessage(),(0), e.getFunction(), e.getLine(), e.getFile())
#define XIP_LOG_INFO_XIP_EXCN0(ex)   XIP_LOG_INFO_FLF(L"An unhandled XipException occured!", ex.getMessage(),(0), e.getFunction(), e.getLine(), e.getFile())
#define XIP_LOG_DEBUG_XIP_EXCN0(ex)  XIP_LOG_DEBUG_FLF(L"An unhandled XipException occured!", ex.getMessage(),(0), e.getFunction(), e.getLine(), e.getFile())
#define XIP_LOG_TRACE_XIP_EXCN0(ex)  XIP_LOG_TRACE_FLF(L"An unhandled XipException occured!", ex.getMessage(),(0), e.getFunction(), e.getLine(), e.getFile())


#define XIP_LOG_FATAL_UNKN_EXCN(flags)  XIP_LOG_FATAL_AUTOFLF(L"An unknown Exception occured!", L"An unknown Exception occured!",flags)
#define XIP_LOG_ERROR_UNKN_EXCN(flags)  XIP_LOG_ERROR_AUTOFLF(L"An unknown Exception occured!", L"An unknown Exception occured!",flags)
#define XIP_LOG_WARN_UNKN_EXCN(flags)   XIP_LOG_WARN_AUTOFLF(L"An unknown Exception occured!", L"An unknown Exception occured!",flags)
#define XIP_LOG_INFO_UNKN_EXCN(flags)   XIP_LOG_INFO_AUTOFLF(L"An unknown Exception occured!", L"An unknown Exception occured!",flags)
#define XIP_LOG_DEBUG_UNKN_EXCN(flags)  XIP_LOG_DEBUG_AUTOFLF(L"An unknown Exception occured!", L"An unknown Exception occured!",flags)
#define XIP_LOG_TRACE_UNKN_EXCN(flags)  XIP_LOG_TRACE_AUTOFLF(L"An unknown Exception occured!", L"An unknown Exception occured!",flags)


#define XIP_LOG_FATAL_UNKN_EXCN0()  XIP_LOG_FATAL_AUTOFLF(L"An unknown Exception occured!", L"An unknown Exception occured!",(0))
#define XIP_LOG_ERROR_UNKN_EXCN0()  XIP_LOG_ERROR_AUTOFLF(L"An unknown Exception occured!", L"An unknown Exception occured!",(0))
#define XIP_LOG_WARN_UNKN_EXCN0()   XIP_LOG_WARN_AUTOFLF(L"An unknown Exception occured!", L"An unknown Exception occured!",(0))
#define XIP_LOG_INFO_UNKN_EXCN0()   XIP_LOG_INFO_AUTOFLF(L"An unknown Exception occured!", L"An unknown Exception occured!",(0))
#define XIP_LOG_DEBUG_UNKN_EXCN0()  XIP_LOG_DEBUG_AUTOFLF(L"An unknown Exception occured!", L"An unknown Exception occured!",(0))
#define XIP_LOG_TRACE_UNKN_EXCN0()  XIP_LOG_TRACE_AUTOFLF(L"An unknown Exception occured!", L"An unknown Exception occured!",(0))


#define XIP_CATCH_ALL_AND_LOG_FATAL(flags) catch (...) {XIP_LOG_FATAL_UNKN_EXCN(flags);}
#define XIP_CATCH_ALL_AND_LOG_FATAL0() catch (...) {XIP_LOG_FATAL_UNKN_EXCN0();}

#define XIP_CATCH_ALL_AND_LOG_ERROR(flags) catch (...) {XIP_LOG_ERROR_UNKN_EXCN(flags);}
#define XIP_CATCH_ALL_AND_LOG_ERROR0() catch (...) {XIP_LOG_ERROR_UNKN_EXCN0();}

#define XIP_CATCH_ALL_AND_LOG_WARN(flags) catch (...) {XIP_LOG_WARN_UNKN_EXCN(flags);}
#define XIP_CATCH_ALL_AND_LOG_WARN0() catch (...) {XIP_LOG_WARN_UNKN_EXCN0();}

#define XIP_CATCH_ALL_AND_LOG_INFO(flags) catch (...) {XIP_LOG_INFO_UNKN_EXCN(flags);}
#define XIP_CATCH_ALL_AND_LOG_INFO0() catch (...) {XIP_LOG_INFO_UNKN_EXCN0();}

#define XIP_CATCH_ALL_AND_LOG_DEBUG(flags) catch (...) {XIP_LOG_DEBUG_UNKN_EXCN(flags);}
#define XIP_CATCH_ALL_AND_LOG_DEBUG0() catch (...) {XIP_LOG_DEBUG_UNKN_EXCN0();}

#define XIP_CATCH_ALL_AND_LOG_TRACE(flags) catch (...) {XIP_LOG_TRACE_UNKN_EXCN(flags);}
#define XIP_CATCH_ALL_AND_LOG_TRACE0() catch (...) {XIP_LOG_TRACE_UNKN_EXCN0();}



#define XIP_CATCH_ALL(LOG_BOOL, RETHROW_BOOL, CLEANUP_CODE)     \
    catch (...)                                             \
        {                                                       \
        if (LOG_BOOL) XIP_LOG_ERROR_UNKN_EXCN0();            \
        CLEANUP_CODE                                         \
        if (RETHROW_BOOL) throw;                             \
        }                                                       \

#define XIP_CATCH_XIP_EXCN(LOG_BOOL, RETHROW_BOOL, CLEANUP_CODE) \
    catch (XipException& e)                              \
            {                                                    \
            if (LOG_BOOL) XIP_LOG_ERROR_XIP_EXCN0(e);         \
            CLEANUP_CODE                                      \
            if (RETHROW_BOOL) throw e;                        \
            }                                                    \


#define CATCH_XIP_EXN_AND_ALL(CLEANUP_CODE)         \
    XIP_CATCH_XIP_EXCN(false, false, CLEANUP_CODE) \
    XIP_CATCH_ALL(false, false, CLEANUP_CODE)      \


#define CATCH_AND_LOG_XIP_EXN_AND_ALL(CLEANUP_CODE)        \
    XIP_CATCH_XIP_EXCN(true, false, CLEANUP_CODE)  \
    XIP_CATCH_ALL(true, false, CLEANUP_CODE)       \

#define CATCH_LOG_AND_RETHROW_XIP_EXN_AND_ALL(CLEANUP_CODE)  \
    XIP_CATCH_XIP_EXCN(true, true, CLEANUP_CODE)      \
    XIP_CATCH_ALL(true, true, CLEANUP_CODE)           \

#define CATCH_AND_RETHROW_XIP_EXN_AND_ALL(CLEANUP_CODE)  \
    XIP_CATCH_XIP_EXCN(false, true, CLEANUP_CODE) \
    XIP_CATCH_ALL(false , true, CLEANUP_CODE)     \



#endif