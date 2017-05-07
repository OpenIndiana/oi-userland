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
# Copyright 2016 Tim Mooney <Timothy.V.Mooney@gmail.com>
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=	Hack
# Both COMPONENT_VERSION and IPS_COMPONENT_VERSION are derived from this
COMPONENT_FILE_VERSION= 2_020
# transform _ in upstream version to .
COMPONENT_VERSION=$(shell echo $(COMPONENT_FILE_VERSION) | sed -e 's/_/./g')
# remove leading 0s in any part of the version.
IPS_COMPONENT_VERSION= $(shell echo $(COMPONENT_VERSION) | sed -e 's/\.0*\([1-9]\)/.\1/')
COMPONENT_SUMMARY= Hack, a typeface designed for source code
COMPONENT_PROJECT_URL= http://sourcefoundry.org/hack/
COMPONENT_FMRI=		system/font/truetype/hack
COMPONENT_CLASSIFICATION=	System/Fonts
COMPONENT_SRC=		$(COMPONENT_NAME)-$(IPS_COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_NAME)-v$(COMPONENT_FILE_VERSION)-ttf.zip
COMPONENT_ARCHIVE_URL=	\
	https://github.com/chrissimpkins/Hack/releases/download/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= \
  sha256:048566ae79c580f725b68340d9d2a3b0fa125fb08c1d30cf0a7c327d07ab739a
COMPONENT_LICENSE=	Hack Open Font License Version 2.0, BitStream Vera Font License
COMPONENT_LICENSE_FILE=	hack.license

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/justmake.mk
include $(WS_TOP)/make-rules/ips.mk

# doesn't extract into its own directory, so pass -r dir to the unpack target
UNPACK_ARGS+=-r $(COMPONENT_SRC)

FONT_TTF_DIR=/usr/share/fonts/TrueType
THIS_FONT_DIR=$(FONT_TTF_DIR)/hack

COMPONENT_BUILD_ACTION= cd $(@D) ; mkfontscale ; mkfontdir

COMPONENT_INSTALL_ACTION= cd $(@D) && \
	rm -rf $(PROTO_DIR)$(THIS_FONT_DIR) && mkdir -p $(PROTO_DIR)$(THIS_FONT_DIR) && \
		$(INSTALL) -c -m 0444 *.ttf fonts.dir fonts.scale $(PROTO_DIR)$(THIS_FONT_DIR);

build: $(BUILD_32)

install: $(INSTALL_32)

test: $(NO_TESTS)

REQUIRED_PACKAGES+= x11/mkfontdir
REQUIRED_PACKAGES+= x11/mkfontscale
