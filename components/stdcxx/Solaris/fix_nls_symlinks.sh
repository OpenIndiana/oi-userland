#!/bin/bash
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
#
# Copyright 2009 Sun Microsystems, Inc.  All rights reserved.
# Use is subject to license terms.
#
# ident	"@(#)fix_nls_symlinks.sh	1.1	09/08/07 SMI"
#

if [ ! -f ../Solaris/readlink.sh ] ; then
    echo "readlink.sh script not found!"
    exit 1
fi

if [ -d build/nls ] ; then
    cp -fp ../Solaris/readlink.sh build/nls/
    cd build/nls

    if [ ! -f readlink.sh ] ; then
        echo "readlink.sh script not found in the nls directory!"
        exit 1
    fi

    chmod 0755 readlink.sh

    for file in \
        "af_ZA.ISO-8859-1" \
        "ar_AE.ISO-8859-6" \
        "ar_BH.ISO-8859-6" \
        "ar_DZ.ISO-8859-6" \
        "ar_EG.ISO-8859-6" \
        "ar_IN.UTF-8" \
        "ar_IQ.ISO-8859-6" \
        "ar_JO.ISO-8859-6" \
        "ar_KW.ISO-8859-6" \
        "ar_LB.ISO-8859-6" \
        "ar_LY.ISO-8859-6" \
        "ar_MA.ISO-8859-6" \
        "ar_OM.ISO-8859-6" \
        "ar_QA.ISO-8859-6" \
        "ar_SA.ISO-8859-6" \
        "ar_SD.ISO-8859-6" \
        "ar_SY.ISO-8859-6" \
        "ar_TN.ISO-8859-6" \
        "ar_YE.ISO-8859-6" \
        "be_BY.CP1251" \
        "bg_BG.CP1251" \
        "br_FR.ISO-8859-1" \
        "bs_BA.ISO-8859-2" \
        "ca_ES.ISO-8859-1" \
        "ca_ES.ISO-8859-15@euro" \
        "cs_CZ.ISO-8859-2" \
        "cy_GB.ISO-8859-14" \
        "da_DK.ISO-8859-1" \
        "de_AT.ISO-8859-1" \
        "de_AT.ISO-8859-15@euro" \
        "de_BE.ISO-8859-1" \
        "de_BE.ISO-8859-15@euro" \
        "de_CH.ISO-8859-1" \
        "de_DE.ISO-8859-1" \
        "de_DE.UTF-8" \
        "de_DE.ISO-8859-15@euro" \
        "de_LU.ISO-8859-1" \
        "de_LU.ISO-8859-15@euro" \
        "el_GR.ISO-8859-7" \
        "en_AU.ISO-8859-1" \
        "en_BW.ISO-8859-1" \
        "en_CA.ISO-8859-1" \
        "en_DK.ISO-8859-1" \
        "en_GB.ISO-8859-1" \
        "en_HK.ISO-8859-1" \
        "en_IE.ISO-8859-1" \
        "en_IE.ISO-8859-15@euro" \
        "en_IN.UTF-8" \
        "en_NZ.ISO-8859-1" \
        "en_PH.ISO-8859-1" \
        "en_SG.ISO-8859-1" \
        "en_US.ISO-8859-1" \
        "en_US.ANSI_X3.4-1968" \
        "en_US.UTF-8" \
        "en_ZA.ISO-8859-1" \
        "en_ZW.ISO-8859-1" \
        "es_AR.ISO-8859-1" \
        "es_BO.ISO-8859-1" \
        "es_CL.ISO-8859-1" \
        "es_CO.ISO-8859-1" \
        "es_CR.ISO-8859-1" \
        "es_DO.ISO-8859-1" \
        "es_EC.ISO-8859-1" \
        "es_ES.ISO-8859-1" \
        "es_ES.ISO-8859-15@euro" \
        "es_GT.ISO-8859-1" \
        "es_HN.ISO-8859-1" \
        "es_MX.ISO-8859-1" \
        "es_NI.ISO-8859-1" \
        "es_PA.ISO-8859-1" \
        "es_PE.ISO-8859-1" \
        "es_PR.ISO-8859-1" \
        "es_PY.ISO-8859-1" \
        "es_SV.ISO-8859-1" \
        "es_US.ISO-8859-1" \
        "es_UY.ISO-8859-1" \
        "es_VE.ISO-8859-1" \
        "et_EE.ISO-8859-1" \
        "eu_ES.ISO-8859-1" \
        "eu_ES.ISO-8859-15@euro" \
        "fa_IR.UTF-8" \
        "fi_FI.ISO-8859-1" \
        "fi_FI.ISO-8859-15@euro" \
        "fo_FO.ISO-8859-1" \
        "fr_BE.ISO-8859-1" \
        "fr_BE.ISO-8859-15@euro" \
        "fr_CA.ISO-8859-1" \
        "fr_CH.ISO-8859-1" \
        "fr_FR.ISO-8859-1" \
        "fr_FR.UTF-8" \
        "fr_FR.ISO-8859-15@euro" \
        "fr_LU.ISO-8859-1" \
        "fr_LU.ISO-8859-15@euro" \
        "ga_IE.ISO-8859-1" \
        "ga_IE.ISO-8859-15@euro" \
        "gl_ES.ISO-8859-1" \
        "gl_ES.ISO-8859-15@euro" \
        "gv_GB.ISO-8859-1" \
        "he_IL.ISO-8859-8" \
        "hi_IN.UTF-8" \
        "hr_HR.ISO-8859-2" \
        "hu_HU.ISO-8859-2" \
        "id_ID.ISO-8859-1" \
        "is_IS.ISO-8859-1" \
        "it_CH.ISO-8859-1" \
        "it_IT.ISO-8859-1" \
        "it_IT.ISO-8859-15@euro" \
        "iw_IL.ISO-8859-8" \
        "ja_JP.EUC-JP" \
        "ja_JP.UTF-8" \
        "ja_JP.Shift_JIS" \
        "ka_GE.GEORGIAN-PS" \
        "kl_GL.ISO-8859-1" \
        "ko_KR.EUC-KR" \
        "ko_KR.UTF-8" \
        "kw_GB.ISO-8859-1" \
        "lt_LT.ISO-8859-13" \
        "lv_LV.ISO-8859-13" \
        "mi_NZ.ISO-8859-13" \
        "mk_MK.ISO-8859-5" \
        "mr_IN.UTF-8" \
        "ms_MY.ISO-8859-1" \
        "mt_MT.ISO-8859-3" \
        "nl_BE.ISO-8859-1" \
        "nl_BE.ISO-8859-15@euro" \
        "nl_NL.ISO-8859-1" \
        "nl_NL.ISO-8859-15@euro" \
        "nn_NO.ISO-8859-1" \
        "no_NO.ISO-8859-1" \
        "oc_FR.ISO-8859-1" \
        "pl_PL.ISO-8859-2" \
        "pt_BR.ISO-8859-1" \
        "pt_PT.ISO-8859-1" \
        "pt_PT.ISO-8859-15@euro" \
        "ro_RO.ISO-8859-2" \
        "ru_RU.ISO-8859-5" \
        "ru_RU.KOI8-R" \
        "ru_RU.UTF-8" \
        "ru_UA.KOI8-U" \
        "sk_SK.ISO-8859-2" \
        "sl_SI.ISO-8859-2" \
        "sq_AL.ISO-8859-1" \
        "sr_YU.ISO-8859-2" \
        "sr_YU.ISO-8859-5@cyrillic" \
        "sv_FI.ISO-8859-1" \
        "sv_FI.ISO-8859-15@euro" \
        "sv_SE.ISO-8859-1" \
        "ta_IN.UTF-8" \
        "te_IN.UTF-8" \
        "tg_TJ.KOI8-T" \
        "th_TH.TIS-620" \
        "tl_PH.ISO-8859-1" \
        "tr_TR.ISO-8859-9" \
        "uk_UA.KOI8-U" \
        "ur_PK.UTF-8" \
        "uz_UZ.ISO-8859-1" \
        "vi_VN.UTF-8" \
        "yi_US.CP1255" \
        "zh_CN.GB2312" \
        "zh_CN.GB18030" \
        "zh_CN.GBK" \
        "zh_CN.UTF-8" \
        "zh_HK.BIG5-HKSCS" \
        "zh_TW.BIG5" \
        "zh_TW.EUC-TW"
    do
        cd ${file}
        if [ -L "LC_CTYPE" ] ; then
            echo "Fixing symlink for ${file}."
            filename=`../readlink.sh "LC_CTYPE"`
            linkname=`basename ${filename}`
            if [ -f "../${linkname}" ] ; then
                rm LC_CTYPE
                ln -sf "../${linkname}" "LC_CTYPE"
            fi
        fi
        cd - > /dev/null 2>&1
    done
else
    echo "\$(topdir)/build/nls directory was not found!"
    echo "This scriptmust be run from the toplevel build directory."
    exit 1
fi

exit 0

