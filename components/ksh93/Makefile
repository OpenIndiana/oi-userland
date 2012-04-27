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
# Copyright (c) 2012, Oracle and/or its affiliates. All rights reserved.
#
PARFAIT_BUILD=no

include ../../make-rules/shared-macros.mk

COMPONENT_PROJECT_URL= http://www2.research.att.com/sw/download/

# These are required if retrieving packages from the AT&T website.
ATT_USERNAME= "I accept www.opensource.org/licenses/cpl"
ATT_PASSWD= "."

# This flag controls the prep.mk behaviour to patch each archive individually
PATCH_EACH_ARCHIVE = 1

COMPONENT_NAME = INIT
COMPONENT_VERSION = 2011-02-08
COMPONENT_SRC = $(COMPONENT_NAME).$(COMPONENT_VERSION)
COMPONENT_ARCHIVE =	$(COMPONENT_NAME).$(COMPONENT_VERSION).tgz
COMPONENT_ARCHIVE_HASH = \
    sha256:d692d476fe4bb933e7b6459c0cc99a2e9f428bfd81a495ed4201ec197e070f57
COMPONENT_ARCHIVE_URL = http://www2.research.att.com/~gsf/download/tgz/$(COMPONENT_ARCHIVE) 
COMPONENT_PATCHES = 

# Patch only required if building ksh93 only and not ast-base
# package-pax-suid.patch

# The ksh93 tarballs don't unpack cleanly into their own directories.
UNPACK_ARGS= -r $(COMPONENT_SRC)

NUM_EXTRA_ARCHIVES= 1
COMPONENT_NAME_1= ast-base
COMPONENT_VERSION_1= 2011-02-08
COMPONENT_SRC_1= $(COMPONENT_NAME_1).$(COMPONENT_VERSION_1)
COMPONENT_ARCHIVE_1= $(COMPONENT_NAME_1).$(COMPONENT_VERSION_1).tgz
COMPONENT_ARCHIVE_HASH_1= \
    sha256:44ae3913e6c0c8992c6c3cba16864fd4c4a18c6da8e7d87c85a23060cea7cd1a
COMPONENT_ARCHIVE_URL_1= http://www2.research.att.com/~gsf/download/tgz/$(COMPONENT_ARCHIVE_1)
COMPONENT_PATCHES_1= solaris_alias.patch build_cflags.patch path_utmp.patch \
					 CR6919590.patch CR7032821.patch CR7071431.patch \
					 CR6964621.patch CR7036535.patch \
					 CRXXX_Error_Catalog.patch CR7025778.patch \
					 CR7065478.patch CR7026179.patch \
					 CR7065900.patch CR7110983.patch \
					 CR7105086.patch disable_dll.patch \
					 CR7057565.patch

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

# Prevent nmake from taking over the entire machine
NPROCS=1

# Set the built to build all targets, install all of ast-base, and test ksh93.
COMPONENT_BUILD_TARGETS += 
COMPONENT_INSTALL_PACKAGES += ast-base
COMPONENT_TEST_TARGETS += ksh93

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

# Packaging information
IPS_PKG_NAME= ksh93
IPS_COMPONENT_VERSION= 20110208

# common targets
build:		$(BUILD_32_and_64)
	
install:	$(INSTALL_32_and_64)	
		
test:		$(TEST_32_and_64)

BUILD_PKG_DEPENDENCIES= $(BUILD_TOOLS)

PKG_PROTO_DIRS +=   $(COMPONENT_DIR)/files

include ../../make-rules/prep.mk
include ../../make-rules/attpackagemake.mk
include ../../make-rules/ips.mk
include ../../make-rules/depend.mk
