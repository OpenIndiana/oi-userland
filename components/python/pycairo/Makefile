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
# Copyright 2017 Alexander Pyhalov
#

BUILD_BITS=64
BUILD_STYLE=waf

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pycairo
COMPONENT_VERSION=	1.10.0
COMPONENT_REVISION=	2
COMPONENT_PROJECT_URL=	http://www.cairographics.org
COMPONENT_SUMMARY=	Python bindings for Cairo
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:9aa4078e7eb5be583aeabbe8d87172797717f95e8c4338f0d4a17b683a7253be
COMPONENT_ARCHIVE_URL=	http://cairographics.org/releases/$(COMPONENT_ARCHIVE)

PYTHON_VERSIONS =	3.5

TEST_TARGET=$(NO_TESTS)
include $(WS_MAKE_RULES)/waf.mk

PATH=$(PATH.gnu)

# Trick bundled waf into unpacking itself so we can patch it
COMPONENT_POST_UNPACK_ACTION += \
        (cd $(@D) ; $(PYTHON.64) waf --help >> /dev/null );

CONFIGURE_OPTIONS+=	--nopyo
CONFIGURE_OPTIONS+=	--nopyc
CONFIGURE_ENV+=		PYTHON=$(PYTHON)

# waf picks up the PYTHONDIR & PYTHONARCHDIR settings at configure time,
# but still insists on installing to site-packages instead of vendor-packages
COMPONENT_POST_INSTALL_ACTION += \
	if [ -d  $(PROTO_DIR)/usr/lib/$(MACH64)/python3.5  ]; then \
            $(MKDIR) -p  $(PROTO_DIR)/$(PYTHON_VENDOR_PACKAGES)      ; \
            $(MV) $(PROTO_DIR)/usr/lib/$(MACH64)/python3.5/site-packages/* $(PROTO_DIR)/$(PYTHON_VENDOR_PACKAGES) ; \
	    $(RM) -fr  $(PROTO_DIR)/usr/lib/$(MACH64)/python3.5 ; \
            $(PYTHON) -m compileall $(PROTO_DIR)/$(PYTHON_VENDOR_PACKAGES)/cairo ; \
	fi ;

REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += runtime/python-35
REQUIRED_PACKAGES += system/library
