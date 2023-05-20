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
#   $WS_TOOLS/python-integrate-project dunamai
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		dunamai
HUMAN_VERSION =			1.17.0
COMPONENT_SUMMARY =		dunamai - Dynamic version generation
COMPONENT_PROJECT_URL =		https://github.com/mtkennerly/dunamai
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/a9/9b/44944afb93fd0e1cec69023d5c0a670ee015237de6146eaac926592aa142/dunamai-1.17.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:459381b585a1e78e4070f0d38a6afb4d67de2ee95064bf6b0438ec620dde0820
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# Testing dependencies for this project are maintained using poetry.  We
# neither do have poetry packaged yet, nor support listing poetry dependencies
# without poetry.  For now we just hope all required testing dependencies are
# installed.

# Testing needs access to dunamai binary
COMPONENT_PRE_TEST_ACTION += $(SYMLINK) dunamai-$(PYTHON_VERSION) $(PROTO_DIR)/usr/bin/dunamai ;
COMPONENT_POST_TEST_ACTION += $(RM) $(PROTO_DIR)/usr/bin/dunamai ;
COMPONENT_TEST_ENV += PATH=$(PROTO_DIR)/usr/bin:$(PATH)

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/importlib-metadata
PYTHON_REQUIRED_PACKAGES += library/python/packaging
PYTHON_REQUIRED_PACKAGES += library/python/poetry-core
PYTHON_REQUIRED_PACKAGES += runtime/python
