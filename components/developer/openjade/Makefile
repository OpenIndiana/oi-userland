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
# Copyright 2015 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= openjade
COMPONENT_VERSION= 1.3.2
COMPONENT_REVISION= 6
COMPONENT_SUMMARY= OpenJade DSSSL-Engine for SGML documents
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:1d2d7996cc94f9b87d0c51cf0e028070ac177c4123ecbfd7ac1cb8d0b7d322d1
COMPONENT_ARCHIVE_URL=	https://sourceforge.net/projects/openjade/files/openjade/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://openjade.sourceforge.net/
COMPONENT_FMRI=			developer/documentation-tool/openjade
COMPONENT_CLASSIFICATION=	System/Text Tools
COMPONENT_LICENSE=		MIT
COMPONENT_LICENSE_FILE=	COPYING

# openjade segfaults in libostyle.so when compiled using gcc 10 or later.
# This needs to be defined before include common.mk otherwise USERLAND_REQUIRED_PACKAGES won't be correct.
GCC_VERSION= 7

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)
					
COMPONENT_PREP_ACTION= ( \
	cp $(COMPONENT_DIR)/files/jade_style-sheet.dtd  $(@D)/dsssl &&\
	cd  $(@D) &&\
	rm -f aclocal.m4 missing &&\
	cp config/configure.in . &&\
	PATH="$(PATH)" libtoolize --force &&\
	aclocal -I config &&\
	autoconf --force )

# The linker is too agressive
LD_Z_IGNORE=

# Missing files in build dir for configure without this.
COMPONENT_PRE_CONFIGURE_ACTION= ( $(CLONEY) $(SOURCE_DIR) $(@D) )

CONFIGURE_SCRIPT = $(@D)/configure
                                        
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-spincludedir=$(USRINCDIR)/OpenSP
CONFIGURE_OPTIONS += --datadir=$(USRSHAREDIR)/sgml/openjade
CONFIGURE_OPTIONS += --enable-splibdir=$(USRLIBDIR.$(BITS))
CONFIGURE_OPTIONS += --disable-http
CONFIGURE_OPTIONS += --enable-mif
CONFIGURE_OPTIONS += --enable-default-catalog="CATALOG:/etc/sgml/catalog:$(USRSHAREDIR)/sgml/CATALOG"
CONFIGURE_OPTIONS += LINKFLAGS="$(LDFLAGS)"

COMPONENT_INSTALL_TARGETS= install install-man

# We need jade symlink
COMPONENT_POST_INSTALL_ACTION += $(SYMLINK) openjade $(PROTOUSRBINDIR)/jade ;

# Install headers
COMPONENT_POST_INSTALL_ACTION += \
	$(INSTALL) -d $(PROTOUSRINCDIR)/openjade ; \
	for f in \
	    $(SOURCE_DIR)/generic/*.h $(SOURCE_DIR)/grove/Node.h $(SOURCE_DIR)/spgrove/GroveApp.h \
	    $(SOURCE_DIR)/spgrove/GroveBuilder.h $(SOURCE_DIR)/style/FOTBuilder.h $(SOURCE_DIR)/style/GroveManager.h \
	    $(SOURCE_DIR)/style/DssslApp.h $(SOURCE_DIR)/style/dsssl_ns.h ; do \
		$(INSTALL) $$f $(PROTOUSRINCDIR)/openjade ; \
	done ;

# Install sgml
COMPONENT_POST_INSTALL_ACTION += \
	$(INSTALL) -d $(PROTOUSRSHAREDIR)/sgml/openjade ; \
	$(INSTALL) -d $(PROTOVARDIR)/lib/sgml ; \
	cd $(SOURCE_DIR)/dsssl && \
	$(CP) catalog dsssl.dtd extensions.dsl fot.dtd style-sheet.dtd \
		builtins.dsl jade_style-sheet.dtd $(PROTOUSRSHAREDIR)/sgml/openjade && \
	$(GSED) 's:"\([^"]*\(dtd\|dsl\)\)"$$:"/usr/share/sgml/openjade/\1":' catalog > $(PROTOVARDIR)/lib/sgml/CATALOG.openjade ; \
	$(SYMLINK) CATALOG.openjade $(PROTOVARDIR)/lib/sgml/CATALOG.jade_dsl ; \
	$(SYMLINK) ../../../..$(VARDIR)/lib/sgml/CATALOG.openjade $(PROTOUSRSHAREDIR)/sgml/CATALOG.openjade ; \
	$(SYMLINK) ../../../..$(VARDIR)/lib/sgml/CATALOG.openjade $(PROTOUSRSHAREDIR)/sgml/CATALOG.jade_dsl ; \
	$(INSTALL) -d $(PROTOUSRSHAREDIR)/sgml/James_Clark/dtd ; \
	$(INSTALL) -d $(PROTOUSRSHAREDIR)/sgml/OpenJade/dtd ; \
	$(INSTALL) -d $(PROTOUSRSHAREDIR)/sgml/ISO_IEC_10179:1996/dtd ; \
	$(SYMLINK) ../../openjade/jade_style-sheet.dtd $(PROTOUSRSHAREDIR)/sgml/James_Clark/dtd/DSSSL_Style_Sheet ; \
	$(SYMLINK) ../../openjade/fot.dtd $(PROTOUSRSHAREDIR)/sgml/James_Clark/dtd/DSSSL_Flow_Object_Tree ; \
	$(SYMLINK) ../../openjade/style-sheet.dtd $(PROTOUSRSHAREDIR)/sgml/OpenJade/dtd/DSSSL_Style_Sheet ; \
	$(SYMLINK) ../../openjade/dsssl.dtd $(PROTOUSRSHAREDIR)/sgml/ISO_IEC_10179:1996/dtd/DSSSL_Architecture ; \
	cd $(PROTOUSRSHAREDIR)/sgml/openjade && \
	$(SYMLINK) ../opensp/japan.dcl . && \
	$(SYMLINK) ../opensp/opensp-implied.dcl sp_implied.dcl && \
	$(SYMLINK) ../opensp/xml.dcl . && \
	$(SYMLINK) ../opensp/xml.soc . && \
	for d in *.dcl ; do \
		rm -f $${d/.dcl/.decl} ; \
		$(SYMLINK) $$d $${d/.dcl/.decl} ; \
	done ;

# Testing currently fails
COMPONENT_TEST_DIR = $(@D)/testsuite
COMPONENT_TEST_TARGETS =

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += developer/documentation-tool/opensp
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
