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
# Copyright 2014 Alexander Pyhalov.  All rights reserved.
# Copyright 2015-2017 Aurelien Larcher. All rights reserved.
#
BUILD_BITS= 32_and_64
BUILD_STYLE= justmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		boost
COMPONENT_VERSION=	1.78.0
COMPONENT_REVISION=	2
COMPONENT_SRC_VERSION=	$(subst .,_,$(COMPONENT_VERSION))
COMPONENT_SUMMARY=	boost - free peer-reviewed portable C++ source libraries
COMPONENT_SRC=		$(COMPONENT_NAME)_$(COMPONENT_SRC_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	sha256:8681f175d4bdb26c52222665793eef08490d7758529330f98d3b29dd0735bccc
COMPONENT_ARCHIVE_URL=	https://boostorg.jfrog.io/artifactory/main/release/$(COMPONENT_VERSION)/source/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	http://www.boost.org
COMPONENT_FMRI=		system/library/boost
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_LICENSE=	Boost Software license
COMPONENT_LICENSE_FILE=	LICENSE_1_0.txt

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH.prepend += $(GCC_BINDIR)

DOCDIR= $(USRSHAREDOCDIR)/$(COMPONENT_NAME)-$(COMPONENT_VERSION)

GTAR= $(GNUBIN)/tar

COMPONENT_BUILD_ENV += PATH="$(PATH)" CC="$(CC)" CXX="$(CXX)" LDFLAGS="$(LDFLAGS)"

# Force CPU detection to workaround failure in some virtual environments
COMPONENT_BUILD_ENV += OPENBLAS_CORETYPE=Prescott

BJAM= ./b2 -d+2 -q address-model=$(BITS) cflags="$(CFLAGS)" cxxflags="$(CXXFLAGS)"

BJAM_BUILD_ARGS= $(filter -j%,$(COMPONENT_BUILD_ARGS))
BJAM_BUILD_ARGS += -sBUILD="release <threading>single/multi"
BJAM_BUILD_ARGS += --prefix=$(PROTOUSRDIR)
BJAM_BUILD_ARGS += --libdir=$(PROTOUSRLIBDIR$(BITS))
BJAM_BUILD_ARGS += -sGCC_ROOT_DIRECTORY=$(GCC_ROOT) -sGCC=gcc -sGXX=g++
BJAM_BUILD_ARGS += --user-config=./user-config.jam

BJAM_BUILD_OPTIONS:= --without-python
BJAM_BUILD_OPTIONS += --without-mpi
BJAM_BUILD_OPTIONS += --without-graph_parallel
BJAM_BUILD_ARGS += $(BJAM_BUILD_OPTIONS)

COMPONENT_PRE_BUILD_ACTION= cd $(@D) && $(TOUCH) user-config.jam;

COMPONENT_BUILD_ACTION= cd $(@D); echo "Build $(BITS)-bit"; \
			 $(ENV) $(COMPONENT_BUILD_ENV) \
			 ./bootstrap.sh --prefix=$(USRDIR) --libdir=$(USRLIBDIR$(BITS)) \
				--with-toolset=gcc --with-icu=$(USRDIR) && \
			 $(BJAM) $(BJAM_BUILD_ARGS) release stage

COMPONENT_INSTALL_ACTION= cd $(@D); echo "Install $(BITS)-bit"; \
			   $(ENV) $(COMPONENT_INSTALL_ENV) \
			   $(BJAM) $(BJAM_BUILD_ARGS) install

COMPONENT_POST_INSTALL_ACTION=  \
	$(MKDIR) $(PROTO_DIR)$(DOCDIR); \
	cd $(SOURCE_DIR) && \
	find . -type f \
		\( -name \*.htm\* -o -name \*.css -o -name \*.js \
			-o -name \*.gif -o -name \*.jpg -o -name \*.png -o -name \*.PNG -o -name \*.ico \
			-o -name \*.qbk -o -name \*.pattern \) | \
		$(GTAR) -cf - --files-from=- | $(GTAR) -C $(PROTO_DIR)$(DOCDIR) -xf - ;
 
# Build dependencies for boost locale
REQUIRED_PACKAGES += developer/icu

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += compress/xz
REQUIRED_PACKAGES += compress/zstd
REQUIRED_PACKAGES += library/icu
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
