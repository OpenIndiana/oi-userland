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

COMPONENT_NAME=		tklib
COMPONENT_VERSION=	0.5
COMPONENT_PROJECT_URL=	http://tcllib.sourceforge.net/
COMPONENT_SUMMARY=	Collection of widgets and other packages for Tk
COMPONENT_FMRI=         tcl/tklib
COMPONENT_CLASSIFICATION=       Development/Other Languages
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:65c0343a6629c98884d9ffd17e87994a3bd54c836195ab0f907c4dff12db66b0
COMPONENT_ARCHIVE_URL=	http://downloads.sourceforge.net/tcllib/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	TCL
COMPONENT_LICENSE_FILE=	license.terms

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CONFIGURE_OPTIONS.64	+= --with-tclsh=$(USRBINDIR64)/tclsh

COMPONENT_POST_INSTALL_ACTION = \
        (for i in $$(find $(PROTO_DIR)$(USRSHAREMANDIR) -name '*.n') ; do \
           mandir="$$(dirname "$$i")"; \
           manbase="$$(basename "$$i" .n)"; \
           mv "$$i" "$${mandir}/$${manbase}.1t"; \
         done)

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

# Build dependencies
REQUIRED_PACKAGES+= tcl/tcllib
