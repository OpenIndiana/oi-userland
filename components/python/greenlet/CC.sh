#! /bin/sh

# Wrapper script to work-around the fact that for Python 2.6,
# /usr/lib/python2.6/config/Makefile always inserts -KPIC when
# building shared objects regardless of the compiler version.

GCC=/usr/gcc/4.7/bin/gcc

newargs=""
for arg in $@; do
	case ${arg} in
	'-KPIC')
		continue
		;;
	*)
		newargs="${newargs} ${arg}"
		;;
	esac
done

exec ${GCC} ${newargs}
