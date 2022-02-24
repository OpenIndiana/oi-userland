#!/usr/bin/perl
# 
# Script to list line with characters that are not in the ASCII class
# 

while (<>) {
  if (/[[:^ascii:]]/) {
    print;
  }
}

