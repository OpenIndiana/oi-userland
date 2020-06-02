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
# Copyright 2017 Alexander Pyhalov
#

BUILD_BITS=64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= speech-dispatcher
COMPONENT_VERSION= 0.8.7
COMPONENT_REVISION= 3
COMPONENT_SUMMARY= Speech Dispatcher
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:200be1adb054dd14bfbc46e798ac6a7c0d4abaa13343fb987312c5265e4cb134
COMPONENT_ARCHIVE_URL= \
  https://devel.freebsoft.org/pub/projects/speechd/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = https://devel.freebsoft.org/speechd
COMPONENT_FMRI= library/desktop/speech-dispatcher
COMPONENT_CLASSIFICATION= Applications/Universal Access
COMPONENT_LICENSE = GPLv2
COMPONENT_LICENSE_FILE = COPYING

TEST_TARGET = $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

PYTHON_VERSION = 3.5

LDFLAGS += -lnsl -lsocket

# The split-version.sh script is called from the builddir by configure.
# Version numbers are silently missing without this.
COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_OPTIONS += --sysconfdir=$(ETCDIR)
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --with-espeak
CONFIGURE_OPTIONS += --with-pulse

# There are no binary python modules, install them in 32-bit path
CONFIGURE_ENV+=    PYTHON=$(PYTHON)
CONFIGURE_ENV+=    am_cv_python_pyexecdir=$(PYTHON_VENDOR_PACKAGES)
CONFIGURE_ENV+=    am_cv_python_pythondir=$(PYTHON_VENDOR_PACKAGES)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/audio/libao
REQUIRED_PACKAGES += library/audio/pulseaudio
REQUIRED_PACKAGES += library/desktop/dotconf
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libsndfile
REQUIRED_PACKAGES += library/libtool/libltdl
REQUIRED_PACKAGES += library/speech/espeak
REQUIRED_PACKAGES += system/library
