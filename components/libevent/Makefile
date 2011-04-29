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
# Copyright (c) 2011, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		libevent
COMPONENT_VERSION=	1.3e
IPS_COMPONENT_VERSION=	1.3.5
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha1:67b064a4533c640dfb86e3d81c0cca9247427353
COMPONENT_ARCHIVE_URL=	http://monkey.org/~provos/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk
include ../../make-rules/lint-libraries.mk

COMPONENT_PRE_CONFIGURE_ACTION =  \
	($(CLONEY) $(SOURCE_DIR) $(@D))

#The libevent that is bundled with Solaris is a trimed down version.
#It does not contain the evhttp*, evdns* functions. The man page 'event.3'
#is patched to remove descriptions regarding these functions.
#
#The original manpage is in a format that the Solaris man command does
#not understand. Hence it has been manually converted.
#
#List of files from the original package that are not being delivered
#
#/usr/share/man/man3/evdns.3
#/usr/include/evhttp.h
#/usr/include/evdns.h
#/usr/bin/event_rpcgen.py

CONFIGURE_OPTIONS	+= CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS	+= --enable-threads

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

# this isn't really true - there _are_ tests, but we can't run
# them because we delete things that the tests want (see above).
test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
