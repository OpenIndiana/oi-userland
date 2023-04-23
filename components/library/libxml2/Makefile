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
# Copyright (c) 2011, 2013, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2013  Erol Zavidic. All rights reserved.
# Copyright (c) 2022  Friedrich Kink. All rights reserved.
#

BUILD_BITS=64_and_32
USE_COMMON_TEST_MASTER=	no
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libxml2
COMPONENT_VERSION=	2.10.4
COMPONENT_SUMMARY=	Libxml2 is the XML C parser and toolkit developed for the Gnome project
COMPONENT_PROJECT_URL=	https://gitlab.gnome.org/GNOME/libxml2/-/wikis/home
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:ed0c91c5845008f1936739e4eee2035531c1c94742c6541f44ee66d885948d45
COMPONENT_ARCHIVE_URL=	https://download.gnome.org/sources/libxml2/2.10/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		library/libxml2
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_LICENSE=	Copyright

# W3C XML Conformance Test Suites
COMPONENT_ARCHIVE_1= xmlts20080827.tar.gz
COMPONENT_ARCHIVE_HASH_1= sha256:96151685cec997e1f9f3387e3626d61e6284d4d6e66e0e440c209286c03e9cc7
COMPONENT_ARCHIVE_URL_1= https://www.w3.org/XML/Test/$(COMPONENT_ARCHIVE_1)

include $(WS_MAKE_RULES)/common.mk

PYV= $(shell echo $(PYTHON_VERSIONS) | tr -d .)
PKG_MACROS += PYVER=$(PYTHON_VERSION)
PKG_MACROS += PYV=$(PYV)

CFLAGS += $(CPP_LARGEFILES)

COMPONENT_PRE_CONFIGURE_ACTION += ( \
	cd $(SOURCE_DIR); \
	$(CLONEY) $(SOURCE_DIR) $(@D); \
	);

CONFIGURE_OPTIONS += --sysconfdir=$(ETCDIR)
CONFIGURE_OPTIONS += --localstatedir="$(VARDIR)"
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --with-pic
CONFIGURE_OPTIONS += --with-icu
CONFIGURE_OPTIONS += --with-ftp
CONFIGURE_OPTIONS += --with-xptr-locs
CONFIGURE_OPTIONS += --with-history
CONFIGURE_OPTIONS += --with-legacy
CONFIGURE_OPTIONS.32 += --with-python=no

CONFIGURE_ENV.64     += PYTHON=$(PYTHON.$(PYTHON_VERSION))
COMPONENT_INSTALL_ARGS.64 += pythondir=$(PYTHON_VENDOR_PACKAGES)
COMPONENT_INSTALL_ARGS.64 += pyexecdir=$(PYTHON_VENDOR_PACKAGES)
COMPONENT_BUILD_ARGS.64 += pythondir=$(PYTHON_VENDOR_PACKAGES)
COMPONENT_BUILD_ARGS.64 += pyexecdir=$(PYTHON_VENDOR_PACKAGES)

COMPONENT_PREP_ACTION += (cd $(@D) ; cp ../mapfile libxml2.syms ; PATH="$(PATH)" autoreconf -if )

# After we have built/installed libxml2, build/install the python
# support for python (only 64 bit is available)
COMPONENT_POST_INSTALL_ACTION.64 = ( \
	cd $(@D)/python; \
	 $(GMAKE) pythondir=$(PYTHON_VENDOR_PACKAGES) \
	pyexecdir=$(PYTHON_VENDOR_PACKAGES) \
	DESTDIR=$(PROTO_DIR) \
	install ; \
	$(MV) $(PROTO_DIR)/$(PYTHON_VENDOR_PACKAGES)/libxml2mod.so $(PROTO_DIR)/$(PYTHON_VENDOR_PACKAGES)/libxml2mod.cpython-$(PYV).so; \
	$(PYTHON) -m compileall $(PROTO_DIR)/$(PYTHON_VENDOR_PACKAGES); \
);

# It's nice to test also python modules (LC_ALL is set to avoid test failure).
COMPONENT_POST_TEST_ACTION.64 = \
    cd $(@D)/python; \
    LC_ALL=en_US.UTF-8 $(GMAKE) $(COMPONENT_TEST_ARGS) check

COMPONENT_PRE_TEST_ACTION.64 += \
    (cd $(@D) ; gtar xf $(USERLAND_ARCHIVES)/$(COMPONENT_ARCHIVE_1));

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-$(BITS).master

COMPONENT_TEST_TRANSFORMS = \
	'-e "s/^make\[.*$$/[EnD]/" ' \
	'-e "/^\#\# XML regression tests/,/^\[EnD\]/p" ' \
	'-e "/^\#\# running Python regression tests/,/^\[EnD\]/p" ' \
	'-e "/.*/d" '

# Auto-generated dependencies
REQUIRED_PACKAGES += compress/xz
REQUIRED_PACKAGES += library/icu
REQUIRED_PACKAGES += library/readline
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
