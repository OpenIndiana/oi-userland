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
# Copyright (c) 2020, Michal Nowak
# Copyright (c) 2021, Nona Hansel
# 

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         bash-completion
COMPONENT_VERSION=      2.16.0
COMPONENT_REVISION=	1
COMPONENT_SUMMARY=      Programmable completion functions for bash
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=  https://github.com/scop/bash-completion
COMPONENT_ARCHIVE=      $(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:3369bd5e418a75fb990863925aed5b420398acebb320ec4c0306b3eae23f107a
COMPONENT_ARCHIVE_URL=	https://github.com/scop/bash-completion/releases/download/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         utility/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=System/Shells
COMPONENT_LICENSE=      GPLv2
COMPONENT_LICENSE_FILE= COPYING

# Fetch OpenIndiana/openindiana-completions project with
# OpenIndiana-specific bash completions.
COMPONENT_OI_COMPLETIONS_COMMIT=a3bf8152286ea1156866f81b53ac943d8ace25ea
COMPONENT_ARCHIVE_1=		$(COMPONENT_OI_COMPLETIONS_COMMIT).zip
COMPONENT_ARCHIVE_HASH_1=	sha256:a62a1d76cc08b13094fb38789683ec6bb885283199fbb539146e11429798a68a
COMPONENT_ARCHIVE_URL_1=	https://github.com/OpenIndiana/openindiana-completions/archive/$(COMPONENT_ARCHIVE_1)

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_POST_UNPACK_ACTION= ( unzip -jo $(USERLAND_ARCHIVES)$(COMPONENT_ARCHIVE_1) -d $(@D)/completions/ )

# Because of openindiana-completions patch
COMPONENT_PREP_ACTION += cd $(@D) && $(ENV) autoreconf -fi ;

# Auto-generated dependencies
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += text/gnu-grep
REQUIRED_PACKAGES += text/gnu-sed
