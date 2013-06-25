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
#ifndef SO_ITK_UTILS_H_
# define SO_ITK_UTILS_H_

# define SO_ITK_SET_FIELD_DATA_VALUE(object,field,type) \
	{ \
		if( field.getValue() ) { \
			itk::Object* obj = static_cast< itk::Object* >( field.getValue()->getPointer() ); \
			if( obj ) { \
				type* val = dynamic_cast< type* >( obj ); \
				if( val ) object->Set##field( *val ); \
			} \
		} \
	}

# define SO_ITK_SET_FIELD_DATA(object,field,type) \
	{ \
		if( field.getValue() ) { \
			itk::Object* obj = static_cast< itk::Object* >( field.getValue()->getPointer() ); \
			if( obj ) { \
				type* val = dynamic_cast< type* >( obj ); \
				if( val ) object->Set##field( val ); \
			} \
		} \
	}

# define SO_ITK_SET_FIELD_MDATA(object,field,index,type) \
	{ \
		if( field##index.getValue() ) { \
			itk::Object* obj = static_cast< itk::Object* >( field##index.getValue()->getPointer() ); \
			if( obj ) { \
				type* val = dynamic_cast< type* >( obj ); \
				if( val ) object->Set##field( index, val ); \
			} \
		} \
	}

# define SO_ITK_SET_FIELD_ARRAY(object,field,type) \
	{ \
		if( field.getNum() ) \
		{ \
			unsigned int num = field.getNum(); \
			itk::Array< type > array( num ); \
			for( unsigned int i = 0; i < num; ++i  ) \
				array[i] = field[i]; \
			\
			object->Set##field( array ); \
		} \
	}

# define SO_ITK_SET_FIELD_ARRAY2D(object,field,type,dimension) \
	{ \
		if( field.getNum() ) \
		{ \
			/* We assume the 2D array has a number of columns equal to */ \
			/* dimension (cf. MultiResolutionPyramidImageFilter)       */ \
			if( field.getNum() % dimension ) \
			{ \
				SoError::post( "Warning: Field '" #field "' ignored. Invalid number of elements." ); \
			} \
			else \
			{ \
				unsigned int cols = dimension; \
				unsigned int rows = field.getNum() / dimension; \
				\
				itk::Array2D< type > array( rows, cols ); \
				for( unsigned int i = 0; i < rows; ++ i ) \
				for( unsigned int j = 0; j < cols; ++ j ) \
					array[i][j] = field[ i* cols + j ]; \
				\
				object->Set##field( array ); \
			} \
		} \
	}

# define SO_ITK_SET_FIELD_FIXEDARRAY(object,field,type,dimension) \
	{ \
		if( field.getNum() == dimension ) \
		{ \
			itk::FixedArray< type, dimension > array; \
			for( unsigned int i = 0; i < dimension; ++ i ) \
				array[i] = field[i]; \
			\
			object->Set##field( array ); \
		} \
		else \
		{ \
			SoError::post( "Warning: Field '" #field "' ignored. Array size should be " #dimension ); \
		} \
	}

# define SO_ITK_SET_FIELD_MATRIX(object,field,type,rows,cols) \
	{ \
		itk::Matrix< type, rows, cols > m; \
		for( unsigned int i = 0; i < rows; ++ i ) \
		for( unsigned int j = 0; j < cols; ++ j ) \
			m[i][j] = field.getValue()[i][j]; \
		object->Set##field( m ); \
	}

# define SO_ITK_SET_FIELD_SIZE(object,field,dimension) \
	{ \
		if( field.getNum() != dimension ) \
		{ \
			SoError::post( "Warning: Field '" #field "' ignored. Array size should be " #dimension ); \
		} \
		else \
		{ \
			itk::Size< dimension > v; \
			for( unsigned int i = 0; i < dimension; ++ i ) \
				v[i] = field[i]; \
			object->Set##field( v ); \
		} \
	}

# define SO_ITK_SET_FIELD_INDEX(object,field,dimension) \
	{ \
		if( field.getNum() != dimension ) \
		{ \
			SoError::post( "Warning: Field '" #field "' ignored. Array size should be " #dimension ); \
		} \
		else \
		{ \
			itk::Index< dimension > v; \
			for( unsigned int i = 0; i < dimension; ++ i ) \
				v[i] = field[i]; \
			object->Set##field( v ); \
		} \
	}   


# define SO_ITK_SET_FIELD_ND_VECTOR(className,object,field,type,dimension) \
	{ \
		if( field.getNum() != dimension ) \
		{ \
			SoError::post( "Warning: Field '" #field "' ignored. Array size should be " #dimension ); \
		} \
		else \
		{ \
			itk::className< type, dimension > v; \
			for( unsigned int i = 0; i < dimension; ++ i ) \
				v[i] = field[i]; \
			object->Set##field( v ); \
		} \
	}

# define SO_ITK_SET_FIELD_VECTOR(object,field,type,dimension) \
	SO_ITK_SET_FIELD_ND_VECTOR(Vector,object,field,type,dimension)

# define SO_ITK_SET_FIELD_POINT(object,field,type,dimension) \
	SO_ITK_SET_FIELD_ND_VECTOR(Point,object,field,type,dimension)
    
# define SO_ITK_SET_FIELD_SEED(object,field,dimension) \
    { \
        itk::Index< dimension > index; \
        SbVec3f v = field.getValue(); \
        Input0.getValue()->getModelMatrix().inverse().multVecMatrix( v, v ); \
        for( unsigned int i = 0; i < dimension; ++ i ) \
            index.m_Index[i] = v[i] * Input0.getValue()->getDimension( i ); \
        object->Set##field( index ); \
    }
    
# define SO_ITK_SET_FIELD_SEEDS(object,field,dimension) \
    { \
        object->Clear##field##s(); \
        \
        unsigned int numSeeds = field.getNum(); \
        for( unsigned int seedId = 0; seedId < numSeeds; ++ seedId ) \
        { \
            itk::Index< dimension > index; \
            SbVec3f v = field[ seedId ]; \
            Input0.getValue()->getModelMatrix().inverse().multVecMatrix( v, v ); \
            for( unsigned int i = 0; i < dimension; ++ i ) \
                index.m_Index[i] = v[i] * Input0.getValue()->getDimension( i ); \
            object->Add##field( index ); \
        } \
    }
    
# define SO_ITK_SET_FIELD_IMAGE_REGION(object,field,dimension) \
	{ \
		if( field.getNum() != dimension * 2 ) \
		{ \
			SoError::post( "Warning: Field '" #field "' ignored. Array size should be %d", 2*dimension ); \
		} \
		else \
		{ \
			itk::ImageRegion< dimension > r; \
			unsigned int i; \
			for( i = 0; i < dimension; ++ i ) \
				r.SetIndex( i, field[i] ); \
			for( i = 0; i < dimension; ++ i ) \
				r.SetSize( i, field[dimension + i] ); \
			object->Set##field( r ); \
		} \
	}
    
# define SO_ITK_SET_FIELD_NODE_CONTAINER(object,field,type,dimension) \
    { \
        SbItkNodeContainer nodes = field.getValue(); \
        if( nodes.getNumElements() )\
        { \
            typedef itk::LevelSetNode< type, dimension > NodeType; \
            typedef itk::VectorContainer< unsigned int, NodeType > NodeContainerType; \
            \
            NodeContainerType::Pointer nc = NodeContainerType::New(); \
			nc->Register(); \
            nc->Initialize(); \
            \
            for( unsigned int s = 0; s < nodes.getNumElements(); ++ s ) \
            { \
                SbVec3f v = nodes.getSeed( s ); \
                Input0.getValue()->getModelMatrix().inverse().multVecMatrix( v, v ); \
                \
                itk::Index< dimension > SeedIndex; \
                for( unsigned int i = 0; i < dimension; ++ i ) \
                    SeedIndex.m_Index[i] = v[i] * Input0.getValue()->getDimension( i ); \
                \
                NodeType node; \
                node.SetValue( nodes.getLabel( s ) ); \
                node.SetIndex( SeedIndex ); \
                \
                nc->InsertElement( s, node ); \
            } \
            object->Set##field( nc ); \
        } \
    }
    
# define SO_ITK_SET_FIELD_VALUE(object,field) \
    object->Set##field( field.getValue() );

# define SO_ITK_SET_FIELD_VALUES(object,field,type,num) \
	{ \
		if( field.getNum() ) \
		{ \
			type values[num]; \
			for( unsigned int i = 0; i < num; ++ i ) \
				values[i] = field[i]; \
			\
			object->Set##field( values ); \
		} \
	}

#endif // SO_ITK_UTILS_H_

