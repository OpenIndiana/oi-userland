#!/usr/bin/python2.7
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

import signal
import curses
import logging
from sys import exit


from __init__ import _
from screen_list import start_screen_list
from main_window import MainWindow
from media_scan import MediaScreen
from device_scan import DeviceScreen


LOG_LOCATION = "/tmp/ddu_log"
LOG_FORMAT = "%(asctime)s - %(levelname)-8s: %(filename)s:%(lineno)d %(message)s"
LOG_LEVEL = 5


def setup_curses():
    initscr = curses.initscr()
    if curses.has_colors():
        curses.start_color()
    curses.noecho()
    curses.cbreak()
    try:
        curses.curs_set(0)
    except curses.error:
        pass
    return initscr


def cleanup_curses():
    curses.echo()
    curses.nocbreak()
    curses.endwin()


def exit_text_installer():
    logging.info("**** END ****")
    print _("Exiting Text Installer. Log is available at:\n%s") % LOG_LOCATION
    exit()


def setup_logging():
    logging.basicConfig(filename = LOG_LOCATION, level = LOG_LEVEL,
                        filemode = 'a', format = LOG_FORMAT)
    logging.addLevelName(5, "INPUT")
    logging.info("**** START ****")


def make_screen_list(main_win):
    result = []
    result.append(DeviceScreen(main_win))
    result.append(MediaScreen(main_win))
    return result


if __name__ == '__main__':
    setup_logging()
    try:
        initscr = setup_curses()
        win_size_y, win_size_x = initscr.getmaxyx()
        if win_size_y < 24 or win_size_x < 80:
            cleanup_curses()
            print _("Terminal too small. Min size is 80x24\n"), "\r"
            exit_text_installer()
        main_win = MainWindow(initscr)
        win_list = make_screen_list(main_win)
        screen = start_screen_list(win_list)
        while screen is not None:
            screen = screen.show()
    finally:
        cleanup_curses()
    exit_text_installer()
