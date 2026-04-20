X11_CATEGORY=DRIVER
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=xf86-video-illumosfb
COMPONENT_VERSION=0.5
COMPONENT_SUMMARY=Xorg driver for illumos UEFI frame buffer
COMPONENT_PROJECT_URL=  https://github.com/LuminousMonkey/xf86-video-illumosfb/
COMPONENT_FMRI=         x11/server/xorg/driver/xorg-video-illumosfb
COMPONENT_SRC=          xf86-video-illumosfb
COMPONENT_CLASSIFICATION=       Drivers/Display
COMPONENT_LICENSE=      ISC
COMPONENT_LICENSE_FILE= LICENSE
COMPONENT_PREP_ACTION= cd $(@D) && PATH="$(PATH)" NOCONFIGURE=1 /usr/bin/bash ./autogen.sh

GIT_BRANCH=main
GIT_REPO=https://github.com/LuminousMonkey/xf86-video-illumosfb.git
GIT_COMMIT_ID=8ad57812ca2e99be6281f5142101811482026c55
GIT_HASH=sha256:315963e992a849eb0a84373d9889a5e604eb8f7e4764518abfedbd7ba7c98888

TEST_TARGET= $(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

REQUIRED_PACKAGES += x11/server/xorg
REQUIRED_PACKAGES += library/graphics/pixman
REQUIRED_PACKAGES += developer/build/autoconf/xorg-macros

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
