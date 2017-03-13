#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright (c) 2016 Sergey Avseyev
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		tcllib
COMPONENT_VERSION=	1.17
COMPONENT_REVISION=	1
COMPONENT_PROJECT_URL=	http://tcllib.sourceforge.net/
COMPONENT_SUMMARY=	The standard Tcl library
COMPONENT_FMRI=		tcl/tcllib
COMPONENT_CLASSIFICATION=       Development/Other Languages
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:5efccf07af9585b448438e349dbb38765941ff0b1cbdf7a8c702cf6490408b5d
COMPONENT_ARCHIVE_URL=	http://downloads.sourceforge.net/tcllib/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	TCL
COMPONENT_LICENSE_FILE=	license.terms

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PREP_ACTION = \
        (for i in $$(find $(SOURCE_DIR)/embedded/man -name '*.n') ; do \
           mandir="$$(dirname "$$i")"; \
           manbase="$$(basename "$$i" .n)"; \
           mv "$$i" "$${mandir}/$${manbase}.1t"; \
         done)

CONFIGURE_OPTIONS.64	+= --with-tclsh=$(USRBINDIR64)/tclsh

USRBINDIR.32 = $(USRBINDIR)
USRBINDIR.64 = $(USRBINDIR64)

APPS = dtplite nns nnsd nnslog page pt tcldocstrip

COMPONENT_POST_INSTALL_ACTION += \
        (for app in $(APPS); do \
          $(GSED) -i '' "s:/usr/bin/env tclsh:$(USRBINDIR.$(BITS))/tclsh:" $(PROTO_DIR)$(USRBINDIR.$(BITS))/$$app; \
        done); \
        $(MV) $(PROTO_DIR)$(USRBINDIR.$(BITS))/{,tcl}page

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include $(WS_MAKE_RULES)/depend.mk
