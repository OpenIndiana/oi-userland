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
# Copyright (c) 2016, Oracle and/or its affiliates. All rights reserved.
#
BUILD_ARCH=		i386
BUILD_BITS=		64
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		docker
COMPONENT_VERSION=	1.10.3
COMPONENT_PROJECT_URL=	http://www.docker.com
COMPONENT_ARCHIVE_URL=	\
	https://github.com/docker/docker/archive/v$(COMPONENT_VERSION).tar.gz

COMPONENT_BUGDB=	utility/docker-engine

TPNO=			27475

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/ips.mk

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

PKG_PROTO_DIRS += $(COMPONENT_DIR)/files/man

# common targets
build:		$(SOURCE_DIR)/.prep
	cd $(SOURCE_DIR); DOCKER_GITCOMMIT=6f2305e \
		AUTO_GOPATH=1 ./hack/make.sh dynbinary
	$(TOUCH) $(SOURCE_DIR)/.built

install:	FRC
	$(TOUCH) $(SOURCE_DIR)/.installed

test:		$(NO_TESTS)

REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += system/core-os
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/zones
