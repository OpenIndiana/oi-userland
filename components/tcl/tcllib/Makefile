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
# Copyright (c) 2018, Michal Nowak
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		tcllib
COMPONENT_VERSION=	1.19
COMPONENT_PROJECT_URL=	https://core.tcl.tk/tcllib/doc/trunk/embedded/index.html
COMPONENT_SUMMARY=	The standard Tcl library
COMPONENT_FMRI=		tcl/tcllib
COMPONENT_CLASSIFICATION=       Development/Other Languages
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
    sha256:4a4f73cc8aca1d6b625717b0ace61205cddaa7768f5f9a0e160dd62abb4177ef
COMPONENT_ARCHIVE_URL=	https://core.tcl.tk/tcllib/uv/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	TCL
COMPONENT_LICENSE_FILE=	license.terms

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PREP_ACTION = \
        (for i in $$(find $(SOURCE_DIR)/idoc/man -name '*.n') ; do \
           mandir="$$(dirname "$$i")"; \
           manbase="$$(basename "$$i" .n)"; \
           mv "$$i" "$${mandir}/$${manbase}.1t"; \
         done)

CONFIGURE_BINDIR.32 =  $(CONFIGURE_PREFIX)/bin/$(MACH32)

CONFIGURE_OPTIONS.64	+= --with-tclsh=$(USRBINDIR64)/tclsh

APPS = dtplite nns nnsd nnslog page pt tcldocstrip

COMPONENT_POST_INSTALL_ACTION += \
        (for app in $(APPS); do \
          $(GSED) -i "s:/usr/bin/env tclsh:$(USRBINDIR.$(BITS))/tclsh:" $(PROTO_DIR)$(USRBINDIR)/$(MACH$(BITS))/$$app; \
        done); \
        $(MV) $(PROTO_DIR)$(USRBINDIR)/$(MACH$(BITS))/{,tcl}page

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/tcl-8
