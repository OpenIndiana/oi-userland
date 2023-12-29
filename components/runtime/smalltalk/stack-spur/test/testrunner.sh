#!/bin/sh

BITS=$1
COMPONENT_DIR=$2
BUILD_DIR=$3
TEST_TARGET=$4

LOGFILE=testrunner-log.$BITS

# the tests could be ran after pkg install as:
#       inisqueak -n;squeak squeak.image testrunner.st
# or interactively simply by opening a Squeak image and going to TestRunner

# however here we want to do this on the newly built VM
# so we start squeak from the BUILD_DIR directory

# make sure that the newly built VM loads plugins fro the build dir
# SQUEAK_PLUGINS=$PLUGIN_DIR
# export SQUEAK_PLUGINS

# download squeak.image to current directory
# since december 2023 we no longer test/include 32bit binaries
case $BITS in
# 32) $COMPONENT_DIR/inisqueak5 -32 -n > $LOGFILE 2>&1 ;;
 32) ;;
 64) $COMPONENT_DIR/inisqueak5 -n > $LOGFILE 2>&1 ;;
  *) echo "Unknown BITS $BITS";exit 1;;
esac

# start squeak binary from the build dir
$BUILD_DIR/squeak squeak.image $COMPONENT_DIR/test/testrunner.st > $LOGFILE 2>&1

# testrunner.st saves output in a file , dump that file as output
cat results.vm

