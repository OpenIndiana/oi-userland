#!/bin/bash
#
# Copyright (c) 2011, 2019, Oracle and/or its affiliates. All rights reserved.
#

function fail()
{
	echo "ERROR:" $*
	exit 1
}

# Verify that the build has certain properties.
if (( $# != 3 )); then
	print "usage: $0 <build_dir> <cc_path> <arch>"
	exit 1
fi

BUILD_DIR="$1"
if [[ ! -d $BUILD_DIR ]]; then
	fail "$BUILD_DIR is not a directory"
fi

CC="$2"
if [[ ! -x ${CC} ]]; then
	fail "Not executable: ${CC}"
fi
echo "Using CC: ${CC}"

BITS="$3"

function disallowed_check()
{
	#XXX: keep rc4 for now since wpa_suplicant uses it
	#XXX: keep md4 for now since wget and nmap use it
	#disallowed=(rc2 rc4 rc5 md2 md4 mdc2 idea whirlpool seed)
	disallowed=(rc2 rc5 md2 mdc2 idea whirlpool seed)
	cipher_regexp=$( echo ${disallowed_ciphers[*]} | \
	    tr '[a-z]' '[A-Z]' | sed 's/ /|/g' )
	pkg_manifest_file="openssl-1.1.p5m"

	echo "Checking libcrypto.so for symbols of disallowed ciphers"
	if elfdump $BUILD_DIR/libcrypto.so | \
	    egrep '($cipher_regexp)' >/dev/null; then
		fail "libcrypto.so contains disallowed ciphers"
	fi

	if [[ ! -r $pkg_manifest_file ]]; then
		fail "Cannot read package manifest file $pkg_manifest_file"
	fi

	# Make sure the header files are not delivered. This is necesssary
	# to do since OpenSSL build system delivers the header files even though
	# Configure was run with 'no-xxx' option.
	for item in ${disallowed[*]} whrlpool; do
		header_file="${item}.h"
		echo "Checking header file $header_file in pkg manifest file"
		if grep $( echo $header_file | sed 's/\./\\./' ) \
		    $pkg_manifest_file >/dev/null; then
			fail "Header file $header_file should not be delivered"
		fi
		#XXX: We do not ship them.
		#echo "Checking header file $header_file in lint library files"
		#if grep $( echo $header_file | sed 's/\./\\./' ) llib-*; then
		#	fail "Header file $header_file present in lint library files"
		#fi
	done
}

function deprecated_check()
{
	# Check that the DECLARE_DEPRECATED macro works for one of the functions.
	tmpdir=$( mktemp -d /tmp/md5-deprecated-test.XXXXXX )
	if [[ -z $tmpdir ]]; then
		echo "cannot create temporary directory"
		exit 1
	fi
	cat << EOF > "$tmpdir/md5.c"
#include "openssl/md5.h"
int
main(void)
{
	MD5_CTX ctx;

	MD5_Init(&ctx);

	return (0);
}
EOF

	echo "Checking that compiler issues deprecated warning for obsolete ciphers"
	${CC} -I $BUILD_DIR/include -o "$tmpdir/md5.o" -c "$tmpdir/md5.c" 2>&1 | \
	    grep "warning: \'MD5_Init\' is deprecated" >/dev/null
	ret=$?
	rm -rf "$tmpdir"
	if (( ret != 0 )); then
		fail "compiler should issue deprecated warning but did not"
	fi
}

function sx_check()
{
	typeset binary="$BUILD_DIR/apps/openssl"

	echo "Checking security extensions for $binary"
	cnt=$( elfdump -d $binary | \
	    egrep -c '(SUNW_SX_ASLR)|(SUNW_SX_NXSTACK)|(SUNW_SX_NXHEAP)' )
	if (( cnt != 3 )); then
		fail "Security extensions are not enabled for $binary"
	fi
}

#
# Check that libcrypto.so was built with thread support enabled.
# This is the default however it does not hurt to check.
#
function threads_check()
{
	typeset libcrypto="$BUILD_DIR/libcrypto.so"

	echo "Checking that $libcrypto was built with threading support"
	if [[ ! -r $libcrypto ]]; then
		fail "Not readable: $libcrypto"
	fi

	if ! nm "$libcrypto" | grep CRYPTO_THREAD >/dev/null; then
		fail "Missing CRYPTO_THREAD symbols"
	fi
}

function soname_check()
{
	for name in libcrypto.so libssl.so; do
		lib="$BUILD_DIR/$name"
		if ! elfdump -d "$lib" | grep SONAME >/dev/null; then
			fail "Missing SONAME in $lib"
		fi
	done
}

#
# To prevent regression of bug
#
#   29967264 64-bit OpenSSL pkgconfig files have 32-bit library path on x86
#
function pkgconfig_64bit_check()
{
	if [[ $BITS != "64" ]]; then
		return
	fi

	for name in openssl.pc libssl.pc libcrypto.pc; do
		file="$BUILD_DIR/$name"
		if ! grep '^libdir=.*\/.*64' "$file" >/dev/null; then
			fail "Missing 64-bit path component in $file"
		fi
	done
}

disallowed_check
#XXX: We do not do this yet: deprecated_check
#XXX: Not supported here: sx_check
threads_check
soname_check
pkgconfig_64bit_check
