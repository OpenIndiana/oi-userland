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
# Copyright (c) 2019, Michal Nowak
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		groff
COMPONENT_VERSION=	1.23.0
COMPONENT_SUMMARY=	GNU troff Text Formatting
COMPONENT_PROJECT_URL=	https://www.gnu.org/software/groff/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:6b9757f592b7518b4902eb6af7e54570bdccba37a871fddb2d30ae3863511c13
COMPONENT_ARCHIVE_URL=	https://ftp.gnu.org/gnu/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		text/groff
COMPONENT_CLASSIFICATION=	System/Text Tools
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_TOP)/make-rules/common.mk

CONFIGURE_OPTIONS += --with-x
CONFIGURE_OPTIONS += --with-appdefdir=$(CONFIGURE_PREFIX)/X11/lib/X11/app-defaults
CONFIGURE_OPTIONS += --with-urw-fonts-dir=/usr/share/ghostscript/fonts

COMPONENT_INSTALL_ARGS += legacyfontdir=/usr/share/ghostscript/fonts
COMPONENT_INSTALL_ARGS += appdefdir=/usr/X11/lib/X11/app-defaults
COMPONENT_INSTALL_ARGS += sys_tmac_prefix=/usr/share/lib/tmac/

COMPONENT_TEST_TRANSFORMER	= $(NAWK)
COMPONENT_TEST_TRANSFORMS	= "'/TOTAL|PASS|FAIL|XFAIL|SKIP|XPASS|ERROR/'"

# Manually added build dependencies
REQUIRED_PACKAGES += developer/test/dejagnu

# Manually added dependencies
# URW fonts:
REQUIRED_PACKAGES += print/filter/ghostscript/fonts/gnu-gs-fonts-std
# 'pnmcrop', 'pnmcut', 'pnmtopng', and 'pnmtops':
REQUIRED_PACKAGES += library/netpbm
REQUIRED_PACKAGES += library/uchardet

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/uchardet
REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += text/gawk
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxmu
REQUIRED_PACKAGES += x11/library/toolkit/libxaw7
REQUIRED_PACKAGES += x11/library/toolkit/libxt
