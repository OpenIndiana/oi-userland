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
# Copyright (c) 2012, 2016, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64
COMPILER= gcc
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		rsyslog
COMPONENT_VERSION=	8.4.2
COMPONENT_PROJECT_URL=	http://www.rsyslog.com/
COMPONENT_ARCHIVE_HASH=	sha256:71c3c6dac74fba2692f9fefb092cd3d22e2bd71eb702e0da06648de51b8b7b9a
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)files/download/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	service/rsyslog

TPNO=                   22636

# The documentation is in a separate download
COMPONENT_SRC_DOC=		$(COMPONENT_NAME)-doc-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE_DOC=		$(COMPONENT_SRC_DOC).tar.gz
COMPONENT_ARCHIVE_HASH_DOC=	sha256:21862b046b3504f136f9b8961466f2b248ac315c67de8742bd4a35c599f3dd48
COMPONENT_ARCHIVE_URL_DOC=	$(COMPONENT_PROJECT_URL)files/download/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE_DOC)

UNPACK_ARGS_DOC=		-r $(COMPONENT_SRC_DOC)

# There are tests, but gmake test is currently broken.
# It was working in the previous version, but not sure why
# it breaks now. Leaving it at no tests for now.
TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Automake fix, regenerates configure file to get rid of the
# automake 'probably too old' error. This fixes gmake test
# needing more than one try to run. This does not fix the
# fact that gmake test runs no tests.
COMPONENT_PRE_CONFIGURE_ACTION= cd $(SOURCE_DIR); \
				aclocal; \
				autoconf; \
				automake -a;

# gmake test will generate different outputs if run multiple
# times. This gets rid of all the unimportant output
COMPONENT_TEST_TRANSFORMS += '-e "/\(CC\).*/d" '
COMPONENT_TEST_TRANSFORMS += '-e "/\(make\).*/d" '
COMPONENT_TEST_TRANSFORMS += '-e "/\(source\).*/d" '
COMPONENT_TEST_TRANSFORMS += '-e "/\(check\).*/d" '
COMPONENT_TEST_TRANSFORMS += '-e "/\(usr\).*/d" '
COMPONENT_TEST_TRANSFORMS += '-e "/\(SOURCE_DIR\).*/d" '

# This is needed for things to be built correctly.
CFLAGS += -std=c99

# A normal 64-bit build would result in /usr/lib/$(MACH64)/rsyslog but since we
# have a self-contained eco-system, simplify things for customers and just use
# /usr/lib/rsyslog .
CONFIGURE_LIBDIR.64 =	$(CONFIGURE_LIBDIR.32)

CONFIGURE_OPTIONS +=    --enable-imsolaris
CONFIGURE_OPTIONS +=    --enable-mail
CONFIGURE_OPTIONS +=    --enable-gssapi_krb5
CONFIGURE_OPTIONS +=    --enable-gnutls
CONFIGURE_OPTIONS +=    --disable-klog
CONFIGURE_OPTIONS +=    --sbindir=$(USRLIBDIR)/rsyslog

# libgcrypt is not approved.
CONFIGURE_OPTIONS +=	--disable-libgcrypt
CONFIGURE_OPTIONS +=	--enable-extended-tests

# There are man pages in the tarball, which will require modification for
# content. Also, building them from here requires python-docutils.
CONFIGURE_OPTIONS +=	--disable-generate-man-pages

# common targets
PROTODOCDIR=	$(PROTOUSRSHAREDOCDIR)/$(COMPONENT_NAME)
# Docs to install are the tree under docs/build with some exceptions.

COMPONENT_POST_INSTALL_ACTION += \
	($(MKDIR) $(PROTODOCDIR) ; \
	cd $(COMPONENT_SRC_DOC)/build ; \
	find . \(    -name '_sources' \
	          -o -name '.doctrees' \
	          -o -name '.buildinfo' \
	          -o -name 'objects.inv' \) \
	     -prune -o -print0 \
	| cpio -pd0u $(PROTODOCDIR))

REQUIRED_PACKAGES += library/gnutls
REQUIRED_PACKAGES += library/json-c
REQUIRED_PACKAGES += library/libestr
REQUIRED_PACKAGES += library/liblogging
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += security/kerberos-5
REQUIRED_PACKAGES += shell/ksh93
