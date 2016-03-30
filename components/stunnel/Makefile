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
# Copyright (c) 2013, 2016, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		stunnel
COMPONENT_VERSION=	5.18
COMPONENT_PROJECT_URL=	http://www.stunnel.org/
COMPONENT_ARCHIVE_HASH=	\
	sha256:0532c0a2f8de3da1ab625e384146501ce5936fac63d01561c3a9bf652b692317

COMPONENT_ARCHIVE_URL=	http://pkgs.fedoraproject.org/repo/pkgs/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)/04f90ffbb65ffa289a5b1db2c52950f5/$(COMPONENT_ARCHIVE)

COMPONENT_PREP_ACTION += (cd $(@D) ; autoreconf -f)

TPNO=                   24738

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# need /usr/perl5/bin on path to access pod2man perl script, used by 
# the build to create docs
COMPONENT_BUILD_ENV +=  PATH=$(USRDIR)/perl5/bin:$(PATH)

CPPFLAGS +=	"-DPIDFILE='\"/var/run/stunnel.pid\"'"

# used to generate the 64-bit interposer location
CPPFLAGS += -DMACH64='\"$(MACH64)\"'

CONFIGURE_OPTIONS +=	--disable-fips
CONFIGURE_OPTIONS +=	--enable-ipv6
CONFIGURE_OPTIONS +=	--sysconfdir=$(ETCDIR)

# used to generate LD_PRELOAD_* interposer pathnames
COMPONENT_BUILD_ARGS += pkglibdir=$(USRLIBDIR)/stunnel

COMPONENT_PRE_INSTALL_ACTION = \
	$(MKDIR) $(PROTOETCDIR)/stunnel ; \
	$(TOUCH) $(PROTOETCDIR)/stunnel/stunnel.pem

REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += system/core-os
REQUIRED_PACKAGES += system/network
