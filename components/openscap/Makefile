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
# Copyright (c) 2012, 2014, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		openscap
COMPONENT_VERSION=	1.0.0
COMPONENT_PROJECT_URL=  http://www.open-scap.org
COMPONENT_DOWNLOAD_URL= https://fedorahosted.org/releases/o/p/openscap
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:47105500b8b3d80cdf07b277bfab59091de5eadb16d97d27ee663bfbee58cb76
COMPONENT_ARCHIVE_URL=  $(COMPONENT_DOWNLOAD_URL)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=        utility/openscap

TPNO=			16560

COMPILER =		gcc
CFLAGS+=		-std=c99
CFLAGS+=		-DNDEBUG
CFLAGS+=		-DOSCAP_THREAD_SAFE

PYTHON_VERSIONS=	2.7 2.6

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

CPPFLAGS +=	-I/usr/include/openldap

# Perl related patch needs configure script recreation.
COMPONENT_PREP_ACTION +=(cd $(@D); autoreconf);

# Need to do cloney, so that the schema files can get packaged.
COMPONENT_PRE_CONFIGURE_ACTION = \
    ($(CLONEY) $(SOURCE_DIR) $(@D))

# We could use a single regular expression to cover all of the following,
# but we want to be as specific as possible to avoid accidentally catching
# workspace paths in our substitution.
COMPONENT_POST_CONFIGURE_ACTION = \
    (cd $(@D) ; cp -rp swig swig2.7 ; \
    $(GSED) -i -e 's|usr/include/python2.6|usr/include/python2.7|' \
     -e 's|$(PYTHON.2.6.VENDOR_PACKAGES.32)|$(PYTHON.2.7.VENDOR_PACKAGES.32)|' \
     -e 's|PYTHON_VERSION = 2.6|PYTHON_VERSION = 2.7|' swig2.7/Makefile)

COMPONENT_POST_INSTALL_ACTION =	\
	(cd $(@D)/swig2.7 ; $(GMAKE) $(COMPONENT_INSTALL_ARGS) install)

# Needed to make "gmake test" work.
CPPFLAGS +=	-I$(SOURCE_DIR)/src/OVAL
CPPFLAGS +=	-I$(SOURCE_DIR)/src/OVAL/probes
CPPFLAGS +=	-I/usr/include/pcre

CONFIGURE_OPTIONS +=	CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS +=	CPPFLAGS="$(CPPFLAGS)"
CONFIGURE_OPTIONS +=	--enable-debug=no
CONFIGURE_OPTIONS +=	--enable-sce=yes
CONFIGURE_OPTIONS +=	--enable-perl=yes
CONFIGURE_OPTIONS +=	--libexecdir=$(CONFIGURE_LIBDIR.$(BITS))
CONFIGURE_OPTIONS +=	am_cv_python_pythondir=$(PYTHON_VENDOR_PACKAGES)
CONFIGURE_OPTIONS +=	am_cv_python_pyexecdir=$(PYTHON_VENDOR_PACKAGES)
CONFIGURE_OPTIONS +=	LIBS="-lldap_r -lscf -ldlpi -lsec -lzonecfg"
CONFIGURE_OPTIONS +=	--with-report-branding="/usr/share/lib/xml/style/os-logo.xsl"

DOCS_DIR = $(PROTO_DIR)/usr/share/docs/openscap/html/

# common targets
configure:	$(CONFIGURE_32)

build:		$(BUILD_32)

install:	$(INSTALL_32)
		$(MKDIR) $(DOCS_DIR)
		$(CP) $(SOURCE_DIR)/docs/html/* $(DOCS_DIR)

test:		$(TEST_32)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include $(WS_TOP)/make-rules/depend.mk
