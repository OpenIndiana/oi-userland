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

export NLSPATH=""
export TOPDIR="../../"
export NTHREADS=2
export NLOOPS=100
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
            --nthreads=*)
            NTHREADS=`echo $1 | sed "s,^--nthreads=\(.*\),\1,"`
            ;;
            --nloops=*)
            NLOOPS=`echo $1 | sed "s,^--nloops=\(.*\),\1,"`
            ;;
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

    export NTHREADS NLOOPS TOPDIR DO_CLEANUP

    if [ "$PRINT_HELP" = "yes" ] || [ "$UNKNOWN_ARG" = "yes" ] ; then
        echo "Usage [1]: `basename $0` [ --nthreads=<number-of-threads> ] [ --nloops=<number-of-loops> ] [ --topdir=\$(top_srcdir) ]"
		echo "Usage [2]: `basename $0` [ --cleanup ]"
		echo "Please set --nloops and --nthreads to something reasonable."
        exit 1
    fi
}

check_environment() {
    HERE="`pwd`"

    cd ${TOPDIR}/build/lib

    if [ ! -f rwstderr.cat ] ; then
	echo "Message catalog 'rwstderr.cat' missing or not found!"
	echo "Some tests will not perform correctly."
	return
    fi

    if [ ! -f rwstderr ] ; then
	cp -fp rwstderr.cat rwstderr
    fi

    export NLSPATH="`pwd`/rwstderr"

    cd ${HERE}
}

setup_index_html() {
    cat /dev/null > ${INDEX_HTML}
}

run_single_threaded_tests() {
    if [ "${DO_CLEANUP}" = "yes" ] ; then
	return
    fi

    echo "------------------------------------------------------------"
    echo "Test programs atomic_add and atomic_xchg take a very long"
    echo "time to run. Please be patient."
    echo "------------------------------------------------------------"

    for file in \
	"0.alloc" \
	"0.braceexp" \
	"0.char" \
	"0.cmdopts" \
	"0.ctype" \
	"0.fnmatch" \
	"0.inputiter" \
	"0.new" \
	"0.outputiter" \
	"0.printf" \
	"0.process" \
	"0.strncmp" \
	"0.valcmp" \
	"17.extensions" \
	"17.names" \
	"18.csetjmp" \
	"18.exception" \
	"18.limits.cvqual" \
	"18.limits.traps" \
	"18.numeric.special.float" \
	"18.numeric.special.int" \
	"18.setjmp" \
	"18.support.dynamic" \
	"18.support.rtti" \
	"19.cerrno" \
	"19.std.exceptions" \
	"20.auto.ptr" \
	"20.function.objects" \
	"20.operators" \
	"20.pairs" \
	"20.specialized" \
	"20.temp.buffer" \
	"21.cctype" \
	"21.cwchar" \
	"21.cwctype" \
	"21.string.access" \
	"21.string.append" \
	"21.string.assign" \
	"21.string.capacity" \
	"21.string.compare" \
	"21.string.cons" \
	"21.string.copy" \
	"21.string.erase" \
	"21.string.exceptions" \
	"21.string.find" \
	"21.string.find.first.not.of" \
	"21.string.find.first.of" \
	"21.string.find.last.not.of" \
	"21.string.find.last.of" \
	"21.string.insert" \
	"21.string.io" \
	"21.string.iterators" \
	"21.string.operators" \
	"21.string.op.plus" \
	"21.string.op.plus.equal" \
	"21.string.replace" \
	"21.string.replace.stdcxx-170" \
	"21.string.rfind" \
	"21.string.substr" \
	"21.string.swap" \
	"22.locale.codecvt.length" \
	"22.locale.codecvt.out" \
	"22.locale.ctype" \
	"22.locale.ctype.is" \
	"22.locale.ctype.narrow" \
	"22.locale.ctype.scan" \
	"22.locale.ctype.tolower" \
	"22.locale.ctype.toupper" \
	"22.locale.ctype.widen" \
	"22.locale.messages" \
	"22.locale.money.get" \
	"22.locale.moneypunct" \
	"22.locale.money.put" \
	"22.locale.num.get" \
	"22.locale.numpunct" \
	"22.locale.num.put" \
	"22.locale.time.get" \
	"22.locale.time.put" \
	"23.bitset" \
	"23.bitset.cons" \
	"23.deque.iterators" \
	"23.deque.modifiers" \
	"23.deque.special" \
	"23.list.assign" \
	"23.list.capacity" \
	"23.list.cons" \
	"23.list.erase" \
	"23.list.insert" \
	"23.list.iterators" \
	"23.list.special" \
	"23.vector.allocator" \
	"23.vector.capacity" \
	"23.vector.cons" \
	"23.vector.modifiers" \
	"24.istream.iterator" \
	"25.adjacent.find" \
	"25.binary.search" \
	"25.copy" \
	"25.equal" \
	"25.equal.range" \
	"25.fill" \
	"25.find" \
	"25.find.end" \
	"25.find.first" \
	"25.for.each" \
	"25.generate" \
	"25.heap" \
	"25.includes" \
	"25.lex.comparison" \
	"25.libc" \
	"25.lower.bound" \
	"25.merge" \
	"25.min.max" \
	"25.mismatch" \
	"25.nth.element" \
	"25.partial.sort" \
	"25.partitions" \
	"25.permutation" \
	"25.random.shuffle" \
	"25.remove" \
	"25.replace" \
	"25.reverse" \
	"25.rotate" \
	"25.search" \
	"25.set.difference" \
	"25.set.intersection" \
	"25.set.sym.difference" \
	"25.set.union" \
	"25.sort" \
	"25.swap" \
	"25.transform" \
	"25.unique" \
	"25.upper.bound" \
	"26.accumulate" \
	"26.adjacent.diff" \
	"26.class.gslice" \
	"26.c.math" \
	"26.gslice.array.cassign" \
	"26.indirect.array" \
	"26.inner.product" \
	"26.mask.array" \
	"26.partial.sum" \
	"26.valarray.cassign" \
	"26.valarray.cons" \
	"26.valarray.transcend" \
	"27.filebuf.codecvt" \
	"27.forward" \
	"27.istream.fmat.arith" \
	"27.istream.manip" \
	"27.istream.readsome" \
	"27.istream.sentry" \
	"27.istream.unformatted.get" \
	"27.objects" \
	"27.ostream" \
	"27.stringbuf.virtuals" \
	"2.smartptr.shared" \
	"2.smartptr.weak" \
	"8.cstdint"
    do
	echo "------------------------------------------------------------"
	if [ -f ${file} ] ; then
	    echo -n "Running test program ${file} ... "
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
	    pat=`cat ${file}.out | egrep 'ASSERTION|ERROR|FATAL'`
	    if [ "x${pat}" != "x" ] ; then
		echo "############################################################"
		tail -9 ${file}.out | egrep 'ASSERTION|ERROR|FATAL' | egrep '%'
		echo "############################################################"
	    fi
	else
	    echo "Test program ${file} not found. Skipping."
	fi
	echo "------------------------------------------------------------"
    done
}

run_mt_tests() {
    if [ "${DO_CLEANUP}" = "yes" ] ; then
	return
    fi

    for file in \
	"19.exceptions.mt" \
	"20.temp.buffer.mt" \
	"21.string.cons.mt" \
	"21.string.push_back.mt" \
	"22.locale.codecvt.mt" \
	"22.locale.cons.mt" \
	"22.locale.ctype.mt" \
	"22.locale.globals.mt" \
	"22.locale.messages.mt" \
	"22.locale.money.get.mt" \
	"22.locale.moneypunct.mt" \
	"22.locale.money.put.mt" \
	"22.locale.num.get.mt" \
	"22.locale.numpunct.mt" \
	"22.locale.num.put.mt" \
	"22.locale.statics.mt" \
	"22.locale.time.get.mt" \
	"22.locale.time.put.mt" \
	"atomic_add" \
	"atomic_xchg"
    do
	echo "------------------------------------------------------------"
	if [ -f ${file} ] ; then
	    echo -n "Running test program ${file} ... "
	    logfile="${file}.out"
	    if [ "x${file}" = "x22.locale.num.put.mt" ] ; then
		./${file} --nthreads=2 --nloops=10 --nlocales=8 > ${logfile} 2>&1
	    else
		./${file} --nthreads=${NTHREADS} --nloops=${NLOOPS} > ${logfile} 2>&1
	    fi
	    ret=$?
	    if [ ${ret} -eq 0 ] ; then
		echo "SUCCESS."
	    else
		echo "FAIL."
	    fi
	    echo "<a href=\"${file}.out\">${file}.out</a>" >> ${INDEX_HTML}
	    echo "</br>" >> ${INDEX_HTML}
	    pat=`cat ${file}.out | egrep 'ASSERTION|ERROR|FATAL'`
	    if [ "x${pat}" != "x" ] ; then
		echo "############################################################"
		tail -9 ${file}.out | egrep 'ASSERTION|ERROR|FATAL' | egrep '%'
		echo "############################################################"
	    fi
	else
	    echo "Test program ${file} not found. Skipping."
	fi
	echo "------------------------------------------------------------"
    done
}

do_cleanup() {
    if [ "${DO_CLEANUP}" = "no" ] ; then
	return
    fi

    for file in \
	"0.alloc" \
	"0.braceexp" \
	"0.char" \
	"0.cmdopts" \
	"0.ctype" \
	"0.fnmatch" \
	"0.inputiter" \
	"0.new" \
	"0.outputiter" \
	"0.printf" \
	"0.process" \
	"0.strncmp" \
	"0.valcmp" \
	"17.extensions" \
	"17.names" \
	"18.csetjmp" \
	"18.exception" \
	"18.limits.cvqual" \
	"18.limits.traps" \
	"18.numeric.special.float" \
	"18.numeric.special.int" \
	"18.setjmp" \
	"18.support.dynamic" \
	"18.support.rtti" \
	"19.cerrno" \
	"19.exceptions.mt" \
	"19.std.exceptions" \
	"20.auto.ptr" \
	"20.function.objects" \
	"20.operators" \
	"20.pairs" \
	"20.specialized" \
	"20.temp.buffer" \
	"20.temp.buffer.mt" \
	"21.cctype" \
	"21.cwchar" \
	"21.cwctype" \
	"21.string.access" \
	"21.string.append" \
	"21.string.assign" \
	"21.string.capacity" \
	"21.string.compare" \
	"21.string.cons" \
	"21.string.cons.mt" \
	"21.string.copy" \
	"21.string.erase" \
	"21.string.exceptions" \
	"21.string.find" \
	"21.string.find.first.not.of" \
	"21.string.find.first.of" \
	"21.string.find.last.not.of" \
	"21.string.find.last.of" \
	"21.string.insert" \
	"21.string.io" \
	"21.string.iterators" \
	"21.string.operators" \
	"21.string.op.plus" \
	"21.string.op.plus.equal" \
	"21.string.push_back.mt" \
	"21.string.replace" \
	"21.string.replace.stdcxx-170" \
	"21.string.rfind" \
	"21.string.substr" \
	"21.string.swap" \
	"22.locale.codecvt.length" \
	"22.locale.codecvt.mt" \
	"22.locale.codecvt.out" \
	"22.locale.cons.mt" \
	"22.locale.ctype" \
	"22.locale.ctype.is" \
	"22.locale.ctype.mt" \
	"22.locale.ctype.narrow" \
	"22.locale.ctype.scan" \
	"22.locale.ctype.tolower" \
	"22.locale.ctype.toupper" \
	"22.locale.ctype.widen" \
	"22.locale.globals.mt" \
	"22.locale.messages" \
	"22.locale.messages.mt" \
	"22.locale.money.get" \
	"22.locale.money.get.mt" \
	"22.locale.moneypunct" \
	"22.locale.moneypunct.mt" \
	"22.locale.money.put" \
	"22.locale.money.put.mt" \
	"22.locale.num.get" \
	"22.locale.num.get.mt" \
	"22.locale.numpunct" \
	"22.locale.numpunct.mt" \
	"22.locale.num.put" \
	"22.locale.num.put.mt" \
	"22.locale.statics.mt" \
	"22.locale.time.get" \
	"22.locale.time.get.mt" \
	"22.locale.time.put" \
	"22.locale.time.put.mt" \
	"23.bitset" \
	"23.bitset.cons" \
	"23.deque.iterators" \
	"23.deque.modifiers" \
	"23.deque.special" \
	"23.list.assign" \
	"23.list.capacity" \
	"23.list.cons" \
	"23.list.erase" \
	"23.list.insert" \
	"23.list.iterators" \
	"23.list.special" \
	"23.vector.allocator" \
	"23.vector.capacity" \
	"23.vector.cons" \
	"23.vector.modifiers" \
	"24.istream.iterator" \
	"25.adjacent.find" \
	"25.binary.search" \
	"25.copy" \
	"25.equal" \
	"25.equal.range" \
	"25.fill" \
	"25.find" \
	"25.find.end" \
	"25.find.first" \
	"25.for.each" \
	"25.generate" \
	"25.heap" \
	"25.includes" \
	"25.lex.comparison" \
	"25.libc" \
	"25.lower.bound" \
	"25.merge" \
	"25.min.max" \
	"25.mismatch" \
	"25.nth.element" \
	"25.partial.sort" \
	"25.partitions" \
	"25.permutation" \
	"25.random.shuffle" \
	"25.remove" \
	"25.replace" \
	"25.reverse" \
	"25.rotate" \
	"25.search" \
	"25.set.difference" \
	"25.set.intersection" \
	"25.set.sym.difference" \
	"25.set.union" \
	"25.sort" \
	"25.swap" \
	"25.transform" \
	"25.unique" \
	"25.upper.bound" \
	"26.accumulate" \
	"26.adjacent.diff" \
	"26.class.gslice" \
	"26.c.math" \
	"26.gslice.array.cassign" \
	"26.indirect.array" \
	"26.inner.product" \
	"26.mask.array" \
	"26.partial.sum" \
	"26.valarray.cassign" \
	"26.valarray.cons" \
	"26.valarray.transcend" \
	"26.valarray.transcend.out" \
	"27.filebuf.codecvt" \
	"27.forward" \
	"27.istream.fmat.arith" \
	"27.istream.manip" \
	"27.istream.readsome" \
	"27.istream.sentry" \
	"27.istream.unformatted.get" \
	"27.objects" \
	"27.ostream" \
	"27.stringbuf.virtuals" \
	"2.smartptr.shared" \
	"2.smartptr.weak" \
	"8.cstdint" \
	"atomic_add" \
	"atomic_xchg"
    do
	rm -f "${file}.out"
    done

    rm -f ${INDEX_HTML}
    rm -f core
}

check_args $@
check_environment
setup_index_html
run_single_threaded_tests
run_mt_tests
do_cleanup

exit 0


