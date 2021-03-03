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
# Copyright 2021 Gary Mills
# Copyright 2019 Grueninger, Grueninger GmbH, (grueni). All rights reserved. 
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= pcs
COMPONENT_VERSION= 0.10.1
# COMPONENT_REVISION= 0
COMPONENT_FMRI= application/cluster/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION= System/Shells
COMPONENT_PROJECT_URL= https://github.com/ClusterLabs/pcs
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:61d36fc96c05a4724b76f45216a483e514c9da5b486ba77e906ae45722592cf2
COMPONENT_ARCHIVE_URL= https://github.com/ClusterLabs/$(COMPONENT_NAME)/archive/$(COMPONENT_VERSION).tar.gz 
COMPONENT_LICENSE= GPLv2
COMPONENT_SUMMARY= Pacemaker command line interface and GUI.

#
# The build process tries to use wget to download an archive without even a
# check for the correct hash.  In order to allow the build to work without
# networking, we download it first.  This will need to be updated if the
# version or URL in "pcs/snmp/Makefile" changes.
#
PYAGENTX_VERSION= 0.4.pcs.2
COMPONENT_ARCHIVE_1= pyagentx-v$(PYAGENTX_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH_1= sha256:9aa8ec276e253ab8fffe04b786e322a1c1fe988e5e2af06fb617a43a4413d139
COMPONENT_ARCHIVE_URL_1= https://github.com/ondrejmular/pyagentx/archive/v$(PYAGENTX_VERSION).tar.gz

#
# The package includes a private copy of a series of Ruby Gems.  We must
# download these in advance so that the build can run without network access.
#
COMPONENT_ARCHIVE_2= backports-3.11.4.gem
COMPONENT_ARCHIVE_HASH_2= sha256:0ff9c1601e381e51f93fca3b9931b5e0de4ff0f359da536603fa40c1799750c3
COMPONENT_ARCHIVE_URL_2= https://rubygems.org/gems/$(COMPONENT_ARCHIVE_2)
CACHED_GEM_FILES += $(COMPONENT_ARCHIVE_2)

COMPONENT_ARCHIVE_3= ethon-0.11.0.gem
COMPONENT_ARCHIVE_HASH_3= sha256:88ec7960a8e00f76afc96ed15dcc8be0cb515f963fe3bb1d4e0b5c51f9d7e078
COMPONENT_ARCHIVE_URL_3= https://rubygems.org/gems/$(COMPONENT_ARCHIVE_3)
CACHED_GEM_FILES += $(COMPONENT_ARCHIVE_3)

COMPONENT_ARCHIVE_4= ffi-1.9.25.gem
COMPONENT_ARCHIVE_HASH_4= sha256:f854f08f08190fec772a12e863f33761d02ad3efea3c3afcdeffc8a06313f54a
COMPONENT_ARCHIVE_URL_4= https://rubygems.org/gems/$(COMPONENT_ARCHIVE_4)
CACHED_GEM_FILES += $(COMPONENT_ARCHIVE_4)

COMPONENT_ARCHIVE_5= json-2.1.0.gem
COMPONENT_ARCHIVE_HASH_5= sha256:b76fd09b881088c6c64a12721a1528f2f747a1c2ee52fab4c1f60db8af946607
COMPONENT_ARCHIVE_URL_5= https://rubygems.org/gems/$(COMPONENT_ARCHIVE_5)
CACHED_GEM_FILES += $(COMPONENT_ARCHIVE_5)

COMPONENT_ARCHIVE_6= multi_json-1.13.1.gem
COMPONENT_ARCHIVE_HASH_6= sha256:db8613c039b9501e6b2fb85efe4feabb02f55c3365bae52bba35381b89c780e6
COMPONENT_ARCHIVE_URL_6= https://rubygems.org/gems/$(COMPONENT_ARCHIVE_6)
CACHED_GEM_FILES += $(COMPONENT_ARCHIVE_6)

COMPONENT_ARCHIVE_7= mustermann-1.0.3.gem
COMPONENT_ARCHIVE_HASH_7= sha256:219ecbefebccb10778273bbd64ae468e5da30ac55f346b93700b786feb7ccc53
COMPONENT_ARCHIVE_URL_7= https://rubygems.org/gems/$(COMPONENT_ARCHIVE_7)
CACHED_GEM_FILES += $(COMPONENT_ARCHIVE_7)

COMPONENT_ARCHIVE_8= open4-1.3.4.gem
COMPONENT_ARCHIVE_HASH_8= sha256:a1df037310624ecc1ea1d81264b11c83e96d0c3c1c6043108d37d396dcd0f4b1
COMPONENT_ARCHIVE_URL_8= https://rubygems.org/gems/$(COMPONENT_ARCHIVE_8)
CACHED_GEM_FILES += $(COMPONENT_ARCHIVE_8)

COMPONENT_ARCHIVE_9= rack-2.0.6.gem
COMPONENT_ARCHIVE_HASH_9= sha256:f5874ac9c2223ecc65fcad3120c884fc2a868c1c18f548ff676a6eb21bda8fdd
COMPONENT_ARCHIVE_URL_9= https://rubygems.org/gems/$(COMPONENT_ARCHIVE_9)
CACHED_GEM_FILES += $(COMPONENT_ARCHIVE_9)

COMPONENT_ARCHIVE_10= rack-protection-2.0.4.gem
COMPONENT_ARCHIVE_HASH_10= sha256:582a96c5a1a0787f2ff4eaf2db71cdbf6183f69816e0e7bdddf6fcad32399d7a
COMPONENT_ARCHIVE_URL_10= https://rubygems.org/gems/$(COMPONENT_ARCHIVE_10)
CACHED_GEM_FILES += $(COMPONENT_ARCHIVE_10)

COMPONENT_ARCHIVE_11= rack-test-1.1.0.gem
COMPONENT_ARCHIVE_HASH_11= sha256:154161f40f162b1c009a655b7b0c5de3a3102cc6d7d2e94b64e1f46ace800866
COMPONENT_ARCHIVE_URL_11= https://rubygems.org/gems/$(COMPONENT_ARCHIVE_11)
CACHED_GEM_FILES += $(COMPONENT_ARCHIVE_11)

COMPONENT_ARCHIVE_12= sinatra-2.0.4.gem
COMPONENT_ARCHIVE_HASH_12= sha256:30a084bd2c9906eb14194e75444a2dd22adc94c64071cbee59411b843aa4bcd7
COMPONENT_ARCHIVE_URL_12= https://rubygems.org/gems/$(COMPONENT_ARCHIVE_12)
CACHED_GEM_FILES += $(COMPONENT_ARCHIVE_12)

COMPONENT_ARCHIVE_13= tilt-2.0.8.gem
COMPONENT_ARCHIVE_HASH_13= sha256:2a3be6c56a8cc6338203c02910e20e858664b633adb550e1103804d75eae4000
COMPONENT_ARCHIVE_URL_13= https://rubygems.org/gems/$(COMPONENT_ARCHIVE_13)
CACHED_GEM_FILES += $(COMPONENT_ARCHIVE_13)


include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk
include $(WS_MAKE_RULES)/ruby.mk

PATH=$(PATH.gnu):/usr/ruby/$(RUBY_VERSION)/bin	

PYTHON = /usr/bin/python3.7
PYTHON_VENDOR_PACKAGES = /usr/lib/python3.7/vendor-packages

COMPONENT_INSTALL_ENV += DESTDIR="$(PROTO_DIR)"
COMPONENT_INSTALL_ENV += am_cv_python_pythondir=$(PYTHON_VENDOR_PACKAGES)
COMPONENT_INSTALL_ENV += am_cv_python_pyexecdir=$(PYTHON_VENDOR_PACKAGES)
COMPONENT_INSTALL_ENV += PYTHON_SITELIB=$(PYTHON_VENDOR_PACKAGES)
COMPONENT_INSTALL_ENV += PYTHON=$(PYTHON)
COMPONENT_INSTALL_ENV += PATH=$(PATH)
COMPONENT_INSTALL_ENV += BASH_COMPLETION_DIR=/usr/share/bash-completion/completions

PKG_MACROS +=	RUBY_VERSION=$(RUBY_VERSION)
PKG_MACROS += RUBY_LIB_VERSION=$(RUBY_LIB_VERSION)

#
# Unpack the pyagentx source into the build directory and pass its location to
# make.  If BUNDLE_PYAGENTX_SRC_DIR is set, "Makefile" will not use wget to
# download the file.
#
# Copy cached Ruby Gems to the bundle cache directory, and set
# BUNDLE_CACHE_PATH so that "bundle install --local ..." can find them.
#
COMPONENT_PREP_ACTION += (mkdir -p $(BUILD_DIR) && cd $(BUILD_DIR) && \
    tar xfz $(USERLAND_ARCHIVES)$(COMPONENT_ARCHIVE_1) && \
    mkdir -p bundle_cache && \
    for x in $(CACHED_GEM_FILES); do \
        cp $(USERLAND_ARCHIVES)$$x bundle_cache/; \
    done)
COMPONENT_INSTALL_ENV += BUNDLE_PYAGENTX_SRC_DIR=$(BUILD_DIR)/pyagentx-$(PYAGENTX_VERSION)
COMPONENT_INSTALL_ENV += BUNDLE_CACHE_PATH=../../bundle_cache

# beware of: the package has a combined build + install 
COMPONENT_BUILD_ACTION = echo 'No build target'

build:          $(BUILD_32)

# pytthon installation class overwrites the shebang during installation
COMPONENT_POST_INSTALL_ACTION=( \
    $(MKDIR)  $(PROTO_DIR)/usr/share/pcs/examples; \
    $(MV) $(PROTO_DIR)/etc/logrotate.d $(PROTO_DIR)/usr/share/pcs/examples; \
    grep -q python3.7 ${PROTO_DIR}/usr/sbin/pcs || \
    gsed -i -- "s~/usr/bin/python~/usr/bin/python3.7~g" ${PROTO_DIR}/usr/sbin/pcs )

install:        $(INSTALL_32)

test:           $(TESTS_32)

# Build dependencies
REQUIRED_PACKAGES += library/ruby/bundler
REQUIRED_PACKAGES += system/font/truetype/liberation

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/libffi
REQUIRED_PACKAGES += library/python/setuptools-37
REQUIRED_PACKAGES += library/python/importlib-metadata-37
REQUIRED_PACKAGES += runtime/python-37
REQUIRED_PACKAGES += runtime/ruby-23
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += system/library
