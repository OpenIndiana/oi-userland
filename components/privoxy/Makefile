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
# Copyright (c) 2011, 2017, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		privoxy
COMPONENT_VERSION=	3.0.24
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)-stable
COMPONENT_ARCHIVE=	$(COMPONENT_SRC)-src.tar.gz
COMPONENT_PROJECT_URL=	http://www.privoxy.org/
COMPONENT_ARCHIVE_HASH=	\
    sha256:a381f6dc78f08de0d4a2342d47a5949a6608073ada34b933137184f3ca9fb012
COMPONENT_ARCHIVE_URL=	http://downloads.sourceforge.net/ijbswa/$(COMPONENT_ARCHIVE)
COMPONENT_ANITYA_ID=	3712

TPNO=		 27274

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Fix 64-bit linking via compiler.
LDFLAGS += $(CC_BITS)

COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))

COMPONENT_PREP_ACTION = \
        (cd $(@D) ; \
            autoheader; \
            autoconf )

# Needed to installed most of the files into the proto area.
CONFIGURE_OPTIONS +=	--sysconfdir=$(ETCDIR)
CONFIGURE_OPTIONS +=	--localstatedir=$(VARDIR)
CONFIGURE_OPTIONS +=	--sbindir=$(CONFIGURE_PREFIX)/lib

# common targets
COMPONENT_POST_INSTALL_ACTION += \
	($(CP) $(BUILD_DIR_64)/templates/* $(PROTOETCDIR)/templates)

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

REQUIRED_PACKAGES += library/pcre
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/core-os
REQUIRED_PACKAGES += system/network
