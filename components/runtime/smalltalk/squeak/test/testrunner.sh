#!/bin/sh

BITS=$1
COMPONENT_DIR=$2
BUILD_DIR=$3
TEST_TARGET=$4

LOGFILE=testrunner-log.$BITS

# the tests could be ran after pkg install as:
#       inisqueak -n;squeak squeak.image testrunner.st
# or interactively simply by opening a Squeak image and going to TestRunner

# however here we want to do this on the newly built 32bit VM
# so we start squeak from the BUILD_DIR directory
# we only test the 32bit VM because inisqueak downloads a 32bit image

case $BITS in
 32) echo "Squeak only tested in 64bit.  See OpenSmalltalk for 64bit.";exit 0;;
 64) ;;
  *) echo "Unknown BITS $BITS";exit 1;;
esac

# unlike OpenSmalltalk libtool/configure plugins are not found in build dir
# make sure that the newly built VM loads plugins fro the build dir

for plugin in vm-display-X11 vm-display-null vm-sound-pulse vm-sound-null UUIDPlugin SqueakSSL
do
  SQUEAK_PLUGINS=$SQUEAK_PLUGINS:$BUILD_DIR/$plugin
# LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$BUILD_DIR/$plugin
done
#echo "Setting LD_LIBRARY_PATH to $LD_LIBRARY_PATH" >> $LOGFILE
#export LD_LIBRARY_PATH
echo "Setting SQUEAK_PLUGINS to $SQUEAK_PLUGINS" >> $LOGFILE
export SQUEAK_PLUGINS

# download squeak.image to current directory
$COMPONENT_DIR/inisqueak4 -n >> $LOGFILE 2>&1

# start squeak binary from the build dir
$BUILD_DIR/squeakvm64 squeak.image $COMPONENT_DIR/test/testrunner.st >> $LOGFILE 2>&1

# testrunner.st saves output in a file , dump that file as output
cat results-32.vm

