#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2011, Andrzej Szeszo
# Copyright 2011, Alasdair Lumsden <alasdairrr@gmail.com>
# Copyright 2012, Piotr Jasiukajtis
# Copyright 2012, Jon Tibble
# Copyright 2018, Michal Nowak
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		illumos-kvm
COMPONENT_VERSION=	a82c4d2a9555461ee43e3fd3b6bbff10e6f5458a
IPS_COMPONENT_VERSION=	0.0.1.20220127
COMPONENT_SRC=		illumos-kvm-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).zip
COMPONENT_ARCHIVE_HASH=	sha256:e1875c8b284683e4470554f7b3be6262e6178143d58827bb2367669a03872721
COMPONENT_ARCHIVE_URL=	https://github.com/joyent/illumos-kvm/archive/$(COMPONENT_VERSION).zip

ifeq ($(MACH), sparc)
PUBLISH_STAMP=
endif

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/justmake.mk
include $(WS_TOP)/make-rules/ips.mk

COMPONENT_PRE_CONFIGURE_ACTION = \
	$(CLONEY) $(SOURCE_DIR) $(@D)

COMPONENT_BUILD_ARGS += KERNEL_SOURCE=$(WS_TOP)/components/openindiana/illumos-gate/illumos-gate/

COMPONENT_INSTALL_ARGS += DESTDIR=$(PROTO_DIR)

build_sparc:
	@echo "Not available."

$(BUILD_32):: $(WS_TOP)/components/openindiana/illumos-gate/build/i386/.built

$(WS_TOP)/components/openindiana/illumos-gate/build/i386/.built:
	$(GMAKE) -C $(WS_TOP)/components/openindiana/illumos-gate  build


build_i386:	$(BUILD_32)

build:		build_$(MACH)

install_sparc:
	@echo "Not available."

install_i386:	$(INSTALL_32)

install:	install_$(MACH)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
