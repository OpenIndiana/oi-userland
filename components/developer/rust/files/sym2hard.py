#!/usr/bin/python

import os
import sys
import uuid

random_unique_name = str(uuid.uuid4()) + str(uuid.uuid1())

dirs = ['src', 'build/tmp']
build_base = os.getcwd()

for dir in dirs:
    for root, d, files in os.walk(os.path.join(build_base, dir)):
        for name in files:
            fullname = os.path.join(root, name)
            tempname = os.path.join(root, random_unique_name)
            if os.path.islink(fullname):
                linkpath = os.readlink(fullname)
                # Rename current link to something temporary
                os.rename(fullname, tempname)
                try:
                    # Try to create hard link for the file
                    os.link(linkpath, fullname)
                    # If we succeeded, remove temporary file
                    os.unlink(tempname)
                    # print "Created  hardlink for %s" % fullname
                except:
                    # If we failed, rename the temporary file back, and abort with some meaningful info
                    e = sys.exc_info()[0]
                    sys.stderr.write("Hardlinking failed on %s, aborting !" % fullname)
                    os.rename(tempname, fullname)
                    sys.exit(e)
