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
# Copyright 2017 Gary Mills
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=           guile
COMPONENT_VERSION=        1.8.8
COMPONENT_REVISION=       2
COMPONENT_SUMMARY=        GNU guile utility
COMPONENT_PROJECT_URL=    http://www.gnu.org/software/guile/
COMPONENT_CLASSIFICATION= Development/Other Languages
COMPONENT_FMRI=           library/guile
COMPONENT_SRC=            $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=        $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
  sha256:c3471fed2e72e5b04ad133bbaaf16369e8360283679bcf19800bc1b381024050
COMPONENT_ARCHIVE_URL=    http://ftp.gnu.org/pub/gnu/guile/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=        LGPLv2.1, FDLv1.2

CONFIGURE_FIX_LIBTOOL_RPATH = no

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PREP_ACTION = (cd $(@D) && libtoolize -f && autoreconf -fi)

CONFIGURE_ENV+= CPP="$(GCC_ROOT)/bin/gcc -E"
CONFIGURE_OPTIONS +=	CPPFLAGS="-I/usr/include/gmp -D__USE_LEGACY_PROTOTYPES__"
CONFIGURE_OPTIONS +=	--disable-static 
CONFIGURE_OPTIONS +=	--disable-error-on-warning
CONFIGURE_OPTIONS +=	ac_cv_type_complex_double=no

CONFIGURE_ENV.64 += LT_SYS_LIBRARY_PATH="/lib/$(MACH64):/usr/lib/$(MACH64)"

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

# FAIL: time.test: strptime: GNU %s format: gmtoff on EST+5
test:		 $(NO_TESTS)

# Build dependencies
REQUIRED_PACKAGES += editor/gnu-emacs

# Auto-generated dependencies
REQUIRED_PACKAGES += library/gmp
REQUIRED_PACKAGES += library/libtool/libltdl
REQUIRED_PACKAGES += library/readline
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
