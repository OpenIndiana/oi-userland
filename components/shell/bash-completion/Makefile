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
COMPONENT_VERSION=      2.18.0
COMPONENT_SUMMARY=      Programmable completion functions for bash
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=  https://github.com/scop/bash-completion
COMPONENT_ARCHIVE=      $(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:88bcf85124f77f74f2f2f8bcd16ac4382d807a827ede742a64940c7116aea33f
COMPONENT_ARCHIVE_URL=	https://github.com/scop/bash-completion/releases/download/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         utility/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=System/Shells
COMPONENT_LICENSE=      GPLv2
COMPONENT_LICENSE_FILE= COPYING

# Fetch OpenIndiana/openindiana-completions project with
# OpenIndiana-specific bash completions.
COMPONENT_OI_COMPLETIONS_COMMIT=716e387d3ad13bb01eba7ab3a8a80ac1ab7f2551
COMPONENT_ARCHIVE_1=		$(COMPONENT_OI_COMPLETIONS_COMMIT).zip
COMPONENT_ARCHIVE_HASH_1=	sha256:ab0c707374ac42cb2934bb6675b37ba4bc4199917c34c1b0fd937859e885e36d
COMPONENT_ARCHIVE_URL_1=	https://github.com/OpenIndiana/openindiana-completions/archive/$(COMPONENT_ARCHIVE_1)

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_POST_UNPACK_ACTION+= ( unzip $(USERLAND_ARCHIVES)$(COMPONENT_ARCHIVE_1) -d $(COMPONENT_DIR)/ );
COMPONENT_POST_UNPACK_ACTION+= ( cd $(COMPONENT_DIR)/openindiana-completions-$(COMPONENT_OI_COMPLETIONS_COMMIT); \
			       find completions/* | cpio -pmdv $(@D)/ ; \
			       find startup/* | cpio -pmdv $(@D)/ ; \
			       );

# Because of openindiana-completions patch
COMPONENT_PREP_ACTION += cd $(@D) && $(ENV) autoreconf -fi ;

# Auto-generated dependencies
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += text/gnu-grep
REQUIRED_PACKAGES += text/gnu-sed
