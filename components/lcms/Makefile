#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#

#
# Copyright (c) 2011, 2016, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64_and_32
include ../../make-rules/shared-macros.mk

COMPONENT_NAME =        lcms
COMPONENT_VERSION=      1.19
COMPONENT_PROJECT_URL=  http://www.littlecms.com/
COMPONENT_ARCHIVE_HASH= \
    sha256:80ae32cb9f568af4dc7ee4d3c05a4c31fc513fc3e31730fed0ce7378237273a9
COMPONENT_ARCHIVE_URL=  http://sourceforge.net/projects/lcms/files/lcms/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)

TPNO=			9072

include $(WS_MAKE_RULES)/common.mk

PATCH_LEVEL = 0

# adding to the C++ compiler because libtool appears to strip it from CXXFLAGS
CXX +=	$(studio_NORUNPATH)
CXX +=	-std=sun03

# It seems that we have no other way to designate that we want large file support
CFLAGS += $(CPP_LARGEFILES)
CXXFLAGS += $(CPP_LARGEFILES)

COMPONENT_TEST_TRANSFORMS += \
     '-e "/libtool/d"' \
     '-e "/-m32/d"' \
     '-e "/-m64/d"' \
     '-e "/little cms testbed/d"' \
     '-e "s/[0-9]\{1,\} tics//g"' \
     '-e "s/[0-9]\{1,\} tics\,//g"' \
     '-e "/Nothing to be done/d"' \
     '-e "/Leaving directory/d"' \
     '-e "/Entering directory/d"' \
     '-e "/warning:/d"' \
     '-e "s/\, [0-9]\{1,\}\.[0-9]\{1,\} sec\.//g"'

# non-default C++ flags
CXXFLAGS += -features=extensions,nestedaccess,tmplrefstatic
CXXFLAGS += -template=geninlinefuncs

CONFIGURE_ENV += PYTHON="$(PYTHON)"
CONFIGURE_ENV += PYTHONMODULEDIR="$(PYTHON_VENDOR_PACKAGES)"

CONFIGURE_OPTIONS  +=           --includedir=$(USRINCDIR)/lcms
CONFIGURE_OPTIONS  +=           --enable-shared
CONFIGURE_OPTIONS  +=           --disable-static
CONFIGURE_OPTIONS  +=           --with-jpeg
CONFIGURE_OPTIONS  +=           --with-tiff
CONFIGURE_OPTIONS  +=           --with-zlib
CONFIGURE_OPTIONS  +=           --with-python
CONFIGURE_OPTIONS  +=           --with-pic

# in order to run the tests, we need to use cloney
COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D))

COMPONENT_POST_CONFIGURE_ACTION = \
    ( cd $(@D); \
    $(CP) -p $(SOURCE_DIR)/include/lcms.h ./include/ ; \
    $(RM) -f $(SOURCE_DIR)/include/icc34.h ; \
    $(CP) -p include/icc34.h $(SOURCE_DIR)/include/ )

LINT_FLAGS += -I$(COMPONENT_DIR)/$(COMPONENT_SRC)/include

COMPONENT_POST_INSTALL_ACTION += \
	$(PYTHON.2.7.32) -m compileall $(PROTOUSRLIBDIR)/python2.7/vendor-packages

REQUIRED_PACKAGES += image/library/libjpeg
REQUIRED_PACKAGES += image/library/libtiff
REQUIRED_PACKAGES += library/lcms
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += system/library/c++-runtime
REQUIRED_PACKAGES += system/library/math
