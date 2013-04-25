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
# File: Parsing::Read.pm
#
# Date: November 2, 2005
#
# Author: Julien Gein
#         Siemens Corporate Research
#         julien.gein@scr.siemens.com
#
###############################################################################

    package Parsing::Read;
    
    require Exporter;
    require Filter::Filter;

    use strict;
    use vars qw{$AUTOLOAD};

    sub new()
    {
        my $class = shift;
        
        my $self =
        {
            paths => undef,
            filters => undef,
            root => undef,
            nodes => undef,
            callback => undef
        };
    
        return bless $self, $class;        
    }
    
    sub add_path()
    {
        my $self = shift;
        push @{$self->{paths}}, shift;
    }
    
    sub clear_paths()
    {        
        my $self = shift;
        @{$self->{paths}} = ();
    }
    
    sub set_callback()
    {
        my $self = shift;
        $self->{callback} = shift;        
    }
    
    sub read()
    {
        my $self = shift;
            
        my @itk_headers;
        my @itk_sources;
        
        foreach( @{$self->{paths}} )
        {
            $self->get_files( $_, "h\$", \@itk_headers );
            $self->get_files( $_, "(cxx|txx)\$", \@itk_sources );
        }
        
        foreach( grep /ImageFilter/, @itk_headers )
        {
            my $path = $_;        
    
            my $name = '[a-zA-Z][a-zA-Z_\d]*';
            my $itk_class = $1 . $2
                if( $path =~ /itk($name)\.h/ );
                
            #my $method = $self->{callback};
            #&$method( "Reading filter " . $itk_class );
                
            my $filter = Filter::Filter->new( $itk_class );
        
            my $header = $self->read_file( $path );
            $self->read_superclass( $header, $filter );
            $self->read_fields( $header, $filter );
            $self->read_enumerations( $header, $filter );
            $self->read_default_values( $header, $filter );
        
            my @sources = grep /itk$itk_class./, @itk_sources;
            if( scalar( @sources ) eq 1 )
            {            
                my $source = $self->read_file( @sources[0] );
                $self->read_default_values( $source, $filter );
            }
            else
            {
                print STDERR "1. Cannot get default values for filter \"$itk_class\"\n";            
            }
            
            if( defined $filter )
            {
                $self->{nodes}{ $filter->{name} } = Tree::Nary->new( $filter );
                $self->{filters}{ $filter->{name} } = $filter;
            }        
        }
        
        # Creates the root of the hierarchy. The name of this filter is
        # ImageFilter. This filter has been manually written and is included
        # in the xipivitk project.
        my $root_filter = Filter::Filter->new( "ImageSource" );
        $root_filter->set_abstract();

        $self->{root} = Tree::Nary->new( $root_filter );
        $self->{filters}{ "ImageSource" } = $root_filter;
        $self->{nodes}{ "ImageSource" } = $self->{root};
        
        my $method = $self->{callback};
        &$method( "Creating Hierarchy" );
              
        # Create the hierarchy
        foreach( values %{$self->{nodes}} )
        {            
            my $node = $_;
            my $filter = $node->{data};
            
            next if( $filter->{name} eq "ImageSource" );
                        
            my $parent_name = $filter->{parent};
            my $parent_node = $self->{nodes}{$parent_name};
                                    
            if( !defined( $parent_node ) )
            {
                $filter->enable(0);
                $parent_node = $self->{root};
            }
            else
            {
                $filter->parent_filter( $parent_node->{data} );
            }
            
            # Attach a child to the parent node
            Tree::Nary->append( $parent_node, $_ );
        }
        
        # If some filters are disabled, we have to propagate this state to the
        # children.
        $self->propagate_disable( $self->{root}, 1 );
    }
    
    sub propagate_disable()
    {
        my $self = shift;
        my $node = shift;
        my $enabled = shift;
        
        $node->{data}->enable(0) if( not $enabled );
        
        my $num_children = Tree::Nary->n_children( $node );
        for( my $i = 0; $i < $num_children; ++ $i )
        {
            my $child = Tree::Nary->nth_child( $node, $i );
            $self->propagate_disable( $child, $node->{data}->{enabled} );
        }
    }
    
    sub write_XML()
    {
        my $self = shift;
        my $output_file = shift;
        
        my $writer = Filter::XML::Write->new( $output_file );
        $writer->set_root( $self->{root} );
        $writer->write();
    }
        
    sub get_files()
    {
        my $self = shift;        
        my $directory = shift;
        my $pattern = shift;
        my $files = shift;
                
        opendir DIR, $directory or 
            die ("Impossible to open the given directory '$directory'\n" );
            
        my @contents = sort grep !/^\.\.?$/, readdir DIR;
        
        push @{$files}, 
            sort map "$directory/$_", 
            grep /$pattern/,
            @contents;

        foreach( @contents )
        {
            next unless !-l "$directory/$_" && -d "$directory/$_" ;
            $self->get_files( $directory."/".$_, $pattern, $files );
        }

        closedir DIR;
    }   
    
    sub read_file()
    {
        my $self = shift;
        my $file_in = shift;
        
        open INPUT, "<$file_in" or die "Impossible to open \"$file_in\"\n";
        
        undef $/;        
        my $content = <INPUT>;        
        $/ = "\n";
        
        close INPUT;
        
        return $content;   
    }
    
    sub read_fields()
    {
        my $self = shift;
        my $content = shift;
        my $filter = shift;
        
        my $wc = '[\s|\n|\r|\t]';
        my $name = '[a-zA-Z][a-zA-Z_\d]*';
        my $type = $name . '(' . $wc . '*' . $name . ')';
        
        while( $content =~ s/itkSetMacro$wc*\($wc*($name)$wc*,$wc*($type)$wc*\)// )
        {
            $filter->add_field( $1, $2 );
        }
        
        while( $content =~ s/itkSetClampMacro$wc*\($wc*($name)$wc*,$wc*($type)$wc*// )
        {
            $filter->add_field( $1, $2 );
        }
        
        while( $content =~ s/void Set($name)$wc*\($wc*(const)?$wc*($name)// )
        {
            $filter->add_field( $1, $3 );
        }
        
        while( $content =~ s/Set($name)$wc*\(// )
        {
            # FIXME
        }        
    }
    
    sub read_enumerations()
    {
        my $self = shift;        
        my $content = shift;
        my $filter = shift;
        
        my $wc = '[\s|\n|\r|\t]';
        my $name = '[a-zA-Z][a-zA-Z_\d]*';
        
        while( $content =~ s/typedef$wc+enum$wc*{([^}]*})$wc*($name);//)
        {
            my $enum = $2;
            $filter->add_enum( $enum );
            
            my $content = $1;
            while( $content =~ s/$wc*($name)$wc*(=[^,}]*)?[,}]// )
            {
              $filter->add_enum_item( $enum, $1 );
            }
        }      
        
        while( $content =~ s/enum$wc+($name)$wc*{([^}]*})//)
        {
            my $enum = $1;
            $filter->add_enum( $enum );
         
            my $content = $2;
            while( $content =~ s/$wc*($name)$wc*(=[^,}]*)?[,}]// )
            {
              $filter->add_enum_item( $enum, $1 );
            }
        }
    }
    
    sub read_default_values()
    {
        my $self = shift;
        my $content = shift;
        my $filter = shift;
        
        my $wc = '[\r\n\t\s]*';
        my $number = '[0-9]*\.?[0-9]*f?';
        my $name = '[a-zA-Z][a-zA-Z_0-9]*';
        my $composed_name = '[a-zA-Z][a-zA-Z_0-9\s]*';
        my $id = $name.'(\(\))?';
                   
        foreach( $filter->fields_names() )
        {            
            my $field = $_;
            
            ## A single value
            if( $content =~ /(m\_$_)$wc=$wc($number|false|true)$wc;/ )       
            {
                $filter->set_field( $field, $2 );
            }
            
            ## A single number used to initialize an array
            elsif( $content =~ /(m\_$_)\.Fill\($wc($number)$wc\)$wc;/ )
            {
                $filter->set_field( $field, $2 );
            }
            
            ## A numeric traits (i.e templated :( ) value
            elsif( $content =~ /(m\_$_)$wc=($wc)NumericTraits<$composed_name>::($id)/ ) 
            { 
                my $itk_value = $3;
                my $value = $3;
                $value =~ s/Zero/0/;
                $value =~ s/One/1/;
                $value =~ s/min\(\)/0/;
                $value =~ s/max\(\)/65535/;
                $value =~ s/NonpositiveMin\(\)/0/;
                
                $filter->set_field( $field, $value );
            }
            
            ## probably an enum
            elsif( $content =~ /(m\_$_)$wc=$wc($name)$wc;/ ) 
            {
                $filter->set_field( $field, $2 );
            }
        }
    }
    
    sub read_superclass()
    {
        my $self = shift;
        my $content = shift;
        my $filter = shift;
        
        my $wc = '[\s|\n|\r|\t]';
        my $name = '[a-zA-Z][a-zA-Z_\d]*';
                      
        if( $content =~ /$filter->{name}$wc*:$wc*public$wc+($name)/ )
        {
            $filter->set_parent( $1 );
        }
    }