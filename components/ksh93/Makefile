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
# Copyright (c) 2012, 2016, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64_and_32
include ../../make-rules/shared-macros.mk

COMPONENT_PROJECT_URL= http://www2.research.att.com/sw/download/

# These are required if retrieving packages from the AT&T website.
ATT_USERNAME= "I accept www.opensource.org/licenses/eclipse"
ATT_PASSWD= "."

COMPONENT_TEST_MASTER = \
	$(COMPONENT_TEST_RESULTS_DIR)/results-$(BITS).$(MACH).master 

COMPONENT_TEST_TRANSFORMS += \
	'-e "s|\(^$(CC)\).*|\\$$(CC)|"' \
	'-e "s|\(temporary directory\).*|\1|"' \
	'-e "1,/package: test start/d"' \
	'-e "s|\(begins\).*|\1|"' \
	'-e "s|\(passed\).*\(\[\)|\1 \2|"' \
	'-e "s|\(failed\).*\(with exit code\)|\1 \2|"' \
	'-e "s|\(package: test done\).*|\1|"'\
	'-e "/usage: sleep/d"' \
	'-e "/invalid interval/d"' \
	'-e "s|\(took\).*\(expected\)|\1 x secs \2|"' \
	'-e "s|\(expected .* sec\).*\(got\).*|\1 \2 x secs|"' \
	'-e "s|^.*\(shcomp-.*\).*|\1|"'

# This flag controls the prep.mk behaviour to patch each archive individually
PATCH_EACH_ARCHIVE = 1

COMPONENT_NAME = ksh93
COMPONENT_SRC_NAME = INIT
COMPONENT_VERSION = 2012-08-01
COMPONENT_SRC = $(COMPONENT_SRC_NAME).$(COMPONENT_VERSION)
COMPONENT_ARCHIVE =	$(COMPONENT_SRC).tgz
COMPONENT_ARCHIVE_HASH = \
    sha256:c40cf57e9b2186271a9c362a560aa4a6e25ba911a8258ab931d2bbdbce44cfe5
COMPONENT_ARCHIVE_URL = http://www2.research.att.com/~astopen/download/tgz/$(COMPONENT_ARCHIVE)

TPNO=		16530

# Patch only required if building ksh93 only and not ast-base
# package-pax-suid.patch

# The ksh93 tarballs don't unpack cleanly into their own directories.
UNPACK_ARGS= -r $(COMPONENT_SRC)

NUM_EXTRA_ARCHIVES= 1
COMPONENT_NAME_1= ast-base
COMPONENT_VERSION_1= 2012-08-01
COMPONENT_SRC_1= $(COMPONENT_NAME_1).$(COMPONENT_VERSION_1)
COMPONENT_ARCHIVE_1= $(COMPONENT_NAME_1).$(COMPONENT_VERSION_1).tgz
COMPONENT_ARCHIVE_HASH_1= \
    sha256:3bd668dbd922790f1d24c78e3522ef4816501e9cf80abf3c480f554c74f4dbac
COMPONENT_ARCHIVE_URL_1= http://www2.research.att.com/~astopen/download/tgz/$(COMPONENT_ARCHIVE_1)

# Fixup HOSTTYPE to match uname output and bits
HOSTTYPE32=sol11.$(shell uname -p)
HOSTTYPE64=sol11.$(shell uname -p)-64

# Make the unpack of the second archive relocate to a sensible place
UNPACK_ARGS_1= -r $(COMPONENT_SRC_1)

# We override LD_B_DIRECT because -B direct has unfortunate consequences for the
# interposition used by the Safe/Fast IO library (i.e. it becomes neither safe
# nor fast, and causes the build to deadly embrace). 
LD_B_DIRECT=

# Disable nmake's probing of runpaths
CC.RUNPATH=
CC.LD.RUNPATH=
CC.LD.ORIGIN=
CC.DLL.ORIGIN=

# Fix up the permissions of the compiler wrapper scripts from the patch
COMPONENT_PRE_BUILD_ACTION=($(CHMOD) +x $(@D)/src/cmd/INIT/cc.sol11.*)

# Prevent nmake from taking over the entire machine
NPROC=1

# Set the built to build all targets, install all of ast-base, and test ksh93.
COMPONENT_BUILD_TARGETS += 
COMPONENT_INSTALL_PACKAGES += ast-base
COMPONENT_TEST_TARGETS = ksh93

# Unpack the ast-base tarball and copy it into the INIT tree,
# mark it as un-patched 
COMPONENT_POST_UNPACK_ACTION_1= \
	$(RM) $(COMPONENT_SRC)/*patched_1; \
    $(CP) -r $(COMPONENT_SRC_1)/* $(COMPONENT_SRC)

# Add the two tarball paths to the paths to be cleaned
CLEAN_PATHS+= build $(COMPONENT_NAME_1).$(COMPONENT_VERSION_1) \
              $(COMPONENT_NAME).$(COMPONENT_VERSION)

# ksh.kshrc needs to be installed with the ksh package
COMPONENT_POST_INSTALL_ACTION= \
	@$(MKDIR) -p $(PROTO_DIR)/etc/; \
	$(CP) ksh.kshrc $(PROTO_DIR)/etc/ 

# Packaging information.
# Note how the AT&T "version letter symbol date" code is translated 
# into the IPS version number:
# 
# shell/ksh93@93.<letter representation>.<0 or 1>.<yymmdd>
#
# <letter representation> is the numeric place in the alphabet of the 
# major version letter.
# 
# <0 or 1> is the presence or absence of the "+" symbol in the AT&T
# version code. The "+" represents a point/bugfix release and would appear as
# "93<version letter>+" in the human readable form.
#
# EXAMPLE:
# AT&T Version string: 93u+ 2011-02-08
# IPS Version number: 93.21.1.20110208
#
IPS_PKG_NAME= ksh93
IPS_COMPONENT_VERSION= 93.21.1.20120801
HUMAN_VERSION= 93u+ 2012-08-01

# Exposes a bug in ON.
ifeq ($(BUILD_TYPE), evaluation)
BUILD_32_and_64=
INSTALL_32_and_64=
PUBLISH_STAMP=

COMPONENT_POST_INSTALL_ACTION += \
	(for binary in msgcvt msgcpp msgget msggen ksh shcomp alias; do \
		/usr/bin/elfedit -e 'dyn:delete RPATH' -e 'dyn:delete RUNPATH' \
		    "$(PROTO_DIR)/$(MACH64)/bin/$$binary" ; \
	done )
endif

BUILD_STYLE= attpackagemake
include $(WS_MAKE_RULES)/common.mk

REQUIRED_PACKAGES += system/core-os
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/library/security/crypto
