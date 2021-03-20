#!/bin/sh

for f in squeak-4.p5m squeak-4-display-X11.p5m squeak-4-nodisplay.p5m
do
  tools/amd64.pl < $f > $f.out
  mv $f.out $f
done

