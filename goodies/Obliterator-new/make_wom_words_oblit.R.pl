#! /usr/bin/perl

# This script takes in a words.R single column word index file generated by a PhiloLogic load and outputs a
# two-column word index, where the left column contains the actual index form (potentially Indic UTF8-encoded 
# strings) and the right-column contains the equivalent ASCII romanizations. To get from Indic UTF8 to Romascii,
# we need to convert to ISCII first. At some point, Obliterator will allow conversion directly from Indic UTF8
# to ASCII.

use Obliterator;

while (<>) {
    chop;
    $index_form = $_;
    $search_form = $_;

    if ($index_form =~ m/^[A-Za-z0-9]+$/) {

	$lineout = $search_form . "\t" . $index_form . "\n";

    } 

    # here we're expecting something that Obliterator should handle, 
    # namely indic UTF or roman with diacritics

    else {

	my $utf = Obliterator->new();
	$utf->indutf("$search_form");
	$iscii_string = sprintf("%s", $utf->to_iscii);
	my $new_string = Obliterator->new();
	$new_string->iscii->bng($iscii_string);
	my $roman = sprintf("%s", $new_string->romascii);
	
	$lineout = $roman . "\t" . $index_form . "\n";
    }

    print $lineout;
}
