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
# Copyright (c) 2016, 2017, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS=64_and_32
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=         pcsc-lite
COMPONENT_VERSION=      1.8.14
COMPONENT_PROJECT_URL=  http://pcsclite.alioth.debian.org/pcsclite.html
COMPONENT_DOWNLOAD_URL= https://alioth.debian.org/frs/download.php/file/4138
COMPONENT_ARCHIVE_HASH= sha256:b91f97806042315a41f005e69529cb968621f73f2ddfbd1380111a175b02334e
COMPONENT_ARCHIVE=      $(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.bz2
COMPONENT_ARCHIVE_URL=  https://alioth.debian.org/frs/download.php/file/4138/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=        library/smartcard
COMPONENT_ANITYA_ID=	2611

TPNO =                  25484

include $(WS_MAKE_RULES)/common.mk

PERL_VERSION = 5.22
POD2MAN_PATH = /usr/perl5/$(PERL_VERSION)/bin

COMPONENT_BUILD_ENV +=  PATH="$(PATH):$(POD2MAN_PATH)"

# binary and shared object creation both require the libusb-1.0 library
CONFIGURE_ENV += LIBUSB_CFLAGS="-I$(USRINCDIR)/libusb-1.0"
CONFIGURE_ENV += LIBUSB_LIBS="-lusb-1.0"

# configure.ac related patch needs configure script re-creation
COMPONENT_PREP_ACTION +=(cd $(@D); autoreconf);

# options needed for configure, otherwise default will install into /usr/local
CONFIGURE_OPTIONS +=    --exec-prefix=$(USRLIBDIR64)
CONFIGURE_OPTIONS +=    --sbindir=$(USRLIBDIR)
CONFIGURE_OPTIONS +=    --enable-libusb
CONFIGURE_OPTIONS +=    --enable-confdir=$(ETCDIR)/pcsc
CONFIGURE_OPTIONS +=    --enable-usbdropdir=$(USRLIBDIR64)/pcsc/drivers

# required packages
REQUIRED_PACKAGES += library/libusb-1
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/core-os
REQUIRED_PACKAGES += system/network
