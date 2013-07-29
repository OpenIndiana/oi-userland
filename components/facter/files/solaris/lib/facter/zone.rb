
# A facter fact to determine if zones are supported
# on a system.

Facter.add("kernel_zone") do
  confine :operatingsystem => :Solaris
  setcode do
      virtinfo = %x{/sbin/virtinfo list -H -o class kernel-zone 2>/dev/null}
      case virtinfo.chomp!
      when "supported", "current", "parent"
          virtinfo
      else
	  "unsupported"
      end
  end
end

Facter.add("non_global_zone") do
  confine :operatingsystem => :Solaris
  setcode do
      virtinfo = %x{/sbin/virtinfo list -H -o class non-global-zone 2>/dev/null}
      case virtinfo.chomp!
      when "supported", "current"
          virtinfo
      else
          "unsupported"
      end 
  end 
end

