#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2020 Alexander Pyhalov
#

BUILD_STYLE=setup.py
BUILD_BITS=32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		Pillow
# Pillow 7 dropped Python 2.7 support
COMPONENT_VERSION=	6.2.2
COMPONENT_PROJECT_URL=	https://pypi.org/project/Pillow/
COMPONENT_SUMMARY=	Python image processing library
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:db9ff0c251ed066d367f53b64827cc9e18ccea001b986d08c265e53625dab950
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_FMRI=		library/python/pillow
COMPONENT_CLASSIFICATION=	Development/Python
COMPONENT_LICENSE=	PIL software license
COMPONENT_LICENSE_FILE=	LICENSE

# 3.4 is not supported
PYTHON_VERSIONS=	2.7 3.5

include $(WS_MAKE_RULES)/common.mk

# build with the distribution preferred libjpeg implementation
CFLAGS            +=    $(JPEG_CPPFLAGS) $(JPEG_CFLAGS)
CXXFLAGS          +=    $(JPEG_CPPFLAGS) $(JPEG_CXXFLAGS)
LDFLAGS           +=    $(JPEG_LDFLAGS)

COMPONENT_TEST_DIR= $(COMPONENT_SRC)
COMPONENT_TEST_ARGS= ./selftest.py
COMPONENT_TEST_ENV= PYTHONPATH=$(PROTO_DIR)$(PYTHON_LIB)

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

COMPONENT_TEST_TRANSFORMS += \
        '-e "s|^PIL [0-9]\{1,\}\(\.[0-9]\{1,\}\)\{1,\}|PIL|" ' \
        '-e "s|\(^Python modules loaded from \).*|\1|" ' \
        '-e "s|\(^Binary modules loaded from \).*|\1|" ' \
        '-e "/Python 3\.[0-9]\.[0-9]/d" -e "/\[GCC.*\]/d" '

# Auto-generated dependencies
REQUIRED_PACKAGES += image/library/libjpeg8-turbo
REQUIRED_PACKAGES += image/library/libtiff
REQUIRED_PACKAGES += image/library/openjpeg
REQUIRED_PACKAGES += library/lcms2
REQUIRED_PACKAGES += library/libwebp
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += runtime/python-35
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/freetype-2
