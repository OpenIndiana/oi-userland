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
# Copyright 2015 Aurelien Larcher
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=           xorg-docs
COMPONENT_VERSION=        1.7.1
COMPONENT_FMRI=           x11/documentation/xorg-docs
COMPONENT_CLASSIFICATION= System/X11
COMPONENT_SUMMARY=  X.Org documentation for the X Window System
COMPONENT_SRC=      $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=  $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:24b8677c3462c10465cf50d40576d76682acd5835526093a575865b2aa242c4b
COMPONENT_ARCHIVE_URL= \
  https://www.x.org/releases/individual/doc/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = https://www.x.org/
COMPONENT_LICENSE=      MIT License
COMPONENT_LICENSE_FILE= xorg-docs.license

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin

X11_DOC_DIR=$(USRSHAREDOCDIR)/X11
X11_SGML_DIR=$(USRSHAREDIR)/sgml

COMPONENT_PREP_ACTION= \
	find $(@D) -name '*.xml' | xargs $(PERL) -i.orig -p -e \
	 's{SYSTEM ".*/X11/defs.ent"}{SYSTEM "$(X11_SGML_DIR)/X11/defs.ent"}'

CONFIGURE_OPTIONS+= --docdir='$(X11_DOC_DIR)' \
	XORG_SGML_PATH=$(PROTODIR)$(X11_SGML_DIR)

$(BUILD_DIR)/.postprocess:	$(INSTALL_32)
	$(MKDIR) $(PROTO_DIR)$(X11_DOC_DIR)
	(cd $(COMPONENT_DIR)/src && tar -cf - .) | \
		(cd $(PROTO_DIR)$(X11_DOC_DIR) && tar -xf - )
	mv -f $(PROTO_DIR)$(USRSHAREMAN5DIR)/Consortium.5 \
		$(PROTO_DIR)$(USRSHAREMAN5DIR)/XConsortium.5
	mv -f $(PROTO_DIR)$(USRSHAREMAN5DIR)/Standards.5 \
		$(PROTO_DIR)$(USRSHAREMAN5DIR)/XStandards.5
	$(TOUCH) $@


build: $(BUILD_32)

install: $(INSTALL_32) $(BUILD_DIR)/.postprocess

test: $(NO_TESTS)

