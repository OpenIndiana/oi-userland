#! /usr/bin/python2.7
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
# Copyright (c) 2008, 2010, Oracle and/or its affiliates. All rights reserved.
#
"""
used for execute command in a virtual xterm
"""

import sys
import gtk
try:
    import vte
except ImportError:
    sys.path.append('/usr/lib/python2.7/vendor-packages/gtk-2.0')
    import vte


class ExecutingTerminal(vte.Terminal):
    """
    run a system command in a virtual xterm
    """
    def __init__(self):
        vte.Terminal.__init__(self)

        self.connect('eof', self.execute_finish_callback)
        self.connect('child-exited', self.execute_finish_callback)
        self.execution = None

    def execute_command(self, action, args):
        """execute a command"""
        self.execution = True
        pid = self.fork_command(action, ( 
                                str(action), str(args["install_method"]),
                                str(args["install_media"]), 
                                str(args["install_server"])))
        return pid
        while self.execution:
            gtk.main_iteration()

    def execute_finish_callback(self, terminal):
        """exit command"""
        del terminal

        self.execution = False
