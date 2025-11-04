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
# This file was automatically generated using the following command:
#   $WS_TOOLS/python-integrate-project py3c
#

BUILD_STYLE = pyproject
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		py3c
HUMAN_VERSION =			1.4
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		Python compatibility headers
COMPONENT_PROJECT_URL =		http://py3c.readthedocs.io/
COMPONENT_ARCHIVE_HASH =	\
	sha256:abc745079ef906148817f4472c3fb4bc41d62a9ea51a746b53e09819494ac006
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE.MIT

# https://github.com/encukou/py3c/issues/56
COMPONENT_ARCHIVE_URL =		\
	https://github.com/encukou/py3c/archive/refs/tags/v$(HUMAN_VERSION).tar.gz

include $(WS_MAKE_RULES)/common.mk

# see $(SOURCE_DIR)/Makefile
# and https://github.com/encukou/py3c/issues/24#issuecomment-1447981119
COMPONENT_POST_INSTALL_ACTION += \
	$(MKDIR) $(PROTO_DIR)$(PKG_CONFIG_PATH.$(BITS)) ; \
	$(GSED) -e 's:@includedir@:$(shell $(PYTHON) -c "from sysconfig import get_paths; print(get_paths()[\"include\"])"):' \
		-e 's|^Cflags:.*$$|& -I$${includedir}/py3c|' \
		$(@D)/py3c.pc.in \
		> $(PROTO_DIR)$(PKG_CONFIG_PATH.$(BITS))/py3c.pc-$(PYTHON_VERSION) ;

# Normalize special PYV case
COMPONENT_TEST_TRANSFORMS += "-e 's/\(cpython-\)$(shell echo $(PYTHON_VERSION) | tr -d .)/\1\$$(PYV)/'"

# Replace Python version in pkgconfig file names
GENERATE_EXTRA_SED += -e 's/\(py3c\.pc-\)3\.[0-9]*$$/\1$$(PYVER)/'

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += runtime/python
