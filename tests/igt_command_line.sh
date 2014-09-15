#!/bin/sh
#
# Copyright © 2014 Intel Corporation
#
# Permission is hereby granted, free of charge, to any person obtaining a
# copy of this software and associated documentation files (the "Software"),
# to deal in the Software without restriction, including without limitation
# the rights to use, copy, modify, merge, publish, distribute, sublicense,
# and/or sell copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice (including the next
# paragraph) shall be included in all copies or substantial portions of the
# Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
# THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
# IN THE SOFTWARE.

#
# Check that command line handling works consistently across all tests
#

for test in `cat single-tests.txt multi-tests.txt`; do

	if [ "$test" = "TESTLIST" -o "$test" = "END" ]; then
		continue
	fi

	# if the test is a script, it will be in $srcdir
	if [ ! -x $test ]; then
		if [ -x $srcdir/$test ]; then
			test=$srcdir/$test
		fi
	fi

	echo "$test:"

	# check invalid option handling
	echo "  Checking invalid option handling..."
	./$test --invalid-option 2> /dev/null && exit 99

	# check valid options succeed
	echo "  Checking valid option handling..."
	./$test --help > /dev/null || exit 99

	# check --list-subtests works correctly
	echo "  Checking subtest enumeration..."
	./$test --list-subtests > /dev/null
	if [ $? -ne 0 -a $? -ne 79 ]; then
		exit 99
	fi

	# check invalid subtest handling
	echo "  Checking invalid subtest handling..."
	./$test --run-subtest invalid-subtest > /dev/null 2>&1 && exit 99
done