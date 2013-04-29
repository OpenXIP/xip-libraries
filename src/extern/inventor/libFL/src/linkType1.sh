#! /bin/sh -e

system=`uname -s`

echo "System:" $system

dps=/usr/lib/DPS/outline/base

if [ $system == "Darwin" ]; then
	type1=/usr/X11/lib/X11/fonts/Type1
else
	type1=/usr/lib/X11/fonts/Type1
fi

if [ ! -d dps ]; then
  echo "dps does not exist; create? (y=yes, n=no)"
  read reply
  if [ $reply == "y" ]; then
    mkdir -p dps
  else
    exit
  fi
fi

for i in $type1/*.pfa; do
  out=dps`egrep ^/FontName $i | cut -d' ' -f2`
  if [ ! -e $out ]; then
    ln -s $i $out
  fi
done
