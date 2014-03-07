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

#
# Copyright (c) 2014, Oracle and/or its affiliates. All rights reserved.
#

import errno
import os
import socket
import subprocess
import sys

target = sys.argv[1]
tdir = os.path.dirname(target)

os.chdir(tdir)

def find_free_port(base=1024, tries=10):
    s = socket.socket()
    for port in xrange(base, base + tries):
        try:
            s.bind(("", port))
        except socket.error, e:
            if e.errno != errno.EADDRINUSE:
                raise
            continue
        else:
            s.close()
        return port

# We want to isolate both the rabbit server and the epmd it might spawn, in case
# either one is already running on the machine (on ports 5672 and 4639,
# respectively).  We do so by specifying the ports they use, and we find a
# couple of free ports here.  This is obviously inherently racy, but it should
# be good enough.
epmd_port = find_free_port(4455)
rabbit_port = find_free_port(5677)

gmake = os.environ.get("GMAKE", "/usr/gnu/bin/make")

# Start up the rabbit server.  In order to use rabbit's makefile targets, we
# have to start it in two steps -- first the main server, then the core rabbit
# routines.  We put all the temporary directories in the build directory, and we
# have to set SCRIPT_DIR because of the way the scripts resolve symlinks when
# they find each other.  We also set PLUGINS_SRC_DIR to an empty value so that
# the rabbit makefile infrastructure doesn't try to rebuild .ez files or recopy
# them to the plugins dir.
ret = subprocess.call([gmake, "start-background-node", "start-rabbit-on-node",
    "ERL_EPMD_PORT=%d" % epmd_port, "RABBITMQ_NODE_PORT=%d" % rabbit_port,
    "SCRIPT_DIR=%s/scripts" % tdir, "RABBITMQ_LOG_BASE=%s/t" % tdir,
    "PLUGINS_SRC_DIR=", "RABBITMQ_MNESIA_DIR=%s/t/rabbit-mnesia" % tdir,
    "RABBITMQ_PLUGINS_EXPAND_DIR=%s/t/rabbit-plugins-scratch" % tdir])

if ret > 0:
    sys.exit(ret)

test_ret = subprocess.call([gmake, "run-tests", "PLUGINS_SRC_DIR=",
    "ERL_EPMD_PORT=%d" % epmd_port, "RABBITMQ_NODE_PORT=%d" % rabbit_port])

stopnode_ret = subprocess.call([gmake, "stop-node", "PLUGINS_SRC_DIR=",
    "ERL_EPMD_PORT=%d" % epmd_port, "RABBITMQ_NODE_PORT=%d" % rabbit_port])
stopepmd_ret = subprocess.call(["/usr/bin/epmd", "-kill"],
    env={"ERL_EPMD_PORT": str(epmd_port)})

# Return with the first non-zero exit code of the three previous commands.
ret = next((r for r in (test_ret, stopnode_ret, stopepmd_ret) if r > 0), 0)

sys.exit(ret)
