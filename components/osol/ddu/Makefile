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
# Copyright 2016 Aurelien Larcher
# Copyright 2016 William Headrick
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= ddu
COMPONENT_VERSION= 1.3.1
COMPONENT_REVISION= 4
COMPONENT_SUMMARY= Device Driver Utility (DDU)
COMPONENT_PROJECT_URL= http://www.openindiana.org/
COMPONENT_FMRI= diagnostic/ddu
COMPONENT_CLASSIFICATION= System/Hardware
COMPONENT_LICENSE= CDDL,BSD3
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license

include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

PCI_IDS_FILE=/usr/share/pci.ids.gz

$(SOURCE_DIR)/.prep: $(MAKEFILE_PREREQ)
	$(TOUCH) $@

# Redefine BUILD_32 as there are not Makefiles all the way down
# for the COMPONENT_BUILD_ACTION to use.
$(BUILD_32): $(SOURCE_DIR)/.prep
	$(RM) -r $(@D); $(MKDIR) $(@D)
	$(TOUCH) $@

# Using gzipped pci.ids at another location than /usr/ddu/data/ is not possible
# until all_devices is modified. For now just copy the file as expected.
$(INSTALL_32): $(BUILD_32)
	$(MKDIR) $(PROTO_DIR)
	($(CP) -rpf $(SOURCE_DIR)/srcs/usr $(PROTO_DIR))
	if [ -f $(PCI_IDS_FILE) ]; \
	then gunzip -c $(PCI_IDS_FILE) > $(PROTO_DIR)/usr/ddu/data/pci.ids; \
	fi;
	$(TOUCH) $@

download:

clean::
	$(RM) $(SOURCE_DIR)/.prep

clobber: clean

build: $(BUILD_32)

install: $(INSTALL_32)

test:		$(NO_TESTS)

# Build dependencies
REQUIRED_PACKAGES += system/pciutils/pci.ids

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += diagnostic/ddu/library
REQUIRED_PACKAGES += library/python/gnome-python-27
REQUIRED_PACKAGES += library/python/pygobject-27
REQUIRED_PACKAGES += library/python/pygtk2-27
REQUIRED_PACKAGES += library/python/python-notify-27
REQUIRED_PACKAGES += library/python/simplejson-27
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += service/hal
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libdbus
