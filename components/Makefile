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
# Copyright (c) 2010, Oracle and/or it's affiliates.  All rights reserved.
#

include ../make-rules/shared-macros.mk

COMPONENT_DIRS +=	lcms
COMPONENT_DIRS +=	file
COMPONENT_DIRS +=	pycups

download:	TARGET = download
prep:		TARGET = prep
build:		TARGET = build
install:	TARGET = install
publish:	TARGET = publish
validate:	TARGET = validate
clean:		TARGET = clean
clobber:	TARGET = clobber
prep build install publish:		LOG =	>$(WS_LOGS)/$(TARGET):$@.log 2>&1

.DEFAULT:	publish

.PARALLEL:	$(COMPONENT_DIRS)

download prep build install publish validate: setup $(COMPONENT_DIRS)

clean clobber:	$(COMPONENT_DIRS)
ifeq ($(findstring file://, $(PKG_REPO)),file://)
	$(RM) -r $(PKG_REPO:file://%=%) $(WS_LOGS)
endif

setup:	$(WS_LOGS) repo tools

$(WS_LOGS):
	$(MKDIR) $@

repo:
	$(PKGSEND) -s $(PKG_REPO) create-repository \
		--set-property publisher.prefix=$(PUBLISHER)

tools:
	@cd ../tools ; echo "building tools..." ; $(GMAKE) setup

$(COMPONENT_DIRS):	FORCE
	@cd $@ ; echo "$(TARGET) \c" ; pwd ; \
	 $(GMAKE) $(TARGET) $(LOG)

FORCE:
