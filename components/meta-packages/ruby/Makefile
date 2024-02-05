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
# Copyright 2024 Marcel Telka
#

BUILD_STYLE = pkg

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		ruby
COMPONENT_VERSION =		$(RUBY_VERSION)
COMPONENT_SUMMARY =		Ruby, RubyGems, and Rake
COMPONENT_PROJECT_URL =		https://www.ruby-lang.org/
COMPONENT_FMRI =		runtime/ruby
COMPONENT_CLASSIFICATION =	Development/Ruby

include $(WS_MAKE_RULES)/common.mk

PKG_MACROS += RUBYV=$(subst .,,$(RUBY_VERSION))

# Auto-generated dependencies
