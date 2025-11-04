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
# Copyright 2015 Alexander Pyhalov
# Copyright 2025 Klaus Ziegler
#

BUILD_BITS= 64_and_32
USE_PARALLEL_BUILD= yes
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		fontconfig
COMPONENT_VERSION=	2.17.1
COMPONENT_SUMMARY=	Fontconfig - Font configuration and customization library
COMPONENT_PROJECT_URL=	https://www.freedesktop.org/wiki/Software/fontconfig
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:9f5cae93f4fffc1fbc05ae99cdfc708cd60dfd6612ffc0512827025c026fa541
COMPONENT_ARCHIVE_URL= 	https://gitlab.freedesktop.org/api/v4/projects/890/packages/generic/fontconfig/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		system/library/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_LICENSE=	MIT
COMPONENT_LICENSE_FILE=	COPYING

TEST_TARGET= $(TEST_64)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_FMRI.fontconfig-32= $(COMPONENT_FMRI)/32

# Make gcc 14 accept the old code.
CFLAGS += -Wno-error=incompatible-pointer-types
CFLAGS += -Wno-error=int-conversion

COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"

# tests require GNU cp (support for -a) & date (support for -d)
PATH= $(PATH.gnu)

CONFIGURE_BINDIR.32 =  $(CONFIGURE_PREFIX)/bin/$(MACH32)

CONFIGURE_OPTIONS += --with-baseconfigdir=$(ETCDIR)/fonts
CONFIGURE_OPTIONS += --with-templatedir='$(ETCDIR)/fonts/conf.avail'
CONFIGURE_OPTIONS += --with-xmldir='$(ETCDIR)/fonts'
CONFIGURE_OPTIONS += --with-default-fonts='$(USRSHAREDIR)/fonts'
CONFIGURE_OPTIONS += --with-add-fonts='/etc/X11/fontpath.d,/usr/share/ghostscript/fonts,/usr/X11/lib/X11/fonts'
CONFIGURE_OPTIONS += --with-cache-dir=/var/cache/fontconfig
# Don't run fc-cache during the build
CONFIGURE_OPTIONS += --disable-cache-build
CONFIGURE_OPTIONS += --enable-iconv

# Makefile.am files of this component are not compatible with illumos make.
# Use GNU make to avoid the configuration error when makefile fragments are processed.
CONFIGURE_OPTIONS += MAKE=$(GMAKE)

# Add a note about the SMF service to the end of the man page
COMPONENT_POST_INSTALL_ACTION += \
    cat files/sunman-notes-fc-cache >> $(PROTOUSRSHAREMAN1DIR)/fc-cache.1 ;

# Because both the 32-bit & 64-bit builds install the config files, whichever
# runs second creates a backup of the first that we don't need in our packages.
COMPONENT_POST_INSTALL_ACTION += $(RM) $(PROTOETCDIR)/fonts/fonts.conf.bak ;

# Make links in conf.d be relative links to ../conf.avail instead of absolute
COMPONENT_POST_INSTALL_ACTION += \
    (cd $(PROTOETCDIR)/fonts/conf.d/ ; \
    for f in *.conf ; do \
    $(RM) $${f} ; \
    $(SYMLINK) ../conf.avail/$${f} $${f} ; \
    done) ;

# Make links in conf.d be relative links to ../conf.avail instead of absolute
COMPONENT_POST_INSTALL_ACTION += \
    (cd $(PROTOETCDIR)/fonts/conf.d/ ; \
    for f in *.conf ; do \
    $(RM) $${f} ; \
    $(SYMLINK) ../conf.avail/$${f} $${f} ; \
    done) ;

# prevent run-test.sh from downloading files from the internet
COMPONENT_TEST_ENV += NO_PROXY='*'

# Manually added build dependencies
REQUIRED_PACKAGES += developer/gperf
REQUIRED_PACKAGES += library/json-c/32

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += library/expat/32
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += system/library/freetype-2/32
