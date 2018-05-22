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
COMPONENT_SUMMARY= OpenJade DSSSL-Engine for SGML documents
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:1d2d7996cc94f9b87d0c51cf0e028070ac177c4123ecbfd7ac1cb8d0b7d322d1
COMPONENT_ARCHIVE_URL= \
  http://sourceforge.net/projects/openjade/files/openjade/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://openjade.sourceforge.net/
COMPONENT_FMRI = developer/documentation-tool/openjade
COMPONENT_CLASSIFICATION = System/Text Tools
COMPONENT_LICENSE = MIT-like
COMPONENT_LICENSE_FILE = COPYING

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)
					
COMPONENT_PREP_ACTION = 	( cp $(COMPONENT_DIR)/files/jade_style-sheet.dtd  $(@D)/dsssl &&\
					cd  $(@D) &&\
					rm -f aclocal.m4 missing &&\
					cp config/configure.in . &&\
					libtoolize --force &&\
					aclocal -I config &&\
					autoconf --force )

# Missing files in build dir for configure without this.
COMPONENT_PRE_CONFIGURE_ACTION =        ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_SCRIPT = $(@D)/configure
                                        
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-spincludedir=/usr/include/OpenSP
CONFIGURE_OPTIONS += --datadir=/usr/share/sgml/openjade
CONFIGURE_OPTIONS += --enable-splibdir=/usr/lib
CONFIGURE_OPTIONS += --disable-http
CONFIGURE_OPTIONS += --enable-mif
CONFIGURE_OPTIONS += --enable-default-catalog="CATALOG:/etc/sgml/catalog:/usr/share/sgml/CATALOG"

COMPONENT_INSTALL_TARGETS = install install-man

INSTALL_HEADERS = $(BUILD_DIR)/.install_headers
INSTALL_SGML = $(BUILD_DIR)/.install_sgml

$(INSTALL_HEADERS):	$(INSTALL_32)
	[ -d $(PROTO_DIR)/usr/include/openjade ] || $(MKDIR) $(PROTO_DIR)/usr/include/openjade
	cp $(SOURCE_DIR)/generic/*.h $(SOURCE_DIR)/grove/Node.h $(SOURCE_DIR)/spgrove/GroveApp.h $(PROTO_DIR)/usr/include/openjade
	cp $(SOURCE_DIR)/spgrove/GroveBuilder.h $(SOURCE_DIR)/style/FOTBuilder.h $(SOURCE_DIR)/style/GroveManager.h $(PROTO_DIR)/usr/include/openjade
	cp $(SOURCE_DIR)/style/DssslApp.h $(SOURCE_DIR)/style/dsssl_ns.h $(PROTO_DIR)/usr/include/openjade
	$(TOUCH) $(@)

$(INSTALL_SGML):	$(INSTALL_32)
	install -d $(PROTO_DIR)/usr/share/sgml/openjade
	pushd $(SOURCE_DIR)/dsssl &&\
	cp catalog dsssl.dtd extensions.dsl fot.dtd style-sheet.dtd \
		builtins.dsl jade_style-sheet.dtd  $(PROTO_DIR)/usr/share/sgml/openjade &&\
	install -d $(PROTO_DIR)/var/lib/sgml &&\
	sed 's:"\([^"]*\(dtd\|dsl\)\)"$$:"/usr/share/sgml/openjade/\1":' catalog > $(PROTO_DIR)/var/lib/sgml/CATALOG.openjade &&\
	ln -sf CATALOG.openjade $(PROTO_DIR)/var/lib/sgml/CATALOG.jade_dsl &&\
	cd $(PROTO_DIR)/usr/share/sgml &&\
		ln -sf ../../../../var/lib/sgml/CATALOG.openjade CATALOG.openjade &&\
		ln -sf ../../../../var/lib/sgml/CATALOG.openjade CATALOG.jade_dsl &&\
	popd
	install -d  $(PROTO_DIR)/usr/share/sgml/James_Clark/dtd
	install -d  $(PROTO_DIR)/usr/share/sgml/OpenJade/dtd
	install -d  $(PROTO_DIR)/usr/share/sgml/ISO_IEC_10179:1996/dtd
	cd $(PROTO_DIR)/usr/share/sgml/James_Clark/dtd &&\
		ln -sf ../../openjade/jade_style-sheet.dtd DSSSL_Style_Sheet &&\
		ln -sf ../../openjade/fot.dtd DSSSL_Flow_Object_Tree
	cd $(PROTO_DIR)/usr/share/sgml/OpenJade/dtd &&\
		ln -sf ../../openjade/style-sheet.dtd DSSSL_Style_Sheet
	cd $(PROTO_DIR)/usr/share/sgml/ISO_IEC_10179:1996/dtd &&\
		ln -sf ../../openjade/dsssl.dtd DSSSL_Architecture
	pushd $(PROTO_DIR)/usr/share/sgml/openjade &&\
	ln -sf ../opensp/japan.dcl . &&\
	ln -sf ../opensp/opensp-implied.dcl sp_implied.dcl &&\
	ln -sf ../opensp/xml.dcl . &&\
	ln -sf ../opensp/xml.soc . &&\
	for d in *.dcl; do \
		rm -f $${d/.dcl/.decl};\
		ln -sf $$d $${d/.dcl/.decl} ; \
	done &&\
	popd
	$(TOUCH) $(@)

build: $(BUILD_32)

install: $(INSTALL_32) $(INSTALL_HEADERS) $(INSTALL_SGML)

# Auto-generated dependencies
REQUIRED_PACKAGES += developer/documentation-tool/opensp
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/g++-6-runtime
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library/math
