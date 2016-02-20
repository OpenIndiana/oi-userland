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
# Copyright 2013 Alexander Pyhalov
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		aspell-ru
COMPONENT_VERSION=	0.99f7-1
COMPONENT_SRC=		aspell6-ru-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	sha256:5c29b6ccce57bc3f7c4fb0510d330446b9c769e59c92bdfede27333808b6e646
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/gnu/aspell/dict/ru/$(COMPONENT_ARCHIVE)


include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

COMPONENT_PRE_CONFIGURE_ACTION += cp -r $(SOURCE_DIR)/* $(@D)

CONFIGURE_OPTIONS = 

build:		$(BUILD_32)

install:	$(INSTALL_32)

