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
COMPONENT_VERSION=      1.12
COMPONENT_FMRI=         x11/documentation/xorg-sgml-doctools
COMPONENT_SUMMARY=      Stylesheets and other data files used to generate X.Org documentation
COMPONENT_ARCHIVE_HASH= \
  sha256:65a9fdddedc17bd5e9c0b00d904960f03f047c3a62de5458989d493c29fec806

include $(WS_MAKE_RULES)/common.mk

COMPONENT_INSTALL_ARGS += pkgconfigdir=$(PKG_CONFIG_PATH.32)

# Auto-generated dependencies
