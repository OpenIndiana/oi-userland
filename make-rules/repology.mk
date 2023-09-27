#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2023 Till Wegmueller
#

PKGDEV="/ws/toasty/.cargo/bin/pkgdev"

generate-pakage-kdl:
	@echo "generating package.kdl for $(COMPONENT_NAME)"
	$(PKGDEV) create $(COMPONENT_NAME)
#	@for package in $(REQUIRED_PACKAGES) ; do \
#		echo $$package ;  \
#	done | LANG=C LC_ALL=C sort -u

