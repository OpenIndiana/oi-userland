#!/bin/sh

# name can be changed to cog-spur or stack-spur for opensmalltalk packages
name=squeak

for f in ${name}.p5m ${name}-display-X11.p5m ${name}-nodisplay.p5m ${name}-ssl.p5m ${name}-vep.p5m
do
  tools/amd64.pl < $f > $f.out
  mv $f.out $f
done

