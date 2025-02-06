#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#
# Copyright (c) 2013, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2021, Tim Mooney.  All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		perl
COMPONENT_VERSION =		5.36.3
COMPONENT_REVISION =		2
PERL_VERSION =			$(subst $(space),.,$(wordlist 1,2,$(subst ., ,$(COMPONENT_VERSION))))
PLV =				$(subst .,,$(PERL_VERSION))
COMPONENT_SUMMARY =		Perl $(PERL_VERSION)
COMPONENT_PROJECT_URL =		https://www.perl.org/
COMPONENT_SRC =			$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE =		$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH =	\
	sha256:45a228daef66d02fdccc820e71f87e40d8e3df1fc4431f8d4580ec08033866bd
COMPONENT_ARCHIVE_URL =		https://www.cpan.org/src/5.0/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI =		runtime/perl-$(PLV)
COMPONENT_CLASSIFICATION =	Development/Perl
COMPONENT_LICENSE =		Artistic-1.0-Perl OR GPL-1.0-or-later

# Archive-Tar
COMPONENT_FMRI.Archive-Tar = library/perl-5/archive-tar-$(PLV)
IPS_COMPONENT_VERSION.Archive-Tar = 2.40
HUMAN_VERSION.Archive-Tar = 2.40
COMPONENT_SUMMARY.Archive-Tar = Manipulates TAR archives

# AutoLoader
COMPONENT_FMRI.AutoLoader = library/perl-5/autoloader-$(PLV)
IPS_COMPONENT_VERSION.AutoLoader = 5.74
HUMAN_VERSION.AutoLoader = 5.74
COMPONENT_SUMMARY.AutoLoader = load subroutines only on demand

# CPAN
COMPONENT_FMRI.CPAN = library/perl-5/cpan-$(PLV)
IPS_COMPONENT_VERSION.CPAN = 2.33
HUMAN_VERSION.CPAN = 2.33
COMPONENT_SUMMARY.CPAN = query, download and build perl modules from CPAN sites

# CPAN-Meta
COMPONENT_FMRI.CPAN-Meta = library/perl-5/cpan-meta-$(PLV)
IPS_COMPONENT_VERSION.CPAN-Meta = 2.15.1.0
HUMAN_VERSION.CPAN-Meta = 2.150010
COMPONENT_SUMMARY.CPAN-Meta = the distribution metadata for a CPAN dist

# CPAN-Meta-Requirements
COMPONENT_FMRI.CPAN-Meta-Requirements = library/perl-5/cpan-meta-requirements-$(PLV)
IPS_COMPONENT_VERSION.CPAN-Meta-Requirements = 2.143	# We already had this version integrated
HUMAN_VERSION.CPAN-Meta-Requirements = 2.140
COMPONENT_SUMMARY.CPAN-Meta-Requirements = a set of version requirements for a CPAN dist

# CPAN-Meta-YAML
COMPONENT_FMRI.CPAN-Meta-YAML = library/perl-5/cpan-meta-yaml-$(PLV)
IPS_COMPONENT_VERSION.CPAN-Meta-YAML = 0.18
HUMAN_VERSION.CPAN-Meta-YAML = 0.018
COMPONENT_SUMMARY.CPAN-Meta-YAML = Read and write a subset of YAML for CPAN Meta files

# Compress-Raw-Bzip2
COMPONENT_FMRI.Compress-Raw-Bzip2 = library/perl-5/compress-raw-bzip2-$(PLV)
IPS_COMPONENT_VERSION.Compress-Raw-Bzip2 = 2.103
HUMAN_VERSION.Compress-Raw-Bzip2 = 2.103
COMPONENT_SUMMARY.Compress-Raw-Bzip2 = Low-Level Interface to bzip2 compression library

# Compress-Raw-Zlib
COMPONENT_FMRI.Compress-Raw-Zlib = library/perl-5/compress-raw-zlib-$(PLV)
IPS_COMPONENT_VERSION.Compress-Raw-Zlib = 2.105
HUMAN_VERSION.Compress-Raw-Zlib = 2.105
COMPONENT_SUMMARY.Compress-Raw-Zlib = Basic utilities for writing tests.

# Config-Perl-V
COMPONENT_FMRI.Config-Perl-V = library/perl-5/config-perl-v-$(PLV)
IPS_COMPONENT_VERSION.Config-Perl-V = 0.33
HUMAN_VERSION.Config-Perl-V = 0.33
COMPONENT_SUMMARY.Config-Perl-V = Structured data retrieval of perl -V output

# DB_File
COMPONENT_FMRI.DB_File = library/perl-5/db_file-$(PLV)
IPS_COMPONENT_VERSION.DB_File = 1.857
HUMAN_VERSION.DB_File = 1.857
COMPONENT_SUMMARY.DB_File = Perl5 access to Berkeley DB version 1.x

# Digest
COMPONENT_FMRI.Digest = library/perl-5/digest-$(PLV)
IPS_COMPONENT_VERSION.Digest = 1.20
HUMAN_VERSION.Digest = 1.20
COMPONENT_SUMMARY.Digest = Modules that calculate message digests

# Digest-MD5
COMPONENT_FMRI.Digest-MD5 = library/perl-5/digest-md5-$(PLV)
IPS_COMPONENT_VERSION.Digest-MD5 = 2.58
HUMAN_VERSION.Digest-MD5 = 2.58
COMPONENT_SUMMARY.Digest-MD5 = Perl interface to the MD-5 algorithm

# Digest-SHA
COMPONENT_FMRI.Digest-SHA = library/perl-5/digest-sha-$(PLV)
IPS_COMPONENT_VERSION.Digest-SHA = 6.2
HUMAN_VERSION.Digest-SHA = 6.02
COMPONENT_SUMMARY.Digest-SHA = Perl extension for SHA-1/224/256/384/512

# Encode
COMPONENT_FMRI.Encode = library/perl-5/encode-$(PLV)
IPS_COMPONENT_VERSION.Encode = 3.17
HUMAN_VERSION.Encode = 3.17
COMPONENT_SUMMARY.Encode = character encodings in Perl

# ExtUtils-Constant
COMPONENT_FMRI.ExtUtils-Constant = library/perl-5/extutils-constant-$(PLV)
IPS_COMPONENT_VERSION.ExtUtils-Constant = 0.25
HUMAN_VERSION.ExtUtils-Constant = 0.25
COMPONENT_SUMMARY.ExtUtils-Constant = generate XS code to import C header constants

# ExtUtils-Install
COMPONENT_FMRI.ExtUtils-Install = library/perl-5/extutils-install-$(PLV)
IPS_COMPONENT_VERSION.ExtUtils-Install = 2.20
HUMAN_VERSION.ExtUtils-Install = 2.20
COMPONENT_SUMMARY.ExtUtils-Install = install files from here to there

# ExtUtils-MakeMaker
COMPONENT_FMRI.ExtUtils-MakeMaker = library/perl-5/extutils-makemaker-$(PLV)
IPS_COMPONENT_VERSION.ExtUtils-MakeMaker = 7.64
HUMAN_VERSION.ExtUtils-MakeMaker = 7.64
COMPONENT_SUMMARY.ExtUtils-MakeMaker = Create a module Makefile

# ExtUtils-Manifest
COMPONENT_FMRI.ExtUtils-Manifest = library/perl-5/extutils-manifest-$(PLV)
IPS_COMPONENT_VERSION.ExtUtils-Manifest = 1.73
HUMAN_VERSION.ExtUtils-Manifest = 1.73
COMPONENT_SUMMARY.ExtUtils-Manifest = Utilities to write and check a MANIFEST file

# ExtUtils-PL2Bat
COMPONENT_FMRI.ExtUtils-PL2Bat = library/perl-5/extutils-pl2bat-$(PLV)
IPS_COMPONENT_VERSION.ExtUtils-PL2Bat = 0.4
HUMAN_VERSION.ExtUtils-PL2Bat = 0.004
COMPONENT_SUMMARY.ExtUtils-PL2Bat = Batch file creation to run perl scripts on Windows

# File-Fetch
COMPONENT_FMRI.File-Fetch = library/perl-5/file-fetch-$(PLV)
IPS_COMPONENT_VERSION.File-Fetch = 1.4
HUMAN_VERSION.File-Fetch = 1.04
COMPONENT_SUMMARY.File-Fetch = Generic file fetching code

# File-Path
COMPONENT_FMRI.File-Path = library/perl-5/file-path-$(PLV)
IPS_COMPONENT_VERSION.File-Path = 2.18
HUMAN_VERSION.File-Path = 2.18
COMPONENT_SUMMARY.File-Path = Create or remove directory trees

# File-Temp
COMPONENT_FMRI.File-Temp = library/perl-5/file-temp-$(PLV)
IPS_COMPONENT_VERSION.File-Temp = 0.23.11
HUMAN_VERSION.File-Temp = 0.2311
COMPONENT_SUMMARY.File-Temp = return name and handle of a temporary file safely

# Filter
COMPONENT_FMRI.Filter = library/perl-5/filter-$(PLV)
IPS_COMPONENT_VERSION.Filter = 1.60
HUMAN_VERSION.Filter = 1.60
COMPONENT_SUMMARY.Filter = Source Filters

# Getopt-Long
COMPONENT_FMRI.Getopt-Long = library/perl-5/getopt-long-$(PLV)
IPS_COMPONENT_VERSION.Getopt-Long = 2.52
HUMAN_VERSION.Getopt-Long = 2.52
COMPONENT_SUMMARY.Getopt-Long = Module to handle parsing command line options

# HTTP-Tiny
COMPONENT_FMRI.HTTP-Tiny = library/perl-5/http-tiny-$(PLV)
IPS_COMPONENT_VERSION.HTTP-Tiny = 0.80
HUMAN_VERSION.HTTP-Tiny = 0.080
COMPONENT_SUMMARY.HTTP-Tiny = A small, simple, correct HTTP/1.1 client

# IO-Compress
COMPONENT_FMRI.IO-Compress = library/perl-5/io-compress-$(PLV)
IPS_COMPONENT_VERSION.IO-Compress = 2.106
HUMAN_VERSION.IO-Compress = 2.106
COMPONENT_SUMMARY.IO-Compress = IO Interface to compressed data files/buffers

# IO-Socket-IP
COMPONENT_FMRI.IO-Socket-IP = library/perl-5/io-socket-ip-$(PLV)
IPS_COMPONENT_VERSION.IO-Socket-IP = 0.41
HUMAN_VERSION.IO-Socket-IP = 0.41
COMPONENT_SUMMARY.IO-Socket-IP = Family-neutral IP socket supporting both IPv4 and IPv6

# IO-Zlib
COMPONENT_FMRI.IO-Zlib = library/perl-5/io-zlib-$(PLV)
IPS_COMPONENT_VERSION.IO-Zlib = 1.11
HUMAN_VERSION.IO-Zlib = 1.11
COMPONENT_SUMMARY.IO-Zlib = IO:: style interface to Compress::Zlib

# IPC-Cmd
COMPONENT_FMRI.IPC-Cmd = library/perl-5/ipc-cmd-$(PLV)
IPS_COMPONENT_VERSION.IPC-Cmd = 1.4
HUMAN_VERSION.IPC-Cmd = 1.04
COMPONENT_SUMMARY.IPC-Cmd = A cross platform way of running (interactive) commandline programs.

# IPC-SysV
COMPONENT_FMRI.IPC-SysV = library/perl-5/ipc-sysv-$(PLV)
IPS_COMPONENT_VERSION.IPC-SysV = 2.9
HUMAN_VERSION.IPC-SysV = 2.09
COMPONENT_SUMMARY.IPC-SysV = System V IPC constants and system calls

# JSON-PP
COMPONENT_FMRI.JSON-PP = library/perl-5/json-pp-$(PLV)
IPS_COMPONENT_VERSION.JSON-PP = 4.7
HUMAN_VERSION.JSON-PP = 4.07
COMPONENT_SUMMARY.JSON-PP = JSON::XS compatible pure-Perl module.

# Locale-Maketext-Simple
COMPONENT_FMRI.Locale-Maketext-Simple = library/perl-5/locale-maketext-simple-$(PLV)
IPS_COMPONENT_VERSION.Locale-Maketext-Simple = 0.21
HUMAN_VERSION.Locale-Maketext-Simple = 0.21_01
COMPONENT_SUMMARY.Locale-Maketext-Simple = Simple interface to Locale::Maketext::Lexicon

# MIME-Base64
COMPONENT_FMRI.MIME-Base64 = library/perl-5/mime-base64-$(PLV)
IPS_COMPONENT_VERSION.MIME-Base64 = 3.16
HUMAN_VERSION.MIME-Base64 = 3.16
COMPONENT_SUMMARY.MIME-Base64 = Encoding and decoding of base64 strings

# Math-BigInt
COMPONENT_FMRI.Math-BigInt = library/perl-5/math-bigint-$(PLV)
IPS_COMPONENT_VERSION.Math-BigInt = 1.99.98.30
HUMAN_VERSION.Math-BigInt = 1.999830
COMPONENT_SUMMARY.Math-BigInt = Pure Perl module to test Math::BigInt with scalars

# Math-BigInt-FastCalc
COMPONENT_FMRI.Math-BigInt-FastCalc = library/perl-5/math-bigint-fastcalc-$(PLV)
IPS_COMPONENT_VERSION.Math-BigInt-FastCalc = 0.50.12
HUMAN_VERSION.Math-BigInt-FastCalc = 0.5012
COMPONENT_SUMMARY.Math-BigInt-FastCalc = Math::BigInt::Calc with some XS for more speed

# Math-BigRat
COMPONENT_FMRI.Math-BigRat = library/perl-5/math-bigrat-$(PLV)
IPS_COMPONENT_VERSION.Math-BigRat = 0.26.21
HUMAN_VERSION.Math-BigRat = 0.2621
COMPONENT_SUMMARY.Math-BigRat = arbitrary size rational number math package

# Memoize
COMPONENT_FMRI.Memoize = library/perl-5/memoize-$(PLV)
IPS_COMPONENT_VERSION.Memoize = 1.3
HUMAN_VERSION.Memoize = 1.03_01
COMPONENT_SUMMARY.Memoize = Make functions faster by trading space for time

# Module-Load
COMPONENT_FMRI.Module-Load = library/perl-5/module-load-$(PLV)
IPS_COMPONENT_VERSION.Module-Load = 0.36
HUMAN_VERSION.Module-Load = 0.36
COMPONENT_SUMMARY.Module-Load = Load modules in a DWIM style

# Module-Load-Conditional
COMPONENT_FMRI.Module-Load-Conditional = library/perl-5/module-load-conditional-$(PLV)
IPS_COMPONENT_VERSION.Module-Load-Conditional = 0.74
HUMAN_VERSION.Module-Load-Conditional = 0.74
COMPONENT_SUMMARY.Module-Load-Conditional = Looking up module information / loading at runtime

# Module-Loaded
COMPONENT_FMRI.Module-Loaded = library/perl-5/module-loaded-$(PLV)
IPS_COMPONENT_VERSION.Module-Loaded = 0.8
HUMAN_VERSION.Module-Loaded = 0.08
COMPONENT_SUMMARY.Module-Loaded = Mark modules as loaded/unloaded

# Module-Metadata
COMPONENT_FMRI.Module-Metadata = library/perl-5/module-metadata-$(PLV)
IPS_COMPONENT_VERSION.Module-Metadata = 1.0.37
HUMAN_VERSION.Module-Metadata = 1.000037
COMPONENT_SUMMARY.Module-Metadata = Gather package and POD information from perl module files

# NEXT
COMPONENT_FMRI.NEXT = library/perl-5/next-$(PLV)
IPS_COMPONENT_VERSION.NEXT = 0.69
HUMAN_VERSION.NEXT = 0.69
COMPONENT_SUMMARY.NEXT = Provide a pseudo-class NEXT (et al) that allows method redispatch

# Params-Check
COMPONENT_FMRI.Params-Check = library/perl-5/params-check-$(PLV)
IPS_COMPONENT_VERSION.Params-Check = 0.38
HUMAN_VERSION.Params-Check = 0.38
COMPONENT_SUMMARY.Params-Check = Templated based param validation

# Perl-OSType
COMPONENT_FMRI.Perl-OSType = library/perl-5/perl-ostype-$(PLV)
IPS_COMPONENT_VERSION.Perl-OSType = 1.10
HUMAN_VERSION.Perl-OSType = 1.010
COMPONENT_SUMMARY.Perl-OSType = Map Perl operating system names to generic types

# PerlIO-via-QuotedPrint
COMPONENT_FMRI.PerlIO-via-QuotedPrint = library/perl-5/perlio-via-quotedprint-$(PLV)
IPS_COMPONENT_VERSION.PerlIO-via-QuotedPrint = 0.9
HUMAN_VERSION.PerlIO-via-QuotedPrint = 0.09
COMPONENT_SUMMARY.PerlIO-via-QuotedPrint = PerlIO layer for quoted-printable strings

# Pod-Checker
COMPONENT_FMRI.Pod-Checker = library/perl-5/pod-checker-$(PLV)
IPS_COMPONENT_VERSION.Pod-Checker = 1.74
HUMAN_VERSION.Pod-Checker = 1.74
COMPONENT_SUMMARY.Pod-Checker = Pod::Checker verifies POD documentation contents for compliance with the POD format specifications

# Pod-Escapes
COMPONENT_FMRI.Pod-Escapes = library/perl-5/pod-escapes-$(PLV)
IPS_COMPONENT_VERSION.Pod-Escapes = 1.7
HUMAN_VERSION.Pod-Escapes = 1.07
COMPONENT_SUMMARY.Pod-Escapes = for resolving Pod Elt...gt sequences

# Pod-Perldoc
COMPONENT_FMRI.Pod-Perldoc = library/perl-5/pod-perldoc-$(PLV)
IPS_COMPONENT_VERSION.Pod-Perldoc = 3.28
HUMAN_VERSION.Pod-Perldoc = 3.2801
COMPONENT_SUMMARY.Pod-Perldoc = Look up Perl documentation in Pod format.

# Pod-Simple
COMPONENT_FMRI.Pod-Simple = library/perl-5/pod-simple-$(PLV)
IPS_COMPONENT_VERSION.Pod-Simple = 3.43
HUMAN_VERSION.Pod-Simple = 3.43
COMPONENT_SUMMARY.Pod-Simple = framework for parsing Pod

# Pod-Usage
COMPONENT_FMRI.Pod-Usage = library/perl-5/pod-usage-$(PLV)
IPS_COMPONENT_VERSION.Pod-Usage = 2.1
HUMAN_VERSION.Pod-Usage = 2.01
COMPONENT_SUMMARY.Pod-Usage = extracts POD documentation and shows usage information

# Scalar-List-Utils
COMPONENT_FMRI.Scalar-List-Utils = library/perl-5/scalar-list-utils-$(PLV)
IPS_COMPONENT_VERSION.Scalar-List-Utils = 1.62
HUMAN_VERSION.Scalar-List-Utils = 1.62
COMPONENT_SUMMARY.Scalar-List-Utils = Common Scalar and List utility subroutines

# Socket
COMPONENT_FMRI.Socket = library/perl-5/socket-$(PLV)
IPS_COMPONENT_VERSION.Socket = 2.33
HUMAN_VERSION.Socket = 2.033
COMPONENT_SUMMARY.Socket = networking constants and support functions

# Sys-Syslog
COMPONENT_FMRI.Sys-Syslog = library/perl-5/sys-syslog-$(PLV)
IPS_COMPONENT_VERSION.Sys-Syslog = 0.36
HUMAN_VERSION.Sys-Syslog = 0.36
COMPONENT_SUMMARY.Sys-Syslog = Perl interface to the UNIX syslog(3) calls

# Term-ANSIColor
COMPONENT_FMRI.Term-ANSIColor = library/perl-5/term-ansicolor-$(PLV)
IPS_COMPONENT_VERSION.Term-ANSIColor = 5.1
HUMAN_VERSION.Term-ANSIColor = 5.01
COMPONENT_SUMMARY.Term-ANSIColor = Color output using ANSI escape sequences

# Term-Cap
COMPONENT_FMRI.Term-Cap = library/perl-5/term-cap-$(PLV)
IPS_COMPONENT_VERSION.Term-Cap = 1.17
HUMAN_VERSION.Term-Cap = 1.17
COMPONENT_SUMMARY.Term-Cap = Perl termcap interface

# Test-Harness
COMPONENT_FMRI.Test-Harness = library/perl-5/test-harness-$(PLV)
IPS_COMPONENT_VERSION.Test-Harness = 3.44
HUMAN_VERSION.Test-Harness = 3.44
COMPONENT_SUMMARY.Test-Harness = contributing to TAP::Harness

# Test-Simple
COMPONENT_FMRI.Test-Simple = library/perl-5/test-simple-$(PLV)
IPS_COMPONENT_VERSION.Test-Simple = 1.302.190
HUMAN_VERSION.Test-Simple = 1.302190
COMPONENT_SUMMARY.Test-Simple = Basic utilities for writing tests.

# Text-Balanced
COMPONENT_FMRI.Text-Balanced = library/perl-5/text-balanced-$(PLV)
IPS_COMPONENT_VERSION.Text-Balanced = 2.4
HUMAN_VERSION.Text-Balanced = 2.04
COMPONENT_SUMMARY.Text-Balanced = Extract delimited text sequences from strings.

# Text-ParseWords
COMPONENT_FMRI.Text-ParseWords = library/perl-5/text-parsewords-$(PLV)
IPS_COMPONENT_VERSION.Text-ParseWords = 3.31
HUMAN_VERSION.Text-ParseWords = 3.31
COMPONENT_SUMMARY.Text-ParseWords = parse text into an array of tokens or array of arrays

# Text-Tabs+Wrap
COMPONENT_FMRI.Text-Tabs+Wrap = library/perl-5/text-tabs+wrap-$(PLV)
IPS_COMPONENT_VERSION.Text-Tabs+Wrap = 2021.8.14
HUMAN_VERSION.Text-Tabs+Wrap = 2021.0814
COMPONENT_SUMMARY.Text-Tabs+Wrap = Expand tabs and do simple line wrapping

# Tie-RefHash
COMPONENT_FMRI.Tie-RefHash = library/perl-5/tie-refhash-$(PLV)
IPS_COMPONENT_VERSION.Tie-RefHash = 1.40
HUMAN_VERSION.Tie-RefHash = 1.40
COMPONENT_SUMMARY.Tie-RefHash = Use references as hash keys

# Time-Local
COMPONENT_FMRI.Time-Local = library/perl-5/time-local-$(PLV)
IPS_COMPONENT_VERSION.Time-Local = 1.30
HUMAN_VERSION.Time-Local = 1.30
COMPONENT_SUMMARY.Time-Local = Efficiently compute time from local and GMT time

# Time-Piece
COMPONENT_FMRI.Time-Piece = library/perl-5/time-piece-$(PLV)
IPS_COMPONENT_VERSION.Time-Piece = 1.34.1
HUMAN_VERSION.Time-Piece = 1.3401
COMPONENT_SUMMARY.Time-Piece = Object Oriented time objects

# Unicode-Collate
COMPONENT_FMRI.Unicode-Collate = library/perl-5/unicode-collate-$(PLV)
IPS_COMPONENT_VERSION.Unicode-Collate = 1.31
HUMAN_VERSION.Unicode-Collate = 1.31
COMPONENT_SUMMARY.Unicode-Collate = Unicode Collation Algorithm

# autodie
COMPONENT_FMRI.autodie = library/perl-5/autodie-$(PLV)
IPS_COMPONENT_VERSION.autodie = 2.34
HUMAN_VERSION.autodie = 2.34
COMPONENT_SUMMARY.autodie = Replace functions with ones that succeed or die with lexical scope

# bignum
COMPONENT_FMRI.bignum = library/perl-5/bignum-$(PLV)
IPS_COMPONENT_VERSION.bignum = 0.65
HUMAN_VERSION.bignum = 0.65
COMPONENT_SUMMARY.bignum = transparent big floating point number support for Perl

# experimental
COMPONENT_FMRI.experimental = library/perl-5/experimental-$(PLV)
IPS_COMPONENT_VERSION.experimental = 0.28
HUMAN_VERSION.experimental = 0.028
COMPONENT_SUMMARY.experimental = Experimental features made easy

# libnet
COMPONENT_FMRI.libnet = library/perl-5/libnet-$(PLV)
IPS_COMPONENT_VERSION.libnet = 3.14
HUMAN_VERSION.libnet = 3.14
COMPONENT_SUMMARY.libnet = Collection of network protocol modules

# parent
COMPONENT_FMRI.parent = library/perl-5/parent-$(PLV)
IPS_COMPONENT_VERSION.parent = 0.238
HUMAN_VERSION.parent = 0.238
COMPONENT_SUMMARY.parent = Establish an ISA relationship with base classes at compile time

# perlfaq
COMPONENT_FMRI.perlfaq = library/perl-5/perlfaq-$(PLV)
IPS_COMPONENT_VERSION.perlfaq = 5.2021.5.20
HUMAN_VERSION.perlfaq = 5.20210520
COMPONENT_SUMMARY.perlfaq = Frequently asked questions about Perl

# podlators
COMPONENT_FMRI.podlators = library/perl-5/podlators-$(PLV)
IPS_COMPONENT_VERSION.podlators = 4.14
HUMAN_VERSION.podlators = 4.14
COMPONENT_SUMMARY.podlators = Convert POD data to various other formats

# version
COMPONENT_FMRI.version = library/perl-5/version-$(PLV)
IPS_COMPONENT_VERSION.version = 0.99.29
HUMAN_VERSION.version = 0.9929
COMPONENT_SUMMARY.version = Structured version objects

include $(WS_MAKE_RULES)/common.mk

# helper target
update-license-file: patch
	( \
		$(GNU_GREP) -v '^=========' $(SOURCE_DIR)/README | $(GSED) -e '0,/^LICENSING/d' -e '/./,$$!d' ; \
		printf -- '--- Copying ---------------------------------------------------------------\n' ; \
		$(CAT) $(SOURCE_DIR)/Copying ; \
		printf -- '\n\n--- Artistic --------------------------------------------------------------\n\n' ; \
		$(CAT) $(SOURCE_DIR)/Artistic | $(GSED) -e '/./,$$!d' \
	) > $(COMPONENT_DIR)/$(COMPONENT_LICENSE_FILE)

CONFIGURE_SCRIPT = $(SOURCE_DIR)/Configure
CONFIGURE_ENV += MAKE=$(GMAKE)

CONFIGURE_OPTIONS =	-de
CONFIGURE_OPTIONS +=	-Dmksymlinks
CONFIGURE_OPTIONS +=	-Ulocincpth=
CONFIGURE_OPTIONS +=	-Uloclibpth=

CONFIGURE_OPTIONS +=	-Dprefix=/usr/perl5/$(PERL_VERSION)
CONFIGURE_OPTIONS +=	-Dprivlib=/usr/perl5/$(PERL_VERSION)/lib
CONFIGURE_OPTIONS +=	-Dsitelib=/usr/perl5/site_perl/$(PERL_VERSION)
CONFIGURE_OPTIONS +=	-Dvendorprefix=/usr/perl5/$(PERL_VERSION)
CONFIGURE_OPTIONS +=	-Dvendorlib=/usr/perl5/vendor_perl/$(PERL_VERSION)
CONFIGURE_OPTIONS +=	-Dman3dir=/usr/perl5/$(PERL_VERSION)/man/man3perl
CONFIGURE_OPTIONS +=	-Dman3ext=3perl

CONFIGURE_OPTIONS +=	-Dmyhostname="localhost"
CONFIGURE_OPTIONS +=	-Dcf_email="oi-dev@openindiana.org"
CONFIGURE_OPTIONS +=	-Dcf_by="perl-bugs"

CONFIGURE_OPTIONS +=	-Duseshrplib
CONFIGURE_OPTIONS +=	-Dlibperl=libperl.so

CONFIGURE_OPTIONS +=	-Dusedtrace
CONFIGURE_OPTIONS +=	-Dusethreads

CONFIGURE_OPTIONS +=	-Dcc="$(CC) $(CC_BITS)"
CONFIGURE_OPTIONS +=	-Doptimize="$(gcc_OPT)"
CONFIGURE_OPTIONS +=	-Dlibpth="/lib/64 /usr/lib/64"

COMPONENT_INSTALL_ENV	+=	DESTDIR="$(PROTO_DIR)"

COMPONENT_TEST_TRANSFORMS += "-e '1,/runtests choose/d'"	# throw out everything prior to test results
COMPONENT_TEST_TRANSFORMS += "-e '/^u=/d'"			# delete timings
COMPONENT_TEST_TRANSFORMS += "-e '/^Elapsed/d'"			# delete timings
COMPONENT_TEST_TRANSFORMS += "-e '/^make\[/d'"			# delete make logs

# Proper PERL_ARCH is needed for manifest processing.
PERL_ARCH = $(shell . $(BUILD_DIR_$(BUILD_BITS))/config.sh && echo $$archname)

#
# All hardlink targets should be listed here so generated sample manifest does
# not change with every run.
#
PKG_HARDLINKS += usr/perl5/$(PERL_VERSION)/bin/perl
PKG_HARDLINKS += usr/perl5/$(PERL_VERSION)/bin/perlbug
PKG_HARDLINKS += usr/perl5/$(PERL_VERSION)/man/man1/perlbug.1

# Auto-generated dependencies
REQUIRED_PACKAGES += database/berkeleydb-5
REQUIRED_PACKAGES += library/database/gdbm
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
