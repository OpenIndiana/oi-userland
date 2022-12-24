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
#   $WS_TOOLS/python-integrate-project tox-current-env
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		tox-current-env
HUMAN_VERSION =			0.0.10
COMPONENT_SUMMARY =		tox-current-env - Use current environment instead of virtualenv for tox testenvs
COMPONENT_PROJECT_URL =		https://github.com/fedora-python/tox-current-env
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/9d/6a/0097135fb7c8835f31ebfb03ba7cddaeedad13b0ebddc6b11ba1ab0f0bd8/tox-current-env-0.0.10.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:ba3229ff0c5d01d56c70bd5e87ccf43158c4ead7f7769d3efb7a78ad2dea87a5
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

# This component is required by following bootstrapped components so it must be
# bootstrapped too.
# - Userland testing framework (see setup.py.mk)
PYTHON_TEST_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# Revert back unneeded PYV normalizations ...
COMPONENT_TEST_TRANSFORMS += "-e 's/py\$$(PYV)]/py$(shell echo $(PYTHON_VERSION) | tr -d .)]/'"
# ... and re-sort list of pytest unit tests after the revert
COMPONENT_TEST_TRANSFORMS += \
	"| ( \
		$(GSED) -u -e '/^=\{1,\} test session starts /q' ; \
		$(GSED) -u -e '/^$$/q' ; \
		$(GSED) -u -e '/^$$/Q' | LC_ALL=C $(GSORT) | $(NAWK) '{print}END{if(NR>0)printf(\"\\\\n\")}' ; \
		$(CAT) \
	) | $(COMPONENT_TEST_TRANSFORMER) -e ''"

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/importlib-metadata
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/tox
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/packaging
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-xdist
