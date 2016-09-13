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
#
#   To build the test:
#   $ cd build/[64-bit directory]
#   $ gmake build-test
#
#   To run the test:
#   $ cd build/[64-bit directory]
#   $ ./testcackey> testoutput.log
#
#   If the last line of output says:
#   Testing libcackey... DONE. Status = 0
#   then you have a finished test and results.
#   Search for CK_FAIL or "failed" in testoutput.log to see the actual failures,
#   if no CK_FAIL or failed were reported, the test ran successfully.

BUILD_BITS=	64_and_32
include ../../make-rules/shared-macros.mk
 
COMPONENT_NAME=         CACKey
COMPONENT_VERSION=      0.7.4
# The new form includes the commit as a disambiguator, but the current archive
# wasn't created with that in its name, so we use the old form until the next
# update.
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=  http://www.rkeene.org/projects/info/wiki/161

COMPONENT_ARCHIVE_SRC=	git

GIT_REPO= https://github.com/Conservatory/CACKey
GIT_COMMIT_ID= 2f51a0d
GIT_HASH=  sha256:72360f032b81923bb2cfcedea7e49ac50ac477e53872840e10ee08a2014ab737

COMPONENT_BUGDB=        library/smartcard

TPNO =                  25489

include $(WS_MAKE_RULES)/common.mk

# does not use typical FOSS dir layout, source is at top level
COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D))

# requires PC/SC libraries and headers
CONFIGURE_ENV += CFLAGS="-I$(USRINCDIR)/PCSC" 
CONFIGURE_ENV += LDFLAGS="-lpcsclite"

# options needed for configure, library location, PC/SC library and headers    
CONFIGURE_OPTIONS +=    --exec-prefix=$(USRLIBDIR64)
CONFIGURE_OPTIONS +=    --with-pcsc-headers=$(USRINCDIR)/PCSC
CONFIGURE_OPTIONS +=    --enable-dod-certs-on-hw-slots

# configure.ac related patch needs configure script re-creation
COMPONENT_PREP_ACTION +=(cd $(@D); autoreconf);

# required packages  
REQUIRED_PACKAGES += library/security/pcsc/pcsclite
REQUIRED_PACKAGES += library/zlib

