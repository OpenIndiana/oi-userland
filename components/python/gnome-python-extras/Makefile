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
# Copyright (c) 2013 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gnome-python-extras
COMPONENT_VERSION=	2.25.3
COMPONENT_REVISION=	2
COMPONENT_PROJECT_URL=	http://www.gnome.org
COMPONENT_SUMMARY=	Supplemental Python bindings for GNOME
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:ca346264e00e193f0866cabd8801d3b7ce70dae7b8b296e41e5b3a45c9b0275c
COMPONENT_ARCHIVE_URL=	http://ftp.gnome.org/pub/GNOME/sources/$(COMPONENT_NAME)/2.25/$(COMPONENT_ARCHIVE)

PATH=/usr/gnu/bin:/usr/bin

VARIANT_PYTHON26 = $(BUILD_DIR)/python-26
VARIANT_PYTHON27 = $(BUILD_DIR)/python-27

VARIANTS = $(VARIANT_PYTHON26) $(VARIANT_PYTHON27)

BUILD_32 = $(VARIANTS:%=%/$(MACH32)/.built)

INSTALL_32 = $(VARIANTS:%=%/$(MACH32)/.installed)

# Avoid overwriting python2.6 files in /usr/share
$(VARIANT_PYTHON26)/$(MACH32)/.installed:       $(VARIANT_PYTHON27)/$(MACH32)/.installed

$(VARIANT_PYTHON26)/$(MACH32)/.configured: PYTHON=$(PYTHON.2.6.32)
$(VARIANT_PYTHON27)/$(MACH32)/.configured: PYTHON=$(PYTHON.2.7.32)
$(VARIANT_PYTHON26)/$(MACH32)/.configured: am_cv_python_pyexecdir=$(PYTHON.2.6.VENDOR_PACKAGES.32)
$(VARIANT_PYTHON27)/$(MACH32)/.configured: am_cv_python_pyexecdir=$(PYTHON.2.7.VENDOR_PACKAGES.32)
$(VARIANT_PYTHON26)/$(MACH32)/.configured: am_cv_python_pythondir=$(PYTHON.2.6.VENDOR_PACKAGES.32)
$(VARIANT_PYTHON27)/$(MACH32)/.configured: am_cv_python_pythondir=$(PYTHON.2.7.VENDOR_PACKAGES.32)

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

COMPONENT_PREP_ACTION = \
	( cd $(@D) ; \
		autoreconf -i -f )

# Missing files in build dir for configure without this.
COMPONENT_PRE_CONFIGURE_ACTION =        ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_OPTIONS+=	--sysconfdir=/etc
CONFIGURE_ENV+=		PYTHON=$(PYTHON)
CONFIGURE_ENV+=		am_cv_python_pythondir="$(am_cv_python_pythondir)"
CONFIGURE_ENV+=		am_cv_python_pyexecdir="$(am_cv_python_pyexecdir)"

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

include $(WS_TOP)/make-rules/depend.mk
