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
# Copyright 2022 Marcel Telka
#

#
# Component defaults
#

# Support for Post-releases (see PEP 440).
COMPONENT_VERSION ?=		$(shell echo $(HUMAN_VERSION) | $(GSED) -e 's/\.post.*//')
COMPONENT_CLASSIFICATION ?=	Development/Python
COMPONENT_SRC ?=		$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE ?=		$(COMPONENT_SRC).tar.gz
# To make the package name comparable we normalize it here by following the
# PyPA Core metadata specifications and PEP 503.
COMPONENT_FMRI ?=		library/python/$(shell echo $(COMPONENT_NAME) | tr [A-Z] [a-z] | $(GSED) -e 's/[._-]\{1,\}/-/g')
COMPONENT_PROJECT_URL ?=	https://pypi.org/project/$(COMPONENT_NAME)/
COMPONENT_ARCHIVE_URL ?=	$(call pypi_url)
COMPONENT_PYPI ?=		$(COMPONENT_NAME)
# Enable ASLR by default.  Component could disable ASLR by setting
# COMPONENT_ASLR to 'no'.
ifeq ($(strip $(COMPONENT_ASLR)),no)
ASLR_MODE = $(ASLR_DISABLE)
else
ASLR_MODE = $(ASLR_ENABLE)
endif

# By default we build Python projects for all supported Python versions
SINGLE_PYTHON_VERSION ?= no
