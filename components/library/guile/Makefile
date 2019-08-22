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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		guile
COMPONENT_VERSION=	2.2.6
COMPONENT_SUMMARY=	GNU guile utility
COMPONENT_PROJECT_URL=	http://www.gnu.org/software/guile/
COMPONENT_CLASSIFICATION= Development/Other Languages
COMPONENT_FMRI=		library/guile
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
	sha256:b33576331465a60b003573541bf3b1c205936a16c407bc69f8419a527bf5c988
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/pub/gnu/guile/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	GPLv3.0, LGPLv3.0, GFDLv1.3
COMPONENT_LICENSE_FILE=	COPYING

CONFIGURE_FIX_LIBTOOL_RPATH = no

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CONFIGURE_ENV+= CPP="$(GCC_ROOT)/bin/gcc -E"

CONFIGURE_OPTIONS +=	CPPFLAGS="-I/usr/include/gmp -D__USE_LEGACY_PROTOTYPES__"
CONFIGURE_OPTIONS +=	LIBS="-lsocket -lnsl"
CONFIGURE_OPTIONS +=	--disable-static 
CONFIGURE_OPTIONS +=	--disable-error-on-warning
CONFIGURE_OPTIONS +=	ac_cv_type_complex_double=no

CONFIGURE_ENV.64 += LT_SYS_LIBRARY_PATH="/lib/$(MACH64):/usr/lib/$(MACH64)"

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

# Build dependencies
REQUIRED_PACKAGES += editor/gnu-emacs

# Auto-generated dependencies
REQUIRED_PACKAGES += library/gc
REQUIRED_PACKAGES += library/gmp
REQUIRED_PACKAGES += library/libffi
REQUIRED_PACKAGES += library/libtool/libltdl
REQUIRED_PACKAGES += library/libunistring
REQUIRED_PACKAGES += library/readline
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
