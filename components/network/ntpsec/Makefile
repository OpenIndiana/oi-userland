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
# Copyright 2019, Michal Nowak
#

PREFERRED_BITS=		64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		ntpsec
COMPONENT_VERSION=	1.1.8
COMPONENT_SUMMARY=	'Network time services'
COMPONENT_DESCRIPTION=	A secure, hardened and improved Network Time Protocol implementation
COMPONENT_PROJECT_URL=	https://www.ntpsec.org/
COMPONENT_SRC=		$(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	 \
	sha256:8445827a4d5029da508a11e9c8e7958db839f73b39de612ab3909244f89a1340
COMPONENT_ARCHIVE_URL=	ftp://ftp.ntpsec.org/pub/releases/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		service/network/ntpsec
COMPONENT_CLASSIFICATION=	System/Services
COMPONENT_LICENSE=	'BSD-2-Clause, NTP, BSD-3-Clause, MIT'

PYTHON_VERSION = 3.5

PYTHON_VERSIONS = 3.5

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/waf.mk
include $(WS_MAKE_RULES)/ips.mk

# Although NTPSec components are tested with python3 and can run with
# either python2 or python3, the default shebang lines just point at
# '#!/usr/bin/env python'; we need to fix them up to use python3.
# (NB: there was discussion on the ntpsec mailing list about providing
#      an option to do this automatically but it has so far been rejected.
#      Distributions are rolling their own patches, e.g.
#      https://sources.debian.org/src/ntpsec/1.1.2+dfsg1-4/debian/patches/hardcode-python3-path.patch/
# Scripting it is more future-proof
COMPONENT_PREP_ACTION = ( sed -i '1s|/usr/bin/env python|/usr/bin/python$(PYTHON_VERSION)|' `find $(@D) -type f`; )

CFLAGS +=	-D__EXTENSIONS__

CONFIGURE_OPTIONS +=	--prefix=/usr
CONFIGURE_OPTIONS +=	--sysconfdir=/etc/inet
CONFIGURE_OPTIONS +=	--refclock=all
CONFIGURE_OPTIONS +=	--define=CONFIG_FILE=/etc/inet/ntp.conf

COMPONENT_POST_INSTALL_ACTION += \
	$(CP) $(@D)/attic/ntpdate $(PROTO_DIR)/usr/bin/ ; \
	$(MKDIR) -p $(PROTO_DIR)/var/ntp/ntpstats ; \
	$(TOUCH) $(PROTO_DIR)/var/ntp/ntpstats/.ghost ;

COMPONENT_TEST_TARGETS = check

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(TEST_64)

# Build requirements
REQUIRED_PACKAGES += text/asciidoc
# ntpviz requirement (not shipped)
#REQUIRED_PACKAGES += library/python/psutil-35
# Auto-generated dependencies
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += runtime/python-35
REQUIRED_PACKAGES += service/network/dns/mdns
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
