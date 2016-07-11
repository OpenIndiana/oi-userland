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
COMPONENT_VERSION=	8.15.0
COMPONENT_PROJECT_URL=	http://www.rsyslog.com/
COMPONENT_ARCHIVE_HASH=	sha256:9ed6615a8503964290471e98ed363f3975b964a34c2d4610fb815a432aadaf59
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)files/download/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	service/rsyslog

TPNO=                   28284

# The documentation is in a separate download
COMPONENT_SRC_DOC=		$(COMPONENT_NAME)-doc-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE_DOC=		$(COMPONENT_SRC_DOC).tar.gz
COMPONENT_ARCHIVE_HASH_DOC=	sha256:3462402165a3ff34ceff23db20382a14bd3727131994f140a004f4872a01c12a
COMPONENT_ARCHIVE_URL_DOC=	$(COMPONENT_PROJECT_URL)files/download/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE_DOC)

UNPACK_ARGS_DOC=		-r $(COMPONENT_SRC_DOC)

# There are tests, but gmake test is currently broken.
# It was working in the previous version, but not sure why
# it breaks now. Leaving it at no tests for now.
TEST_TARGET= $(NO_TESTS)

# Requires mysql-57 not available on S11.
ifeq ($(BUILD_TYPE), evaluation)
BUILD_64=
INSTALL_64=
PUBLISH_STAMP=
endif

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
PKG_CONFIG_PATH = /usr/lib/pkgconfig/gnutls-3

# The configure script runs the pkg-config command. This allows it to
# find the non-default GnuTLS v3 library.
PKG_CONFIG_PATH.64 := $(PKG_CONFIG_PATH.64)/gnutls-3:$(PKG_CONFIG_PATH.64)
LDFLAGS += -L$(USRLIBDIR64)/gnutls-3

# Rsyslog sources contain __FILE__ macros which contain full path to the workspace
# This may appear in debug output which is not nice. By specifying the source
# path relative we force the macro to be relative path too.
CONFIGURE_OPTIONS +=    --srcdir=../../$(COMPONENT_NAME)-$(COMPONENT_VERSION)
CONFIGURE_OPTIONS +=    --enable-imsolaris
CONFIGURE_OPTIONS +=    --enable-mail
CONFIGURE_OPTIONS +=    --enable-gssapi_krb5
CONFIGURE_OPTIONS +=    --enable-gnutls
CONFIGURE_OPTIONS +=    --disable-klog
CONFIGURE_OPTIONS +=    --sbindir=$(USRLIBDIR)/rsyslog

CONFIGURE_OPTIONS +=    --enable-imfile
CONFIGURE_OPTIONS +=    --enable-impstats
CONFIGURE_OPTIONS +=    --enable-mysql
CONFIGURE_ENV     +=    "MYSQL_CONFIG=/usr/mysql/5.7/bin/mysql_config"
CONFIGURE_OPTIONS +=    --enable-omstdout
CONFIGURE_OPTIONS +=    --enable-omuxsock

# libgcrypt is not approved.
CONFIGURE_OPTIONS +=	--disable-libgcrypt
CONFIGURE_OPTIONS +=	--enable-extended-tests

# There are man pages in the tarball, which will require modification for
# content. Also, building them from here requires python-docutils.
CONFIGURE_OPTIONS +=	--disable-generate-man-pages

# Make the build verbose, show executed commands
COMPONENT_BUILD_ARGS += AM_DEFAULT_VERBOSITY=1

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

REQUIRED_PACKAGES += database/mysql-57
REQUIRED_PACKAGES += database/mysql-57/library
REQUIRED_PACKAGES += library/gnutls-3
REQUIRED_PACKAGES += library/json-c
REQUIRED_PACKAGES += library/libestr
REQUIRED_PACKAGES += library/liblogging
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += security/kerberos-5
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/core-os
