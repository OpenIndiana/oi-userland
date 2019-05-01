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
# Copyright (c) 2013-2017, Aurelien Larcher. All rights reserved.
# Copyright (c) 2019, Michal Nowak
# 

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         bash-completion
COMPONENT_VERSION=      2.9
COMPONENT_FMRI=         utility/$(COMPONENT_NAME)
COMPONENT_SUMMARY=      Programmable completion functions for bash
COMPONENT_CLASSIFICATION=System/Shells
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=  https://github.com/scop/bash-completion
COMPONENT_ARCHIVE=      $(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.xz
COMPONENT_ARCHIVE_HASH= \
	sha256:d48fe378e731062f479c5f8802ffa9d3c40a275a19e6e0f6f6cc4b90fa12b2f5
COMPONENT_ARCHIVE_URL= \
	https://github.com/scop/bash-completion/releases/download/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=      GPLv2

# Fetch OpenIndiana/openindiana-completions project with
# OpenIndiana-specific bash completions.
COMPONENT_OI_COMPLETIONS_COMMIT=583472062baab7b5981f82c71b0b4dfe47f4d21f
COMPONENT_ARCHIVE_1=		$(COMPONENT_OI_COMPLETIONS_COMMIT).zip
COMPONENT_ARCHIVE_HASH_1=	\
	sha256:cc171ee9eb53d8746aef89f7f2c03ad8bd47592f4585dc247de67832c76c1ffb
COMPONENT_ARCHIVE_URL_1=	\
	https://github.com/OpenIndiana/openindiana-completions/archive/$(COMPONENT_ARCHIVE_1)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_POST_UNPACK_ACTION = ( unzip -jo $(USERLAND_ARCHIVES)$(COMPONENT_ARCHIVE_1) -d $(@D)/completions/ )

# Because of openindiana-completions patch
COMPONENT_PREP_ACTION=	cd $(@D) && autoreconf -fi

CONFIGURE_OPTIONS += --sysconfdir=/etc

build: 		$(BUILD_32)

install: 	$(INSTALL_32)

test: 		$(NO_TESTS)

# Auto-generated dependencies
# NONE
