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
# Copyright 2017 Gary Mills
# Copyright 2019 Michal Nowak
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
#

BUILD_BITS=		32_and_64
BUILD_STYLE=		configure

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		guile
COMPONENT_VERSION=	2.2.7
COMPONENT_SUMMARY=	GNU guile utility
COMPONENT_PROJECT_URL=	http://www.gnu.org/software/guile/
COMPONENT_CLASSIFICATION= Development/Other Languages
COMPONENT_FMRI=		library/guile
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
	sha256:cdf776ea5f29430b1258209630555beea6d2be5481f9da4d64986b077ff37504
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/pub/gnu/guile/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	GPLv3.0, LGPLv3.0, GFDLv1.3
COMPONENT_LICENSE_FILE=	COPYING

CONFIGURE_FIX_LIBTOOL_RPATH = no

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_ENV+= CPP="$(GCC_ROOT)/bin/gcc -E"

CONFIGURE_OPTIONS +=	CPPFLAGS="-I/usr/include/gmp -D__USE_LEGACY_PROTOTYPES__"
CONFIGURE_OPTIONS +=	LIBS="-lsocket -lnsl"
CONFIGURE_OPTIONS +=	--disable-static 
CONFIGURE_OPTIONS +=	--disable-error-on-warning
CONFIGURE_OPTIONS +=	ac_cv_type_complex_double=no

CONFIGURE_ENV.64 += LT_SYS_LIBRARY_PATH="/lib/$(MACH64):/usr/lib/$(MACH64)"

# It is imperative the timestamps of .scm and .go files be preserved, and .go
# file be newer than its source, or nothing works
PKGSEND_PUBLISH_OPTIONS += -T \*.scm -T \*.go
COMPONENT_POST_INSTALL_ACTION= (find $(PROTO_DIR) -name *.go -print0 | xargs -0 touch)

# Build dependencies
# The tests need an ISO-8859-1 locale to run in
REQUIRED_PACKAGES += locale/en-extra

# Auto-generated dependencies
REQUIRED_PACKAGES += library/gc
REQUIRED_PACKAGES += library/gmp
REQUIRED_PACKAGES += library/libffi
REQUIRED_PACKAGES += library/libtool/libltdl
REQUIRED_PACKAGES += library/libunistring
REQUIRED_PACKAGES += library/readline
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
