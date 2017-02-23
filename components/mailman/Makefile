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
# Copyright (c) 2014, 2017, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		mailman
COMPONENT_VERSION=	2.1.18-1
IPS_COMPONENT_VERSION=	2.1.18.1
COMPONENT_PROJECT_URL=	http://www.list.org/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tgz
COMPONENT_ARCHIVE_HASH=	sha256:ce70ed8b58d719cab80758f39a7258c0a28f8e8e859facdaa8c29add620a5c2c
COMPONENT_ANITYA_ID=	1875

TPNO=			18736

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/gnu-component.mk

CONFIGURE_ENV	+=	MAILMAN_USER=mailman
CONFIGURE_ENV	+=	MAILMAN_GROUP=mailman

CONFIGURE_PREFIX= $(USRLIBDIR)/mailman
CONFIGURE_OPTIONS +=	--with-var-prefix=$(VARDIR)/mailman
CONFIGURE_OPTIONS +=	--with-mail-gid=other
CONFIGURE_OPTIONS +=	--with-cgi-gid=webservd
CONFIGURE_OPTIONS +=	--with-python=$(PYTHON.2.7)
CONFIGURE_OPTIONS +=	--without-permcheck
CONFIGURE_OPTIONS +=	--with-mailhost=localhost
CONFIGURE_OPTIONS +=	--with-urlhost=localhost

# Copy generated file to proto area.  Then py-compile several files that are
# used as modules in a devious way.
COMPONENT_POST_INSTALL_ACTION=	\
	($(CP) $(BUILD_DIR_64)/Mailman/Defaults.py \
		$(PROTOUSRLIBDIR)/mailman/Mailman/ ; \
	 $(PYTHON.2.7) -m py_compile $(PROTOUSRLIBDIR)/mailman/*/paths.py \
		$(PROTOUSRLIBDIR)/mailman/Mailman/Defaults.py)

REQUIRED_PACKAGES += library/python/dnspython-27
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/core-os
REQUIRED_PACKAGES += system/network
