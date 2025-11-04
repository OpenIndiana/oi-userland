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
# Copyright 2015 Aurelien Larcher
#

X11_CATEGORY=DOC
include ../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/x11.mk

COMPONENT_NAME=         xorg-sgml-doctools
COMPONENT_VERSION=      1.12.1
COMPONENT_SUMMARY=      Stylesheets and other data files used to generate X.Org documentation
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:0a5d54c0706b4e89d5acd4d455db3745ab4ad26be627cce015b90ad403b56d6f
COMPONENT_FMRI=         x11/documentation/xorg-sgml-doctools
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

COMPONENT_INSTALL_ARGS += pkgconfigdir=$(PKG_CONFIG_PATH.64)

# Auto-generated dependencies
