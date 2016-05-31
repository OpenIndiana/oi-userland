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
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= ddu
COMPONENT_VERSION= 1.3.1
COMPONENT_SUMMARY= Device Driver Utility (DDU)
COMPONENT_PROJECT_URL= http://www.openindiana.org/
COMPONENT_FMRI= diagnostic/ddu
COMPONENT_CLASSIFICATION= System/Hardware
COMPONENT_LICENSE= CDDL,BSD3
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license

include $(WS_MAKE_RULES)/ips.mk

PCI_IDS_FILE=/usr/share/pci.ids.gz

build:

# Using gzipped pci.ids at another location than /usr/ddu/data/ is not possible
# until all_devices is modified. For now just copy the file as expected.

install:
	$(MKDIR) $(PROTO_DIR)
	($(CP) -rpf $(SOURCE_DIR)/srcs/usr $(PROTO_DIR))
	if [ -f $(PCI_IDS_FILE) ]; \
	then gunzip -c $(PCI_IDS_FILE) > $(PROTO_DIR)/usr/ddu/data/pci.ids; \
	fi;

clean:
	$(RM) -rf	$(BUILD_DIR)

clobber: clean

test:		$(NO_TESTS)

REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += library/python-2/python-notify-26
REQUIRED_PACKAGES += library/python-2/simplejson-26
REQUIRED_PACKAGES += library/python/gnome-python-26
REQUIRED_PACKAGES += library/python/pygobject-26
REQUIRED_PACKAGES += library/python/pygtk2-26
REQUIRED_PACKAGES += runtime/python-26
REQUIRED_PACKAGES += service/hal
REQUIRED_PACKAGES += system/pciutils/pci.ids
