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
# Copyright 2016 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= 	numpy
COMPONENT_VERSION= 	1.13.3
COMPONENT_FMRI= 	library/python/numpy
COMPONENT_SRC= 		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= 	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:4c6b4eef790528bebb7ec9590d74cc193868940fe68e4109a91c196df72d8094
COMPONENT_ARCHIVE_URL= \
  https://github.com/numpy/numpy/releases/download/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://numpy.scipy.org/
COMPONENT_CLASSIFICATION= Development/Python
COMPONENT_SUMMARY= 	Numerical-Python
COMPONENT_LICENSE= 	BSD

PYTHON_VERSIONS=	2.7

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

LD_OPTIONS	+= -lm

CFLAGS+= -std=gnu99 -D_XOPEN_SOURCE=600

COMPONENT_PRE_BUILD_ACTION  +=	$(CLONEY) $(SOURCE_DIR) $(@D) ;

# This ugly hack is necessary to compile 64-bit modules
# http://mail.scipy.org/pipermail/numpy-discussion/2010-June/051189.html
COMPONENT_PRE_BUILD_ACTION  +=	echo '\#!/bin/sh' > $(BUILD_DIR)/fake_cc ;
COMPONENT_PRE_BUILD_ACTION  +=	echo 'gcc -m$(BITS) $$@' >> $(BUILD_DIR)/fake_cc ;
COMPONENT_PRE_BUILD_ACTION  +=	chmod 755 $(BUILD_DIR)/fake_cc

COMPONENT_PRE_INSTALL_ACTION  +=	echo '\#!/bin/sh' > $(BUILD_DIR)/fake_cc ;
COMPONENT_PRE_INSTALL_ACTION  +=	echo 'gcc -m$(BITS) $$@' >> $(BUILD_DIR)/fake_cc ;
COMPONENT_PRE_INSTALL_ACTION  +=	chmod 755 $(BUILD_DIR)/fake_cc
	
COMPONENT_POST_BUILD_ACTION =	$(RM) $(BUILD_DIR)/fake_cc
COMPONENT_POST_INSTALL_ACTION =	$(RM) $(BUILD_DIR)/fake_cc

CC=$(BUILD_DIR)/fake_cc

COMPONENT_BUILD_ARGS	=	--fcompiler=gnu95 

NUMPY_WRONG_HASHBANG =\
	fft/tests/test_helper.py\
	testing/print_coercion_tables.py\
	testing/setup.py\
	setup.py\
	f2py/use_rules.py\
	f2py/common_rules.py\
	f2py/capi_maps.py\
	f2py/auxfuncs.py\
	f2py/f2py2e.py\
	f2py/__init__.py\
	f2py/cfuncs.py\
	f2py/func2subr.py\
	f2py/rules.py\
	f2py/cb_rules.py\
	f2py/crackfortran.py\
	f2py/f90mod_rules.py\
	f2py/diagnose.py\
	f2py/setup.py\
	ma/setup.py\
	matrixlib/setup.py\
	distutils/tests/test_misc_util.py\
	distutils/exec_command.py\
	distutils/setup.py\
	distutils/cpuinfo.py\
	distutils/system_info.py\
	compat/setup.py

COMPONENT_POST_INSTALL_ACTION = ( $(GSED) -i -e 's:\#!/usr/bin/amd64/python$(PYTHON_VERSION):\#!/usr/bin/python$(PYTHON_VERSION):' \
	$(PROTO_DIR)/usr/bin/f2py$(PYTHON_VERSION) && \
	( for file in $(NUMPY_WRONG_HASHBANG); do $(GSED) -i -e 's:\#!/usr/bin/env python:\#!/usr/bin/python$(PYTHON_VERSION):' \
	$(PROTO_DIR)/usr/lib/python$(PYTHON_VERSION)/vendor-packages/numpy/$${file}; done; ) );

# Borrowed from solaris-userland
# Merge 32-bit & 64-bit versions of header with different SIZEOF values
NUMPYCONFIG_H = $(PYTHON_VENDOR_PACKAGES.32)/numpy/core/include/numpy/_numpyconfig.h
$(BUILD_DIR)/.merged-header: $(INSTALL_32_and_64)
	-$(RM) $(PROTO_DIR)/$(NUMPYCONFIG_H)
	print '#include <sys/isa_defs.h>' > $(PROTO_DIR)/$(NUMPYCONFIG_H)
	$(GDIFF) -D _LP64 \
	    $(BUILD_DIR)/$(MACH32)-$(PYTHON_VERSION)/src.solaris-*.32bit-$(PYTHON_VERSION)/numpy/core/include/numpy/_numpyconfig.h \
	    $(BUILD_DIR)/$(MACH64)-$(PYTHON_VERSION)/src.solaris-*.64bit-$(PYTHON_VERSION)/numpy/core/include/numpy/_numpyconfig.h \
	    >> $(PROTO_DIR)/$(NUMPYCONFIG_H) ; \
	diffstatus=$$? ; \
	if (( $$diffstatus != 1 )) ; then exit $$diffstatus ; fi
	touch $@

COMPONENT_TEST_DIR  = $(COMPONENT_DIR)
COMPONENT_TEST_ARGS = -c 'import numpy; numpy.test()'
COMPONENT_TEST_ENV += F77="$(F77) -m$(BITS)"
COMPONENT_TEST_ENV += FC="$(FC) -m$(BITS)"
COMPONENT_TEST_TRANSFORMS += '-e "s|^\\(Ran [0-9]* tests\\) in .*s|\1|"'
COMPONENT_TEST_TRANSFORMS += '-e "s|$(PROTO_DIR)|\\$$(PROTO_DIR)|g"'

build: $(BUILD_32_and_64)

install: $(BUILD_DIR)/.merged-header

test: $(TEST_32_and_64)

REQUIRED_PACKAGES += library/math/openblas
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
