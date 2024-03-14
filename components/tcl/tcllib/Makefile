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
# Copyright (c) 2023, Klaus Ziegler
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		tcllib
COMPONENT_VERSION=	1.21
COMPONENT_REVISION=	2
COMPONENT_PROJECT_URL=	https://core.tcl.tk/tcllib/doc/trunk/embedded/index.html
COMPONENT_SUMMARY=	The standard Tcl library
COMPONENT_FMRI=		tcl/tcllib
COMPONENT_CLASSIFICATION=       Development/Other Languages
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:10c7749e30fdd6092251930e8a1aa289b193a3b7f1abf17fee1d4fa89814762f
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

APPS = dtplite nns nnsd nnslog page pt tcldocstrip

# Fix invocation in scripts and rename page to tclpage because of a name clash with a file from SUNWcs:
COMPONENT_POST_INSTALL_ACTION += \
        (for app in $(APPS); do \
          $(GSED) -i "s:/usr/bin/env tclsh:$(USRBINDIR)/tclsh:" $(PROTO_DIR)$(USRBINDIR)/$$app; \
        done); \
		$(MV) $(PROTO_DIR)$(USRBINDIR)/{,tcl}page

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/tcl-8
REQUIRED_PACKAGES += shell/ksh93
