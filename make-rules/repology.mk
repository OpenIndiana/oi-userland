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
	$(PKGDEV) create $(COMPONENT_FMRI)
	@for package in $(REQUIRED_PACKAGES) ; do \
		$(PKGDEV) edit add dependency -- --dev --kind require $$package ;  \
	done
	$(PKGDEV) edit set project-name "$(COMPONENT_NAME)"
	$(PKGDEV) edit set summary "$(COMPONENT_SUMMARY)"
	$(PKGDEV) edit set classification "$(COMPONENT_CLASSIFICATION)"
	$(PKGDEV) edit set license -- "$(COMPONENT_LICENSE)" -f "$(COMPONENT_LICENSE_FILE)"
	$(PKGDEV) edit set version "$(COMPONENT_VERSION)"
	$(PKGDEV) edit set project-url "$(COMPONENT_PROJECT_URL)"
	$(PKGDEV) edit set maintainer "The OpenIndiana Maintainers"
	$(PKGDEV) edit add source archive "$(COMPONENT_ARCHIVE_URL)" "$(COMPONENT_ARCHIVE_HASH)"
	if [ -d "patches" ]; then $(PKGDEV) edit add source patch patches; fi
ifdef CONFIGURE_OPTIONS
	$(PKGDEV) edit add build configure -- --options="$(CONFIGURE_OPTIONS)" --flags="$(CONFIGURE_ENV)"
endif
