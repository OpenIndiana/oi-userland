#!/bin/sh

for f in squeak.p5m squeak-display-X11.p5m squeak-nodisplay.p5m
do
  tools/amd64.pl < $f > $f.out
  mv $f.out $f
done

