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
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
#
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		bind
COMPONENT_VERSION=	9.6-ESV-R5-P1
IPS_COMPONENT_VERSION=	9.6.3.5.1
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL=	http://www.isc.org/software/bind/

# hash from: sha256sum $(COMPONENT_ARCHIVE) | sed 's/\(.[^ ]*\).*/sha256:\1/'
COMPONENT_ARCHIVE_HASH=	 \
    sha256:80e1ee926a49c2a787b4eb7c7516fbbe9fdac1f07f20c18fccfa6ce59196a6bc
COMPONENT_ARCHIVE_URL=	\
	http://ftp.isc.org/isc/bind9/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

# Build.
#
# FYI, The configure options are displayed by 'named -V'.  Previously
# that was overriden by setting CONFIGARGS to hide build server
# pathnames.

# Traditionally all BIND executables are installed in sbin not bin.
# DNS libraries are in usr/lib/dns - Override settings from configure.mk
CONFIGURE_BINDIR.32 =	$(CONFIGURE_PREFIX)/sbin
CONFIGURE_LIBDIR.32 =	$(CONFIGURE_PREFIX)/lib/dns

CONFIGURE_OPTIONS +=	--with-libtool
CONFIGURE_OPTIONS +=	--sbindir=$(CONFIGURE_BINDIR.$(BITS))
CONFIGURE_OPTIONS +=	--sysconfdir=/etc
CONFIGURE_OPTIONS +=	--localstatedir=/var
CONFIGURE_OPTIONS +=	--with-openssl
CONFIGURE_OPTIONS +=	--enable-threads=yes
CONFIGURE_OPTIONS +=	--enable-devpoll=yes
CONFIGURE_OPTIONS +=	--disable-openssl-version-check
CONFIGURE_OPTIONS +=	--enable-fixed-rrset
CONFIGURE_OPTIONS +=	--disable-getifaddrs
CONFIGURE_OPTIONS +=	--with-pkcs11

CONFIGURE_OPTIONS +=	CFLAGS="$(CFLAGS)"
# Configure will add "-mt" to CC which is already set in CFLAGS, so override.
CONFIGURE_OPTIONS +=	CC="$(CC)"

.PHONY: build
build:		$(BUILD_32)

include ../../make-rules/shared-targets.mk

# Install.
#
# Currently manual pages are distributed from pkg:/system/manual@.
# While there are some changes in our manuals, for example section
# numbering and additions to named(1M) for SMF - that could be fixed
# by patch.
#
# In addition to BIND deliverables we also deliver SMF files and
# migration notes.  There is no need to install these extras into the
# prototype directory, they are simply referenced in relevant manifest
# (p5m) file.

.PHONY: install
install: $(INSTALL_32)

# Testing.
#
# sumarize nawk script; reads ISC output which is of the form:
# /^T:/ = Start of a test.
# /^I:/ = Info from a test;  colleced for possible use later.
# /^A:/ = About: summary of the test - not used here.
# /^R:/ = Result: If 'PASS' then continue, else print line and collected info.
# Known issues may then be accounted for.
# @ EOF = Display count of RESULTS: i.e. R:PASS=124 R:UNTESTED=26 Total=150
# if not 100% pass rate and issue is not known the word 'issues!' is appended
# to resulting string.
summarize=	'\
		/^T:/ {name=$$0;info="";}\
		/^I:/ {info=sprintf("%s%s\n", info, $$0);}\
		/^R:/ {test++; result[$$1]++;}\
		/^R:PASS/ {next;}\
		/^R:/ {printf("%s: %s\n%s\n", $$1, name, info);}\
		/^R:UNTESTED/ && name ~ /^T:dst:2:A/ {known++;}\
		/^R:UNRESOLVED/ && name ~ /^T:dst:1:A/ {known++;}\
		END{for (item in result)\
				printf("%s=%d ", item, result[item]);\
			printf("(known=%d) Total=%d%s\n", known, test, \
				((result["R:PASS"] + known) < test)? \
				" issues!" : "");\
		}'

isc_ifconfig=	./bin/tests/system/ifconfig.sh

.PHONY: test
test: build $(TEST_32)

# fulltest requires sufficient privileges to configures IP addresses
# 10.53.0.1 through 10.53.0.5 as aliases on the loopback interface.
FULL_TEST_32=	$(TEST_32:%=%_FULL)

.PHONY: fulltest
fulltest: build $(FULL_TEST_32)

$(FULL_TEST_32):
	cd $(COMPONENT_SRC) && $(SHELL)  $(isc_ifconfig) up
	-cd $(@D) && $(MAKE) test 2>&1 | $(TEE) $@
	cd $(COMPONENT_SRC) && $(SHELL) $(isc_ifconfig) down
	$(NAWK) $(summarize) $@

$(TEST_32):
	-cd $(@D) && $(MAKE) test 2>&1 | $(TEE) $@
	$(NAWK) $(summarize) $@

# test-summary shows summary for targets test and fulltest. Use target
# test-clean to remove previous tests.
.PHONY: test-summary
test-summary:
	@for file in $(TEST_32)*; do \
		if [ -f $$file ]; then \
			echo 'Summary for' $$file;\
			$(NAWK) $(summarize) $$file;\
			fi;\
		done

.PHONY: test-version
test-version:
	@echo;echo 32 bit version
	-LD_LIBRARY_PATH=$(PROTO_DIR)$(CONFIGURE_LIBDIR.32) \
		$(PROTO_DIR)$(CONFIGURE_BINDIR.32)/named -V

.PHONY: test-clean
test-clean:
	$(RM) $(TEST_32) $(FULL_TEST_32)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
