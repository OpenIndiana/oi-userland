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
# Copyright (c) 2013, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		groff
COMPONENT_VERSION=	1.22.2
COMPONENT_PROJECT_URL=	http://www.gnu.org/software/groff/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:380864dac4772e0c0d7b1282d25d0c5fd7f63baf45c87c4657afed22a13d2076
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/gnu/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/groff

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

# The grog.sh script needs GNU awk not the Solaris one.
COMPONENT_PRE_CONFIGURE_ACTION = \
	$(GSED) -i -e 's?awk?/usr/gnu/bin/awk?' \
		$(SOURCE_DIR)/src/roff/grog/grog.sh

CONFIGURE_OPTIONS += \
    --with-appresdir=$(CONFIGURE_PREFIX)/X11/lib/X11/app-defaults

COMPONENT_INSTALL_ARGS += legacyfontdir=/usr/lib/font
COMPONENT_INSTALL_ARGS += appresdir=/usr/X11/lib/X11/app-defaults
COMPONENT_INSTALL_ARGS += sys_tmac_prefix=/usr/share/lib/tmac/

COMPONENT_PRE_INSTALL_ACTION = \
	($(MKDIR) $(PROTOUSRBINDIR) )

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

# groff tests use dejagnu which isn't currently included in Solaris.
test:		$(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += runtime/perl-524
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += text/gawk
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxmu
REQUIRED_PACKAGES += x11/library/toolkit/libxaw7
REQUIRED_PACKAGES += x11/library/toolkit/libxt
