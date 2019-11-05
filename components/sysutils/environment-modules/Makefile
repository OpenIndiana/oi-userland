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
# Copyright 2013 Aurelien Larcher.  All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		environment-modules
COMPONENT_VERSION=	3.2.10
COMPONENT_REVISION=     1
COMPONENT_FMRI=		package/$(COMPONENT_NAME)
COMPONENT_PROJECT_URL=	http://modules.sourceforge.net/
SOURCE_NAME=		modules
COMPONENT_SRC=		$(SOURCE_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
    sha256:e8403492a8d57ace6485813ad6cdaafe0a735b7d93b9435553a8d11d3fdd29a2
COMPONENT_ARCHIVE_URL=	http://sourceforge.net/projects/modules/files/Modules/$(COMPONENT_SRC)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	$(COMPONENT_FMRI)

COMPONENT_SUMMARY=	Package for managing different versions of applications or metamodules to bundle a suite of applications
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license
COMPONENT_LICENSE=	GPLv2


include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk  


CONFIGURE_PREFIX=	$(USRLIBDIR)

CONFIGURE_DEFAULT_DIRS=	no

# Need to workaround a bug in the install system: specify the bindir path
CONFIGURE_OPTIONS+=	--bindir=$(CONFIGURE_PREFIX)/Modules/$(COMPONENT_VERSION)/bin
CONFIGURE_OPTIONS+=	--mandir=$(USRSHAREMANDIR)
CONFIGURE_OPTIONS+=	--enable-versioning
CONFIGURE_OPTIONS+=	--enable-logging
CONFIGURE_OPTIONS+=	--with-module-path=$(MODULE_PATH)
CONFIGURE_OPTIONS+=	--with-version-path=$(MODULE_VERSIONS_PATH)


build:		$(BUILD_32)

install:	$(INSTALL_32)
	$(MKDIR) $(PROTO_DIR)$(BASH_COMPLETIONS_PATH);
	$(CP) $(PROTO_DIR)$(CONFIGURE_PREFIX)/Modules/$(COMPONENT_VERSION)/init/bash_completion \
		$(PROTO_DIR)$(BASH_COMPLETIONS_PATH)/modules;
	$(MKDIR) $(PROTOETCDIR)/profile.d;
	$(CP) files/modules.sh $(PROTOETCDIR)/profile.d;

test:	$(NO_TESTS)


# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += runtime/tcl-8
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libx11
