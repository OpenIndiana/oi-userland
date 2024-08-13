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
# Copyright (c) 2023, Franklin Ronald <franklin@wiselabs.com.br>
#

BUILD_STYLE= cmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		multitail
COMPONENT_VERSION=	7.1.4
COMPONENT_SUMMARY=	Tail multiple files on console with ncurses
COMPONENT_PROJECT_URL=	https://www.vanheusden.com/multitail/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	https://github.com/folkertvanheusden/multitail/archive/refs/tags/$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:96b781a9c22f3518fc25c4f3ce3833ec5069158b2a743a30f7586cd063824704
COMPONENT_FMRI=				file/multitail
COMPONENT_CLASSIFICATION= 	Applications/System Utilities
COMPONENT_LICENSE=			Apache 2.0
COMPONENT_LICENSE_FILE=		LICENSE

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

CMAKE_OPTIONS += -DUTF8_SUPPORT=Yes -DCURSES_INCLUDE_PATH=/usr/include

COMPONENT_POST_INSTALL_ACTION  = \
	/usr/bin/elfedit -e 'dyn:value -s  RUNPATH "/usr/gnu/lib/$(MACH64)"' "$(PROTO_DIR)/usr/bin/multitail"; \
	/usr/bin/elfedit -e 'dyn:value -s  RPATH "/usr/gnu/lib/$(MACH64)"' "$(PROTO_DIR)/usr/bin/multitail"; \
	rm -Rf "$(PROTO_DIR)/usr/etc/multitail/conversion-scripts"; \
	mv "$(PROTO_DIR)/usr/share/doc/$(COMPONENT_NAME)-VERSION=$(COMPONENT_VERSION)" "$(PROTO_DIR)/usr/share/doc/multitail"; \
	rm -Rf "$(PROTO_DIR)/etc"; \
	mkdir -p "$(PROTO_DIR)/etc"; \
	mv "$(PROTO_DIR)/usr/etc/multitail.conf.new" "$(PROTO_DIR)/etc/multitail.conf.sample";

# The native Makefile invites patching to set the following, but doing it here
# instead will keep it working if the build system changes.
COMPONENT_BUILD_ARGS += CC="$(CC)"
COMPONENT_BUILD_ARGS += CFLAGS="$(CC_BITS) $(CFLAGS)"
COMPONENT_BUILD_ARGS += LDFLAGS="$(LDFLAGS)"
COMPONENT_INSTALL_ARGS += BINDIR=$(PROTOUSRBINDIR)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
