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
# Copyright (c) 2014 Alexander Pyhalov
# Copyright (c) 2018 Michal Nowak
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		compizconfig-python
COMPONENT_VERSION=	0.8.14
COMPONENT_PROJECT_URL=	http://www.northfield.ws
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
    sha256:a119c51f4892bb5f5f8067c038e3a5b7720df0c73280ce642d87a0495c9ca256
COMPONENT_ARCHIVE_URL=	http://www.northfield.ws/projects/compiz/releases/$(COMPONENT_VERSION)/$(COMPONENT_SRC).tar.xz
COMPONENT_FMRI=		library/python/python-compizconfig

PATH=/usr/gnu/bin:/usr/bin

PYTHON_VERSIONS=	2.7

VARIANT_PYTHON27 = $(BUILD_DIR)/python-27

VARIANTS_64 = $(VARIANT_PYTHON27)

BUILD_64 = $(VARIANTS_64:%=%/$(MACH64)/.built)

INSTALL_64 = $(VARIANTS_64:%=%/$(MACH64)/.installed)

$(VARIANT_PYTHON27)/$(MACH64)/.configured: BITS=64
$(VARIANT_PYTHON27)/$(MACH64)/.configured: PYTHON=$(PYTHON.2.7.64)
$(VARIANT_PYTHON27)/$(MACH64)/.configured: am_cv_python_pyexecdir=$(PYTHON.2.7.VENDOR_PACKAGES.64)
$(VARIANT_PYTHON27)/$(MACH64)/.configured: am_cv_python_pythondir=$(PYTHON.2.7.VENDOR_PACKAGES.64)

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

COMPONENT_PREP_ACTION = \
			( cd $(@D) ; \
					aclocal -I m4 --install  &&\
                	                libtoolize --force --copy &&\
                                        autoheader &&\
                                        automake -a -f -c &&\
                                        autoconf )

CONFIGURE_ENV+=		PYTHON=$(PYTHON)
CONFIGURE_ENV+=		am_cv_python_pythondir="$(am_cv_python_pythondir)"
CONFIGURE_ENV+=		am_cv_python_pyexecdir="$(am_cv_python_pyexecdir)"

CONFIGURE_OPTIONS+=	--sysconfdir=/etc
CONFIGURE_OPTIONS+=	--disable-static

# common targets
build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(NO_TESTS)

# Dependencies not found by auto-generator
REQUIRED_PACKAGES += desktop/compiz/library/libcompizconfig
REQUIRED_PACKAGES += library/python/cython-27
REQUIRED_PACKAGES += library/python/pyrex-27
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += system/library

# Auto-generated dependencies
REQUIRED_PACKAGES += desktop/compiz/library/libcompizconfig
REQUIRED_PACKAGES += system/library
