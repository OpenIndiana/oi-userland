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
COMPONENT_VERSION=	0.8.18
COMPONENT_REVISION=	2
COMPONENT_SUMMARY=	compizconfig libraries - is an alternative configuration system for compiz
COMPONENT_CLASSIFICATION=	Development/Python
COMPONENT_PROJECT_URL=	http://www.northfield.ws
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
	sha256:9a8bd0adb7e9a3893f9499fcfdaa354952f7ec2eb2eb4f39c43318f5b4cfc908
COMPONENT_ARCHIVE_URL=	http://www.northfield.ws/projects/compiz/releases/$(COMPONENT_VERSION)/$(COMPONENT_SRC).tar.xz
COMPONENT_FMRI=		library/python/python-compizconfig
COMPONENT_LICENSE=	GPL-2.0-only
COMPONENT_LICENSE_FILE=	COPYING

SINGLE_PYTHON_VERSION = no

define python-variant-rule
VARIANT_PYTHON.$(1) = $(BUILD_DIR)/python-$(1)
endef
$(foreach pyver, $(PYTHON_VERSIONS), $(eval $(call python-variant-rule,$(pyver))))

VARIANTS_64 =
define variants-rule
VARIANTS_64 += $(VARIANT_PYTHON.$(1))
$(VARIANT_PYTHON.$(1))/$(MACH64)/.configured:	BITS=64
$(VARIANT_PYTHON.$(1))/$(MACH64)/.configured:	PYTHON_VERSION=$(1)
$(VARIANT_PYTHON.$(1))/$(MACH64)/.built:	BITS=64
$(VARIANT_PYTHON.$(1))/$(MACH64)/.built:	PYTHON_VERSION=$(1)
$(VARIANT_PYTHON.$(1))/$(MACH64)/.installed:	BITS=64
$(VARIANT_PYTHON.$(1))/$(MACH64)/.installed:	PYTHON_VERSION=$(1)
endef
$(foreach pyver, $(PYTHON_VERSIONS), $(eval $(call variants-rule,$(pyver))))

BUILD_64 = $(VARIANTS_64:%=%/$(MACH64)/.built)
INSTALL_64 = $(VARIANTS_64:%=%/$(MACH64)/.installed)

TEST_TARGET = $(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_ENV +=	PATH=$(PATH)
CONFIGURE_ENV +=	PYTHON=$(PYTHON)
CONFIGURE_ENV +=	am_cv_python_pythondir="$(PYTHON_LIB)"
CONFIGURE_ENV +=	am_cv_python_pyexecdir="$(PYTHON_LIB)"

CONFIGURE_OPTIONS +=	--disable-static
CONFIGURE_OPTIONS +=	--with-cython=cython-$(PYTHON_VERSION)

# Rename pkgconfig files in PKG_CONFIG_PATH to contain version number
COMPONENT_POST_INSTALL_ACTION += \
	for f in $(PROTO_DIR)$(PKG_CONFIG_PATH.$(BITS))/* ; do \
		[[ -f $$f ]] || continue ; \
		for v in $(PYTHON_VERSIONS) ; do \
			[[ "$$f" == "$${f%%$$v}" ]] || continue 2 ; \
		done ; \
		$(MV) $$f $$f-$(PYTHON_VERSION) ; \
	done ;
# Rename the generated library to follow Python SOABI naming scheme
COMPONENT_POST_INSTALL_ACTION += \
	EXT_SUFFIX=$(shell $(PYTHON) -c "import sysconfig; print(sysconfig.get_config_var('EXT_SUFFIX'))") ; \
	$(MV) $(PROTO_DIR)$(PYTHON_LIB)/compizconfig.so $(PROTO_DIR)$(PYTHON_LIB)/compizconfig$$EXT_SUFFIX ;

# We need to add -$(PYV) to package fmri
GENERATE_EXTRA_CMD += | \
	$(GSED) -e 's/^\(set name=pkg.fmri [^@]*\)\(.*\)$$/\1-$$(PYV)\2/'
# Replace Python version in pkgconfig file names
GENERATE_EXTRA_CMD += | \
	$(GSED) -e 's|\(pkgconfig/compizconfig-python\.pc-\)3\.[0-9]*$$|\1$$(PYVER)|' | uniq

# Manually added dependencies
PYTHON_REQUIRED_PACKAGES += library/python/cython
PYTHON_REQUIRED_PACKAGES += runtime/python

# Auto-generated dependencies
REQUIRED_PACKAGES += desktop/compiz/library/libcompizconfig
REQUIRED_PACKAGES += system/library
