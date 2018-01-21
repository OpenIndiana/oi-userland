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
# Copyright (c) 2011, 2014, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		grails
COMPONENT_VERSION=	1.0.3
COMPONENT_REVISION=	3
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	http://grails.org/
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-src-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:529e3cb766e1d49ef60f591f4b9355c5f3d090e38ba193505685cc0cdb729a59
COMPONENT_ARCHIVE_URL=	http://dlc.openindiana.org/oi-build/source-archives/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/grails

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/ant.mk
include $(WS_MAKE_RULES)/ips.mk

# Make sure we use the specially modified versions of grails and grails-debug
COMPONENT_POST_UNPACK_ACTION = \
	$(CP) $(COMPONENT_DIR)/files/grails $(SOURCE_DIR)/bin; \
	$(CP) $(COMPONENT_DIR)/files/grails-debug $(SOURCE_DIR)/bin

COMPONENT_PRE_BUILD_ACTION = $(MKDIR) $(@D)/tmp
COMPONENT_BUILD_ENV += "ANT_OPTS=-Djava.io.tmpdir=$(BUILD_DIR_32)/tmp"

COMPONENT_BUILD_ARGS=

# Need to package the .jar files we've built, not the ones included in
# the source tarball.
PKG_PROTO_DIRS = $(BUILD_DIR_32) $(MANGLED_DIR) $(PROTO_DIR) $(@D) \
	$(COMPONENT_DIR) $(COMPONENT_SRC)

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

# common targets
build:		$(BUILD_32)

# fix names with spaces
# workaround for bug 6734267 (pkgmk does not allow spaces in file names)
# the following files are not used directly by Grails framework...
$(INSTALL_32):	$(BUILD_32)
	(cd $(COMPONENT_SRC)/media/icons ; \
		mv 'grails - 16x16 icon.png' grails-16x16icon.png ; \
		mv 'grails - 32x32 icon.png' grails-32x32icon.png ; \
		mv 'grails - 48x48 icon.png' grails-48x48icon.png ; \
		mv 'grails - 64x64 icon.png' grails-64x64icon.png ; \
		mv 'grails - 128x128 icon.png' grails-128x128icon.png)
	$(TOUCH) $@

install:	$(INSTALL_32)

test:		$(NO_TESTS)

# Build dependencies
REQUIRED_PACKAGES += developer/build/ant

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += developer/java/openjdk7
REQUIRED_PACKAGES += developer/java/openjdk8
REQUIRED_PACKAGES += runtime/java/openjdk8
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += runtime/perl-524
REQUIRED_PACKAGES += runtime/python-27
