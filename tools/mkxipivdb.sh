#!/bin/bash
#
# ------------------------------------------------------------------------
#
#   mkxipivdb.sh - Make XIP Inventor Component Database
#
#   Copyright (c) 2009, Siemens Corporate Research
#   Princeton, NJ, USA
#
#   Author: Patric Ljung, patric.ljung@siemens.com
#
# ------------------------------------------------------------------------

tooldir=`dirname "$0"`

srcroot=$tooldir/..
xipanalyzer=$tooldir/bin/XipIvSourceAnalyzer


while [ $# -ge 1 ]
do
  case $1 in
    (-o | --outdir) outdir=$2; shift 2;;
    (-x | --exec) xipanalyzer=$2; shift 2;;
    (-\? | --help)
      cat <<EOF
NAME
    mkxipivdb - Make XIP Inventor Component Database

SYNOPSIS
    mkxipivdb [--outdir OUTDIR] [XIP_SOURCE_ROOT]

DESCRIPTION
    Create the XIP Inventor Component Database.  It consists of a 
    set of XML files describing all the Inventor nodes, engines and
    elements found in the XIP Libraries.

    XIP_SOURCE_ROOT specifies the XIP Libraries source root directory.
    It is typically the root directory of the checked out source code.
    The default is ../ relative to the location of this script.

    By default the source files are expected to be located at
    XIP_SOURCE_ROOT/src/database/<library>. This applies up to XIP
    Libraries version 0.3 and will change with version 0.4.

    -o, --outdir DIR
        Save the XML Database files in this directory.  By default
        it is taken to be XIP_SOURCE_ROOT/build/xipivdb.

    -x, --exec XIPANALYZER
        Specify the executable for XipIvSourceAnalyzer.  By default
        the executable is expected to be found in tools/bin.

    -?, --help
        Display this help text

AUTHOR
    Written by Patric Ljung

REPORTING BUGS
    Report bugs on https://collab01a.scr.siemens.com/gf/project/xip

COPYRIGHT
    Copyright (c) 2009 Siemens.  License caBIG...  There is NO WARRANTY,
    to the extent permitted by law.

XIP Utilities 0.2.2
EOF
      exit 0;;

    (-* | --*)
      echo "Option $1 not recognized. Use option -? or --help for more info";
      shift 1;;
    (*)
      srcroot=$*;
      break;;
  esac
done

if [ -z "$srcdir" ]
then
  srcdir=$srcroot/src/database
fi

if [ -z "$outdir" ]
then
  outdir=$srcroot/build/xipivdb
fi

echo ""
echo "Current settings:"
echo "  Source root:  $srcroot"
echo "  Source dir:   $srcdir"
echo "  Output dir:   $outdir"
echo "  Executable:   $xipanalyzer"

if [ ! -d $srcdir ]
then
  echo "The specified source directory is not a directory: \"$srcdir\""
  exit 1
fi

if [ ! -d outdir ]
then
  mkdir -p $outdir
fi

if [ ! -d $outdir ]
then
  echo "Output directory for Database files is not a directory: \"$outdir\""
  exit 2
fi

if [ ! -x $xipanalyzer ]
then
  echo "Xip Analyzer is not found or not an executable: \"$xipanalyzer\"\n"
  echo 3
fi


#
# Generate the Database XML files

for lib in core coregl dicom overlay renderer extra itk vtk remote
do
  if [ -d $srcdir/$lib ]
  then
    echo "Processing library $lib:"
    $xipanalyzer -o $outdir/$lib.xml $srcdir/$lib
  else
    echo "Library $lib missing, skipped..."
  fi
done
