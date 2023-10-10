#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2016 Alexander Pyhalov
#

BUILD_BITS=64_and_32
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         libproxy

COMPONENT_VERSION=      0.3.1
COMPONENT_REVISION=     	4
COMPONENT_SUMMARY=      Libproxy is a library that provides automatic proxy configuration management
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= \
	sha256:dbb2dd519d58c0a41c5c59204863c327dfa61f3ac564fc448ab2703a35610a2e
COMPONENT_ARCHIVE_URL=  \
	https://github.com/libproxy/libproxy/archive/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=  https://github.com/libproxy/libproxy
COMPONENT_FMRI=			library/libproxy
COMPONENT_CLASSIFICATION=	System/Libraries
COMPONENT_LICENSE=		LGPL-2.1-only
COMPONENT_LICENSE_FILE=		COPYING

DROP_STATIC_LIBRARIES = yes

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION= ( cd $(@D) && \
		PATH="$(PATH)" libtoolize --force && \
                aclocal -I . &&\
                automake -a -c -f &&\
                autoconf )

COMPONENT_PRE_CONFIGURE_ACTION =        ($(CLONEY) $(SOURCE_DIR) $(@D)) 

CFLAGS+= -D__EXTENSIONS__

# Drop 32-bit binaries
COMPONENT_POST_INSTALL_ACTION += $(RM) -r $(PROTOUSRBINDIR32) ;
# Move the 'proxy' binary to demos
$(INSTALL_64):	COMPONENT_POST_INSTALL_ACTION += $(INSTALL) -d $(PROTOUSRDIR)/demo/jds/bin/ ;
$(INSTALL_64):	COMPONENT_POST_INSTALL_ACTION += $(MV) $(PROTOUSRBINDIR)/proxy $(PROTOUSRDIR)/demo/jds/bin/ ;

CONFIGURE_OPTIONS+= --sysconfdir=$(ETCDIR)
CONFIGURE_OPTIONS+= --includedir=$(USRINCDIR)/libproxy
CONFIGURE_OPTIONS+= --libexecdir=$(USRLIBDIR)
CONFIGURE_OPTIONS+= --localstatedir=$(VARDIR)/lib
CONFIGURE_OPTIONS+= --with-gnome
CONFIGURE_OPTIONS+= --without-dotnet
CONFIGURE_OPTIONS+= --with-direct
CONFIGURE_OPTIONS+= --with-envvar
CONFIGURE_OPTIONS+= --with-file
CONFIGURE_OPTIONS+= --with-wpad
CONFIGURE_OPTIONS+= --without-networkmanager
CONFIGURE_OPTIONS+= --without-webkit
CONFIGURE_OPTIONS+= --without-mozjs

CONFIGURE_ENV    += XGETTEXT=/usr/gnu/bin/xgettext
CONFIGURE_ENV    += MSGFMT=/usr/gnu/bin/msgfmt
CONFIGURE_ENV    += PERL=$(PERL)
CONFIGURE_ENV    += PYTHON="$(PYTHON)"
CONFIGURE_ENV    += am_cv_python_pythondir="$(PYTHON_VENDOR_PACKAGES)"
CONFIGURE_ENV    += am_cv_python_pyexecdir="$(PYTHON_VENDOR_PACKAGES)"

COMPONENT_INSTALL_ENV+= GCONF_DISABLE_MAKEFILE_SCHEMA_INSTALL=1

# Build dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxmu
