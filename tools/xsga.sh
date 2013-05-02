#!/bin/sh

# XIP Scene Graph Analyser (xsga)
#
# Authors: Patric Ljung, patric.ljung@siemens.com
# Copyright (c), 2008, Siemens Corporate Research
#
# ========================================================================
#
# This tool processes and analyze a Scene graph (.xip file) and outputs
# a simplified version that more easily can be compared and analyzed.
#
# Source XIP file is given as argument 1. The basename is used as base
# for the output name in the current directory.
#
# base-obj.txt           Contains all the nodes and engines in order
# base-conns.txt         Contains all the field connections
# base-bwdconns.txt      Contains all the backwards connections
#
#
# The main work is done by an AWK script xsga.awk
# 
# ========================================================================

tooldir=`dirname "$0"`

src=$1

base=`basename $src | sed -e 's/\.xip//g'`

rm -f $base-*.{log,txt}

awk -f $tooldir/xsga.awk -v outnamebase=$base $src > $base-obj.txt
