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
# Copyright 2014 Alexander Pyhalov.  All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= sgml-common
COMPONENT_VERSION= 0.6.3
COMPONENT_SUMMARY= Common SGML catalog and DTD files
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tgz
COMPONENT_ARCHIVE_HASH= \
  sha256:7dc418c1d361123ffc5e45d61f1b97257940a8eb35d0bfbbc493381cc5b1f959
COMPONENT_ARCHIVE_URL= \
  ftp://sources.redhat.com/pub/docbook-tools/new-trials/SOURCES/$(COMPONENT_ARCHIVE)

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

XMLCATALOG=$(PROTO_DIR)/etc/xml/catalog

COMPONENT_PREP_ACTION +=(cd $(@D) && \
			aclocal && \
			autoconf &&\
			automake --add-missing --copy );

# Missing files in build dir for configure without this.
COMPONENT_PRE_CONFIGURE_ACTION =        ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_OPTIONS+= --sysconfdir=/etc
CONFIGURE_OPTIONS+= --with-docdir=$(USRSHAREDOCDIR)

build: $(BUILD_32)

install: $(INSTALL_32)
	$(MKDIR) $(PROTO_DIR)/etc/xml $(PROTO_DIR)/usr/share/sgml/docbook
	# Create an empty XML catalog.
	/usr/bin/xmlcatalog --noout --create $(XMLCATALOG)
	# Now put the common DocBook entries in it
	/usr/bin/xmlcatalog --noout --add "delegatePublic" "-//OASIS//ENTITIES DocBook XML" "file:///usr/share/sgml/docbook/xmlcatalog" $(XMLCATALOG)
	/usr/bin/xmlcatalog --noout --add "delegatePublic" "-//OASIS//DTD DocBook XML" "file:///usr/share/sgml/docbook/xmlcatalog" $(XMLCATALOG)
	/usr/bin/xmlcatalog --noout --add "delegatePublic" "ISO 8879:1986" "file:///usr/share/sgml/docbook/xmlcatalog" $(XMLCATALOG)
	/usr/bin/xmlcatalog --noout --add "delegateSystem" "http://www.oasis-open.org/docbook/" "file:///usr/share/sgml/docbook/xmlcatalog" $(XMLCATALOG)
	/usr/bin/xmlcatalog --noout --add "delegateURI" "http://www.oasis-open.org/docbook/" "file:///usr/share/sgml/docbook/xmlcatalog" $(XMLCATALOG)
	# Also create the common DocBook catalog
	/usr/bin/xmlcatalog --noout --create $(PROTO_DIR)/usr/share/sgml/docbook/xmlcatalog
	$(TOUCH) $(PROTO_DIR)/etc/sgml/catalog
