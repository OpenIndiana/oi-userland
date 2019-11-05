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
# Copyright (c) 2011, 2013, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		snort
COMPONENT_VERSION=	2.9.9.0
COMPONENT_SUMMARY=	snort - Network Intrusion and Protection Detector
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:71b147125e96390a12f3d55796ed5073df77206bd3563d84d3e5a1f19e7d7a56
COMPONENT_PROJECT_URL=	http://www.snort.org/
COMPONENT_ARCHIVE_URL=	https://snort.org/downloads/archive/snort/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=	diagnostic/snort
COMPONENT_CLASSIFICATION=	Applications/Internet
COMPONENT_LICENSE=	GPLv2, BSD, LGPLv2.1

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=/usr/gnu/bin:/usr/bin

# Need to recreate the configure script for gethrtime checks.
COMPONENT_PREP_ACTION +=	(cd $(@D); autoreconf -f -i);

CONFIGURE_OPTIONS +=	--with-libpcre-libraries="/usr/lib"
CONFIGURE_OPTIONS +=	--with-dnet-libraries="/usr/lib"
CONFIGURE_OPTIONS +=	--enable-ipv6
CONFIGURE_OPTIONS +=	--disable-static-daq

#Our nghttp2 is too old
CONFIGURE_ENV +=	ac_cv_lib_nghttp2_nghttp2_option_new=no

# Move snort shared objects to 64-bit path to stop pkglint bitching.
#COMPONENT_POST_INSTALL_ACTION += \
#	$(MV) $(PROTOUSRLIBDIR)/snort_dynamicengine $(PROTOUSRLIBDIR64); \
#	$(MV) $(PROTOUSRLIBDIR)/snort_dynamicpreprocessor $(PROTOUSRLIBDIR64) ;

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += compress/xz
REQUIRED_PACKAGES += library/pcre
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libdaq
REQUIRED_PACKAGES += system/library/libdnet
REQUIRED_PACKAGES += system/library/libpcap
REQUIRED_PACKAGES += system/library/math
