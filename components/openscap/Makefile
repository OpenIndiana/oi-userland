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
# Copyright (c) 2012, 2015, Oracle and/or its affiliates. All rights reserved.
#

COMPILER =	gcc

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		openscap
COMPONENT_VERSION=	1.2.3
COMPONENT_PROJECT_URL=  http://www.open-scap.org
COMPONENT_DOWNLOAD_URL= https://fedorahosted.org/releases/o/p/openscap
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:c15d587e5cdfcef1316536e6ed8ad66fea3e083ac3d3b723b7e54208f63787c7
COMPONENT_ARCHIVE_URL=  $(COMPONENT_DOWNLOAD_URL)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=        utility/openscap

TPNO =			22513	

CFLAGS+=		-std=c99
CFLAGS+=		-DNDEBUG
CFLAGS+=		-DOSCAP_THREAD_SAFE

# When Python 2.6 goes away, the _VERSION (singular) line below can go as well,
# as can the COMPONENT_POST_CONFIGURE_ACTION and possibly more.
PYTHON_VERSION=		2.6
PYTHON_VERSIONS=	$(PYTHON2_VERSIONS)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PERL_VERSION.32 = 5.12
PERL_VERSION.64 = 5.16
PERL_VERSION = $(PERL_VERSION.$(BITS))
PERL = $(PERL.$(PERL_VERSION))
CONFIGURE_BINDIR.64 =	$(CONFIGURE_PREFIX)/bin
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
     -e 's|PYTHON_VERSION = 2.6|PYTHON_VERSION = 2.7|' swig2.7/Makefile swig2.7/python2/Makefile)

COMPONENT_POST_INSTALL_ACTION =	\
	(cd $(@D)/swig2.7 ; $(GMAKE) $(COMPONENT_INSTALL_ARGS) install) ; \
	$(RM) $(PROTO_DIR)/usr/share/openscap/cpe/* && \
	$(CP) files/cpe/* $(PROTO_DIR)/usr/share/openscap/cpe


# Needed to make "gmake test" work.
CPPFLAGS +=	-I$(SOURCE_DIR)/src/OVAL
CPPFLAGS +=	-I$(SOURCE_DIR)/src/OVAL/probes
CPPFLAGS +=	-I/usr/include/pcre

CONFIGURE_ENV +=        PERL="$(PERL)"
CONFIGURE_ENV +=        PYTHON="$(PYTHON.$(BITS))"
CONFIGURE_OPTIONS.32 +=	CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS.64 +=	CFLAGS="$(CFLAGS) -D_FILE_OFFSET_BITS=64"
CONFIGURE_OPTIONS +=	CPPFLAGS="$(CPPFLAGS)"
CONFIGURE_OPTIONS +=	--enable-debug=no
CONFIGURE_OPTIONS +=	--enable-sce=yes
CONFIGURE_OPTIONS +=	--enable-perl=yes
CONFIGURE_OPTIONS +=	--libexecdir=$(CONFIGURE_LIBDIR.$(BITS))
CONFIGURE_OPTIONS +=	am_cv_python_pythondir=$(PYTHON_VENDOR_PACKAGES)
CONFIGURE_OPTIONS +=	am_cv_python_pyexecdir=$(PYTHON_VENDOR_PACKAGES)
CONFIGURE_OPTIONS +=	LIBS="-lldap_r -lscf -ldlpi -lsec -lzonecfg"

DOCS_DIR = $(PROTO_DIR)/usr/share/docs/openscap/html/

# Enable ASLR for this component
ASLR_MODE = $(ASLR_ENABLE)

# common targets
configure:	$(CONFIGURE_32_and_64)

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)
		$(MKDIR) $(DOCS_DIR)
		$(CP) $(SOURCE_DIR)/docs/html/* $(DOCS_DIR)

test:		$(TEST_32_and_64)

REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += developer/swig
REQUIRED_PACKAGES += gnome/config/gconf
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/libxslt
REQUIRED_PACKAGES += library/openldap
REQUIRED_PACKAGES += library/pcre
REQUIRED_PACKAGES += runtime/perl-512
REQUIRED_PACKAGES += runtime/perl-516
REQUIRED_PACKAGES += runtime/python-26
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += security/compliance/openscap
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/gcc-3-runtime
REQUIRED_PACKAGES += system/library/gcc-45-runtime
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/library/security/libgcrypt
REQUIRED_PACKAGES += system/zones
REQUIRED_PACKAGES += web/curl
