# See the file LICENSE for redistribution information.
#
# Copyright (c) 1996-2001
#	Sleepycat Software.  All rights reserved.
#
# Id: log.tcl,v 11.23 2001/10/05 02:38:08 bostic Exp 
#
# Options are:
# -dir <directory in which to store log files>
# -iterations <iterations>
# -maxfilesize <maxsize of log file>
proc logtest { args } {
	source ./include.tcl
	global rand_init

	# Set defaults
	set iterations 1000
	set maxfile [expr 1024 * 128]
	for { set i 0 } { $i < [llength $args] } {incr i} {
		switch -regexp -- [lindex $args $i] {
			-d.* { incr i; set testdir [lindex $args $i] }
			-i.* { incr i; set iterations [lindex $args $i] }
			-m.* { incr i; set maxfile [lindex $args $i] }
			default {
				puts "FAIL:[timestamp] log usage"
	puts "usage: log -dir <directory>\
	    -iterations <number of ops> -maxfilesize <max log file size>"
				return
			}
		}
	}

	# Clean out old log if it existed
	puts "Unlinking log: error message OK"
	env_cleanup $testdir

	# Now run the various functionality tests
	berkdb srand $rand_init

	log001 $testdir $maxfile $iterations 1
	log001 $testdir $maxfile $iterations 0
	log001 $testdir $maxfile [expr 15 * $iterations] 1
	log001 $testdir $maxfile [expr 15 * $iterations] 0
	log002 $testdir $maxfile
	log003 $testdir $maxfile
	log004 $testdir
}

# TEST	log001
# TEST	Read/write log records.
proc log001 { dir max nrecs fixedlength } {
	source ./include.tcl

	if { $fixedlength == 1 } {
		puts "Log001: Basic put/get test (fixed-length log records)"
	} else {
		puts "Log001: Basic put/get test (variable-length log records)"
	}

	env_cleanup $dir

	set env [berkdb env -log -create -home $dir -mode 0644 -log_max $max]
	error_check_bad log_env:$dir $env NULL
	error_check_good log:$dir [is_substr $env "env"] 1

	# We will write records to the log and make sure we can
	# read them back correctly.  We'll use a standard pattern
	# repeated some number of times for each record.
	set lsn_list {}
	set rec_list {}
	puts "Log001.a: Writing $nrecs log records"
	for { set i 0 } { $i < $nrecs } { incr i } {
		set rec ""
		for { set j 0 } { $j < [expr $i % 10 + 1] } {incr j} {
			set rec $rec$i:logrec:$i
		}
		if { $fixedlength != 1 } {
			set rec $rec:[random_data 237 0 0]
		}
		if { $i == 0 } {
			set lsn [$env log_put -checkpoint $rec]
		} else {
			set lsn [$env log_put $rec]
		}
		error_check_bad log_put [is_substr $lsn log_cmd] 1
		lappend lsn_list $lsn
		lappend rec_list $rec
	}

	# Open a log cursor.
	set logc [$env log_cursor]
	error_check_good logc [is_valid_logc $logc $env] TRUE

	puts "Log001.b: Retrieving log records sequentially (forward)"
	set i 0
	for { set grec [$logc get -first] } { [llength $grec] != 0 } {
		set grec [$logc get -next]} {
		error_check_good log_get:seq [lindex $grec 1] \
						 [lindex $rec_list $i]
		incr i
	}

	puts "Log001.c: Retrieving log records sequentially (backward)"
	set i [llength $rec_list]
	for { set grec [$logc get -last] } { [llength $grec] != 0 } {
	    set grec [$logc get -prev] } {
		incr i -1
		error_check_good \
		    log_get:seq [lindex $grec 1] [lindex $rec_list $i]
	}

	puts "Log001.d: Retrieving log records sequentially by LSN"
	set i 0
	foreach lsn $lsn_list {
		set grec [$logc get -set $lsn]
		error_check_good \
		    log_get:seq [lindex $grec 1] [lindex $rec_list $i]
		incr i
	}

	puts "Log001.e: Retrieving log records randomly by LSN"
	set m [expr [llength $lsn_list] - 1]
	for { set i 0 } { $i < $nrecs } { incr i } {
		set recno [berkdb random_int 0 $m ]
		set lsn [lindex $lsn_list $recno]
		set grec [$logc get -set $lsn]
		error_check_good \
		    log_get:seq [lindex $grec 1] [lindex $rec_list $recno]
	}

	puts "Log001.f: Retrieving first/current, last/current log record"
	set grec [$logc get -first]
	error_check_good log_get:seq [lindex $grec 1] [lindex $rec_list 0]
	set grec [$logc get -current]
	error_check_good log_get:seq [lindex $grec 1] [lindex $rec_list 0]
	set i [expr [llength $rec_list] - 1]
	set grec [$logc get -last]
	error_check_good log_get:seq [lindex $grec 1] [lindex $rec_list $i]
	set grec [$logc get -current]
	error_check_good log_get:seq [lindex $grec 1] [lindex $rec_list $i]

	# Retrieve checkpoint records as the first record, middle record
	# and last record in the log.
	puts "Log001.g: Retrieving checkpoint records."
	set grec [$logc get -checkpoint]
	error_check_good \
	    log_get:checkpoint [lindex $grec 1] [lindex $rec_list 0]
	set lsn [$env log_put -checkpoint $rec]
	error_check_bad log_put [is_substr $lsn log_cmd] 1
	for { set i 0 } { $i < 50 } { incr i } {
		if { $fixedlength != 1 } {
			set rec $rec:[random_data 237 0 0]
		}
		set tlsn [$env log_put $rec]
		error_check_bad log_put [is_substr $tlsn log_cmd] 1
	}
	set grec [$logc get -checkpoint]
	error_check_good log_get:checkpoint [lindex $grec 0] $lsn
	set lsn [$env log_put -checkpoint $rec]
	error_check_bad log_put [is_substr $lsn log_cmd] 1
	set grec [$logc get -checkpoint]
	error_check_good log_get:checkpoint [lindex $grec 0] $lsn

	# Close and unlink the file
	error_check_good log_cursor:close:$logc [$logc close] 0
	error_check_good env:close:$env [$env close] 0
	error_check_good envremove:$dir [berkdb envremove -home $dir] 0

	puts "Log001 Complete"
}

# TEST	log002
# TEST	Tests multiple logs
# TEST		Log truncation
# TEST		LSN comparison and file functionality.
proc log002 { dir {max 32768} } {
	source ./include.tcl

	puts "Log002: Multiple log test w/trunc, file, compare functionality"

	env_cleanup $dir

	set env [berkdb env -create -home $dir -mode 0644 -log -log_max $max]
	error_check_bad log_env:$dir $env NULL
	error_check_good log:$dir [is_substr $env "env"] 1

	# We'll record every hundred'th record for later use
	set info_list {}

	puts "Log002.a: Writing log records"
	set i 0
	for {set s 0} { $s <  [expr 3 * $max] } { incr s $len } {
		set rec [random_data 120 0 0]
		set len [string length $rec]
		set lsn [$env log_put $rec]

		if { [expr $i % 100 ] == 0 } {
			lappend info_list [list $lsn $rec]
		}
		incr i
	}

	puts "Log002.b: Checking log_compare"
	set last {0 0}
	foreach p $info_list {
		set l [lindex $p 0]
		if { [llength $last] != 0 } {
			error_check_good \
			    log_compare [$env log_compare $l $last] 1
			error_check_good \
			    log_compare [$env log_compare $last $l] -1
			error_check_good \
			    log_compare [$env log_compare $l $l] 0
		}
		set last $l
	}

	puts "Log002.c: Checking log_file"
	set flist [glob $dir/log*]
	foreach p $info_list {

		set lsn [lindex $p 0]
		set f [$env log_file $lsn]

		# Change all backslash separators on Windows to forward slash
		# separators, which is what the rest of the test suite expects.
		regsub -all {\\} $f {/} f

		error_check_bad log_file:$f [lsearch $flist $f] -1
	}

	puts "Log002.d: Verifying records"

	set logc [$env log_cursor]
	error_check_good log_cursor [is_valid_logc $logc $env] TRUE

	for {set i [expr [llength $info_list] - 1] } { $i >= 0 } { incr i -1} {
		set p [lindex $info_list $i]
		set grec [$logc get -set [lindex $p 0]]
		error_check_good log_get:$env [lindex $grec 1] [lindex $p 1]
	}

	# Close and unlink the file
	error_check_good log_cursor:close:$logc [$logc close] 0
	error_check_good env:close:$env [$env close] 0
	error_check_good envremove:$dir [berkdb envremove -home $dir] 0

	puts "Log002 Complete"
}

# TEST	log003
# TEST	Verify that log_flush is flushing records correctly.
proc log003 { dir {max 32768} } {
	source ./include.tcl

	puts "Log003: Verify log_flush behavior"

	env_cleanup $dir
	set short_rec "abcdefghijklmnopqrstuvwxyz"
	set long_rec [repeat $short_rec 200]
	set very_long_rec [repeat $long_rec 4]

	foreach rec "$short_rec $long_rec $very_long_rec" {
		puts "Log003.a: Verify flush on [string length $rec] byte rec"

		set env [berkdb env -log -home $dir \
				-create -mode 0644 -log_max $max]
		error_check_bad log_env:$dir $env NULL
		error_check_good log:$dir [is_substr $env "env"] 1

		set lsn [$env log_put $rec]
		error_check_bad log_put [lindex $lsn 0] "ERROR:"
		set ret [$env log_flush $lsn]
		error_check_good log_flush $ret 0

		# Now, we want to crash the region and recheck.  Closing the
		# log does not flush any records, so we'll use a close to
		# do the "crash"
		set ret [$env close]
		error_check_good log_env:close $ret 0

		# Now, remove the log region
		#set ret [berkdb envremove -home $dir]
		#error_check_good env:remove $ret 0

		# Re-open the log and try to read the record.
		set env [berkdb env -create -home $dir \
				-log -mode 0644 -log_max $max]
		error_check_bad log_env:$dir $env NULL
		error_check_good log:$dir [is_substr $env "env"] 1

		set logc [$env log_cursor]
		error_check_good log_cursor [is_valid_logc $logc $env] TRUE

		set gotrec [$logc get -first]
		error_check_good lp_get [lindex $gotrec 1] $rec

		# Close and unlink the file
		error_check_good log_cursor:close:$logc [$logc close] 0
		error_check_good env:close:$env [$env close] 0
		error_check_good envremove:$dir [berkdb envremove -home $dir] 0
		log_cleanup $dir
	}

	foreach rec "$short_rec $long_rec $very_long_rec" {
		puts "Log003.b: \
		    Verify flush on non-last record [string length $rec]"
		set env [berkdb env \
		    -create -log -home $dir -mode 0644 -log_max $max]
		error_check_bad log_env:$dir $env NULL
		error_check_good log:$dir [is_substr $env "env"] 1

		# Put 10 random records
		for { set i 0 } { $i < 10 } { incr i} {
			set r [random_data 450 0 0]
			set lsn [$env log_put $r]
			error_check_bad log_put [lindex $lsn 0] "ERROR:"
		}

		# Put the record we are interested in
		set save_lsn [$env log_put $rec]
		error_check_bad log_put [lindex $save_lsn 0] "ERROR:"

		# Put 10 more random records
		for { set i 0 } { $i < 10 } { incr i} {
			set r [random_data 450 0 0]
			set lsn [$env log_put $r]
			error_check_bad log_put [lindex $lsn 0] "ERROR:"
		}

		# Now check the flush
		set ret [$env log_flush $save_lsn]
		error_check_good log_flush $ret 0

		# Now, we want to crash the region and recheck.  Closing the
		# log does not flush any records, so we'll use a close to
		# do the "crash"

		#
		# Now, close and remove the log region
		error_check_good env:close:$env [$env close] 0
		set ret [berkdb envremove -home $dir]
		error_check_good env:remove $ret 0

		# Re-open the log and try to read the record.
		set env [berkdb env \
		    -home $dir -create -log -mode 0644 -log_max $max]
		error_check_bad log_env:$dir $env NULL
		error_check_good log:$dir [is_substr $env "env"] 1

		set logc [$env log_cursor]
		error_check_good log_cursor [is_valid_logc $logc $env] TRUE

		set gotrec [$logc get -set $save_lsn]
		error_check_good lp_get [lindex $gotrec 1] $rec

		# Close and unlink the file
		error_check_good log_cursor:close:$logc [$logc close] 0
		error_check_good env:close:$env [$env close] 0
		error_check_good envremove:$dir [berkdb envremove -home $dir] 0
		log_cleanup $dir
	}

	puts "Log003 Complete"
}

# TEST	log004
# TEST	Make sure that if we do PREVs on a log, but the beginning of the
# TEST	log has been truncated, we do the right thing.
proc log004 { dir } {
	source ./include.tcl

	puts "Log004: Prev on log when beginning of log has been truncated."
	# Use archive test to populate log
	env_cleanup $dir
	puts "Log004.a: Call archive to populate log."
	archive

	# Delete all log files under 100
	puts "Log004.b: Delete all log files under 100."
	set ret [catch { glob $dir/log.00000000* } result]
	if { $ret == 0 } {
		eval fileremove -f $result
	}

	# Now open the log and get the first record and try a prev
	puts "Log004.c: Open truncated log, attempt to access missing portion."
	set myenv [berkdb env -create -log -home $dir]
	error_check_good log_open [is_substr $myenv "env"] 1

	set mylogc [$myenv log_cursor]
	error_check_good log_cursor [is_valid_logc $mylogc $myenv] TRUE

	set ret [$mylogc get -first]
	error_check_bad log_get [llength $ret] 0

	# This should give DB_NOTFOUND which is a ret of length 0
	catch {$mylogc get -prev} ret
	error_check_good log_get_prev [string length $ret] 0

	puts "Log004.d: Close log and environment."
	error_check_good log_cursor_close [$mylogc close] 0
	error_check_good log_close [$myenv close] 0
	puts "Log004 complete."
}
