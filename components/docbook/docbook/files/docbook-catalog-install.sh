#!/bin/bash

#
# docbook-dtds.spec %post
#

export Version=1.0
export Release=30.1

/usr/bin/xmlcatalog --sgml --noout --add \
	/etc/sgml/sgml-docbook-3.0-${Version}-${Release}.cat \
	/usr/share/sgml/sgml-iso-entities-8879.1986/catalog
/usr/bin/xmlcatalog --sgml --noout --add \
	/etc/sgml/sgml-docbook-3.0-${Version}-${Release}.cat \
	/usr/share/sgml/docbook/sgml-dtd-3.0-${Version}-${Release}/catalog

# DocBook V3.1
/usr/bin/xmlcatalog --sgml --noout --add \
	/etc/sgml/sgml-docbook-3.1-${Version}-${Release}.cat \
	/usr/share/sgml/sgml-iso-entities-8879.1986/catalog
/usr/bin/xmlcatalog --sgml --noout --add \
	/etc/sgml/sgml-docbook-3.1-${Version}-${Release}.cat \
	/usr/share/sgml/docbook/sgml-dtd-3.1-${Version}-${Release}/catalog

# DocBook V4.0
/usr/bin/xmlcatalog --sgml --noout --add \
	/etc/sgml/sgml-docbook-4.0-${Version}-${Release}.cat \
	/usr/share/sgml/sgml-iso-entities-8879.1986/catalog
/usr/bin/xmlcatalog --sgml --noout --add \
	/etc/sgml/sgml-docbook-4.0-${Version}-${Release}.cat \
	/usr/share/sgml/docbook/sgml-dtd-4.0-${Version}-${Release}/catalog

# DocBook V4.1
/usr/bin/xmlcatalog --sgml --noout --add \
	/etc/sgml/sgml-docbook-4.1-${Version}-${Release}.cat \
	/usr/share/sgml/sgml-iso-entities-8879.1986/catalog
/usr/bin/xmlcatalog --sgml --noout --add \
	/etc/sgml/sgml-docbook-4.1-${Version}-${Release}.cat \
	/usr/share/sgml/docbook/sgml-dtd-4.1-${Version}-${Release}/catalog

# DocBook XML V4.1.2
/usr/bin/xmlcatalog --sgml --noout --add \
	/etc/sgml/xml-docbook-4.1.2-${Version}-${Release}.cat \
	/usr/share/sgml/sgml-iso-entities-8879.1986/catalog
/usr/bin/xmlcatalog --sgml --noout --add \
	/etc/sgml/xml-docbook-4.1.2-${Version}-${Release}.cat \
	/usr/share/sgml/docbook/xml-dtd-4.1.2-${Version}-${Release}/catalog

# DocBook V4.2
/usr/bin/xmlcatalog --sgml --noout --add \
	/etc/sgml/sgml-docbook-4.2-${Version}-${Release}.cat \
	/usr/share/sgml/sgml-iso-entities-8879.1986/catalog
/usr/bin/xmlcatalog --sgml --noout --add \
	/etc/sgml/sgml-docbook-4.2-${Version}-${Release}.cat \
	/usr/share/sgml/docbook/sgml-dtd-4.2-${Version}-${Release}/catalog

# DocBook XML V4.2
/usr/bin/xmlcatalog --sgml --noout --add \
	/etc/sgml/xml-docbook-4.2-${Version}-${Release}.cat \
	/usr/share/sgml/sgml-iso-entities-8879.1986/catalog
/usr/bin/xmlcatalog --sgml --noout --add \
	/etc/sgml/xml-docbook-4.2-${Version}-${Release}.cat \
	/usr/share/sgml/docbook/xml-dtd-4.2-${Version}-${Release}/catalog

# DocBook V4.3
/usr/bin/xmlcatalog --sgml --noout --add \
	/etc/sgml/sgml-docbook-4.3-${Version}-${Release}.cat \
	/usr/share/sgml/sgml-iso-entities-8879.1986/catalog
/usr/bin/xmlcatalog --sgml --noout --add \
	/etc/sgml/sgml-docbook-4.3-${Version}-${Release}.cat \
	/usr/share/sgml/docbook/sgml-dtd-4.3-${Version}-${Release}/catalog

# DocBook XML V4.3
/usr/bin/xmlcatalog --sgml --noout --add \
	/etc/sgml/xml-docbook-4.3-${Version}-${Release}.cat \
	/usr/share/sgml/sgml-iso-entities-8879.1986/catalog
/usr/bin/xmlcatalog --sgml --noout --add \
	/etc/sgml/xml-docbook-4.3-${Version}-${Release}.cat \
	/usr/share/sgml/docbook/xml-dtd-4.3-${Version}-${Release}/catalog

# DocBook V4.4
/usr/bin/xmlcatalog --sgml --noout --add \
	/etc/sgml/sgml-docbook-4.4-${Version}-${Release}.cat \
	/usr/share/sgml/sgml-iso-entities-8879.1986/catalog
/usr/bin/xmlcatalog --sgml --noout --add \
	/etc/sgml/sgml-docbook-4.4-${Version}-${Release}.cat \
	/usr/share/sgml/docbook/sgml-dtd-4.4-${Version}-${Release}/catalog

# DocBook XML V4.4
/usr/bin/xmlcatalog --sgml --noout --add \
	/etc/sgml/xml-docbook-4.4-${Version}-${Release}.cat \
	/usr/share/sgml/sgml-iso-entities-8879.1986/catalog
/usr/bin/xmlcatalog --sgml --noout --add \
	/etc/sgml/xml-docbook-4.4-${Version}-${Release}.cat \
	/usr/share/sgml/docbook/xml-dtd-4.4-${Version}-${Release}/catalog

### Note about "added by laca" bits: When preparing subsequent incremental
### updates, make sure only the newest docbook version contains this clause
### for the install script (the uninstall script should remove old file
### when the SMF service is refreshed, e.g. as part of IPS package update).
# DocBook V4.5
/usr/bin/xmlcatalog --sgml --noout --add \
	/etc/sgml/sgml-docbook-4.5-${Version}-${Release}.cat \
	/usr/share/sgml/sgml-iso-entities-8879.1986/catalog
/usr/bin/xmlcatalog --sgml --noout --add \
	/etc/sgml/sgml-docbook-4.5-${Version}-${Release}.cat \
	/usr/share/sgml/docbook/sgml-dtd-4.5-${Version}-${Release}/catalog
# added by laca
test ! -f /etc/sgml/sgml-docbook.cat && \
    ( cd /etc/sgml; \
      ln -s sgml-docbook-4.5-${Version}-${Release}.cat sgml-docbook.cat )

# DocBook XML V4.5
/usr/bin/xmlcatalog --sgml --noout --add \
	/etc/sgml/xml-docbook-4.5-${Version}-${Release}.cat \
	/usr/share/sgml/sgml-iso-entities-8879.1986/catalog
/usr/bin/xmlcatalog --sgml --noout --add \
	/etc/sgml/xml-docbook-4.5-${Version}-${Release}.cat \
	/usr/share/sgml/docbook/xml-dtd-4.5-${Version}-${Release}/catalog
# added by laca
test ! -f /etc/sgml/xml-docbook.cat && \
    ( cd /etc/sgml; \
      ln -s xml-docbook-4.5-${Version}-${Release}.cat xml-docbook.cat )

# The following lines are for the case in which the style sheets
# were installed after another DTD but before this DTD
STYLESHEETS=$(echo /usr/share/sgml/docbook/dsssl-stylesheets-*)
STYLESHEETS=${STYLESHEETS##*/dsssl-stylesheets-}
if [ "$STYLESHEETS" != "*" ]; then
    # DocBook V3.0
    /usr/bin/xmlcatalog --sgml --noout --add \
	/etc/sgml/sgml-docbook-3.0-${Version}-${Release}.cat \
	/usr/share/sgml/openjade/catalog
    /usr/bin/xmlcatalog --sgml --noout --add \
	/etc/sgml/sgml-docbook-3.0-${Version}-${Release}.cat \
	/usr/share/sgml/docbook/dsssl-stylesheets-$STYLESHEETS/catalog

    # DocBook V3.1
    /usr/bin/xmlcatalog --sgml --noout --add \
	/etc/sgml/sgml-docbook-3.1-${Version}-${Release}.cat \
	/usr/share/sgml/openjade/catalog
    /usr/bin/xmlcatalog --sgml --noout --add \
	/etc/sgml/sgml-docbook-3.1-${Version}-${Release}.cat \
	/usr/share/sgml/docbook/dsssl-stylesheets-$STYLESHEETS/catalog

    # DocBook V4.0
    /usr/bin/xmlcatalog --sgml --noout --add \
	/etc/sgml/sgml-docbook-4.0-${Version}-${Release}.cat \
	/usr/share/sgml/openjade/catalog
    /usr/bin/xmlcatalog --sgml --noout --add \
	/etc/sgml/sgml-docbook-4.0-${Version}-${Release}.cat \
	/usr/share/sgml/docbook/dsssl-stylesheets-$STYLESHEETS/catalog

    # DocBook V4.1
    /usr/bin/xmlcatalog --sgml --noout --add \
	/etc/sgml/sgml-docbook-4.1-${Version}-${Release}.cat \
	/usr/share/sgml/openjade/catalog
    /usr/bin/xmlcatalog --sgml --noout --add \
	/etc/sgml/sgml-docbook-4.1-${Version}-${Release}.cat \
	/usr/share/sgml/docbook/dsssl-stylesheets-$STYLESHEETS/catalog

    # DocBook XML V4.1.2
    /usr/bin/xmlcatalog --sgml --noout --add \
	/etc/sgml/xml-docbook-4.1.2-${Version}-${Release}.cat \
	/usr/share/sgml/openjade/catalog
    /usr/bin/xmlcatalog --sgml --noout --add \
	/etc/sgml/xml-docbook-4.1.2-${Version}-${Release}.cat \
	/usr/share/sgml/docbook/dsssl-stylesheets-$STYLESHEETS/catalog

    # DocBook V4.2
    /usr/bin/xmlcatalog --sgml --noout --add \
	/etc/sgml/sgml-docbook-4.2-${Version}-${Release}.cat \
	/usr/share/sgml/openjade/catalog
    /usr/bin/xmlcatalog --sgml --noout --add \
	/etc/sgml/sgml-docbook-4.2-${Version}-${Release}.cat \
	/usr/share/sgml/docbook/dsssl-stylesheets-$STYLESHEETS/catalog

    # DocBook XML V4.2
    /usr/bin/xmlcatalog --sgml --noout --add \
	/etc/sgml/xml-docbook-4.2-${Version}-${Release}.cat \
	/usr/share/sgml/openjade/catalog
    /usr/bin/xmlcatalog --sgml --noout --add \
	/etc/sgml/xml-docbook-4.2-${Version}-${Release}.cat \
	/usr/share/sgml/docbook/dsssl-stylesheets-$STYLESHEETS/catalog

    # DocBook V4.3
    /usr/bin/xmlcatalog --sgml --noout --add \
	/etc/sgml/sgml-docbook-4.3-${Version}-${Release}.cat \
	/usr/share/sgml/openjade/catalog
    /usr/bin/xmlcatalog --sgml --noout --add \
	/etc/sgml/sgml-docbook-4.3-${Version}-${Release}.cat \
	/usr/share/sgml/docbook/dsssl-stylesheets-$STYLESHEETS/catalog

    # DocBook XML V4.3
    /usr/bin/xmlcatalog --sgml --noout --add \
	/etc/sgml/xml-docbook-4.3-${Version}-${Release}.cat \
	/usr/share/sgml/openjade/catalog
    /usr/bin/xmlcatalog --sgml --noout --add \
	/etc/sgml/xml-docbook-4.3-${Version}-${Release}.cat \
	/usr/share/sgml/docbook/dsssl-stylesheets-$STYLESHEETS/catalog

    # DocBook V4.4
    /usr/bin/xmlcatalog --sgml --noout --add \
	/etc/sgml/sgml-docbook-4.4-${Version}-${Release}.cat \
	/usr/share/sgml/openjade/catalog
    /usr/bin/xmlcatalog --sgml --noout --add \
	/etc/sgml/sgml-docbook-4.4-${Version}-${Release}.cat \
	/usr/share/sgml/docbook/dsssl-stylesheets-$STYLESHEETS/catalog

    # DocBook XML V4.4
    /usr/bin/xmlcatalog --sgml --noout --add \
	/etc/sgml/xml-docbook-4.4-${Version}-${Release}.cat \
	/usr/share/sgml/openjade/catalog
    /usr/bin/xmlcatalog --sgml --noout --add \
	/etc/sgml/xml-docbook-4.4-${Version}-${Release}.cat \
	/usr/share/sgml/docbook/dsssl-stylesheets-$STYLESHEETS/catalog

    # DocBook V4.5
    /usr/bin/xmlcatalog --sgml --noout --add \
	/etc/sgml/sgml-docbook-4.5-${Version}-${Release}.cat \
	/usr/share/sgml/openjade/catalog
    /usr/bin/xmlcatalog --sgml --noout --add \
	/etc/sgml/sgml-docbook-4.5-${Version}-${Release}.cat \
	/usr/share/sgml/docbook/dsssl-stylesheets-$STYLESHEETS/catalog

    # DocBook XML V4.5
    /usr/bin/xmlcatalog --sgml --noout --add \
	/etc/sgml/xml-docbook-4.5-${Version}-${Release}.cat \
	/usr/share/sgml/openjade/catalog
    /usr/bin/xmlcatalog --sgml --noout --add \
	/etc/sgml/xml-docbook-4.5-${Version}-${Release}.cat \
	/usr/share/sgml/docbook/dsssl-stylesheets-$STYLESHEETS/catalog
fi

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
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Publishing//EN" \
		"xml-dtd-4.1.2-${Version}-${Release}/ent/iso-pub.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Greek Letters//EN" \
		"xml-dtd-4.1.2-${Version}-${Release}/ent/iso-grk1.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"-//OASIS//ELEMENTS DocBook XML Information Pool V4.1.2//EN" \
		"xml-dtd-4.1.2-${Version}-${Release}/dbpoolx.mod" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Box and Line Drawing//EN" \
		"xml-dtd-4.1.2-${Version}-${Release}/ent/iso-box.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"-//OASIS//DTD DocBook XML V4.1.2//EN" \
		"xml-dtd-4.1.2-${Version}-${Release}/docbookx.dtd" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Greek Symbols//EN" \
		"xml-dtd-4.1.2-${Version}-${Release}/ent/iso-grk3.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Added Math Symbols: Negated Relations//EN" \
		"xml-dtd-4.1.2-${Version}-${Release}/ent/iso-amsn.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Numeric and Special Graphic//EN" \
		"xml-dtd-4.1.2-${Version}-${Release}/ent/iso-num.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"-//OASIS//ENTITIES DocBook XML Character Entities V4.1.2//EN" \
		"xml-dtd-4.1.2-${Version}-${Release}/dbcentx.mod" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Alternative Greek Symbols//EN" \
		"xml-dtd-4.1.2-${Version}-${Release}/ent/iso-grk4.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"-//OASIS//ENTITIES DocBook XML Notations V4.1.2//EN" \
		"xml-dtd-4.1.2-${Version}-${Release}/dbnotnx.mod" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Diacritical Marks//EN" \
		"xml-dtd-4.1.2-${Version}-${Release}/ent/iso-dia.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Monotoniko Greek//EN" \
		"xml-dtd-4.1.2-${Version}-${Release}/ent/iso-grk2.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"-//OASIS//ENTITIES DocBook XML Additional General Entities V4.1.2//EN" \
		"xml-dtd-4.1.2-${Version}-${Release}/dbgenent.mod" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"-//OASIS//ELEMENTS DocBook XML Document Hierarchy V4.1.2//EN" \
		"xml-dtd-4.1.2-${Version}-${Release}/dbhierx.mod" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Added Math Symbols: Arrow Relations//EN" \
		"xml-dtd-4.1.2-${Version}-${Release}/ent/iso-amsa.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Added Math Symbols: Ordinary//EN" \
		"xml-dtd-4.1.2-${Version}-${Release}/ent/iso-amso.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Russian Cyrillic//EN" \
		"xml-dtd-4.1.2-${Version}-${Release}/ent/iso-cyrl.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES General Technical//EN" \
		"xml-dtd-4.1.2-${Version}-${Release}/ent/iso-tech.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Added Math Symbols: Delimiters//EN" \
		"xml-dtd-4.1.2-${Version}-${Release}/ent/iso-amsc.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"-//OASIS//DTD XML Exchange Table Model 19990315//EN" \
		"xml-dtd-4.1.2-${Version}-${Release}/soextblx.dtd" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"-//OASIS//DTD DocBook XML CALS Table Model V4.1.2//EN" \
		"xml-dtd-4.1.2-${Version}-${Release}/calstblx.dtd" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Added Latin 1//EN" \
		"xml-dtd-4.1.2-${Version}-${Release}/ent/iso-lat1.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Added Math Symbols: Binary Operators//EN" \
		"xml-dtd-4.1.2-${Version}-${Release}/ent/iso-amsb.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Added Latin 2//EN" \
		"xml-dtd-4.1.2-${Version}-${Release}/ent/iso-lat2.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Added Math Symbols: Relations//EN" \
		"xml-dtd-4.1.2-${Version}-${Release}/ent/iso-amsr.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Non-Russian Cyrillic//EN" \
		"xml-dtd-4.1.2-${Version}-${Release}/ent/iso-cyr2.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "rewriteSystem" \
		"http://www.oasis-open.org/docbook/xml/4.1.2" \
		"xml-dtd-4.1.2-${Version}-${Release}" $CATALOG
	/usr/bin/xmlcatalog --noout --add "rewriteURI" \
		"http://www.oasis-open.org/docbook/xml/4.1.2" \
		"xml-dtd-4.1.2-${Version}-${Release}" $CATALOG

	# DocBook XML V4.2
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Publishing//EN" \
		"xml-dtd-4.2-${Version}-${Release}/ent/iso-pub.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Greek Letters//EN" \
		"xml-dtd-4.2-${Version}-${Release}/ent/iso-grk1.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"-//OASIS//ELEMENTS DocBook XML Information Pool V4.2//EN" \
		"xml-dtd-4.2-${Version}-${Release}/dbpoolx.mod" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Box and Line Drawing//EN" \
		"xml-dtd-4.2-${Version}-${Release}/ent/iso-box.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"-//OASIS//DTD DocBook XML V4.2//EN" \
		"xml-dtd-4.2-${Version}-${Release}/docbookx.dtd" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Greek Symbols//EN" \
		"xml-dtd-4.2-${Version}-${Release}/ent/iso-grk3.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Added Math Symbols: Negated Relations//EN" \
		"xml-dtd-4.2-${Version}-${Release}/ent/iso-amsn.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Numeric and Special Graphic//EN" \
		"xml-dtd-4.2-${Version}-${Release}/ent/iso-num.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"-//OASIS//ENTITIES DocBook XML Character Entities V4.2//EN" \
		"xml-dtd-4.2-${Version}-${Release}/dbcentx.mod" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Alternative Greek Symbols//EN" \
		"xml-dtd-4.2-${Version}-${Release}/ent/iso-grk4.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"-//OASIS//ENTITIES DocBook XML Notations V4.2//EN" \
		"xml-dtd-4.2-${Version}-${Release}/dbnotnx.mod" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Diacritical Marks//EN" \
		"xml-dtd-4.2-${Version}-${Release}/ent/iso-dia.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Monotoniko Greek//EN" \
		"xml-dtd-4.2-${Version}-${Release}/ent/iso-grk2.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"-//OASIS//ENTITIES DocBook XML Additional General Entities V4.2//EN" \
		"xml-dtd-4.2-${Version}-${Release}/dbgenent.mod" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"-//OASIS//ELEMENTS DocBook XML Document Hierarchy V4.2//EN" \
		"xml-dtd-4.2-${Version}-${Release}/dbhierx.mod" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Added Math Symbols: Arrow Relations//EN" \
		"xml-dtd-4.2-${Version}-${Release}/ent/iso-amsa.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Added Math Symbols: Ordinary//EN" \
		"xml-dtd-4.2-${Version}-${Release}/ent/iso-amso.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Russian Cyrillic//EN" \
		"xml-dtd-4.2-${Version}-${Release}/ent/iso-cyrl.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES General Technical//EN" \
		"xml-dtd-4.2-${Version}-${Release}/ent/iso-tech.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Added Math Symbols: Delimiters//EN" \
		"xml-dtd-4.2-${Version}-${Release}/ent/iso-amsc.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"-//OASIS//DTD XML Exchange Table Model 19990315//EN" \
		"xml-dtd-4.2-${Version}-${Release}/soextblx.dtd" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"-//OASIS//DTD DocBook XML CALS Table Model V4.2//EN" \
		"xml-dtd-4.2-${Version}-${Release}/calstblx.dtd" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Added Latin 1//EN" \
		"xml-dtd-4.2-${Version}-${Release}/ent/iso-lat1.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Added Math Symbols: Binary Operators//EN" \
		"xml-dtd-4.2-${Version}-${Release}/ent/iso-amsb.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Added Latin 2//EN" \
		"xml-dtd-4.2-${Version}-${Release}/ent/iso-lat2.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Added Math Symbols: Relations//EN" \
		"xml-dtd-4.2-${Version}-${Release}/ent/iso-amsr.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Non-Russian Cyrillic//EN" \
		"xml-dtd-4.2-${Version}-${Release}/ent/iso-cyr2.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "rewriteSystem" \
		"http://www.oasis-open.org/docbook/xml/4.2" \
		"xml-dtd-4.2-${Version}-${Release}" $CATALOG
	/usr/bin/xmlcatalog --noout --add "rewriteURI" \
		"http://www.oasis-open.org/docbook/xml/4.2" \
		"xml-dtd-4.2-${Version}-${Release}" $CATALOG

	# DocBook XML V4.3
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Publishing//EN" \
		"xml-dtd-4.3-${Version}-${Release}/ent/iso-pub.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Greek Letters//EN" \
		"xml-dtd-4.3-${Version}-${Release}/ent/iso-grk1.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"-//OASIS//ELEMENTS DocBook XML Information Pool V4.3//EN" \
		"xml-dtd-4.3-${Version}-${Release}/dbpoolx.mod" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Box and Line Drawing//EN" \
		"xml-dtd-4.3-${Version}-${Release}/ent/iso-box.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"-//OASIS//DTD DocBook XML V4.3//EN" \
		"xml-dtd-4.3-${Version}-${Release}/docbookx.dtd" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Greek Symbols//EN" \
		"xml-dtd-4.3-${Version}-${Release}/ent/iso-grk3.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Added Math Symbols: Negated Relations//EN" \
		"xml-dtd-4.3-${Version}-${Release}/ent/iso-amsn.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Numeric and Special Graphic//EN" \
		"xml-dtd-4.3-${Version}-${Release}/ent/iso-num.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"-//OASIS//ENTITIES DocBook XML Character Entities V4.3//EN" \
		"xml-dtd-4.3-${Version}-${Release}/dbcentx.mod" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Alternative Greek Symbols//EN" \
		"xml-dtd-4.3-${Version}-${Release}/ent/iso-grk4.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"-//OASIS//ENTITIES DocBook XML Notations V4.3//EN" \
		"xml-dtd-4.3-${Version}-${Release}/dbnotnx.mod" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Diacritical Marks//EN" \
		"xml-dtd-4.3-${Version}-${Release}/ent/iso-dia.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Monotoniko Greek//EN" \
		"xml-dtd-4.3-${Version}-${Release}/ent/iso-grk2.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"-//OASIS//ENTITIES DocBook XML Additional General Entities V4.3//EN" \
		"xml-dtd-4.3-${Version}-${Release}/dbgenent.mod" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"-//OASIS//ELEMENTS DocBook XML Document Hierarchy V4.3//EN" \
		"xml-dtd-4.3-${Version}-${Release}/dbhierx.mod" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Added Math Symbols: Arrow Relations//EN" \
		"xml-dtd-4.3-${Version}-${Release}/ent/iso-amsa.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Added Math Symbols: Ordinary//EN" \
		"xml-dtd-4.3-${Version}-${Release}/ent/iso-amso.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Russian Cyrillic//EN" \
		"xml-dtd-4.3-${Version}-${Release}/ent/iso-cyrl.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES General Technical//EN" \
		"xml-dtd-4.3-${Version}-${Release}/ent/iso-tech.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Added Math Symbols: Delimiters//EN" \
		"xml-dtd-4.3-${Version}-${Release}/ent/iso-amsc.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"-//OASIS//DTD XML Exchange Table Model 19990315//EN" \
		"xml-dtd-4.3-${Version}-${Release}/soextblx.dtd" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"-//OASIS//DTD DocBook XML CALS Table Model V4.3//EN" \
		"xml-dtd-4.3-${Version}-${Release}/calstblx.dtd" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Added Latin 1//EN" \
		"xml-dtd-4.3-${Version}-${Release}/ent/iso-lat1.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Added Math Symbols: Binary Operators//EN" \
		"xml-dtd-4.3-${Version}-${Release}/ent/iso-amsb.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Added Latin 2//EN" \
		"xml-dtd-4.3-${Version}-${Release}/ent/iso-lat2.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Added Math Symbols: Relations//EN" \
		"xml-dtd-4.3-${Version}-${Release}/ent/iso-amsr.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Non-Russian Cyrillic//EN" \
		"xml-dtd-4.3-${Version}-${Release}/ent/iso-cyr2.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "rewriteSystem" \
		"http://www.oasis-open.org/docbook/xml/4.3" \
		"xml-dtd-4.3-${Version}-${Release}" $CATALOG
	/usr/bin/xmlcatalog --noout --add "rewriteURI" \
		"http://www.oasis-open.org/docbook/xml/4.3" \
		"xml-dtd-4.3-${Version}-${Release}" $CATALOG

	# DocBook XML V4.4
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Publishing//EN" \
		"xml-dtd-4.4-${Version}-${Release}/ent/iso-pub.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Greek Letters//EN" \
		"xml-dtd-4.4-${Version}-${Release}/ent/iso-grk1.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"-//OASIS//ELEMENTS DocBook XML Information Pool V4.4//EN" \
		"xml-dtd-4.4-${Version}-${Release}/dbpoolx.mod" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Box and Line Drawing//EN" \
		"xml-dtd-4.4-${Version}-${Release}/ent/iso-box.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"-//OASIS//DTD DocBook XML V4.4//EN" \
		"xml-dtd-4.4-${Version}-${Release}/docbookx.dtd" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Greek Symbols//EN" \
		"xml-dtd-4.4-${Version}-${Release}/ent/iso-grk3.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Added Math Symbols: Negated Relations//EN" \
		"xml-dtd-4.4-${Version}-${Release}/ent/iso-amsn.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Numeric and Special Graphic//EN" \
		"xml-dtd-4.4-${Version}-${Release}/ent/iso-num.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"-//OASIS//ENTITIES DocBook XML Character Entities V4.4//EN" \
		"xml-dtd-4.4-${Version}-${Release}/dbcentx.mod" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Alternative Greek Symbols//EN" \
		"xml-dtd-4.4-${Version}-${Release}/ent/iso-grk4.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"-//OASIS//ENTITIES DocBook XML Notations V4.4//EN" \
		"xml-dtd-4.4-${Version}-${Release}/dbnotnx.mod" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Diacritical Marks//EN" \
		"xml-dtd-4.4-${Version}-${Release}/ent/iso-dia.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Monotoniko Greek//EN" \
		"xml-dtd-4.4-${Version}-${Release}/ent/iso-grk2.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"-//OASIS//ENTITIES DocBook XML Additional General Entities V4.4//EN" \
		"xml-dtd-4.4-${Version}-${Release}/dbgenent.mod" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"-//OASIS//ELEMENTS DocBook XML Document Hierarchy V4.4//EN" \
		"xml-dtd-4.4-${Version}-${Release}/dbhierx.mod" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Added Math Symbols: Arrow Relations//EN" \
		"xml-dtd-4.4-${Version}-${Release}/ent/iso-amsa.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Added Math Symbols: Ordinary//EN" \
		"xml-dtd-4.4-${Version}-${Release}/ent/iso-amso.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Russian Cyrillic//EN" \
		"xml-dtd-4.4-${Version}-${Release}/ent/iso-cyrl.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES General Technical//EN" \
		"xml-dtd-4.4-${Version}-${Release}/ent/iso-tech.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Added Math Symbols: Delimiters//EN" \
		"xml-dtd-4.4-${Version}-${Release}/ent/iso-amsc.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"-//OASIS//DTD XML Exchange Table Model 19990315//EN" \
		"xml-dtd-4.4-${Version}-${Release}/soextblx.dtd" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"-//OASIS//DTD DocBook XML CALS Table Model V4.4//EN" \
		"xml-dtd-4.4-${Version}-${Release}/calstblx.dtd" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Added Latin 1//EN" \
		"xml-dtd-4.4-${Version}-${Release}/ent/iso-lat1.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Added Math Symbols: Binary Operators//EN" \
		"xml-dtd-4.4-${Version}-${Release}/ent/iso-amsb.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Added Latin 2//EN" \
		"xml-dtd-4.4-${Version}-${Release}/ent/iso-lat2.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Added Math Symbols: Relations//EN" \
		"xml-dtd-4.4-${Version}-${Release}/ent/iso-amsr.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Non-Russian Cyrillic//EN" \
		"xml-dtd-4.4-${Version}-${Release}/ent/iso-cyr2.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "rewriteSystem" \
		"http://www.oasis-open.org/docbook/xml/4.4" \
		"xml-dtd-4.4-${Version}-${Release}" $CATALOG
	/usr/bin/xmlcatalog --noout --add "rewriteURI" \
		"http://www.oasis-open.org/docbook/xml/4.4" \
		"xml-dtd-4.4-${Version}-${Release}" $CATALOG

	# DocBook XML V4.5
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Publishing//EN" \
		"xml-dtd-4.5-${Version}-${Release}/ent/iso-pub.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Greek Letters//EN" \
		"xml-dtd-4.5-${Version}-${Release}/ent/iso-grk1.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"-//OASIS//ELEMENTS DocBook XML Information Pool V4.5//EN" \
		"xml-dtd-4.5-${Version}-${Release}/dbpoolx.mod" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Box and Line Drawing//EN" \
		"xml-dtd-4.5-${Version}-${Release}/ent/iso-box.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"-//OASIS//DTD DocBook XML V4.5//EN" \
		"xml-dtd-4.5-${Version}-${Release}/docbookx.dtd" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Greek Symbols//EN" \
		"xml-dtd-4.5-${Version}-${Release}/ent/iso-grk3.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Added Math Symbols: Negated Relations//EN" \
		"xml-dtd-4.5-${Version}-${Release}/ent/iso-amsn.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Numeric and Special Graphic//EN" \
		"xml-dtd-4.5-${Version}-${Release}/ent/iso-num.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"-//OASIS//ENTITIES DocBook XML Character Entities V4.5//EN" \
		"xml-dtd-4.5-${Version}-${Release}/dbcentx.mod" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Alternative Greek Symbols//EN" \
		"xml-dtd-4.5-${Version}-${Release}/ent/iso-grk4.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"-//OASIS//ENTITIES DocBook XML Notations V4.5//EN" \
		"xml-dtd-4.5-${Version}-${Release}/dbnotnx.mod" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Diacritical Marks//EN" \
		"xml-dtd-4.5-${Version}-${Release}/ent/iso-dia.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Monotoniko Greek//EN" \
		"xml-dtd-4.5-${Version}-${Release}/ent/iso-grk2.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"-//OASIS//ENTITIES DocBook XML Additional General Entities V4.5//EN" \
		"xml-dtd-4.5-${Version}-${Release}/dbgenent.mod" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"-//OASIS//ELEMENTS DocBook XML Document Hierarchy V4.5//EN" \
		"xml-dtd-4.5-${Version}-${Release}/dbhierx.mod" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Added Math Symbols: Arrow Relations//EN" \
		"xml-dtd-4.5-${Version}-${Release}/ent/iso-amsa.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Added Math Symbols: Ordinary//EN" \
		"xml-dtd-4.5-${Version}-${Release}/ent/iso-amso.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Russian Cyrillic//EN" \
		"xml-dtd-4.5-${Version}-${Release}/ent/iso-cyrl.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES General Technical//EN" \
		"xml-dtd-4.5-${Version}-${Release}/ent/iso-tech.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Added Math Symbols: Delimiters//EN" \
		"xml-dtd-4.5-${Version}-${Release}/ent/iso-amsc.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"-//OASIS//DTD XML Exchange Table Model 19990315//EN" \
		"xml-dtd-4.5-${Version}-${Release}/soextblx.dtd" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"-//OASIS//DTD DocBook XML CALS Table Model V4.5//EN" \
		"xml-dtd-4.5-${Version}-${Release}/calstblx.dtd" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Added Latin 1//EN" \
		"xml-dtd-4.5-${Version}-${Release}/ent/iso-lat1.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Added Math Symbols: Binary Operators//EN" \
		"xml-dtd-4.5-${Version}-${Release}/ent/iso-amsb.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Added Latin 2//EN" \
		"xml-dtd-4.5-${Version}-${Release}/ent/iso-lat2.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Added Math Symbols: Relations//EN" \
		"xml-dtd-4.5-${Version}-${Release}/ent/iso-amsr.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "public" \
		"ISO 8879:1986//ENTITIES Non-Russian Cyrillic//EN" \
		"xml-dtd-4.5-${Version}-${Release}/ent/iso-cyr2.ent" $CATALOG
	/usr/bin/xmlcatalog --noout --add "rewriteSystem" \
		"http://www.oasis-open.org/docbook/xml/4.5" \
		"xml-dtd-4.5-${Version}-${Release}" $CATALOG
	/usr/bin/xmlcatalog --noout --add "rewriteURI" \
		"http://www.oasis-open.org/docbook/xml/4.5" \
		"xml-dtd-4.5-${Version}-${Release}" $CATALOG
fi

# Finally, make sure everything in /etc/sgml is readable!
/bin/chmod a+r /etc/sgml/*

#
# docbook-style-dsssl.spec %post
#

Version=1.79
Release=1

rel=$(echo /etc/sgml/sgml-docbook-3.0-*.cat)
rel=${rel##*-}
rel=${rel%.cat}
for centralized in /etc/sgml/*-docbook-*.cat
do
	/usr/bin/install-catalog --remove $centralized \
		/usr/share/sgml/docbook/dsssl-stylesheets-*/catalog \
		>/dev/null 2>/dev/null
done

for centralized in /etc/sgml/*-docbook-*$rel.cat
do
	/usr/bin/install-catalog --add $centralized \
		/usr/share/sgml/openjade/catalog \
		> /dev/null 2>/dev/null
	/usr/bin/install-catalog --add $centralized \
		/usr/share/sgml/docbook/dsssl-stylesheets-${Version}/catalog \
		> /dev/null 2>/dev/null
done

#
# docbook-style-xsl.spec %post
#

Version=1.78.1
Release=5.1

CATALOG=/etc/xml/catalog
/usr/bin/xmlcatalog --noout --add "rewriteSystem" \
 "http://docbook.sourceforge.net/release/xsl/${Version}" \
 "file:///usr/share/sgml/docbook/xsl-stylesheets-${Version}-${Release}" $CATALOG
/usr/bin/xmlcatalog --noout --add "rewriteURI" \
 "http://docbook.sourceforge.net/release/xsl/${Version}" \
 "file:///usr/share/sgml/docbook/xsl-stylesheets-${Version}-${Release}" $CATALOG
/usr/bin/xmlcatalog --noout --add "rewriteSystem" \
 "http://docbook.sourceforge.net/release/xsl/current" \
 "file:///usr/share/sgml/docbook/xsl-stylesheets-${Version}-${Release}" $CATALOG
/usr/bin/xmlcatalog --noout --add "rewriteURI" \
 "http://docbook.sourceforge.net/release/xsl/current" \
 "file:///usr/share/sgml/docbook/xsl-stylesheets-${Version}-${Release}" $CATALOG
