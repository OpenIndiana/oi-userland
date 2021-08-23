#!/bin/sh

#
# script to replace the plugin version by the string $(PLUGIN_REV)
#

svn_rev=$1
perl -p -e "s/$svn_rev/\\$\(PLUGIN_REV\)/;"

