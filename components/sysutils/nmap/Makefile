
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
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
# Copyright 2016 Jim Klimov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= 		nmap
COMPONENT_VERSION=		7.40
COMPONENT_PROJECT_URL=	http://nmap.org/
COMPONENT_FMRI=			diagnostic/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	System/Administration and Configuration
COMPONENT_SUMMARY=		Network exploration tool and security / port scanner
COMPONENT_DESCRIPTION=	Nmap is useful for inventorying the network, managing \
service upgrade schedules, and monitoring host or service uptime
COMPONENT_SRC=			$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=		$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
	sha256:9e14665fffd054554d129d62c13ad95a7b5c7a046daa2290501909e65f4d3188
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)dist/$(COMPONENT_ARCHIVE)
COMPONENT_SIG_URL=	$(COMPONENT_PROJECT_URL)dist/sigs/$(COMPONENT_ARCHIVE).asc	
COMPONENT_BUGDB=		utility/nmap
COMPONENT_LICENSE=		GPLv2,OpenSSL,SSLeay
# Note: This license file incorporates nmap COPYING and OpenSSL license text
COMPONENT_LICENSE_FILE=	nmap.license

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PKG_OPTIONS +=	-D COMPONENT_DESCRIPTION="$(COMPONENT_DESCRIPTION)"
PKG_OPTIONS +=	-D PYTHON_VERSION="$(PYTHON_VERSION)"

COMPONENT_PREP_ACTION = (cd $(@D)/libdnet-stripped && autoconf)

COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_OPTIONS  +=   CPPFLAGS="$(CPPFLAGS)"
CONFIGURE_OPTIONS  +=   LIBS="-lsocket -lnsl"
CONFIGURE_OPTIONS  +=   PYTHON="$(PYTHON)"
CONFIGURE_OPTIONS  +=   --srcdir=$(BUILD_DIR_$(BITS))
CONFIGURE_OPTIONS  +=   --localstatedir=/var
CONFIGURE_OPTIONS  +=   --without-localdirs
CONFIGURE_OPTIONS  +=   --with-zenmap
CONFIGURE_OPTIONS  +=   --with-openssl
CONFIGURE_OPTIONS  +=   --with-libpcap
CONFIGURE_OPTIONS  +=   --with-libpcre
# libdnet-stripped fails to build with external lua
CONFIGURE_OPTIONS  +=   --with-liblua=included
CONFIGURE_OPTIONS  +=   --with-ncat
CONFIGURE_OPTIONS  +=   --with-ndiff

# pkgdepend doesn't like the first line of a Python script to be:
# '#!/usr/bin/env python' so turn it into '#!/usr/bin/python2.7'
COMPONENT_POST_INSTALL_ACTION += \
        $(GSED) -e 's?env python?python$(PYTHON_VERSION)?' \
                -i $(PROTOUSRBINDIR)/uninstall_zenmap && \
        $(GSED) -e 's?env python?python$(PYTHON_VERSION)?' \
                -i $(PROTOUSRBINDIR)/uninstall_ndiff

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/pcre
REQUIRED_PACKAGES += library/python/pygobject-27
REQUIRED_PACKAGES += library/python/pygtk2-27
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library/libpcap
REQUIRED_PACKAGES += system/library/math
