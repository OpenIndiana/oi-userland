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
# Copyright 2015 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		notify-python
COMPONENT_VERSION=	0.1.1
COMPONENT_REVISION=	4
COMPONENT_PROJECT_URL=	http://www.galago-project.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:8c5ee28017fdc5b110c31cb76503e535e15e0c60b9a1f1e95ff6c018dd806022
COMPONENT_ARCHIVE_URL=	http://www.galago-project.org/files/releases/source/notify-python/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE_FILE = COPYING
COMPONENT_LICENSE = LGPLv2.1
COMPONENT_CLASSIFICATION = Development/Python

PATH=/usr/gnu/bin:/usr/bin

PYTHON_VERSIONS= 2.7

VARIANT_PYTHON27 = $(BUILD_DIR)/python-27

VARIANTS = $(VARIANT_PYTHON27)

BUILD_32 = $(VARIANTS:%=%/$(MACH32)/.built)
BUILD_64 = $(VARIANTS:%=%/$(MACH64)/.built)

INSTALL_32 = $(VARIANTS:%=%/$(MACH32)/.installed)
INSTALL_64 = $(VARIANTS:%=%/$(MACH64)/.installed)

$(VARIANT_PYTHON27)/$(MACH64)/.configured: BITS=64
$(VARIANT_PYTHON27)/$(MACH64)/.configured: PYTHON=$(PYTHON.2.7.64)
$(VARIANT_PYTHON27)/$(MACH64)/.configured: am_cv_python_pyexecdir=$(PYTHON.2.7.VENDOR_PACKAGES.64)

$(VARIANT_PYTHON27)/$(MACH32)/.configured: PYTHON=$(PYTHON.2.7.32)
$(VARIANT_PYTHON27)/$(MACH32)/.configured: am_cv_python_pyexecdir=$(PYTHON.2.7.VENDOR_PACKAGES.32)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CFLAGS += -I/usr/include/gtk-2.0
CFLAGS += -I/usr/include/cairo
CFLAGS += -I/usr/include/pango-1.0

# There was reference to now unavailable http://trac.galago-project.org/ticket/121 
# for the reason to remove the file
COMPONENT_PREP_ACTION =        ( cd $(@D)  && \
					rm src/pynotify.c &&\
					autoreconf -f -i )

CONFIGURE_OPTIONS+=	--sysconfdir=/etc
CONFIGURE_ENV+=		PYTHON=$(PYTHON)
CONFIGURE_ENV+=		am_cv_python_pyexecdir=$(am_cv_python_pyexecdir)

COMPONENT_POST_BUILD_ACTION= $(TOUCH) $(BUILD_DIR)

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(NO_TESTS)

REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libnotify
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += system/library
