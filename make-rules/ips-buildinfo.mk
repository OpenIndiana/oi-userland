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
# Copyright (c) 2010, 2016, Oracle and/or its affiliates. All rights reserved.
#


# The package branch version scheme is:
#
#       release_major.release_minor.update.SRU.platform.buildid.nightlyid
#
# where
#       update   : 0 for FCS, 1 for update 1, etc.
#       SRU      : SRU (support repository update) number for this update
#       platform : reserved for future use.
#       buildid  : the build number of the last non-zero element from above
#	nightlyid: nightly build identifier
#
# This scheme is used below.
#

#
# The Solaris Update number. This will be set by the gatekeepers.
# The value must match the update number of the release.
#
UPDATENUM ?= 0

#
# Support Respository Update number. This is here to reserve space within the
# version string. Typically it should not be set unless all the packages
# are being delivered within an SRU.
#
SRUNUM ?= 0

#
# Platform number. This is here to reserve space within the version
# string. It should not be set unless there is a specific need to
# release a platform update while the Solaris Update is being built.
#
PLATNUM ?= 0

#
# Build Identifier. Used to indicate which build (or respin for
# the development build) of the Solaris Update is being built.
# This is set by the gatekeepers.
#
BUILDID ?= 108

# Each (nightly) build of the code that produces packages needs to
# be uniquely identified so that packages produced by different
# builds can't be mixed.  Mixing packages from different builds can
# easily result in broken global and nonglobal zones. Or at least
# that's the case in ON, which this is copied from. We keep it simple,
# though you could use something like this if you want:
#
#NIGHTLYID ?= $(shell hg tip --template '{rev}\n')
#
NIGHTLYID ?= 1

#
# Branch Identifier.  Used in the version section of the package name to
# identify the operating system branch that the package was produced for.
#
BRANCHID ?= \
    $(PKG_SOLARIS_VERSION).$(UPDATENUM).$(SRUNUM).$(PLATNUM).$(BUILDID).$(NIGHTLYID)

#
# Build Version.  Used in the version section of the package name to identify
# the operating system version and branch that the package was produced for.
#
BUILD_VERSION ?=  $(PKG_SOLARIS_VERSION)-$(BRANCHID)

# Set a default reference repository against which pkglint is run, in case it
# hasn't been set in the environment.
ifeq ($(BUILD_TYPE),evaluation)
CANONICAL_REPO ?=		http://ipkg.us.oracle.com/solaris11/release/
else
CANONICAL_REPO ?=		http://ipkg.us.oracle.com/solaris12/minidev/
endif
