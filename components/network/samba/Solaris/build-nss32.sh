#!/bin/ksh
#
# Build a 32-bit nss_winbind.so.1 from the Samba nsswitch sources, using the
# 64-bit config.h with the SIZEOF_* values of the 32-bit ABI.
#
# usage: build-nss32.sh <samba source dir> <waf bin/default dir> <out dir> [cc]
set -e
SRC=$1 BLD=$2 OUT=$3 CC=${4:-gcc}
SOCKDIR=$(gsed -n "s/^WINBINDD_SOCKET_DIR = .\\(.*\\).$/\\1/p" $BLD/../c4che/default_cache.py)
[ -n "$SOCKDIR" ] || SOCKDIR=/var/samba/run/winbindd
CPPDEFS="-D_LARGEFILE64_SOURCE -D_XOPEN_SOURCE=600 -D__EXTENSIONS__=1 -D_XPG6"
rm -rf $OUT; mkdir -p $OUT/include
cat > $OUT/probe.c <<EOP
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <sys/types.h>
#include <time.h>
#define P(n,t) printf("%s %u\n", n, (unsigned)sizeof (t))
int main(void) { P("BOOL",bool); P("CHAR",char); P("INT",int);
P("LONG_LONG",long long); P("LONG",long); P("SHORT",short);
P("SIZE_T",size_t); P("SSIZE_T",ssize_t); P("VOID_P",void *);
P("OFF_T",off_t); P("DEV_T",dev_t); P("INO_T",ino_t); P("TIME_T",time_t);
return 0; }
EOP
$CC -m32 $CPPDEFS -o $OUT/probe $OUT/probe.c
cp $BLD/include/config.h $OUT/include/config.h
$OUT/probe | while read n v; do
	gsed -i "s/^#define SIZEOF_$n .*/#define SIZEOF_$n $v/" $OUT/include/config.h
done
gsed -i "/^#define SIZEOF_BLKCNT_T_8 /d" $OUT/include/config.h
cat > $OUT/shim.c <<EOP
/* rep_memset_explicit() from lib/replace/replace.c, used by ZERO_STRUCT */
#include <string.h>
void *rep_memset_explicit(void *block, int c, size_t size)
{
	void *ptr = memset(block, c, size);
	__asm__ volatile("" : : "g"(block) : "memory");
	return ptr;
}
EOP
$CC -m32 -fPIC -shared -O2 -std=c17 -fvisibility=hidden \
	-D__STDC_WANT_LIB_EXT1__=1 -D_SAMBA_BUILD_=4 -DHAVE_CONFIG_H=1 \
	-D_REENTRANT -D_POSIX_PTHREAD_SEMANTICS $CPPDEFS \
	-DWINBINDD_SOCKET_DIR=\"$SOCKDIR\" \
	-Wno-implicit-function-declaration -Wno-incompatible-pointer-types \
	-Wno-int-conversion \
	-I$OUT/include -I$SRC/lib/replace -I$BLD/lib/replace -I$SRC/nsswitch \
	-I$SRC -I$BLD -I$SRC/include -I$BLD/include/public -I$SRC/lib \
	-I$SRC/source3/include \
	$SRC/nsswitch/winbind_nss_solaris.c $SRC/nsswitch/winbind_nss_linux.c \
	$SRC/nsswitch/wb_common.c $OUT/shim.c \
	-Wl,-h,nss_winbind.so.1 -Wl,-z,defs -lsocket -lnsl -lrt -lc \
	-o $OUT/nss_winbind.so.1
