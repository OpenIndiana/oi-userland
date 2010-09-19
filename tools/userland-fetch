#!/usr/bin/python2.6
#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#
# Copyright (c) 2010, Oracle and/or it's affiliates.  All rights reserved.
#
#
# fetch.py - a file download utility
#
#  A simple program similiar to wget(1), but handles local file copy, ignores
#  directories, and verifies file hashes.
#

import os
import sys

def validate(filename, hash):
	import hashlib

	try:
		file = open(filename, 'r')
	except IOError:
		return False

	if (hash == None):
		return True

	algorithm, value = hash.split(':')
	try:
		m = hashlib.new(algorithm)
	except ValueError:
		return False

	while True:
		block = file.read()
		m.update(block)
		if block == '':
			break

	return m.hexdigest() == value

def download(url, filename = None, hash = None, verbose = False):
	from urllib import splittype, urlopen
	import hashlib

	src = None
	filename = None

	#print "Downloading %s from %s" % (filename, url)

	# open the download source
	if splittype(url)[0]:
		try:
			src = urlopen(url)
		except IOError:
			return None
		remote_name = src.geturl().split('/')[-1]
	elif os.path.isfile(url):
		os.symlink(url, filename)
		return filename, filehash(filename)
		src = open(url, 'r')
		remote_name = url.split('/')[-1]
	else:
		return None

	if filename == None:
		filename = remote_name

	# if we have a source to download, open a destination and copy the data
	if src:
		dst = open(filename, 'wb');
		if verbose:
			print "Downloading %s from %s" % (filename, url)
		while True:
			block = src.read()
			if block == '':
				break;
			dst.write(block)
		dst.close()

	# return the name of the file that we downloaded the data to.
	return filename

def download_paths(search, filename):
	tmp = os.getenv('DOWNLOAD_SEARCH_PATH')
	if tmp:
		search += tmp.split(' ')
	base = os.path.basename(filename)

	urls = list()

	for path in search:
		urls.append(path+'/'+base)

	return urls

def usage():
	print "Usage: %s [-v|--verbose] [-f|--file (file)] [-h|--hash (hash)] --url (url)" % (sys.argv[0].split('/')[-1])
	sys.exit(1)

def main():
	from urllib import splittype, urlopen
	import getopt
	import sys

	# FLUSH STDOUT 
	sys.stdout = os.fdopen(sys.stdout.fileno(), 'w', 0)

	verbose = False
	filename = None
	url = None
	hash = None
	search = list()

	try:
		opts, args = getopt.getopt(sys.argv[1:], "f:h:s:u:v",
			["file=", "hash=", "search=", "url=", "verbose"])
	except getopt.GetoptError, err:
		print str(err)
		usage()

	for opt, arg in opts:
		if opt in [ "-f", "--file" ]:
			filename = arg
		elif opt in [ "-h", "--hash" ]:
			hash = arg
		elif opt in [ "-s", "--search" ]:
			search.append(arg)
		elif opt in [ "-u", "--url" ]:
			url = arg
		elif opt in [ "-v", "--verbose" ]:
			verbose = True
		else:
			assert False, "unknown option"

	if url == None:
		usage()

	print "Fetching %s" % filename

	if validate(filename, hash):
		print "\tcurrent copy is ok, nothing to do"
		sys.exit(0)

	# generate a list of URLS to search for a suitable download
	urls = download_paths(search, filename)
	urls.append(url)

	for url in urls:
		print "\tTrying %s..." % url,

		if os.path.isfile(url):
			os.symlink(url, filename)
		elif splittype(url)[0]:
			if download(url, filename) == None:
				print "failed"
				continue

		print "retrieved...",

		if validate(filename, hash):
			print "validated"
			sys.exit(0)
		else:
			print "corrupt"

		try:
			os.remove(filename)
		except OSError:
			pass

	sys.exit(1)

if __name__ == "__main__":
	main()
