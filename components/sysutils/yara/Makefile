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
# Copyright 2022, Friedrich Kink. All rights reserved.
#

BUILD_BITS= 64
USE_OPENSSL11= yes
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		yara
COMPONENT_VERSION=	4.3.2
COMPONENT_SUMMARY=	YARA is a tool aimed at (but not limited to) helping malware \
	researchers to identify and classify malware samples.
COMPONENT_DESCRIPTION=	With YARA you can create descriptions of malware families \
	(or whatever you want to describe) based on textual or binary patterns. Each \
	description, a.k.a rule, consists of a set of strings and a boolean expression \
	which determine its logic.
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	v$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:a9587a813dc00ac8cdcfd6646d7f1c172f730cda8046ce849dfea7d3f6600b15
COMPONENT_PROJECT_URL=	https://virustotal.github.io/yara/
COMPONENT_ARCHIVE_URL=	https://github.com/VirusTotal/yara/archive/refs/tags/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI= 	antivirus/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	Applications/System Utilities
COMPONENT_LICENSE=	BSD-3-Clause
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PRE_CONFIGURE_ACTION += ( \
	cd $(SOURCE_DIR); \
	./bootstrap.sh; \
	$(CLONEY) $(SOURCE_DIR) $(@D); \
	)

CFLAGS += $(CPP_LARGEFILES) -I$(OPENSSL_INCDIR)

LDFLAGS += -L$(OPENSSL_LIBDIR)

CONFIGURE_OPTION+=	--enable-cuckoo
CONFIGURE_OPTION+=	--enable-magic
CONFIGURE_OPTION+=	--enable-macho
CONFIGURE_OPTION+=	--enable-dex
CONFIGURE_OPTION+=	--enable-pb-tests

# Auto-generated dependencies
REQUIRED_PACKAGES += library/security/openssl-11
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
