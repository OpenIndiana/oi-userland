#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2019 Grueninger, Grueninger GmbH, (grueni). All rights reserved. 
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= pcs
COMPONENT_VERSION= 0.9.168
COMPONENT_FMRI= application/cluster/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION= System/Shells
COMPONENT_PROJECT_URL= https://github.com/ClusterLabs/pcs
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:f1f3684978e13f2bd95a5fbd5d662a3f7b30908969addbb3559152b2791efc19
COMPONENT_ARCHIVE_URL= https://github.com/ClusterLabs/$(COMPONENT_NAME)/archive/$(COMPONENT_VERSION).tar.gz 
COMPONENT_LICENSE= GPLv2
COMPONENT_SUMMARY= Pacemaker command line interface and GUI.

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk
include $(WS_MAKE_RULES)/ruby.mk

PATH=$(PATH.gnu):/usr/ruby/$(RUBY_VERSION)/bin	

ENV += DESTDIR="$(PROTO_DIR)"
ENV += am_cv_python_pythondir=$(PYTHON_VENDOR_PACKAGES)
ENV += am_cv_python_pyexecdir=$(PYTHON_VENDOR_PACKAGES)
ENV += PYTHON_SITELIB=$(PYTHON_VENDOR_PACKAGES)
ENV += PYTHON=$(PYTHON)
ENV += PATH=$(PATH)

COMPONENT_BUILD_GMAKE_ARGS += BASH_COMPLETION_DIR=$(PROTO_DIR)/usr/share/bash-completion/completions

PKG_MACROS +=	RUBY_VERSION=$(RUBY_VERSION)
PKG_MACROS += RUBY_LIB_VERSION=$(RUBY_LIB_VERSION)

# Ugly hack to avoid fail on second install
COMPONENT_PRE_BUILD_ACTION = ($(RM) -r $(PROTO_DIR))

COMPONENT_POST_BUILD_ACTION=( \
    $(MKDIR)  $(PROTO_DIR)/usr/share/pcs/examples; \
    $(MV) $(PROTO_DIR)/etc/logrotate.d    $(PROTO_DIR)/usr/share/pcs/examples )

# pytthon installation class overwrites the shebang during installation
$(INSTALL_32):  $(BUILD_32)
		grep -q python2.7 ${PROTO_DIR}/usr/sbin/pcs || \
		gsed -i -- "s~/usr/bin/python~/usr/bin/python2.7~g" ${PROTO_DIR}/usr/sbin/pcs

# beware of: the package has a combined build + install 
build:          $(BUILD_32)

install:        $(INSTALL_32)

test:           $(TESTS_32)

# Build dependencies
REQUIRED_PACKAGES += library/ruby/bundler
REQUIRED_PACKAGES += system/font/liberation

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/libffi
REQUIRED_PACKAGES += library/python/setuptools-27
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += runtime/ruby-23
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += system/library
