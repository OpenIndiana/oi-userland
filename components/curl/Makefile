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
# Copyright (c) 2011, Oracle and/or its affiliates. All rights reserved.
#
include ../../make-rules/shared-macros.mk

COMPONENT_NAME =        curl
COMPONENT_VERSION=      7.21.2
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=  http://curl.haxx.se/
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha1:af8182165d7a0d16b97e2c2936ed92f3ba5c868c
COMPONENT_ARCHIVE_URL=  http://curl.haxx.se/download/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

PKG_CONFIG_PATH_32 = /usr/lib/pkgconfig
PKG_CONFIG_PATH_64 = /usr/lib/$(MACH64)/pkgconfig

PATCH_LEVEL = 0

LIBNAME =       $(COMPONENT_NAME)
LINTOUT =       lint.out

GSSAPI_LIBDIR_32 = /usr/lib
GSSAPI_LIBDIR_64 = /usr/lib/$(MACH64)

# Enable C99 mode
studio_C99MODE = $(studio_C99_ENABLE)

# And we want -Xc too
CFLAGS += $(CC_BITS) -Xc -xnorunpath $(XPG6MODE)
CFLAGS += $(CPP_POSIX) $(CPP_LARGEFILES)
CPPFLAGS += $(CPP_POSIX) $(CPP_LARGEFILES) -D__EXTENSIONS__=1 -DNDEBUG
LDFLAGS += -lpthread -lc -lm -lgss -lsocket -lresolv -lnsl -lgen

CONFIGURE_ENV += CPP="$(CC) $(CPPFLAGS) $(CFLAGS) -E"
CONFIGURE_ENV += CFLAGS="$(CFLAGS)"
CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"
CONFIGURE_ENV += CCLD="$(CC) $(CFLAGS) $(LDFLAGS)"
CONFIGURE_ENV += LDFLAGS="$(LDFLAGS)"
CONFIGURE_ENV += PKG_CONFIG_PATH="$(PKG_CONFIG_PATH_$(BITS))"

CONFIGURE_OPTIONS += --localstatedir=/var --enable-shared --disable-static
CONFIGURE_OPTIONS += --enable-http --enable-ftp
CONFIGURE_OPTIONS += --enable-file --enable-dict
CONFIGURE_OPTIONS += --enable-manual --disable-libgcc
CONFIGURE_OPTIONS += --enable-rtsp --enable-proxy
CONFIGURE_OPTIONS += --enable-telnet --enable-tftp --enable-pop3
CONFIGURE_OPTIONS += --enable-imap --enable-smtp
CONFIGURE_OPTIONS += --enable-ipv6 --enable-nonblocking
CONFIGURE_OPTIONS += --enable-thread --enable-verbose
CONFIGURE_OPTIONS += --disable-sspi --enable-crypto-auth
CONFIGURE_OPTIONS += --enable-cookies --disable-hidden-symbols
CONFIGURE_OPTIONS += --disable-soname-bump
CONFIGURE_OPTIONS += --enable-ldap --with-random=/dev/urandom
CONFIGURE_OPTIONS += --with-ssl --with-ldap-lib=ldap
CONFIGURE_OPTIONS += --with-lber-lib=sldap
CONFIGURE_OPTIONS += --with-gssapi-includes=/usr/include/gssapi
CONFIGURE_OPTIONS += --with-gssapi-libs=$(GSSAPI_LIBDIR_$(BITS))
CONFIGURE_OPTIONS += --with-gssapi=/usr --without-ca-bundle
CONFIGURE_OPTIONS += --with-ca-path=/etc/openssl/certs
CONFIGURE_OPTIONS += --with-zlib=/usr --with-libidn=/usr
CONFIGURE_OPTIONS += --with-pic
CONFIGURE_OPTIONS += "curl_disallow_getifaddrs=yes"

PKG_PROTO_DIRS +=	$(COMPONENT_SRC)

COMPONENT_POST_BUILD_ACTION = \
    ( cd $(@D) ; \
	$(LINT) -nsvx $(CC_BITS) -o $(LIBNAME) -I$(@D) \
	-I$(COMPONENT_DIR)/$(COMPONENT_SRC)/include \
	-I$(COMPONENT_DIR)/$(COMPONENT_SRC) \
	$(COMPONENT_DIR)/llib-l$(LIBNAME) > $(LINTOUT) 2>&1)

COMPONENT_POST_INSTALL_ACTION = \
    ( $(CP) $(COMPONENT_DIR)/llib-l$(LIBNAME) $(PROTOUSRLIBDIR)/ ; \
	cd $(@D); $(INSTALL) llib-l$(LIBNAME).ln \
	    $(PROTO_DIR)/$(CONFIGURE_LIBDIR.$(BITS)) )

PROTOUSRBINDIR64 = $(PROTOUSRBINDIR)/$(MACH64)
PROTOUSRSHAREDOCDIR1 = $(PROTOUSRSHAREDIR)/doc/curl/html
PROTOUSRSHAREDOCDIR2 = $(PROTOUSRSHAREDIR)/doc/libcurl/html

build: $(BUILD_32_and_64)

HTMLDOCLIST1 = curl.html curl-config.html index.html
HTMLDOCLIST2 = curl_easy_cleanup.html curl_easy_duphandle.html \
	       curl_easy_escape.html curl_easy_getinfo.html \
	       curl_easy_init.html curl_easy_pause.html \
	       curl_easy_perform.html curl_easy_recv.html \
	       curl_easy_reset.html curl_easy_send.html \
	       curl_easy_setopt.html curl_easy_strerror.html \
	       curl_easy_unescape.html curl_escape.html \
	       curl_formadd.html curl_formfree.html \
	       curl_formget.html curl_free.html \
	       curl_getdate.html curl_getenv.html \
	       curl_global_cleanup.html curl_global_init.html \
	       curl_global_init_mem.html curl_mprintf.html \
	       curl_multi_add_handle.html curl_multi_assign.html \
	       curl_multi_cleanup.html curl_multi_fdset.html \
	       curl_multi_info_read.html curl_multi_init.html \
	       curl_multi_perform.html curl_multi_remove_handle.html \
	       curl_multi_setopt.html curl_multi_socket.html \
	       curl_multi_socket_action.html curl_multi_strerror.html \
	       curl_multi_timeout.html curl_share_cleanup.html \
	       curl_share_init.html curl_share_setopt.html \
	       curl_share_strerror.html curl_slist_append.html \
	       curl_slist_free_all.html curl_strequal.html \
	       curl_unescape.html curl_version.html \
	       curl_version_info.html index.html \
	       libcurl-easy.html libcurl-errors.html \
	       libcurl-multi.html libcurl-share.html \
	       libcurl-tutorial.html libcurl.html

MAN1LIST = curl-config.1 curl.1
MAN3LIST = curl_easy_cleanup.3 curl_easy_duphandle.3 \
	   curl_easy_escape.3 curl_easy_getinfo.3 \
	   curl_easy_init.3 curl_easy_pause.3 \
	   curl_easy_perform.3 curl_easy_recv.3 \
	   curl_easy_reset.3 curl_easy_send.3 \
	   curl_easy_setopt.3 curl_easy_strerror.3 \
	   curl_easy_unescape.3 curl_escape.3 \
	   curl_formadd.3 curl_formfree.3 \
	   curl_formget.3 curl_free.3 \
	   curl_getdate.3 curl_getenv.3 \
	   curl_global_cleanup.3 curl_global_init.3 \
	   curl_global_init_mem.3 curl_mprintf.3 \
	   curl_multi_add_handle.3 curl_multi_assign.3 \
	   curl_multi_cleanup.3 curl_multi_fdset.3 \
	   curl_multi_info_read.3 curl_multi_init.3 \
	   curl_multi_perform.3 curl_multi_remove_handle.3 \
	   curl_multi_setopt.3 curl_multi_socket.3 \
	   curl_multi_socket_action.3 curl_multi_strerror.3 \
	   curl_multi_timeout.3 curl_share_cleanup.3 \
	   curl_share_init.3 curl_share_setopt.3 \
	   curl_share_strerror.3 curl_slist_append.3 \
	   curl_slist_free_all.3 curl_strequal.3 \
	   curl_unescape.3 curl_version.3 \
	   curl_version_info.3 libcurl-easy.3 \
	   libcurl-errors.3 libcurl-multi.3 \
	   libcurl-share.3 libcurl-tutorial.3 libcurl.3

GSED = /usr/gnu/bin/sed

include ../../make-rules/shared-targets.mk

install: $(INSTALL_32_and_64)
	$(MKDIR) $(PROTOUSRSHAREDOCDIR1) ; \
	    list1='$(HTMLDOCLIST1)' ; for f in $$list1; do \
	    $(INSTALL) -m 0644 $(COMPONENT_DIR)/$(COMPONENT_SRC)/docs/$$f \
		$(PROTOUSRSHAREDOCDIR1)/ ; \
	    done
	$(MKDIR) $(PROTOUSRSHAREDOCDIR2) ; \
	    list2='$(HTMLDOCLIST2)' ; for f in $$list2; do \
	    $(INSTALL) -m 0644 \
		$(COMPONENT_DIR)/$(COMPONENT_SRC)/docs/libcurl/$$f \
		$(PROTOUSRSHAREDOCDIR2)/ ; \
	    done
	$(MKDIR) $(PROTOUSRSHAREMAN1DIR) ; \
	    list3='$(MAN1LIST)'; for f in $$list3; do \
	    $(GSED) -f oracleman-stability \
		$(PROTOUSRSHAREMAN1DIR)/$$f > \
		$(PROTOUSRSHAREMAN1DIR)/$$f.sed 2>&1 ; \
	    $(CP) -fp $(PROTOUSRSHAREMAN1DIR)/$$f.sed \
		$(PROTOUSRSHAREMAN1DIR)/$$f ; \
	    $(RM) -f $(PROTOUSRSHAREMAN1DIR)/$$f.sed ; \
	    done
	$(MKDIR) $(PROTOUSRSHAREMAN3DIR) ; \
	    list4='$(MAN3LIST)'; for f in $$list4; do \
	    $(GSED) -f oracleman-stability \
		$(PROTOUSRSHAREMAN3DIR)/$$f > \
		$(PROTOUSRSHAREMAN3DIR)/$$f.sed 2>&1 ; \
	    $(CP) -fp $(PROTOUSRSHAREMAN3DIR)/$$f.sed \
		$(PROTOUSRSHAREMAN3DIR)/$$f ; \
	    $(RM) -f $(PROTOUSRSHAREMAN3DIR)/$$f.sed ; \
	    done
	$(RM) $(PROTOUSRBINDIR)/curl-config ; \
	$(INSTALL) -m 0755 $(COMPONENT_DIR)/Solaris/curl-config \
	    $(PROTOUSRBINDIR)/
	$(RM) $(PROTOUSRBINDIR64)/curl-config 
	$(GSED) -e "s#MACH64#$(MACH64)#g" \
	    $(COMPONENT_DIR)/Solaris/curl-config-64 > \
		$(COMPONENT_DIR)/curl-config 
	$(INSTALL) -m 0755  \
		$(COMPONENT_DIR)/curl-config $(PROTOUSRBINDIR64)/
	$(RM) $(COMPONENT_DIR)/curl-config

test: $(BUILD_32_and_64)
	@cd $(BUILD_DIR_32); $(GMAKE) check
	@cd $(BUILD_DIR_64); $(GMAKE) check

BUILD_PKG_DEPENDENCIES = $(BUILD_TOOLS)

include ../../make-rules/depend.mk

