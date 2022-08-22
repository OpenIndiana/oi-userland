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

X11_CATEGORY= DOC
include ../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/x11.mk

COMPONENT_NAME=         xorg-docs
COMPONENT_VERSION=      1.7.2
COMPONENT_FMRI=         x11/documentation/xorg-docs
COMPONENT_SUMMARY=      X.Org documentation for the X Window System
COMPONENT_ARCHIVE_HASH= \
	sha256:2391b8af472626c12d3c3814b5e7a0ea43c3a96eda94255b7ed8bdff0fbf08e3

include $(WS_MAKE_RULES)/common.mk

X11_DOC_DIR=$(USRSHAREDOCDIR)/X11
X11_SGML_DIR=$(USRSHAREDIR)/sgml

COMPONENT_PREP_ACTION= \
	find $(@D) -name '*.xml' | xargs $(PERL) -i.orig -p -e \
	 's{SYSTEM ".*/X11/defs.ent"}{SYSTEM "$(X11_SGML_DIR)/X11/defs.ent"}'

CONFIGURE_OPTIONS+= --docdir='$(X11_DOC_DIR)' \
	XORG_SGML_PATH=$(PROTODIR)$(X11_SGML_DIR)
CONFIGURE_OPTIONS+= --with-xmlto
CONFIGURE_OPTIONS+= --without-xsltproc

COMPONENT_POST_INSTALL_ACTION= \
	( $(MKDIR) $(PROTO_DIR)$(X11_DOC_DIR); \
	    (cd $(COMPONENT_DIR)/src && tar -cf - .) | \
	      (cd $(PROTO_DIR)$(X11_DOC_DIR) && tar -xf - ); \
	    $(MV) $(PROTO_DIR)$(USRSHAREMAN7DIR)/Consortium.7 \
		$(PROTO_DIR)$(USRSHAREMAN7DIR)/XConsortium.7; \
	    $(MV) $(PROTO_DIR)$(USRSHAREMAN7DIR)/Standards.7 \
		$(PROTO_DIR)$(USRSHAREMAN7DIR)/XStandards.7 )

# Build dependencies
REQUIRED_PACKAGES+=text/xmlto
# Auto-generated dependencies
# None as it seems...
