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
# Copyright 2017 Adam Stevko
# Copyright 2018 Michal Nowak
# Copyright 2022 Niklas Poslovski
# Copyright 2022 Daniel Bell
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= geoip-database
COMPONENT_VERSION= 20240128
COMPONENT_SUMMARY= GeoLite geolocation databases compiled by MaxMind
COMPONENT_PROJECT_URL= https://mailfud.org/geoip-legacy
COMPONENT_FMRI= database/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_DOWNLOAD_BASE=https://github.com/dbh201/geoip-database/raw/$(COMPONENT_VERSION)/
COMPONENT_LICENSE= CC-BY-SA-4.0

# Note for updates: Make sure to not only update the component version but also update the hashes in hashes/sha256sums.txt
# Plus, remove all former downloaded files.

HASH_DIR=$(COMPONENT_DIR)/hashes
export HASH_DIR

FETCH_KEEP=-gn
COMPONENT_SRC=  GeoIP.dat
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).gz
COMPONENT_ARCHIVE_URL=  $(COMPONENT_DOWNLOAD_BASE)/GeoIP.dat.gz

COMPONENT_SRC_1=GeoIPv6.dat
COMPONENT_ARCHIVE_1=$(COMPONENT_SRC_1).gz
COMPONENT_ARCHIVE_URL_1=$(COMPONENT_DOWNLOAD_BASE)/GeoIPv6.dat.gz

COMPONENT_SRC_2=GeoIPCity.dat
COMPONENT_ARCHIVE_2=$(COMPONENT_SRC_2).gz
COMPONENT_ARCHIVE_URL_2=$(COMPONENT_DOWNLOAD_BASE)/GeoIPCity.dat.gz

COMPONENT_SRC_3=GeoIPCityv6.dat
COMPONENT_ARCHIVE_3=$(COMPONENT_SRC_3).gz
COMPONENT_ARCHIVE_URL_3=$(COMPONENT_DOWNLOAD_BASE)/GeoIPCityv6.dat.gz

COMPONENT_SRC_4=GeoIPASNum.dat
COMPONENT_ARCHIVE_4=$(COMPONENT_SRC_4).gz
COMPONENT_ARCHIVE_URL_4=$(COMPONENT_DOWNLOAD_BASE)/GeoIPASNum.dat.gz

COMPONENT_SRC_5=GeoIPASNumv6.dat
COMPONENT_ARCHIVE_5=$(COMPONENT_SRC_5).gz
COMPONENT_ARCHIVE_URL_5=$(COMPONENT_DOWNLOAD_BASE)/GeoIPASNumv6.dat.gz

define switch-source-dir
SOURCE_DIR$(1)= $$(COMPONENT_SRC$(1))-$$(COMPONENT_VERSION)
UNPACK_ARGS$(1)= -r $$(SOURCE_DIR$(1))
endef

$(eval $(call switch-source-dir,))
$(foreach suffix,1 2 3 4 5,$(eval $(call switch-source-dir,_$(suffix))) )

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/ips.mk

CLEAN_PATHS+= $(BUILD_DIR)

$(BUILD_DIR_64)/.built:
	$(MKDIR) $(BUILD_DIR_64)
	$(TOUCH) $(@)

$(INSTALL_64):
	$(MKDIR) $(PROTOUSRSHAREDIR)/GeoIP
        
	$(INSTALL) -m 0644 $(SOURCE_DIR)/GeoIP.dat $(PROTOUSRSHAREDIR)/GeoIP/GeoIP.dat
	$(INSTALL) -m 0644 $(SOURCE_DIR_1)/GeoIPv6.dat $(PROTOUSRSHAREDIR)/GeoIP/GeoIPv6.dat
	$(INSTALL) -m 0644 $(SOURCE_DIR_2)/GeoIPCity.dat $(PROTOUSRSHAREDIR)/GeoIP/GeoIPCity.dat
	$(INSTALL) -m 0644 $(SOURCE_DIR_3)/GeoIPCityv6.dat $(PROTOUSRSHAREDIR)/GeoIP/GeoIPCityv6.dat
	$(INSTALL) -m 0644 $(SOURCE_DIR_4)/GeoIPASNum.dat $(PROTOUSRSHAREDIR)/GeoIP/GeoIPASNum.dat
	$(INSTALL) -m 0644 $(SOURCE_DIR_5)/GeoIPASNumv6.dat $(PROTOUSRSHAREDIR)/GeoIP/GeoIPASNumv6.dat

	$(TOUCH) $(@)

build:          $(BUILD_64) prep

install:        $(INSTALL_64) build

# Auto-generated dependencies
