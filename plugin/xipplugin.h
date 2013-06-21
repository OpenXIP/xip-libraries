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

// use XIPPLUGIN_API only for classes that are needed in other libraries

#ifdef WIN32
	#ifdef  XIPPLUGIN_EXPORTS
		#define XIPPLUGIN_API __declspec(dllexport)
	#else
		#define XIPPLUGIN_API __declspec(dllimport)
	#endif
#else
	// no export needed for non-Windows platforms
	#define XIPPLUGIN_API 
#endif

