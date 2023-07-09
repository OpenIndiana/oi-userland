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
# Copyright (c) 2022, Friedrich Kink. All rights reserved.
#

BUILD_BITS=	64_and_32
USEOPENSSL11= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libxslt
COMPONENT_VERSION=	1.1.38
COMPONENT_SUMMARY=      XSLT support for libxml2 (XML toolkit from the GNOME project)
COMPONENT_PROJECT_URL=	http://xmlsoft.org/XSLT/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:1f32450425819a09acaff2ab7a5a7f8a2ec7956e505d7beeb45e843d0e1ecab1
COMPONENT_ARCHIVE_URL=	https://download.gnome.org/sources/libxslt/1.1/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         library/libxslt
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_LICENSE=      MIT
COMPONENT_LICENSE_FILE= Copyright

include $(WS_MAKE_RULES)/common.mk

PYV= $(shell echo $(PYTHON_VERSIONS) | tr -d .)
PKG_MACROS += PYVER=$(PYTHON_VERSION)
PKG_MACROS += PYV=$(PYV)

LINT_FLAGS += -I/usr/include/libxml2 

CFLAGS  += $(CPP_LARGEFILES)
LDFLAGS += $(LD_Z_DEFS) $(LD_Z_TEXT) -lpthread

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --with-pic
CONFIGURE_OPTIONS.64 += --with-python=$(PYTHON)
CONFIGURE_OPTIONS.32 += --with-python=no
CONFIGURE_OPTIONS += --with-crypto
CONFIGURE_OPTIONS += CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS += LDFLAGS="$(LDFLAGS)"
CONFIGURE_OPTIONS += PYTHON_VENDOR_PACKAGES=$(PYTHON_VENDOR_PACKAGES)

CONFIGURE_ENV.64     += PYTHON=$(PYTHON.$(PYTHON_VERSION))
COMPONENT_INSTALL_ARGS.64 += pythondir=$(PYTHON_VENDOR_PACKAGES)
COMPONENT_INSTALL_ARGS.64 += pyexecdir=$(PYTHON_VENDOR_PACKAGES)
COMPONENT_BUILD_ARGS.64 += pythondir=$(PYTHON_VENDOR_PACKAGES)
COMPONENT_BUILD_ARGS.64 += pyexecdir=$(PYTHON_VENDOR_PACKAGES)

CONFIGURE_ENV.64 += LT_SYS_LIBRARY_PATH="/lib/$(MACH64):/usr/lib/$(MACH64)"

COMPONENT_PREP_ACTION = \
	(cd $(@D) ; cp ../mapfile.xslt libxslt/libxslt.syms ; \
		    $(RM) libxslt/xsltconfig.h libexslt/exsltconfig.h ; \
		    libtoolize --force --copy ; aclocal ; \
		    automake -f -a --copy ; autoconf)

# After we have built/installed libxml2, build/install the python
# support for python (only 64 bit is available)
COMPONENT_POST_INSTALL_ACTION.64 = ( \
        cd $(@D)/python; \
         $(GMAKE) pythondir=$(PYTHON_VENDOR_PACKAGES) \
        pyexecdir=$(PYTHON_VENDOR_PACKAGES) \
        DESTDIR=$(PROTO_DIR) \
        install ; \
        $(MV) $(PROTO_DIR)/$(PYTHON_VENDOR_PACKAGES)/libxsltmod.so $(PROTO_DIR)/$(PYTHON_VENDOR_PACKAGES)/libxsltmod.cpython-$(PYV).so; \
        $(PYTHON) -m compileall $(PROTO_DIR)/$(PYTHON_VENDOR_PACKAGES); \
);

# system-test should really use system version library
COMPONENT_PRE_SYSTEM_TEST_ACTION = ($(RM) $(@D)/libxslt/.libs/*)

# It's nice to test also python modules (LC_ALL is set to avoid test failure).
COMPONENT_POST_TEST_ACTION.64 = \
    cd $(@D)/python; \
    LC_ALL=en_US.UTF-8 $(GMAKE) $(COMPONENT_TEST_ARGS) check

COMPONENT_TEST_TRANSFORMS = \
        '-e "/^-- /p" ' \
        '-e "/^OK /p" ' \
        '-e "/^\#\# Running .* tests/p" ' \
        '-e "/^\#\# running Python regression tests/p" ' \
        '-e "/ result /p" ' \
        '-e "/failed/p" ' \
        '-e "/.*/d" '

# Auto-generated dependencies
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/security/libgpg-error
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/library/security/libgcrypt
