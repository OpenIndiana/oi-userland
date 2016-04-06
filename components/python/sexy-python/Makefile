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

COMPONENT_NAME=		sexy-python
COMPONENT_VERSION=	0.1.9
COMPONENT_PROJECT_URL=	http://blog.chipx86.com/tag/libsexy/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:2d8d257bbfa498a89792e0405ed8cf70396648b3df3c8e32cdc3dcc9bb666f15
COMPONENT_ARCHIVE_URL=	http://releases.chipx86.com/libsexy/sexy-python/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE_FILE = COPYING
COMPONENT_LICENSE = LGPLv2.1
COMPONENT_CLASSIFICATION = Development/Python

PATH=/usr/gnu/bin:/usr/bin

VARIANT_PYTHON26 = $(BUILD_DIR)/python-26
VARIANT_PYTHON27 = $(BUILD_DIR)/python-27

VARIANTS = $(VARIANT_PYTHON26) $(VARIANT_PYTHON27)

BUILD_32 = $(VARIANTS:%=%/$(MACH32)/.built)
BUILD_64 = $(VARIANTS:%=%/$(MACH64)/.built)

INSTALL_32 = $(VARIANTS:%=%/$(MACH32)/.installed)
INSTALL_64 = $(VARIANTS:%=%/$(MACH64)/.installed)

$(VARIANT_PYTHON26)/$(MACH64)/.configured: BITS=64
$(VARIANT_PYTHON27)/$(MACH64)/.configured: BITS=64
$(VARIANT_PYTHON26)/$(MACH64)/.configured: PYTHON=$(PYTHON.2.6.64)
$(VARIANT_PYTHON27)/$(MACH64)/.configured: PYTHON=$(PYTHON.2.7.64)
$(VARIANT_PYTHON26)/$(MACH64)/.configured: am_cv_python_pyexecdir=$(PYTHON.2.6.VENDOR_PACKAGES.64)
$(VARIANT_PYTHON27)/$(MACH64)/.configured: am_cv_python_pyexecdir=$(PYTHON.2.7.VENDOR_PACKAGES.64)

$(VARIANT_PYTHON26)/$(MACH32)/.configured: PYTHON=$(PYTHON.2.6.32)
$(VARIANT_PYTHON27)/$(MACH32)/.configured: PYTHON=$(PYTHON.2.7.32)
$(VARIANT_PYTHON26)/$(MACH32)/.configured: am_cv_python_pyexecdir=$(PYTHON.2.6.VENDOR_PACKAGES.32)
$(VARIANT_PYTHON27)/$(MACH32)/.configured: am_cv_python_pyexecdir=$(PYTHON.2.7.VENDOR_PACKAGES.32)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PREP_ACTION =        ( cd $(@D)  && \
					libtoolize --copy --force &&\
					aclocal -I m4 &&\
					automake -c -f -a &&\
					autoconf )

CONFIGURE_OPTIONS+=	--sysconfdir=/etc
CONFIGURE_ENV+=		PYTHON=$(PYTHON)
CONFIGURE_ENV+=		am_cv_python_pyexecdir=$(am_cv_python_pyexecdir)

# common targets
build:		$(BUILD_32_and_64)
	$(TOUCH) $(BUILD_DIR)

install:	$(INSTALL_32_and_64)

test:		$(NO_TESTS)

include $(WS_MAKE_RULES)/depend.mk
