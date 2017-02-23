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
# Copyright (c) 2013, 2017, Oracle and/or its affiliates. All rights reserved.
#
COMPILER= gcc
BUILD_BITS= 64
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		webalizer
COMPONENT_VERSION=	2.23.8
HUMAN_VERSION=		2.23-08
COMPONENT_PROJECT_URL=	http://www.mrunix.net/webalizer/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC)-src.tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:b37524fbd98e97052a80d59f75e69f857468752cf74cc0eb0972e5fab02eb6f7
COMPONENT_ARCHIVE_URL=	ftp://ftp.mrunix.net/pub/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_ANITYA_ID=	13271

TPNO=			27276

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Fix 64-bit linking via compiler.
LDFLAGS += $(CC_BITS)

COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))

# Adjust the log file pathname in the sample configuration file.
COMPONENT_PRE_BUILD_ACTION += \
	$(GSED) -i -e 's?lib/httpd/logs/?apache2/2.4/logs/?' \
		$(SOURCE_DIR)/sample.conf

CONFIGURE_OPTIONS +=	--enable-dns
CONFIGURE_OPTIONS +=	--with-gd=$(USRINCDIR)/gd2

# webalizer is defining u_int64_t but also uses db.h
# which typedefs it, and parfait and gcc 4.7 aren't happy.
CC += -Du_int64_t=uint64_t
CONFIGURE_OPTIONS +=	c_cv_type_u_int64_t=yes

REQUIRED_PACKAGES += database/berkeleydb-5
REQUIRED_PACKAGES += library/gd
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library/math
