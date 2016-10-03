#!/usr/bin/bash

#
# docbook-style-xsl %post
#
# cleanup catalog from previous release
/usr/bin/xmlcatalog -v --noout --del "http://docbook.sourceforge.net/release/xsl/1.69.1" /etc/xml/catalog

export version=1.75.2

CATALOG=/etc/xml/catalog

xmlcatalog --noout --add "rewriteSystem" \
 "http://docbook.sourceforge.net/release/xsl/${version}" \
 "file:///usr/share/sgml/docbook/xsl-stylesheets-${version}" $CATALOG
xmlcatalog --noout --add "rewriteURI" \
 "http://docbook.sourceforge.net/release/xsl/${version}" \
 "file:///usr/share/sgml/docbook/xsl-stylesheets-${version}" $CATALOG
xmlcatalog --noout --add "rewriteSystem" \
 "http://docbook.sourceforge.net/release/xsl/current" \
 "file:///usr/share/sgml/docbook/xsl-stylesheets-${version}" $CATALOG
xmlcatalog --noout --add "rewriteURI" \
 "http://docbook.sourceforge.net/release/xsl/current" \
 "file:///usr/share/sgml/docbook/xsl-stylesheets-${version}" $CATALOG
