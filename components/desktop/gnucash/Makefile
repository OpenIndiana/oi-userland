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
# Copyright 2025 Bill Sommerfeld
#

BUILD_STYLE= cmake
USE_PARALLEL_BUILD= yes
USE_DEFAULT_TEST_TRANSFORMS= yes

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= gnucash
COMPONENT_VERSION= 5.11
COMPONENT_SUMMARY= Desktop accounting program
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL= https://github.com/gnucash/
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:a5d3a12991cff287267f6896d70bd8b3fe7030fb552b1d18067300d0ed7f8a2f
COMPONENT_ARCHIVE_URL=	https://github.com/Gnucash/gnucash/releases/download/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)

COMPONENT_CLASSIFICATION= Applications/Office
COMPONENT_FMRI= desktop/gnucash
COMPONENT_LICENSE= GPLv2+
COMPONENT_LICENSE_FILE= LICENSE

COMPONENT_PRE_TEST_ACTION += (cd $(BUILD_DIR_64); $(COMPONENT_BUILD_CMD) $(COMPONENT_BUILD_CMAKE_ARGS) -t testbuild)

# Tests load *.scm files out of proto area
COMPONENT_TEST_DEP += $(BUILD_DIR)/%/.installed
CMAKE_ENV += DESTDIR=$(PROTO_DIR)

# TODO: enable python bindings
# TODO: package these dependencies
CMAKE_OPTIONS += -D WITH_AQBANKING=OFF
CMAKE_OPTIONS += -D WITH_OFX=OFF

include $(WS_MAKE_RULES)/common.mk

# libstc++ locale code throws an exception if it sees a non-"C" locale facet.
COMPONENT_TEST_ENV += LC_ALL=C
# One subtest of test-qof fails outside of GMT
COMPONENT_TEST_ENV += TZ=GMT

# preserve mod times on .scm source to avoid recompilation
PKGSEND_PUBLISH_OPTIONS += -T \*.scm

PATH=$(PATH.gnu)

# Manual build dependencies

REQUIRED_PACKAGES += developer/swig
REQUIRED_PACKAGES += text/gnu-gettext
REQUIRED_PACKAGES += library/libdbi/sqlite3

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(ICU_LIBRARY_PKG)
REQUIRED_PACKAGES += developer/icu
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/desktop/webkitgtk2
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/guile
REQUIRED_PACKAGES += library/libdbi
REQUIRED_PACKAGES += library/libsecret
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/boost
REQUIRED_PACKAGES += system/library/math
