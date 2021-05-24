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

BUILD_BITS= 32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		tcllib
COMPONENT_VERSION=	1.20
COMPONENT_PROJECT_URL=	https://core.tcl.tk/tcllib/doc/trunk/embedded/index.html
COMPONENT_SUMMARY=	The standard Tcl library
COMPONENT_FMRI=		tcl/tcllib
COMPONENT_CLASSIFICATION=       Development/Other Languages
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:199e8ec7ee26220e8463bc84dd55c44965fc8ef4d4ac6e4684b2b1c03b1bd5b9
COMPONENT_ARCHIVE_URL=	https://core.tcl.tk/tcllib/uv/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	TCL
COMPONENT_LICENSE_FILE=	license.terms

include $(WS_MAKE_RULES)/common.mk

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

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/tcl-8
