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
COMPONENT_REVISION= 1
COMPONENT_FMRI= application/cluster/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION= System/Shells
COMPONENT_PROJECT_URL= https://github.com/ClusterLabs/pcs
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:f1f3684978e13f2bd95a5fbd5d662a3f7b30908969addbb3559152b2791efc19
COMPONENT_ARCHIVE_URL= https://github.com/ClusterLabs/$(COMPONENT_NAME)/archive/$(COMPONENT_VERSION).tar.gz 
COMPONENT_LICENSE= GPLv2
COMPONENT_SUMMARY= Pacemaker command line interface and GUI.

#
# The build process tries to use wget to download an archive without even a
# check for the correct hash.  In order to allow the build to work without
# networking, we download it first.  This will need to be updated if the
# version or URL in "pcs/snmp/Makefile" changes.
#
PYAGENTX_VERSION= 0.4.pcs.1
COMPONENT_ARCHIVE_1= pyagentx-v$(PYAGENTX_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH_1= sha256:700ee61aef73f4c7af6dcf368c44d84479227112aaa535651a09665484aa30cc
COMPONENT_ARCHIVE_URL_1= https://github.com/ondrejmular/pyagentx/archive/v$(PYAGENTX_VERSION).tar.gz

#
# The package includes a private copy of a series of Ruby Gems.  We must
# download these in advance so that the build can run without network access.
#
COMPONENT_ARCHIVE_2= backports-3.11.3.gem
COMPONENT_ARCHIVE_HASH_2= sha256:57b04d4e2806c199bff3663d810db25e019cf88c42cacc0edbb36d3038d6a5ab
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

COMPONENT_ARCHIVE_7= open4-1.3.4.gem
COMPONENT_ARCHIVE_HASH_7= sha256:a1df037310624ecc1ea1d81264b11c83e96d0c3c1c6043108d37d396dcd0f4b1
COMPONENT_ARCHIVE_URL_7= https://rubygems.org/gems/$(COMPONENT_ARCHIVE_7)
CACHED_GEM_FILES += $(COMPONENT_ARCHIVE_7)

COMPONENT_ARCHIVE_8= rack-1.6.10.gem
COMPONENT_ARCHIVE_HASH_8= sha256:58e8ae09c502f219a6ad2e7f932072faf2d2b38ce6fd0251ac7ff3096c55c046
COMPONENT_ARCHIVE_URL_8= https://rubygems.org/gems/$(COMPONENT_ARCHIVE_8)
CACHED_GEM_FILES += $(COMPONENT_ARCHIVE_8)

COMPONENT_ARCHIVE_9= rack-protection-1.5.5.gem
COMPONENT_ARCHIVE_HASH_9= sha256:5a9f0d56ef96b616a242138986dc930aca76f6efa24f998e8683164538e5c057
COMPONENT_ARCHIVE_URL_9= https://rubygems.org/gems/$(COMPONENT_ARCHIVE_9)
CACHED_GEM_FILES += $(COMPONENT_ARCHIVE_9)

COMPONENT_ARCHIVE_10= rack-test-0.7.0.gem
COMPONENT_ARCHIVE_HASH_10= sha256:217421e6811faa7bd13536e93cf2f90e64112ca8110a2270100f8db7a8a4a038
COMPONENT_ARCHIVE_URL_10= https://rubygems.org/gems/$(COMPONENT_ARCHIVE_10)
CACHED_GEM_FILES += $(COMPONENT_ARCHIVE_10)

COMPONENT_ARCHIVE_11= rpam-ruby19-1.2.1.gem
COMPONENT_ARCHIVE_HASH_11= sha256:0184e4a1c51056c566b5b9228966937838a2ec24dd7aa1cf17ae9ab07857b85c
COMPONENT_ARCHIVE_URL_11= https://rubygems.org/gems/$(COMPONENT_ARCHIVE_11)
CACHED_GEM_FILES += $(COMPONENT_ARCHIVE_11)

COMPONENT_ARCHIVE_12= sinatra-1.4.8.gem
COMPONENT_ARCHIVE_HASH_12= sha256:18cb20ffabf31484b02d8606e450fbf040b52aea6147755a07718e9e0ffddd2f
COMPONENT_ARCHIVE_URL_12= https://rubygems.org/gems/$(COMPONENT_ARCHIVE_12)
CACHED_GEM_FILES += $(COMPONENT_ARCHIVE_12)

COMPONENT_ARCHIVE_13= sinatra-contrib-1.4.7.gem
COMPONENT_ARCHIVE_HASH_13= sha256:d9597918b1346c550bffe4127e54f53ad875f1eafb76afe28b4ec4c52288236e
COMPONENT_ARCHIVE_URL_13= https://rubygems.org/gems/$(COMPONENT_ARCHIVE_13)
CACHED_GEM_FILES += $(COMPONENT_ARCHIVE_13)

COMPONENT_ARCHIVE_14= tilt-2.0.8.gem
COMPONENT_ARCHIVE_HASH_14= sha256:2a3be6c56a8cc6338203c02910e20e858664b633adb550e1103804d75eae4000
COMPONENT_ARCHIVE_URL_14= https://rubygems.org/gems/$(COMPONENT_ARCHIVE_14)
CACHED_GEM_FILES += $(COMPONENT_ARCHIVE_14)


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

#
# Unpack the pyagentx source into the build directory and pass its location to
# make.  If PYAGENTX_DIR is set, "pcs/snmp/Makefile" will not use wget to
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
ENV += PYAGENTX_DIR=$(BUILD_DIR)/pyagentx-$(PYAGENTX_VERSION)
ENV += BUNDLE_CACHE_PATH=../../bundle_cache


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
REQUIRED_PACKAGES += system/font/truetype/liberation

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/libffi
REQUIRED_PACKAGES += library/python/setuptools-27
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += runtime/ruby-23
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += system/library
