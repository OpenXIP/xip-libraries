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

    package Filter::Visitor;
    
    require XML::Parser::PerlSAX;
    require XML::Grove;
    require XML::Grove::Builder;
    require XML::Grove::AsString;
    require Data::Grove::Visitor;
    
    require Stack::Stack;
    
    require Filter::Filter;
    
    use strict;
    use vars qw{$AUTOLOAD};
    
    sub new
    {
        my $class = shift;
        
        my $self =
        {
            ROOT     => undef,
            FILTER   => undef,
            FILTERS  => undef,
            ARGUMENT => undef,
            DECLARE  => 0,
            ENUM     => undef
        };
    
        return bless $self, $class;
    }
    
    # Get current objects from the stacks
    sub root()
    {
        my $self = shift;
        return $self->{ROOT};
    }
    
    sub filters()
    {
        my $self = shift;
        return @{$self->{FILTERS}};
    }
    
    sub current_filter()
    {
        my $self = shift;
        return $self->{FILTER}->top();
    }
    
    sub current_argument()
    {
        my $self = shift;
        return $self->{ARGUMENT}->top();
    }

    # Get objects previously defined in the filter hierarchy.
    # First look at the current filter. If not found, object is searched in the parent filters.
    sub get_previous_argument()
    {
        my $self = shift;
        my $filter = shift;
        my $argument_name = shift;
        
        my $argument = $filter->typenode( $argument_name );
        return $argument if( defined $argument );
        return undef if( not defined $filter->owner() );
        return $self->get_previous_argument( $filter->owner(), $argument_name );
    }

    sub get_previous_field()
    {
        my $self = shift;
        my $filter = shift;
        my $field_name = shift;
                      
        my $field = $filter->field( $field_name );
        return $field if( defined $field );
        return undef if( not defined $filter->owner() );
        return $self->get_previous_field( $filter->owner(), $field_name );
    }
    
    sub get_previous_enum()
    {
        my $self = shift;
        my $filter = shift;
        my $enum_name = shift;
                      
        my $enum = $filter->enum( $enum_name );
        return $enum if( defined $enum );
        return undef if( not defined $filter->owner() );
        return $self->get_previous_field( $filter->owner(), $enum_name );
    }


    # Visitor's main routines
    sub visit_document
    {
        my $self = shift;
        my $grove = shift;
        
        $self->{FILTER} = Stack::Stack->new();
        $self->{FILTER}->push( Filter::Filter->new( "" ) );
        
        $grove->children_accept_name ($self, @_);

        die( "Invalid XML file" ) if( $self->{FILTER}->num() ne 1 );

        $self->{ROOT} = $self->current_filter()->filter( "ProcessObject" );
        $self->{ROOT}->{OWNER} = undef;
    }
    
    sub visit_element
    {
        my $self = shift;
        my $element = shift;
    
        $element->children_accept_name ($self);
    }
    
    sub visit_entity
    {
        my $self = shift;
        my $entity = shift;
    }
    
    sub visit_characters
    {
        my $self = shift;
        my $characters = shift;
        my $data = $characters->{Data};
    }
    
    # Visitor's specific tags matching
    sub visit_name_filter
    {
        my $self = shift;
        my $element = shift;
    
        my $filter_name = $element->{Attributes}{"id"};
        my $filter_enabled = $element->{Attributes}{"enabled"};
        
        # Create the filter
        my $filter = Filter::Filter->new( $filter_name );                        
        push @{$self->{FILTERS}}, $filter;
        
        $filter->enable( 0 )
            if( defined $filter_enabled and $filter_enabled ne "true" );

        # Set the Parent
        $self->current_filter()->add_filter( $filter );
        
        # By default, inherit the template configurations from parent
        # Will be overwrited later if the user specify its own configurations
        if( defined $filter->owner() )
        {           
            my $parent_root = $filter->owner()->typeroot();
            
            my $num_children = $parent_root->num_children();
            for( my $i = 0; $i < $num_children; ++ $i )
            {                                
                $filter->typeroot()->add_child( 
                    $parent_root->child( $i ),
                    $parent_root->child_name( $i ),
                    $parent_root->child_active( $i ) );
            }
        }
        
        # Push the current filter into the stack
        $self->{FILTER}->push( $filter );
    
        # Continue traversing of the child nodes
        $element->children_accept_name( $self );
          
        # Pop the filters stack
        $self->{FILTER}->pop(); 
    }
    
    sub visit_name_abstract
    {
        my $self = shift;   
        $self->current_filter->abstract(1);
    }
    
    sub visit_name_enum
    {
        my $self = shift;
        my $element = shift;
    
        my $enum_name = $element->{Attributes}{"id"};
        my $enum = Filter::Enum->new( $enum_name );
        
        $self->{ENUM} = $self->current_filter()->add_enum( $enum );
        
        my $enum_arg = $element->{Attributes}{"type"};
        if( defined $enum_arg and $enum_arg =~ /ARG\( ([^\)]*) \)/ )
        {
            my $argument_name = $1;
            my $argument = $self->get_previous_argument( $self->current_filter(), $argument_name );
            
            die( "Unknown reference to argument '$argument_name'" ) if( not defined $argument );

            $enum->argument_name( $argument_name );
        }
    
        $element->children_accept_name( $self );
    }
    
    sub visit_name_include
    {
        my $self = shift;
        my $element = shift;
        
        my $include = $element->{Attributes}{"id"};
        $self->current_filter()->add_include( $include );
    }
    
    sub visit_name_item
    {
        my $self = shift;
        my $element = shift;

        my $item_name = $element->{Attributes}{"id"};
        $self->{ENUM}->add_item( $item_name );
        
        my $item_value = $element->{Attributes}{"value"};
        $self->{ENUM}->item_value( $item_name, $item_value ) if( defined $item_value );
    }
    
    sub visit_name_input
    {
        my $self = shift;
        my $element = shift;
        
        my $id = $element->{Attributes}{"id"};
        my $type = $element->{Attributes}{"type"};
        
        my $field;
        if( $type =~ /ARG\( ([^\)]*) \)/ )
        {
            my $argument = $1;
           
            my $access = $element->{Attributes}{"access"};
            if( defined $access )
            {
                my $input = $self->get_previous_field( $self->current_filter(), $id );
                
                die( "Unknown reference to field '$id'" ) if( not defined $input );
                                
                $field = Filter::Field::Accessor->new( $input, $access, $argument );
            }
            else
            {                
                $field = Filter::Field::InputArg->new( $id, $argument );
                
                my $multiple = $element->{Attributes}{"multiple"};
                $field->multiple(0) if( defined $multiple and $multiple eq "false" );
            }
        }
        else
        {
            my $value = $element->{Attributes}{"value"};

            my $enum = $self->get_previous_enum( $self->current_filter(), $type );            
            if( defined $enum )
            {
                $field = Filter::Field::InputEnum->new( $id, $enum, $value );
            }
            else
            {               
                $field = Filter::Field::Input->new( $id, $type, $value );
                
                my $num = $element->{Attributes}{"num"};
                $field->num( $num ) if( defined $num );
            }
        }
        
        my $field_enabled = $element->{Attributes}{"enabled"};
        $field->enable(0)
            if( defined $field_enabled and $field_enabled ne "true" );
        
        $self->current_filter()->add_field( $field );
    }
    
    sub visit_name_output
    {
        my $self = shift;
        my $element = shift;
        
        my $id = $element->{Attributes}{"id"};
        my $type = $element->{Attributes}{"type"};
        
        my $field;
        if( $type =~ /ARG\( ([^\)]*) \)/ )
        {
            my $argument_name = $1;
            my $argument = $self->get_previous_argument( $self->current_filter(), $argument_name );
            
            die( "Unknown reference to argument '$argument_name'" ) if( not defined $argument );
            
            $field = Filter::Field::OutputArg->new( $id, $argument_name );
        }
        else
        {
            $field = Filter::Field::Output->new( $id, $type );
        }
        
        my $field_enabled = $element->{Attributes}{"enabled"};
        $field->enable(0)
            if( defined $field_enabled and $field_enabled ne "true" );
            
        $self->current_filter()->add_field( $field );
    }
    
    sub visit_name_arguments
    {
        my $self = shift;
        my $element = shift;
                    
        # Create the corresponding argument
        $self->{ARGUMENT} = Stack::Stack->new();
        $self->{ARGUMENT}->push( $self->current_filter()->typeroot() );        

        $self->current_filter()->typeroot()->remove_active_children();
        
        $element->children_accept_name( $self );
                
        $self->{ARGUMENT}->pop();
    }
    
    sub visit_name_declarations
    {
        my $self = shift;
        my $element = shift;
                           
        # Create the corresponding argument
        $self->{ARGUMENT} = Stack::Stack->new();
        $self->{ARGUMENT}->push( $self->current_filter()->typeroot() );
        $self->{DECLARE} = 1;
        
        $element->children_accept_name( $self );
                
        $self->{DECLARE} = 0;
        $self->{ARGUMENT}->pop();
    }
    
    sub visit_name_argument()
    {
        my $self = shift;
        my $element = shift;    
        
        die( "<type> expected, <argument> found" ) if( $self->current_argument()->is_argument() );
        
        my $argument_name = $element->{Attributes}{"id"}; 
                      
        my $argument = Filter::TypeNode::Argument->new( $argument_name );
        my $active = ( ( $self->current_filter()->typeroot() != $self->current_argument() ) or ( not $self->{DECLARE} ) ) ? 1 : 0;
        $self->current_argument()->add_child( $argument, $argument_name, $active );
        
        $self->{ARGUMENT}->push( $argument );
        
        $element->children_accept_name( $self );
        
        $self->{ARGUMENT}->pop();
    }
    
    sub visit_name_type()
    {
        my $self = shift;
        my $element = shift;
        
        die( "<argument> expected, <type> found" ) if( $self->current_argument()->is_type() );
        
        my $type_name = $element->{Attributes}{"id"};
        my $type = $self->current_argument()->add_child( Filter::TypeNode::Type->new( $type_name ) );

        my $namespace = $element->{Attributes}{"namespace"};
        $type->namespace( $namespace ) if( defined $namespace );
        
        $self->{ARGUMENT}->push( $type );
        
        $element->children_accept_name( $self );
        
        $self->{ARGUMENT}->pop();
    }
    
    sub visit_name_use_argument()
    {
        my $self = shift;
        my $element = shift;   

        die( "<type> expected, <argument> found" ) if( $self->current_argument()->is_argument() );
        
        my $ref_name = $element->{Attributes}{"ref"};
        my $argument = $self->get_previous_argument( $self->current_filter(), $ref_name );

        die( "Unknown reference to argument '$ref_name'" ) if( not defined $argument );
                        
        my $id = $element->{Attributes}{"id"};
        my $active = ( ( $self->current_filter()->typeroot() != $self->current_argument() ) or ( not $self->{DECLARE} ) ) ? 1 : 0;
        
        $self->current_argument()->add_child( $argument, defined $id ? $id : $ref_name, $active );
    }