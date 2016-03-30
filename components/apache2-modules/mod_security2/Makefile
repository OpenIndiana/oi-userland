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
# Copyright (c) 2011, 2016, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		mod_security2
COMPONENT_VERSION=	2.8.0
COMPONENT_PROJECT_URL=	http://www.modsecurity.org/
COMPONENT_SRC_NAME=	modsecurity-apache
COMPONENT_SRC=		$(COMPONENT_SRC_NAME)_$(COMPONENT_VERSION)
COMPONENT_ARCHIVE_HASH=	\
    sha256:95de6ec30982e5bde7981929ba89be89488e9f237ee8c4236e064b074bbb6f28
COMPONENT_ARCHIVE_URL= \
    $(COMPONENT_PROJECT_URL)tarball/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)

TPNO=			18233

MODULES_INSTALL=
include ../modules.mk

COMPONENT_POST_UNPACK_ACTION += \
  (cd $(SOURCE_DIR); \
  $(CP) modsecurity.conf-recommended modsecurity-24.conf-recommended)

CONFIGURE_OPTIONS += LTFLAGS="--silent --tag=CC"
CONFIGURE_OPTIONS += --with-apr=`$(APXS) -q APR_CONFIG`
CONFIGURE_OPTIONS += --with-apu=`$(APXS) -q APU_CONFIG`

COMPONENT_TEST_ARGS += CFLAGS="$(CFLAGS) -DMSC_TEST"

REQUIRED_PACKAGES += library/apr-15
REQUIRED_PACKAGES += library/apr-util-15
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/pcre
REQUIRED_PACKAGES += runtime/lua
