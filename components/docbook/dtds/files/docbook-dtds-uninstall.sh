#!/bin/bash

#
# docbook-dtds.spec %postun
#

export version=1.0
export release=51
export version_list="{3,4}.{0,1}-sgml 4.1.2-xml 4.{2,3,4,5}-{sgml,xml}"

catcmd='/usr/bin/xmlcatalog --noout'
xmlcatalog=/usr/share/sgml/docbook/xmlcatalog
entities="
ent/iso-pub.ent
ent/iso-grk1.ent
dbpoolx.mod
ent/iso-box.ent
docbookx.dtd
ent/iso-grk3.ent
ent/iso-amsn.ent
ent/iso-num.ent
dbcentx.mod
ent/iso-grk4.ent
dbnotnx.mod
ent/iso-dia.ent
ent/iso-grk2.ent
dbgenent.mod
dbhierx.mod
ent/iso-amsa.ent
ent/iso-amso.ent
ent/iso-cyr1.ent
ent/iso-tech.ent
ent/iso-amsc.ent
soextblx.dtd
calstblx.dtd
ent/iso-lat1.ent
ent/iso-amsb.ent
ent/iso-lat2.ent
ent/iso-amsr.ent
ent/iso-cyr2.ent
"
eval set ${version_list}
for dir
do
  fmt=${dir#*-} ver=${dir%%-*} vvr=$ver-${version}-${release}
  sgmldir=/usr/share/sgml/docbook/$fmt-dtd-$vvr
  ## SGML catalog
  # Update the centralized catalog corresponding to this version of the DTD
  $catcmd --sgml --del /etc/sgml/catalog /etc/sgml/$fmt-docbook-$vvr.cat
  rm -f /etc/sgml/$fmt-docbook-$vvr.cat
  ## XML catalog
  if [ $fmt = xml -a -w $xmlcatalog ]; then
    for f in $entities; do
      case $ver in 4.[45]) f=${f/-/} ;; esac
      $catcmd --del $sgmldir/$f $xmlcatalog
    done
    $catcmd --del $sgmldir $xmlcatalog
  fi
done

# See the comment attached to this command in the %%post scriptlet.
/usr/gnu/bin/sed -ni '
  /xml-docbook/ H
  /xml-docbook/ !p
  $ {
          g
          s/^\n//p
  }
  ' /etc/sgml/catalog
