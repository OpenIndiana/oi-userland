#
# Tcl package index file
#
# Note sqlite*3* init specifically
#
global tcl_platform
if {$tcl_platform(wordSize) == 8} {
  package ifneeded sqlite3 3.7.17 \
    [list load [file join $dir amd64/libsqlite3.7.17.so] Sqlite3]
} else {
  package ifneeded sqlite3 3.7.17 \
    [list load [file join $dir libsqlite3.7.17.so] Sqlite3]
}

