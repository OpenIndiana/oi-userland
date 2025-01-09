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
# Copyright 2016 Alexander Pyhalov
# 

USE_DEFAULT_TEST_TRANSFORMS = yes

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= 	xmlto
COMPONENT_VERSION= 	0.0.29
COMPONENT_SUMMARY= 	xmlto is a shell-script tool for converting XML files to various formats
COMPONENT_SRC= 		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= 	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:40504db68718385a4eaa9154a28f59e51e59d006d1aa14f5bc9d6fded1d6017a
COMPONENT_ARCHIVE_URL=	https://pagure.io/xmlto/archive/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://pagure.io/xmlto
COMPONENT_FMRI=	text/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	System/Text Tools
COMPONENT_LICENSE=	GPL-2.0-only
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

# We need to bootstrap the project
COMPONENT_PREP_ACTION += ( cd $(@D) && $(ENV) autoreconf -fi ) ;

# Make sure that configure finds the GNU variants:
CONFIGURE_ENV += BASH=/usr/bin/bash
CONFIGURE_ENV += CP=/usr/bin/gcp
CONFIGURE_ENV += FIND=/usr/bin/gfind
CONFIGURE_ENV += GETOPT=/usr/gnu/bin/getopt
CONFIGURE_ENV += GREP=/usr/bin/ggrep
CONFIGURE_ENV += SED=/usr/bin/gsed

# Auto-generated dependencies
REQUIRED_PACKAGES += file/gnu-coreutils
REQUIRED_PACKAGES += file/gnu-findutils
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/libxslt
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += shell/gnu-getopt
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += text/gnu-grep
REQUIRED_PACKAGES += web/browser/lynx
