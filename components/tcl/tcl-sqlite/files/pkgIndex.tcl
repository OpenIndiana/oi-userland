#
# Tcl package index file
#
# Note sqlite*3* init specifically
#
global tcl_platform
if {$tcl_platform(wordSize) == 8} {
  package ifneeded sqlite3 3.13.0 \
    [list load [file join $dir amd64/libsqlite3.13.0.so] Sqlite3]
} else {
  package ifneeded sqlite3 3.13.0 \
    [list load [file join $dir libsqlite3.13.0.so] Sqlite3]
}
