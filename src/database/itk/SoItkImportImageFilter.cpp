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
*/			/* increment the reference count of the resulting image, to avoid */ \
			/* the importFilter instance to destroy it.                       */ \
																				 \
			import->GetOutput()->Register();                                     \
																				 \
			mOutput = new SoItkDataImage( SoItkDataImage::typeFlag, 2 );         \
			mOutput->ref();                                                      \
			mOutput->setPointer( import->GetOutput() );                          \
		}

		#define CASE( type, typeFlag )                                           \
			case typeFlag:                                                       \
				DO_IT( type, typeFlag );                                         \
				break ;

		switch( Type.getValue() )
		{
			CASE( unsigned short, UNSIGNED_SHORT );
			CASE(          float,          FLOAT );
		}

		#undef CASE
		#undef DO_IT
	}
	catch( itk::ExceptionObject& e )
	{
		SoDebugError::post( e.GetFile(), " line %d: %s", e.GetLine(), e.GetDescription() );
		return ;
	}
	catch(...)
	{
		SoDebugError::post( __FILE__, "Unknown Exception" );
		return ;
	}

	SO_ENGINE_OUTPUT( Output, SoItkSFDataImage, setValue( mOutput ) );
}
