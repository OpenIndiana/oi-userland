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
# Copyright 2021 Carsten Grzemba
#

BUILD_BITS=64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= speech-dispatcher
COMPONENT_VERSION= 0.10.2
COMPONENT_REVISION= 0
COMPONENT_SUMMARY= Speech Dispatcher
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
	sha256:b06319f201e15e56c6296653af5bcfc300cb348e972d517df8b06eac77eae2dc
COMPONENT_ARCHIVE_URL= \
   https://github.com/brailcom/speechd/releases/download/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = https://devel.freebsoft.org/speechd
COMPONENT_FMRI= library/desktop/speech-dispatcher
COMPONENT_CLASSIFICATION= Applications/Universal Access
COMPONENT_LICENSE = GPLv2
COMPONENT_LICENSE_FILE = COPYING.GPL-2

TEST_TARGET = $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

PYTHON_VERSION = 3.5

LDFLAGS += -lnsl -lsocket

# The split-version.sh script is called from the builddir by configure.
# Version numbers are silently missing without this.
COMPONENT_PRE_CONFIGURE_ACTION = ( \
	$(CLONEY) $(SOURCE_DIR) $(@D); \
        cd  $(SOURCE_DIR) && aclocal ;)

CONFIGURE_OPTIONS += --sysconfdir=$(ETCDIR)
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --with-espeak
CONFIGURE_OPTIONS += --with-pulse
CONFIGURE_OPTIONS += --with-voxin=no
CONFIGURE_OPTIONS += --with-kali=no
CONFIGURE_OPTIONS += --with-ibmtts=no
CONFIGURE_OPTIONS += --with-baratinoo=no

# There are no binary python modules, install them in 32-bit path
CONFIGURE_ENV+=    PYTHON=$(PYTHON)
CONFIGURE_ENV+=    am_cv_python_pyexecdir=$(PYTHON_VENDOR_PACKAGES)
CONFIGURE_ENV+=    am_cv_python_pythondir=$(PYTHON_VENDOR_PACKAGES)
# build will run configure again ???...
COMPONENT_BUILD_ENV+=    $(CONFIGURE_ENV)

REQUIRED_PACKAGES += library/python/python-xdg
# for python-xdg Python3.5
REQUIRED_PACKAGES += runtime/python-35
# Auto-generated dependencies
REQUIRED_PACKAGES += library/audio/libao
REQUIRED_PACKAGES += library/audio/pulseaudio
REQUIRED_PACKAGES += library/desktop/dotconf
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libsndfile
REQUIRED_PACKAGES += library/libtool/libltdl
REQUIRED_PACKAGES += library/speech/espeak
REQUIRED_PACKAGES += system/library
# Auto-generated dependencies
REQUIRED_PACKAGES += library/audio/libao
REQUIRED_PACKAGES += library/audio/pulseaudio
REQUIRED_PACKAGES += library/desktop/dotconf
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libsndfile
REQUIRED_PACKAGES += library/libtool/libltdl
REQUIRED_PACKAGES += library/speech/espeak
REQUIRED_PACKAGES += runtime/python-35
REQUIRED_PACKAGES += system/library
