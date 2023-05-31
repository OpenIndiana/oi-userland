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
#   $WS_TOOLS/python-integrate-project ansible
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		ansible
HUMAN_VERSION =			8.0.0
COMPONENT_SUMMARY =		ansible - Radically simple IT automation
COMPONENT_PROJECT_URL =		https://ansible.com/
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/bf/d2/41bfb43774c98b6df721170ec2070d517e7ee20ff106edeaa2e29dc0fa7e/ansible-8.0.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:8670c7c46021c188cac235e9fde7adadbb3c380c2436a3b0c1c493c4ba10bcab
COMPONENT_LICENSE =		GPL-3.0-only
COMPONENT_LICENSE_FILE =	COPYING

# This project is a collection of other projects (see tags.yaml), each with its
# own test requirements.  We do not support testing of that (yet).
TEST_STYLE = none

# This is a standalone application.  Since no other Python project depends on
# it we just provide single unversioned package.
SINGLE_PYTHON_VERSION = yes

include $(WS_MAKE_RULES)/common.mk

# Remove python shebang from installed files.  We usually do this by a patch,
# but this project have many files so it is far easier to use a script to avoid
# maintenance nightmage on upgrades.  We need to recompile modified files to
# make sure pyc files are not outdated.
COMPONENT_POST_INSTALL_ACTION += \
	for d in $(PROTO_DIR)/$(PYTHON_DIR)/site-packages $(PROTO_DIR)/$(PYTHON_LIB) ; do \
		[ -d $$d ] || continue ; \
		$(FIND) $$d -type f -name '*.py' -print0 ; \
	done | /usr/bin/xargs -0 $(GSED) -i -e '1{/^\#!.*python/d}' ; \
	$(PYTHON) -m compileall $(PROTO_DIR)/$(PYTHON_DIR)/site-packages $(PROTO_DIR)/$(PYTHON_LIB) ;

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/ansible-core
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
