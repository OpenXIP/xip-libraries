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

    package Filter::Filter;
    
    require Filter::Entity;
    @ISA = qw(Filter::Entity);
    
    # Fields
    require Filter::Field;
    require Filter::Field::Input;
    require Filter::Field::InputEnum;
    require Filter::Field::InputArg;
    require Filter::Field::Accessor;    
    require Filter::Field::Output;
    require Filter::Field::OutputArg;    
    
    # Enumeration
    require Filter::Enum;
    
    # Template Arguments Configurations
    require Filter::TypeNode;
    require Filter::TypeNode::Argument;
    require Filter::TypeNode::Type;
    
    sub new()
    {
        my ($that, $name) = @_;
       
        my $class = ref($that) || $that;
        
        my $self =
        {
            NAME            => $name,
            OWNER           => undef,
            FILTERS         => undef,
            TYPEROOT        => Filter::TypeNode::Type->new( $name ),
            FIELDS	        => undef,
            ENUMS	        => undef,
            ABSTRACT        => undef,
            INCLUDES        => undef,
            ENABLED         => 1
        };
      
        # Transform $self into an object of class $class
        return bless $self, $class;
    }
    
    sub typeroot()
    {
        my $self = shift;
        if( @_ )
        {
            $self->{TYPEROOT} = shift;
        }
        return $self->{TYPEROOT};
    }
    
    sub typenode()
    {
        my $self = shift;
        my $name = shift;
        
        return $self->{TYPEROOT}->get_node( $name );
    }
    
    sub abstract()
    {
        my $self = shift;
        if( @_ )
        {
            $self->{ABSTRACT} = shift;
        }
        return $self->{ABSTRACT};        
    }
    
    sub add_filter()
    {
        my $self = shift;
        my $filter = shift;
        $filter->owner( $self );
        $self->{FILTERS}{$filter->name()} = $filter;
    }
    
    sub add_field()
    {
        my $self = shift;
        my $field = shift;
        $field->owner( $self );
        $self->{FIELDS}{$field->name()} = $field;
        return $field;
    }
    
    sub add_enum()
    {
        my $self = shift;
        my $enum = shift;
        $enum->owner( $self );
        $self->{ENUMS}{$enum->name()} = $enum;
        return $enum;        
    }
    
    sub add_include()
    {
        my $self = shift;
        push @{$self->{INCLUDES}}, shift;
    }
    
    sub filter()
    {
        my $self = shift;
        my $filter_name = shift;
        return $self->{FILTERS}{$filter_name};        
    }
    
    sub field()
    {
        my $self = shift;
        my $field_name = shift;
        return $self->{FIELDS}{$field_name};
    }
    
    sub enum()
    {
        my $self = shift;
        my $enum_name = shift;
        return $self->{ENUMS}{$enum_name};
    }
    
    sub fields()
    {
        my $self = shift;
        return values %{$self->{FIELDS}};
    }
    
    sub enums()
    {
        my $self = shift;
        return values %{$self->{ENUMS}};
    }
    
    sub includes()
    {
        my $self = shift;
        return @{$self->{INCLUDES}};
    }
    
    sub filters()
    {
        my $self = shift;
        return values %{$self->{FILTERS}};
    }
    
    sub accessors()
    {
        my $self = shift;
        
        my @accessors;        
        map { push @accessors, $_ if( $_->is_accessor() ) } values %{$self->{FIELDS}};
        return @accessors;        
    }
    
    sub inputs()
    {
        my $self = shift;
        
        my @inputs;
        map { push @inputs, $_ if( $_->is_input() ) } values %{$self->{FIELDS}};
        return @inputs;        
    }
    
    sub outputs()
    {
        my $self = shift;       
       
        my @outputs;        
        map { push @outputs, $_ if( $_->is_output() ) } values %{$self->{FIELDS}};
        return @outputs;
    }
    
    sub input_index_()
    {
        my $self = shift;
        my $input = shift;
                        
        my ( $num, $found ) = defined $self->owner() ? $self->owner()->input_index_( $input ) : ( -1, 0 );
        return ( $num, $found ) if( $found );
                
        foreach( $self->inputs() )
        {
            next if( not $_->enable() );
            next if( not $_->is_arg() );
            next if( $_->is_accessor() );
            next if( $_->is_enum() );           
            
            return ( $num + 1, 1 ) if( $_ eq $input );            
            ++ $num if( $_->argument_name() eq $input->argument_name() );
        }

        return ( $num, 0 );
    }
    
    sub input_index()
    {
        my $self = shift;
        my $input = shift;
                        
        my ( $num, $found ) = $self->input_index_( $input );
        return $num;
    }

    sub serialize()
    {
        my $self = shift;
        
        my ( @lines, @sub_lines );
        
        # Filter
        #
        my $enable = $self->enable() ? "" : " enabled = \"false\"";
        push @lines, "<filter id = \"" . $self->name() . "\"" . $enable . ">";
        
        # Abstract
        #
        push @lines, "\t" . "<abstract/>" if( $self->abstract() );
        
        # Includes
        #
        @lines = ( @lines, map { "\t" . "<include id = \"" . $_ . "\"/>" } $self->includes() );
        
        # Arguments and Declarations
        #
        my $typenode = $self->typeroot();

        my $has_arguments = 0;
        my $has_declarations = 0;
        
        my $num_children = $typenode->num_children();
        for( my $i = 0; $i < $num_children; ++ $i )
        {           
            $has_arguments = 1 if( $typenode->child_active( $i ) );
            $has_declarations = 1 if(
                not $typenode->child_active( $i ) and
                ( not $typenode->child( $i )->mark() or $typenode->child_name( $i ) ne $typenode->child( $i )->reference() ) );
        }
       
        if( $has_arguments )
        {
            push @lines, "\t" . "<arguments>";
            for( my $i = 0; $i < $num_children; ++ $i )
            {
                next if( not $typenode->child_active( $i ) );
                @lines = ( @lines, map { "\t\t$_" } $typenode->child( $i )->serialize( $typenode->child_name( $i ), 1 ) );
            }
            push @lines, "\t" . "</arguments>";
            push @lines, "";
        }
        
        if( $has_declarations )
        {
            push @lines, "\t" . "<declarations>";
            for( my $i = $index; $i < $num_children; ++ $i )
            {
                next if( $typenode->child_active( $i ) );
                @lines = ( @lines, map { "\t\t$_" } $typenode->child( $i )->serialize( $typenode->child_name( $i ), 0 ) );
            }
            push @lines, "\t" . "</declarations>";                
            push @lines, "";
        }
        
        @sub_lines = ();
        @lines = ( @lines, map { ( @sub_lines, map { "\t$_" } $_->serialize() ) } $self->enums() );
        @lines = ( @lines, ( map "\t" . $_->serialize(), sort{ $a->name() cmp $b->name() } $self->fields() ) );
        
        push @lines, "" if( scalar $self->filters() );
        
        @sub_lines = ();
        @lines = ( @lines, map { ( @sub_lines, map { "\t$_" } $_->serialize() ) } $self->filters() );
        
        push @lines, "</filter>";
        push @lines, "";
        
        return @lines;
    }