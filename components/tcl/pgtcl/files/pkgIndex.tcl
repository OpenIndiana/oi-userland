global tcl_platform
if {$tcl_platform(wordSize) == 8} {
  package ifneeded Pgtcl 2.6.3  [list load [file join $dir amd64/libpgtcl2.6.3.so]]
} else {
  package ifneeded Pgtcl 2.6.3  [list load [file join $dir libpgtcl2.6.3.so]]
}
package ifneeded sc_postgres 1.3 \
    [list source [file join $dir postgres-helpers.tcl]]
