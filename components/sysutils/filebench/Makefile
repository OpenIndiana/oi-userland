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
# Copyright 2014 Alexander Pyhalov.  All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= filebench
COMPONENT_VERSION= 1.4.9.1
COMPONENT_REVISION= 2
COMPONENT_FMRI=	benchmark/filebench
COMPONENT_SUMMARY= FileBench Commands, Workloads, Scripts, and Config Files
COMPONENT_CLASSIFICATION= Development/System
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:77ae91b83c828ded1219550aec74fbbd6975dce02cb5ab13c3b99ac2154e5c2e
COMPONENT_ARCHIVE_URL= \
  https://github.com/filebench/filebench/archive/$(COMPONENT_VERSION).tar.gz
COMPONENT_PROJECT_URL = https://github.com/filebench/filebench/wiki
COMPONENT_LICENSE_FILE=	LICENSE
COMPONENT_LICENSE=	CDDL

include $(WS_MAKE_RULES)/common.mk

PATCH_LEVEL=0

COMPONENT_PREP_ACTION = (cd $(@D) &&\
                         aclocal -I . &&\
                         autoheader &&\
                         automake -a -f -c --gnu &&\
                         autoconf &&\
                         $(RM) config.h ) 

CONFIGURE_PREFIX=/usr/benchmarks/filebench

CONFIGURE_OPTIONS+=	--datarootdir=/usr/benchmarks

# Auto-generated dependencies
REQUIRED_PACKAGES += library/libtecla
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
