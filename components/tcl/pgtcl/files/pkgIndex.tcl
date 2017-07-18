global tcl_platform
if {$tcl_platform(wordSize) == 8} {
  package ifneeded Pgtcl 2.2  [list load [file join $dir amd64/libpgtcl2.2.0.so]]
} else {
  package ifneeded Pgtcl 2.2  [list load [file join $dir libpgtcl2.2.0.so]]
}
package ifneeded sc_postgres 1.2 \
    [list source [file join $dir postgres-helpers.tcl]]
