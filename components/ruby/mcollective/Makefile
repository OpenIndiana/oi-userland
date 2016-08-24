
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

#
# Copyright (c) 2016, Oracle and/or its affiliates. All rights reserved.
#
include ../../../make-rules/shared-macros.mk
include ../../../make-rules/shared-targets.mk
include ../../../make-rules/ruby.mk

RUBY_VERSION=       2.1
RUBY_LIB_VERSION=   2.1.0
RUBY_VERSIONS=      2.1.0
PATCH_EACH_ARCHIVE = 1

COMPONENT=		mcollective
COMPONENT_NAME=		marionette-collective
COMPONENT_VERSION=	2.8.8
COMPONENT_ARCHIVE= $(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:503b26cb0beeb505bf9cd2abbb8724c67bc743ffff4fbaddc321e2a4d663b133
COMPONENT_ARCHIVE_URL=	https://github.com/puppetlabs/marionette-collective/archive/$(COMPONENT_VERSION).tar.gz
COMPONENT_PROJECT_URL=  https://github.com/puppetlabs/marionette-collective
COMPONENT_BUGDB=	utility/mcollective

TPNO_FRMWK=        29321
TPNO_PKG_AGENT=    26722
TPNO_PPT_AGENT=    26719
TPNO_FCT_AGENT=    26723
TPNO_SVC_AGENT=    26724

COMPONENT_NAME_1=  mcollective-puppet-agent
VERSION_PPT_AGENT= 1.10.0
GIT_REPO_1=        https://github.com/puppetlabs/$(COMPONENT_NAME_1)
GIT_COMMIT_ID_1=   cfa4b5e4a9752f6b631f0231b25051c3c16e89d8
PKG_PROTO_DIRS +=  $(COMPONENT_NAME_1)-$(GIT_COMMIT_ID_1)

COMPONENT_NAME_2=  mcollective-package-agent
VERSION_PKG_AGENT= 4.4.0
GIT_REPO_2=        https://github.com/puppetlabs/$(COMPONENT_NAME_2)
GIT_COMMIT_ID_2=   8520f756cbe4ce8a1e0fc416ed4d79ee774bcb71
PKG_PROTO_DIRS +=  $(COMPONENT_NAME_2)-$(GIT_COMMIT_ID_2)

COMPONENT_NAME_3=  mcollective-service-agent
VERSION_SVC_AGENT= 3.3.1
GIT_REPO_3=        https://github.com/puppetlabs/$(COMPONENT_NAME_3)
GIT_COMMIT_ID_3=   75478ac81f80bfd5ebaab05fe5dc5b92d90af815
PKG_PROTO_DIRS +=  $(COMPONENT_NAME_3)-$(GIT_COMMIT_ID_3)

COMPONENT_NAME_4=  mcollective-facter-facts
VERSION_FCT_AGENT= 1.0.0
GIT_REPO_4=        https://github.com/puppetlabs/$(COMPONENT_NAME_4)
GIT_COMMIT_ID_4=   30adc0e50bc38fc261cae437e84a1b69a08fdae3
PKG_PROTO_DIRS +=  $(COMPONENT_NAME_4)-$(GIT_COMMIT_ID_4)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/install.rb.mk
include $(WS_MAKE_RULES)/ips.mk

# --mandir option not supported by mcollective install.rb
INSTALL_RB_MANDIR_OPTION =

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

COMPONENT_POST_UNPACK_ACTION_3 += \
  $(GPATCH) -d \
      $(COMPONENT_DIR)/$(COMPONENT_NAME_3)-$(GIT_COMMIT_ID_3) \
      $(GPATCH_FLAGS) \
      < patches/03-mco-service-name

# common targets
build:		$(BUILD_NO_ARCH)

install:	$(INSTALL_NO_ARCH)

test:		$(NO_TESTS)

system-test:    $(NO_TESTS)


REQUIRED_PACKAGES += runtime/ruby-21
REQUIRED_PACKAGES += system/core-os
