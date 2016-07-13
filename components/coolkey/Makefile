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
# Copyright (c) 2016, Oracle and/or its affiliates. All rights reserved.
#

# TESTING:
#   Requires physical card reader attached to USB with card inserted.
#   SCM Microsystems, model SCR3310 is what was used in-house to test.
#   The pkcs11_coolkey package, once built needs to be installed on
#   the system building and running the test. 
#
#   To build the test:
#   $ cd components/coolkey/test
#   $ gmake build-test
#
#   To run the test, as root:
#   # cd components/coolkey/test
#   # ./testcoolkey> testoutput.log
#   enter PIN at prompt and press <enter>
#
#   If the last line of output says:
#   Testing libcoolkey... DONE. Status = 0
#   then you have a finished test and results.
#   Search for "failed" in testoutput.log to see the actual failures, then
#   review any failed messages to determine if the test ran successfully or not.

BUILD_BITS= 64 
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		coolkey
COMPONENT_VERSION=	1.1.0
COMPONENT_PROJECT_URL=	http://pki.fedoraproject.org/wiki/CoolKey
COMPONENT_DOWNLOAD_URL=	http://pkgs.fedoraproject.org/repo/pkgs/$(COMPONENT_NAME)/$(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz/815a1811a46bf9b8782107c073149cbe
COMPONENT_ARCHIVE_HASH=	sha256:8448e3abb81bffc593c96b577dcfbc05b40e8684188456c31be15fae73d730f7
COMPONENT_ARCHIVE_URL=	$(COMPONENT_DOWNLOAD_URL)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	library/smartcard

TPNO =			25487

include $(WS_MAKE_RULES)/common.mk

# configuration related patch needs aclocal to be regenerated
COMPONENT_PREP_ACTION +=(cd $(@D); autoconf);

# do not add the SUNWspro area to the RUNPATH
LD_UNSET += "-R$(SPRO_VROOT)/lib/$(MACH64)"
COMPONENT_BUILD_ENV += LD_UNSET="$(LD_UNSET)"
COMPONENT_INSTALL_ENV += LD_UNSET="$(LD_UNSET)"

# requires PC/SC headers and library
CONFIGURE_ENV +=	PCSC_CFLAGS="-I$(USRINCDIR)/PCSC"
CONFIGURE_ENV +=	PCSC_LIBS="-lpcsclite"

# no dependency information exists the first time this package is built
CONFIGURE_OPTIONS +=    --disable-dependency-tracking

# required packages
REQUIRED_PACKAGES += library/security/pcsc/pcsclite
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library/c++-runtime

