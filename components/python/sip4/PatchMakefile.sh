#!/bin/sh
sed -i 's/\$(LINK)/\/usr\/bin\/amd64\/ld/g' $1
