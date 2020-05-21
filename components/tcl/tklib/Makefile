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
# Copyright (c) 2018 Michal Nowak
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		tklib
COMPONENT_VERSION=	0.6
COMPONENT_REVISION=	1
COMPONENT_PROJECT_URL=	https://core.tcl.tk/tklib/home
COMPONENT_SUMMARY=	Collection of widgets and other packages for Tk
COMPONENT_FMRI=         tcl/tklib
COMPONENT_CLASSIFICATION=       Development/Other Languages
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:d2e0648bdaf1ab0f874136f1e5645bd68a8fe206f1905d9f08614d90ee2e3025
COMPONENT_ARCHIVE_URL=	https://core.tcl.tk/tklib/raw/$(COMPONENT_ARCHIVE)?name=6a397dec6188148cf6a6fe290cf2bd92a9190c42
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

# Auto-generated dependencies
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += SUNWcs
