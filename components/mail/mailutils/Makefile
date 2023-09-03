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
# Copyright 2021, Klaus Ziegler
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		mailutils
COMPONENT_VERSION=	3.16
COMPONENT_REVISION=	1
COMPONENT_SUMMARY=	GNU-mailutils provides IMAP4D LMTPD MDA POP3D servers and various mail programs
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:041d158d308c0376184388e9c936cfa841a51cdc25d4db75984a771a3fa002c0
COMPONENT_ARCHIVE_URL=	https://ftp.gnu.org/gnu/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://mailutils.org/
COMPONENT_FMRI=		mail/mailutils
COMPONENT_CLASSIFICATION=	Applications/Internet
COMPONENT_LICENSE=	GPLv3,LGPLv3

include $(WS_MAKE_RULES)/common.mk

PKG_MACROS += PYVER=$(PYTHON_VERSION)

CONFIGURE_ENV += PYTHON_CONFIG=/usr/bin/python3.9-config

# cpp flags.
CONFIGURE_ENV += CPPFLAGS="-I/usr/include/openldap \
		-I$(MYSQL_HOME)/include \
		-I$(PG_HOME)/include"

# library link flags.
CONFIGURE_ENV += LIBS="-lldap-2.6"
# needed for 01-pg-mariadb.patch
CONFIGURE_ENV += MYSQL_LIB="$(MYSQL_LIBDIR)"
CONFIGURE_ENV += PG_LIB="$(PG_LIBDIR)"

CONFIGURE_OPTIONS  +=		--libexecdir=/usr/gnu/libexec
CONFIGURE_OPTIONS  +=		--enable-static=no
CONFIGURE_OPTIONS  +=		--with-ldap
CONFIGURE_OPTIONS  +=		--with-mysql
CONFIGURE_OPTIONS  +=		--with-postgres
CONFIGURE_OPTIONS  +=		--with-pythondir=$(PYTHON_LIB)

COMPONENT_POST_INSTALL_ACTION = \
	( cd $(PROTOUSRLIBDIR)/python$(PYTHON_VERSION)/vendor-packages/mailutils ; \
		ln c_api.so c_api.cpython-39.so ; \
	  cd $(PROTOUSRSHAREDIR)/info ; rm dir )

COMPONENT_TEST_TRANSFORMS= \
	'-e "/^\/usr\/gnu\/bin\/make/d" ' \
	'-e "/^make/d" ' \
	'-e "/^Making/d" '

# build dependencies.
REQUIRED_PACKAGES += editor/gnu-emacs

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += $(MYSQL_LIBRARY_PKG)
REQUIRED_PACKAGES += $(PG_LIBRARY_PKG)
REQUIRED_PACKAGES += database/berkeleydb-5
REQUIRED_PACKAGES += library/database/gdbm
REQUIRED_PACKAGES += library/fribidi
REQUIRED_PACKAGES += library/gnutls-3
REQUIRED_PACKAGES += library/guile
REQUIRED_PACKAGES += library/libgsasl
REQUIRED_PACKAGES += library/libtool/libltdl
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += library/openldap
REQUIRED_PACKAGES += library/readline
REQUIRED_PACKAGES += service/security/kerberos-5
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/security/gss
