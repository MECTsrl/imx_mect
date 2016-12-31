# See the file LICENSE for redistribution information.
#
# Copyright (c) 1996-2001
#	Sleepycat Software.  All rights reserved.
#
# Id: test001.tcl,v 11.22 2001/08/03 16:39:32 bostic Exp 
#
# TEST	test001
# TEST	Small keys/data
# TEST		Put/get per key
# TEST		Dump file
# TEST		Close, reopen
# TEST		Dump file
# TEST
# TEST	Use the first 10,000 entries from the dictionary.
# TEST	Insert each with self as key and data; retrieve each.
# TEST	After all are entered, retrieve all; compare output to original.
# TEST	Close file, reopen, do retrieve and re-verify.
proc test001 { method {nentries 10000} {start 0} {tnum "01"} args } {
	source ./include.tcl

	set args [convert_args $method $args]
	set omethod [convert_method $method]

	puts "Test0$tnum: $method ($args) $nentries equal key/data pairs"
	if { $start != 0 } {
		puts "\tStarting at $start"
	}

	# Create the database and open the dictionary
	set eindex [lsearch -exact $args "-env"]
	#
	# If we are using an env, then testfile should just be the db name.
	# Otherwise it is the test directory and the name.
	# If we are not using an external env, then test setting
	# the database cache size and using multiple caches.
	if { $eindex == -1 } {
		set testfile $testdir/test0$tnum.db
		append args " -cachesize {0 1048576 3} "
		set env NULL
	} else {
		set testfile test0$tnum.db
		incr eindex
		set env [lindex $args $eindex]
	}
	set t1 $testdir/t1
	set t2 $testdir/t2
	set t3 $testdir/t3
	cleanup $testdir $env
	set db [eval {berkdb_open \
	     -create -mode 0644} $args $omethod $testfile]
	error_check_good dbopen [is_valid_db $db] TRUE
	set did [open $dict]

	set pflags ""
	set gflags ""
	set txn ""

	if { [is_record_based $method] == 1 } {
		set checkfunc test001_recno.check
		append gflags " -recno"
	} else {
		set checkfunc test001.check
	}
	puts "\tTest0$tnum.a: put/get loop"
	# Here is the loop where we put and get each key/data pair
	set count 0
	while { [gets $did str] != -1 && $count < $nentries } {
		if { [is_record_based $method] == 1 } {
			global kvals

			set key [expr $count + 1 + $start]
			if { 0xffffffff > 0 && $key > 0xffffffff } {
				set key [expr $key - 0x100000000]
			}
			if { $key == 0 || $key - 0xffffffff == 1 } {
				incr key
				incr count
			}
			set kvals($key) [pad_data $method $str]
		} else {
			set key $str
			set str [reverse $str]
		}
		set ret [eval \
		    {$db put} $txn $pflags {$key [chop_data $method $str]}]
		error_check_good put $ret 0

		set ret [eval {$db get} $gflags {$key}]
		error_check_good \
		    get $ret [list [list $key [pad_data $method $str]]]

		# Test DB_GET_BOTH for success
		set ret [$db get -get_both $key [pad_data $method $str]]
		error_check_good \
		    getboth $ret [list [list $key [pad_data $method $str]]]

		# Test DB_GET_BOTH for failure
		set ret [$db get -get_both $key [pad_data $method BAD$str]]
		error_check_good getbothBAD [llength $ret] 0

		incr count
	}
	close $did
	# Now we will get each key from the DB and compare the results
	# to the original.
	puts "\tTest0$tnum.b: dump file"
	dump_file $db $txn $t1 $checkfunc
	error_check_good db_close [$db close] 0

	# Now compare the keys to see if they match the dictionary (or ints)
	if { [is_record_based $method] == 1 } {
		set oid [open $t2 w]
		for {set i 1} {$i <= $nentries} {incr i} {
			set j [expr $i + $start]
			if { 0xffffffff > 0 && $j > 0xffffffff } {
				set j [expr $j - 0x100000000]
			}
			if { $j == 0 } {
				incr i
				incr j
			}
			puts $oid $j
		}
		close $oid
	} else {
		set q q
		filehead $nentries $dict $t2
	}
	filesort $t2 $t3
	file rename -force $t3 $t2
	filesort $t1 $t3

	error_check_good Test0$tnum:diff($t3,$t2) \
	    [filecmp $t3 $t2] 0

	puts "\tTest0$tnum.c: close, open, and dump file"
	# Now, reopen the file and run the last test again.
	open_and_dump_file $testfile $env $txn $t1 $checkfunc \
	    dump_file_direction "-first" "-next"
	if { [string compare $omethod "-recno"] != 0 } {
		filesort $t1 $t3
	}

	error_check_good Test0$tnum:diff($t2,$t3) \
	    [filecmp $t2 $t3] 0

	# Now, reopen the file and run the last test again in the
	# reverse direction.
	puts "\tTest0$tnum.d: close, open, and dump file in reverse direction"
	open_and_dump_file $testfile $env $txn $t1 $checkfunc \
	    dump_file_direction "-last" "-prev"

	if { [string compare $omethod "-recno"] != 0 } {
		filesort $t1 $t3
	}

	error_check_good Test0$tnum:diff($t3,$t2) \
	    [filecmp $t3 $t2] 0
}

# Check function for test001; keys and data are identical
proc test001.check { key data } {
	error_check_good "key/data mismatch" $data [reverse $key]
}

proc test001_recno.check { key data } {
	global dict
	global kvals

	error_check_good key"$key"_exists [info exists kvals($key)] 1
	error_check_good "key/data mismatch, key $key" $data $kvals($key)
}
