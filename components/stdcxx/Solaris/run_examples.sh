#!/bin/bash
#
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
#

unset LD_LIBRARY_PATH
unset LD_LIBRARY_PATH_32
unset LD_LIBRARY_PATH_64
unset LD_PRELOAD
unset LD_PRELOAD_32
unset LD_PRELOAD_64

export TOPDIR="../../"
export DO_CLEANUP="no"
export INDEX_HTML="index.html"
export LD_LIBRARY_PATH="../lib"
export LD_LIBRARY_PATH_32="../lib"
export LD_LIBRARY_PATH_64="../lib"

UNKNOWN_ARG=no
PRINT_HELP=no

check_args() {
    while [ "$#" -gt 0 ] ; do
        UNKNOWN_ARG=no
        case "$1" in
            --topdir=*)
            TOPDIR=`echo $1 | sed "s,^--topdir=\(.*\),\1,"`
            ;;
            --cleanup)
            DO_CLEANUP=yes
            ;;
            --help)
            PRINT_HELP=yes
			;;
            *)
            UNKNOWN_ARG=yes
            ;;
        esac

        if [ "${UNKNOWN_ARG}" = "yes" ] ; then
            echo "$1: Invalid argument"
            PRINT_HELP=yes
            shift
            continue
        fi

        shift
    done

    export TOPDIR DO_CLEANUP

    if [ "$PRINT_HELP" = "yes" ] || [ "$UNKNOWN_ARG" = "yes" ] ; then
        echo "Usage [1]: `basename $0` [ --topdir=\$(top_srcdir) ]"
		echo "Usage [2]: `basename $0` [ --cleanup ]"
        exit 1
    fi
}

setup_index_html() {
	cat /dev/null > ${INDEX_HTML}
}

run_examples() {
	if [ "${DO_CLEANUP}" = "yes" ] ; then
		return
	fi

	for file in \
		"accumulate" \
		"adj_diff" \
		"advance" \
		"alg1" \
		"alg2" \
		"alg3" \
		"alg4" \
		"alg5" \
		"alg6" \
		"alg7" \
		"auto_ptr" \
		"binary_search" \
		"binders" \
		"bitset" \
		"codecvt" \
		"codecvt1" \
		"collate" \
		"complex" \
		"complx" \
		"copyex" \
		"count" \
		"ctype" \
		"deque" \
		"distance" \
		"dynatype" \
		"equal" \
		"equal_range" \
		"failure" \
		"filebuf" \
		"fill" \
		"find" \
		"find_end" \
		"find_first_of" \
		"fmtflags_manip" \
		"for_each" \
		"fstream" \
		"funct_ob" \
		"generate" \
		"graph" \
		"gslice" \
		"gslice_array" \
		"has_facet" \
		"heap_ops" \
		"icecream" \
		"ifstream" \
		"includes" \
		"indirect_array" \
		"inner_product" \
		"insert_iterator" \
		"insert_wchar" \
		"isalnum" \
		"istream1" \
		"istreambuf_iterator" \
		"istringstream" \
		"istrstream" \
		"lex_compare" \
		"limits" \
		"list" \
		"locale" \
		"map" \
		"mask_array" \
		"max" \
		"max_elem" \
		"mbsrtowcs" \
		"memfunc" \
		"memfunref" \
		"merge" \
		"messages" \
		"mismatch" \
		"money_get" \
		"moneypunct" \
		"moneyput" \
		"multimap" \
		"multiset" \
		"mutex" \
		"negator" \
		"nthelem" \
		"num_get" \
		"numpunct" \
		"num_put" \
		"ostream" \
		"ostreambuf_iterator" \
		"partial_sort" \
		"partial_sum" \
		"partition" \
		"permutation" \
		"pnt2fnct" \
		"priority_queue" \
		"queue" \
		"radix" \
		"random_shuffle" \
		"remove" \
		"replace" \
		"reverse" \
		"reverse_iterator" \
		"rotate" \
		"rwexcept" \
		"search" \
		"set_diff" \
		"setex" \
		"set_intr" \
		"set_sym_diff" \
		"set_union" \
		"sieve" \
		"slice" \
		"slice_array" \
		"sort" \
		"stack" \
		"stdexcept" \
		"stringbuf" \
		"strstream" \
		"strstreambuf" \
		"swap" \
		"tele" \
		"teller" \
		"time_get" \
		"time_put" \
		"toupper" \
		"transform" \
		"ul_bound" \
		"unique" \
		"use_facet" \
		"valarray" \
		"vector" \
		"widwork" \
		"wostream" \
		"wstringstream"
	do
        echo "------------------------------------------------------------"
		if [ -f ${file} ] ; then
			echo -n "Running example program ${file} ..."
			logfile="${file}.out"
			./${file} > ${logfile} 2>&1
			ret=$?
			if [ ${ret} -eq 0 ] ; then
                echo "SUCCESS."
            else
                echo "FAIL."
			fi
			echo "<a href=\"${file}.out\">${file}.out</a>" >> ${INDEX_HTML}
			echo "</br>" >> ${INDEX_HTML}
		else
			echo "Example program ${file} not found. Skipping."
		fi
        echo "------------------------------------------------------------"
	done
}

run_examples_with_input() {
	if [ "${DO_CLEANUP}" = "yes" ] ; then
		return
	fi

	echo "------------------------------------------------------------"
	echo -n "Running example program spell ... "
	echo spelltest  | ./spell > ./spell.out 2>&1
    ret=$?
    if [ ${ret} -eq 0 ] ; then
        echo "SUCCESS."
    else
        echo "FAIL."
    fi
	echo "------------------------------------------------------------"
	echo "<a href=\"spell.out\">spell.out</a>" >> ${INDEX_HTML}
	echo "</br>" >> ${INDEX_HTML}

	echo "------------------------------------------------------------"
	echo -n "Running example program stocks ... "
	echo y y q | ./stocks >> ./stocks.out 2>&1
    ret=$?
    if [ ${ret} -eq 0 ] ; then
        echo "SUCCESS."
    else
        echo "FAIL."
    fi
    echo "------------------------------------------------------------"
	echo "<a href=\"stocks.out\">stocks.out</a>" >> ${INDEX_HTML}
	echo "</br>" >> ${INDEX_HTML}

	echo "------------------------------------------------------------"
	echo -n "Running example program calc ... "
	echo '5 1 2 + 4 * 3 - +' p q | ./calc >> ./calc.out 2>&1
    ret=$?
    if [ ${ret} -eq 0 ] ; then
        echo "SUCCESS."
    else
        echo "FAIL."
    fi
    echo "------------------------------------------------------------"
	echo "<a href=\"calc.out\">calc.out</a>" >> ${INDEX_HTML}
	echo "</br>" >> ${INDEX_HTML}

	echo "------------------------------------------------------------"
	echo -n "Running example program concord ... "
	echo 'this is a line of text'  | ./concord >> ./concord.out 2>&1
    ret=$?
    if [ ${ret} -eq 0 ] ; then
        echo "SUCCESS."
    else
        echo "FAIL."
    fi
    echo "------------------------------------------------------------"
	echo "<a href=\"concord.out\">concord.out</a>" >> ${INDEX_HTML}
	echo "</br>" >> ${INDEX_HTML}

	echo "------------------------------------------------------------"
	echo -n "Running example program money_manip ... "
	echo '1234.56' | ./money_manip >> ./money_manip.out 2>&1
    ret=$?
    if [ ${ret} -eq 0 ] ; then
        echo "SUCCESS."
    else
        echo "FAIL."
    fi
    echo "------------------------------------------------------------"
	echo "<a href=\"money_manip.out\">money_manip.out</a>" >> ${INDEX_HTML}
	echo "</br>" >> ${INDEX_HTML}

	echo "------------------------------------------------------------"
	echo -n "Running example program string ... "
	echo 'This is a test string' | ./string >> ./string.out 2>&1
    ret=$?
    if [ ${ret} -eq 0 ] ; then
        echo "SUCCESS."
    else
        echo "FAIL."
    fi
    echo "------------------------------------------------------------"
	echo "<a href=\"string.out\">string.out</a>" >> ${INDEX_HTML}
	echo "</br>" >> ${INDEX_HTML}

	echo "------------------------------------------------------------"
	echo -n "Running example program time_manip ... "
	echo 'Thu Sep 17 13:23:53 2009' | ./time_manip >> ./time_manip.out 2>&1
    ret=$?
    if [ ${ret} -eq 0 ] ; then
        echo "SUCCESS."
    else
        echo "FAIL."
    fi
    echo "------------------------------------------------------------"
	echo "<a href=\"time_manip.out\">time_manip.out</a>" >> ${INDEX_HTML}
	echo "</br>" >> ${INDEX_HTML}
}

do_cleanup() {
	if [ "${DO_CLEANUP}" = "no" ] ; then
		return
	fi

	for file in \
		"accumulate" \
		"adj_diff" \
		"advance" \
		"alg1" \
		"alg2" \
		"alg3" \
		"alg4" \
		"alg5" \
		"alg6" \
		"alg7" \
		"auto_ptr" \
		"binary_search" \
		"binders" \
		"bitset" \
		"calc" \
		"codecvt" \
		"codecvt1" \
		"collate" \
		"complex" \
		"complx" \
		"concord" \
		"copyex" \
		"count" \
		"ctype" \
		"deque" \
		"distance" \
		"dynatype" \
		"equal" \
		"equal_range" \
		"failure" \
		"filebuf" \
		"fill" \
		"find" \
		"find_end" \
		"find_first_of" \
		"fmtflags_manip" \
		"for_each" \
		"fstream" \
		"funct_ob" \
		"generate" \
		"graph" \
		"gslice" \
		"gslice_array" \
		"has_facet" \
		"heap_ops" \
		"icecream" \
		"ifstream" \
		"includes" \
		"indirect_array" \
		"inner_product" \
		"insert_iterator" \
		"insert_wchar" \
		"isalnum" \
		"istream1" \
		"istreambuf_iterator" \
		"istringstream" \
		"istrstream" \
		"lex_compare" \
		"limits" \
		"list" \
		"locale" \
		"map" \
		"mask_array" \
		"max" \
		"max_elem" \
		"mbsrtowcs" \
		"memfunc" \
		"memfunref" \
		"merge" \
		"messages" \
		"mismatch" \
		"money_get" \
		"moneypunct" \
		"moneyput" \
		"money_manip" \
		"multimap" \
		"multiset" \
		"mutex" \
		"negator" \
		"nthelem" \
		"num_get" \
		"numpunct" \
		"num_put" \
		"ostream" \
		"ostreambuf_iterator" \
		"partial_sort" \
		"partial_sum" \
		"partition" \
		"permutation" \
		"pnt2fnct" \
		"priority_queue" \
		"queue" \
		"radix" \
		"random_shuffle" \
		"remove" \
		"replace" \
		"reverse" \
		"reverse_iterator" \
		"rotate" \
		"rwexcept" \
		"search" \
		"set_diff" \
		"setex" \
		"set_intr" \
		"set_sym_diff" \
		"set_union" \
		"sieve" \
		"slice" \
		"slice_array" \
		"sort" \
		"spell" \
		"stack" \
		"stdexcept" \
		"stocks" \
		"string" \
		"stringbuf" \
		"strstream" \
		"strstreambuf" \
		"swap" \
		"tele" \
		"teller" \
		"time_get" \
		"time_manip" \
		"time_put" \
		"toupper" \
		"transform" \
		"ul_bound" \
		"unique" \
		"use_facet" \
		"valarray" \
		"vector" \
		"widwork" \
		"wostream" \
		"wstringstream"
	do
		rm -f "${file}.out"
	done

	rm -f core
}

check_args $@
run_examples
run_examples_with_input
do_cleanup

exit 0


