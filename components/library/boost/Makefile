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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		boost
COMPONENT_VERSION=	1.64.0
COMPONENT_SRC_VERSION=	1_64_0
COMPONENT_REVISION=     2
COMPONENT_FMRI=		system/library/boost
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_SUMMARY=	boost - free peer-reviewed portable C++ source libraries
COMPONENT_SRC=		$(COMPONENT_NAME)_$(COMPONENT_SRC_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:7bcc5caace97baa948931d712ea5f37038dbb1c5d89b43ad4def4ed7cb683332
COMPONENT_ARCHIVE_URL= \
  http://sourceforge.net/projects/boost/files/boost/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)/download
COMPONENT_PROJECT_URL=	http://www.boost.org
COMPONENT_LICENSE=	Boost Software license

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/ips.mk
include $(WS_MAKE_RULES)/modules.mk

PATH=$(GCC_ROOT)/bin:$(PATH.illumos)

LIBDIR.32= $(USRLIBDIR)
LIBDIR.64= $(USRLIBDIR64)
LIBDIR= $(LIBDIR.$(BITS))

DOCDIR=$(USRSHAREDOCDIR)/$(COMPONENT_NAME)-$(COMPONENT_VERSION)

GTAR=$(GNUBIN)/tar
BJAM=./bjam --v2 -d+2 -q address-model=$(BITS) \
	cflags="$(CFLAGS)" cxxflags="$(CXXFLAGS)" \
	-sBUILD="release <threading>single/multi" \
	--prefix=$(PROTO_DIR)$(USRDIR) \
	--libdir=$(PROTO_DIR)$(LIBDIR) \
	-sGCC_ROOT_DIRECTORY=$(GCC_ROOT) -sGCC=gcc -sGXX=g++ \
	--user-config=./user-config.jam --without-fiber

COMPONENT_BUILD_ENV += PATH="$(PATH)" CC="$(CC)" CXX="$(CXX)" LDFLAGS="$(LDFLAGS)"

# Force CPU detection to workaround failure in some virtual environments
COMPONENT_BUILD_ENV += OPENBLAS_CORETYPE=Prescott

COMPONENT_PRE_BUILD_ACTION = \
			$(MODULES_ENV); $(MODULE_PURGE); \
			$(MODULE_LOAD) mpich/gcc/$(BITS)/latest

BJAM_BUILD_ARGS:= $(filter -j%,$(COMPONENT_BUILD_ARGS))

COMPONENT_BUILD_ACTION = \
	    		./bootstrap.sh --prefix=$(USRDIR) --libdir=$(LIBDIR) \
				--with-toolset=gcc --with-icu=$(USRDIR); \
			echo 'using mpi ;' > ./user-config.jam; \
			$(BJAM) $(BJAM_BUILD_ARGS) release stage

COMPONENT_POST_BUILD_ACTION = \
			$(MODULE_UNLOAD) mpich/gcc/$(BITS)/latest

COMPONENT_PRE_INSTALL_ACTION = \
			$(MODULES_ENV); $(MODULE_PURGE); \
			$(MODULE_LOAD) mpich/gcc/$(BITS)/latest

COMPONENT_INSTALL_ACTION = \
			$(BJAM) install \

COMPONENT_POST_INSTALL_ACTION= \
	$(MKDIR) $(PROTO_DIR)$(DOCDIR); \
	cd $(SOURCE_DIR) && \
	find . -type f \
		\( -name \*.htm\* -o -name \*.css -o -name \*.js \
			-o -name \*.gif -o -name \*.jpg -o -name \*.png -o -name \*.PNG -o -name \*.ico \
			-o -name \*.qbk -o -name \*.pattern \) | \
		$(GTAR) -cf - --files-from=- | $(GTAR) -C $(PROTO_DIR)$(DOCDIR) -xf - ; \
	$(MODULE_UNLOAD) mpich/gcc/$(BITS)/latest
 


$(BUILD_DIR)/%/.built:    $(SOURCE_DIR)/.prep
	$(RM) -r $(@D) ; $(MKDIR) $(@D)
	$(CLONEY) $(SOURCE_DIR) $(@D)
	(cd $(@D);\
		$(COMPONENT_PRE_BUILD_ACTION) ; \
		$(ENV) $(COMPONENT_BUILD_ENV) $(COMPONENT_BUILD_ACTION) ; \
		$(COMPONENT_POST_BUILD_ACTION))
	$(TOUCH) $@

$(BUILD_DIR)/%/.installed:  $(BUILD_DIR)/%/.built
	(cd $(@D); \
		$(COMPONENT_PRE_INSTALL_ACTION) ; \
		$(COMPONENT_INSTALL_ENV) $(COMPONENT_INSTALL_ACTION) ; \
		$(COMPONENT_POST_INSTALL_ACTION))
	$(TOUCH) $@

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

clean::
	$(RM) -r $(BUILD_DIR) $(PROTO_DIR)

# Build dependencies for boost locale
REQUIRED_PACKAGES += developer/icu

# Build dependencies for boost mpi
REQUIRED_PACKAGES += library/mpich/gcc/modulefiles

# Build dependencies for boost numpy
REQUIRED_PACKAGES += library/python/numpy-27

# Auto-generated dependencies
REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += library/icu
REQUIRED_PACKAGES += library/mpich/gcc
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library/math
