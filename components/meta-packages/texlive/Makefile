#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2021 David Stes. All rights reserved.
#
# Package for building TeX Live using the TUG install-tl script
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		texlive
COMPONENT_FMRI=		meta-packages/texlive
COMPONENT_VERSION=	1.0
COMPONENT_REVISION=	1
COMPONENT_SUMMARY=	Metapackage for the TeX typesetting system
COMPONENT_CLASSIFICATION=	Meta Packages/Builds
COMPONENT_SRC=          install-tl-20210128
COMPONENT_ARCHIVE=      install-tl-unx.tar.gz
CTAN_URL=               http://mirror.ctan.org/systems/texlive
COMPONENT_PROJECT_URL=  https://tug.org/texlive/
COMPONENT_ARCHIVE_URL=  $(CTAN_URL)/tlnet/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=      TL
COMPONENT_LICENSE_FILE= LICENSE.TL
COMPONENT_ARCHIVE_HASH= \
	sha256:bf40985138bfa8a77623c3ded3ce2260419727a9d0adeeeb93536226efd37421

include ../../../make-rules/prep.mk
include ../../../make-rules/ips.mk

PKGLINT=/bin/true

# the install-tl scripts are just scripts, there is no build
# we install the scripts under /usr/share/install-tl-<version>

# no-op
$(BUILD_DIR)/%/.built:  $(SOURCE_DIR)/.prep
	$(RM) -r $(@D) ; $(MKDIR) $(@D)

build: $(BUILD_DIR)/%/.built

# install the source into the proto directory
$(BUILD_DIR)/%/.installed:      $(BUILD_DIR)/%/.built
	$(MKDIR) -p $(PROTO_DIR)$(USRSHAREDIR)
	$(CP) -r $(SOURCE_DIR) $(PROTO_DIR)$(USRSHAREDIR)

install: $(BUILD_DIR)/%/.installed

clean::
	$(RM) -r $(SOURCE_DIR) $(BUILD_DIR)

