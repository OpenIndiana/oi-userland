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
# Copyright 2018 Michal Nowak
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=	Hack
# Both COMPONENT_VERSION and IPS_COMPONENT_VERSION are derived from this
COMPONENT_VERSION= 3.003
# remove leading 0s in any part of the version.
IPS_COMPONENT_VERSION= $(shell echo $(COMPONENT_VERSION) | sed -e 's/\.0*\([1-9]\)/.\1/')
COMPONENT_SUMMARY= Hack, a typeface designed for source code
COMPONENT_PROJECT_URL= https://sourcefoundry.org/hack/
COMPONENT_FMRI=		system/font/truetype/hack
COMPONENT_CLASSIFICATION=	System/Fonts
COMPONENT_SRC=		$(COMPONENT_NAME)-$(IPS_COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_NAME)-v$(COMPONENT_VERSION)-ttf.tar.xz
COMPONENT_ARCHIVE_URL=	\
	https://github.com/chrissimpkins/Hack/releases/download/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= \
  sha256:d9ed5d0a07525c7e7bd587b4364e4bc41021dd668658d09864453d9bb374a78d
COMPONENT_LICENSE=	MIT, BitStream Vera Font License
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
