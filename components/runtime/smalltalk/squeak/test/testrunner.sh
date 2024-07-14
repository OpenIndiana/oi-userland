#!/bin/sh

BITS=$1
COMPONENT_DIR=$2
BUILD_DIR=$3

LOGFILE=testrunner-log.$BITS

echo "BITS set to $BITS" >> $LOGFILE
echo "COMPONENT_DIR set to $COMPONENT_DIR" >> $LOGFILE
echo "BUILD_DIR set to $BUILD_DIR" >> $LOGFILE

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
echo "Running $COMPONENT_DIR/inisqueak4 -n" >> $LOGFILE
$COMPONENT_DIR/inisqueak4 -n >> $LOGFILE 2>&1

# start squeak binary from the build dir
cd $BUILD_DIR

# check DISPLAY is set
if [ -z "$DISPLAY" ]
then
  echo "Setting DISPLAY to :0" >> $LOGFILE
  DISPLAY=":0"
  export DISPLAY
fi

echo "Running $BUILD_DIR/squeakvm64 -display $DISPLAY squeak.image $COMPONENT_DIR/test/testrunner.st" >> $LOGFILE
$BUILD_DIR/squeakvm64 -display $DISPLAY squeak.image $COMPONENT_DIR/test/testrunner.st >> $LOGFILE 2>&1

# testrunner.st saves output in a file , dump that file as output
cat results-32.vm

