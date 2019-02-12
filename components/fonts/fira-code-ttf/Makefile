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
# Copyright 2018 Andreas Wacknitz
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=				fira-code-ttf
COMPONENT_SUMMARY=			Monospaced font with programming ligatures
COMPONENT_VERSION= 			1.206
COMPONENT_PROJECT_URL= 		https://github.com/tonsky/FiraCode
COMPONENT_FMRI=				system/font/truetype/fira-code
COMPONENT_CLASSIFICATION=	System/Fonts
COMPONENT_SRC_NAME=			FiraCode
COMPONENT_SRC=				$(COMPONENT_SRC_NAME)_$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      	$(COMPONENT_SRC).zip
COMPONENT_ARCHIVE_URL=	\
	https://github.com/tonsky/FiraCode/releases/download/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= \
    sha256:433e9e059e53ae1e94c674819b73e49d65bd76e3c6ec70f42d2324062ea3210b
COMPONENT_LICENSE=			FiraCode License
COMPONENT_LICENSE_FILE=		fira-code.license

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

# doesn't extract into its own directory, so pass -r dir to the unpack target
UNPACK_ARGS+=-r $(COMPONENT_SRC)

FONT_TTF_DIR=/usr/share/fonts/TrueType
THIS_FONT_DIR=$(FONT_TTF_DIR)/fira-code

COMPONENT_BUILD_ACTION= cd $(@D)/ttf ; mkfontscale ; mkfontdir

COMPONENT_INSTALL_ACTION= cd $(@D) && \
	rm -rf $(PROTO_DIR)$(THIS_FONT_DIR) && mkdir -p $(PROTO_DIR)$(THIS_FONT_DIR) && \
		$(INSTALL) -c -m 0444 ttf/*.ttf ttf/fonts.dir ttf/fonts.scale $(PROTO_DIR)$(THIS_FONT_DIR);

build: $(BUILD_32)

install: $(INSTALL_32)

test: $(NO_TESTS)

REQUIRED_PACKAGES+= x11/mkfontdir
REQUIRED_PACKAGES+= x11/mkfontscale
