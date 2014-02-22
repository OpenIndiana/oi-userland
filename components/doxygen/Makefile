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
# Copyright (c) 2011, 2013, Oracle and/or its affiliates. All rights reserved.
#
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		doxygen
COMPONENT_VERSION=	1.7.6.1
COMPONENT_PROJECT_URL=	http://www.stack.nl/~dimitri/doxygen/index.html
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).src.tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:0e60e794fb172d3fa4a9a9535f0b8e0eeb04e8366153f6b417569af0bcd61fcd
COMPONENT_ARCHIVE_URL=	http://ftp.stack.nl/pub/users/dimitri/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/doxygen

# Download the manual so that we don't have to keep updating it in the gate.
COMPONENT_ARCHIVE_1 =	$(COMPONENT_NAME)_manual-$(COMPONENT_VERSION).pdf.zip
COMPONENT_ARCHIVE_HASH_1 =	\
    sha256:abe8ea7db00fe68632edeb2d6e44f94ad96a0dc798702b044afbc1752c7b2a61
COMPONENT_ARCHIVE_URL_1 =	ftp://ftp.stack.nl/pub/users/dimitri/$(COMPONENT_ARCHIVE_1)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

# Necessary to find gcc during build
PATH=$(GCC_ROOT)/bin:/usr/bin

# Missing files in build dir for configure without this.
COMPONENT_PRE_CONFIGURE_ACTION =	($(CLONEY) $(SOURCE_DIR) $(@D))

# Need to override default options since configure doesn't
# understand CC, CXX, etc.
CONFIGURE_OPTIONS =	--platform solaris-g++
CONFIGURE_OPTIONS +=	--prefix /usr
CONFIGURE_OPTIONS +=	--enable-langs nl,sv,cz,fr,id,it,de,jp,je,es,fi,ru,hr,pl,pt,hu,kr,ke,ro,si,cn,no,br,dk,sk,ua,gr,tw,sr,ca,lt,za,ar,fa

ASLR_MODE = $(ASLR_ENABLE)

# common targets
build:		$(BUILD_64)

install:	$(INSTALL_64)
	$(UNPACK) $(USERLAND_ARCHIVES)$(COMPONENT_ARCHIVE_1) 
	[ -f $(PROTO_DIR)/doxygen_manual-$(IPS_COMPONENT_VERSION).pdf ] || \
	  $(MV) doxygen_manual-$(IPS_COMPONENT_VERSION).pdf $(PROTO_DIR)

test:	$(NO_TESTS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
