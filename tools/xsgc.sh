#!/bin/sh

# XIP Scene Graph Comparison (xsgc)
#
# Authors: Patric Ljung, patric.ljung@siemens.com
# Copyright (c), 2008, Siemens Corporate Research
#
# ========================================================================
#
# This tool compares two Scene graphs (.xip files) and outputs simplified
# versions and files with all the connections and backwards connections.
#
# Source XIP files are given as arguments 1 and 2. The base name is used
# as base for the output name in the current directory.
#
# base-obj.txt           Contains all the nodes and engines in order
# base-conns.txt         Contains all the field connections
# base-bwdconns.txt      Contains all the backwards connections
#
# abase-bbase-diff.txt
#   Contains the diff between a and b obj files
#
# abase-bbase-conns-diff.txt
#   Contains the diff between connections in a and b
#
# abase-bbase-bwdconns-diff.txt
#   Contains the diff between bwd connections in a and b
#
# The main work is done by an AWK script xsga.awk
# 
# ========================================================================

tooldir=`dirname "$0"`

asrc=$1
bsrc=$2

abase=`basename $asrc | sed -e 's/\.xip//g'`
bbase=`basename $bsrc | sed -e 's/\.xip//g'`

rm -f $abase-*.{log,txt}
rm -f $bbase-*.{log,txt}

awk -f $tooldir/xsga.awk -v outnamebase=$abase $asrc > $abase-obj.txt
awk -f $tooldir/xsga.awk -v outnamebase=$bbase $bsrc > $bbase-obj.txt

diff $abase-obj.txt $bbase-obj.txt > $abase-$bbase-diff.txt
diff $abase-conns.txt $bbase-conns.txt > $abase-$bbase-conns-diff.txt
diff $abase-bwdconns.txt $bbase-bwdconns.txt > $abase-$bbase-bwdconns-diff.txt
