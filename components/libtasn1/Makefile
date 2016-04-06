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
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME= libtasn1
COMPONENT_VERSION= 2.14
COMPONENT_SUMMARY= Tiny ASN.1 library
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:bc2936cd20267859278145e563427c274d27aaae30ecdf50a04cdd4ec0153d54
COMPONENT_ARCHIVE_URL= \
  http://ftp.gnu.org/gnu/libtasn1/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = https://www.gnu.org/software/libtasn1/
COMPONENT_FMRI= library/libtasn1
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_LICENSE = Library is LGPLv2.1, binaries are GPLv3
COMPONENT_LICENSE_FILE = libtasn1.license

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=/usr/gnu/bin:/usr/bin

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-shared

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(TEST_32_and_64)
