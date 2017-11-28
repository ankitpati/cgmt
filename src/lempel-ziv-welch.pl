#!/usr/bin/env perl

# lempel-ziv-welch.pl
# Date  : 28 November 2017
# Author: Ankit Pati

use strict;
use warnings;

my @prelist = (' ', 'a' .. 'z', 'A' .. 'Z', 0 .. 9,
                split '', '.?!@#$%^&*()[]{}<>/\|+-=_,;:`~"\'');

my %dict;
@dict{@prelist} = (0 .. @prelist);

my $code = @prelist;

print "Enter lines to compress with Lempel-Ziv-Welch. Ctrl+D to end.\n\n";

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
my %revdict = reverse %dict;
foreach (sort {$a <=> $b} keys %revdict) {
    print " $_\t->\t$revdict{$_}\n" if $_ >= @prelist;
}

# end of lempel-ziv-welch.pl

__END__
Output

Enter lines to compress with Lempel-Ziv. Ctrl+D to end.

TOBEORNOTTOBEORTOBEORNOT
46 41 28 31 41 44 40 41 46 95 97 99 104 98 100 102

Extended Dictionary
 95     ->      TO
 96     ->      OB
 97     ->      BE
 98     ->      EO
 99     ->      OR
 100    ->      RN
 101    ->      NO
 102    ->      OT
 103    ->      TT
 104    ->      TOB
 105    ->      BEO
 106    ->      ORT
 107    ->      TOBE
 108    ->      EOR
 109    ->      RNO
