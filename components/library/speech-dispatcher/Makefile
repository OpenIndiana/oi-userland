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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= speech-dispatcher
COMPONENT_VERSION= 0.8.7
COMPONENT_REVISION= 1
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

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

PYTHON_VERSION = 3.4

LDFLAGS += -lnsl -lsocket

CONFIGURE_BINDIR.64 = /usr/bin

CONFIGURE_OPTIONS += --sysconfdir=$(ETCDIR)
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --with-espeak
CONFIGURE_OPTIONS += --with-pulse

# There are no binary python modules, install them in 32-bit path
CONFIGURE_ENV+=    PYTHON=$(PYTHON)
CONFIGURE_ENV+=    am_cv_python_pyexecdir=$(PYTHON_VENDOR_PACKAGES.32)
CONFIGURE_ENV+=    am_cv_python_pythondir=$(PYTHON_VENDOR_PACKAGES.32)

build: $(BUILD_64)

install: $(INSTALL_64)

test: $(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/audio/libao
REQUIRED_PACKAGES += library/audio/pulseaudio
REQUIRED_PACKAGES += library/desktop/dotconf
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libsndfile
REQUIRED_PACKAGES += library/libtool/libltdl
REQUIRED_PACKAGES += library/speech/espeak
REQUIRED_PACKAGES += system/library
