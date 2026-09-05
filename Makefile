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
# Copyright (c) 2010, 2013, Oracle and/or its affiliates. All rights reserved.
#

include make-rules/shared-macros.mk

SUBDIRS += components

download:	TARGET = download
prep:		TARGET = prep
build:		TARGET = build
install:	TARGET = install
publish:	TARGET = publish
pre-publish:	TARGET = pre-publish
validate:	TARGET = validate
clean:		TARGET = clean
clobber:	TARGET = clobber
setup:		TARGET = setup
test:		TARGET = test
component-hook:		TARGET = component-hook
generate-package-kdl:	TARGET = generate-package-kdl

.DEFAULT:	publish

download prep build install pre-publish publish validate clean clobber test component-hook generate-package-kdl unpack patch: $(SUBDIRS)

$(SUBDIRS):	FORCE
	@+echo "$(TARGET) $@" ; $(GMAKE) -s -C $@ $(TARGET)

FORCE:

# Bootstrap pkgdev before running component setup
setup: bootstrap-pkgdev $(SUBDIRS)

bootstrap-pkgdev:
	@echo "Bootstrapping pkgdev via cargo from toasterson/forge"
	cargo install --git https://github.com/toasterson/forge pkgdev

update-pkgdev:
	@echo "Updating pkgdev via cargo from toasterson/forge"
	cargo install --git https://github.com/toasterson/forge pkgdev --force

# Generate repology metadata using pkgdev
.PHONY: repology
repology: bootstrap-pkgdev
	@echo "Generating repology metadata with pkgdev"
	pkgdev generate --output=repology-metadata.json repology

# Clean generated package.kdl files and missing-metadata list
.PHONY: clean-package-kdl
clean-package-kdl:
	@echo "Cleaning generated package.kdl files and components.missing-metadata"
	@/usr/bin/find components -type f -name package.kdl -exec rm -f {} +
	@rm -f $(WS_TOP)/components.missing-metadata components.missing-metadata
