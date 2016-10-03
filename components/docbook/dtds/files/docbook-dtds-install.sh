#!/usr/bin/bash
#
# docbook-dtds.spec %post
#

# clean up old catalog which were generated during post install

oldfiles=`ls /etc/sgml/*ml-*-30.1.cat`
for oldfile in $oldfiles
do
    echo $oldfile
    if [ -f "$oldfile" ]; then
        /usr/bin/xmlcatalog --sgml --noout --del /etc/sgml/catalog $oldfile
        rm  $oldfile
    fi
done

export version=1.0
export release=51
export version_list="{3,4}.{0,1}-sgml 4.1.2-xml 4.{2,3,4,5}-{sgml,xml}"


catcmd='/usr/bin/xmlcatalog --noout'
xmlcatalog=/usr/share/sgml/docbook/xmlcatalog

## Clean up pre-docbook-dtds mess caused by broken trigger.
for v in 3.0 3.1 4.0 4.1 4.2
do
  if [ -f /etc/sgml/sgml-docbook-$v-${version}-${release}.cat ]
  then
    $catcmd --sgml --del /etc/sgml/sgml-docbook-$v.cat \
      /usr/share/sgml/openjade/catalog 2>/dev/null
  fi
done

# The STYLESHEETS/catalog command is for the case in which the style sheets
# were installed after another DTD but before this DTD
for STYLESHEETS in /usr/share/sgml/docbook/dsssl-stylesheets-*; do : ; done
case $STYLESHEETS in
  *-"*") STYLESHEETS= ;;
esac
eval set ${version_list}
for dir
do
  fmt=${dir#*-} ver=${dir%%-*} vvr=$ver-${version}-${release}
  sgmldir=/usr/share/sgml/docbook/$fmt-dtd-$vvr
  ## SGML catalog
  # Update the centralized catalog corresponding to this version of the DTD
  for cat_dir in /usr/share/sgml/sgml-iso-entities-8879.1986 $sgmldir $STYLESHEETS; do
    $catcmd --sgml --add /etc/sgml/$fmt-docbook-$vvr.cat $cat_dir/catalog
  done
  ## XML catalog
  if [ $fmt = xml -a -w $xmlcatalog ]; then
    while read f desc; do
      case $ver in 4.[45]) f=${f/-/} ;; esac
      $catcmd --add public "$desc" $sgmldir/$f $xmlcatalog
    done <<ENDENT
      ent/iso-pub.ent	ISO 8879:1986//ENTITIES Publishing//EN
      ent/iso-grk1.ent	ISO 8879:1986//ENTITIES Greek Letters//EN
      dbpoolx.mod	-//OASIS//ELEMENTS DocBook XML Information Pool V$ver//EN
      ent/iso-box.ent	ISO 8879:1986//ENTITIES Box and Line Drawing//EN
      docbookx.dtd	-//OASIS//DTD DocBook XML V$ver//EN
      ent/iso-grk3.ent	ISO 8879:1986//ENTITIES Greek Symbols//EN
      ent/iso-amsn.ent	ISO 8879:1986//ENTITIES Added Math Symbols: Negated Relations//EN
      ent/iso-num.ent	ISO 8879:1986//ENTITIES Numeric and Special Graphic//EN
      dbcentx.mod	-//OASIS//ENTITIES DocBook XML Character Entities V$ver//EN
      ent/iso-grk4.ent	ISO 8879:1986//ENTITIES Alternative Greek Symbols//EN
      dbnotnx.mod	-//OASIS//ENTITIES DocBook XML Notations V$ver//EN
      ent/iso-dia.ent	ISO 8879:1986//ENTITIES Diacritical Marks//EN
      ent/iso-grk2.ent	ISO 8879:1986//ENTITIES Monotoniko Greek//EN
      dbgenent.mod	-//OASIS//ENTITIES DocBook XML Additional General Entities V$ver//EN
      dbhierx.mod	-//OASIS//ELEMENTS DocBook XML Document Hierarchy V$ver//EN
      ent/iso-amsa.ent	ISO 8879:1986//ENTITIES Added Math Symbols: Arrow Relations//EN
      ent/iso-amso.ent	ISO 8879:1986//ENTITIES Added Math Symbols: Ordinary//EN
      ent/iso-cyr1.ent	ISO 8879:1986//ENTITIES Russian Cyrillic//EN
      ent/iso-tech.ent	ISO 8879:1986//ENTITIES General Technical//EN
      ent/iso-amsc.ent	ISO 8879:1986//ENTITIES Added Math Symbols: Delimiters//EN
      soextblx.dtd	-//OASIS//DTD XML Exchange Table Model 19990315//EN
      calstblx.dtd	-//OASIS//DTD DocBook XML CALS Table Model V$ver//EN
      ent/iso-lat1.ent	ISO 8879:1986//ENTITIES Added Latin 1//EN
      ent/iso-amsb.ent	ISO 8879:1986//ENTITIES Added Math Symbols: Binary Operators//EN
      ent/iso-lat2.ent	ISO 8879:1986//ENTITIES Added Latin 2//EN
      ent/iso-amsr.ent	ISO 8879:1986//ENTITIES Added Math Symbols: Relations//EN
      ent/iso-cyr2.ent	ISO 8879:1986//ENTITIES Non-Russian Cyrillic//EN
ENDENT
    for f in System URI; do
      $catcmd --add rewrite$f "http://www.oasis-open.org/docbook/xml/$ver" \
	$sgmldir $xmlcatalog
    done
  fi
done

# include openjade catalog into /etc/sgml catalogs.
rel=$(echo /etc/sgml/sgml-docbook-3.0-*.cat)
rel=${rel##*-}

for file in `ls /etc/sgml/*$rel`;
do
    /usr/bin/xmlcatalog --sgml --noout --add $file /usr/share/sgml/openjade/catalog;
done

# Historic versions of this scriptlet contained the following comment:
# <quote>
# Fix up SGML super catalog so that there isn't an XML DTD before an
# SGML one.  We need to do this (*sigh*) because xmlcatalog messes up
# the order of the lines, and SGML tools don't like to see XML things
# they aren't expecting.
# </quote>
# But the code that followed just found the first XML DTD and the first
# SGML DTD, swappinmg these two lines if the XML one preceded.
# But that only ensures that there is an SGML DTD before all XML ones.
# No one complained, so either this was enough, or the buggy SGML tools
# are long dead, or their users do not use bugzilla.
# Anyway, the following code, introduced in 1.0-46, does better: it ensures
# that all XML DTDs are after all SGML ones, by moving them to the end.
/usr/gnu/bin/sed -ni '
  /xml-docbook/ H
  /xml-docbook/ !p
  $ {
          g
          s/^\n//p
  }
  ' /etc/sgml/catalog

# Finally, make sure everything in /etc/sgml is readable!
/bin/chmod a+r /etc/sgml/*
/bin/chgrp bin /etc/sgml/*
