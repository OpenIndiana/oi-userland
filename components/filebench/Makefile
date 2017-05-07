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

include ../../make-rules/shared-macros.mk

COMPONENT_NAME= filebench
COMPONENT_VERSION= 1.4.9.1
COMPONENT_SUMMARY= FileBench Commands, Workloads, Scripts, and Config Files
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:a1d1516083a1d46bccf6246caf709e800e93eccf17572583343e77726b720678
COMPONENT_ARCHIVE_URL= \
  http://sourceforge.net/projects/filebench/files/filebench/$(COMPONENT_NAME)-$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)/download
COMPONENT_PROJECT_URL = http://sourceforge.net/apps/mediawiki/filebench/index.php?title=Main_Page

COMPONENT_LICENSE_FILE=	LICENSE
COMPONENT_LICENSE=	CDDL
COMPONENT_FMRI=	benchmark/filebench

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

PATCH_LEVEL=0

COMPONENT_PREP_ACTION =        (cd $(@D) &&\
                                        aclocal -I . &&\
                                        autoheader &&\
                                        automake -a -f -c --gnu &&\
                                        autoconf &&\
					$(RM) config.h ) 

CONFIGURE_PREFIX=/usr/benchmarks/filebench

CONFIGURE_OPTIONS+=	--datarootdir=/usr/benchmarks

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)
