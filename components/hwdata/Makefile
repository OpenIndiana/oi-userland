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
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
#
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=         hwdata
COMPONENT_VERSION=      0.5.11

include ../../make-rules/ips.mk

# Since upstream only offers the latest snapshot for download, without
# any way to retrieve a specific version, we just keep the currently
# shipped versions of these two text files directly in the gate and 
# simply check in new versions to update them.
#
# When it's time to update, you can use these rules to download with
# 'gmake -B pci.ids usb.ids'   After updating the data files, ensure
# that the header with version/date and license info is still being 
# correctly extracted and copied into the generated license files.

download::
	@echo 'No downloads for this component'

ID_FILES = pci.ids usb.ids

COMPONENT_ARCHIVE_URL_pci.ids =	http://pciids.sourceforge.net/v2.2/pci.ids
COMPONENT_ARCHIVE_URL_usb.ids =	http://www.linux-usb.org/usb.ids
COMPONENT_ARCHIVE_URLS = $(foreach i,$(ID_FILES),$(COMPONENT_ARCHIVE_URL_$(i)))

COMPONENT_BUGDB=	utility/hwdata

PKG_OPTIONS += -D COMPONENT_ARCHIVE_URLS='$(COMPONENT_ARCHIVE_URLS:%=value="%")'

$(ID_FILES):
	curl -s -o $@ $(COMPONENT_ARCHIVE_URL_$(@F))

# License files for packaging are generated during the build
LICENSES = $(ID_FILES:%=%.license)
BUILT_LICENSES = $(LICENSES:%=$(BUILD_DIR)/%)
TPNO_pci.ids.license = 7530
TPNO_usb.ids.license = 7831

# Extract the header up to the first blank line
$(BUILD_DIR)/%.header: %
	$(MKDIR) $(@D)
	$(GSED) -e '/^$$/ q' $< > $@

# Generate license files for each document by substituting in templates:
# __FILE_NAME_VERS__ replace with name & version of ids file
# __TPNO__ - Oracle tracking number
# __HEADER__ - read in contents of generated header file, then delete the 
#		__HEADER__ line
$(BUILD_DIR)/%.license: $(BUILD_DIR)/%.header
	FILENAME="$(basename $(@F))" ; \
	VERSION="$$(awk -F: '/Version:/ { print $$2 ; exit }' $<)" ; \
	FILE_NAME_VERS="$${FILENAME}$${VERSION}" ; \
	$(GSED) -e "s/__FILE_NAME_VERS__/$${FILE_NAME_VERS}/" \
	    -e 's/__TPNO__/$(TPNO_$(@F))/' \
	    -e '/__HEADER__/ r $<' -e '/__HEADER__/ d' ids.license.tmpl > $@

install build: $(BUILT_LICENSES)

test:	$(NO_TESTS)

clobber clean::
	$(RM) -r $(BUILD_DIR)

include ../../make-rules/depend.mk
