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
# Copyright 2013 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= aspell-ru
HUMAN_VERSION= 0.99f7-1
COMPONENT_VERSION= 0.99.15.7.1
COMPONENT_REVISION= 1
COMPONENT_SUMMARY= GNU Aspell spell russian dictionaries
COMPONENT_PROJECT_URL= https://ftp.gnu.org/gnu/aspell/dict/0index.html
COMPONENT_SRC= aspell6-ru-$(HUMAN_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= sha256:5c29b6ccce57bc3f7c4fb0510d330446b9c769e59c92bdfede27333808b6e646
COMPONENT_ARCHIVE_URL= https://ftp.gnu.org/gnu/aspell/dict/ru/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI= text/aspell/ru
COMPONENT_CLASSIFICATION= System/Text Tools
COMPONENT_LICENSE= aspell-ru Copyright
COMPONENT_LICENSE_FILE= Copyright

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PRE_CONFIGURE_ACTION += ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_OPTIONS = 

# Auto-generated dependencies
