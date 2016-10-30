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
COMPONENT_VERSION= 	1.11.1
COMPONENT_REVISION=	1
COMPONENT_FMRI= 	library/python/numpy
COMPONENT_SRC= 		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= 	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:dc4082c43979cc856a2bf352a8297ea109ccb3244d783ae067eb2ee5b0d577cd
COMPONENT_ARCHIVE_URL= \
  http://sourceforge.net/projects/$(COMPONENT_NAME)/files/NumPy/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)/download
COMPONENT_PROJECT_URL = http://numpy.scipy.org/
COMPONENT_CLASSIFICATION= Development/Python
COMPONENT_SUMMARY= 	Numerical-Python
COMPONENT_LICENSE= 	BSD
COMPONENT_LICENSE_FILE= $(COMPONENT_NAME).license

PYTHON_VERSIONS=	2.7

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/setup.py.mk
include $(WS_TOP)/make-rules/ips.mk

LD_OPTIONS	+= -lm

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
	f2py/docs/usersguide/setup_example.py\
	ma/setup.py\
	matrixlib/setup.py\
	distutils/tests/f2py_ext/setup.py\
	distutils/tests/test_misc_util.py\
	distutils/tests/setup.py\
	distutils/tests/f2py_f90_ext/setup.py\
	distutils/tests/pyrex_ext/setup.py\
	distutils/tests/gen_ext/setup.py\
	distutils/tests/swig_ext/setup.py\
	distutils/exec_command.py\
	distutils/setup.py\
	distutils/cpuinfo.py\
	distutils/system_info.py\
	compat/setup.py

COMPONENT_POST_INSTALL_ACTION = ( $(GSED) -i -e 's:\#!/usr/bin/amd64/python$(PYTHON_VERSION):\#!/usr/bin/python$(PYTHON_VERSION):' \
	$(PROTO_DIR)/usr/bin/f2py$(PYTHON_VERSION) && \
	( for file in $(NUMPY_WRONG_HASHBANG); do $(GSED) -i -e 's:\#!/usr/bin/env python:\#!/usr/bin/python$(PYTHON_VERSION):' \
	$(PROTO_DIR)/usr/lib/python$(PYTHON_VERSION)/vendor-packages/numpy/$${file}; done; ) );

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

REQUIRED_PACKAGES += library/math/openblas
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
