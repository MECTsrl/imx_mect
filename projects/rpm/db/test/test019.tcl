# See the file LICENSE for redistribution information.
#
# Copyright (c) 1996-2001
#	Sleepycat Software.  All rights reserved.
#
# Id: test019.tcl,v 11.19 2001/08/03 16:39:36 bostic Exp 
#
# TEST	test019
# TEST	Partial get test.
proc test019 { method {nentries 10000} args } {
	global fixed_len
	global rand_init
	source ./include.tcl

	set args [convert_args $method $args]
	set omethod [convert_method $method]
	puts "Test019: $method ($args) $nentries partial get test"

	# Create the database and open the dictionary
	set eindex [lsearch -exact $args "-env"]
	#
	# If we are using an env, then testfile should just be the db name.
	# Otherwise it is the test directory and the name.
	if { $eindex == -1 } {
		set testfile $testdir/test019.db
		set env NULL
	} else {
		set testfile test019.db
		incr eindex
		set env [lindex $args $eindex]
	}
	cleanup $testdir $env

	set db [eval {berkdb_open \
	     -create -mode 0644} $args {$omethod $testfile}]
	error_check_good dbopen [is_valid_db $db] TRUE
	set did [open $dict]
	berkdb srand $rand_init

	set pflags ""
	set gflags ""
	set txn ""
	set count 0

	if { [is_record_based $method] == 1 } {
		append gflags " -recno"
	}

	puts "\tTest019.a: put/get loop"
	for { set i 0 } { [gets $did str] != -1 && $i < $nentries } \
	    { incr i } {

		if { [is_record_based $method] == 1 } {
			set key [expr $i + 1]
		} else {
			set key $str
		}
		set repl [berkdb random_int $fixed_len 100]
		set data [chop_data $method [replicate $str $repl]]
		set ret [eval {$db put} $txn {-nooverwrite $key $data}]
		error_check_good dbput:$key $ret 0

		set ret [eval {$db get} $txn $gflags {$key}]
		error_check_good \
		    dbget:$key $ret [list [list $key [pad_data $method $data]]]
		set kvals($key) $repl
	}
	close $did

	puts "\tTest019.b: partial get loop"
	set did [open $dict]
	for { set i 0 } { [gets $did str] != -1 && $i < $nentries } \
	    { incr i } {
		if { [is_record_based $method] == 1 } {
			set key [expr $i + 1]
		} else {
			set key $str
		}
		set data [pad_data $method [replicate $str $kvals($key)]]

		set maxndx [expr [string length $data] - 1]

		set beg [berkdb random_int 0 [expr $maxndx - 1]]
		set len [berkdb random_int 0 [expr $maxndx * 2]]

		set ret [eval {$db get} \
		    $txn {-partial [list $beg $len]} $gflags {$key}]

		# In order for tcl to handle this, we have to overwrite the
		# last character with a NULL.  That makes the length one less
		# than we expect.
		set k [lindex [lindex $ret 0] 0]
		set d [lindex [lindex $ret 0] 1]
		error_check_good dbget_key $k $key

		error_check_good dbget_data $d \
		    [string range $data $beg [expr $beg + $len - 1]]

	}
	error_check_good db_close [$db close] 0
	close $did
}
