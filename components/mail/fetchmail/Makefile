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
# Copyright (c) 2011, 2013, Oracle and/or its affiliates. All rights reserved.
# Copyright 2018, Michal Nowak
#

PREFERRED_BITS=64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		fetchmail
COMPONENT_VERSION=	6.3.26
COMPONENT_REVISION=	3
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:1c724a4e48c47e84981aef0da31cf01e0334c99b295d907d0d21d31674762a23
COMPONENT_ARCHIVE_URL=	http://sourceforge.net/projects/$(COMPONENT_NAME).berlios/files/$(COMPONENT_ARCHIVE)/download
COMPONENT_PROJECT_URL=	http://www.fetchmail.info/
COMPONENT_BUGDB=	utility/fetchmail
COMPONENT_FMRI=		mail/fetchmail

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CONFIGURE_OPTIONS  +=		am_cv_python_pythondir="$(PYTHON_VENDOR_PACKAGES)"
CONFIGURE_OPTIONS  +=		--with-kerberos5
CONFIGURE_OPTIONS  +=		--with-ssl
CONFIGURE_OPTIONS  +=		--enable-NTLM

CONFIGURE_ENV += PYTHON=$(PYTHON)

# We don't have any .so files, so we want to ship the .py and .pyc files in
# the same place as we would for 32-bit.
PYTHON_VENDOR_PACKAGES.64 =	$(PYTHON_VENDOR_PACKAGES.32)

ASLR_MODE = $(ASLR_ENABLE)

COMPONENT_POST_INSTALL_ACTION = \
    $(PYTHON) -m compileall $(PROTO_DIR)/$(PYTHON_VENDOR_PACKAGES)

# common targets
build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(TEST_64)

REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/python-2/tkinter-27
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += service/security/kerberos-5
REQUIRED_PACKAGES += system/library
