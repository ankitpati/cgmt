#!/usr/bin/env perl

# lempel-ziv.pl
# Date  : 28 November 2017
# Author: Ankit Pati

use strict;
use warnings;

my @prelist = (' ', 'a' .. 'z', 'A' .. 'Z', 0 .. 9,
                split '', '.?!@#$%^&*()[]{}<>/\|+-=_,;:`~"\'');

my %dict;
@dict{@prelist} = (0 .. @prelist);

my $code = @prelist;

print "Enter lines to compress with Lempel-Ziv. Ctrl+D to end.\n\n";

while (<>) {
    chomp;

    my $w = '';

    for my $c (split '', $_) {
        if (exists $dict{$w.$c}) {
            $w .= $c;
        }
        else {
            $dict{$w.$c} = $code++;
            print $dict{$w}.' ';
            $w = $c;
        }
    }

    print "$dict{$w}\n";
}
print "\n";

print "Extended Dictionary\n";
foreach (sort keys %dict) {
    print "\t'$_' => '$dict{$_}'\n" if $dict{$_} >= @prelist;
}

# end of lempel-ziv.pl

__END__
Output

Enter lines to compress with Lempel-Ziv. Ctrl+D to end.

TOBEORNOTTOBEORTOBEORNOT
46 41 28 31 41 44 40 41 46 95 97 99 104 98 100 102

Extended Dictionary
    'BE' => '97'
    'BEO' => '105'
    'EO' => '98'
    'EOR' => '108'
    'NO' => '101'
    'OB' => '96'
    'OR' => '99'
    'ORT' => '106'
    'OT' => '102'
    'RN' => '100'
    'RNO' => '109'
    'TO' => '95'
    'TOB' => '104'
    'TOBE' => '107'
    'TT' => '103'
