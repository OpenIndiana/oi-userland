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
# Copyright 2023 Friedrich Kink
#

BUILD_BITS= 64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=	Zarith
COMPONENT_VERSION=	1.12
COMPONENT_SUMMARY=	The Zarith library - This library implements arithmetic and logical operations over arbitrary-precision integers.
COMPONENT_PROJECT_URL=	https://github.com/ocaml/Zarith
COMPONENT_FMRI=	library/ocaml/Zarith
COMPONENT_CLASSIFICATION= Development/Other Languages
COMPONENT_SRC=		$(COMPONENT_NAME)-release-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_URL=	https://github.com/ocaml/Zarith/archive/refs/tags/release-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:cc32563c3845c86d0f609c86d83bf8607ef12354863d31d3bffc0dacf1ed2881
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE= LICENSE

include $(WS_MAKE_RULES)/common.mk
include $(WS_MAKE_RULES)/ocaml.mk

PATH=$(PATH.gnu)

COMPONENT_PRE_CONFIGURE_ACTION  +=  $(CLONEY) $(SOURCE_DIR) $(@D) ;

CONFIGURE_OPTIONS=	-installdir $(PROTO_DIR)/usr/lib/$(MACH64)/ocaml
CONFIGURE_OPTIONS+=	-ocamllibdir /usr/lib/$(MACH64)/ocaml

COMPONENT_TEST_DIR =  $(@D)/tests
COMPONENT_TEST_TARGETS = test
COMPONENT_TEST_TRANSFORMS = \
        '-n ' \
        '-e "/ passed$$/p" '


# Auto-generated dependencies
REQUIRED_PACKAGES += library/gmp
REQUIRED_PACKAGES += runtime/ocaml
REQUIRED_PACKAGES += system/library
