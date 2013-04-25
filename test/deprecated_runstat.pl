#!/usr/bin/perl

$numPassed = 0;
$numFailed = 0;

@list = `ls compare/*.xml`;

foreach $filename (@list)	# Visit each item in turn
				# and call it $filename
{
	#print "$filename\n";	# Print the item

	open(INFO, $filename);		# Open the file
	@lines = <INFO>;		# Read it into an array
	close(INFO);			# Close the file

	#print @lines;			# Print the array

	foreach $line (@lines)
	{
		if ($line =~ /<result>PASSED/)
		{
		print "the test passed\n";
		$numPassed++;
		}
		elsif ($line =~ /<result>FAILED/)
		{
		print "the test failed\n";
		$numFailed++;
		}
	}
}

$outputfilename = "runstat.xml";
open(OUTPUTFILE, ">$outputfilename");	# Open for output

print OUTPUTFILE "<runstat>\n";
print OUTPUTFILE "<TestsPassed>$numPassed</TestsPassed>\n";
print OUTPUTFILE "<TestsFailed>$numFailed</TestsFailed>\n";
print OUTPUTFILE "</runstat>\n";
