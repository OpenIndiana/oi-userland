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
# Copyright (c) 2015, Oracle and/or its affiliates. All rights reserved.
#

USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         opensp
COMPONENT_VERSION=      1.5.2
COMPONENT_REVISION=		1
COMPONENT_SUMMARY=	The OpenJade group's SGML and XML parsing tools
COMPONENT_PROJECT_URL=  https://openjade.sourceforge.net/
COMPONENT_SRC=          OpenSP-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
	sha256:57f4898498a368918b0d49c826aa434bb5b703d2c3b169beb348016ab25617ce
COMPONENT_ARCHIVE_URL=  https://prdownloads.sourceforge.net/openjade/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		developer/documentation-tool/opensp
COMPONENT_CLASSIFICATION=	System/Text Tools
COMPONENT_LICENSE=	MIT
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

COMPONENT_PREP_ACTION += ( cd $(@D); PATH="$(PATH)" autoreconf -fiv )

CONFIGURE_OPTIONS += --disable-http
CONFIGURE_OPTIONS += --disable-nls
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-default-catalog="CATALOG:$(ETCDIR)/sgml/catalog:$(USRSHAREDIR)/sgml/CATALOG"

# Custom modifications
COMPONENT_POST_INSTALL_ACTION += \
	$(INSTALL) -d $(PROTOUSRSHAREDIR)/sgml/opensp ; \
	$(MV) \
		$(PROTOUSRSHAREDIR)/OpenSP/japan.dcl \
		$(PROTOUSRSHAREDIR)/OpenSP/opensp-implied.dcl \
		$(PROTOUSRSHAREDIR)/OpenSP/xml.dcl \
		$(PROTOUSRSHAREDIR)/OpenSP/xml.soc \
		$(PROTOUSRSHAREDIR)/sgml/opensp ; \
	$(RM) -r $(PROTOUSRSHAREDIR)/OpenSP ; \
	$(INSTALL) -d $(PROTOVARDIR)/lib/sgml ; \
	$(INSTALL) $(COMPONENT_DIR)/files/CATALOG.opensp $(PROTOVARDIR)/lib/sgml ; \
	$(SYMLINK) ../../../..$(VARDIR)/lib/sgml/CATALOG.opensp $(PROTOUSRSHAREDIR)/sgml/CATALOG.opensp ;

# Create compatibility symlinks for binaries
COMPONENT_POST_INSTALL_ACTION += $(SYMLINK) onsgmls $(PROTOUSRBINDIR)/nsgmls ;
COMPONENT_POST_INSTALL_ACTION += $(SYMLINK) osx $(PROTOUSRBINDIR)/osgml2xml ;
COMPONENT_POST_INSTALL_ACTION += $(SYMLINK) osx $(PROTOUSRBINDIR)/s2x ;
COMPONENT_POST_INSTALL_ACTION += $(SYMLINK) osx $(PROTOUSRBINDIR)/sgml2xml ;
COMPONENT_POST_INSTALL_ACTION += $(SYMLINK) osgmlnorm $(PROTOUSRBINDIR)/sgmlnorm ;
COMPONENT_POST_INSTALL_ACTION += $(SYMLINK) ospam $(PROTOUSRBINDIR)/spam ;
COMPONENT_POST_INSTALL_ACTION += $(SYMLINK) ospcat $(PROTOUSRBINDIR)/spcat ;
COMPONENT_POST_INSTALL_ACTION += $(SYMLINK) ospent $(PROTOUSRBINDIR)/spent ;
# Create compatibility symlinks for man pages
COMPONENT_POST_INSTALL_ACTION += $(SYMLINK) onsgmls.1 $(PROTOUSRSHAREMAN1DIR)/nsgmls.1 ;
COMPONENT_POST_INSTALL_ACTION += $(SYMLINK) osx.1 $(PROTOUSRSHAREMAN1DIR)/osgml2xml.1 ;
COMPONENT_POST_INSTALL_ACTION += $(SYMLINK) osx.1 $(PROTOUSRSHAREMAN1DIR)/s2x.1 ;
COMPONENT_POST_INSTALL_ACTION += $(SYMLINK) osx.1 $(PROTOUSRSHAREMAN1DIR)/sgml2xml.1 ;
COMPONENT_POST_INSTALL_ACTION += $(SYMLINK) osgmlnorm.1 $(PROTOUSRSHAREMAN1DIR)/sgmlnorm.1 ;
COMPONENT_POST_INSTALL_ACTION += $(SYMLINK) ospam.1 $(PROTOUSRSHAREMAN1DIR)/spam.1 ;
COMPONENT_POST_INSTALL_ACTION += $(SYMLINK) ospcat.1 $(PROTOUSRSHAREMAN1DIR)/spcat.1 ;
COMPONENT_POST_INSTALL_ACTION += $(SYMLINK) ospent.1 $(PROTOUSRSHAREMAN1DIR)/spent.1 ;

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
