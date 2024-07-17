#!/usr/bin/perl
#  genWords.pl
#  wordlesolve
#
#  Created by Jeremy Rand on 2022-07-21.
#  Copyright © 2022 Jeremy Rand. All rights reserved.

use strict;

die "$0: Expected three arguments, input file, word count file and output dir" if ($#ARGV != 2);

my $gInputFileName = $ARGV[0];
my $gWordCountFileName = $ARGV[1];
my $gGenDir = $ARGV[2];
my $gOutputFileName = $gGenDir . "/wordData.s";
my $gOutputCountFileName = $gGenDir . "/countData.s";

my %gAllWordCounts;
open my $gWordCountFile, "<", "$gWordCountFileName" or die "$0: Unable to open $gWordCountFileName for reading, $!";
while (<$gWordCountFile>) {
    chomp;
    tr/[a-z]/[A-Z]/;
    my @cols = split;
    next if ($cols[0] !~ /^[0-9]+/);
    $gAllWordCounts{$cols[1]} = $cols[0];
    
}
close($gWordCountFile);

open my $gOutputFile, ">", "$gOutputFileName" or die "$0: Unable to open $gOutputFileName for writing, $!";
open my $gOutputCountFile, ">", "$gOutputCountFileName" or die "$0: Unable to open $gOutputCountFileName for writing, $!";
open my $gInputFile, "<", "$gInputFileName" or die "$0: Unable to open $gInputFileName for reading, $!";

my $text = << "EOF";
    case on
    mcopy wordData.macros
    keep wordData

wordData data wordDataSeg
EOF
print $gOutputFile $text;

my @words;
my @wordLines;
my %gWordCounts;
while (<$gInputFile>) {
    chomp;
    tr/[a-z]/[A-Z]/;
    my $word = $_;
    push(@words, "$word");
    push(@wordLines, "    dc c'$word'\n");
    
    if (defined $gAllWordCounts{$word}) {
        $gWordCounts{$word} = $gAllWordCounts{$word};
        next
    }
    
    if ($word =~ /[^S]S$/) {
        my $subword = $word;
        $subword =~ s/S$//;
        if (defined $gAllWordCounts{$subword}) {
            $gWordCounts{$word} = $gAllWordCounts{$subword};
            next
        }
    }
    
    if ($word =~ /ES$/) {
        my $subword = $word;
        $subword =~ s/ES$//;
        if (defined $gAllWordCounts{$subword}) {
            $gWordCounts{$word} = $gAllWordCounts{$subword};
            next
        }
    }
    
    if ($word =~ /ED$/) {
        my $subword = $word;
        $subword =~ s/D$//;
        if (defined $gAllWordCounts{$subword}) {
            $gWordCounts{$word} = $gAllWordCounts{$subword};
            next
        }
        $subword = $word;
        $subword =~ s/ED$//;
        if (defined $gAllWordCounts{$subword}) {
            $gWordCounts{$word} = $gAllWordCounts{$subword};
            next
        }
    }
    
    if ($word =~ /ING$/) {
        my $subword = $word;
        $subword =~ s/ING$//;
        if (defined $gAllWordCounts{$subword}) {
            $gWordCounts{$word} = $gAllWordCounts{$subword};
            next
        }
        $subword = $word;
        $subword =~ s/ING$/E/;
        if (defined $gAllWordCounts{$subword}) {
            $gWordCounts{$word} = $gAllWordCounts{$subword};
            next
        }
    }
}
close($gInputFile);

print $gOutputFile "    dc i2'" . ($#words + 1) ."'\n";
print $gOutputFile join("", @wordLines);

$text = << "EOF";
    end
EOF
print $gOutputFile $text;
close($gOutputFile);

my $rank = scalar keys %gWordCounts;
foreach my $word (sort { $gWordCounts{$a} <=> $gWordCounts{$b} } keys %gWordCounts) {
    $gWordCounts{$word} = $rank;
    $rank--;
}

$text = << "EOF";
    case on
    mcopy countData.macros
    keep countData

countData data countDataSeg
EOF

print $gOutputCountFile $text;

foreach my $word (@words) {
    $rank = 0;
    if (defined $gWordCounts{$word}) {
        $rank = $gWordCounts{$word};
    }
    
    print $gOutputCountFile "    dc i2'" . ($rank) ."'\n";
}
$text = << "EOF";
    end
EOF
print $gOutputCountFile $text;
close($gOutputCountFile);


exit(0);
