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
// use XIPIVRENDERER_API only for classes that are needed in other libraries
#ifndef XIPIVRENDERER_H
#define XIPIVRENDERER_H

#ifdef WIN32
	#ifdef  XIPIVRENDERER_EXPORTS
		#define XIPIVRENDERER_API __declspec(dllexport)
	#else
		#define XIPIVRENDERER_API __declspec(dllimport)
	#endif
#else
	// no export needed for non-Windows platforms
	#define XIPIVRENDERER_API 
#endif

int XIPIVRENDERER_API xipivrenderer_init();

#endif
