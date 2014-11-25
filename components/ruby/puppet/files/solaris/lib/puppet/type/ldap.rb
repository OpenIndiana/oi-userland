#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#

#
# Copyright (c) 2013, 2014, Oracle and/or its affiliates. All rights reserved.
#

require 'ipaddr'
require 'puppet/property/list'

def valid_hostname?(hostname)
    return false if hostname.length > 255 or hostname.scan('..').any?
    hostname = hostname[0...-1] if hostname.index('.', -1)
    return hostname.split('.').collect { |i|
        i.size <= 63 and
        not (i.rindex('-', 0) or i.index('-', -1) or i.scan(/[^a-z\d-]/i).any?)
    }.all?
end

def valid_ip?(value)
    begin
        ip = IPAddr.new(value)
    rescue ArgumentError
        return false
    end
    return true
end

Puppet::Type.newtype(:ldap) do
    @doc = "Manage the configuration of the LDAP client for Oracle Solaris"

    newparam(:name) do
        desc "The symbolic name for the LDAP client settings to use.  This name
              is used for human reference only."
        isnamevar
    end

    newproperty(:profile) do
        desc "The LDAP profile name"
        class << self
            attr_accessor :pg
        end
        self.pg = "config"
        desc "The LDAP profile name"
    end

    newproperty(:server_list, :parent => Puppet::Property::List) do
        desc "LDAP server names or addresses.  Specify multiple servers as an
              array"

        class << self
            attr_accessor :pg
        end
        self.pg = "config"

        # ensure should remains an array
        def should
            @should
        end
        
        def insync?(is)
            is = [] if is == :absent or is.nil?
            is.sort == self.should.sort
        end

        # svcprop returns multivalue entries delimited with a space
        def delimiter
            " "
        end

        validate do |value|
            raise Puppet::Error, "default_server entry:  #{value} is 
                invalid" if not valid_ip?(value) and not valid_hostname?(value)
        end
    end

    newproperty(:preferred_server_list, :parent => Puppet::Property::List) do
        desc "LDAP server(s) to contact before any servers listed in
              default_server_list"
        class << self
            attr_accessor :pg
        end
        self.pg = "config"

        # ensure should remains an array
        def should
            @should
        end
        
        def insync?(is)
            is = [] if is == :absent or is.nil?
            is.sort == self.should.sort
        end

        # svcprop returns multivalue entries delimited with a space
        def delimiter
            " "
        end

        validate do |value|
            raise Puppet::Error, "preferred_server entry:  #{value} is 
                invalid" if not valid_ip?(value) and not valid_hostname?(value)
        end
    end

    newproperty(:search_base) do
        desc "The default search base DN"
        class << self
            attr_accessor :pg
        end
        self.pg = "config"
    end

    newproperty(:search_scope) do
        desc "The default search scope for the client's search operations."
        newvalues("base", "one", "sub")
        class << self
            attr_accessor :pg
        end
        self.pg = "config"
    end

    newproperty(:authentication_method, :parent => Puppet::Property::List) do
        desc "The default authentication method(s).  Specify multiple methods
              as an array."

        class << self
            attr_accessor :pg
        end
        self.pg = "config"
        
        # ensure should remains an array
        def should
            @should
        end
        
        def insync?(is)
            is = [] if is == :absent or is.nil?
            is.sort == self.should.sort
        end

        # svcprop returns multivalue entries delimited with a space
        def delimiter
            " "
        end

        newvalues("none", "simple", "sasl/CRAM-MD5", "sasl/DIGEST-MD5",
                  "sasl/GSSAPI", "tls:simple", "tls:sasl/CRAM-MD5",
                  "tls:sasl/DIGEST-MD5")
    end

    newproperty(:credential_level) do
        desc "The credential level the client should use to contact the
              directory."
        newvalues("anonymous", "proxy", "self")
        class << self
            attr_accessor :pg
        end
        self.pg = "config"
    end

    newproperty(:search_time_limit) do
        desc "The maximum number of seconds allowed for an LDAP search
              operation."
        class << self
            attr_accessor :pg
        end
        self.pg = "config"
    end

    newproperty(:bind_time_limit) do
        desc "The maximum number of seconds a client should spend performing a
              bind operation."
        class << self
            attr_accessor :pg
        end
        self.pg = "config"
    end

    newproperty(:follow_referrals) do
        desc "The referral setting."
        newvalues(:true, :false)
        class << self
            attr_accessor :pg
        end
        self.pg = "config"
    end

    newproperty(:profile_ttl) do
        desc "The TTL value in seconds for the client information"
        class << self
            attr_accessor :pg
        end
        self.pg = "config"
    end

    newproperty(:attribute_map, :parent => Puppet::Property::List) do
        desc "A mapping from an attribute defined by a service to an attribute
              in an alternative schema.  Specify multiple mappings as an array."

        class << self
            attr_accessor :pg
        end
        self.pg = "config"
        
        # ensure should remains an array
        def should
            @should
        end
        
        def insync?(is)
            is = [] if is == :absent or is.nil?
            is.sort == self.should.sort
        end

        # svcprop returns multivalue entries delimited with a space
        def delimiter
            " "
        end
    end

    newproperty(:objectclass_map, :parent => Puppet::Property::List) do
        desc "A  mapping from an objectclass defined by a service to an
              objectclass in an alternative schema.  Specify multiple mappings
              as an array."
        
        class << self
            attr_accessor :pg
        end
        self.pg = "config"

        # ensure should remains an array
        def should
            @should
        end
        
        def insync?(is)
            is = [] if is == :absent or is.nil?
            is.sort == self.should.sort
        end

        # svcprop returns multivalue entries delimited with a space
        def delimiter
            " "
        end
    end

    newproperty(:service_credential_level) do
        desc "The credential level to be used by a service."
        newvalues("anonymous", "proxy")
        class << self
            attr_accessor :pg
        end
        self.pg = "config"
    end

    newproperty(:service_authentication_method,
                :parent => Puppet::Property::List) do
        desc "The authentication method to be used by a service.  Specify
              multiple methods as an array."

        class << self
            attr_accessor :pg
        end
        self.pg = "config"

        # ensure should remains an array
        def should
            @should
        end
        
        def insync?(is)
            is = [] if is == :absent or is.nil?
            is.sort == self.should.sort
        end

        # svcprop returns multivalue entries delimited with a space
        def delimiter
            " "
        end
    end

    newproperty(:bind_dn, :parent => Puppet::Property::List) do
        desc "An entry that has read permission for the requested database.
              Specify multiple entries as an array."

        class << self
            attr_accessor :pg
        end
        self.pg = "cred"

        # ensure should remains an array
        def should
            @should
        end
        
        def insync?(is)
            is = [] if is == :absent or is.nil?
            is.sort == self.should.sort
        end

        # svcprop returns multivalue entries delimited with a space
        def delimiter
            " "
        end
    end
    
    newproperty(:bind_passwd) do
        desc "password to be used for authenticating the bind DN."
        class << self
            attr_accessor :pg
        end
        self.pg = "cred"
    end

    newproperty(:enable_shadow_update) do
        desc "Specify whether the client is allowed to update shadow
              information."
        newvalues(:true, :false)
        class << self
            attr_accessor :pg
        end
        self.pg = "cred"
    end

    newproperty(:admin_bind_dn) do
        desc "The Bind Distinguished Name for the administrator identity that
              is used for shadow information update"
        class << self
            attr_accessor :pg
        end
        self.pg = "cred"
    end

    newproperty(:admin_bind_passwd) do
        desc "The administrator password"
        class << self
            attr_accessor :pg
        end
        self.pg = "cred"
    end

    newproperty(:host_certpath) do
        desc "The location of the certificate files"
        class << self
            attr_accessor :pg
        end
        self.pg = "cred"
    end
end
