#!/usr/bin/bash
# Generate illumos data files describing system calls and structures
# found in core files.
CW=/opt/onbld/bin/i386/cw
GENOFFSETS=/opt/onbld/bin/genoffsets
TMPDIR=${COMPONENT_DIR}/tmp
CTFSTABS=/opt/onbld/bin/i386/ctfstabs
CTFCONVERT=/opt/onbld/bin/i386/ctfconvert
GENOFFSETS_CFLAGS="-gdwarf-2 -_gcc=-fno-eliminate-unused-debug-symbols -_gcc=-fno-eliminate-unused-debug-types"
EGREP=/usr/gnu/bin/egrep
GCC=/usr/gcc/${GCC_VERSION}/bin/gcc
CFLAGS32=-m32
CFLAGS64=-m64
OOCEBIN=/usr/bin

function generate {

    # System call table
    {   
        cat << EOM
<?xml version="1.0"?>
<!DOCTYPE feature SYSTEM "gdb-syscalls.dtd">
<syscalls_info>
EOM
        $EGREP $'^#define\tSYS_.*[0-9]$' /usr/include/sys/syscall.h \
            | while read _ call num; do
                printf '  <syscall name="%s" number="%d"/>\n' \
                    ${call#SYS_} $num
        done

        echo "</syscalls_info>"
    } > $TMPDIR/syscalls.xml
    echo $TMPDIR/syscalls.xml
    for arch in i386 amd64; do
        cp ${TMPDIR}/syscalls.xml \
            ${SOURCE_DIR}/gdb/syscalls/$arch-illumos.xml \
            || echo "Could not install $arch system call table"
    done

    for bits in 32 64; do
        flags=CFLAGS$bits
        $GENOFFSETS -s $CTFSTABS -r $CTFCONVERT \
            $CW --primary gcc,${GCC},gnu --noecho -- \
            $GENOFFSETS_CFLAGS ${!flags} \
            < ${COMPONENT_DIR}/Solaris/offsets.in > $TMPDIR/offsets$bits.h
    done
    {   
        sed < $TMPDIR/offsets32.h 's/\t0x/_32&/'
        sed < $TMPDIR/offsets64.h 's/\t0x/_64&/'
        $EGREP $'define\tPR(FN|ARG)SZ' /usr/include/sys/old_procfs.h
    } > ${SOURCE_DIR}/bfd/illumos-offsets.h

}

[ ! -d ${TMPDIR} ] && mkdir ${TMPDIR}
generate
rm -rf ${TMPDIR}
