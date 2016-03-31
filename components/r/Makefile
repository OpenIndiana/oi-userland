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
# Copyright (c) 2015, 2016, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		R
COMPONENT_VERSION=	3.2.3
COMPONENT_PROJECT_URL=	http://www.r-project.org/
COMPONENT_ARCHIVE_HASH=	\
    sha256:b93b7d878138279234160f007cb9b7f81b8a72c012a15566e9ec5395cfd9b6c1
COMPONENT_ARCHIVE_URL=	http://cran.mtu.edu/src/base/R-3/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/r

TPNO=			26540

# Need to build the tests before using them.
SYSTEM_TEST_TARGET= build $(SYSTEM_TEST_64)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))

# Get rid of compiler path set in RUNPATH
LDFLAGS += $(studio_NORUNPATH)

LDFLAGS += $(CC_BITS)

LDFLAGS += $(studio_PIC)
LDFLAGS += $(LD_DEF_LIBS)

STUDIO_LIBS_PATH =	$(USRLIBDIR)/studio/64
# R_LIBS_PATH is used when creating /usr/lib/64/R/etc/Makeconf
# Using a resolved pathname here (rather than say $(USRLIBDIR64)/R/lib) so
# that the Makeconf-GNU.patch patch used by the COMPONENT_POST_INSTALL_ACTION
# will just work on both platforms.
R_LIBS_PATH =		/usr/lib/64/R/lib
JAVA_LIBS_PATH =	$(JAVA8_HOME)/jre/lib/$(MACH64)/server

LDFLAGS += -L$(STUDIO_LIBS_PATH) -R$(STUDIO_LIBS_PATH) \
		-lsunperf -lfsu -lmtsk -lpicl -lkstat

# Augment the PATH and set CC/CXX/F95 such that the build environment doesn't
# leak into usr/lib/64/etc/Makeconf and force consumers to have a setup like
# our build environment to build R modules.
export PATH=$(SPRO_VROOT)/bin:$(USRBINDIR):$(GNUBIN)
CC =		cc
CXX =		CC
F95 =		f95
ifeq   ($(strip $(PARFAIT_BUILD)),yes)
export PATH=$(PARFAIT_TOOLS):$(SPRO_VROOT)/bin:$(USRBINDIR):$(GNUBIN)
endif


CONFIGURE_ENV += F77="$(F95) $(CC_BITS)"
CONFIGURE_ENV += FC="$(F95) $(CC_BITS)"

# For now, R is built with a very specific set of optimization flags to match
# Oracle-provided builds.  These should be re-evaluated when upgrading to
# Studio 12.5 or later or when next upgrading R.
studio_OPT= -xO3
studio_XBITS=
studio_XREGS=
studio_IROPTS=
studio_C99MODE= $(studio_C99_ENABLE)
studio_ALIGN=
studio_MT=

CFLAGS.studio += -xlibmieee
CXXFLAGS += -std=c++11
# We (the Userland) team don't need -D__MATHERR_RENAME_EXCEPTION for the
# creation of the R packages we provide in Solaris. It would be needed by
# our customers that try to install R packages that use C++. And they would
# be using the version of the Studio compilers on their machine(s) to do this.
# Studio 12.5 will hopefully automatically provide this definition when C++
# code is compiled with "-std=c++11". When that version of the Studio
# compilers is released, we should encourage customers to install it, but
# for those still using Studio 12.4, this definition will continue to be needed.
CXXFLAGS += -D__MATHERR_RENAME_EXCEPTION
LDFLAGS += -L$(R_LIBS_PATH) -R$(R_LIBS_PATH)

CONFIGURE_ENV += CPICFLAGS="$(studio_PIC)"
CONFIGURE_ENV += FPICFLAGS="$(studio_PIC)"
CONFIGURE_ENV += FFLAGS="$(studio_OPT) $(CC_BITS)"
CONFIGURE_ENV += FCFLAGS="$(studio_OPT) $(CC_BITS)"
CONFIGURE_ENV += FCLIBS="-lsunperf -lfsu -lsunmath"
CONFIGURE_ENV += FLIBS="-lsunperf -lfsu -lsunmath"
# Needed so that R packages using C++ code can link against the standard
# C++ libraries.
CONFIGURE_ENV += SHLIB_CXXLDFLAGS="-lCrunG3"

# Set the various Java variables otherwise it auto-detects the 32-bit ones.
CONFIGURE_ENV += JAVA_CPPFLAGS="-I$(JAVA8_HOME)/jre/../include -I$(JAVA8_HOME)/jre/../include/solaris"
CONFIGURE_ENV += JAVA_LIBS="-L$(JAVA_LIBS_PATH) -R$(JAVA_LIBS_PATH) -ljvm"

# From Brian Whitney:
# You need to define this option on SPARC, otherwise you will get quad
# arithmetic on SPARC but not on x86.  Really makes some R functions run
# very slow on SPARC (COR path).
CONFIGURE_OPTIONS.sparc +=	--disable-long-double

CONFIGURE_OPTIONS += --enable-R-shlib
CONFIGURE_OPTIONS += --with-blas='-lsunperf'
CONFIGURE_OPTIONS += --with-ICU
CONFIGURE_OPTIONS += --with-lapack
CONFIGURE_OPTIONS += --with-recommended-packages
CONFIGURE_OPTIONS += --with-tcltk
CONFIGURE_OPTIONS += --enable-prebuilt-html

# Supply Makeconf files for both the Studio and the GNU C, C++ and Fortran
# compilers.
COMPONENT_POST_INSTALL_ACTION += \
	$(MV) $(PROTOUSRLIBDIR64)/R/etc/Makeconf \
	      $(PROTOUSRLIBDIR64)/R/etc/Makeconf.Studio ; \
	$(CP) $(PROTOUSRLIBDIR64)/R/etc/Makeconf.Studio \
	      $(PROTOUSRLIBDIR64)/R/etc/Makeconf.GNU ; \
	(cd $(PROTOUSRLIBDIR64)/R/etc ; $(GPATCH) --strip=0 \
	      < $(COMPONENT_DIR)/files/Makeconf-GNU.patch) ;

COMPONENT_PRE_TEST_ACTION = \
	$(RM) $(BUILD_DIR_64)/tests/Examples/*.prev

COMPONENT_PRE_SYSTEM_TEST_ACTION = \
	$(RM) $(BUILD_DIR_64)/tests/Examples/*.prev

# Increase stack limit to allow the "infinite recursion" test to work.
COMPONENT_TEST_ENV_CMD =	ulimit -Ss 32768 ; $(ENV)
COMPONENT_SYSTEM_TEST_ENV_CMD =	ulimit -Ss 32768 ; $(ENV)

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

COMPONENT_TEST_TRANSFORMS += \
	'-n ' \
	'-e "/^Testing examples for package /p" ' \
	'-e "/^running /p" ' \
	'-e "/^  expect some differences/p" ' \
	'-e "/comparing.*datetime.Rout/d" ' \
	'-e "/comparing.*reg-examples3.Rout/d" ' \
	'-e "/^  comparing /p" '

# Use the installed version of R, not the one in the build area.
# These definitions override those found in .../test/Makefile.
COMPONENT_SYSTEM_TEST_ARGS += R="LANGUAGE=en LC_ALL=C SRCDIR=$(BUILD_DIR_64)/tests R_DEFAULT_PACKAGES= $(USRBINDIR)/R --vanilla"
COMPONENT_SYSTEM_TEST_ARGS += R2="R_DEFAULT_PACKAGES= $(USRBINDIR)/R --vanilla"
COMPONENT_SYSTEM_TEST_ARGS += R3="$(USRBINDIR)/R CMD check"
COMPONENT_SYSTEM_TEST_ARGS += RDIFF="$(USRBINDIR)/R CMD Rdiff"
COMPONENT_SYSTEM_TEST_ARGS += RDCONV="LC_CTYPE=C $(USRBINDIR)/R CMD Rdconv"

COMPONENT_TEST_ARGS =		-k -i
COMPONENT_SYSTEM_TEST_ARGS +=	-k -i

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
REQUIRED_PACKAGES += system/library/fortran-runtime
REQUIRED_PACKAGES += system/library/iconv
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/library/sunperf
REQUIRED_PACKAGES += web/curl
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxmu
REQUIRED_PACKAGES += x11/library/toolkit/libxt
