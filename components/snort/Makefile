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
# Copyright (c) 2011, 2015, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		snort
COMPONENT_VERSION=	2.9.6.2
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:8e1d7fc5e1523a786d845ca0102cc474abfcebfcc7e964a1653680034b5b5d77
COMPONENT_PROJECT_URL=	http://www.snort.org/
COMPONENT_ARCHIVE_URL=	http://sourceforge.net/projects/snort.mirror/files/Snort%202.9.6.2/$(COMPONENT_ARCHIVE)/download
COMPONENT_BUGDB=	utility/snort

TPNO=			19385

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATCH_LEVEL =		0

# without this we bus error on sparc. sadly I don't see any patches
# that might relate from the upstream (though maybe that's really
# "happily", as this is simpler)
studio_ALIGN.sparc.64=  -xmemalign=1i

# Need to recreate the configure script for gethrtime checks.
COMPONENT_PREP_ACTION +=	(cd $(@D); autoconf);

# This option has the side-effect of getting the bindir lines correct in
# snort_output.pc, snort_preproc.pc and snort.pc under
# /usr/lib/$(MACH64)/pkgconfig/
CONFIGURE_OPTIONS +=	--bindir=/usr/bin

CONFIGURE_OPTIONS +=	--with-libpcre-libraries="/usr/lib/$(MACH64)"
CONFIGURE_OPTIONS +=	--with-dnet-libraries="/usr/lib/$(MACH64)"
CONFIGURE_OPTIONS +=	--without-mysql
CONFIGURE_OPTIONS +=	--without-postgresql
CONFIGURE_OPTIONS +=	--enable-zlib
CONFIGURE_OPTIONS +=	--enable-ipv6
CONFIGURE_OPTIONS +=	--disable-static-daq
CONFIGURE_OPTIONS +=	CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS +=	LDFLAGS="$(LDFLAGS)"

# Move snort shared objects to 64-bit path to stop pkglint bitching.
COMPONENT_POST_INSTALL_ACTION += \
	$(MV) $(PROTOUSRLIBDIR)/snort_dynamicengine $(PROTOUSRLIBDIR64); \
	$(MV) $(PROTOUSRLIBDIR)/snort_dynamicpreprocessor $(PROTOUSRLIBDIR64) ;

# Enable ASLR for this component
ASLR_MODE = $(ASLR_ENABLE)

# common targets
configure:	$(CONFIGURE_64)

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(NO_TESTS)

system-test:    $(NO_TESTS)


REQUIRED_PACKAGES += developer/lexer/flex
REQUIRED_PACKAGES += developer/parser/bison
REQUIRED_PACKAGES += library/pcre
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/security/openssl/openssl-fips-140
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/core-os
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libdaq
REQUIRED_PACKAGES += system/library/libdnet
REQUIRED_PACKAGES += system/library/libpcap
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/network
