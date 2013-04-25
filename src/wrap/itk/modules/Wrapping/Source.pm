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
# File: Source.pm
#
# Date: October 17, 2005
#
# Author: Julien Gein
#         Siemens Corporate Research
#         julien.gein@scr.siemens.com
#
###############################################################################

    package Wrapping::Source;
    
    require Wrapping::Object;
    require Wrapping::InputInit;
    require Wrapping::InputSet;
    
    @ISA = qw(Wrapping::Object);
  
    sub new
    {
        my ( $class, $include_dir ) = @_;
        
        my $self =
        {
            INCLUDE_DIR  => $include_dir,
            FILENAME     => undef,
            FILTER       => undef
        };
    
        return bless $self, $class;
    }
    
    sub get_input_argument()
    {
        my $self = shift;
        my $input = shift;
                
        if( $input->is_enum() )
        {
            my $enum = $input->enum();
            return ( $enum->argument_name(), $self->get_tree_argument( $enum->argument_name() ) );
        }
        elsif( $input->is_accessor() )
        {           
            my $input_field = $input->input();
            my $input_argument = $self->get_tree_argument( $input_field->argument_name() );
            
            return $input_argument->sub_argument( $input->index() );
        }
        return undef;
    }  
    
    sub get_inputs()
    {
        my $self = shift;
        my $filter = shift;
                
        my @inputs;
        
        foreach( $filter->inputs() )
        {
            my $input = $_;
                                    
            my ( $argument_name, $argument ) = $self->get_input_argument( $input );
            next if( not defined $argument_name );
            next if( not $argument->is_terminal() );
            next if( $argument->mark() );

            $argument->mark(1);
            
            push @inputs, $input;
        }        
        
        @inputs = ( @inputs, $self->get_inputs( $filter->owner() ) ) if( $filter->owner() );
        return @inputs;
    }
    
# Write 
#
##########################################################################

    sub write()
    {
        my $self = shift;
        
        $self->check_before_write();
        
        open WRAPPER, ">$self->{FILENAME}" or
            die "Impossible to open file \"$self->{FILENAME}\"";
                    
        print WRAPPER map { $_ . "\n" } (
            $self->serialize_declarations(),
            "",
            $self->serialize_constructor(),
            "",
            $self->serialize_destructor(),
            "",
            $self->serialize_init_class(),
            ""
        );
            
        if( not $self->filter()->abstract() )
        { 
            print WRAPPER map { $_ . "\n" } (
                $self->serialize_check_input(),
                "",               
                $self->serialize_evaluate()
            );
        }
        
        close WRAPPER;
        
        my $filename = $self->{FILENAME};
        
        # Add the XIP copyright
        `..\\..\\..\\build\\addcopyright.bat $filename`;
    }      
    
# Serialize Functions
#
##########################################################################

    sub serialize_declarations()
    {
        my $self = shift;
        my $filter = $self->filter();
        
        return (
            ( map { "#include <" . $_ . ">" } $filter->includes() ),
            "#include <itk" . $filter->name() . ".h>",
            "#include <" . $self->include_dir() . "SoItkUtils.h>",
            "#include \"SoItk" . $filter->name() . ".h\"",
            "",
            "SO_ENGINE_" . ( $filter->abstract() ? "ABSTRACT_" : "" ) . "SOURCE( SoItk" . $filter->name() . " );"
        );        
    }
    
    sub serialize_enum_init()
    {
        my $self = shift;
        my $filter = $self->filter();

        my @lines;               
        foreach( $filter->enums() )
        {
            my $enum = $_;
            
            if( scalar @lines eq 0 )
            {
                push @lines, "" ;
                push @lines, "// Enumerations";
            }            
            
            foreach( $enum->items() )            
            {
                push @lines, "SO_ENGINE_DEFINE_ENUM_VALUE( " . $enum->name() . ", " . $_ . " );";
            }
        }
        return @lines;
    }
    
    sub serialize_input_init()
    {
        my $self = shift;
        my $filter = $self->filter();
        
        my @lines;       
        foreach( $filter->inputs() )
        {
            my $input = $_;
            
            next if( $input->is_accessor() );
            next if( not $input->enable() );           
            
            if( scalar @lines eq 0 )
            {
                push @lines, "" ;
                push @lines, "// Inputs";
            }
            
            my $is = Wrapping::InputInit->new( $filter, $input );
            @lines = ( @lines, $is->serialize() );
        }
        
        return @lines;
    }
     
    sub serialize_output_init()
    {
        my $self = shift;
        my $filter = $self->filter();
        
        my @lines;        
        foreach( $filter->outputs() )
        {
            my $output = $_;
            
            my $method = "serialize_output_init_" . $output->type();
            $method = "serialize_output_init_ARG_" . $self->get_type( $output ) if( $output->is_arg() );
            
            if( scalar @lines eq 0 )
            {
                push @lines, "" ;
                push @lines, "// Outputs";
            }
            
            if( $self->can( $method ) )
            {
                @lines = ( @lines, $self->$method( $output ) );
            }
            else
            {
                push @lines, "SO_ENGINE_ADD_OUTPUT( " . $output->name() . ", SoSFFloat );";
            }
        }
        
        return @lines;
    }
    
    sub serialize_constructor()
    {
        my $self = shift;
        my $filter = $self->filter();
        
        return (
            "SoItk" . $filter->name() . "\::SoItk" . $filter->name() . "()",
            "{",
            ( map { "\t" . $_ } (
                "SO_ENGINE_CONSTRUCTOR( SoItk" . $filter->name() . " );",
                $self->serialize_enum_init(),
                $self->serialize_input_init(),
                $self->serialize_output_init()
            ) ),
            "}"
        );
    }
    
    sub serialize_destructor()
    {
        my $self = shift;
        my $filter = $self->filter();
        
        my @lines;
        push @lines, "SoItk" . $filter->name() . "\::~SoItk" . $filter->name() . "()";
        push @lines, "{";
        
        my @outputs = $filter->outputs();
        
        push @lines, "" if( scalar @outputs eq 0 );
            
        foreach( @outputs )
        {
            my $output = $_;
            next if( not $output->is_arg() );
            
            my $method = "serialize_output_destroy_ARG_" . $self->get_type( $output );
            
            if( $self->can( $method ) )
            {
                @lines = ( @lines, map { "\t" . $_ } $self->$method( $output ) );
            }
        }
            
        push @lines, "}";
        
        return @lines;
    }
    
    sub serialize_init_class()
    {
        my $self = shift;
        my $filter = $self->filter();
        my $name = $filter->name();
                        
        my $parent_class = "SoEngine";
        $parent_class = "SoItk" . $filter->owner()->name() if( defined $filter->owner() );
        
        return (
            "void",
            "SoItk" . $name . "\::initClass()",
            "{",
                "\tSO_ENGINE_INIT_" . ( $filter->abstract() ? "ABSTRACT_" : "" ) .
                    "CLASS( SoItk" . $name .", " . $parent_class . ", \"" . $parent_class . "\" );",
            "}"
        );
    }    
    
    sub serialize_check_input_terminal()
    {       
        return "return true;";
    }
    
    sub serialize_check_input()
    {
        my $self = shift;        
        my $filter = $self->filter();
        
        my $root = $filter->typeroot();
        $root->mark_all( 0 );
        
        my $method = "serialize_check_input_terminal";
        
        return (
            "bool",
            "SoItk" . $filter->name() . "\::checkInput()",
            "{",
            ( map { "\t" . $_ } (
                $self->serialize_switch( $method ), 
                "", 
                "return false;"
            ) ),
            "}"
        );
    } 
    
    sub serialize_typedefs()
    {
        my $self = shift;
        my $node = shift;
        my $name = shift;
        my $lines = shift;        
            
        if( $node->is_argument() )
        {
            if( $node->is_terminal() )
            {
                return $node->value() if( defined $node->active_child() );
                
                my $child = $node->child(0);
                my $namespace = defined $child->namespace() ? $child->namespace() . "\::" : "";
                
                push @$lines, "typedef " . $namespace . $child->name() . " " . $name . ";";
                return $name;                
            }
            else
            {
                my $type_child = $node->child( $node->active_child() );
                my @args = $self->serialize_typedefs( $type_child, undef, $lines );
                                
                push @$lines, "typedef itk\::" . $node->value() . "< " . join( ", ", @args ) . " > " . $name . ";";
                return $name;
            }            
        }
        else
        {           
            my @args;
            my $num_children = $node->num_children();            
            for( my $i = 0; $i < $num_children; ++ $i )
            {                
                push @args, $self->serialize_typedefs( $node->child($i), $node->child_name($i), $lines )
                    if( $node->child_active( $i ) or $node ne $self->filter()->typeroot() );
            }
            return @args;
        }
    }   
     
    sub serialize_set_inputs()
    {
        my $self = shift;        
        my $filter = shift;
        
        return if( not defined( $filter ) );
                
        my @lines;        
        foreach( $filter->inputs() )
        {
            my $input = $_;
            
            next if( $input->is_accessor() );
            next if( not $input->enable() );           
                        
            push @lines, "// Inherited from SoItk" . $filter->name()
                if( scalar @lines eq 0  and $filter ne $self->filter() );
                                            
            ## Print useful typedefs
            if( $input->is_arg() )
            {           
                my $method = "has_typedef_ARG_" . $self->get_type( $input );
                
                if( $self->can( $method ) )
                {
                    #print "typedef for ", $input->name(), "\n";
                    my $argument = $self->get_tree_argument( $input->argument_name() );
                    $self->serialize_typedefs( $argument, $input->argument_name(), \@lines );
                }
            }
            
            my $is = Wrapping::InputSet->new( $filter, $input, "filter" );
            @lines = ( @lines, $is->serialize() );
        }
        
        push @lines, "";
                
        @lines = ( @lines, $self->serialize_set_inputs( $filter->owner() ) );
        return @lines;
    }
    
    sub get_accessors()
    {
        my $self = shift;        
        my $filter = shift;
        
        my @accessors;
        if( defined( $filter ) )
        {
            foreach( $filter->accessors() )
            {
                my $input_name = $_->input()->name();
                my $method = "serialize_input_ARG_" . $self->get_type( $_->input() );
                                          
                $input_name = $self->$method( $_->input() ) if( $self->can( $method ) );
                push @accessors, $input_name;
            }
            @accessors = ( @accessors, $self->get_accessors( $filter->owner() ) );            
        }
        return @accessors;
    }
    
    sub serialize_check_inputs()
    {
        my $self = shift;        
        my $filter = shift;
        
        my @accessors = $self->get_accessors( $filter );
           
        # Remove the equal entries using a hash map        
        my %unique_accessors;
        foreach( @accessors ){ $unique_accessors{ $_ } = ""; }
        
        my @lines;
        foreach( sort keys %unique_accessors )
        {
            push @lines, "if( !" . $_ . ".getValue() )";
            push @lines, "\t" . "return ;";
            push @lines, "";
        }        
        return @lines;
    }

    sub serialize_set_outputs()
    {
        my $self = shift;        
        my $filter = shift;
        
        return if( not defined( $filter ) );
        
        my @lines;        
        foreach( $filter->outputs() )
        {
            my $output = $_;
            
            next if( not $output->enable() );
                        
            my $method = "serialize_output_set_" . $output->type();
            $method = "serialize_output_set_ARG_" . $self->get_type( $output ) if( $output->is_arg() );
                       
            if( $self->can( $method ) )
            {
                @lines = ( @lines, $self->$method( $output ) );
            }
            else
            {
                push @lines, "SO_ENGINE_OUTPUT( " . $output->name() . ", SoSFFloat, setValue( filter->Get" . $output->name() . "() ) ); "
            }
        }
        
        @lines = ( @lines, $self->serialize_set_outputs( $filter->owner() ) );
        return @lines;
    }
    
    sub serialize_reset_outputs()
    {
        my $self = shift;        
        my $filter = shift;
        
        return if( not defined( $filter ) );
        
        my @lines;
        foreach( $filter->outputs() )
        {
            my $output = $_;
            
            next if( not $output->enable() );
            next if( not $output->is_arg() );
            
            my $method = "serialize_output_reset_ARG_" . $self->get_type( $output );
            
            if( $self->can( $method ) )
            {
                @lines = ( @lines, $self->$method( $output ) );
            }
        }
        
        @lines = ( @lines, $self->serialize_reset_outputs( $filter->owner() ) );
        return @lines;
    }
    
    sub serialize_set_last_outputs()
    {
        my $self = shift;        
        my $filter = shift;
        
        return if( not defined( $filter ) );
        
        my @lines;
        foreach( $filter->outputs() )
        {
            my $output = $_;
            
            next if( not $output->enable() );
            next if( not $output->is_arg() );
            
            my $method = "serialize_output_set_last_ARG_" . $self->get_type( $output );
            
            if( $self->can( $method ) )
            {
                @lines = ( @lines, $self->$method( $output ) );
            }
        }
        
        @lines = ( @lines, $self->serialize_set_last_outputs( $filter->owner() ) );
        return @lines;
    }
    
    sub serialize_evaluate_terminal()
    {    
        my $self = shift;        
        my $filter = $self->filter();
        
        my $top_argument = Filter::TypeNode::Argument->new( "" );
        $top_argument->add_child( $filter->typeroot() );
        $top_argument->active_child(0);        
        
        my @lines;
        $self->serialize_typedefs( $top_argument, "FilterType", \@lines );
        
        push @lines, "";
        push @lines, "FilterType::Pointer filter = FilterType::New();";
        push @lines, "";       

        push @lines, "// Set the filter's inputs";
        @lines = ( @lines, $self->serialize_set_inputs( $filter ) );
        
        push @lines, "// Start processing the ouputs";
        push @lines, "filter->Update();";
        push @lines, "";

        push @lines, "// Retrieve the filter's outputs";
        @lines = ( @lines, $self->serialize_set_outputs( $filter ) );
        
        return @lines;
    }
    
    sub serialize_evaluate()
    {
        my $self = shift;        
        my $filter = $self->filter();
        
        my $root = $filter->typeroot();
        $root->mark_all( 0 );
        
        my $method = "serialize_evaluate_terminal";
        
        my @lines;        
        push @lines, "void";
        push @lines, "SoItk" . $filter->name() . "\::evaluate()";
        push @lines, "{";
        
        @lines = ( @lines, map { "\t" . $_ } $self->serialize_reset_outputs( $filter ) );
        
        push @lines, "";
        
        @lines = ( @lines, map { "\t" . $_ } $self->serialize_check_inputs( $filter ) );
        
        push @lines, "\t" . "if( !checkInput() )";
        push @lines, "\t" . "{";
        push @lines, "\t" . "\t" . "SoDebugError::post( __FILE__, \"Invalid Input Types\" );";
        push @lines, "\t" . "\t" . "return ;";
        push @lines, "\t" . "}"; 
                
        push @lines, "";
        push @lines, "\t" . "try";
        push @lines, "\t" . "{";
        
        @lines = ( @lines, map { "\t\t" . $_ } $self->serialize_switch( $method ) );
        
        push @lines, "\t" . "}";
        push @lines, "\t" . "catch( itk::ExceptionObject& e )";
        push @lines, "\t" . "{";
        push @lines, "\t" . "\t" . "SoDebugError::post( e.GetFile(), \"line \%d: \%s\", e.GetLine(), e.GetDescription() );";
        push @lines, "\t" . "\t" . "return ;";
        push @lines, "\t" . "}";
        push @lines, "\t" . "catch(...)";
        push @lines, "\t" . "{";
        push @lines, "\t" . "\t" . "SoDebugError::post( __FILE__, \"Unknown Exception\" );";
        push @lines, "\t" . "\t" . "return ;";
        push @lines, "\t" . "}";
        push @lines, "";
        
        @lines = ( @lines, map { "\t" . $_ } $self->serialize_set_last_outputs( $filter ) );
        
        push @lines, "}";
        
        return @lines
    }
    
    sub serialize_input_ARG_Image()
    {
        my $self = shift;
        my $input = shift;
        
        
        return $input->multiple() ?
            "Input" . $self->filter()->input_index( $input ) :
            $input->name()
    }

    sub serialize_input_switch()
    {
        my $self = shift;
        my $input = shift;
        
        if( $input->is_accessor() )
        {
            my $method = "serialize_input_ARG_" . $self->get_type( $input->input() );
            if( $self->can( $method ) )
            {
                my $input_name = $self->$method( $input->input() );
                return "switch( " . $input_name . ".getValue()->" . $input->access() . "() )";
            }
        }
        elsif( $input->is_enum() )
        {
            return "switch( " . $input->name() . ".getValue() )";
        }
        else
        {
            die( "Invalid Input type in serialize_input_switch()" );
        }
    }
        
    sub serialize_input_case()
    {
        my $self = shift;
        my $input = shift;
        my $argument = shift;
        my $child_index = shift;
        
        my %convert_symbols;
        $convert_symbols{ "float" } = "SoItkDataImage::FLOAT";
        $convert_symbols{ "unsigned short" } = "SoItkDataImage::UNSIGNED_SHORT";
        $convert_symbols{ "bool" } = "SoItkDataImage::BOOL";
        
        if( $input->is_enum() )
        {
            return "case " . $input->enum()->item( $child_index ) . ":";
        }
        else
        {
            my $name = $argument->child( $child_index )->name();
            $name = $convert_symbols{ $name } if( defined $convert_symbols{ $name } );
            return "case " . $name . ":";
        }
    }
        
    sub serialize_switch_()
    {
        my $self = shift;
        my $inputs = shift;
        my $funcref = shift;
               
        my $input = shift @$inputs;
        my ( $argument_name, $argument ) = $self->get_input_argument( $input );

        my @lines;
        push @lines, $self->serialize_input_switch( $input );
        push @lines, "{";
                
            my $num_children = $argument->num_children();
            for( my $i = 0; $ i < $num_children; ++ $i )
            {
                $argument->active_child( $i );
                
                push @lines, "\t" . $self->serialize_input_case( $input, $argument, $i );
                push @lines, "\t" . "{";
         
                if( scalar @$inputs > 0 )
                {
                    my @inputs_cp = @$inputs;
                    @lines = ( @lines, map { "\t\t" . $_ } $self->serialize_switch_( \@inputs_cp, $funcref ) );
                }
                else
                {
                    @lines = ( @lines, map { "\t\t" . $_ } $self->$funcref() );
                }
                
                push @lines, "\t" . "}";
                push @lines, "\t" . "break ;";
            }
        
        push @lines, "}";
        
        return @lines;
    }
    
    sub serialize_switch()
    {
        my $self = shift;
        my $funcref = shift;
        
        my @inputs = $self->get_inputs( $self->filter() );
        
        $self->filter()->typeroot()->mark_all(0);
                     
        return $self->serialize_switch_( \@inputs, $funcref );
    }
    
# Specific Serialize Functions
#
##############################################################################

    sub serialize_input_init_ARG_Image()
    {
        my $self = shift;
        my $input = shift;
                        
        my $index = $self->filter()->input_index( $input );
        
        return "SO_ENGINE_ADD_INPUT( InputImage" . $index . ", (0) );";
    }
    
    sub serialize_input_init_ARG_Array()
    {
        my $self = shift;
        my $input = shift;
                                
        return (
            "SO_ENGINE_ADD_INPUT( " . $input->name() . ", (0) );",
            $input->name() . ".setNum(0);"
        );
    }
    
    sub serialize_input_init_ARG_Matrix()
    {
        my $self = shift;
        my $input = shift;
        
        return "SO_ENGINE_ADD_INPUT( " . $input->name() . ", (1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 ) );";
    }
    
    sub serialize_input_init_ARG_Point()
    {
        my $self = shift;
        my $input = shift;
        
        return "SO_ENGINE_ADD_INPUT( " . $input->name() . ", ( 0, 0, 0 ) );";
    }
   
    sub serialize_input_init_SoItkSFImageRegion()
    {
        my $self = shift;
        my $input = shift;

        return (
            "SO_ENGINE_ADD_INPUT( " . $input->name() . "Index, (0, 0, 0) );",
            "SO_ENGINE_ADD_INPUT( " . $input->name() . "Size, (0, 0, 0) );"
        );
    }
    
    sub serialize_input_init_SoItkSFNodeContainer()
    {
        my $self = shift;
        my $input = shift;

        return (
            "SO_ENGINE_ADD_INPUT( " . $input->name() . "Seed, (0, 0, 0) );",
            "SO_ENGINE_ADD_INPUT( " . $input->name() . "Label, (0) );"
        );
    }
        
    sub serialize_output_init_ARG_Image()
    {
        my $self = shift;
        my $output = shift;
        
        return (
            "m" . $output->name() . " = 0;",
            "SO_ENGINE_ADD_OUTPUT( " . $output->name() . ", SoItkSFDataImage );"
        );
    }
    
    sub serialize_output_init_ARG_Mesh()
    {
        my $self = shift;
        my $output = shift;
        
        return (
            "m" . $output->name() . " = 0;",
            "SO_ENGINE_ADD_OUTPUT( " . $output->name() . ", SoItkSFDataPointSet );"
        );
    }
    
    sub serialize_output_init_ARG_SimpleDataObjectDecorator()
    {
        my $self = shift;
        my $output = shift;
        
        return (
            "m" . $output->name() . " = 0;",
            "SO_ENGINE_ADD_OUTPUT( " . $output->name() . ", SoItkSFDataDecorator );"
        );
    }
    
    sub serialize_output_destroy_ARG_Image()
    {
        my $self = shift;
        my $output = shift;
        
        return (
            "if( m" . $output->name() . " )",
            "\t" . "m" . $output->name() . "->unref();",
            "m" . $output->name() . " = 0;"
        );
    }
    
    sub serialize_output_destroy_ARG_SimpleDataObjectDecorator()
    {
        my $self = shift;
        my $output = shift;
        
        return (
            "if( m" . $output->name() . " )",
            "\t" . "m" . $output->name() . "->unref();",
            "m" . $output->name() . " = 0;"
        );
    }
    
    ## Set
    
    sub serialize_input_set_ARG_Image()
    {
        my $self = shift;
        my $input = shift;
        
        my $index = $self->filter->input_index( $input );
        
        return (
            "SoItkDataImage* InputImage" . $index . "\_ = InputImage" . $index . ".getValue();",
            $input->argument_name() . "* itkInputImage" . $index . " =",
            "\tstatic_cast< " . $input->argument_name() . "* >( InputImage" . $index . "\_->getPointer() );",
            "if( !itkInputImage" . $index . " )",
            "\treturn ;",
            "filter->SetInput( $index, itkInputImage" . $index . " );"
        );
    }
    
    sub serialize_input_set_ARG_Array()
    {
        my $self = shift;
        my $input = shift;
        
        return "FIXME";
    }
    
    sub serialize_input_set_ARG_Matrix()
    {
        my $self = shift;
        my $input = shift;
        
        my $image_argument = $self->get_tree_argument( "InputImageType" );
        my $pxt = $image_argument->sub_argument( 0 )->value();
        my $dim = $image_argument->sub_argument( 1 )->value();
        
        my @lines;
        push @lines, "SbMatrix " . $input->name() . "Matrix_ = " . $input->name() . ".getValue();";
        push @lines, "MatrixType " . $input->name() . "Matrix;";
        
        for( my $i = 0; $i < $dim; ++ $i )
        {
            for( my $j = 0; $j < $dim; ++ $j )
            {
                push @lines, $input->name() . "Matrix[" . $i . "][" . $j . "] = " . $input->name() . "Matrix_[" . $i . "][" . $j . "];";
            }   
        }
        push @lines, "filter->Set" . $input->name() . "( " . $input->name() . "Matrix );";
        return @lines;
    }
    
    sub serialize_input_set_ARG_Point()
    {
        my $self = shift;
        my $input = shift;
        
        my $image_argument = $self->get_tree_argument( "InputImageType" );
        my $pxt = $image_argument->sub_argument( 0 )->value();
        my $dim = $image_argument->sub_argument( 1 )->value();
        
        my @lines;
        push @lines, "SbVec3f " . $input->name() . "Point_ = " . $input->name() . ".getValue();";
        push @lines, "PointType " . $input->name() . "Point;";
        
        for( my $i = 0; $i < $dim; ++ $i )
        {
            push @lines, $input->name() . "Point[" . $i . "] = " . $input->name() . "Point_[" . $i . "];";
        }
        push @lines, "filter->Set" . $input->name() . "( " . $input->name() . "Point );";
        return @lines;
    }
    
    sub serialize_input_set_ARG_ImageToImageMetric()
    {
        my $self = shift;
        my $input = shift;
        
        return (
            "SoItkDataImageMetric* " . $input->name() . "\_ = " . $input->name() . ".getValue();",
            $input->argument_name() . "* itk" . $input->name() . " =",
            "\tstatic_cast< " . $input->argument_name() . "* >( " . $input->name() . "\_->getPointer() );",
            "if( !itk" . $input->name() . " )",
            "\treturn ;",
            "filter->Set" . $input->name() . "( itk" . $input->name() . " );",
            ""
        );
    }
    
    sub serialize_input_set_ARG_InterpolateImageFunction()
    {
        my $self = shift;
        my $input = shift;
        
        return (
            "SoItkDataInterpolator* " . $input->name() . "\_ = " . $input->name() . ".getValue();",
            $input->argument_name() . "* itk" . $input->name() . " =",
            "\tstatic_cast< " . $input->argument_name() . "* >( " . $input->name() . "\_->getPointer() );",
            "if( !itk" . $input->name() . " )",
            "\treturn ;",
            "filter->Set" . $input->name() . "( itk" . $input->name() . " );",
            ""
        );
    }
    
    sub serialize_input_set_ARG_Transform()
    {
        my $self = shift;
        my $input = shift;
        
        return (
            "SoItkDataTransform* " . $input->name() . "\_ = " . $input->name() . ".getValue();",
            $input->argument_name() . "* itk" . $input->name() . " =",
            "\tstatic_cast< " . $input->argument_name() . "* >( " . $input->name() . "\_->getPointer() );",
            "if( !itk" . $input->name() . " )",
            "\treturn ;",
            "filter->Set" . $input->name() . "( itk" . $input->name() . " );",
            ""
        );
    }
    
    sub serialize_input_set_ARG_SingleValuedNonLinearOptimizer()
    {
        my $self = shift;
        my $input = shift;
        
        return (
            "SoItkDataOptimizer* " . $input->name() . "\_ = " . $input->name() . ".getValue();",
            $input->argument_name() . "* itk" . $input->name() . " =",
            "\tstatic_cast< " . $input->argument_name() . "* >( " . $input->name() . "\_->getPointer() );",
            "if( !itk" . $input->name() . " )",
            "\treturn ;",
            "filter->Set" . $input->name() . "( itk" . $input->name() . " );",
            ""
        );
    }
    
    sub serialize_input_set_SoItkSFIndex()
    {
        my $self = shift;
        my $input = shift;

        my $dimension = $self->get_tree_argument( "Dimension" )->value();
        
        return (
            "{",
            "\titk::Index< " . $dimension . " > " . $input->name() . "Index;",
            "\tfor( unsigned int i = 0; i < " . $dimension . "; ++ i )",
            "\t\t" . $input->name() . "Index.m_Index[i] = " . $input->name() . ".getValue()[i];",
            "\tfilter->Set" . $input->name() . "( " . $input->name() . "Index );",
            "}"
        );
    }

    sub serialize_input_set_SoItkSFSeeds()
    {
        my $self = shift;
        my $input = shift;
        
        my $dimension = $self->get_tree_argument( "Dimension" )->value();
        
        return (
            "{",
            "\titk::Index< " . $dimension . " > SeedIndex;",
            "\tfilter->ClearSeeds();",
            "\tfor( unsigned int s = 0; s < " . $input->name() . ".getNum(); ++ s )",
            "\t{",
            "\t\tSbVec3f v = " . $input->name() . "[s];",
            "\t\tInput0.getValue()->getModelMatrix().inverse().multVecMatrix( v, v );",
            "\t\tfor( unsigned int i = 0; i < " . $dimension . "; ++ i )",
            "\t\t\tSeedIndex.m_Index[i] = v[i] * Input0.getValue()->getDimension( i );",
            "\t\tfilter->Add" . $input->name() . "( SeedIndex );",
            "\t}",
            "}"
        );
    }

    sub serialize_input_set_SoItkSFSeed()
    {
        my $self = shift;
        my $input = shift;

        my $dimension = $self->get_tree_argument( "Dimension" )->value();
        
        return (
            "{",
            "\titk::Index< " . $dimension . "> SeedIndex;",
            "\tSbVec3f v = " . $input->name() . ".getValue();",
            "\tInput0.getValue()->getModelMatrix().inverse().multVecMatrix( v, v );",
            "\tfor( unsigned int i = 0; i < " . $dimension . "; ++ i )",
            "\t\tSeedIndex.m_Index[i] = v[i] * Input0.getValue()->getDimension( i );",
            "\tfilter->Set" . $input->name() . "( SeedIndex );",
            "}"
        );
    }

    sub serialize_input_set_SoItkSFSize()
    {
        my $self = shift;
        my $input = shift;

        my $dimension = $self->get_tree_argument( "Dimension" )->value();
        
        return (
            "{",
            "\titk::Size< " . $dimension . "> " . $input->name() . "Size;",
            "\tfor( unsigned int i = 0; i < " . $dimension . "; ++ i )",
            "\t\t" . $input->name() . "Size.m_Size[i] = " . $input->name() . ".getValue()[i];",
            "\tfilter->Set" . $input->name() . "( " . $input->name() . "Size );",
            "}"
        );
    }

    sub serialize_input_set_SoItkSFPoint()
    {
        my $self = shift;
        my $input = shift;        

        my $dimension = $self->get_tree_argument( "Dimension" )->value();
        
        return (
            "{",
            "\titk::Point< double, " . $dimension . " > " . $input->name() . "Point;",
            "\tfor( unsigned int i = 0; i < " . $dimension . "; ++ i )",
            "\t\t" . $input->name() . "Point[i] = " . $input->name() . ".getValue()[i];",
            "\tfilter->Set" . $input->name() . "( " . $input->name() . "Point );",
            "}"
        );
    }

    sub serialize_input_set_SoItkSFImageRegion()
    {
        my $self = shift;
        my $input = shift;

        my $dimension = $self->get_tree_argument( "Dimension" )->value();
        
        return (
            "{",
            "\t" . "itk::ImageRegion< " . $dimension . " > " . $input->name() . "Region;",
            "\t" . "for( unsigned int i = 0; i < " . $dimension . "; ++ i )",
            "\t" . "{",
            "\t" . "\t" . $input->name() . "Region.SetIndex( i, " . $input->name() . "Index.getValue()[i] );",
            "\t" . "\t" . $input->name() . "Region.SetSize( i, " . $input->name() . "Size.getValue()[i] );",
            "\t" . "}",
            "\t" . "filter->Set" . $input->name() . "( " . $input->name() . "Region );",
            "}"
        );
    }

    sub serialize_input_set_SoItkSFNodeContainer()
    {
        my $self = shift;
        my $input = shift;

        my $dimension = $self->get_tree_argument( "Dimension" )->value();
        
        return (
            "{",
            "\tif( " . $input->name() . "Seed.getNum() != " . $input->name() . "Label.getNum() )",
            "\t{",
            "\t\tSoDebugError::post( __FILE__, \"Number of Seeds and Labels do not match\" );",
            "\t\treturn ;",
            "\t}",
            "\ttypedef FilterType::NodeContainer NodeContainer;",
            "\ttypedef FilterType::NodeType NodeType;",
            "\tNodeContainer::Pointer seeds = NodeContainer::New();",
            "\tseeds->Initialize();",
            "\tfor( unsigned int s = 0; s < " . $input->name() . "Seed.getNum(); ++ s )",
            "\t{",
            "\t\tSbVec3f v = " . $input->name() . "Seed[s];",
            "\t\tInput0.getValue()->getModelMatrix().inverse().multVecMatrix( v, v );",
            "\t\titk::Index< " . $dimension . "> SeedIndex;",
            "\t\tfor( unsigned int i = 0; i < " . $dimension . "; ++ i )",
            "\t\tSeedIndex.m_Index[i] = v[i] * Input0.getValue()->getDimension( i );",
            "\t\t\\\n",
            "\t\tNodeType node;",
            "\t\tnode.SetValue( " . $input->name() . "Label[s] );",
            "\t\tnode.SetIndex( SeedIndex );",
            "\t\t\\\n",
            "\t\tseeds->InsertElement( s, node );",
            "\t}",
            "\tfilter->Set" . $input->name() . "( seeds );",
            "}"
        );
    }
    
    sub serialize_output_set_ARG_SimpleDataObjectDecorator()
    {
        my $self = shift;
        my $output = shift;
        
        my %xip_flag;
        $xip_flag{"float"} = "FLOAT";
        $xip_flag{"unsigned short"} = "UNSIGNED_SHORT";
        $xip_flag{"double"} = "DOUBLE";
        
        my $argument = $self->get_tree_argument( $output->argument_name() );
        my $type = $argument->sub_argument( 0 )->value();
        
        my $type_flag = $xip_flag{ $type };
        
        return (
            "filter->Get" . $output->name() . "()->Register();",
            "m" . $output->name() . " = new SoItkDataDecorator( SoItkDataDecorator::" . $type_flag . " );" ,
            "m" . $output->name() . "->ref();",
            "m" . $output->name() . "->setPointer( filter->Get" . $output->name() . "() );"
        );
    }
    
    sub serialize_output_set_ARG_Image()
    {
        my $self = shift;
        my $output = shift;
        
        my %xip_flag;
        $xip_flag{"float"} = "FLOAT";
        $xip_flag{"unsigned short"} = "UNSIGNED_SHORT";
        $xip_flag{"bool"} = "BOOL";
        
        my $image_argument = $self->get_tree_argument( "OutputImageType" );
        my $pixel_type = $image_argument->sub_argument( 0 )->value();
        my $dimension  = $image_argument->sub_argument( 1 )->value();
        
        my $type_flag = $xip_flag{ $pixel_type };
        
        return (
            "filter->Get" . $output->name() . "()->Register();",
            "m" . $output->name() . " = new SoItkDataImage( SoItkDataImage::" . $type_flag . ", " . $dimension . ",",
            "\t" . "Input0.getValue()->getModelMatrix() );" ,
            "m" . $output->name() . "->ref();",
            "m" . $output->name() . "->setPointer( filter->Get" . $output->name() . "() );"
        );
    }
    
    sub serialize_output_set_ARG_Mesh()
    {
        my $self = shift;
        my $output = shift;
        
        my %xip_flag;
        $xip_flag{"float"} = "FLOAT";
        $xip_flag{"unsigned short"} = "UNSIGNED_SHORT";
        
        my $image_argument = $self->get_tree_argument( "OutputMeshType" );
        my $pixel_type = $image_argument->sub_argument( 0 )->value();
        my $dimension  = $image_argument->sub_argument( 1 )->value();
        
        my $type_flag = $xip_flag{ $pixel_type };
        
        return (
            "filter->Get" . $output->name() . "()->Register();",
            "m" . $output->name() . " = new SoItkDataPointSet( SoItkDataPointSet::" . $type_flag . ", " . $dimension . " );",
            "m" . $output->name() . "->ref();",
            "m" . $output->name() . "->setPointer( filter->Get" . $output->name() . "() );"
        );
    }
    
    sub serialize_output_reset_ARG_Image()
    {
        my $self = shift;
        my $output = shift;
        
        return (
            "if( m" . $output->name() . " )",
            "{",
            "\t" . "m" . $output->name() . "->unref();",
            "\t" . "m" . $output->name() . " = 0;",
            "\t" . "SO_ENGINE_OUTPUT( " . $output->name() . ", SoItkSFDataImage, setValue( 0 ) );",
            "}"
        );
    }
    
    sub serialize_output_reset_ARG_Mesh()
    {
        my $self = shift;
        my $output = shift;
        
        return (
            "if( m" . $output->name() . " )",
            "{",
            "\t" . "m" . $output->name() . "->unref();",
            "\t" . "m" . $output->name() . " = 0;",
            "\t" . "SO_ENGINE_OUTPUT( " . $output->name() . ", SoItkSFDataPointSet, setValue( 0 ) );",
            "}"
        );
    }
    
    sub serialize_output_reset_ARG_SimpleDataObjectDecorator()
    {
        my $self = shift;
        my $output = shift;
        
        return (
            "if( m" . $output->name() . " )",
            "{",
            "\t" . "m" . $output->name() . "->unref();",
            "\t" . "m" . $output->name() . " = 0;",
            "\t" . "SO_ENGINE_OUTPUT( " . $output->name() . ", SoItkSFDataDecorator, setValue( 0 ) );",
            "}"
        );
    }
    
    sub serialize_output_set_last_ARG_SimpleDataObjectDecorator()
    {
        my $self = shift;
        my $output = shift;
        
        return "SO_ENGINE_OUTPUT( " . $output->name() . ", SoItkSFDataDecorator, setValue( m" . $output->name() . " ) );";
    }
    
    sub serialize_output_set_last_ARG_Image()
    {
        my $self = shift;
        my $output = shift;
        
        return "SO_ENGINE_OUTPUT( " . $output->name() . ", SoItkSFDataImage, setValue( m" . $output->name() . " ) );";
    }
    
    ##################
    ##################
    
    sub has_typedef_ARG_Image() { return 1; }
    sub has_typedef_ARG_ImageMetric() { return 1; }
    sub has_typedef_ARG_Interpolator() { return 1; }
    sub has_typedef_ARG_Optimizer() { return 1; }
    sub has_typedef_ARG_Transform() { return 1; }    
    sub has_typedef_ARG_SimpleDataObjectDecorator() { return 1; }
    sub has_typedef_ARG_Neighborhood() { return 1; }
    sub has_typedef_ARG_Mesh() { return 1; }
    