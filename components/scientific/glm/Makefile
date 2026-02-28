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
# Copyright 2020 Aurelien Larcher
# Copyright 2025 Klaus Ziegler
#

BUILD_STYLE= cmake
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= glm
COMPONENT_VERSION= 1.0.3
COMPONENT_FMRI= library/math/glm
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_SUMMARY= glm - OpenGL Mathematics, A C++ mathematics library for graphics programming
COMPONENT_PROJECT_URL= https://glm.g-truc.net
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:6775e47231a446fd086d660ecc18bcd076531cfedd912fbd66e576b118607001
COMPONENT_ARCHIVE_URL= https://github.com/g-truc/glm/archive/$(COMPONENT_VERSION).tar.gz
COMPONENT_LICENSE= MIT
COMPONENT_LICENSE_FILE= copying.txt

include $(WS_MAKE_RULES)/common.mk

CMAKE_OPTIONS += -DCMAKE_BUILD_TYPE=Release
CMAKE_OPTIONS += -DGLM_BUILD_TESTS=On

# remove backup'd file from patch phase to prevent its appearance in the sample-manifest
# install pkgconfig file.
COMPONENT_POST_INSTALL_ACTION += ( \
	$(RM) $(PROTOUSRINCDIR)/glm/detail/*.hpp.* ; \
	$(MKDIR) $(PROTOUSRLIBDIR64)/pkgconfig ; \
	$(GSED) -e 's/@GLM_VERSION@/$(COMPONENT_VERSION)/g' \
	$(COMPONENT_DIR)/files/glm.pc > $(PROTOUSRLIBDIR64)/pkgconfig/glm.pc )

# Note that test-core_func_integer fails with gcc-13 but is ok with gcc-7 and gcc-10.
COMPONENT_TEST_TRANSFORMS += ' -e "/aborted/p" '

# Auto-generated dependencies
