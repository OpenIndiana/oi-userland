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
# Copyright (c) 2013, 2017, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk
include ../../../make-rules/shared-targets.mk

COMPONENT_NAME=		horizon
COMPONENT_CODENAME=	mitaka
COMPONENT_VERSION=	9.1.0
COMPONENT_BE_VERSION=	2016.1
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:bf06eda4d9a8a25e576c381baa93dafd48453287ad15d8e91ffde59f43a35830
COMPONENT_ARCHIVE_URL=	\
    https://tarballs.openstack.org/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_SIG_URL=	$(COMPONENT_ARCHIVE_URL).asc
COMPONENT_PROJECT_URL=	http://www.openstack.org/
COMPONENT_BUGDB=	service/horizon

TPNO_HORIZON=			30356
TPNO_ANGULAR=			21640
TPNO_ANGULAR_BOOTSTRAP=		23154
TPNO_ANGULAR_GETTEXT=		27199
TPNO_ANGULAR_LR_DND=		23155
TPNO_BOOTSTRAP_DP=		20670
TPNO_BOOTSTRAP_SCSS=		20671
TPNO_BOOTSWATCH=		27202
TPNO_D3=			20822
TPNO_FONT_AWESOME=		25763
TPNO_HOGAN=			21827
TPNO_IRONIC_UI=			31179
TPNO_JQUERY=			21642
TPNO_JQUERY_MIGRATE=		13315
TPNO_JQUERY_QUICKSEARCH=	20396
TPNO_JQUERY_TABLESORTER=	20824
TPNO_JQUERY_UI=			18416
TPNO_JSENCRYPT=			20397
TPNO_MDI=			30294
TPNO_RICKSHAW=			20673
TPNO_ROBOTO_FF=			27203
TPNO_SMART_TABLE=		23157
TPNO_SPIN=			20674
TPNO_TERM_JS=			23158

#
# Starting with Juno, Horizon depends on a number of XStatic modules
# to deliver the required JavaScript modules.  This delivery method
# may be changing in future releases, so the XStatic modules for now
# are built as part of Horizon rather than being stand alone
# components/packages.
#
# XStatic itself is only used during the build process and so while it
# is downloaded and installed in the proto area, none of its
# components are delivered in the Horizon package itself.
#
COMPONENT_NAME_1 =	XStatic
COMPONENT_VERSION_1 =	1.0.1
COMPONENT_SRC_1 =	XStatic-$(COMPONENT_VERSION_1)
COMPONENT_ARCHIVE_1 =	$(COMPONENT_SRC_1).tar.gz
COMPONENT_ARCHIVE_HASH_1 = \
    sha256:0ec93d7c66ebb9e0d31b664753437dc8634cb66e13310cb47c9eb1e0bc66d726
COMPONENT_ARCHIVE_URL_1 = $(call pypi_url,1)

COMPONENT_NAME_2 =	XStatic-Angular
COMPONENT_VERSION_2 =	1.3.7.0
COMPONENT_SRC_2 =	XStatic-Angular-$(COMPONENT_VERSION_2)
COMPONENT_ARCHIVE_2 =	$(COMPONENT_SRC_2).tar.gz
COMPONENT_ARCHIVE_HASH_2 = \
    sha256:7cad216b226399cbe8d2909ed5b9f28d724907b9c9e1e078e6e25d320a3d5dd7
COMPONENT_ARCHIVE_URL_2 = $(call pypi_url,2)
PKG_MACROS +=		VERSION_ANGULAR=$(basename $(COMPONENT_VERSION_2))

COMPONENT_NAME_3 =	XStatic-Bootstrap-Datepicker
COMPONENT_VERSION_3 =	1.3.1.0
COMPONENT_SRC_3 =	XStatic-Bootstrap-Datepicker-$(COMPONENT_VERSION_3)
COMPONENT_ARCHIVE_3 =	$(COMPONENT_SRC_3).tar.gz
COMPONENT_ARCHIVE_HASH_3 = \
    sha256:9edc9b77501001fcee9fbf4bf0a722c263efd928ef928b40081a8269fdd9a944
COMPONENT_ARCHIVE_URL_3 = $(call pypi_url,3)
PKG_MACROS +=		VERSION_BOOTSTRAP_DP=$(basename $(COMPONENT_VERSION_3))

COMPONENT_NAME_4 =	XStatic-Bootstrap-SCSS
COMPONENT_VERSION_4 =	3.2.0.0
COMPONENT_SRC_4 =	XStatic-Bootstrap-SCSS-$(COMPONENT_VERSION_4)
COMPONENT_ARCHIVE_4 =	$(COMPONENT_SRC_4).tar.gz
COMPONENT_ARCHIVE_HASH_4 = \
    sha256:7e9858737e2e6aac921ec7a3fca627e522901c3061611e154ebc0b8a892c7018
COMPONENT_ARCHIVE_URL_4 = $(call pypi_url,4)
PKG_MACROS +=		VERSION_BOOTSTRAP_SCSS=$(basename $(COMPONENT_VERSION_4))

COMPONENT_NAME_5 =	XStatic-D3
COMPONENT_VERSION_5 =		3.1.6.2
COMPONENT_SRC_5 =	XStatic-D3-$(COMPONENT_VERSION_5)
COMPONENT_ARCHIVE_5 =	$(COMPONENT_SRC_5).tar.gz
COMPONENT_ARCHIVE_HASH_5 = \
    sha256:46fe521f8dad99f5e20f6702180510c37b81d11f1d78119d308fcec31381f90e
COMPONENT_ARCHIVE_URL_5 = $(call pypi_url,5)
PKG_MACROS +=		VERSION_D3=$(basename $(COMPONENT_VERSION_5))

COMPONENT_NAME_6 =	XStatic-Font-Awesome
COMPONENT_VERSION_6 =	4.3.0.0
COMPONENT_SRC_6 =	XStatic-Font-Awesome-$(COMPONENT_VERSION_6)
COMPONENT_ARCHIVE_6 =	$(COMPONENT_SRC_6).tar.gz
COMPONENT_ARCHIVE_HASH_6 = \
    sha256:d2c0548990a22744ad20013e1d095de8ba1ea56b1878d8393a721205b03885c3
COMPONENT_ARCHIVE_URL_6 = $(call pypi_url,6)
PKG_MACROS +=		VERSION_FONT_AWESOME=$(basename $(COMPONENT_VERSION_6))

COMPONENT_NAME_7 =	XStatic-Hogan
COMPONENT_VERSION_7 =	2.0.0.2
COMPONENT_SRC_7 =	XStatic-Hogan-$(COMPONENT_VERSION_7)
COMPONENT_ARCHIVE_7 =	$(COMPONENT_SRC_7).tar.gz
COMPONENT_ARCHIVE_HASH_7 = \
    sha256:5941bc7fb2a09916b8837848e6fc2a13b2dfc271811e9b522c61e1337d5fc2bd
COMPONENT_ARCHIVE_URL_7 = $(call pypi_url,7)
PKG_MACROS +=		VERSION_HOGAN=$(basename $(COMPONENT_VERSION_7))

COMPONENT_NAME_8 =	XStatic-jQuery
COMPONENT_VERSION_8 =	1.10.2.1
COMPONENT_SRC_8 =	XStatic-jQuery-$(COMPONENT_VERSION_8)
COMPONENT_ARCHIVE_8 =	$(COMPONENT_SRC_8).tar.gz
COMPONENT_ARCHIVE_HASH_8 = \
    sha256:83416a6bb86e8534858c4d1ddca45e881c87639da6f78000c28c3a193fe91305
COMPONENT_ARCHIVE_URL_8 = $(call pypi_url,8)
PKG_MACROS +=		VERSION_JQUERY=$(basename $(COMPONENT_VERSION_8))

COMPONENT_NAME_9 =	XStatic-JQuery-Migrate
COMPONENT_VERSION_9 =	1.2.1.1
COMPONENT_SRC_9 =	XStatic-JQuery-Migrate-$(COMPONENT_VERSION_9)
COMPONENT_ARCHIVE_9 =	$(COMPONENT_SRC_9).tar.gz
COMPONENT_ARCHIVE_HASH_9 = \
    sha256:e2959b3df49afdddb00d36b74cca727a91b994b9f4edb993d7264731a750900e
COMPONENT_ARCHIVE_URL_9 = $(call pypi_url,9)
PKG_MACROS +=		VERSION_JQUERY_MIGRATE=$(basename $(COMPONENT_VERSION_9))

COMPONENT_NAME_10 =	XStatic-jquery-ui
COMPONENT_VERSION_10 =	1.11.0.1
COMPONENT_SRC_10 =	XStatic-jquery-ui-$(COMPONENT_VERSION_10)
COMPONENT_ARCHIVE_10 =	$(COMPONENT_SRC_10).tar.gz
COMPONENT_ARCHIVE_HASH_10 = \
    sha256:099b1836eb0d91b8dc98f5b8a6b856a2631d43af0d47f33ef90ee72ed37bda58
COMPONENT_ARCHIVE_URL_10 = $(call pypi_url,10)
PKG_MACROS +=		VERSION_JQUERY_UI=$(basename $(COMPONENT_VERSION_10))

COMPONENT_NAME_11 =	XStatic-JQuery.quicksearch
COMPONENT_VERSION_11 =	2.0.3.1
COMPONENT_SRC_11 =	XStatic-JQuery.quicksearch-$(COMPONENT_VERSION_11)
COMPONENT_ARCHIVE_11 =	$(COMPONENT_SRC_11).tar.gz
COMPONENT_ARCHIVE_HASH_11 = \
    sha256:1271571b420417add56c274fd935e81bfc79e0d54a03559d6ba5ef369f358477
COMPONENT_ARCHIVE_URL_11 = $(call pypi_url,11)
PKG_MACROS +=		VERSION_JQUERY_QS=$(basename $(COMPONENT_VERSION_11))

COMPONENT_NAME_12 =	XStatic-JQuery.TableSorter
COMPONENT_VERSION_12 =	2.14.5.1
COMPONENT_SRC_12 =	XStatic-JQuery.TableSorter-$(COMPONENT_VERSION_12)
COMPONENT_ARCHIVE_12 =	$(COMPONENT_SRC_12).tar.gz
COMPONENT_ARCHIVE_HASH_12 = \
    sha256:3ba24aecd9a3dc71a79dd4096fa5a8a041c3a7b892c61d05e6e46de0605070f0
COMPONENT_ARCHIVE_URL_12 = $(call pypi_url,12)
PKG_MACROS +=		VERSION_JQUERY_TS=$(basename $(COMPONENT_VERSION_12))

COMPONENT_NAME_13 =	XStatic-JSEncrypt
COMPONENT_VERSION_13 =	2.0.0.2
COMPONENT_SRC_13 =	XStatic-JSEncrypt-$(COMPONENT_VERSION_13)
COMPONENT_ARCHIVE_13 =	$(COMPONENT_SRC_13).tar.gz
COMPONENT_ARCHIVE_HASH_13 = \
    sha256:5852892afc6f80c7848f4110b6dad190a54aeb908271d67aaeae9d966f4a26b5
COMPONENT_ARCHIVE_URL_13 = $(call pypi_url,13)
PKG_MACROS +=		VERSION_JSENCRYPT=$(basename $(COMPONENT_VERSION_13))

COMPONENT_NAME_14 =	XStatic-Rickshaw
COMPONENT_VERSION_14 =	1.5.0.0
COMPONENT_SRC_14 =	XStatic-Rickshaw-$(COMPONENT_VERSION_14)
COMPONENT_ARCHIVE_14 =	$(COMPONENT_SRC_14).tar.gz
COMPONENT_ARCHIVE_HASH_14 = \
    sha256:147574228757254442700a9eea5150f14acb1224ef0612f896b663ab58406de8
COMPONENT_ARCHIVE_URL_14 = $(call pypi_url,14)
PKG_MACROS +=		VERSION_RICKSHAW=$(basename $(COMPONENT_VERSION_14))

COMPONENT_NAME_15 =	XStatic-Spin
COMPONENT_VERSION_15 =	1.2.5.2
COMPONENT_SRC_15 =	XStatic-Spin-$(COMPONENT_VERSION_15)
COMPONENT_ARCHIVE_15 =	$(COMPONENT_SRC_15).tar.gz
COMPONENT_ARCHIVE_HASH_15 = \
    sha256:7f46ef0e45e047019ba6eda22c432fb96f681b97bbe7f1749aa9209e07727192
COMPONENT_ARCHIVE_URL_15 = $(call pypi_url,15)
PKG_MACROS +=		VERSION_SPIN=$(basename $(COMPONENT_VERSION_15))

COMPONENT_NAME_16 =	XStatic-Angular-lrdragndrop
COMPONENT_VERSION_16 =	1.0.2.2
COMPONENT_SRC_16 =	XStatic-Angular-lrdragndrop-$(COMPONENT_VERSION_16)
COMPONENT_ARCHIVE_16 =	$(COMPONENT_SRC_16).tar.gz
COMPONENT_ARCHIVE_HASH_16 = \
    sha256:1cf04495981db5dfd5536441e17ec69bb18d624f847ddc203f3259d81b10a77e
COMPONENT_ARCHIVE_URL_16 = $(call pypi_url,16)
PKG_MACROS +=		VERSION_LR_DND=$(basename $(COMPONENT_VERSION_16))

COMPONENT_NAME_18 =	XStatic-smart-table
COMPONENT_VERSION_18 =	1.4.5.3
COMPONENT_SRC_18 =	XStatic-smart-table-$(COMPONENT_VERSION_18)
COMPONENT_ARCHIVE_18 =	$(COMPONENT_SRC_18).tar.gz
COMPONENT_ARCHIVE_HASH_18 = \
    sha256:573bdff0b1ec88dd81b7f92c1b46fda4dd1b92cde94817837d61e62c9b20a8b6
COMPONENT_ARCHIVE_URL_18 = $(call pypi_url,18)
PKG_MACROS +=		VERSION_SMART_TABLE=$(basename $(COMPONENT_VERSION_18))

COMPONENT_NAME_19 =	XStatic-term.js
COMPONENT_VERSION_19 =	0.0.4.2
COMPONENT_SRC_19 =	XStatic-term.js-$(COMPONENT_VERSION_19)
COMPONENT_ARCHIVE_19 =	$(COMPONENT_SRC_19).tar.gz
COMPONENT_ARCHIVE_HASH_19 = \
    sha256:1ed5c1cd4de60d6f290a032bfc7cdc4261d8d36cb7788b2b0a610551bbda15ec
COMPONENT_ARCHIVE_URL_19 = $(call pypi_url,19)
PKG_MACROS +=		VERSION_TERM_JS=$(basename $(COMPONENT_VERSION_19))

COMPONENT_NAME_20 =	XStatic-Angular-Bootstrap
COMPONENT_VERSION_20 =	0.11.0.2
COMPONENT_SRC_20 =	XStatic-Angular-Bootstrap-$(COMPONENT_VERSION_20)
COMPONENT_ARCHIVE_20 =	$(COMPONENT_SRC_20).tar.gz
COMPONENT_ARCHIVE_HASH_20 = \
    sha256:cbe428bf04c000460776b521f6ace0455e9f3f20135499e9aa2f4af693dc7b3e
COMPONENT_ARCHIVE_URL_20 = $(call pypi_url,20)
PKG_MACROS +=		VERSION_ANGULAR_BS=$(basename $(COMPONENT_VERSION_20))

COMPONENT_NAME_21 =	XStatic-Angular-Gettext
COMPONENT_VERSION_21 =	2.1.0.2
COMPONENT_SRC_21 =	XStatic-Angular-Gettext-$(COMPONENT_VERSION_21)
COMPONENT_ARCHIVE_21 =	$(COMPONENT_SRC_21).tar.gz
COMPONENT_ARCHIVE_HASH_21 = \
    sha256:c0745f433bb2f87d8222cdd65690c9089f5128c736309c3bc8d689aec39fa493
COMPONENT_ARCHIVE_URL_21 = $(call pypi_url,21)
COMPONENT_ANITYA_ID_21=	7295
PKG_MACROS +=		VERSION_ANGULAR_GT=$(basename $(COMPONENT_VERSION_21))

COMPONENT_NAME_22 =	XStatic-bootswatch
COMPONENT_VERSION_22 =	3.3.5.3
COMPONENT_SRC_22 =	XStatic-bootswatch-$(COMPONENT_VERSION_22)
COMPONENT_ARCHIVE_22 =	$(COMPONENT_SRC_22).tar.gz
COMPONENT_ARCHIVE_HASH_22 = \
    sha256:3c018cb0fdf591a520b2832a4ba8d8face633c765f29f9ccca8275b47be8aa94
COMPONENT_ARCHIVE_URL_22 = $(call pypi_url,22)
COMPONENT_ANITYA_ID_22=	7847
PKG_MACROS +=		VERSION_BOOTSWATCH=$(basename $(COMPONENT_VERSION_22))

COMPONENT_NAME_23 =	XStatic-mdi
COMPONENT_VERSION_23 =		1.1.70.1
COMPONENT_SRC_23 =	XStatic-mdi-$(COMPONENT_VERSION_23)
COMPONENT_ARCHIVE_23 =	$(COMPONENT_SRC_23).tar.gz
COMPONENT_ARCHIVE_HASH_23 = \
    sha256:39f177ca42baa074a13ce256a24191248c353fbf0754c0dcbf429f34ad0fd903
COMPONENT_ARCHIVE_URL_23 = $(call pypi_url,23)
COMPONENT_ANITYA_ID_23=	7846
PKG_MACROS +=		VERSION_MDI=$(COMPONENT_VERSION_23)

COMPONENT_NAME_24 =	XStatic-roboto-fontface
COMPONENT_VERSION_24 =	0.4.3.2
COMPONENT_SRC_24 =	XStatic-roboto-fontface-$(COMPONENT_VERSION_24)
COMPONENT_ARCHIVE_24 =	$(COMPONENT_SRC_24).tar.gz
COMPONENT_ARCHIVE_HASH_24 = \
    sha256:e539aa991300d8ee09ee557d3cab1066237806e365ceaf868084777379e307a5
COMPONENT_ARCHIVE_URL_24 = $(call pypi_url,24)
PKG_MACROS +=		VERSION_ROBOTO_FF=$(basename $(COMPONENT_VERSION_24))

COMPONENT_NAME_25 =		ironic-ui
COMPONENT_VERSION_25 =	1.1.2
COMPONENT_SRC_25 =		ironic-ui-$(COMPONENT_VERSION_25)
COMPONENT_ARCHIVE_25 =	ironic-ui-$(COMPONENT_VERSION_25).tar.gz
COMPONENT_ARCHIVE_HASH_25 =	\
    sha256:4db1d1516b1fde1b917cb8a87a877d3e470e8159a84ad0dc989ec4e71f17a7fd
COMPONENT_ARCHIVE_URL_25 = $(call pypi_url,25)
PKG_MACROS +=		VERSION_IRONIC_UI=$(COMPONENT_VERSION_25)

PKG_VARS +=		COMPONENT_BE_VERSION

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
# OpenStack Mitaka requires OVS and RAD changes not present in 11.3
BUILD_BITS=NO_ARCH
include $(WS_MAKE_RULES)/no-evaluation.mk
include $(WS_MAKE_RULES)/ips.mk

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

# Since this is an app, and doesn't provide any public library interfaces, we
# only need to deliver one version.  The manifest is parameterized, though.
PYTHON_VERSIONS=	2.7

PKG_MACROS +=		PYVER=$(PYTHON_VERSIONS)
PKG_MACROS +=		PYV=$(shell echo $(PYTHON_VERSIONS) | tr -d .)

PROTO_PYTHON_LIB =	$(PROTO_DIR)$(PYTHON_LIB)

# Copy the Oracle branding files, Django app customizations, and
# Horizon SMF service components into place
COMPONENT_POST_INSTALL_ACTION += \
    ($(MKDIR) $(PROTO_PYTHON_LIB)/openstack_dashboard/static/dashboard/css; \
     $(CP) files/branding/css/* \
	 $(PROTO_PYTHON_LIB)/openstack_dashboard/static/dashboard/css; \
     $(CP) files/branding/img/* \
	 $(PROTO_PYTHON_LIB)/openstack_dashboard/static/dashboard/img; \
     $(MKDIR) $(PROTO_PYTHON_LIB)/openstack_dashboard/templates/solaris; \
     $(CP) files/branding/theme/_stylesheets.html \
	 $(PROTO_PYTHON_LIB)/openstack_dashboard/templates/solaris; \
     $(CP) files/overrides.py $(PROTO_PYTHON_LIB)/openstack_dashboard; \
     $(MKDIR) $(PROTO_DIR)/lib/svc/manifest/application/openstack; \
     $(CP) \
	 files/horizon.xml \
	 files/horizon-upgrade.xml \
	 $(PROTO_DIR)/lib/svc/manifest/application/openstack);

# Generate .pyc files for the files in the proto directory
COMPONENT_POST_INSTALL_ACTION += \
    $(PYTHON) -m compileall $(PROTO_PYTHON_LIB);

# Collect the JavaScript files and compress the static assets
COMPONENT_POST_INSTALL_ACTION += \
    (set -e; \
     $(CP) $(SOURCE_DIR)/manage.py $(PROTO_PYTHON_LIB)/openstack_dashboard; \
     $(TOUCH) $(PROTO_PYTHON_LIB)/xstatic/__init__.py; \
     $(TOUCH) $(PROTO_PYTHON_LIB)/xstatic/pkg/__init__.py; \
     cd $(PROTO_PYTHON_LIB)/openstack_dashboard; \
     $(CP) $(COMPONENT_DIR)/files/local_settings_static.py \
	 local/local_settings.py; \
     $(CP) ../ironic_ui/enabled/_2200_ironic.py enabled; \
     $(ENV) PYTHONPATH=$(PROTO_PYTHON_LIB) ./manage.py \
	 collectstatic --noinput -v 0; \
     $(ENV) PYTHONPATH=$(PROTO_PYTHON_LIB) ./manage.py compress -v 0; \
     $(CP) \
	 static/dashboard/manifest.json \
	 static/dashboard/nondebug_manifest.json; \
     echo "DEBUG = True\nTEMPLATE_DEBUG = True" >> local/local_settings.py; \
     $(ENV) PYTHONPATH=$(PROTO_PYTHON_LIB) \
	 ./manage.py collectstatic --noinput -v 0; \
     $(ENV) PYTHONPATH=$(PROTO_PYTHON_LIB) ./manage.py compress -v 0; \
     $(CP) \
	 static/dashboard/manifest.json static/dashboard/debug_manifest.json; \
     $(ENV) $(COMPONENT_DIR)/files/merge_manifest.py \
	 static/dashboard/debug_manifest.json \
	 static/dashboard/nondebug_manifest.json; \
     $(RM) -r \
	 $(PROTO_PYTHON_LIB)/XStatic* \
	 $(PROTO_PYTHON_LIB)/openstack_dashboard/local/.secret_key_store \
	 $(PROTO_PYTHON_LIB)/openstack_dashboard/local/local_settings.py \
	 $(PROTO_PYTHON_LIB)/openstack_dashboard/manage.py \
	 $(PROTO_PYTHON_LIB)/static \
	 $(PROTO_PYTHON_LIB)/xstatic); (( $$? )) && exit 1;

# Patch openstack_dashboard/settings.py to remove the xstatic imports
# and use.  This is done after 'gmake prep' because we need the
# xstatic imports for static asset collection.
COMPONENT_POST_INSTALL_ACTION += \
     $(GPATCH) -d $(PROTO_DIR) $(GPATCH_FLAGS) \
	 < patches/99-remove.xstatic.patch-proto

#
# The xstatic target builds each XStatic component alongside Horizon.
# This is done because the Django script which collects
# the JavaScript libraries and compresses the static assets
# (manage.py) requires the packages be "installed".  Rather than
# forcing a CBE update for any revision of any XStatic module, we use
# what's specified above.
#
# This extra work is done at package build time rather than when the
# application runs because a) compressing the assets ahead of time
# makes things faster and b) this allows the package to be entirely
# contained in /usr rather than having a separate spot in /var for the
# webservd user to write compressed assets to as they get used.
#
ifneq ($(BUILD_TYPE), evaluation)
.PHONY:	xstatic
xstatic:	$(PROTO_DIR) build
	for xs_archive in $$(ls -d XStatic-* ironic-ui-* | grep -v .tar.gz); do \
		cd $$xs_archive; \
		$(ENV) $(PYTHON.$(BITS)) ./setup.py build; \
		$(ENV) $(PYTHON.$(BITS)) ./setup.py install \
		    --force \
		    --install-data=$(PYTHON_DATA) \
		    --install-lib=$(PYTHON_LIB) \
		    --install-platlib=$(PYTHON_LIB) \
		    --install-purelib=$(PYTHON_LIB) \
		    --root $(PROTO_DIR); \
		cd ../; \
	done
endif

# common targets
build:		$(BUILD_NO_ARCH)

ifneq ($(BUILD_TYPE), evaluation)
# make sure all of the xstatic modules are built
install:	$(INSTALL_NO_ARCH) xstatic
endif

test:		$(NO_TESTS)

system-test:	$(NO_TESTS)

# Includes packages required by Django's manage.py during the Horizon build
REQUIRED_PACKAGES += library/python/babel-27
REQUIRED_PACKAGES += library/python/ceilometerclient-27
REQUIRED_PACKAGES += library/python/cinderclient-27
REQUIRED_PACKAGES += library/python/django-27
REQUIRED_PACKAGES += library/python/django-pyscss-27
REQUIRED_PACKAGES += library/python/django_compressor-27
REQUIRED_PACKAGES += library/python/django_openstack_auth-27
REQUIRED_PACKAGES += library/python/fasteners-27
REQUIRED_PACKAGES += library/python/glanceclient-27
REQUIRED_PACKAGES += library/python/heatclient-27
REQUIRED_PACKAGES += library/python/iso8601-27
REQUIRED_PACKAGES += library/python/keystoneclient-27
REQUIRED_PACKAGES += library/python/lockfile-27
REQUIRED_PACKAGES += library/python/monotonic-27
REQUIRED_PACKAGES += library/python/netaddr-27
REQUIRED_PACKAGES += library/python/neutronclient-27
REQUIRED_PACKAGES += library/python/novaclient-27
REQUIRED_PACKAGES += library/python/oslo.concurrency-27
REQUIRED_PACKAGES += library/python/oslo.config-27
REQUIRED_PACKAGES += library/python/oslo.i18n-27
REQUIRED_PACKAGES += library/python/oslo.serialization-27
REQUIRED_PACKAGES += library/python/oslo.utils-27
REQUIRED_PACKAGES += library/python/pathlib-27
REQUIRED_PACKAGES += library/python/pbr-27
REQUIRED_PACKAGES += library/python/pytz-27
REQUIRED_PACKAGES += library/python/pyyaml-27
REQUIRED_PACKAGES += library/python/requests-27
REQUIRED_PACKAGES += library/python/saharaclient-27
REQUIRED_PACKAGES += library/python/six-27
REQUIRED_PACKAGES += library/python/swiftclient-27
REQUIRED_PACKAGES += library/python/troveclient-27
REQUIRED_PACKAGES += system/core-os
REQUIRED_PACKAGES += web/server/apache-24
REQUIRED_PACKAGES += web/server/apache-24/module/apache-ssl
REQUIRED_PACKAGES += web/server/apache-24/module/apache-wsgi-27
