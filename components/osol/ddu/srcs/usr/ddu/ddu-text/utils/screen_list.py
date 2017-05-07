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

import logging

screen_list = []
visited_list = []


def start_screen_list(window_list):
    global screen_list
    screen_list.extend(window_list)
    return screen_list[0]


def get_next_group(current = None):
    global visited_list
    global screen_list
    
    if current is not None:
        visited_list.append(current)
        current_index = screen_list.index(current) + 1
        if current_index < len(screen_list):
            return screen_list[current_index]
        else:
            return None
    else:
        return screen_list[0]


def previous_screen(current = None):
    global visited_list
    return visited_list.pop()


def go_to(current = None, next = None):
    global visited_list
    visited_list.append(current)
    return next


def quit(current = None):
    logging.debug("screen_list.quit triggered")
    return None

def dummy(current = None):
    pass
