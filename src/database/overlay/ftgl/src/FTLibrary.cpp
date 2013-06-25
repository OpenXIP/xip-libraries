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
*/#include    "FTLibrary.h"


const FTLibrary&  FTLibrary::Instance()
{
    static FTLibrary ftlib;
    return ftlib;
}


FTLibrary::~FTLibrary()
{
    if( library != 0)
    {
        FT_Done_FreeType( *library);

        delete library;
        library= 0;
    }

//  if( manager != 0)
//  {
//      FTC_Manager_Done( manager );
//
//      delete manager;
//      manager= 0;
//  }
}


FTLibrary::FTLibrary()
:   library(0),
    err(0)
{
    Initialise();
}


bool FTLibrary::Initialise()
{
    if( library != 0)
        return true;

    library = new FT_Library;
    
    err = FT_Init_FreeType( library);
    if( err)
    {
        delete library;
        library = 0;
        return false;
    }
    
//  FTC_Manager* manager;
//  
//  if( FTC_Manager_New( lib, 0, 0, 0, my_face_requester, 0, manager )
//  {
//      delete manager;
//      manager= 0;
//      return false;
//  }

    return true;
}
