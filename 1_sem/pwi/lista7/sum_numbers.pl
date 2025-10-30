
#!/usr/bin/perl
use strict;
use warnings;

my $sum = 0;

while (<>) {
    while (/\b(\d+)\b/g) {
        $sum += $1;
    }
}

print "Sum: $sum\n";
