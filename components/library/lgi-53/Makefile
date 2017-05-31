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
# Copyright (c) 2015, 2017, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         lgi
COMPONENT_VERSION=      0.9.1
COMPONENT_SUMMARY=	Dynamic Lua binding to GObject libraries using GObject-Introspection
COMPONENT_PROJECT_URL=  https://github.com/pavouk/lgi
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:0c70fb2b1ca17d333b7e2c18d5fc943944b5872e063de60df3035ee20b6dafba
COMPONENT_ARCHIVE_URL=  https://github.com/pavouk/lgi/archive/$(COMPONENT_VERSION).tar.gz
COMPONENT_FMRI=         library/lua/lgi-53
COMPONENT_CLASSIFICATION=Development/Other Languages
COMPONENT_LICENSE=	MIT
COMPONENT_LICENSE_FILE=	LICENSE

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

PATH.32=/usr/gnu/bin:/usr/bin
PATH.64=/usr/gnu/bin/$(MACH64):/usr/bin/$(MACH64):/usr/gnu/bin:/usr/bin

LDFLAGS += $(CC_BITS) 

CFLAGS += -I/usr/include/lua5.3
COMPONENT_BUILD_ENV += CC="$(CC)"
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)" 
COMPONENT_BUILD_ENV += LDFLAGS="$(LDFLAGS)"
COMPONENT_BUILD_ENV += PATH=$(PATH.$(BITS))

COMPONENT_INSTALL_ARGS += LUA_VERSION=5.3 PREFIX=$(USRDIR)
COMPONENT_INSTALL_ARGS.64 += LUA_LIBDIR=$(USRDIR)/lib/lua/5.3/64

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(NO_TESTS)


REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libffi
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += runtime/lua-53
