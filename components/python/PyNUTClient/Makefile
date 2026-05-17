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
#   $WS_TOOLS/python-integrate-project -d python/PyNUTClient pynutclient
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pynutclient
HUMAN_VERSION =			2.8.5
COMPONENT_SUMMARY =		Python client bindings for NUT
COMPONENT_PROJECT_URL =		https://github.com/networkupstools/nut/tree/master/scripts/python/module
COMPONENT_ARCHIVE_HASH =	\
	sha256:53dff5840ea1aab5a40757f5b5d16eceee13ee17820bfd74bdcb7e316ce613e7
COMPONENT_LICENSE =		GPL-3.0-only
COMPONENT_LICENSE_FILE =	LICENSE-GPL3

include $(WS_MAKE_RULES)/common.mk

#
# To run tests you need:
#
# 1) to have this in /etc/nut/ups.conf (see PyNUTClient/test_nutclient.py):
#
#	[dummy]
#		driver = dummy-ups
#		desc = "Test device"
#		port = /usr/share/nut/etc-samples/evolution500.seq.dummy-ups.sample
#
# 2) the svc:/system/power/nut-server:default service running:
#
# 	svcadm enable svc:/system/power/nut-server:default
#
# 3) start dummy-ups:
#
# 	/usr/lib/nut/bin/dummy-ups -a dummy

# Testing needs to find the PyNUT module
COMPONENT_TEST_ENV += PYTHONPATH=$(PROTOPYTHONVENDORDIR)/PyNUTClient

# Remove colors from test output
COMPONENT_TEST_TRANSFORMS += "-e 's/\x1b\[[0-9;]*m//g'"

# Needed for:
# 	/etc/nut/ups.conf
# 	svc:/system/power/nut-server:default
TEST_REQUIRED_PACKAGES += system/management/nut/server

# Needed for:
# 	/usr/lib/nut/bin/dummy-ups
# 	/usr/share/nut/etc-samples/evolution500.seq.dummy-ups.sample
TEST_REQUIRED_PACKAGES += system/management/nut/drivers/software

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += runtime/python
