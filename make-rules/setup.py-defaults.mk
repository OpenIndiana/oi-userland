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
# To support Post-releases (see PEP 440) we need to convert the 'post' part of
# the (human) version number to some numbers.  According to PEP 440 we need to
# make sure that Post-release always immediately follows the corresponding
# release and is ahead of any subsequent release.  We do so by converting word
# 'post' to sequence of zeros.
#
# Unfortunately it is not possible to create solution that would work in all
# cases, so we arbitrarily chose to use 'three dotted zeros'.
#
# Example when the 'three dotted zeros' solution won't work properly:
#
#	HUMAN_VERSION		COMPONENT_VERSION
#	1.1			1.1
#	1.2			1.2
#	1.2.post1		1.2.0.0.0.1
#	1.2.post2		1.2.0.0.0.2
#	1.2.0.0.0.0.1		1.2.0.0.0.0.1
#	1.2.0.0.0.1		1.2.0.0.0.1
#
COMPONENT_VERSION ?=		$(shell echo $(HUMAN_VERSION) | $(GSED) -e 's/post/0.0.0./')
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
