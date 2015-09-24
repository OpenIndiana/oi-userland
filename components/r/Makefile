#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#

#
# Copyright (c) 2015, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		R
COMPONENT_VERSION=	3.2.0
COMPONENT_PROJECT_URL=	http://www.r-project.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:f5ae953f18ba6f3d55b46556bbbf73441350f9fd22625402b723a2b81ff64f35
COMPONENT_ARCHIVE_URL=	http://cran.mtu.edu/src/base/R-3/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/r

TPNO=			22535

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))

# Get rid of compiler path set in RUNPATH
LDFLAGS += $(studio_NORUNPATH)

LDFLAGS += $(CC_BITS)

LDFLAGS += $(studio_PIC)
LDFLAGS += $(LD_Z_TEXT)
LDFLAGS += $(LD_DEF_LIBS)

STUDIO_LIBS_PATH =	/usr/lib/studio/64
R_LIBS_PATH =		/usr/lib/$(MACH64)/R/lib
JAVA_LIBS_PATH =	$(JAVA8_HOME)/jre/lib/$(MACH64)/server

LDFLAGS += -L$(STUDIO_LIBS_PATH) -R$(STUDIO_LIBS_PATH) \
		-lsunperf -lfsu -lmtsk -lpicl -lkstat

F95 =			$(SPRO_VROOT)/bin/f95

CONFIGURE_ENV += CC="$(CC)"
CONFIGURE_ENV += CXX="$(CXX)"
CONFIGURE_ENV += F77="$(F95) $(CC_BITS)"
CONFIGURE_ENV += FC="$(F95) $(CC_BITS)"

CONFIGURE_ENV += CPPFLAGS=""
CONFIGURE_ENV += CPICFLAGS="$(studio_PIC)"
CONFIGURE_ENV += CFLAGS="-xO3 -xc99 -xlibmieee $(CC_BITS)"
CONFIGURE_ENV += CXXFLAGS="-xO3 $(CC_BITS)"
CONFIGURE_ENV += FPICFLAGS="$(studio_PIC)"
CONFIGURE_ENV += FFLAGS="-xO3 $(CC_BITS)"
CONFIGURE_ENV += FCFLAGS="-xO3 $(CC_BITS)"
CONFIGURE_ENV += FCLIBS="-lsunperf -lfsu -lsunmath"
CONFIGURE_ENV += FLIBS="-lsunperf -lfsu -lsunmath"
CONFIGURE_ENV += LDFLAGS="$(LDFLAGS) -L$(R_LIBS_PATH) -R$(R_LIBS_PATH)"

# Set the various Java variables otherwise it auto-detects the 32-bit ones.
CONFIGURE_ENV += JAVA_CPPFLAGS="-I$(JAVA8_HOME)/jre/../include -I$(JAVA8_HOME)/jre/../include/solaris"
CONFIGURE_ENV += JAVA_LIBS="-L$(JAVA_LIBS_PATH) -R$(JAVA_LIBS_PATH) -ljvm"

# From Brian Whitney:
# You need to define this option on SPARC, otherwise you will get quad
# arithmetic on SPARC but not on x86.  Really makes some R functions run
# very slow on SPARC (COR path).
CONFIGURE_OPTIONS.i386 =
CONFIGURE_OPTIONS.sparc =	--disable-long-double
CONFIGURE_OPTIONS +=		$(CONFIGURE_OPTIONS.$(MACH))

CONFIGURE_OPTIONS += --enable-R-shlib
CONFIGURE_OPTIONS += --with-blas='-lsunperf'
CONFIGURE_OPTIONS += --with-ICU
CONFIGURE_OPTIONS += --with-lapack
CONFIGURE_OPTIONS += --with-recommended-packages
CONFIGURE_OPTIONS += --with-tcltk
CONFIGURE_OPTIONS += --enable-prebuilt-html

COMPONENT_PRE_TEST_ACTION = \
	$(RM) $(BUILD_DIR_64)/tests/Examples/*.prev

COMPONENT_PRE_SYSTEM_TEST_ACTION = \
	$(RM) $(BUILD_DIR_64)/tests/Examples/*.prev

# Increase stack limit to allow the "infinite recursion" test to work.
COMPONENT_TEST_ENV_CMD =	ulimit -Ss 32768 ; $(ENV)
COMPONENT_SYSTEM_TEST_ENV_CMD =	ulimit -Ss 32768 ; $(ENV)

# Master test results are different between x86 and SPARC.
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-$(MACH).master

COMPONENT_TEST_TRANSFORMS += \
	'-n ' \
	'-e "/^Testing examples for package /p" ' \
	'-e "/^  comparing /p" ' \
	'-e "/^running /p" ' \
	'-e "/^  expect some differences/p" '

ASLR_MODE = $(ASLR_ENABLE)

# Use the installed version of R, not the one in the build area.
# These definitions override those found in .../test/Makefile.
COMPONENT_SYSTEM_TEST_ARGS += R="LANGUAGE=en LC_ALL=C SRCDIR=$(srcdir) R_DEFAULT_PACKAGES= /usr/bin/R --vanilla"
COMPONENT_SYSTEM_TEST_ARGS += R2="R_DEFAULT_PACKAGES= /usr/bin/R --vanilla"
COMPONENT_SYSTEM_TEST_ARGS += R3="/usr/bin/R CMD check"
COMPONENT_SYSTEM_TEST_ARGS += RDIFF="/usr/bin/R CMD Rdiff"
COMPONENT_SYSTEM_TEST_ARGS += RDCONV="LC_CTYPE=C /usr/bin/R CMD Rdconv"

COMPONENT_TEST_ARGS =		-k -i
COMPONENT_SYSTEM_TEST_ARGS +=	-k -i

configure:	$(CONFIGURE_64)

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(TEST_64)

# Need to build the tests before use them.
system-test:	build $(SYSTEM_TEST_64)

REQUIRED_PACKAGES += image/library/libjpeg
REQUIRED_PACKAGES += image/library/libpng
REQUIRED_PACKAGES += image/library/libtiff
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/icu
REQUIRED_PACKAGES += library/pcre
REQUIRED_PACKAGES += library/readline
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/fortran-runtime
REQUIRED_PACKAGES += system/library/iconv/xsh4/latin
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/library/sunperf
REQUIRED_PACKAGES += web/curl
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxmu
REQUIRED_PACKAGES += x11/library/toolkit/libxt
