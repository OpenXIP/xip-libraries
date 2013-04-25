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
# File: Header.pm
#
# Date: October 17, 2005
#
# Author: Julien Gein
#         Siemens Corporate Research
#         julien.gein@scr.siemens.com
#
###############################################################################

    package Wrapping::Header;
    
    require Wrapping::Object;
    require Wrapping::InputInclude;
    require Wrapping::InputDecl;
    
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
    
# Write Functions
#
##########################################################################
    
    sub write()
    {
        my $self = shift;
        my $filter = $self->filter();
        
        $self->check_before_write();
        
        open WRAPPER, ">$self->{FILENAME}" or
            die "Impossible to open file \"$self->{FILENAME}\"";
        
        print WRAPPER "#ifndef SO_ITK_".uc( $filter->name() )."_H_\n";
        print WRAPPER "# define SO_ITK_".uc( $filter->name() )."_H_\n\n";        
        
        my $parent_class;
        if( defined $filter->owner() )
        {         
            print WRAPPER map { "# include <" . $_ . ">\n" } $self->serialize_includes();
            
            $parent_class = "SoItk" . $filter->owner()->name();
            print WRAPPER "# include \"" . $parent_class . ".h\"" . "\n";            
        }
        else
        {
            $parent_class = "SoEngine";
            print WRAPPER "# include <Inventor/Engines/SoSubEngine.h>" . "\n";
            print WRAPPER "# include <xip/inventor/itk/xipivitk.h>" . "\n";
        }
        
        print WRAPPER "\n";
        
        print WRAPPER "class XIPIVITK_API SoItk" . $filter->name() . " : public " . $parent_class . "\n";
        print WRAPPER "{\n";
        
        print WRAPPER "\tSO_ENGINE_" . ( $filter->abstract() ? "ABSTRACT_" : "" ) . "HEADER( " . $filter->name() ." );\n";
        print WRAPPER "\n";
        print WRAPPER "public:\n";
        
        print WRAPPER map { "\t" . $_ . "\n" } $self->serialize_enumerations();
        
        print WRAPPER "\t" . "SoItk" . $filter->name() . "();\n";
        print WRAPPER "\n";
        
        print WRAPPER map { "\t" . $_ . "\n" } $self->serialize_fields();               
        
        print WRAPPER "\tstatic void initClass();\n";
        print WRAPPER "\n";
        
        print WRAPPER "protected:\n";
        print WRAPPER "\t" . "~SoItk" . $filter->name() . "();\n";
        print WRAPPER "\n";
        
        my $abstract_suffix = $filter->abstract() ? " = 0" : "";        
        print WRAPPER "\tvirtual bool checkInput()", $abstract_suffix, ";\n";
        print WRAPPER "\tvirtual void evaluate()", $abstract_suffix, ";\n";
        print WRAPPER "\n";
        
        print WRAPPER map { "\t" . $_ . "\n" } $self->serialize_internal_outputs();

        print WRAPPER "};";
        print WRAPPER "\n";
        print WRAPPER "\n";
        print WRAPPER "#endif // SO_ITK_".uc( $filter->name() )."_H_\n";        
        
        close WRAPPER;
        
        my $filename = $self->{FILENAME};
        
        # Add the XIP copyright
        `..\\..\\..\\build\\addcopyright.bat $filename`;
    }
    
    sub write_copyright()
    {
        print WRAPPER
        
    }
    
    sub serialize_includes()
    {
        my $self = shift;        
        my $filter = $self->filter();
        
        my @lines;
        foreach( $filter->fields() )
        {
            my $input = $_;
            
            next if( $input->is_accessor() );
            next if( not $input->enable() );
            
            my $is = Wrapping::InputInclude->new( $filter, $input );
            @lines = ( @lines, $is->serialize() );
        }
        
        # Remove the equal entries using a hash map
        my %unique_includes;
        @unique_includes{ @lines } = ();       
        return sort keys %unique_includes;
    }
    
    sub serialize_enumerations()
    {
        my $self = shift;        
        my $filter = $self->filter();
        
        my @lines;
        foreach( $filter->enums() )
        {       
            my $enum = $_;
            my $last_item = ($enum->items())[ $enum->num_items() - 1 ];
            
            @lines = ( @lines, (
                "enum " . $enum->name(),
                "{",
                ( map { "\t" . $_ . ( $_ eq $last_item ? "" : "," ) } $enum->items() ),
                "};",
                ""
            ) );
        }
        return @lines;
    }
    
    sub serialize_fields()
    {
        my $self = shift;        
        my $filter = $self->filter();
        
        my @lines;
        foreach( $filter->inputs() )
        {
            my $input = $_;
            
            next if( $input->is_accessor() );
            next if( not $input->enable() );
            
            my $is = Wrapping::InputDecl->new( $filter, $input );
            @lines = ( @lines, $is->serialize() );
        }
        
        foreach( $filter->outputs() )
        {
            my $output = $_;
            
            next if( not $output->enable() );
            
            push @lines, "" if( scalar @lines ne 0 );            
            push @lines, "SoEngineOutput " . $output->name() . ";";
        }
        
        push @lines, "" if( scalar @lines ne 0 );            
        
        return @lines;
    }
    
    sub serialize_internal_outputs()
    {
        my $self = shift;        
        my $filter = $self->filter();
        
        my @lines;
        foreach( $filter->outputs() )
        {
            my $output = $_;
            
            next if( not $output->enable() );
            next if( not $output->is_arg() );
            
            $method = "serialize_output_ARG_" . $self->get_type( $output ) if( $output->is_arg() );
            
            if( $self->can( $method ) )
            {
                @lines = ( @lines, $self->$method( $output ) );
            }
        }        
        return @lines;
    }
    
    sub serialize_output_ARG_Image()
    {
        my $self = shift;
        my $output = shift;
        
        return "SoItkDataImage* m" . $output->name() . ";"
    }
    
    sub serialize_output_ARG_Mesh()
    {
        my $self = shift;
        my $output = shift;
        
        return "SoItkDataPointSet* m" . $output->name() . ";"
    }
    
    sub serialize_output_ARG_SimpleDataObjectDecorator()
    {
        my $self = shift;
        my $output = shift;
        
        return "SoItkDataDecorator* m" . $output->name() . ";"
    }