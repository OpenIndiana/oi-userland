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

COMPONENT_NAME=		stunnel
COMPONENT_VERSION=	4.56
COMPONENT_REVISION=	1
COMPONENT_PROJECT_URL=	http://www.stunnel.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:9cae2cfbe26d87443398ce50d7d5db54e5ea363889d5d2ec8d2778a01c871293

COMPONENT_ARCHIVE_URL=	http://pkgs.fedoraproject.org/repo/pkgs/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)/ac4c4a30bd7a55b6687cbd62d864054c/$(COMPONENT_ARCHIVE)

COMPONENT_BUGDB=	utility/stunnel

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

# need /usr/perl5/bin on path to access pod2man perl script, used by 
# the build to create docs. 
# Perl 5.10 pod2man does not recognize "-u" argument.
COMPONENT_BUILD_ENV +=  PATH=/usr/perl5/5.16/bin:$(PATH)

CPPFLAGS +=	"-DPIDFILE='\"/var/run/stunnel.pid\"'"

# used to generate the 64-bit interposer location
CPPFLAGS += -DMACH64='\"$(MACH64)\"'

CONFIGURE_OPTIONS +=	--disable-fips
CONFIGURE_OPTIONS +=	--enable-ipv6
CONFIGURE_OPTIONS +=	--sysconfdir=$(ETCDIR)
CONFIGURE_OPTIONS +=	CPPFLAGS="$(CPPFLAGS)"
CONFIGURE_OPTIONS +=	CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS +=	LDFLAGS="$(LDFLAGS)"

# used to generate LD_PRELOAD_* interposer pathnames
COMPONENT_BUILD_ARGS += pkglibdir=/usr/lib/stunnel

COMPONENT_PRE_INSTALL_ACTION = \
	$(MKDIR) $(PROTOETCDIR)/stunnel ; \
	$(TOUCH) $(PROTOETCDIR)/stunnel/stunnel.pem

PKG_PROTO_DIRS +=	$(COMPONENT_DIR)/files

ASLR_MODE = $(ASLR_ENABLE)

# common targets
build:          $(BUILD_32_and_64)

install:        $(INSTALL_32_and_64)

test:           $(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
