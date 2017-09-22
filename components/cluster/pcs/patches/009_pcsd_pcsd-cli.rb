diff -nur a/pcsd/pcsd-cli.rb b/pcsd/pcsd-cli.rb
--- a/pcsd/pcsd-cli.rb	Fri Nov  4 15:09:59 2016
+++ b/pcsd/pcsd-cli.rb	Fri Nov  4 15:10:33 2016
@@ -1,5 +1,8 @@
 #!/usr/bin/ruby
 
+$LOAD_PATH.unshift File.dirname(__FILE__)
+
+require 'bundler/setup'
 require 'rubygems'
 require 'etc'
 require 'json'
