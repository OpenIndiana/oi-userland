#!/bin/bash

#
# docbook-style-dsssl.spec %preun
#

version=1.79

for centralized in /etc/sgml/*-docbook-*.cat
  do   
    /usr/bin/install-catalog --remove $centralized /usr/share/sgml/docbook/dsssl-stylesheets-${version}/catalog > /dev/null 2>/dev/null
done
