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
# Copyright (c) 2014, 2016, Oracle and/or its affiliates. All rights reserved.
#
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		ftp-proxy
COMPONENT_VERSION=	OPENBSD_5_5
IPS_COMPONENT_VERSION=	5.5
COMPONENT_PROJECT_URL=	http://www.openbsd.org
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
CVS_REPO=anoncvs@anoncvs.ca.openbsd.org:/cvs
CVS_PATH=src/usr.sbin/ftp-proxy
CVS_HASH=  sha256:fc4487a5ea3f8f088d8096d512bda15c99b811db9d66fee44bdd40aa93122403
CVS_TAG=$(COMPONENT_VERSION)
COMPONENT_BUGDB=	service/ftp-proxy

TPNO=	24255

#
# Don't overwrite CFLAGS here, just add our options there.
#
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS) -D_SOLARIS_ -DOBSD_COMP -lscf"
COMPONENT_BUILD_ARGS +=	CC="$(CC)"

include ../../make-rules/prep.mk
include ../../make-rules/justmake.mk
include ../../make-rules/ips.mk

COMPONENT_INSTALL_ARGS +=	PREFIX=$(PROTOUSRDIR)
COMPONENT_INSTALL_ARGS +=	MANDIR=$(PROTOUSRSHAREMANDIR)
COMPONENT_INSTALL_ARGS +=	INSTALL=/usr/gnu/bin/install

ASLR_MODE = $(ASLR_ENABLE)

# common targets
build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(NO_TESTS)

REQUIRED_PACKAGES += library/libevent
REQUIRED_PACKAGES += network/firewall
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/core-os
REQUIRED_PACKAGES += system/header
REQUIRED_PACKAGES += system/library
