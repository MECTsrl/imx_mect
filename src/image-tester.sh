#!/bin/sh

#set -x

golddir="$1"
if test -z "$golddir" -o ! -d "$golddir"; then
	echo "ERROR: no reference directory provided."
	exit 1
fi

testimg="$2"
if test -z "$golddir" -o ! -r "$golddir" -o ! -s "$golddir"; then
	echo "ERROR: cannot access the archive to test \"$golddir\"."
	exit 1
fi

tmpdir="$3"
if test -z "$tmpdir"; then
	echo "ERROR: no temporary directory provided."
	exit 1
fi
if test -e "$tmpdir" -a ! -d "$tmpdir"; then
	echo "ERROR: $tmpdir is not suitable for a temporary directory."
	exit 1
fi
if test ! -e "$tmpdir" && ! mkdir "$tmpdir"; then
	echo "ERROR: cannot create the temporary directory \"$tmpdir\"."
	exit 1
fi

imgsfx="$4"
if test -z "$imgsfx"; then
	echo "ERROR: no image release suffix provided."
	exit 1
fi

buildir=$(pwd)

tmpfile=$(mktemp) || exit 1

# Cleanup and abort execution with an error code.
terminate()
{
	sudo rm -f $tmpfile $workdir
	exit 1
}


goldimg="$(readlink -m ${golddir}/$(basename $testimg))"
goldimg="$(ls ${goldimg%$imgsfx}*.zip)"
if ! test -s "$goldimg"; then
	echo "ERROR: cannot find the test image file $goldimg."
	terminate
fi

workdir="$tmpdir"/"$(basename $testimg .zip).testing"
test -d "$workdir" && sudo rm -rf "$workdir"

mkdir "$workdir"
cd "$workdir" > /dev/null

# Expand the test and reference archives.
mkdir test
cd test > /dev/null
unzip -q "$testimg"
cd - > /dev/null

mkdir gold
cd gold > /dev/null
unzip -q "$goldimg"
cd - > /dev/null

# Compare archive structure.
if diff -rq test gold | grep -v '^Files .* and .* differ$' | grep -q .; then
	echo "ERROR: different archive structure for \"$testimg\" and \"goldimg\"."
	terminate
fi

# Expand all file system archives.
for d in test gold; do
	find $d -name \*.tar -print | sed 's/^\.\///' | while read archive; do
		expanddir="$d/`basename \"$archive\" .tar`"
		if test -d "$expanddir"; then
			echo "ERROR: directory \"$expanddir\" exists."
			terminate
		fi

		mkdir "$expanddir"
		sudo tar xf "$archive" -C "$expanddir"
		rm -f "$archive"
	done
done

retval=0

# Check for new files in test vs. gold.
rsync -aOJIvnc --delete test/ gold/ | tail -n +2 | head -n -3 > $tmpfile 2>&1
if test -s $tmpfile; then
	if grep -q '^deleting ' $tmpfile; then
		echo "*** ERROR: MISSING files in \"$testimg\":"
		echo "==============="
		sed -n '/^deleting / { s/^deleting //; p; }' $tmpfile | while read f; do
			echo -n '[ ]'

			(
				ls -l gold/"$f" 2>&1
				md5sum gold/"$f" 2>&1
			) | sed 's/^/\t/'
			echo "==============="
		done

		retval=1
	fi
fi

# Check for new files in gold vs. test
rsync -aOJIvnc --delete gold/ test/ | tail -n +2 | head -n -3 > $tmpfile 2>&1
if test -s $tmpfile; then
	if grep -q '^deleting ' $tmpfile; then
		echo "*** ERROR: NEW files in \"$testimg\":"
		echo "==============="
		sed -n '/^deleting / { s/^deleting //; p; }' $tmpfile | while read f; do
			(
				ls -l test/"$f" 2>&1
				md5sum test/"$f" 2>&1
			) | sed 's/^/\t/'
			echo "==============="
		done

		retval=1
	fi

	# Check for contents differences.
	if sed '/^deleting / d' $tmpfile | grep -q .; then
		echo "*** ERROR: CHANGED files in \"$testimg\":"
		echo "==============="
		sed '/^deleting / d' $tmpfile | while read f; do
			if test -f test/"$f" -a -f gold/"$f"; then
				# Are we comparing binaries?
				if file gold/"$f" | grep -q ' ELF 32-bit LSB '; then
					# Strip and check again.
					cp gold/"$f" ${tmpfile}.gold
					cp test/"$f" ${tmpfile}.test
					/opt/CodeSourcery/bin/arm-none-linux-gnueabi-strip -s ${tmpfile}.gold ${tmpfile}.test
					cmp -s ${tmpfile}.gold ${tmpfile}.test && continue

					# Last resort: disassemble and compare again.
					/opt/CodeSourcery/bin/arm-none-linux-gnueabi-objdump -d test/"$f" | tail -n +3 > ${tmpfile}.test
					/opt/CodeSourcery/bin/arm-none-linux-gnueabi-objdump -d gold/"$f" | tail -n +3 > ${tmpfile}.gold
					cmp -s ${tmpfile}.gold ${tmpfile}.test && continue
				elif expr "$f" : .*\.tar\.bz2\$ > /dev/null; then
					sudo rm -rf ${tmpfile}.gold.dir
					mkdir -p ${tmpfile}.gold.dir || exit 1
					tar xjf gold/"$f" -C ${tmpfile}.gold.dir

					sudo rm -rf ${tmpfile}.test.dir
					mkdir -p ${tmpfile}.test.dir || exit 1
					tar xjf test/"$f" -C ${tmpfile}.test.dir

					diff -rq ${tmpfile}.gold.dir ${tmpfile}.test.dir && continue
				fi
			fi

			# Detailed difference report.
			if test -f gold/"$f" -a -f test/"$f"; then
				echo -n '[ ]'
				(
					ls -l gold/"$f" test/"$f"

					echo ""
					md5sum gold/"$f" test/"$f"

					if file --mime gold/"$f" | grep -q '\(: text/\|: application/xml\)'; then
						echo ""
						diff -u gold/"$f" test/"$f" | head --lines=50
					elif file gold/"$f" | grep -qw ELF; then
						/opt/CodeSourcery/bin/arm-none-linux-gnueabi-objdump -d test/"$f" | tail -n +3 > ${tmpfile}.test
						/opt/CodeSourcery/bin/arm-none-linux-gnueabi-objdump -d gold/"$f" | tail -n +3 > ${tmpfile}.gold
						echo ""
						diff -u ${tmpfile}.gold ${tmpfile}.test # | head --lines=50
					fi
				) | sed 's/^/\t/'
				echo "==============="
			fi
		done

		retval=1
	fi
fi

sudo rm -rf $tmpfile ${tmpfile}.gold ${tmpfile}.test ${tmpfile}.gold.dir ${tmpfile}.test.dir
test "$retval" = 0 && sudo rm -rf $workdir

exit $retval
