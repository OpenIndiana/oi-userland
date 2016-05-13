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
COMPONENT_VERSION=	6.3.22
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:09093168552119e962617f86f2713564cf6e3fe7fd32d6799aa0b87df28f1e89
COMPONENT_ARCHIVE_URL=	http://download.berlios.de/fetchmail/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	http://fetchmail.berlios.de/

TPNO=			8416

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
	'-e "s|^.*$(CC).*$$|XXX_CC_XXX|"' \
	'-e "/^XXX_CC_XXX$$/d"'

# If there is no mediator, use MIT.  Note, once all userland build systems have
# the Userland security/kerberos-5 pkg installed this logic can be removed.
KRB5_API = $(shell pkg mediator -H kerberos5 2>/dev/null | nawk '{print $$4;}')

REQUIRED_PACKAGES += library/python/tkinter-27
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += runtime/python-27
ifeq ($(KRB5_API), solaris)
    # require the solaris version of Kerberos/GSS
    REQUIRED_PACKAGES += service/security/kerberos-5
else
    # require the Userland version of Kerberos/GSS
    REQUIRED_PACKAGES += security/kerberos-5
endif
REQUIRED_PACKAGES += shell/ksh93
