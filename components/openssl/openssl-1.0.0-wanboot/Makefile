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
# Copyright (c) 2012, Oracle and/or its affiliates. All rights reserved.


#
# This component is not to be installed. It is used from openssl-1.0.0
# to build static stand-alone OpenSSL binaries to link with wanboot.
#

include ../../../make-rules/shared-macros.mk

# COMPONENT_NAME, COMPONENT_VERSION, IPS_COMPONENT_VERSION and some other
# related macros definitions were moved to ../openssl-1.0.0/Makefile.version
# in order to keep OpenSSL versions in ../openssl-1.0.0 and 
# ../openssl-1.0.0-wanboot in sync
include ../openssl-1.0.0/Makefile.version

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk
include $(WS_TOP)/make-rules/lint-libraries.mk

PATH=$(SPRO_VROOT)/bin:/usr/bin:/usr/gnu/bin:/usr/perl5/bin

# OpenSSL does not use autoconf but its own configure system.
CONFIGURE_SCRIPT = $(SOURCE_DIR)/Configure

# This is to force OpenSSL's Configure script to use gmake for "make links". 
# Otherwise it fails with:
#     mksh: Fatal error in reader: Unmatched `(' on line
CONFIGURE_ENV += MAKE="$(GMAKE)"

CONFIGURE_OPTIONS =  -DNO_WINDOWS_BRAINDEATH
CONFIGURE_OPTIONS += -DNO_CHMOD -D_BOOT -DOPENSSL_NO_DTLS1
CONFIGURE_OPTIONS += no-cast
CONFIGURE_OPTIONS += no-dso
CONFIGURE_OPTIONS += no-ec
CONFIGURE_OPTIONS += no-ecdh
CONFIGURE_OPTIONS += no-ecdsa
CONFIGURE_OPTIONS += no-mdc2
CONFIGURE_OPTIONS += no-rc3
CONFIGURE_OPTIONS += no-rc4
CONFIGURE_OPTIONS += no-rc5
CONFIGURE_OPTIONS += no-ripemd
CONFIGURE_OPTIONS += no-idea
CONFIGURE_OPTIONS += no-hw
CONFIGURE_OPTIONS += no-threads
CONFIGURE_OPTIONS += no-shared
CONFIGURE_OPTIONS += no-seed
# We use both no-whirlpool and no-whrlpool since there is an inconsistency in
# the OpenSSL code and one needs both to build OpenSSL successfully with
# Whirlpool implementation removed.
CONFIGURE_OPTIONS += no-whirlpool
CONFIGURE_OPTIONS += no-whrlpool

# For wanboot, we only need 64-bit sparc binaries
CONFIGURE_OPTIONS +=	solaris64-sparcv9-cc-sunw

# OpenSSL has its own configure system which must be run from the fully
# populated source code directory. However, the Userland configuration phase is
# run from the build directory. So, we must get the full source code into the
# build directory.
COMPONENT_PRE_CONFIGURE_ACTION = \
    ( $(CLONEY) $(SOURCE_DIR) $(BUILD_DIR)/$(MACH$(BITS)); )

# File stubs.c stubs out several functions, that are not available for wanboot.
# We do not provide it in a form of a patch to ease future maintenance.
COMPONENT_PRE_BUILD_ACTION = \
    ( $(CP) -fp files/stubs.c       $(@D)/crypto/; )

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
    crypto/stubs.o crypto/ts/ts_err.o crypto/ui/ui_err.o crypto/x509/by_dir.o \
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
# Interface for wanboot is specified in mapfile. Object files are compiled 
# to have functions in separate sections, unused sections get discarded.
CREATE_BIG_OBJECT_FILE = ( \
    cd $(BUILD_DIR)/$(MACH64); \
    $(LD) -o wanboot-openssl.o -r -M../../mapfile -Breduce \
        -zdiscard-unused=sections,files -zguidance \
        $(WANBOOT_OBJS); \
    )

COMPONENT_POST_BUILD_ACTION = \
    ($(CREATE_BIG_OBJECT_FILE); )


# For wanboot, we only need 64-bit sparc binaries
build_sparc:		$(BUILD_64)

build_i386:
	@echo "Not available"

build:			build_$(MACH)

install:
	@echo "This component is not to be installed individually."

publish:
	@echo "This component is not to be published individually."

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include $(WS_TOP)/make-rules/depend.mk
