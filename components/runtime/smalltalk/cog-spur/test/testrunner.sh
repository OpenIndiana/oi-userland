#!/bin/sh

BITS=$1
COMPONENT_DIR=$2
BUILD_DIR=$3
TEST_TARGET=$4

LOGFILE=testrunner-log.$BITS

# the tests could be ran after pkg install as:
#       inisqueak -n;squeak squeak.image testrunner.st
# or interactively simply by opening a Squeak image and going to TestRunner

# however here we want to do this on the newly built 64bit VM
# so we start squeak from the BUILD_DIR directory
# we only test the 64bit VM because inisqueak downloads a 64bit image
# in the future we could improve inisqueak to also download the 32bit image

# WARNING HACK : fake 32bit results because we don't want to run 32bit test
case $BITS in
 32) cat $COMPONENT_DIR/test/results-all.master ;exit 0;;
 64) ;;
  *) echo "Unknown BITS $BITS";exit 1;;
esac

# make sure that the newly built VM loads plugins fro the build dir
# SQUEAK_PLUGINS=$PLUGIN_DIR
# export SQUEAK_PLUGINS

# download squeak.image to current directory
$COMPONENT_DIR/inisqueak5c -n > $LOGFILE 2>&1

# start squeak binary from the build dir
$BUILD_DIR/squeak squeak.image $COMPONENT_DIR/test/testrunner.st > $LOGFILE 2>&1

# testrunner.st saves output in a file , dump that file as output
cat results-64.vm

