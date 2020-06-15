#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2020 Aurelien Larcher
#

-include ../../make-rules/shared-macros.mk

PYVER=$(strip $(filter $(VERSION),$(PYTHON_ALL_VERSIONS)))
ifeq ($(PYVER),)
$(error Invalid version $(PYVER))
endif
PYV=$(subst .,,$(PYVER))

print-dependents:
	@$(GMAKE) -s print-dependents -C $(WS_COMPONENTS) FMRI=runtime/python-$(PYV) | sort -u

# Deprecation of Python version PYVER
#
# For each dependent component:
#   - remove PYVER from PYTHON_VERSIONS in the Makefile
#   - bump COMPONENT_REVISION
#   - add the FMRI to history
#
deprecate-modules:
	@$(WS_TOOLS)/userland-deprecate --workspace=$(WS_TOP) --type python --version $(PYVER)
