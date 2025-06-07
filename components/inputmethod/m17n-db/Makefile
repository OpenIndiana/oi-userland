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
# Copyright 2025 Jiwon Na
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=           m17n-db
COMPONENT_VERSION=        1.8.10
COMPONENT_SUMMARY=        m17n-db - The data files for m17n
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=        $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=   sha256:31024e0513533448b9b31ea3294d35a6426e6690eb44628680731aa955c0c16c
COMPONENT_ARCHIVE_URL=    https://download.savannah.nongnu.org/releases/m17n/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=           system/input-method/library/m17n/db
COMPONENT_CLASSIFICATION= System/Localizations
COMPONENT_LICENSE=        LGPLv2.1
COMPONENT_LICENSE_FILE=   COPYING
COMPONENT_PROJECT_URL=    https://www.nongnu.org/m17n/


#m17db requires charmap from glibc
COMPONENT_NAME_1= glibc
COMPONENT_VERSION_1= 2.41
COMPONENT_SRC_1= $(COMPONENT_NAME_1)-$(COMPONENT_VERSION_1)
COMPONENT_ARCHIVE_1= $(COMPONENT_SRC_1).tar.bz2
COMPONENT_ARCHIVE_URL_1= https://ftp.gnu.org/gnu/glibc/$(COMPONENT_ARCHIVE_1)
COMPONENT_ARCHIVE_HASH_1= sha256:13cffc682feef721d575250bd4845f92950d3aab23c471279c0f70e497b08442
COMPONENT_SRC_GLIBC= $(COMPONENT_SRC_1)
COMPONENT_LICENSE_1=	LGPLv2.1

CONFIGURE_OPTIONS  = --with-charmaps=$(COMPONENT_DIR)/$(COMPONENT_SRC_GLIBC)/localedata/charmaps

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

COMPONENT_PRE_CONFIGURE_ACTION= ( $(CLONEY) $(SOURCE_DIR) $(@D) )

# Auto-generated dependencies
REQUIRED_PACKAGES += shell/ksh93
