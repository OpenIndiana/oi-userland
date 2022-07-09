#find $1 -name Makefile -exec sed -I 's/lsocket/luuid/g' {} \; ; find $1 -name Makefile -exec sed -I "s:rpath-link,\$(top_builddir)/lib:-no-undefined:g" {} \;
find $1 -name Makefile -exec sed -I 's:lsocket:luuid:g' {} \;
find $1 -name Makefile -exec sed -I 's:libext2fs.so:libext2fs.so \$(LIB)/libcom_err.so:g' {} \;
find $1 -name Makefile -exec sed -I "s:-Wl,-rpath-link,\$(top_builddir)/lib::g" {} \;
