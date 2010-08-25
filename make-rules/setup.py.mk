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

$(COMPONENT_SRC)/build-%-2.6/.built:		PYTHON_VERSION=2.6
$(COMPONENT_SRC)/build-%-2.4/.built:		PYTHON_VERSION=2.4
$(COMPONENT_SRC)/build-$(MACH32)-%/.built:	BITS=32
$(COMPONENT_SRC)/build-$(MACH64)-%/.built:	BITS=64

$(COMPONENT_SRC)/build-%-2.6/.installed:	PYTHON_VERSION=2.6
$(COMPONENT_SRC)/build-%-2.4/.installed:	PYTHON_VERSION=2.4
$(COMPONENT_SRC)/build-$(MACH32)-%/.installed:	BITS=32
$(COMPONENT_SRC)/build-$(MACH64)-%/.installed:	BITS=64

BUILD_32 = $(PYTHON_VERSIONS:%=$(COMPONENT_SRC)/build-$(MACH32)-%/.built)
BUILD_64 = $(PYTHON_VERSIONS:%=$(COMPONENT_SRC)/build-$(MACH64)-%/.built)

INSTALL_32 = $(PYTHON_VERSIONS:%=$(COMPONENT_SRC)/build-$(MACH32)-%/.installed)
INSTALL_64 = $(PYTHON_VERSIONS:%=$(COMPONENT_SRC)/build-$(MACH64)-%/.installed)

# build the configured source
$(COMPONENT_SRC)/build-%/.built:	$(COMPONENT_SRC)/.prep
	$(RM) -r $(@D) ; $(MKDIR) $(@D)
	$(COMPONENT_PRE_BUILD_ACTION)
	(cd $(COMPONENT_SRC) ; $(ENV) $(PYTHON_ENV) \
		$(PYTHON.$(BITS)) ./setup.py build --build-temp $(@D:$(COMPONENT_SRC)/%=%))
	$(COMPONENT_POST_BUILD_ACTION)
	$(TOUCH) $@

# The default is site-packages, but that directory belongs to the end-user.
# Modules which are shipped by the OS but not with the core Python distribution
# belong in vendor-packages.
PYTHON_LIB= /usr/lib/python$(PYTHON_VERSION)/vendor-packages

# install the built source into a prototype area
$(COMPONENT_SRC)/build-%/.installed:	$(COMPONENT_SRC)/build-%/.built
	$(COMPONENT_PRE_INSTALL_ACTION)
	(cd $(COMPONENT_SRC) ; $(ENV) $(PYTHON_ENV) \
		$(PYTHON.$(BITS)) ./setup.py install --root $(PROTO_DIR) \
			--install-lib=$(PYTHON_LIB))
	$(COMPONENT_POST_INSTALL_ACTION)
	$(TOUCH) $@
