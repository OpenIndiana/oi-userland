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

#
# Copyright (c) 2012, 2017, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		boto
COMPONENT_VERSION=	2.40.0
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:e12d5fca11fcabfd0acd18f78651e0f0dba60f958a0520ff4e9b73e35cd9928f
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_PROJECT_URL=	http://github.com/boto/boto/
COMPONENT_BUGDB=	python-mod/boto
COMPONENT_ANITYA_ID=	11794

TPNO=			29473

# Syntax issues: not Python 3 ready.
PYTHON_VERSIONS=	$(PYTHON2_VERSIONS)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

COMPONENT_POST_INSTALL_ACTION= \
    (cd $(PROTO_DIR)/usr/demo/$(COMPONENT_NAME) ; \
     $(MV) -f asadmin asadmin-$(PYTHON_VERSION) ; \
     $(MV) -f bundle_image bundle_image-$(PYTHON_VERSION) ; \
     $(MV) -f cfadmin cfadmin-$(PYTHON_VERSION) ; \
     $(MV) -f cq cq-$(PYTHON_VERSION) ; \
     $(MV) -f cwutil cwutil-$(PYTHON_VERSION) ; \
     $(MV) -f dynamodb_dump dynamodb_dump-$(PYTHON_VERSION) ; \
     $(MV) -f dynamodb_load dynamodb_load-$(PYTHON_VERSION) ; \
     $(MV) -f elbadmin elbadmin-$(PYTHON_VERSION) ; \
     $(MV) -f fetch_file fetch_file-$(PYTHON_VERSION) ; \
     $(MV) -f glacier glacier-$(PYTHON_VERSION) ; \
     $(MV) -f instance_events instance_events-$(PYTHON_VERSION) ; \
     $(MV) -f kill_instance kill_instance-$(PYTHON_VERSION) ; \
     $(MV) -f launch_instance launch_instance-$(PYTHON_VERSION) ; \
     $(MV) -f list_instances list_instances-$(PYTHON_VERSION) ; \
     $(MV) -f lss3 lss3-$(PYTHON_VERSION) ; \
     $(MV) -f mturk mturk-$(PYTHON_VERSION) ; \
     $(MV) -f pyami_sendmail pyami_sendmail-$(PYTHON_VERSION) ; \
     $(MV) -f route53 route53-$(PYTHON_VERSION) ; \
     $(MV) -f s3put s3put-$(PYTHON_VERSION) ; \
     $(MV) -f sdbadmin sdbadmin-$(PYTHON_VERSION) ; \
     $(MV) -f taskadmin taskadmin-$(PYTHON_VERSION))

COMPONENT_INSTALL_ARGS +=	--install-script=/usr/demo/$(COMPONENT_NAME)

# common targets
build:		$(BUILD_NO_ARCH)

install:	$(INSTALL_NO_ARCH)

# Tests require access to AWS/OpenStack metadata service & the Internet
test:		$(NO_TESTS)

system-test:	$(NO_TESTS)

REQUIRED_PACKAGES += library/python/filechunkio-27
