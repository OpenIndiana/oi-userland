#!/bin/bash

#
# docbook-style-xsl.spec %postun
#

export version=1.75.2


# remove entries only on removal of package
if [ "$1" = 0 ]; then
  CATALOG=/etc/xml/catalog
  /usr/bin/xmlcatalog --noout --del \
   "file:///usr/share/sgml/docbook/xsl-stylesheets-${version}" $CATALOG
fi

