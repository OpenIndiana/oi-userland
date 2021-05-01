#!/bin/sh

#
# script to replace the subversion version by the string $(SVN_REV)
#

svn_rev=$1
perl -p -e "s/$svn_rev/\\$\(SVN_REV\)/;"

