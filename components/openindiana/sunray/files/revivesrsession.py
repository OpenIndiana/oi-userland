#!/usr/bin/python3.9

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
# Copyright 2025 Carsten Grzemba
#

'''
 Reconnect SunRay X-session: some times after logout, the gdm will not start login screen on the X-session and the DTU remains in state 26D
 INSTALL: - cp to /opt/SUNWut/lib/gdm/revivesrsession.py
          - create script /etc/opt/SUNWut/gdm/SunRayPostSession/helpers/revivesession:
            /opt/SUNWut/lib/gdm/revivesrsession.py &
'''

import subprocess as sp
import re
import pdb
import time
import logging

logformat = "%(asctime)s %(levelname)s:%(message)s"
logging.basicConfig(format = logformat)
logger = logging.getLogger(__name__)

logger.setLevel(logging.DEBUG)

time.sleep(7)

pid = sp.Popen(['pgrep','gdm-binary'], stdout=sp.PIPE).stdout.readline().strip()
logger.debug("GDM pid %s ", pid.decode())
dpl = [ p.split()[2].strip(b':') for p in sp.Popen(['ptree', pid], stdout=sp.PIPE).stdout.readlines() if b'/opt/SUNWut/lib/Xnewt' in p ]
logger.debug("Xnewt display {}".format( dpl))

# error -4 gdm-simple-slave not started for Display, no UT sessions
for sess in sp.Popen(['/opt/SUNWut/sbin/utsession','-px'], stdout=sp.PIPE).stdout.readlines():
    logger.debug("{}".format(sess))
    for t in sess.split(b';'):
        if b'STATE' in t: state = t.split(b'=')[1]
        if b'DISPLAY' in t: disp = t.split(b'=')[1]
    if state == 0 and disp in dpl:
        # ok
        pass
    else:
        logger.debug("restart display %s"  % disp.decode())
        sp.Popen(['/opt/SUNWut/lib/gdm/utgdmdynamic','-a', disp])
