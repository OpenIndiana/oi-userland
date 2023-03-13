#
# Tcl package index file
#
# Note sqlite*3* init specifically
#
global tcl_platform
if {$tcl_platform(wordSize) == 8} {
  package ifneeded sqlite3 3.30.1 \
    [list load [file join $dir amd64/libsqlite3.30.1.so] Sqlite3]
} else {
  package ifneeded sqlite3 3.30.1 \
    [list load [file join $dir libsqlite3.30.1.so] Sqlite3]
}
