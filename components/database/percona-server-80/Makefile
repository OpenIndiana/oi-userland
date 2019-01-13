#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2011-2013, EveryCity Ltd. All rights reserved.
# Copyright 2018-2019, Michal Nowak
# 

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		percona-server
COMPONENT_VERSION=	8.0.13-3
IPS_COMPONENT_VERSION=	8.0.13.3
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL=	https://www.percona.com/
COMPONENT_ARCHIVE_HASH=	sha256:ab00626775b85ea506c1d992d66acee50f0bfbde54b830731f61652e87ff93da
COMPONENT_ARCHIVE_URL=	https://www.percona.com/downloads/Percona-Server-8.0/Percona-Server-$(COMPONENT_VERSION)/source/tarball/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE_FILE=	LICENSE
COMPONENT_LICENSE=	GPLv2

# We need specific boost version
COMPONENT_ARCHIVE_1= boost_1_67_0.tar.gz
COMPONENT_ARCHIVE_HASH_1= \
	sha256:8aa4e330c870ef50a896634c931adf468b21f8a69b77007e45c444151229f665
COMPONENT_ARCHIVE_URL_1= http://downloads.sourceforge.net/project/boost/boost/1.67.0/$(COMPONENT_ARCHIVE_1)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/cmake.mk
include $(WS_MAKE_RULES)/ips.mk

GCC_VERSION = 7

COMPONENT_POST_UNPACK_ACTION = \
	( $(MKDIR) $(BUILD_DIR)/boost && /usr/gnu/bin/tar -C $(BUILD_DIR)/boost -xzf $(USERLAND_ARCHIVES)$(COMPONENT_ARCHIVE_1) )

CMAKE_PREFIX=/usr/percona-server/8.0
CONFDIR=/etc/percona-server/8.0
DATA_PREFIX=/var/percona-server/8.0

CMAKE_PLUGINDIR.32 =	lib/plugin
CMAKE_PLUGINDIR.64 =	lib/$(MACH64)/plugin

CMAKE_OPTIONS+= -DCMAKE_BUILD_TYPE=RelWithDebInfo
CMAKE_OPTIONS+= -DBUILD_CONFIG=mysql_release
CMAKE_OPTIONS+= -DFEATURE_SET=community
CMAKE_OPTIONS+=	-DWITH_SSL=system
CMAKE_OPTIONS+=	-DWITHOUT_TOKUDB=1
CMAKE_OPTIONS+= -DINSTALL_LAYOUT=SVR4
CMAKE_OPTIONS+= -DINSTALL_BINDIR=$(CMAKE_BINDIR.$(BITS))
CMAKE_OPTIONS+= -DINSTALL_INCLUDEDIR=include
CMAKE_OPTIONS+= -DINSTALL_INFODIR=bin
CMAKE_OPTIONS+= -DINSTALL_LIBDIR=$(CMAKE_LIBDIR.$(BITS))
CMAKE_OPTIONS+= -DINSTALL_PLUGINDIR=$(CMAKE_PLUGINDIR.$(BITS))
CMAKE_OPTIONS+= -DINSTALL_MANDIR=man
CMAKE_OPTIONS+= -DINSTALL_SHAREDIR=share
CMAKE_OPTIONS+= -DINSTALL_MYSQLSHAREDIR=share
CMAKE_OPTIONS+= -DINSTALL_SBINDIR=$(CMAKE_BINDIR.$(BITS))
CMAKE_OPTIONS+= -DINSTALL_SCRIPTDIR=$(CMAKE_BINDIR.$(BITS))
CMAKE_OPTIONS+= -DMYSQL_DATADIR=$(DATA_PREFIX)/data
CMAKE_OPTIONS+= -DSYSCONFDIR=$(CONFDIR)
CMAKE_OPTIONS+= -DENABLE_DTRACE=on
CMAKE_OPTIONS+= -DINSTALL_SUPPORTFILESDIR=share/mysql
CMAKE_OPTIONS+= -DWITH_BOOST=$(BUILD_DIR)/boost
CMAKE_OPTIONS+= -DINSTALL_SECURE_FILE_PRIVDIR=""

# gcc invocation in some link.txt file is missing -m$(BITS) parameter
# and it makes 64-bit build to fail, this is a quick hack to make it build
# for now, cmake build system needs a proper fix
COMPONENT_POST_CMAKE_ACTION.32=
COMPONENT_POST_CMAKE_ACTION.64= find $(@D) -type f -name link.txt \
    -exec perl -pi -e 's/gcc\ \ -fPIC/\/gcc\ -m64\ -fPIC/' {} \;
COMPONENT_POST_CMAKE_ACTION=$(COMPONENT_POST_CMAKE_ACTION.$(BITS))

COMPONENT_TEST_TARGETS=

COMPONENT_TEST_TRANSFORMS= \
	'-n ' \
	'-e "s/ \].*/ \]/"' \
	'-e "s/ w[0-9] //"' \
	'-e "s/\[//"' \
	'-e "s/\]//"' \
	'-e "s/  */ /g"' \
	'-e "s/ $$//"' \
	'-e "/pass$$/p"' \
	'-e "/fail$$/p"'

COMPONENT_TEST_CMD= mysql-test/mtr \
	--parallel=$(shell getconf NPROCESSORS_ONLN) \
	--mem \
	--force \
	--retry=0 \
	--mysqld=--binlog-format=mixed \
	--force-restart \
	--max-test-fail=0
#	--skip-test-list=unstable-tests | sort

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(TEST_64)

REQUIRED_PACKAGES += runtime/perl-522
# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/readline
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/perl-524
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/library/security/libsasl
REQUIRED_PACKAGES += web/curl
