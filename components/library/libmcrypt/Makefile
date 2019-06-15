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
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2019, Nona Hansel
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libmcrypt
COMPONENT_VERSION=	2.5.8
COMPONENT_REVISION=	1
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:e4eb6c074bbab168ac47b947c195ff8cef9d51a211cdd18ca9c9ef34d27a373e
COMPONENT_ARCHIVE_URL=	http://sourceforge.net/projects/mcrypt/files/Libmcrypt/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=  http://mcrypt.sourceforge.net/

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

LDFLAGS += -lsocket -lnsl

CONFIGURE_ENV +=	MAKE=$(GMAKE)

# Need the GNU sed in our path because of assumptions 
# in the configure script.
CONFIGURE_ENV +=	PATH=$(PATH.gnu)

CONFIGURE_OPTIONS += --disable-dynamic-loading
CONFIGURE_OPTIONS += --with-included-algos="\
	rijndael-128,rijndael-192,rinjndael-256,enigma,arcfour,blowfish,des,\
	tripledes,ecb,cbc,cfb,ctr,ncfb,nofb,ofb,stream" 

# Use cloney to symlink to everything in the source directory because
# some of parts of the build seem to reference directories relative 
# to the current (build) directory, but are expecting to find files (e.g.,
# header files) which reside in the source dir. 
#
# We also must remove the config.status file; otherwise, configure
# thinks it has already been configured.
COMPONENT_PRE_CONFIGURE_ACTION += \
	$(TOUCH) $(CONFIGURE_SCRIPT) ; \
	$(RM) $(SOURCE_DIR)/config.status ; \
	($(CLONEY) $(SOURCE_DIR) $(@D))

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
