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

COMPONENT_NAME=		privoxy
COMPONENT_VERSION=	3.0.23
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)-stable
COMPONENT_ARCHIVE=	$(COMPONENT_SRC)-src.tar.gz
COMPONENT_PROJECT_URL=	http://www.privoxy.org/
COMPONENT_ARCHIVE_HASH=	\
    sha256:b75f6b8b8409ed7ac6c3a00dcd608a45180f07bfa46658c836d5c6ffc4dc25c4
COMPONENT_ARCHIVE_URL=	http://downloads.sourceforge.net/ijbswa/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/privoxy

TPNO=		 22977	

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))

COMPONENT_PREP_ACTION = \
        (cd $(@D) ; \
            autoheader; \
            autoconf )

CC += $(CC_BITS)

# Needed to installed most of the files into the proto area.
CONFIGURE_OPTIONS +=	--sysconfdir=/etc
CONFIGURE_OPTIONS +=	--localstatedir=/var
CONFIGURE_OPTIONS +=	--sbindir=$(CONFIGURE_PREFIX)/lib

ASLR_MODE = $(ASLR_ENABLE)

# common targets
configure:	$(CONFIGURE_64)

build:		$(BUILD_64)

install:	$(INSTALL_64)
	$(CP) $(BUILD_DIR_64)/templates/* $(PROTOETCDIR)/templates

# Regression tests exist for privoxy in tools/privoxy-regression-test.pl,
# however these are not applicable to us since they violate the company policy
# of not allowing third-party programs to communicate outside the company.
#
# To test privoxy, follow the instructions in the privoxy quick start guide:
# http://www.privoxy.org/user-manual/quickstart.html
# 
# Privoxy is disabled by default, so make sure to enable it if necessary:
# 	# svcs privoxy
#	# svcadm enable privoxy
# You may need to set the forward address in /etc/privoxy/config to the 
# Oracle proxy to access pages in your web browser with privoxy running. 

test: 		$(NO_TESTS)

system-test:    $(NO_TESTS)


REQUIRED_PACKAGES += library/pcre
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/core-os
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/network
