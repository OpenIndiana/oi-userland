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
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =	openssl
# When new version of OpenSSL comes in, you must update both COMPONENT_VERSION
# and IPS_COMPONENT_VERSION.
# When upgrading OpenSSL, please, DON'T FORGET TO TEST WANBOOT too. 
# For more information about wanboot-openssl testing, please refer to
# ../README.
COMPONENT_VERSION =	1.0.0i
# Version for IPS. It is easier to do it manually than convert the letter to a
# number while taking into account that there might be no letter at all.
IPS_COMPONENT_VERSION = 1.0.0.9
COMPONENT_PROJECT_URL=	http://www.openssl.org/
COMPONENT_SRC =		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE =	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:548262d15777c504be1ab9bb8fabef1e14a3de54837a6593c8f403dd843d5e57
COMPONENT_ARCHIVE_URL =	$(COMPONENT_PROJECT_URL)source/$(COMPONENT_ARCHIVE)

# Architecture-specific patches
EXTRA_PATCHES.i386 = $(PATCH_DIR)/openssl-1.0.0d-aesni-v4.i386-patch
EXTRA_PATCHES.sparc = $(PATCH_DIR)/openssl-1.0.0d-t4-engine.sparc-patch
EXTRA_PATCHES = $(EXTRA_PATCHES.$(MACH))

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk
include $(WS_TOP)/make-rules/lint-libraries.mk

PATH=$(SPRO_VROOT)/bin:/usr/bin:/usr/gnu/bin:/usr/perl5/bin

# Variant of OpenSSL for wanboot is built in build/sparcv9-wanboot.
BUILD_DIR_WANBOOT = $(BUILD_DIR)/$(MACH64)-wanboot

# OpenSSL does not use autoconf but its own configure system.
CONFIGURE_SCRIPT = $(SOURCE_DIR)/Configure

# This is to force OpenSSL's Configure script to use gmake for 'make links'. 
# Otherwise it fails with:
#     mksh: Fatal error in reader: Unmatched `(' on line
CONFIGURE_ENV += MAKE="$(GMAKE)"

# Used in the configure options below.
PKCS11_LIB32 = /usr/lib/libpkcs11.so.1
PKCS11_LIB64 = /usr/lib/64/libpkcs11.so.1
ENGINESDIR_32 = /lib/openssl/engines
ENGINESDIR_64 = /lib/openssl/engines/64

# Configure options common to both regular OpenSSL and OpenSSL for wanboot.
CONFIGURE_OPTIONS =  -DSOLARIS_OPENSSL -DNO_WINDOWS_BRAINDEATH
CONFIGURE_OPTIONS += --openssldir=/etc/openssl
CONFIGURE_OPTIONS += --prefix=/usr
# We use OpenSSL install code for installing only manual pages and we do that
# for 32-bit version only.
CONFIGURE_OPTIONS += --install_prefix=$(PROTO_DIR)
CONFIGURE_OPTIONS += no-ec
CONFIGURE_OPTIONS += no-ecdh
CONFIGURE_OPTIONS += no-ecdsa
CONFIGURE_OPTIONS += no-rc3
CONFIGURE_OPTIONS += no-rc5
CONFIGURE_OPTIONS += no-mdc2
CONFIGURE_OPTIONS += no-idea
CONFIGURE_OPTIONS += no-hw_4758_cca
CONFIGURE_OPTIONS += no-hw_aep
CONFIGURE_OPTIONS += no-hw_atalla
CONFIGURE_OPTIONS += no-hw_chil
CONFIGURE_OPTIONS += no-hw_gmp
CONFIGURE_OPTIONS += no-hw_ncipher
CONFIGURE_OPTIONS += no-hw_nuron
CONFIGURE_OPTIONS += no-hw_padlock
CONFIGURE_OPTIONS += no-hw_sureware
CONFIGURE_OPTIONS += no-hw_ubsec
CONFIGURE_OPTIONS += no-hw_cswift
# MD2 is not enabled by default in OpensSSL but some software we have in
# Userland needs it. One example is nmap.
CONFIGURE_OPTIONS += enable-md2
CONFIGURE_OPTIONS += no-seed
# We use both no-whirlpool and no-whrlpool since there is an inconsistency in
# the OpenSSL code and one needs both to build OpenSSL successfully with
# Whirlpool implementation removed.
CONFIGURE_OPTIONS += no-whirlpool
CONFIGURE_OPTIONS += no-whrlpool
# Some additional options needed for our engines.
CONFIGURE_OPTIONS += --pk11-libname=$(PKCS11_LIB$(BITS))
CONFIGURE_OPTIONS += --enginesdir=$(ENGINESDIR_$(BITS))

# We define our own compiler and linker option sets for Solaris. See Configure
# for more information.
CONFIGURE_OPTIONS32_i386 =	solaris-x86-cc-sunw
CONFIGURE_OPTIONS32_sparc =	solaris-sparcv9-cc-sunw
CONFIGURE_OPTIONS64_i386 =	solaris64-x86_64-cc-sunw
CONFIGURE_OPTIONS64_sparc =	solaris64-sparcv9-cc-sunw

# Options specific to regular build.
# They must not be specified as common, as they cannot be overridden.
$(BUILD_DIR)/$(MACH32)/.configured:	CONFIGURE_OPTIONS += threads
$(BUILD_DIR)/$(MACH64)/.configured:	CONFIGURE_OPTIONS += threads
$(BUILD_DIR)/$(MACH32)/.configured:	CONFIGURE_OPTIONS += shared
$(BUILD_DIR)/$(MACH64)/.configured:	CONFIGURE_OPTIONS += shared
$(BUILD_DIR)/$(MACH32)/.configured:	CONFIGURE_OPTIONS += shared
$(BUILD_DIR)/$(MACH64)/.configured:	CONFIGURE_OPTIONS += shared
$(BUILD_DIR)/$(MACH32)/.configured:	CONFIGURE_OPTIONS += \
	$(CONFIGURE_OPTIONS32_$(MACH))
$(BUILD_DIR)/$(MACH64)/.configured:	CONFIGURE_OPTIONS += \
	$(CONFIGURE_OPTIONS64_$(MACH))

# OpenSSL for wanboot specific options
$(BUILD_DIR_WANBOOT)/.configured:	BITS=64
$(BUILD_DIR_WANBOOT)/.configured:	CONFIGURE_OPTIONS += -DNO_CHMOD
$(BUILD_DIR_WANBOOT)/.configured:	CONFIGURE_OPTIONS += -D_BOOT
$(BUILD_DIR_WANBOOT)/.configured:	CONFIGURE_OPTIONS += -DOPENSSL_NO_DTLS1
$(BUILD_DIR_WANBOOT)/.configured:	CONFIGURE_OPTIONS += no-cast
$(BUILD_DIR_WANBOOT)/.configured:	CONFIGURE_OPTIONS += no-dso
$(BUILD_DIR_WANBOOT)/.configured:	CONFIGURE_OPTIONS += no-rc4
$(BUILD_DIR_WANBOOT)/.configured:	CONFIGURE_OPTIONS += no-ripemd
$(BUILD_DIR_WANBOOT)/.configured:	CONFIGURE_OPTIONS += no-hw
$(BUILD_DIR_WANBOOT)/.configured:	CONFIGURE_OPTIONS += no-threads
$(BUILD_DIR_WANBOOT)/.configured:	CONFIGURE_OPTIONS += no-shared
$(BUILD_DIR_WANBOOT)/.configured:	CONFIGURE_OPTIONS += \
	solaris64-sparcv9-cc-sunw-wanboot


# OpenSSL has its own configure system which must be run from the fully
# populated source code directory. However, the Userland configuration phase is
# run from the build directory. So, we must get the full source code into the
# build directory.
COMPONENT_PRE_CONFIGURE_ACTION = \
    ( $(CLONEY) $(SOURCE_DIR) $(BUILD_DIR)/$(MACH$(BITS)); )

$(BUILD_DIR_WANBOOT)/.configured:	COMPONENT_PRE_CONFIGURE_ACTION = \
	    ( $(CLONEY) $(SOURCE_DIR) $(BUILD_DIR_WANBOOT); )

# We deliver only one opensslconf.h file which must be suitable for both 32 and
# 64 bits. Depending on the configuration option, OpenSSL's Configure script
# creates opensslconf.h for either 32 or 64 bits. A patch makes the resulting
# header file usable on both architectures. The patch was generated against the
# opensslconf.h version from the 32 bit build.
COMPONENT_POST_CONFIGURE_ACTION = \
    ( [ $(BITS) -eq 32 ] && $(GPATCH) -p1 $(@D)/crypto/opensslconf.h \
      patches-post-config/opensslconf.patch; cd $(@D); $(MAKE) depend; )


# We do not ship our engines as patches since it would be more difficult to
# update the files which have been under continuous development. We rather copy
# the files to the right directories.
# Same holds for wanboot-stubs.c, which stubs out several functions, that are
# not available in the stand-alone environment of wanboot.
COMPONENT_PRE_BUILD_ACTION = \
    ( $(CP) -fp engines/aesni/eng_aesni.c	$(@D)/crypto/engine; \
      $(CP) -fp engines/aesni/aesni-x86*.pl	$(@D)/crypto/aes/asm; \
      $(CP) -fp engines/devcrypto/*.[ch]	$(@D)/engines; \
      $(CP) -fp engines/pkcs11/*.[ch]		$(@D)/crypto/engine; \
      $(CP) -fp engines/t4/eng_t4*.[ch]		$(@D)/crypto/engine; \
      $(CP) -fp engines/t4/t4_aes.S		$(@D)/crypto/aes/asm; \
      $(CP) -fp engines/t4/t4_des.S		$(@D)/crypto/des/asm; \
      $(CP) -fp engines/t4/t4_md5.S		$(@D)/crypto/md5/asm; \
      $(CP) -fp engines/t4/t4_sha?.S		$(@D)/crypto/sha/asm; \
      $(CP) -fp wanboot-openssl/wanboot-stubs.c	$(@D)/crypto; )

# OpenSSL for wanboot is built on sparc only.
ifeq ($(MACH), sparc)
BUILD_64 +=	$(BUILD_DIR_WANBOOT)/.built
endif

build:		$(BUILD_32_and_64)

# Object files for wanboot-openssl.o have to be listed explicitly.
WANBOOT_OBJS =  \
    crypto/aes/aes-sparcv9.o crypto/aes/aes_cbc.o crypto/aes/aes_cfb.o \
    crypto/aes/aes_core.o crypto/aes/aes_ecb.o crypto/aes/aes_ofb.o \
    crypto/aes/aes_wrap.o crypto/asn1/a_bitstr.o crypto/asn1/a_bool.o \
    crypto/asn1/a_bytes.o crypto/asn1/a_d2i_fp.o crypto/asn1/a_digest.o \
    crypto/asn1/a_dup.o crypto/asn1/a_enum.o crypto/asn1/a_gentm.o \
    crypto/asn1/a_i2d_fp.o crypto/asn1/a_int.o crypto/asn1/a_mbstr.o \
    crypto/asn1/a_object.o crypto/asn1/a_octet.o crypto/asn1/a_print.o \
    crypto/asn1/a_set.o crypto/asn1/a_sign.o crypto/asn1/a_strex.o \
    crypto/asn1/a_strnid.o crypto/asn1/a_time.o crypto/asn1/a_type.o \
    crypto/asn1/a_utctm.o crypto/asn1/a_utf8.o crypto/asn1/a_verify.o \
    crypto/asn1/ameth_lib.o crypto/asn1/asn1_err.o crypto/asn1/asn1_gen.o \
    crypto/asn1/asn1_lib.o crypto/asn1/asn1_par.o crypto/asn1/asn_mime.o \
    crypto/asn1/asn_pack.o crypto/asn1/bio_asn1.o crypto/asn1/bio_ndef.o \
    crypto/asn1/d2i_pr.o crypto/asn1/evp_asn1.o crypto/asn1/f_int.o \
    crypto/asn1/f_string.o crypto/asn1/i2d_pr.o crypto/asn1/nsseq.o \
    crypto/asn1/p5_pbe.o crypto/asn1/p5_pbev2.o crypto/asn1/p8_pkey.o \
    crypto/asn1/t_pkey.o crypto/asn1/t_x509.o crypto/asn1/t_x509a.o \
    crypto/asn1/tasn_dec.o crypto/asn1/tasn_enc.o crypto/asn1/tasn_fre.o \
    crypto/asn1/tasn_new.o crypto/asn1/tasn_prn.o crypto/asn1/tasn_typ.o \
    crypto/asn1/tasn_utl.o crypto/asn1/x_algor.o crypto/asn1/x_attrib.o \
    crypto/asn1/x_bignum.o crypto/asn1/x_crl.o crypto/asn1/x_exten.o \
    crypto/asn1/x_info.o crypto/asn1/x_long.o crypto/asn1/x_name.o \
    crypto/asn1/x_pkey.o crypto/asn1/x_pubkey.o crypto/asn1/x_req.o \
    crypto/asn1/x_sig.o crypto/asn1/x_spki.o crypto/asn1/x_val.o \
    crypto/asn1/x_x509.o crypto/asn1/x_x509a.o crypto/bf/bf_cfb64.o \
    crypto/bf/bf_ecb.o crypto/bf/bf_enc.o crypto/bf/bf_ofb64.o \
    crypto/bf/bf_skey.o crypto/bio/b_dump.o crypto/bio/b_print.o \
    crypto/bio/bf_buff.o crypto/bio/bio_err.o crypto/bio/bio_lib.o \
    crypto/bio/bss_file.o crypto/bio/bss_mem.o crypto/bio/bss_null.o \
    crypto/bio/bss_sock.o crypto/bn/bn-sparcv9.o crypto/bn/bn_add.o \
    crypto/bn/bn_blind.o crypto/bn/bn_ctx.o crypto/bn/bn_div.o \
    crypto/bn/bn_err.o crypto/bn/bn_exp.o crypto/bn/bn_exp2.o \
    crypto/bn/bn_gcd.o crypto/bn/bn_lib.o crypto/bn/bn_mod.o \
    crypto/bn/bn_mont.o crypto/bn/bn_mul.o crypto/bn/bn_prime.o \
    crypto/bn/bn_print.o crypto/bn/bn_rand.o crypto/bn/bn_recp.o \
    crypto/bn/bn_shift.o crypto/bn/bn_sqr.o crypto/bn/bn_word.o \
    crypto/bn/sparcv9-mont.o crypto/bn/sparcv9a-mont.o \
    crypto/buffer/buf_err.o crypto/buffer/buffer.o crypto/camellia/camellia.o \
    crypto/camellia/cmll_cbc.o crypto/camellia/cmll_cfb.o \
    crypto/camellia/cmll_ecb.o crypto/camellia/cmll_misc.o \
    crypto/camellia/cmll_ofb.o crypto/cms/cms_asn1.o crypto/cms/cms_att.o \
    crypto/cms/cms_dd.o crypto/cms/cms_enc.o crypto/cms/cms_env.o \
    crypto/cms/cms_err.o crypto/cms/cms_io.o crypto/cms/cms_lib.o \
    crypto/cms/cms_sd.o crypto/comp/c_zlib.o crypto/comp/comp_err.o \
    crypto/comp/comp_lib.o crypto/conf/conf_api.o crypto/conf/conf_def.o \
    crypto/conf/conf_err.o crypto/conf/conf_lib.o crypto/conf/conf_mod.o \
    crypto/cpt_err.o crypto/cryptlib.o crypto/des/cfb64ede.o \
    crypto/des/cfb64enc.o crypto/des/cfb_enc.o crypto/des/des_enc-sparc.o \
    crypto/des/ecb3_enc.o crypto/des/ecb_enc.o crypto/des/ofb64ede.o \
    crypto/des/ofb64enc.o crypto/des/set_key.o crypto/des/xcbc_enc.o \
    crypto/dh/dh_ameth.o crypto/dh/dh_asn1.o crypto/dh/dh_check.o \
    crypto/dh/dh_err.o crypto/dh/dh_gen.o crypto/dh/dh_key.o \
    crypto/dh/dh_lib.o crypto/dh/dh_pmeth.o crypto/dsa/dsa_ameth.o \
    crypto/dsa/dsa_asn1.o crypto/dsa/dsa_err.o crypto/dsa/dsa_gen.o \
    crypto/dsa/dsa_key.o crypto/dsa/dsa_lib.o crypto/dsa/dsa_ossl.o \
    crypto/dsa/dsa_pmeth.o crypto/dsa/dsa_sign.o crypto/dsa/dsa_vrf.o \
    crypto/dso/dso_lib.o crypto/dso/dso_null.o crypto/dso/dso_openssl.o \
    crypto/engine/eng_ctrl.o crypto/engine/eng_err.o crypto/engine/eng_init.o \
    crypto/engine/eng_lib.o crypto/engine/eng_list.o crypto/engine/eng_pkey.o \
    crypto/engine/eng_table.o crypto/engine/tb_asnmth.o \
    crypto/engine/tb_cipher.o crypto/engine/tb_dh.o crypto/engine/tb_digest.o \
    crypto/engine/tb_dsa.o crypto/engine/tb_pkmeth.o crypto/engine/tb_rand.o \
    crypto/engine/tb_rsa.o crypto/err/err.o crypto/err/err_all.o \
    crypto/err/err_prn.o crypto/evp/bio_b64.o crypto/evp/bio_enc.o \
    crypto/evp/bio_md.o crypto/evp/c_all.o crypto/evp/c_allc.o \
    crypto/evp/c_alld.o crypto/evp/digest.o crypto/evp/e_aes.o \
    crypto/evp/e_bf.o crypto/evp/e_camellia.o crypto/evp/e_des.o \
    crypto/evp/e_des3.o crypto/evp/e_null.o crypto/evp/e_rc2.o \
    crypto/evp/e_xcbc_d.o crypto/evp/encode.o crypto/evp/evp_enc.o \
    crypto/evp/evp_err.o crypto/evp/evp_key.o crypto/evp/evp_lib.o \
    crypto/evp/evp_pbe.o crypto/evp/evp_pkey.o crypto/evp/m_dss.o \
    crypto/evp/m_dss1.o crypto/evp/m_md4.o crypto/evp/m_md5.o \
    crypto/evp/m_sha.o crypto/evp/m_sha1.o crypto/evp/m_sigver.o \
    crypto/evp/names.o crypto/evp/p5_crpt.o crypto/evp/p5_crpt2.o \
    crypto/evp/p_lib.o crypto/evp/p_sign.o crypto/evp/p_verify.o \
    crypto/evp/pmeth_fn.o crypto/evp/pmeth_gn.o crypto/evp/pmeth_lib.o \
    crypto/ex_data.o crypto/hmac/hm_ameth.o crypto/hmac/hm_pmeth.o \
    crypto/hmac/hmac.o crypto/lhash/lhash.o crypto/md4/md4_dgst.o \
    crypto/md5/md5_dgst.o crypto/mem.o crypto/mem_dbg.o crypto/modes/cbc128.o \
    crypto/modes/cfb128.o crypto/modes/ofb128.o crypto/o_dir.o \
    crypto/o_time.o crypto/objects/o_names.o crypto/objects/obj_dat.o \
    crypto/objects/obj_err.o crypto/objects/obj_lib.o \
    crypto/objects/obj_xref.o crypto/ocsp/ocsp_asn.o crypto/ocsp/ocsp_err.o \
    crypto/pem/pem_all.o crypto/pem/pem_err.o crypto/pem/pem_info.o \
    crypto/pem/pem_lib.o crypto/pem/pem_oth.o crypto/pem/pem_pk8.o \
    crypto/pem/pem_pkey.o crypto/pem/pem_x509.o crypto/pem/pem_xaux.o \
    crypto/pkcs12/p12_add.o crypto/pkcs12/p12_asn.o crypto/pkcs12/p12_attr.o \
    crypto/pkcs12/p12_crpt.o crypto/pkcs12/p12_decr.o crypto/pkcs12/p12_key.o \
    crypto/pkcs12/p12_mutl.o crypto/pkcs12/p12_p8d.o crypto/pkcs12/p12_p8e.o \
    crypto/pkcs12/p12_utl.o crypto/pkcs12/pk12err.o crypto/pkcs7/pk7_asn1.o \
    crypto/pkcs7/pk7_attr.o crypto/pkcs7/pk7_doit.o crypto/pkcs7/pk7_lib.o \
    crypto/pkcs7/pkcs7err.o crypto/rand/md_rand.o crypto/rand/rand_err.o \
    crypto/rand/rand_lib.o crypto/rand/rand_unix.o crypto/rand/randfile.o \
    crypto/rc2/rc2_cbc.o crypto/rc2/rc2_ecb.o crypto/rc2/rc2_skey.o \
    crypto/rc2/rc2cfb64.o crypto/rc2/rc2ofb64.o crypto/rsa/rsa_ameth.o \
    crypto/rsa/rsa_asn1.o crypto/rsa/rsa_eay.o crypto/rsa/rsa_err.o \
    crypto/rsa/rsa_gen.o crypto/rsa/rsa_lib.o crypto/rsa/rsa_none.o \
    crypto/rsa/rsa_oaep.o crypto/rsa/rsa_pk1.o crypto/rsa/rsa_pmeth.o \
    crypto/rsa/rsa_pss.o crypto/rsa/rsa_sign.o crypto/rsa/rsa_ssl.o \
    crypto/rsa/rsa_x931.o crypto/sha/sha1-sparcv9.o crypto/sha/sha1dgst.o \
    crypto/sha/sha256-sparcv9.o crypto/sha/sha256.o \
    crypto/sha/sha512-sparcv9.o crypto/sha/sha512.o crypto/sha/sha_dgst.o \
    crypto/sparccpuid.o crypto/sparcv9cap.o crypto/stack/stack.o \
    crypto/wanboot-stubs.o \
    crypto/ts/ts_err.o crypto/ui/ui_err.o crypto/x509/by_dir.o \
    crypto/x509/by_file.o crypto/x509/x509_att.o crypto/x509/x509_cmp.o \
    crypto/x509/x509_d2.o crypto/x509/x509_def.o crypto/x509/x509_err.o \
    crypto/x509/x509_ext.o crypto/x509/x509_lu.o crypto/x509/x509_obj.o \
    crypto/x509/x509_req.o crypto/x509/x509_trs.o crypto/x509/x509_txt.o \
    crypto/x509/x509_v3.o crypto/x509/x509_vfy.o crypto/x509/x509_vpm.o \
    crypto/x509/x509name.o crypto/x509/x509rset.o crypto/x509/x509type.o \
    crypto/x509/x_all.o crypto/x509v3/pcy_cache.o crypto/x509v3/pcy_data.o \
    crypto/x509v3/pcy_lib.o crypto/x509v3/pcy_map.o crypto/x509v3/pcy_node.o \
    crypto/x509v3/pcy_tree.o crypto/x509v3/v3_akey.o crypto/x509v3/v3_akeya.o \
    crypto/x509v3/v3_alt.o crypto/x509v3/v3_bcons.o crypto/x509v3/v3_bitst.o \
    crypto/x509v3/v3_conf.o crypto/x509v3/v3_cpols.o crypto/x509v3/v3_crld.o \
    crypto/x509v3/v3_enum.o crypto/x509v3/v3_extku.o crypto/x509v3/v3_genn.o \
    crypto/x509v3/v3_ia5.o crypto/x509v3/v3_info.o crypto/x509v3/v3_int.o \
    crypto/x509v3/v3_lib.o crypto/x509v3/v3_ncons.o crypto/x509v3/v3_ocsp.o \
    crypto/x509v3/v3_pci.o crypto/x509v3/v3_pcia.o crypto/x509v3/v3_pcons.o \
    crypto/x509v3/v3_pku.o crypto/x509v3/v3_pmaps.o crypto/x509v3/v3_prn.o \
    crypto/x509v3/v3_purp.o crypto/x509v3/v3_skey.o crypto/x509v3/v3_sxnet.o \
    crypto/x509v3/v3_utl.o crypto/x509v3/v3err.o ssl/s3_both.o ssl/s3_clnt.o \
    ssl/s3_enc.o ssl/s3_lib.o ssl/s3_pkt.o ssl/ssl_algs.o ssl/ssl_asn1.o \
    ssl/ssl_cert.o ssl/ssl_ciph.o ssl/ssl_err.o ssl/ssl_err2.o ssl/ssl_lib.o \
    ssl/ssl_rsa.o ssl/ssl_sess.o ssl/t1_enc.o ssl/t1_lib.o ssl/t1_reneg.o

# Linking of openssl bits for wanboot.
# Interface for wanboot is specified in mapfile.wanboot. Object files are
# compiled to have functions in separate sections, unused sections get
# discarded.
CREATE_BIG_OBJECT_FILE = ( \
    cd $(BUILD_DIR_WANBOOT); \
    $(LD) -o wanboot-openssl.o -r -M../../mapfile.wanboot -Breduce \
        -zdiscard-unused=sections,files -zguidance \
        $(WANBOOT_OBJS); \
    )

$(BUILD_DIR_WANBOOT)/.built:	COMPONENT_POST_BUILD_ACTION = \
    ($(CREATE_BIG_OBJECT_FILE); )

# OpenSSL uses sections man[1357] by default so we must create the man
# directories we use for OpenSSL man pages in Solaris. Note that we patch the
# OpenSSL man page install script to use the correct directories.
MANDIR_SECTIONS =  $(PROTO_DIR)/usr/share/man/man1openssl
MANDIR_SECTIONS += $(PROTO_DIR)/usr/share/man/man3openssl
MANDIR_SECTIONS += $(PROTO_DIR)/usr/share/man/man5openssl
MANDIR_SECTIONS += $(PROTO_DIR)/usr/share/man/man7openssl

# We must create man page directories manually since we patched OpenSSL install
# code to install into manXopenssl instead of manX. Also, OpenSSL does not
# install into <dir>/$(MACH64) for 64-bit install so no such directory is
# created and Userland install code would fail when installing lint libraries.
COMPONENT_PRE_INSTALL_ACTION = ( $(MKDIR) $(MANDIR_SECTIONS); \
    $(MKDIR) $(PROTO_DIR)/usr/lib/$(MACH64); )

# The install_docs target will install man pages into $(PROTO_DIR)/$(MANDIR). We
# also add /usr/perl5/bin to PATH so that OpenSSL install code can locate the
# system pod2man. If not set, OpenSSL make would use an internal implementation
# from the tarball which would corrupt some man pages.
COMPONENT_INSTALL_ARGS += PATH=$(PATH) MANDIR=/usr/share/man

WANBOOT_TO      = $(PROTO_DIR)/lib/openssl/wanboot/$(MACH64)

# We could run OpenSSL install code for 32 bits only to process header files and
# manual pages. However, lint libraries depend on install stamps so we run
# install for 64 bit as well. Note that we must take built binary files from
# build directories, not from the proto area which contains whatever was
# installed first.
# OpenSSL for wanboot is built on sparc only.
ifeq ($(MACH), sparc)
install:	$(INSTALL_32_and_64) $(BUILD_DIR_WANBOOT)/.built
	$(MKDIR) -p $(WANBOOT_TO);
	$(CP) $(BUILD_DIR_WANBOOT)/wanboot-openssl.o $(WANBOOT_TO);
else
install:	$(INSTALL_32_and_64)
endif

# We need to modify the default lint flags to include patched opensslconf.h from
# the build directory. If we do not do that, lint will complain about md2.h
# which is not enabled by default but it is in our opensslconf.h.
LFLAGS_32 := -I$(BUILD_DIR_32)/include $(LINT_FLAGS) -lsoftcrypto
LFLAGS_64 := -I$(BUILD_DIR_64)/include $(LINT_FLAGS) -lsoftcrypto

# Set modified lint flags for our lint library targets.
$(BUILD_DIR_32)/llib-lcrypto.ln: LINT_FLAGS="$(LFLAGS_32)"
$(BUILD_DIR_32)/llib-lssl.ln: LINT_FLAGS="$(LFLAGS_32)"
$(BUILD_DIR_64)/llib-lcrypto.ln: LINT_FLAGS="$(LFLAGS_64)"
$(BUILD_DIR_64)/llib-lssl.ln: LINT_FLAGS="$(LFLAGS_64)"

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include $(WS_TOP)/make-rules/depend.mk
