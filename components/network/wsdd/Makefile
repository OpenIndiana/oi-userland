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
# Copyright 2025 Carsten Grzemba
#
BUILD_STYLE = archive
BUILD_BITS = NO_ARCH
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		wsdd
COMPONENT_VERSION=	0.9
COMPONENT_REVISION=	1
COMPONENT_SUMMARY=	Web Service Discovery host daemon
COMPONENT_DESCRIPTION=	This enables SMB server to be found by Web Service Discovery Clients like Windows.
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=  https://github.com/christgau/$(COMPONENT_NAME)/archive/refs/tags/v$(COMPONENT_VERSION).tar.gz

COMPONENT_ARCHIVE_HASH= sha256:009efafb763686d9e265ca8f1dd17696bc80fc0ee619f48ea7878ec21471f61e
COMPONENT_PROJECT_URL=	https://github.com/christgau/wsdd
COMPONENT_FMRI=		network/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	Applications/Internet
COMPONENT_LICENSE=		MIT
COMPONENT_LICENSE_FILE= LICENSE


include $(WS_MAKE_RULES)/common.mk


install: prep
	mkdir -p $(PROTOLIBDIR)/svc/method/
	mkdir -p $(PROTOLIBDIR)/svc/manifest/network
	mkdir -p $(PROTOUSRLIBDIR)/wsdd
	mkdir -p $(PROTOUSRSHAREDIR)/man/man8
	cp -p $(COMPONENT_DIR)/files/svc-wsdd $(PROTOLIBDIR)/svc/method/
	cp -p $(COMPONENT_DIR)/files/wsdd.xml $(PROTOLIBDIR)/svc/manifest/network/
	cp -p $(COMPONENT_DIR)/files/README $(PROTOUSRLIBDIR)/wsdd/
	cp -p $(COMPONENT_SRC)/src/wsdd.py $(PROTOUSRLIBDIR)/wsdd/
	cp -p $(COMPONENT_SRC)/man/wsdd.8 $(PROTOUSRSHAREDIR)/man/man8/

clean::
	rm -rf $(BUILD_DIR)


# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += service/file-system/smb
REQUIRED_PACKAGES.python += library/python/defusedxml
REQUIRED_PACKAGES.python += runtime/python
