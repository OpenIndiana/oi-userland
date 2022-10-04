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

# Component defaults
COMPONENT_CLASSIFICATION ?=	Development/Python
COMPONENT_SRC ?=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE ?=		$(COMPONENT_SRC).tar.gz
COMPONENT_FMRI ?=		library/python/$(shell echo $(COMPONENT_NAME) | tr [A-Z] [a-z])
COMPONENT_PROJECT_URL ?=	https://pypi.org/project/$(COMPONENT_NAME)/
COMPONENT_ARCHIVE_URL ?=	$(call pypi_url)
# Enable ASLR by default.  Component could disable ASLR by setting
# COMPONENT_ASLR to 'no'.
ifeq ($(strip $(COMPONENT_ASLR)),no)
ASLR_MODE = $(ASLR_DISABLE)
else
ASLR_MODE = $(ASLR_ENABLE)
endif
