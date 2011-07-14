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
# Copyright (c) 2009, 2011, Oracle and/or its affiliates. All rights reserved.
#

export PREFIX=""
export SRCDIR=""
export MACH64=""
export BUILDDIR=""
export COMPONENTDIR=""
export COMPONENTSRC=""
export LIBDIR=""
export INCDIR=""
export DOCDIR=""
export MAN3LIBDIR=""
export IS_64_BIT="no"
export unamep=`uname -p`
export SED="/usr/gnu/bin/sed"
export CP="/usr/gnu/bin/cp"

UNKNOWN_ARG=yes
PRINT_HELP=no

while [ "$#" -gt 0 ] ; do
    UNKNOWN_ARG=no
    case "$1" in
        -prefix=*)
        export PREFIX=`echo $1 | ${SED} "s,^-prefix=\(.*\),\1,"`
        ;;
        -builddir=*)
        export BUILDDIR=`echo $1 | ${SED} "s,^-builddir=\(.*\),\1,"`
        ;;
	-componentdir=*)
        export COMPONENTDIR=`echo $1 | ${SED} "s,^-componentdir=\(.*\),\1,"`
        ;;
	-componentsrc=*)
        export COMPONENTSRC=`echo $1 | ${SED} "s,^-componentsrc=\(.*\),\1,"`
	;;
	-srcdir=*)
        export SRCDIR=`echo $1 | ${SED} "s,^-srcdir=\(.*\),\1,"`
	;;
        -mach64=*)
        export MACH64=`echo $1 | ${SED} "s,^-mach64=\(.*\),\1,"`
        export IS_64_BIT="yes"
        ;;
        *)
        UNKNOWN_ARG=yes
        ;;
    esac

    if [ "$UNKNOWN_ARG" = "yes" ] ; then
        echo "$1: Invalid argument"
        PRINT_HELP=yes
        shift
        continue
    fi
    shift
done

if [ "x${PREFIX}" = "x" ] || [ "x${SRCDIR}" = "x" ] || [ "x${BUILDDIR}" = "x" ] || [ "x${COMPONENTDIR}" = "x" ] ; then
    PRINT_HELP=yes
fi

if [ "$PRINT_HELP" = "yes" ] || [ "$UNKNOWN_ARG" = "yes" ] ; then
    echo "Usage: `basename $0` -prefix=[ installation prefix ]"
    echo "      -builddir=[ \$(blddir) ]"
    echo "      -componentdir=[ toplevel component directory ]"
    echo "      -topdir=[ \$(top_blddir) ]"
    echo "      -srcdir=[ \$(top_srcdir) ]"
    echo "      [ -mach64=[ 64-bit ISA suffix ] ]"
    echo ""
    exit 1
fi

if [ "x${MACH64}" = "x" ] ; then
    export LIBDIR="${PREFIX}/lib"
else
    export LIBDIR="${PREFIX}/lib/${MACH64}"
fi

export INCDIR="${PREFIX}/include"
export NLSDIR="${PREFIX}/share/stdcxx4/locale"
export DOCDIR="${PREFIX}/share/doc/stdcxx4/html"
export MAN3LIBDIR="${PREFIX}/share/man/man3lib"
export PKGCONFIGDIR="${LIBDIR}/pkgconfig"

mkdir -p ${INCDIR} ${LIBDIR} ${NLSDIR} ${DOCDIR} ${MAN3LIBDIR} ${PKGCONFIGDIR}

if [ -f ${BUILDDIR}/.installed ] ; then
    rm -f ${BUILDDIR}/.installed
fi

cd ${BUILDDIR}/build/lib
${CP} -fp libstdcxx4.so.4.2.1 ${LIBDIR}/
cd ${LIBDIR}
elfedit -e 'dyn:delete RUNPATH' libstdcxx4.so.4.2.1
elfedit -e 'dyn:delete RPATH' libstdcxx4.so.4.2.1
chmod 0755 libstdcxx4.so.4.2.1

if [ -L libstdcxx4.so.4 ] ; then
    rm libstdcxx4.so.4
fi

if [ -L libstdcxx4.so ] ; then
    rm libstdcxx4.so
fi

ln -sf libstdcxx4.so.4.2.1 libstdcxx4.so.4
ln -sf libstdcxx4.so.4.2.1 libstdcxx4.so

cd ${COMPONENTDIR}

export TOPINCLUDE="${SRCDIR}/build/include"
export HEADER_FILE="stdcxx"

if [ "x${unamep}" = "xsparc" ] ; then
    if [ "x${IS_64_BIT}" = "xno" ] ; then
        export HEADER_FILE="${HEADER_FILE}_sparc.h"
    else
        export HEADER_FILE="${HEADER_FILE}_sparcv9.h"
    fi
else
    if [ "x${IS_64_BIT}" = "xno" ] ; then
        export HEADER_FILE="${HEADER_FILE}_i386.h"
    else
        export HEADER_FILE="${HEADER_FILE}_amd64.h"
    fi
fi

if [ ! -f ${TOPINCLUDE}/${HEADER_FILE} ] ; then
    echo "Platform-specific configuration file ${TOPINCLUDE}/${HEADER_FILE} missing or not found!"
    echo "This installation of libstdcxx is incomplete and broken!"
    exit 1
else
    echo "Installing platform-specific configuration file ${TOPINCLUDE}/${HEADER_FILE}."

    if [ -f "${COMPONENTDIR}/${HEADER_FILE}.sed" ] ; then
	rm -f "${COMPONENTDIR}/${HEADER_FILE}.sed"
    fi

    ${SED} -e "s#${COMPONENTDIR}/${COMPONENTSRC}/include#/usr/include/stdcxx4#g" ${TOPINCLUDE}/${HEADER_FILE} > "${COMPONENTDIR}/${HEADER_FILE}.sed"

    if [ ! -d  ${INCDIR}/stdcxx4/rw/config ] ; then
        mkdir -p ${INCDIR}/stdcxx4/rw/config
    fi

    ${CP} -fp "${COMPONENTDIR}/${HEADER_FILE}.sed" \
	${INCDIR}/stdcxx4/rw/config/${HEADER_FILE}
    if [ -f ${INCDIR}/stdcxx4/rw/config/rwconfig_std.h ] ; then
	rm -f ${INCDIR}/stdcxx4/rw/config/rwconfig_std.h
    fi
    ${CP} -fp ${COMPONENTDIR}/Solaris/rwconfig_std.h ${INCDIR}/stdcxx4/rw/config/
fi


if [ -f rwconfig_std.h.sed ] ; then
    rm -f rwconfig_std.h.sed
fi

if [ "x${MACH64}" = "x" ] ; then
    cd ${SRCDIR}
    if [ -f include/tr1/cstdint ] ; then
	${CP} -fp include/tr1/cstdint include/ansi/
    fi

    ${CP} -Rdf include/* ${INCDIR}/stdcxx4/
    ${CP} -fp ${COMPONENTDIR}/Solaris/libstdcxx4.pc ${PKGCONFIGDIR}/

    cd ${INCDIR}/stdcxx4/
    find . -type f -exec chmod 0644 {} \; > /dev/null 2>&1
    find . -type f -name "*.~1~" -exec rm -f {} \; > /dev/null 2>&1
    find . -type f -name "*.~2~" -exec rm -f {} \; > /dev/null 2>&1
    find . -type f -name "*.~3~" -exec rm -f {} \; > /dev/null 2>&1

    cd ${SRCDIR}/doc

    for file in \
        "banner.gif" \
        "index.html" \
        "rw.css" \
        "rwbanner.css" \
        "stdlibref" \
        "stdlibug"
    do
        if [ -f ${file} ] ; then
            ${CP} -fp ${file} ${DOCDIR}/${file}
            chmod 0644 ${DOCDIR}/${file}
        fi

        # Copy directories recursively, preserving symbolic links.
        if [ -d ${file} ] ; then
            ${CP} -rfP ${file} ${DOCDIR}/
	    chmod 0755 ${DOCDIR}/${file}
        fi
    done

    cd ${DOCDIR}

    find . -type f -name "*.html" -exec chmod 0644 {} \; > /dev/null 2>&1
    find . -type f -name "*.gif" -exec chmod 0644 {} \; > /dev/null 2>&1
    find . -type f -name "*.css" -exec chmod 0644 {} \; > /dev/null 2>&1

    cd ${COMPONENTDIR}
fi

if [ "x${MACH64}" != "x" ] ; then

    cd ${SRCDIR}/build/nls

    for file in \
        "ANSI_X3.4-1968" \
        "BIG5" \
        "BIG5-HKSCS" \
        "CP1251" \
        "CP1255" \
        "EUC-JP" \
        "EUC-KR" \
        "EUC-TW" \
        "GB18030" \
        "GB2312" \
        "GBK" \
        "GEORGIAN-PS" \
        "ISO-8859-1" \
        "ISO-8859-13" \
        "ISO-8859-14" \
        "ISO-8859-15" \
        "ISO-8859-2" \
        "ISO-8859-3" \
        "ISO-8859-5" \
        "ISO-8859-6" \
        "ISO-8859-7" \
        "ISO-8859-8" \
        "ISO-8859-9" \
        "KOI8-R" \
        "KOI8-T" \
        "KOI8-U" \
        "Shift_JIS" \
        "TIS-620" \
        "UTF-8" \
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
        "de_DE.ISO-8859-15@euro" \
        "de_DE.UTF-8" \
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
        "en_US.ANSI_X3.4-1968" \
        "en_US.ISO-8859-1" \
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
        "fr_FR.ISO-8859-15@euro" \
        "fr_FR.UTF-8" \
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
        "i18n.ctype.ANSI_X3.4-1968" \
        "i18n.ctype.BIG5" \
        "i18n.ctype.BIG5-HKSCS" \
        "i18n.ctype.CP1251" \
        "i18n.ctype.CP1255" \
        "i18n.ctype.EUC-JP" \
        "i18n.ctype.EUC-KR" \
        "i18n.ctype.EUC-TW" \
        "i18n.ctype.GB18030" \
        "i18n.ctype.GB2312" \
        "i18n.ctype.GBK" \
        "i18n.ctype.GEORGIAN-PS" \
        "i18n.ctype.ISO-8859-1" \
        "i18n.ctype.ISO-8859-13" \
        "i18n.ctype.ISO-8859-14" \
        "i18n.ctype.ISO-8859-15" \
        "i18n.ctype.ISO-8859-2" \
        "i18n.ctype.ISO-8859-3" \
        "i18n.ctype.ISO-8859-5" \
        "i18n.ctype.ISO-8859-6" \
        "i18n.ctype.ISO-8859-7" \
        "i18n.ctype.ISO-8859-8" \
        "i18n.ctype.KOI8-R" \
        "i18n.ctype.KOI8-T" \
        "i18n.ctype.KOI8-U" \
        "i18n.ctype.Shift_JIS" \
        "i18n.ctype.TIS-620" \
        "i18n.ctype.UTF-8" \
	"i18n.ctype.CP1255" \
        "id_ID.ISO-8859-1" \
        "is_IS.ISO-8859-1" \
        "it_CH.ISO-8859-1" \
        "it_IT.ISO-8859-1" \
        "it_IT.ISO-8859-15@euro" \
        "iw_IL.ISO-8859-8" \
        "ja_JP.EUC-JP" \
        "ja_JP.Shift_JIS" \
        "ja_JP.UTF-8" \
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
        "zh_CN.GB18030" \
        "zh_CN.GB2312" \
        "zh_CN.GBK" \
        "zh_CN.UTF-8" \
        "zh_HK.BIG5-HKSCS" \
        "zh_TW.BIG5" \
        "zh_TW.EUC-TW"
    do
        if [ -f ${file} ] ; then
            ${CP} -fp ${file} ${NLSDIR}/${file}
            chmod 0644 ${NLSDIR}/${file}
        fi

        if [ -d $file ] ; then
            ${CP} -rd ${file} ${NLSDIR}/
	    chmod 0755 ${NLSDIR}/${file}
        fi
    done

    cd ${COMPONENTDIR}
    ${SED} -e "s#\${prefix}/lib#\${prefix}/lib/${MACH64}#g" ${COMPONENTDIR}/Solaris/libstdcxx4.pc > libstdcxx4.pc.sed
    if [ -s libstdcxx4.pc.sed ] ; then
        ${CP} -fp libstdcxx4.pc.sed ${PKGCONFIGDIR}/libstdcxx4.pc
	rm -f libstdcxx4.pc.sed
    fi
fi

cd ${COMPONENTDIR}
${CP} -fp ${COMPONENTDIR}/Solaris/libstdcxx4.3lib ${MAN3LIBDIR}/libstdcxx4.3lib

echo "Proto area installation of stdcxx completed successfully."
touch ${BUILDDIR}/.installed

exit 0

