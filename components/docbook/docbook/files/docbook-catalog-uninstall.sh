#!/bin/bash

#
# docbook-dtds.spec %preun
#

Version=1.0
Release=30.1

##
## SGML catalog
##

# Update the centralized catalog corresponding to this version of the DTD
# DocBook V3.0
/usr/bin/xmlcatalog --sgml --noout --del /etc/sgml/catalog \
	/etc/sgml/sgml-docbook-3.0-${Version}-${Release}.cat
rm -f /etc/sgml/sgml-docbook-3.0-${Version}-${Release}.cat

# DocBook V3.1
/usr/bin/xmlcatalog --sgml --noout --del /etc/sgml/catalog \
	/etc/sgml/sgml-docbook-3.1-${Version}-${Release}.cat
rm -f /etc/sgml/sgml-docbook-3.1-${Version}-${Release}.cat

# DocBook V4.0
/usr/bin/xmlcatalog --sgml --noout --del /etc/sgml/catalog \
	/etc/sgml/sgml-docbook-4.0-${Version}-${Release}.cat
rm -f /etc/sgml/sgml-docbook-4.0-${Version}-${Release}.cat

# DocBook V4.1
/usr/bin/xmlcatalog --sgml --noout --del /etc/sgml/catalog \
	/etc/sgml/sgml-docbook-4.1-${Version}-${Release}.cat
rm -f /etc/sgml/sgml-docbook-4.1-${Version}-${Release}.cat

# DocBook XML V4.1.2
/usr/bin/xmlcatalog --sgml --noout --del /etc/sgml/catalog \
	/etc/sgml/xml-docbook-4.1.2-${Version}-${Release}.cat
rm -f /etc/sgml/xml-docbook-4.1.2-${Version}-${Release}.cat

# DocBook V4.2
/usr/bin/xmlcatalog --sgml --noout --del /etc/sgml/catalog \
	/etc/sgml/sgml-docbook-4.2-${Version}-${Release}.cat
rm -f /etc/sgml/sgml-docbook-4.2-${Version}-${Release}.cat

# DocBook XML V4.2
/usr/bin/xmlcatalog --sgml --noout --del /etc/sgml/catalog \
	/etc/sgml/xml-docbook-4.2-${Version}-${Release}.cat
rm -f /etc/sgml/xml-docbook-4.2-${Version}-${Release}.cat

# DocBook V4.3
/usr/bin/xmlcatalog --sgml --noout --del /etc/sgml/catalog \
	/etc/sgml/sgml-docbook-4.3-${Version}-${Release}.cat
rm -f /etc/sgml/sgml-docbook-4.3-${Version}-${Release}.cat

# DocBook XML V4.3
/usr/bin/xmlcatalog --sgml --noout --del /etc/sgml/catalog \
	/etc/sgml/xml-docbook-4.3-${Version}-${Release}.cat
rm -f /etc/sgml/xml-docbook-4.3-${Version}-${Release}.cat

### Note about "added by laca" bits: Pedantically, these checks and removals
### should be above for every version too. However, the docbook-4.4 version
### of the package was released a few years ago, perhaps before OI/Hipster -
### so in practice we do not care about updating docbook from older versions.
### However, subsequent incremental updates should all contain this clause.
# DocBook V4.4
/usr/bin/xmlcatalog --sgml --noout --del /etc/sgml/catalog \
	/etc/sgml/sgml-docbook-4.4-${Version}-${Release}.cat
# added by laca:
cmp -s /etc/sgml/sgml-docbook.cat /etc/sgml/sgml-docbook-4.4-${Version}-${Release}.cat && \
    rm -f /etc/sgml/sgml-docbook.cat
rm -f /etc/sgml/sgml-docbook-4.4-${Version}-${Release}.cat

# DocBook XML V4.4
/usr/bin/xmlcatalog --sgml --noout --del /etc/sgml/catalog \
	/etc/sgml/xml-docbook-4.4-${Version}-${Release}.cat
# added by laca:
cmp -s /etc/sgml/xml-docbook.cat /etc/sgml/xml-docbook-4.4-${Version}-${Release}.cat && \
    rm -f /etc/sgml/xml-docbook.cat
rm -f /etc/sgml/xml-docbook-4.4-${Version}-${Release}.cat

# DocBook V4.5
/usr/bin/xmlcatalog --sgml --noout --del /etc/sgml/catalog \
	/etc/sgml/sgml-docbook-4.5-${Version}-${Release}.cat
# added by laca:
cmp -s /etc/sgml/sgml-docbook.cat /etc/sgml/sgml-docbook-4.5-${Version}-${Release}.cat && \
    rm -f /etc/sgml/sgml-docbook.cat
rm -f /etc/sgml/sgml-docbook-4.5-${Version}-${Release}.cat

# DocBook XML V4.5
/usr/bin/xmlcatalog --sgml --noout --del /etc/sgml/catalog \
	/etc/sgml/xml-docbook-4.5-${Version}-${Release}.cat
# added by laca:
cmp -s /etc/sgml/xml-docbook.cat /etc/sgml/xml-docbook-4.5-${Version}-${Release}.cat && \
    rm -f /etc/sgml/xml-docbook.cat
rm -f /etc/sgml/xml-docbook-4.5-${Version}-${Release}.cat

# Fix up SGML super catalog so that there isn't an XML DTD before an
# SGML one.  We need to do this (*sigh*) because xmlcatalog messes up
# the order of the lines, and SGML tools don't like to see XML things
# they aren't expecting.
CATALOG=/etc/sgml/catalog
SGML=$(cat -n ${CATALOG} | grep sgml-docbook | head -1 | (read n line;echo $n))
XML=$(cat -n ${CATALOG} | grep xml-docbook | head -1 | (read n line; echo $n))
# Do they need switching around?
if [ -n "${XML}" ] && [ -n "${SGML}" ] && [ "${XML}" -lt "${SGML}" ]
then
  # Switch those two lines around.
  XML=$((XML - 1))
  SGML=$((SGML - 1))
  perl -e "@_=<>;@_[$XML, $SGML]=@_[$SGML, $XML];print @_" \
    ${CATALOG} > ${CATALOG}.rpmtmp
  mv -f ${CATALOG}.rpmtmp ${CATALOG}
fi

##
## XML catalog
##

CATALOG=/etc/xml/docbook-xmlcatalog

if [ -w $CATALOG ]
then
	# DocBook XML V4.1.2
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.1.2-${Version}-${Release}/ent/iso-pub.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.1.2-${Version}-${Release}/ent/iso-grk1.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.1.2-${Version}-${Release}/dbpoolx.mod" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.1.2-${Version}-${Release}/ent/iso-box.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.1.2-${Version}-${Release}/docbookx.dtd" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.1.2-${Version}-${Release}/ent/iso-grk3.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.1.2-${Version}-${Release}/ent/iso-amsn.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.1.2-${Version}-${Release}/ent/iso-num.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.1.2-${Version}-${Release}/dbcentx.mod" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.1.2-${Version}-${Release}/ent/iso-grk4.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.1.2-${Version}-${Release}/dbnotnx.mod" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.1.2-${Version}-${Release}/ent/iso-dia.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.1.2-${Version}-${Release}/ent/iso-grk2.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.1.2-${Version}-${Release}/dbgenent.mod" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.1.2-${Version}-${Release}/dbhierx.mod" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.1.2-${Version}-${Release}/ent/iso-amsa.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.1.2-${Version}-${Release}/ent/iso-amso.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.1.2-${Version}-${Release}/ent/iso-cyrl.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.1.2-${Version}-${Release}/ent/iso-tech.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.1.2-${Version}-${Release}/ent/iso-amsc.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.1.2-${Version}-${Release}/soextblx.dtd" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.1.2-${Version}-${Release}/calstblx.dtd" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.1.2-${Version}-${Release}/ent/iso-lat1.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.1.2-${Version}-${Release}/ent/iso-amsb.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.1.2-${Version}-${Release}/ent/iso-lat2.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.1.2-${Version}-${Release}/ent/iso-amsr.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.1.2-${Version}-${Release}/ent/iso-cyr2.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.1.2-${Version}-${Release}" $CATALOG

	# DocBook XML V4.2
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.2-${Version}-${Release}/ent/iso-pub.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.2-${Version}-${Release}/ent/iso-grk1.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.2-${Version}-${Release}/dbpoolx.mod" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.2-${Version}-${Release}/ent/iso-box.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.2-${Version}-${Release}/docbookx.dtd" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.2-${Version}-${Release}/ent/iso-grk3.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.2-${Version}-${Release}/ent/iso-amsn.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.2-${Version}-${Release}/ent/iso-num.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.2-${Version}-${Release}/dbcentx.mod" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.2-${Version}-${Release}/ent/iso-grk4.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.2-${Version}-${Release}/dbnotnx.mod" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.2-${Version}-${Release}/ent/iso-dia.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.2-${Version}-${Release}/ent/iso-grk2.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.2-${Version}-${Release}/dbgenent.mod" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.2-${Version}-${Release}/dbhierx.mod" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.2-${Version}-${Release}/ent/iso-amsa.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.2-${Version}-${Release}/ent/iso-amso.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.2-${Version}-${Release}/ent/iso-cyrl.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.2-${Version}-${Release}/ent/iso-tech.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.2-${Version}-${Release}/ent/iso-amsc.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.2-${Version}-${Release}/soextblx.dtd" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.2-${Version}-${Release}/calstblx.dtd" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.2-${Version}-${Release}/ent/iso-lat1.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.2-${Version}-${Release}/ent/iso-amsb.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.2-${Version}-${Release}/ent/iso-lat2.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.2-${Version}-${Release}/ent/iso-amsr.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.2-${Version}-${Release}/ent/iso-cyr2.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.2-${Version}-${Release}" $CATALOG

	# DocBook XML V4.3
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.3-${Version}-${Release}/ent/iso-pub.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.3-${Version}-${Release}/ent/iso-grk1.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.3-${Version}-${Release}/dbpoolx.mod" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.3-${Version}-${Release}/ent/iso-box.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.3-${Version}-${Release}/docbookx.dtd" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.3-${Version}-${Release}/ent/iso-grk3.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.3-${Version}-${Release}/ent/iso-amsn.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.3-${Version}-${Release}/ent/iso-num.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.3-${Version}-${Release}/dbcentx.mod" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.3-${Version}-${Release}/ent/iso-grk4.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.3-${Version}-${Release}/dbnotnx.mod" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.3-${Version}-${Release}/ent/iso-dia.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.3-${Version}-${Release}/ent/iso-grk2.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.3-${Version}-${Release}/dbgenent.mod" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.3-${Version}-${Release}/dbhierx.mod" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.3-${Version}-${Release}/ent/iso-amsa.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.3-${Version}-${Release}/ent/iso-amso.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.3-${Version}-${Release}/ent/iso-cyrl.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.3-${Version}-${Release}/ent/iso-tech.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.3-${Version}-${Release}/ent/iso-amsc.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.3-${Version}-${Release}/soextblx.dtd" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.3-${Version}-${Release}/calstblx.dtd" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.3-${Version}-${Release}/ent/iso-lat1.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.3-${Version}-${Release}/ent/iso-amsb.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.3-${Version}-${Release}/ent/iso-lat2.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.3-${Version}-${Release}/ent/iso-amsr.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.3-${Version}-${Release}/ent/iso-cyr2.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.3-${Version}-${Release}" $CATALOG

	# DocBook XML V4.4
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.4-${Version}-${Release}/ent/iso-pub.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.4-${Version}-${Release}/ent/iso-grk1.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.4-${Version}-${Release}/dbpoolx.mod" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.4-${Version}-${Release}/ent/iso-box.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.4-${Version}-${Release}/docbookx.dtd" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.4-${Version}-${Release}/ent/iso-grk3.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.4-${Version}-${Release}/ent/iso-amsn.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.4-${Version}-${Release}/ent/iso-num.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.4-${Version}-${Release}/dbcentx.mod" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.4-${Version}-${Release}/ent/iso-grk4.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.4-${Version}-${Release}/dbnotnx.mod" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.4-${Version}-${Release}/ent/iso-dia.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.4-${Version}-${Release}/ent/iso-grk2.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.4-${Version}-${Release}/dbgenent.mod" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.4-${Version}-${Release}/dbhierx.mod" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.4-${Version}-${Release}/ent/iso-amsa.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.4-${Version}-${Release}/ent/iso-amso.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.4-${Version}-${Release}/ent/iso-cyrl.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.4-${Version}-${Release}/ent/iso-tech.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.4-${Version}-${Release}/ent/iso-amsc.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.4-${Version}-${Release}/soextblx.dtd" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.4-${Version}-${Release}/calstblx.dtd" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.4-${Version}-${Release}/ent/iso-lat1.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.4-${Version}-${Release}/ent/iso-amsb.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.4-${Version}-${Release}/ent/iso-lat2.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.4-${Version}-${Release}/ent/iso-amsr.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.4-${Version}-${Release}/ent/iso-cyr2.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.4-${Version}-${Release}" $CATALOG

	# DocBook XML V4.5
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.5-${Version}-${Release}/ent/iso-pub.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.5-${Version}-${Release}/ent/iso-grk1.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.5-${Version}-${Release}/dbpoolx.mod" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.5-${Version}-${Release}/ent/iso-box.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.5-${Version}-${Release}/docbookx.dtd" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.5-${Version}-${Release}/ent/iso-grk3.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.5-${Version}-${Release}/ent/iso-amsn.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.5-${Version}-${Release}/ent/iso-num.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.5-${Version}-${Release}/dbcentx.mod" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.5-${Version}-${Release}/ent/iso-grk4.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.5-${Version}-${Release}/dbnotnx.mod" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.5-${Version}-${Release}/ent/iso-dia.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.5-${Version}-${Release}/ent/iso-grk2.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.5-${Version}-${Release}/dbgenent.mod" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.5-${Version}-${Release}/dbhierx.mod" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.5-${Version}-${Release}/ent/iso-amsa.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.5-${Version}-${Release}/ent/iso-amso.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.5-${Version}-${Release}/ent/iso-cyrl.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.5-${Version}-${Release}/ent/iso-tech.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.5-${Version}-${Release}/ent/iso-amsc.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.5-${Version}-${Release}/soextblx.dtd" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.5-${Version}-${Release}/calstblx.dtd" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.5-${Version}-${Release}/ent/iso-lat1.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.5-${Version}-${Release}/ent/iso-amsb.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.5-${Version}-${Release}/ent/iso-lat2.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.5-${Version}-${Release}/ent/iso-amsr.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.5-${Version}-${Release}/ent/iso-cyr2.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --del \
		"xml-dtd-4.5-${Version}-${Release}" $CATALOG
fi

#
# docbook-style-dsssl.spec %preun
#

Version=1.79
Release=1

for centralized in /etc/sgml/*-docbook-*.cat
  do   /usr/bin/install-catalog --remove $centralized /usr/share/sgml/openjade/catalog > /dev/null 2>/dev/null
    /usr/bin/install-catalog --remove $centralized /usr/share/sgml/docbook/dsssl-stylesheets-${Version}/catalog > /dev/null 2>/dev/null
done

#
# docbook-style-xsl.spec %postun
#

Version=1.69.1
Release=5.1

CATALOG=/etc/xml/catalog
/usr/bin/xmlcatalog --noout --del \
 "file:///usr/share/sgml/docbook/xsl-stylesheets-${Version}-${Release}" $CATALOG

