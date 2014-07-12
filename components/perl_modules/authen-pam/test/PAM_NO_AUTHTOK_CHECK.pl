#!/usr/bin/perl
use Authen::PAM;
ref($pamh = new Authen::PAM($service, $username, \&my_conv_func));
$pamh->pam_chauthtok(PAM_DISALLOW_NULL_AUTHTOK());
$pamh->pam_chauthtok(PAM_NO_AUTHTOK_CHECK());
print "$0 ($^X - $^V) PASSED\n";
