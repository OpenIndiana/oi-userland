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
# Copyright (c) 2009, 2018, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2018, Aurelien Larcher. All rights reserved.
#
BUILD_BITS  ?= NO_ARCH
BUILD_STYLE ?= archive

ifneq ($(findstring X11,$(FONT_TYPE)),)
X11_CATEGORY = FONT
include $(WS_MAKE_RULES)/x11.mk
endif

include $(WS_MAKE_RULES)/common.mk

MKFONTSCALE = mkfontscale
MKFONTDIR = mkfontdir

ETCFONTSDIR = $(ETCDIR)/fonts
ETCFONTSCONFDIR = $(ETCFONTSDIR)/conf.avail
USRSHAREFONTSDIR = $(USRSHAREDIR)/fonts

#
# Font type macros 
#

TTFFONTDIR     = TrueType
OTFFONTDIR     = OpenType
X11FONTDIR     = X11
X11MISCFONTDIR = X11
PKGFONTDIR?= $($(FONT_TYPE)FONTDIR)

# For compatibility
USRSHARETTFFONTSDIR = $(USRSHAREFONTSDIR)/$(TTFFONTDIR)
USRSHAREOTFFONTSDIR = $(USRSHAREFONTSDIR)/$(OTFFONTDIR)
USRSHAREX11FONTSDIR = $(USRSHAREFONTSDIR)/$(X11FONTDIR)

TTFFONTSRC     = ttf
OTFFONTSRC     = otf
X11FONTSRC     =
X11MISCFONTSRC =
PKGFONTSRC?= $($(FONT_TYPE)FONTSRC)

TTFFONTCLS     = truetype
OTFFONTCLS     = opentype
X11FONTCLS     = xorg
X11MISCFONTCLS =
PKGFONTCLS?= $($(FONT_TYPE)FONTCLS)

TTFFONTEXT     = *.ttc *.tte *.ttf
OTFFONTEXT     = *.otf *.otc *.ttf *.ttc
X11FONTEXT     = *.pcf
X11MISCFONTEXT = *.pcf
PKGFONTEXT?= $($(FONT_TYPE)FONTEXT)

PKGFONTCONFSRC = fontconfig
PKGFONTCONFEXT = *.conf

#
# Proto area directories
#

PROTOFONTSDIR = $(PROTO_DIR)$(USRSHAREFONTSDIR)
PROTOTTFFONTSDIR = $(PROTOFONTSDIR)/$(TTFFONTDIR)
PROTOOTFFONTSDIR = $(PROTOFONTSDIR)/$(OTFFONTDIR)
PROTOX11FONTSDIR = $(PROTOFONTSDIR)/$(X11FONTDIR)
PROTOPKGFONTSDIR = $(PROTO$(FONT_TYPE)FONTSDIR)

PROTOFONTSCONFDIR = $(PROTO_DIR)$(ETCFONTSCONFDIR)

#
# Default macros 
#

COMPONENT_FONT_TYPE = $(PKGFONTCLS)
COMPONENT_FONT_NAME = $(COMPONENT_NAME)
COMPONENT_FONT_PKG  = $(COMPONENT_NAME)
ifeq ($(strip $(COMPONENT_FONT_TYPE)),)
COMPONENT_FMRI ?= \
  system/font/$(strip $(COMPONENT_FONT_PKG))
else
COMPONENT_FMRI ?= \
  system/font/$(strip $(COMPONENT_FONT_TYPE))/$(strip $(COMPONENT_FONT_PKG))
endif
COMPONENT_CLASSIFICATION = System/Fonts
COMPONENT_CATEGORY = font 

COMPONENT_FONT_DEST_DIR?= $(USRSHAREFONTSDIR)/$(PKGFONTDIR)/$(COMPONENT_FONT_NAME)
COMPONENT_FONT_SRC_DIR ?= $(PKGFONTSRC)
COMPONENT_FONT_FILES    =

COMPONENT_FONTCONF_DEST_DIR?= $(ETCFONTSCONFDIR)
COMPONENT_FONTCONF_SRC_DIR ?= $(PKGFONTCONFSRC)
COMPONENT_FONTCONF_FILES    = $(PKGFONTCONFEXT)

#
# Build style specific rules
#

ifeq ($(strip $(BUILD_STYLE)),archive)

POST_INSTALL_MKFONT?=no 

COMPONENT_BUILD_ACTION?= true
ifeq ($(strip $(POST_INSTALL_MKFONT)),no)
COMPONENT_BUILD_ACTION = \
  cd $(@D)/$(COMPONENT_FONT_SRC_DIR); $(MKFONTSCALE); $(MKFONTDIR);
endif

$(BUILD_DIR)/%/.built: $(SOURCE_DIR)/.prep
	($(RM) -rf $(@D) ; $(MKDIR) $(@D))
	$(ENV) $(CLONEY_ARGS) $(CLONEY) $(SOURCE_DIR) $(@D)
	$(COMPONENT_PRE_BUILD_ACTION)
	($(COMPONENT_BUILD_ACTION))
	$(COMPONENT_POST_BUILD_ACTION)
	$(TOUCH) $@

build: $(BUILD_$(MK_BITS))

COMPONENT_FONT_POST_INSTALL_ACTION = \
  ( $(MKFONTSCALE) $(PROTO_DIR)$(COMPONENT_FONT_DEST_DIR); \
    $(MKFONTDIR) $(PROTO_DIR)$(COMPONENT_FONT_DEST_DIR) )

ifeq ($(strip $(POST_INSTALL_MKFONT)),yes)
COMPONENT_POST_INSTALL_ACTION+=$(COMPONENT_FONT_POST_INSTALL_ACTION)
else
COMPONENT_FONT_FILES += fonts.dir
COMPONENT_FONT_FILES += fonts.scale
endif

COMPONENT_INSTALL_ACTION = \
  cd $(@D)/$(COMPONENT_FONT_SRC_DIR) && \
    $(INSTALL) -m 0444 $(COMPONENT_FONT_FILES) \
      $(PROTO_DIR)$(COMPONENT_FONT_DEST_DIR) ; \
  if [ -n "$(strip $(COMPONENT_FONTCONF_FILES))" ]; \
  then \
    cd $(@D)/$(COMPONENT_FONTCONF_SRC_DIR) && \
      $(INSTALL) -m 0444 $(COMPONENT_FONTCONF_FILES) \
        $(PROTO_DIR)$(COMPONENT_FONTCONF_DEST_DIR) ; \
  fi;

$(BUILD_DIR)/%/.installed: $(BUILD_DIR)/%/.built
	$(MKDIR) $(@D)
	$(COMPONENT_PRE_INSTALL_ACTION)
	-$(RM) -r $(PROTO_DIR)$(COMPONENT_FONT_DEST_DIR)
	$(MKDIR) $(PROTO_DIR)$(COMPONENT_FONT_DEST_DIR)
	$(MKDIR) $(PROTO_DIR)$(COMPONENT_FONTCONF_DEST_DIR)
	($(COMPONENT_INSTALL_ACTION))
	$(COMPONENT_POST_INSTALL_ACTION)
	$(TOUCH) $@

install: $(INSTALL_$(MK_BITS))

clean::
	$(RM) -r $(BUILD_DIR) $(PROTO_DIR)

endif

ifeq ($(strip $(BUILD_STYLE)),configure)
# We don't compress individual font files so that we get better compression
# at higher levels in ZFS & IPS, and so that we aren't constantly replacing
# font files in every build just because the timestamp in the compressed
# version changed.
CONFIGURE_OPTIONS += --without-compression
endif

# Add font metadata to packages to make it easier to search for fonts
$(CANONICAL_MANIFESTS:%.p5m=$(MANIFEST_BASE)-%.mogrified): PUBLISH_TRANSFORMS += $(@:.mogrified=.font-transforms)

$(CANONICAL_MANIFESTS:%.p5m=$(MANIFEST_BASE)-%.mogrified): font-transforms
font-transforms: $(CANONICAL_MANIFESTS:%.p5m=$(MANIFEST_BASE)-%.font-transforms)

$(MANIFEST_BASE)-%.font-transforms: %.p5m
	$(PERL) $(WS_TOOLS)/generate_font_metadata.pl \
	-p $(PROTO_DIR) -m $< > $@ || ( rm $@ ; exit 1 )

# Package containing fc-scan used in generate_font_metadata.pl
USERLAND_REQUIRED_PACKAGES += system/library/fontconfig
# Package containing $(MKFONTSCALE) & $(MKFONTDIR)
USERLAND_REQUIRED_PACKAGES += x11/font-utilities

