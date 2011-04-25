#!/usr/ruby/1.8/bin/ruby
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
# Copyright (c) 2009, 2011, Oracle and/or its affiliates. All rights reserved.
#

require 'optparse'

$pass_on_opts = ["generate_index"]
suppress = false
deprecation_msg =  "WARNING: index_gem_repository.rb has been deprecated and will be removed in a future release of Solaris, use 'gem generate_index' instead. (use '-s' to suppress these warnings)\n\n"

options = OptionParser.new do |opts|
    opts.on('-d', '--dir=DIRNAME', '--directory=DIRNAME',
         "repository base dir containing gems subdir",
         String) do |value|
           $pass_on_opts << '-d'
           $pass_on_opts << value
    end
        
    opts.on( '--[no-]quick',
         "include quick index"
     ) do |value|
      print "WARNING: Quick index always generated with RubyGems 1.3.1\n"
    end

    opts.on('-v', '--verbose',
         "show verbose output"
       ) do
         $pass_on_opts << '-V'
    end

    opts.on('-V', '--version',
         "show version"
       ) do
         print deprecation_msg
         system("gem", "env", "version")
         exit
    end

    opts.on_tail('-s', '--suppress-warnings', 
           "Suppress deprecation warning"
       ) do
        suppress = true
    end

    opts.on_tail('-h', '--help', "Display this help message"
       ) do
        puts deprecation_msg
        puts opts
        exit
     end


end

begin
  options.parse!(ARGV)
rescue OptionParser::InvalidArgument => err
  puts options
  puts
  puts err.message
  exit(-1)
end

ARGV.each do |arg|
  $pass_on_opts << arg
end

print deprecation_msg unless suppress

system("gem", *$pass_on_opts)
