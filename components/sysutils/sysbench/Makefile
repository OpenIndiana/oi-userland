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
# Copyright 2017 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= sysbench
COMPONENT_VERSION= 0.4.12
COMPONENT_REVISION= 2
COMPONENT_SUMMARY= Sysbench - sytem performance benchmark
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:83fa7464193e012c91254e595a89894d8e35b4a38324b52a5974777e3823ea9e
COMPONENT_ARCHIVE_URL=  \
  ftp://ftp.netbsd.org/pub/pkgsrc/distfiles/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = https://github.com/akopytov/sysbench
COMPONENT_CLASSIFICATION= Development/System
COMPONENT_FMRI= benchmark/sysbench
COMPONENT_LICENSE=  GPLv2
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CFLAGS+= -std=c89

COMPONENT_PREP_ACTION+=        (cd $(@D) && $(TOUCH) NEWS AUTHORS && autoreconf -fi)

COMPONENT_POST_INSTALL_ACTION+= \
        $(CP) $(COMPONENT_SRC)/doc/manual.xml $(PROTOUSRSHAREDOCDIR)/$(COMPONENT_NAME)

CONFIGURE_OPTIONS +=    --enable-largefile
CONFIGURE_OPTIONS +=    --bindir=/usr/benchmarks/sysbench/bin

CONFIGURE_ENV +=	mysqlconfig=$(MYSQL_CONFIG)

build: $(BUILD_64)

install: $(INSTALL_64)

test: $(NO_TESTS)

REQUIRED_PACKAGES += library/libxslt
REQUIRED_PACKAGES += database/mariadb-101/library
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
