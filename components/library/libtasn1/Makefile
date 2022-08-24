#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2015 Alexander Pyhalov
# Copyright 2021 Andreas Wacknitz
#

BUILD_BITS= 64_and_32
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= libtasn1
COMPONENT_VERSION= 4.19.0
COMPONENT_SUMMARY= Tiny ASN.1 library
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:1613f0ac1cf484d6ec0ce3b8c06d56263cc7242f1c23b30d82d23de345a63f7a
COMPONENT_ARCHIVE_URL=	https://ftp.gnu.org/gnu/libtasn1/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = https://www.gnu.org/software/libtasn1/
COMPONENT_FMRI= library/libtasn1
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_LICENSE = Library is LGPLv2.1, binaries are GPLv3

include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-shared

# Two tests fail otherwise
unexport SHELLOPTS

COMPONENT_TEST_TRANSFORMS= \
  '-n ' \
  '-e "/TOTAL/p" ' \
  '-e "/PASS/p" '  \
  '-e "/SKIP/p" '  \
  '-e "/XFAIL/p" ' \
  '-e "/FAIL/p" '  \
  '-e "/XPASS/p" ' \
  '-e "/ERROR/p" ' 

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
