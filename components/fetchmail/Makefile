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
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		fetchmail
COMPONENT_VERSION=	6.3.26
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
    sha256:79b4c54cdbaf02c1a9a691d9948fcb1a77a1591a813e904283a8b614b757e850
COMPONENT_ARCHIVE_URL=	https://sourceforge.net/projects/$(COMPONENT_NAME)/files/branch_6.3/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	http://www.fetchmail.info/

TPNO=			29615

# Enable adiheap and adistack security extensions
ADIHEAP_MODE =	$(ADIHEAP_ENABLE)
ADISTACK_MODE =	$(ADISTACK_ENABLE)

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS  +=		PYTHON="$(PYTHON.2.7.32)"
CONFIGURE_OPTIONS  +=		--with-kerberos5
CONFIGURE_OPTIONS  +=		--with-ssl
CONFIGURE_OPTIONS  +=		--enable-NTLM

# Change the shebang line to use Python 2.7 explicitly, and drop the
# fixed file into /usr/bin, where our package manifest expects it.
COMPONENT_POST_INSTALL_ACTION = \
    $(GSED) -e "s|/usr/bin/env python|$(PYTHON.2.7.32)|" \
	$(PROTO_DIR)/usr/lib/python2.7/site-packages/fetchmailconf.py > \
	$(PROTO_DIR)$(USRBIN.32)/fetchmailconf

COMPONENT_TEST_TRANSFORMS += \
	'-n ' \
	'-e "/SKIP/p" ' \
	'-e "/PASS/p" ' \
	'-e "/FAIL/p" ' \
	'-e "/^=======/p" ' \
	'-e "/were not run/p" ' \
	'-e "/passed/p" '

REQUIRED_PACKAGES += library/python/tkinter-27
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += security/kerberos-5
ifeq ($(OS_VERSION),5.11)
REQUIRED_PACKAGES += service/security/kerberos-5
endif
REQUIRED_PACKAGES += shell/ksh93
