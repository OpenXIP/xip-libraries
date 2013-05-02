#!/bin/bash
#
# ------------------------------------------------------------------------
#
#   xipdac.sh - XIP Developer Package Archive Creator
#
#   Copyright (c) 2009, Siemens Corporate Research
#   Princeton, NJ, USA
#
#   Author: Patric Ljung, patric.ljung@siemens.com
#
# ------------------------------------------------------------------------

tooldir=`dirname "$0"`

prefix=xipdev
postfix=""
version=0.3.0
platform=win32
buildenv="vs8"
pkglist="libs inventor extern ITK VTK"
force=false;

while [ $# -ge 1 ]
do
  case $1 in
    (-b | --builddir) builddir=$2; shift 2;;
    (-i | --sourcedir) sourcedir=$2; shift 2;;
    (-o | --outdir) outdir=$2; shift 2;;
    (-f | --force) force="true"; shift 1;;
    (-p | --prefix) prefix=$2; shift 2;;
    (-s | --postfix) postfix=$2; shift 2;;
    (-v | --version) version=$2; shift 2;;
    (-l | --platform) platform=$2; shift 2;;
    (-e | --buildenv) buildenv=$2; shift 2;;
    (-\? | --help)
      cat <<EOF
NAME
    xipdac - XIP Development Archives Creator

SYNOPSIS
    xipdac --builddir BUILDDIR --outdir OUTDIR [PKGLIST...]

DESCRIPTION
    Create Development Archives from XIP build and source
    directories.

    -b, --builddir DIR
        Read build content from directory DIR.  The structure
        is expected to be as output from build (not install structure).

    -i, --sourcedir DIR
        Read source files from directory DIR.  The structure
        is expected to be as it should be in archives.

    -o, --outdir DIR
        Save archives in director DIR.

    -p, --prefix
        Specifies the prefix for archive names, default is xip.

    -s, --postfix
        Specifies the postfix for achive names, default is empty.

    -v, --version VERSION
        Specifies the version of the build.  This allows xipdac to
	correctly extract files and create archives compatible with
	previous versions.  Currently supported versions are 0.2, 0.2.1
	0.2.2, 0.3, 0.3.0. Default in this version is 0.3.0.

    -l, --platform PLATFORM
        PLATFORM is one of win32, win64, osx, linux32, linux64
        (This option should be guessed, current default is win32)

    -e, --buildenv BUILDENV
        Used on Windows to specify vs6, vs8, or vs9. Current default is
	vs8, but it should be possible to do a good guess.

    -?, --help
        Display this help text

AUTHOR
    Written by Patric Ljung

REPORTING BUGS
    Report bugs on https://collab01a.scr.siemens.com/gf/project/xip

COPYRIGHT
    Copyright (c) 2009 Siemens.  License caBIG...  There is NO WARRANTY,
    to the extent permitted by law.

XIP Utilities 0.3.0
EOF
      exit 0;;

    (-* | --*)
      echo "Option $1 not recognized. Use option -? or --help for more info";
      shift 1;;
    (*)
      pkglist=$*;
      break;;
  esac
done

echo ""
echo "Current settings:"
echo "  Build dir:    $builddir"
echo "  Source dir:   $sourcedir"
echo "  Output dir:   $outdir"
echo "  Prefix:       $prefix"
echo "  Postfix:      $postfix"
echo "  Version:      $version"
echo "  Platform:     $platform"
echo "  Buildenv:     $buildenv"
echo "  Package list: $pkglist"

if [ ! -d $builddir ]
then
  echo "Base directory for XIP builds is not a directory: \"$builddir\""
  exit 1
else
  pushd $builddir > /dev/null
  builddir=`pwd`
  popd > /dev/null
  echo "Actual base:      $builddir"
fi

if [ ! -d $sourcedir ]
then
  echo "Source directory for XIP source files is not a directory: \"$sourcedir\""
  exit 2
else
  pushd $sourcedir > /dev/null
  sourcedir=`pwd`
  popd > /dev/null
  echo "Actual sourcedir: $sourcedir"
fi


mkdir -p $outdir

if [ ! -d $outdir ]
then
  echo "Output directory for ZIP-files is not a directory: \"$outdir\""
  exit 2
else
  pushd $outdir > /dev/null
  outdir=`pwd`
  popd > /dev/null
  echo "Actual outdir:    $outdir"
fi

ZIP=`which zip`

if [ ! -x $ZIP ]
then
  echo "Executable zip is not found or executable\n"
  echo "Install zip and unzip"
  echo 3
else
#  ZIP="$ZIP -qdgds 1k -r"
  ZIP="$ZIP -r"
fi

# If prefix contains "dev", then don't add -dev postfix
tmp=`echo $prefix | grep "dev"`
if [ -z "$tmp" ]; then postf="-dev"; fi

if [ -n "$version" ]; then postf=$postf-$version; fi
if [ -n "$platform" ]; then postf=$postf-$platform; fi
if [ -n "$buildenv" ]; then postf=$postf-$buildenv; fi
if [ -n "$postfix" ]; then postf=$postf-$postfix; fi

# Content (subdirs) of meta packages
libs="libs"
inventor="inventor"
dcmtk="dcmtk"
itk="ITK"
vtk="VTK"
#extern="extern"
extern="zlib freetype2 ftgl EasyBMP"
all="$libs $inventor $dcmtk $extern $itk $vtk"

srcdir=$sourcedir/src
incdir=$sourcedir/include

INSTALL="install -p -D -t"
INSTALL_FILE="install -p -D"


function instfiles()
{
  local out=$1
  shift
  local files=$*

  for f in $files
  do
    if [ -f $f ]; then
	echo "Installing from $f"
	mkdir -p $out
	$INSTALL_FILE $f $out;
    elif [ -d $f ]; then
	echo "Installing from $f"
	$INSTALL_FILE `find $f -printf "%P\n" | egrep -v '.svn/|/.svn|~$|/#.*#$|.#.*$|^\.$'` $out
    fi
  done
}

function instheaders()
{
  local out=$1
  shift
  local files=$*

  for f in $files
  do
    if [ -f $f ]; then
	echo "Installing from $f"
	mkdir -p $out
	$INSTALL_FILE $f $out;
    elif [ -d $f ]; then
	echo "Installing from $f"
	find $f "(" -name "*.h" -o -name "*.hpp" -o -name "*.hxx" ")" -a -printf "%P\n" |
	while read file; do
	    echo -n "."
	    $INSTALL_FILE $f/$file $out/$file
	done
	echo ""
    fi
  done
}

function instsources()
{
  local out=$1
  shift
  local files=$*

  for f in $files
  do
    if [ -f $f ]; then
	echo "Installing from $f"
	mkdir -p $out
	$INSTALL_FILE $f $out;
    elif [ -d $f ]; then
	echo "Installing from $f"
	find $f "(" -name "*.c" -o -name "*.cpp" -o -name "*.cxx" -o -name "*.c++" ")" \
	    -a -printf "%P\n" |
	while read file; do
	    echo -n "."
	    $INSTALL_FILE $f/$file $out/$file
	done
	echo ""
    fi
  done
}

function create_content()
{
  local p=$1
  local out=$2
  local bdir=$builddir
  local sdir=$srcdir
  local idir=$incdir

  DCMTKVER=dcmtk-3.5.4
  ZLIBVER=zlib-1.2.3
  EASYBMPVER=EasyBMP-1.06
  FREETYPE2VER=freetype-2.2.1

  case $p in
  # Inventor
  (inventor)
    instfiles $out/lib/release \
	$bdir/lib/release/xipinv240.{dll,lib,a,so}
    instfiles $out/lib/debug \
	$bdir/lib/debug/xipinv240*.{dll,lib,a,so,pdb}
    instheaders $out/include \
	$sdir/extern/inventor/lib/database/include \
	$sdir/extern/inventor/lib/interaction/include \
	$sdir/extern/inventor/lib/mevis/include \
	$sdir/extern/inventor/lib/nodekits/include \
	$sdir/extern/inventor/lib/xip/include
    # Currently ignored:
    # $sdir/extern/inventor/libSoXt/include
    ;;

  # XIP Libraries
  (libs)
    instfiles $out/lib/release \
	$bdir/lib/release/xipiv{core,coregl,renderer}.{dll,lib,a,so} \
	$bdir/lib/release/xipiv{dicom,overlay,extra,remote}.{dll,lib,a,so} \
	$bdir/lib/release/xipcommon.{dll,lib,a,so}
    instfiles $out/lib/debug \
	$bdir/lib/debug/xipiv{core,coregl,renderer}*.{dll,lib,a,so,pdb} \
	$bdir/lib/debug/xipiv{dicom,overlay,extra,remote}*.{dll,lib,a,so,pdb} \
	$bdir/lib/debug/xipcommon*.{dll,lib,a,so,pdb}
    instheaders $out/include $idir
    ;;

  # OFFIS DCMTK
  (dcmtk)
    instfiles $out/lib/release \
	$bdir/lib/release/{dcmdata,dcmimage,dcmimgle}.{dll,lib,a,so} \
	$bdir/lib/release/{dcmjpeg,dcmpstat,ofstd}.{dll,lib,a,so}
    instfiles $out/lib/debug \
	$bdir/lib/debug/{dcmdata,dcmimage,dcmimgle}*.{dll,lib,a,so,pdb} \
	$bdir/lib/debug/{dcmjpeg,dcmpstat,ofstd}*.{dll,lib,a,so,pdb}
    for s in config ofstd dcmdata dcmimgle dcmimage dcmjpeg dcmpstat
    do
      instheaders $out/include \
	  $sdir/extern/$DCMTKVER/$s/include
    done
    ;;

  # XIP External Libs (miscellaneous)
  # Option: Put specific package includes in separate or common include???
  #   Both zlib and EasyBMP require its dir in include path... 
  #   Keeping separate dirs allows for easier separation, but more work in
  #   setup of include paths... (no biggie?!?!?)
  (extern)
    # zlib
    instfiles $out/lib/release \
	$bdir/lib/release/zlib.{dll,lib,a,so}
    instfiles $out/lib/debug \
	$bdir/lib/debug/zlib*.{dll,lib,a,so,pdb}
    instheaders $out/include/zlib \
	$sdir/extern/$ZLIBVER/{zlib,zconf,vtk_zlib_mangle,zlibDllConfig}.h
    # EasyBMP
    instfiles $out/lib/release \
	$bdir/lib/release/EasyBMP.{dll,lib,a,so}
    instfiles $out/lib/debug \
	$bdir/lib/debug/EasyBMP*.{dll,lib,a,so,pdb}
    instheaders $out/include/EasyBMP \
	$sdir/extern/$EASYBMPVER/*.h
    # FreeType2
    instfiles $out/lib/release \
	$bdir/lib/release/freetype2*.{dll,lib,a,so}
    instfiles $out/lib/debug \
	$bdir/lib/debug/freetype2*.{dll,lib,a,so,pdb}
    instheaders $out/include/freetype2 \
	$sdir/extern/$FREETYPE2VER/include
    # FTGL
    instfiles $out/lib/release \
	$bdir/lib/release/ftgl.{dll,lib,a,so}
    instfiles $out/lib/debug \
	$bdir/lib/debug/ftgl*.{dll,lib,a,so,pdb}
    instheaders $out/include/ftgl \
	$sdir/database/overlay/ftgl/include/*.h
    ;;

  # zlib extern package, but separate dir
  (zlib)
    instfiles $out/lib/release \
	$bdir/lib/release/zlib.{dll,lib,a,so}
    instfiles $out/lib/debug \
	$bdir/lib/debug/zlib*.{dll,lib,a,so,pdb}
    instheaders $out/include \
	$sdir/extern/$ZLIBVER/{zlib,zconf,vtk_zlib_mangle,zlibDllConfig}.h
    ;;

  # EasyBMP extern package, but separate dir
  (EasyBMP)
    instfiles $out/lib/release \
	$bdir/lib/release/EasyBMP.{dll,lib,a,so}
    instfiles $out/lib/debug \
	$bdir/lib/debug/EasyBMP*.{dll,lib,a,so,pdb}
    instheaders $out/include \
	$sdir/extern/$EASYBMPVER/*.h
    ;;

  # freetype2 extern package, but separate dir
  (freetype2)
    instfiles $out/lib/release \
	$bdir/lib/release/freetype2*.{dll,lib,a,so}
    instfiles $out/lib/debug \
	$bdir/lib/debug/freetype2*.{dll,lib,a,so,pdb}
    instheaders $out/include \
	$sdir/extern/$FREETYPE2VER/include
    ;;

  # ftgl extern package, but separate dir
  (ftgl)
    instfiles $out/lib/release \
	$bdir/lib/release/ftgl.{dll,lib,a,so}
    instfiles $out/lib/debug \
	$bdir/lib/debug/ftgl*.{dll,lib,a,so,pdb}
    instheaders $out/include \
	$sdir/database/overlay/ftgl/include/*.h
    ;;
  esac
}

#
# Main Execution part
# ------------------------------------------------------------------------

for mp in $pkglist
do
  # Remap meta-packages (mp)
  case $mp in
    (all) pdirs="$all";;
    (extern) pdirs="$extern";;
    (*) pdirs=$mp;;
  esac

  echo "Creating archive for package: $mp"
  zipfile=`echo $outdir/$prefix-$mp$postf.zip |
    tr "ABCDEFGHIJKLMNOPQRSTUVWXYZ" "abcdefghijklmnopqrstuvwxyz"`
  rm -rf $zipfile

  for p in $pdirs
  do
    pkg=$outdir/$p
    if [ ! -d $pkg -o "$force" == "true" ]
    then
      echo "Creating package content: $pkg"
      create_content $p $pkg
    fi

    if [ -d $pkg ]
    then
      b=`basename $builddir`
      d=$outdir
      pushd $d > /dev/null
      $ZIP $zipfile $p
      popd > /dev/null
    fi
  done
done

