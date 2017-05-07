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
# Copyright (c) 2008, 2010, Oracle and/or its affiliates. All rights reserved.
#

'''
Represent sets of curses background attributes as a 'theme' for the various
UI pieces of the text installer
'''


import curses


class ColorTheme(object):
    '''Represents a 'theme' for the text installer

    Note that 'color' can be any combination of curses attributes,
    not just color (e.g. bold, underline, etc)

    Note that attributes get OR'ed with any additional attributes. This means
    in the case of non-color attributes such as A_REVERSE and A_BOLD,
    they can't be removed easily in a temporary fashion.

    '''

    def __init__(self, border=None, header=None, default=None, edit_field=None,
                 highlight_edit=None, list_field=None, error_msg=None,
                 status_msg=None, success_msg=None,
                 inactive=None, progress_bar=None, force_bw=False):
        '''curses.start_color() must be called prior to instantiation of a
        ColorTheme, if the terminal supports colors. Terminals that don't
        support color are given a black and white theme.

        force_bw - If true, uses a black and white color theme, regardless of
                   whether the current terminal supports colors

        All other parameters should be either a positive integer, representing
        a bitwise OR of desired curses attributes for UI elements of that type,
        or None, in which case a default value is chosen.

        '''
        has_colors = curses.has_colors() and not force_bw

        if default is not None:
            self.default = default
        else:
            if has_colors:
                curses.init_pair(1, curses.COLOR_BLACK, curses.COLOR_WHITE)
                self.default = curses.color_pair(1) | curses.A_BOLD
            else:
                self.default = 0

        if border is not None:
            self.border = border
        else:
            if has_colors:
                curses.init_pair(2, curses.COLOR_WHITE, curses.COLOR_CYAN)
                self.border = curses.color_pair(2) | curses.A_BOLD
            else:
                self.border = curses.A_REVERSE

        if header is not None:
            self.header = header
        else:
            if has_colors:
                curses.init_pair(3, curses.COLOR_WHITE, curses.COLOR_BLUE)
                self.header = curses.color_pair(3) | curses.A_BOLD
            else:
                self.header = curses.A_REVERSE

        if edit_field is not None:
            self.edit_field = edit_field
        else:
            if has_colors:
                self.edit_field = self.default
            else:
                self.edit_field = self.default

        if highlight_edit is not None:
            self.highlight_edit = highlight_edit
        else:
            if has_colors:
                curses.init_pair(4, curses.COLOR_WHITE, curses.COLOR_BLUE)
                self.highlight_edit = curses.color_pair(4) | curses.A_BOLD
            else:
                self.highlight_edit = curses.A_REVERSE | curses.A_BOLD

        if list_field is not None:
            self.list_field = list_field
        else:
            if has_colors:
                curses.init_pair(5, curses.COLOR_WHITE, curses.COLOR_CYAN)
                self.list_field = curses.color_pair(5) | curses.A_BOLD
            else:
                self.list_field = curses.A_REVERSE | curses.A_BOLD

        if progress_bar is not None:
            self.progress_bar = progress_bar
        else:
            if has_colors:
                curses.init_pair(6, curses.COLOR_WHITE, curses.COLOR_RED)
                self.progress_bar = curses.color_pair(7)
            else:
                self.progress_bar = curses.A_REVERSE

        if success_msg is not None:
            self.success_msg = success_msg
        else:
            if has_colors:
                curses.init_pair(7, curses.COLOR_WHITE, curses.COLOR_GREEN)
                self.success_msg = curses.color_pair(7) | curses.A_BOLD
            else:
                self.success_msg = curses.A_REVERSE

        if status_msg is not None:
            self.status_msg = status_msg
        else:
            if has_colors:
                curses.init_pair(8, curses.COLOR_YELLOW, curses.COLOR_BLUE)
                self.status_msg = curses.color_pair(8) | curses.A_BOLD
            else:
                self.status_msg = curses.A_REVERSE

        if error_msg is not None:
            self.error_msg = error_msg
        else:
            if has_colors:
                curses.init_pair(9, curses.COLOR_WHITE, curses.COLOR_RED)
                self.error_msg = curses.color_pair(9) | curses.A_BOLD
            else:
                self.error_msg = curses.A_REVERSE

        if inactive is not None:
            self.inactive = inactive
        else:
            if has_colors:
                self.inactive = self.error_msg | curses.A_REVERSE
            else:
                self.inactive = 0

