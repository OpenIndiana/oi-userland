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

COMPONENT_NAME =		sccache
HUMAN_VERSION =			0.10.0
COMPONENT_SUMMARY =     Sccache is a ccache-like tool. It is used as a compiler wrapper and avoids compilation when possible. Sccache has the capability to utilize caching in remote storage environments, including various cloud storage options, or alternatively, in local storage. 
COMPONENT_ARCHIVE_HASH =	\
	sha256:77727cb9a7b4e5cbc718811053088235d19e442079f43c01b77c8adfe818b40f
COMPONENT_FMRI =		developer/sccache
COMPONENT_CLASSIFICATION =	Development/C
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	LICENSE

TEST_TARGET= $(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

# A note on the tests. It seems these tests
# depend on a very specific CI setup which we could not
# fully reverse engineer and copy
# thus some of the advanced tests are currently failing
# as a testing crate is not part of this repo.

# The sccache tests assume that rust is installed
# via rustup thus CARGO_HOME would point
# to ~/.cargo/ it the tries to hardcoded find
# $CARGO_HOME/bin/rustc to read it and find rust
# dependencies it needs to cache.
# Pointing CARGO_HOME to /usr
# works and is probably a dirty hack but this makes the
# unittests pass
COMPONENT_TEST_ENV += CARGO_HOME=/usr

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(OPENSSL_PKG)
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
