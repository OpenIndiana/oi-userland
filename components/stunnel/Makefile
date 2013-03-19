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

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		stunnel
COMPONENT_VERSION=	4.29
COMPONENT_PROJECT_URL=	http://stunnel.mirt.net/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:018064e852a2a125bcfb4b81baa77b5701ccf6aabe6a47564bfc046b18d11f9b

# ftp://stunnel.mirt.net/stunnel/stunnel-4.29.tar.gz is no longer there.
COMPONENT_ARCHIVE_URL=	http://pkgs.fedoraproject.org/repo/pkgs/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)/14dc3f8412947f0548975cbce74d6863/$(COMPONENT_ARCHIVE)

COMPONENT_BUGDB=	utility/stunnel

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

COMPONENT_PREP_ACTION =	(cd $(@D) ; autoreconf -if)

# need /usr/perl5/bin on path to access pod2man perl script, used by 
# the build to create docs
COMPONENT_BUILD_ENV +=  PATH=/usr/perl5/bin:$(PATH)

CPPFLAGS +=	"-DPIDFILE='\"/var/run/stunnel.pid\"'"

CONFIGURE_OPTIONS +=	--disable-fips
CONFIGURE_OPTIONS +=	--enable-ipv6
CONFIGURE_OPTIONS +=	--sysconfdir=$(ETCDIR)
CONFIGURE_OPTIONS +=	CPPFLAGS="$(CPPFLAGS)"
CONFIGURE_OPTIONS +=	CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS +=	LDFLAGS="$(LDFLAGS)"

COMPONENT_PRE_INSTALL_ACTION = \
	$(MKDIR) $(PROTOETCDIR)/stunnel ; \
	$(TOUCH) $(PROTOETCDIR)/stunnel/stunnel.pem

PKG_PROTO_DIRS +=	$(COMPONENT_DIR)/files

ASLR_MODE = $(ASLR_ENABLE)

# common targets
build:          $(BUILD_32_and_64)

install:        $(INSTALL_32_and_64)

test:           $(NO_TESTS)

BUILD_PKG_DEPENDENCIES =        $(BUILD_TOOLS)

include ../../make-rules/depend.mk
