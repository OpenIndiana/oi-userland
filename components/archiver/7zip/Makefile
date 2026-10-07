#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#

#
# Copyright (c) 2011, 2025, Oracle and/or its affiliates.
#

BUILD_STYLE= justmake
ENV=/usr/bin/env

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         7zip
COMPONENT_VERSION=	26.4
HUMAN_VERSION=		26.04
COMPONENT_SUMMARY=      File archiver for extremely high compression
COMPONENT_PROJECT_URL=  https://www.7-zip.org
COMPONENT_SRC=          $(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE=      $(HUMAN_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:48fdc6dfe879ee2db867bb07f19c4a9406bfea01d51f48785b6c7a137881e25c
COMPONENT_ARCHIVE_URL=	https://github.com/ip7z/7zip/archive/refs/tags/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         compress/7zip
COMPONENT_CLASSIFICATION= Applications/System Utilities
COMPONENT_LICENSE=      LGPL-2.1-or-later, BSD-3-Clause, LicenseRef-UnRAR
COMPONENT_LICENSE_FILE= 7zip.license

include $(WS_MAKE_RULES)/common.mk

COMPONENT_BUILD_ARGS += -f ../../cmpl_gcc.mak

COMPONENT_BUILD_ACTION = \
        cd $(@D)/CPP/7zip/Bundles/Alone2; $(ENV) $(COMPONENT_BUILD_ENV) \
        $(GMAKE) $(COMPONENT_BUILD_ARGS) $(COMPONENT_BUILD_TARGETS)

PROTODOC=$(PROTOUSRSHAREDOCDIR)/7zip 
STRIP=strip

COMPONENT_INSTALL_ACTION = \
        $(MKDIR) $(PROTOUSRBINDIR) $(PROTOUSRSHAREMAN1DIR) $(PROTODOC) ; \
	$(INSTALL) $(@D)/CPP/7zip/Bundles/Alone2/b/g/7zz $(PROTOUSRBINDIR)/7zz ; \
	$(STRIP) $(PROTOUSRBINDIR)/7zz ; \
	$(INSTALL) -m 444 $(@D)/DOC/7zC.txt $(PROTODOC) ; \
	$(INSTALL) -m 444 $(@D)/DOC/7zFormat.txt $(PROTODOC) ; \
	$(INSTALL) -m 444 $(@D)/DOC/License.txt $(PROTODOC) ; \
	$(INSTALL) -m 444 $(@D)/DOC/Methods.txt $(PROTODOC) ; \
	$(INSTALL) -m 444 $(@D)/DOC/copying.txt $(PROTODOC) ; \
	$(INSTALL) -m 444 $(@D)/DOC/lzma.txt $(PROTODOC) ; \
	$(INSTALL) -m 444 $(@D)/DOC/readme.txt $(PROTODOC) ; \
	$(INSTALL) -m 444 $(@D)/DOC/src-history.txt $(PROTODOC) ; \
	$(INSTALL) -m 444 $(@D)/DOC/unRarLicense.txt $(PROTODOC) ; \
	$(INSTALL) -m 444 files/7zz.1 $(PROTOUSRSHAREMAN1DIR)/7zz.1 ;

# No tests. p7zip tests can be used eventually with 7-Zip binary.
test:	$(NO_TESTS)
system-test:	$(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
