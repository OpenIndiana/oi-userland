#!/bin/sh

for f in dtlsqueak.p5m dtlsqueak-display-X11.p5m dtlsqueak-nodisplay.p5m dtlsqueak-ssl.p5m dtlsqueak-vep.p5m
do
  tools/amd64.pl < $f > $f.out
  mv $f.out $f
done

