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
# Copyright 2025 Till Wegmueller
#

BUILD_STYLE = cargo

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		bat
HUMAN_VERSION =			0.25.0
COMPONENT_SUMMARY =     A cat(1) clone with wings. 
COMPONENT_ARCHIVE_HASH =	\
	sha256:2ab792c2ad113a666f08856c88cdec0a62d732559b1f3982eedf0142571e669a
COMPONENT_FMRI =		utilities/bat
COMPONENT_CLASSIFICATION =	Applications/System Utilities
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	LICENSE-APACHE

include $(WS_MAKE_RULES)/common.mk

# This line is needed to instruct the rust
# oniguruma wrappers to use the system provided oniguruma
# library and not the vendored shared library.
# The Vendored oniguruma library does not compile.
CARGO_ENV += RUSTONIG_DYNAMIC_LIBONIG=1

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += text/oniguruma
