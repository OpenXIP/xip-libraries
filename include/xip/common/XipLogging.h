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