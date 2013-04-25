#
# COPYRIGHT NOTICE.  Copyright (C) 2007 Siemens Corporate Research, 
# Inc. ("caBIG(tm) Participant"). The eXtensible Imaging Platform
# (XIP) was created with NCI funding and is part of the caBIG(tm) 
# initiative. The software subject to this notice and license 
# includes both human readable source code form and machine 
# readable, binary, object code form (the "caBIG(tm) Software").
# 
# This caBIG(tm) Software License (the "License") is between 
# caBIG(tm) Participant and You.  "You (or "Your") shall mean a 
# person or an entity, and all other entities that control, are 
# controlled by, or are under common control with the entity.  
# "Control" for purposes of this definition means (i) the direct or 
# indirect power to cause the direction or management of such 
# entity, whether by contract or otherwise, or (ii) ownership of 
# fifty percent (50%) or more of the outstanding shares, or (iii) 
# beneficial ownership of such entity.
# 
# LICENSE.  Provided that You agree to the conditions described 
# below, caBIG(tm) Participant grants You a non-exclusive, 
# worldwide, perpetual, fully-paid-up, no-charge, irrevocable, 
# transferable and royalty-free right and license in its rights in 
# the caBIG(tm) Software, including any copyright or patent rights 
# therein that may be infringed by the making, using, selling, 
# offering for sale, or importing of caBIG(tm) Software, to (i) 
# use, install, access, operate, execute, reproduce, copy, modify, 
# translate, market, publicly display, publicly perform, and 
# prepare derivative works of the caBIG(tm) Software; (ii) make, 
# have made, use, practice, sell, and offer for sale, and/or 
# otherwise dispose of caBIG(tm) Software (or portions thereof); 
# (iii) distribute and have distributed to and by third parties the 
# caBIG(tm) Software and any modifications and derivative works 
# thereof; and (iv) sublicense the foregoing rights set out in (i), 
# (ii) and (iii) to third parties, including the right to license 
# such rights to further third parties.  For sake of clarity, and 
# not by way of limitation, caBIG(tm) Participant shall have no 
# right of accounting or right of payment from You or Your 
# sublicensees for the rights granted under this License.  This 
# License is granted at no charge to You.  Your downloading, 
# copying, modifying, displaying, distributing or use of caBIG(tm) 
# Software constitutes acceptance of all of the terms and 
# conditions of this Agreement.  If you do not agree to such terms 
# and conditions, you have no right to download, copy, modify, 
# display, distribute or use the caBIG(tm) Software.
# 
# 1.	Your redistributions of the source code for the caBIG(tm) 
#     Software must retain the above copyright notice, this list 
#     of conditions and the disclaimer and limitation of 
#     liability of Article 6 below.  Your redistributions in 
#     object code form must reproduce the above copyright notice, 
#     this list of conditions and the disclaimer of Article 6 in 
#     the documentation and/or other materials provided with the 
#     distribution, if any.
# 2.	Your end-user documentation included with the 
#     redistribution, if any, must include the following 
#     acknowledgment: "This product includes software developed 
#     by Siemens Corporate Research Inc."  If You do not include 
#     such end-user documentation, You shall include this 
#     acknowledgment in the caBIG(tm) Software itself, wherever 
#     such third-party acknowledgments normally appear.
# 3.	You may not use the names "Siemens Corporate Research, 
#     Inc.", "The National Cancer Institute", "NCI", "Cancer 
#     Bioinformatics Grid" or "caBIG(tm)" to endorse or promote 
#     products derived from this caBIG(tm) Software.  This 
#     License does not authorize You to use any trademarks, 
# 	service marks, trade names, logos or product names of 
#     either caBIG(tm) Participant, NCI or caBIG(tm), except as 
#     required to comply with the terms of this License.
# 4.	For sake of clarity, and not by way of limitation, You may 
#     incorporate this caBIG(tm) Software into Your proprietary 
#     programs and into any third party proprietary programs.  
#     However, if You incorporate the caBIG(tm) Software into 
#     third party proprietary programs, You agree that You are 
#     solely responsible for obtaining any permission from such 
#     third parties required to incorporate the caBIG(tm) 
#     Software into such third party proprietary programs and for 
#     informing Your sublicensees, including without limitation 
#     Your end-users, of their obligation to secure any required 
#     permissions from such third parties before incorporating 
#     the caBIG(tm) Software into such third party proprietary 
#     software programs.  In the event that You fail to obtain 
#     such permissions, You agree to indemnify caBIG(tm) 
#     Participant for any claims against caBIG(tm) Participant by 
#     such third parties, except to the extent prohibited by law, 
#     resulting from Your failure to obtain such permissions.
# 5.	For sake of clarity, and not by way of limitation, You may 
#     add Your own copyright statement to Your modifications and 
#     to the derivative works, and You may provide additional or 
#     different license terms and conditions in Your sublicenses 
#     of modifications of the caBIG(tm) Software, or any 
#     derivative works of the caBIG(tm) Software as a whole, 
#     provided Your use, reproduction, and distribution of the 
#     Work otherwise complies with the conditions stated in this 
#     License.
# 6.	THIS caBIG(tm) SOFTWARE IS PROVIDED "AS IS" AND ANY 
#     EXPRESSED OR IMPLIED WARRANTIES (INCLUDING, BUT NOT LIMITED 
#     TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, NON-
#     INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE) ARE 
#     DISCLAIMED.  IN NO EVENT SHALL SIEMENS CORPORATE RESEARCH 
#     INC. OR ITS AFFILIATES BE LIABLE FOR ANY DIRECT, INDIRECT, 
#     INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
#     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE 
#     GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR 
#     BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
#     LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
#     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT 
#     OF THE USE OF THIS caBIG(tm) SOFTWARE, EVEN IF ADVISED OF 
#     THE POSSIBILITY OF SUCH DAMAGE.
#
###############################################################################
#
# File: InputSet.pm
#
# Date: December 2, 2005
#
# Author: Julien Gein
#         Siemens Corporate Research
#         julien.gein@scr.siemens.com
#
###############################################################################

    package Wrapping::InputSet;
    
    require Exporter;
    @ISA = qw(Exporter);
  
    sub new
    {
        my ( $class, $filter, $input, $object ) = @_;
        
        my $self =
        {
            FILTER => $filter,
            INPUT => $input,
            OBJECT => $object
        };
    
        return bless $self, $class;
    }    
    
    sub filter()
    {
        my $self = shift;
        $self->{FILTER} = shift if( @_ );
        return $self->{FILTER};
    }
    
    sub input()
    {
        my $self = shift;
        $self->{INPUT} = shift if( @_ );
        return $self->{INPUT};
    }
    
    sub object()
    {
        my $self = shift;
        $self->{OBJECT} = shift if( @_ );
        return $self->{OBJECT};
    }
    
    sub get_tree_argument()
    {
        my $self = shift;
        my $arg_name = shift;
        
        return $self->filter()->typeroot()->get_node( $arg_name );
    }
    
    sub get_type()
    {
        my $self = shift;
        my $field = shift;
        
        my $argument = $self->get_tree_argument( $field->argument_name() );
        die( "Argument not found '" . $field->argument_name() . "'" ) if( not defined $argument );
        
        # FIXME : only support one single type
        return $argument->child(0)->name();
    }

    # Serialize Functions
    #
    ##########################################################################
    
    sub serialize()
    {
        my $self = shift;
        my $input = $self->input();
        my $object = $self->object();
         
        if( $input->is_enum() )
        {
            my $enum = $input->enum();                
            return "" if( $enum->is_arg() );
            
            return $self->serialize_input_set_enum();
        }         
        elsif( $input->is_arg() )
        {
            my $type = $self->get_type( $input );
            my $method = "serialize_input_set_ITK_ARG_" . $type;
            
            return $self->$method() if( $self->can( $method ) );
            
            return $self->serialize_input_set_ITK_Data_All();
        }

        my $num = $input->num();
        my $num_arg = $self->get_tree_argument( $input->num() );
        $num = $num_arg->value() if( defined $num_arg );
        
        return "SO_ITK_SET_FIELD_VALUE( " .$object . ", " . $input->name() . " );" if( $num == 1 );
        return "SO_ITK_SET_FIELD_VALUES( " .$object . ", " . $input->name() . ", " . $input->type() . ", " . $num . " );"
    }
    
    sub serialize_input_set_enum
    {
        my $self = shift;
        my $input = $self->input();
        my $object = $self->object();
        my $enum = $input->enum();
        
        my @lines;
        push @lines, "FilterType::" . $enum->name() . " " . $enum->name() . "_;";
        push @lines, "switch( " . $input->name() . ".getValue() )";
        push @lines, "{";
        
        @lines = ( @lines, map { (
            "\t" . "case " . $_ . ":",
            "\t" . "\t" . $enum->name() . "_ = FilterType::" . $_ . ";",
            "\t" . "\t" . "break ;" ) } $enum->items() );
        
        push @lines, "}";
        push @lines, $object . "->Set" . $input->name() . "( " . $enum->name() . "_ );";
        
        return @lines;
    }

    sub serialize_input_set_ITK_ARG_Array
    {
        my $self = shift;
        my $object = $self->object();
        my $input = $self->input();
        
        my $value_type = $self->get_tree_argument( $input->argument_name() )->sub_argument( 0 )->value();
        
        return "SO_ITK_SET_FIELD_ARRAY( " . $object . ", " . $input->name() . ", " . $value_type . " );"
    }
    
    sub serialize_input_set_ITK_ARG_Array2D
    {
        my $self = shift;
        my $object = $self->object();
        my $input = $self->input();
        
        my $value_type = $self->get_tree_argument( $input->argument_name() )->sub_argument( 0 )->value();
        my $dimension = $self->get_tree_argument( "Dimension" )->value();

        return "SO_ITK_SET_FIELD_ARRAY2D( " . $object . ", " . $input->name() . ", " . $value_type . ", " . $dimension . " );"
    }       
    
    sub serialize_input_set_ITK_ARG_FixedArray
    {
        my $self = shift;
        my $object = $self->object();
        my $input = $self->input();
        
        my $value_type = $self->get_tree_argument( $input->argument_name() )->sub_argument( 0 )->value();
        my $dimension = $self->get_tree_argument( "Dimension" )->value();

        return "SO_ITK_SET_FIELD_FIXEDARRAY( " . $object . ", " . $input->name() . ", " . $value_type . ", " . $dimension . " );"
    }       
        
    sub serialize_input_set_ITK_ND_Vector
    {
        my $self = shift;
        my $type = shift;
        my $object = $self->object();
        my $input = $self->input();
        
        my $value_type = $self->get_tree_argument( $input->argument_name() )->sub_argument( 0 )->value();
        my $dimension = $self->get_tree_argument( "Dimension" )->value();
        
        return "SO_ITK_SET_FIELD_" . $type . "( " . $object . ", " . $input->name() .
            ", " . $value_type . ", " . $dimension . " );"        
    }
    
    sub serialize_input_set_ITK_ARG_Point
    {
        my $self = shift;
        
        return $self->serialize_input_set_ITK_ND_Vector( "POINT" );
    }
    
    sub serialize_input_set_ITK_ARG_Vector
    {
        my $self = shift;
        
        return $self->serialize_input_set_ITK_ND_Vector( "VECTOR" );
    }
    
    sub serialize_input_set_ITK_ARG_Index
    {
        my $self = shift;
        my $object = $self->object();
        my $input = $self->input();
        my $dimension = $self->get_tree_argument( "Dimension" )->value();
        
        return "SO_ITK_SET_FIELD_INDEX( " . $object . ", " . $input->name() .
            ", " . $dimension . " );"
    }
    
    sub serialize_input_set_ITK_ARG_Size
    {
        my $self = shift;
        my $object = $self->object();
        my $input = $self->input();
        my $dimension = $self->get_tree_argument( "Dimension" )->value();

        return "SO_ITK_SET_FIELD_SIZE( " . $object . ", " . $input->name() .
            ", " . $dimension . " );"
    }
        
    sub serialize_input_set_ITK_ARG_ImageRegion
    {
        my $self = shift;
        my $object = $self->object();
        my $input = $self->input();
        
        my $dimension = $self->get_tree_argument( "Dimension" )->value();
        
        return "SO_ITK_SET_FIELD_IMAGE_REGION( " . $object . ", " . $input->name() . ", " . $dimension . " );"
    }        
    
    sub serialize_input_set_ITK_ARG_VectorContainer
    {
        my $self = shift;
        my $object = $self->object();
        my $input = $self->input();
        
        my $value_type = $self->get_tree_argument( $input->argument_name() )->sub_argument( 1 )->sub_argument( 0 )->value();
        my $dimension = $self->get_tree_argument( "Dimension" )->value();
        
        return "SO_ITK_SET_FIELD_NODE_CONTAINER( " . $object . ", " . $input->name() . 
            ", " . $value_type . ", " . $dimension . " );"
    } 
    
    sub serialize_input_set_ITK_ARG_Matrix
    {
        my $self = shift;
        my $object = $self->object();
        my $input = $self->input();
        
        my $value_type = $self->get_tree_argument( $input->argument_name() )->sub_argument( 0 )->value();
        my $dimension = $self->get_tree_argument( "Dimension" )->value();
        
        return "SO_ITK_SET_FIELD_MATRIX( " . $object . ", " . $input->name() . 
            ", " . $value_type . ", " . $dimension . ", " . $dimension . " );"
    } 
        
    sub serialize_input_set_ITK_Data
    {
        my $self = shift;
        my $object = $self->object();
        my $input = $self->input();
        
        return "SO_ITK_SET_FIELD_DATA( " . $object . ", " . $input->name() . ", " . $input->argument_name() . " );"
    }
    
    sub serialize_input_set_ITK_MData
    {
        my $self = shift;
        my $object = $self->object();
        my $input = $self->input();
        
        my $index = $self->filter()->input_index( $input );
        
        return "SO_ITK_SET_FIELD_MDATA( " . $object . ", Input, " . $index .
            ", " . $input->argument_name() . " );"
    }
    
    sub serialize_input_set_ITK_ARG_Image
    {
        my $self = shift;
        my $object = $self->object();
        my $input = $self->input();
        
        return $self->serialize_input_set_ITK_MData() if( $input->multiple() );
        return $self->serialize_input_set_ITK_Data();
    }
    
    sub serialize_input_set_ITK_ARG_Neighborhood
    {
        my $self = shift;
        my $object = $self->object();
        my $input = $self->input();
        
        return "SO_ITK_SET_FIELD_DATA_VALUE( " . $object . ", " . $input->name() . ", " . $input->argument_name() . " );"
    }
    
    sub serialize_input_set_ITK_Data_All
    {
        my $self = shift;
        my $object = $self->object();
        my $input = $self->input();
        
        return $self->serialize_input_set_ITK_Data();
    }
    
    sub serialize_input_set_ITK_ARG_Seed
    {
        my $self = shift;
        my $object = $self->object();
        my $input = $self->input();
        
        my $dimension = $self->get_tree_argument( "Dimension" )->value();
        
        return "SO_ITK_SET_FIELD_SEED( ". $object . ", " . $input->name() . ", " . $dimension . " );"
    }
    
    sub serialize_input_set_ITK_ARG_Seeds
    {
        my $self = shift;
        my $object = $self->object();
        my $input = $self->input();
        
        my $dimension = $self->get_tree_argument( "Dimension" )->value();
        
        # Remove the 's' from the input name
        my $short_input_name = $input->name();
        $short_input_name =~ s/(.)*s$/$1/;        
        
        return "SO_ITK_SET_FIELD_SEEDS( ". $object . ", " . $input->name() . ", " . $dimension . " );"
    }  
