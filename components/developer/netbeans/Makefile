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
# Copyright 2017 Jim Klimov
# Copyright 2013 Andrzej Szeszo (this recipe uses parts of studio-netbeans.p5m)
#

include ../../../make-rules/shared-macros.mk

# Download pages for nightly builds and final releases of "OS Independent ZIP":
#   http://bits.netbeans.org/dev/nightly/latest/start.html?platform=zip&lang=en&option=all
#   https://netbeans.org/downloads/start.html?platform=zip&lang=en&option=all

COMPONENT_NAME=		netbeans
COMPONENT_MAJOR_VERSION=	8
COMPONENT_MINOR_VERSION=	2
COMPONENT_PATCH_VERSION=	0
NETBEANS_RELEASE=	final
NETBEANS_TIMESTAMP=	201609300101

# Remote files for initial version do not include trailing ".0", we do
# Add suffix to initial releases, like "8.2": rename into "8.2.0"
# but keep subsequent ones intact like "8.2.1"
COMPONENT_VERSION=	$(COMPONENT_MAJOR_VERSION).$(COMPONENT_MINOR_VERSION).$(COMPONENT_PATCH_VERSION)
ifeq ($(strip $(COMPONENT_PATCH_VERSION)),0)
COMPONENT_SOURCE_VERSION=$(COMPONENT_MAJOR_VERSION).$(COMPONENT_MINOR_VERSION)
else
COMPONENT_SOURCE_VERSION=$(COMPONENT_MAJOR_VERSION).$(COMPONENT_MINOR_VERSION).$(COMPONENT_PATCH_VERSION)
endif

# Local filename including trailing ".0" if needed
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(COMPONENT_VERSION)-$(NETBEANS_TIMESTAMP).zip
# Local dir
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)-$(NETBEANS_TIMESTAMP)
# Remote filename might avoid trailing ".0"
COMPONENT_ARCHIVE_URL=\
	http://download.netbeans.org/netbeans/$(COMPONENT_SOURCE_VERSION)/final/zip/netbeans-$(COMPONENT_SOURCE_VERSION)-$(NETBEANS_TIMESTAMP).zip
### Sample URLs for different downloadable variants:
#	http://download.netbeans.org/netbeans/8.2/final/zip/netbeans-8.2-201609300101.zip
#	http://bits.netbeans.org/dev/nightly/latest/zip/netbeans-trunk-nightly-201707240001.zip
#	http://bits.netbeans.org/dev/nightly/2017-07-24_00-01-25/zip/netbeans-trunk-nightly-201707240001.zip
COMPONENT_ARCHIVE_HASH=	\
	sha256:ad9888334b9a6c1f1138dcb2eccc8ce4921463e871e46def4ecc617538160948

COMPONENT_PROJECT_URL=	https://netbeans.org/
COMPONENT_FMRI=		developer/$(COMPONENT_NAME)
COMPONENT_LICENSE=		GPLv2,CDDL
COMPONENT_LICENSE_FILE= netbeans.license
COMPONENT_SUMMARY=	Netbeans is an IDE with support for many languages and multihost development

# Note: we only download a ZIP - no unpacking via fetcher, no building...
include $(WS_MAKE_RULES)/prep-download.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

CLEAN_PATHS += $(SOURCE_DIR)

download::

$(SOURCE_DIR)/.prep:    download
	$(COMPONENT_PREP_ACTION)
	$(TOUCH) $@

prep::  $(SOURCE_DIR)/.prep

clean::
	$(PRE_CLEAN_ACTION)
	$(RM) -r $(CLEAN_PATHS)

clobber::   clean
	$(RM) -r $(CLOBBER_PATHS)

COMPONENT_PREP_ACTION = ( $(MKDIR) $(@D)/ && ln -sfr $(USERLAND_ARCHIVES)/$(COMPONENT_ARCHIVE) $(COMPONENT_DIR)/files/Makefile $(@D)/ )

# This, and the symlinks in the custom Makefile, save quite a bit
# of storage overhead (do not need to copy the ZIP 3 extra times)
COMPONENT_COPY_ACTION = ( $(CLONEY) $(SOURCE_DIR)/ $(@D)/ )

COMPONENT_INSTALL_ENV += NETBEANS_VERSION=$(COMPONENT_VERSION)
COMPONENT_INSTALL_ENV += NETBEANS_RELEASE=$(NETBEANS_RELEASE)
COMPONENT_INSTALL_ENV += COMPONENT_ARCHIVE=$(SOURCE_DIR)/$(COMPONENT_ARCHIVE)

build: $(BUILD_32)

install: $(INSTALL_32)

test: $(NO_TESTS)

# Note: this recipe just downloads and packages stuff.
# No real build, no magic tools, no java even, should be needed!
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
