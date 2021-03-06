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
# File: InputInclude.pm
#
# Date: December 2, 2005
#
# Author: Julien Gein
#         Siemens Corporate Research
#         julien.gein@scr.siemens.com
#
###############################################################################

    package Wrapping::InputInclude;
    
    require Exporter;
    @ISA = qw(Exporter);
  
    sub new
    {
        my ( $class, $filter, $input ) = @_;
        
        my $self =
        {
            FILTER => $filter,
            INPUT => $input
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
    
    sub serialize()
    {
        my $self = shift;
        my $input = $self->input();

        if( $input->is_enum() )
        {
            return "Inventor/Fields/SoSFEnum.h"            
        }
        elsif( $input->is_arg() )
        {            
            my $type = $self->get_type( $input );
            my $method = "serialize_input_include_ITK_ARG_" . $type;
            
            return $self->$method() if( $self->can( $method ) );
            
            return "FIXME type " . $type . " not supported";
        }
        elsif( lc $input->type() eq "bool" )
        {
            return "Inventor/Fields/SoSFBool.h"
        }
        
        my $num = $input->num();
        my $num_arg = $self->get_tree_argument( $input->num() );
        $num = $num_arg->value() if( defined $num_arg );
        
        return "Inventor/Fields/SoSFFloat.h" if( $num == 1 );
        return "Inventor/Fields/SoMFFloat.h";
    }

    sub serialize_input_include_ITK_ARG_Array
    {
        return "Inventor/Fields/SoMFFloat.h";                        
    }
    
    sub serialize_input_include_ITK_ARG_FixedArray
    {
        return "Inventor/Fields/SoMFFloat.h";                        
    }
    
    sub serialize_input_include_ITK_ARG_Array2D
    {
        return "Inventor/Fields/SoMFFloat.h";        
    }
    
    sub serialize_input_include_ITK_ARG_Index
    {
        return "Inventor/Fields/SoMFInt32.h";
    }
    
    sub serialize_input_include_ITK_ARG_Size
    {
        return "Inventor/Fields/SoMFInt32.h";
    }
    
    sub serialize_input_include_ITK_ARG_Point
    {
        return "Inventor/Fields/SoMFFloat.h";
    }
    
    sub serialize_input_include_ITK_ARG_Vector
    {
        return "Inventor/Fields/SoMFFloat.h";
    }
    
    sub serialize_input_include_ITK_ARG_ImageRegion
    {
        return "Inventor/Fields/SoMFInt32.h";        
    }
    
    sub serialize_input_include_ITK_ARG_VectorContainer
    {
        return "xip/inventor/itk/SoItkSFNodeContainer.h";
    }
    
    sub serialize_input_include_ITK_ARG_Matrix
    {
        return "Inventor/Fields/SoSFMatrix.h";
    }
    
    sub serialize_input_include_ITK_ARG_Image
    {
        return "xip/inventor/itk/SoItkSFDataImage.h";        
    }
    
    sub serialize_input_include_ITK_ARG_Mesh
    {
        return "xip/inventor/itk/SoItkSFDataPointSet.h";        
    }
    
    sub serialize_input_include_ITK_ARG_ImageToImageMetric
    {
        return "xip/inventor/itk/SoItkSFDataImageMetric.h";
    }
    
    sub serialize_input_include_ITK_ARG_Optimizer
    {
        return "xip/inventor/itk/SoItkSFDataOptimizer.h";                
    }
    
    sub serialize_input_include_ITK_ARG_SingleValuedNonLinearOptimizer
    {
        return "xip/inventor/itk/SoItkSFDataOptimizer.h";                
    }
    
    sub serialize_input_include_ITK_ARG_Transform
    {
        return "xip/inventor/itk/SoItkSFDataTransform.h";                
    }
    
    sub serialize_input_include_ITK_ARG_InterpolateImageFunction
    {
        return "xip/inventor/itk/SoItkSFDataInterpolator.h";                
    }
    
    sub serialize_input_include_ITK_ARG_SimpleDataObjectDecorator
    {
        return "xip/inventor/itk/SoItkSFDataDecorator.h";
    }
    
    sub serialize_input_include_ITK_ARG_Neighborhood
    {
        return "xip/inventor/itk/SoItkSFDataNeighborhood.h";
    }
    
    sub serialize_input_include_ITK_ARG_Seed
    {      
        return "Inventor/Fields/SoSFVec3f.h"
    }
    
    sub serialize_input_include_ITK_ARG_Seeds
    {      
        return "Inventor/Fields/SoMFVec3f.h"
    }  
