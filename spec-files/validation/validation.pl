#!/bin/perl

sub traverse {
    my ($dir, @callbacks) = @_;
    my $present;
    
    opendir $present, $dir or return();

    for (grep { ! /^(\.|\.\.)$/ } readdir $present) {
        my $path = "$dir/$_";

	foreach $validation (@callbacks) 
	{
	  &$validation($path);
	}
        traverse($path, @callbacks) if -d $path;
    }

    closedir $present;
    return();
}

sub checkManpage {
  my $file = shift;
  if (-T $file) {
    if ($file =~ /\/man\//) {
      my $attribute_section = 0;
      open (FILE, $file);
      while (<FILE>) {
	if (/\.so /) { return; }#reference only manpage 
	if (/.SH.*ATTRIBUTES/) {
	  $attribute_section = 1;
	}
      }
      close (FILE);
      if ($attribute_section == 0) {
	print "MAN CHECK : Error in $file\n\tNo attribute section missing\n";
      }
    }
  }
  return;
}


sub checkExecutableNotWritable {
  my $file = shift;
  if (not -d $file and -x $file and -w $file)
  {
    print "ATTRIBUTE CHECK : Error in $file\n\texecutable file should not be writable\n";
  }
  return;
}

@validationFcts = (\&checkManpage, \&checkExecutableNoWritable);


traverse($ARGV[0], @validationFcts);

