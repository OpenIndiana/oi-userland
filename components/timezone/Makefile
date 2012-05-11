#
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
# Copyright (c) 2005, 2012, Oracle and/or its affiliates. All rights reserved.
#
include ../../make-rules/shared-macros.mk

COMPONENT_NAME= 	timezone

HUMAN_VERSION=		2012c

# "etcetera" must be listed before "backward" because it sets up links that
# "backward" needs.
TZFILES= africa antarctica asia australasia etcetera europe \
	 factory northamerica pacificnew solar87 solar88 solar89 \
	 southamerica backward

include ../../make-rules/ips.mk

POFILE=zoneinfo.po

download:
	@echo "Nothing to download."

prep:
	@echo "Nothing to prep."

build:
	@/bin/sh ./do_pofile.sh > $(POFILE)

install: build
	/usr/sbin/zic -d $(PROTOUSRSHARELIBDIR)/zoneinfo $(TZFILES)

# empty test target
test:	$(NO_TESTS)

clean:
	$(RM) -r $(BUILD_DIR) $(POFILE)

clobber: clean

include ../../make-rules/depend.mk

