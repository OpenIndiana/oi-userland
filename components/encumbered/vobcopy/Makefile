#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2016 Apostolos Syropoulos
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= vobcopy
COMPONENT_VERSION= 1.2.0
COMPONENT_SUMMARY= The VOBcopy DVD tool
COMPONENT_PROJECT_URL= http://www.vobcopy.org/
COMPONENT_FMRI= media/vobcopy
COMPONENT_CLASSIFICATION= System/Media
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL= http://www.vobcopy.org/download/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= \
	sha256:511f3550c1dda3fd4dfb748ed7abb9cd6f1e46f8490faad406a19cbb947c1df9
COMPONENT_LICENSE= GPLv2

include $(WS_MAKE_RULES)/encumbered.mk
include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_BUILD_ENV+= CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ENV+= LDFLAGS="$(LDFLAGS)"

COMPONENT_INSTALL_ARGS+= DESTDIR="$(PROTO_DIR)"
COMPONENT_INSTALL_ARGS+= PREFIX="$(USRDIR)"
COMPONENT_INSTALL_ARGS+= BINDIR="$(USRBINDIR.$(BITS))"
COMPONENT_INSTALL_ARGS+= MANDIR="$(USRSHAREMANDIR)"
COMPONENT_INSTALL_ARGS+= DOCDIR="$(USRSHAREDOCDIR)"

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(NO_TESTS)

REQUIRED_PACKAGES += library/video/libdvdread
REQUIRED_PACKAGES += system/library
