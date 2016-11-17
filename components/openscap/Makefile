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
# Copyright (c) 2012, 2016, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64
COMPILER= gcc
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		openscap
COMPONENT_VERSION=	1.2.9
COMPONENT_PROJECT_URL=  http://www.open-scap.org
COMPONENT_DOWNLOAD_URL= https://fedorahosted.org/releases/o/p/openscap
COMPONENT_ARCHIVE_HASH= sha256:20ae67ffabf90865fb2033d5c5e49bfb5fb485ffa6ff37910e8d7084c2236c74
COMPONENT_ARCHIVE_URL=  $(COMPONENT_DOWNLOAD_URL)/$(COMPONENT_ARCHIVE)

TPNO =			28398

# Requires newer version of system/management/rad/client/rad-c from ON,
# available in S12 but not 11.3, so do not publish.
ifeq ($(BUILD_TYPE), evaluation)
BUILD_64=
INSTALL_64=
PUBLISH_STAMP=
endif

CFLAGS+=		-std=c99
CFLAGS+=		-DNDEBUG
CFLAGS+=		-DOSCAP_THREAD_SAFE
CFLAGS+=		-D__$(MACH64)

PYTHON_VERSIONS=	$(PYTHON2_VERSIONS)

# publish for only one version of perl
PERL_VERSIONS = $(PERL_VERSION)

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_BINDIR.64 =	$(CONFIGURE_PREFIX)/bin
CPPFLAGS +=	-I$(USRINCDIR)/openldap
RAD_CLIENT_LIB_PATH =   /usr/lib/rad/client/c/$(MACH64)

LDFLAGS += -L$(RAD_CLIENT_LIB_PATH) -R$(RAD_CLIENT_LIB_PATH) -lradclient -ladr -lips_client -lzonemgr_client

# XXX This shouldn't be necessary, but is; investigate why.
CFLAGS += -D_FILE_OFFSET_BITS=64

# Enable adiheap and adistack security extensions
ADIHEAP_MODE = $(ADIHEAP_ENABLE)
ADISTACK_MODE = $(ADISTACK_ENABLE)

# Perl related patch needs configure script recreation.
COMPONENT_PREP_ACTION +=(cd $(@D); autoreconf);

# Need to do cloney, so that the schema files can get packaged.
COMPONENT_PRE_CONFIGURE_ACTION = \
    ($(CLONEY) $(SOURCE_DIR) $(@D))

COMPONENT_POST_INSTALL_ACTION =	\
	$(RM) $(PROTO_DIR)/usr/share/openscap/cpe/* && \
	$(CP) files/cpe/* $(PROTO_DIR)/usr/share/openscap/cpe; \
	$(MV) $(PROTO_DIR)/usr/lib/python2.7/vendor-packages/64/*.py* \
	$(PROTO_DIR)/usr/lib/python2.7/vendor-packages/ ;


# Needed to make "gmake test" work.
CPPFLAGS +=	-I$(SOURCE_DIR)/src/OVAL
CPPFLAGS +=	-I$(SOURCE_DIR)/src/OVAL/probes
CPPFLAGS +=	-I$(USRINCDIR)/pcre

CONFIGURE_ENV +=        PERL="$(PERL)"
CONFIGURE_ENV +=        PYTHON="$(PYTHON.$(BITS))"
CONFIGURE_OPTIONS +=	--enable-debug=no
CONFIGURE_OPTIONS +=	--enable-sce=yes
CONFIGURE_OPTIONS +=	--enable-perl=yes
CONFIGURE_OPTIONS +=	--libexecdir=$(CONFIGURE_LIBDIR.$(BITS))
CONFIGURE_OPTIONS +=	am_cv_python_pythondir=$(PYTHON_VENDOR_PACKAGES)
CONFIGURE_OPTIONS +=	am_cv_python_pyexecdir=$(PYTHON_VENDOR_PACKAGES)
EXTRA_LIBS =		-lldap_r
ifeq ($(OS_VERSION),5.11)
EXTRA_LIBS +=		-lnsl -lsocket
endif
EXTRA_LIBS +=		-lscf -ldlpi -lsec -lv12n
CONFIGURE_OPTIONS +=	LDFLAGS="$(LDFLAGS) $(EXTRA_LIBS)"

DOCS_DIR = $(PROTO_DIR)/usr/share/doc/openscap/html/

COMPONENT_POST_INSTALL_ACTION += \
	$(MKDIR) $(DOCS_DIR); \
	$(CP) -r $(SOURCE_DIR)/docs/html/* $(DOCS_DIR);

REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += developer/swig
REQUIRED_PACKAGES += gnome/config/gconf
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/libxslt
REQUIRED_PACKAGES += library/openldap
REQUIRED_PACKAGES += library/pcre
REQUIRED_PACKAGES += $(PERL_PKG)
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += security/compliance/openscap
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/library/security/libgcrypt
REQUIRED_PACKAGES += system/library/libv12n
REQUIRED_PACKAGES += system/management/rad
REQUIRED_PACKAGES += system/management/rad/client/rad-c
REQUIRED_PACKAGES += system/network/ldap/openldap
REQUIRED_PACKAGES += system/zones
REQUIRED_PACKAGES += web/curl
