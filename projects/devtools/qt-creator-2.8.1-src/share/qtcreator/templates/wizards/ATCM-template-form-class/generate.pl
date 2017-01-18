#!/usr/bin/perl -w

# *************************************************************************
#
# This file is part of Qt Creator
#
# Copyright (c) 2011 Nokia Corporation and/or its subsidiary(-ies).
#
# Contact: Nokia Corporation (qt-info@nokia.com)
#
# GNU Lesser General Public License Usage
#
# This file may be used under the terms of the GNU Lesser General Public
# License version 2.1 as published by the Free Software Foundation and
# appearing in the file LICENSE.LGPL included in the packaging of this file.
# Please review the following information to ensure the GNU Lesser General
# Public License version 2.1 requirements will be met:
# http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
#
# In addition, as a special exception, Nokia gives you certain additional
# rights. These rights are described in the Nokia Qt LGPL Exception
# version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
#
# Other Usage
#
# Alternatively, this file may be used in accordance with the terms and
# conditions contained in a signed written agreement between you and Nokia.
#
# If you are unsure which license is appropriate for your use, please
# contact the sales department at http://qt.nokia.com/contact.
#
# *************************************************************************

use strict;
use Getopt::Long;
use IO::File;

my $optDryRun = 0;
my $optHelp = 0;
my $optClassName = 'MyClass';
my $optProjectName = 'MyProject';
my $optCppHeaderSuffix = 'h';
my $optCppSourceSuffix = 'cpp';
my $optDescription = '';
my $optTarget = 'TPAC1007';

# -- Read in a file and return its lines
sub readFile
{
    my ($fileName) = @_;
    my @rc = ();
    my $fh = new IO::File('<' . $fileName) or die ('Unable to open for reading ' .  $fileName . ' :' . $!);
    while (my $line = <$fh>) {
	chomp($line);
        push (@rc, $line);
    }
    $fh->close();
    return @rc;
}

my $USAGE=<<EOF;
Usage: generate.pl [--help] | [--dry-run]
                   [--class-name=<class name>]
                   [--project-name=<project name>]
                   [--header-suffix=<header suffix>]
                   [--source-suffix=<source suffix>]
                   [--description=<description-file>]

Custom wizard project generation example script.

EOF

my $argCount = scalar(@ARGV);
if ($argCount == 0
    || !GetOptions("help" => \$optHelp,
                   "dry-run" => \$optDryRun,
                   "class-name:s" => \$optClassName,
                   "project-name:s" => \$optProjectName,
                   "header-suffix:s" => \$optCppHeaderSuffix,
                   "source-suffix:s" => \$optCppSourceSuffix,
                   "description:s" => \$optDescription)
    || $optHelp != 0) {
    print $USAGE;
    exit (1);
}

# -- Determine file names
my $baseFileName = lc($optClassName);
my $sourceFileName = $baseFileName . '.' . $optCppSourceSuffix;
my $headerFileName = $baseFileName . '.' . $optCppHeaderSuffix;
my $mainSourceFileName = 'main.' . $optCppSourceSuffix;
my $projectFileName = lc($optProjectName) . '.pro';

my $Height=0;
my $Width=0;

if ($optDryRun) {
#   -- Step 1) Dry run: Print file names along with attributes
    print "pages.cpp\n";
    print "pages.h\n";
} else {

	open FILE, "<", "template.pri" or die $! . $projectFileName;

	while (<FILE>) {
		if ($_ =~/MODEL/)
		{
			my (@display_size) = $_ =~ /(\d+)/g;
			$Width  = $display_size[0];
			$Height = $display_size[1];
			last;
		}
	}
	close FILE;

	my $found = 0;

	open FILE, "<", "$optClassName.ui" or die $!;
	open TMP, "+>", undef or die $!;
	while (<FILE>) {
		if ($_ =~/<width>XXX<\/width>/)
		{
			$found = 1;
			$_ =~ s/XXX/$Width/g;
			print TMP $_;
		}
		elsif ($_ =~/<height>XXX<\/height>/)
		{
			$found = 1;
			$_ =~ s/XXX/$Height/g;
			print TMP $_;
		}
		else
		{
			print TMP $_;
		}
	}
	if ($found == 1)
	{
		close FILE;
		open FILE, ">", "$optClassName.ui" or die $!;

		# Move to the beginning of file
		seek(TMP,0,0);
		# Read contents of the anonymous file
		while (<TMP>) {
			print FILE $_;
		}
		close TMP;
		close FILE;
	}

	open FILE, "<", "pages.h" or die $!;
	open TMP, "+>", undef or die $!;

	my $ClassiIndex = $optClassName;
	$ClassiIndex =~ s/page//;
	
	$found = 0;

	while (<FILE>) {
		if ($_ =~/#include \"page$ClassiIndex.h/)
		{
			$found = 1;
			close(FILE);
		}
		if ($_ =~/add here the header of the new page/)
		{
			print TMP "#include \"page$ClassiIndex.h\"\n";
		}
		print TMP $_;
	}

	if ($found == 0)
	{
		close FILE;
		open FILE, ">", "pages.h" or die $!;

		# Move to the beginning of file
		seek(TMP,0,0);
		# Read contents of the anonymous file
		while (<TMP>) {
			print FILE $_;
		}
		close TMP;
		close FILE;
	}

	open FILE, "<", "pages.cpp" or die $!;
	open TMP, "+>", undef or die $!;
	$ClassiIndex = $optClassName;
	$ClassiIndex =~ s/page//;

	$found = 0;
	while (<FILE>) {
		if ($_ =~/case 0x$ClassiIndex:/)
		{
			close(FILE);
			$found = 1;
		}
		if ($_ =~/<< \"$optClassName\"/)
		{
			close(FILE);
			$found = 1;
		}
		if ($_ =~/add here the label of the new page/)
		{
            print TMP "            << \"$optClassName\"\n";
		}
		if ($_ =~/add here the case labeled with the HEX id of the new pages/)
		{
			print TMP "    case 0x$ClassiIndex:\n";
			print TMP "        *p = (page *)(new $optClassName);\n";
			print TMP "        break;\n";
		}
		print TMP $_;
	}
	if ($found == 0)
	{
		close FILE;
		open FILE, ">", "pages.cpp" or die $!;

		# Move to the beginning of file
		seek(TMP,0,0);
		# Read contents of the anonymous file
		while (<TMP>) {
			print FILE $_;
		}
		close TMP;
		close FILE;
	}
}
