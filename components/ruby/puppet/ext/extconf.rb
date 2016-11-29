require 'mkmf'
$CPPFLAGS = "-I/usr/include/bsm"
$LDFLAGS  = "-L/usr/lib"
$LOCAL_LIBS = "-lbsm"
create_makefile("PuppetAudit")
