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

import curses
import curses.ascii
import curses.panel as panel
import logging

from __init__ import _
import screen_list as screen_list
from color_theme import ColorTheme
from action import Action
from inner_window import InnerWindow
from window_area import WindowArea
from error_window import ErrorWindow


def show_help(current = None):
    return None


class MainWindow(object):
    '''
    classdocs
    '''
    
    def _reset_actions(self):
        self.continue_action = Action(curses.KEY_F2, _("Continue"), screen_list.get_next_group)
        self.back_action = Action(curses.KEY_F3, _("Back"), screen_list.previous_screen)
        self.help_action = Action(curses.KEY_F6, _("Help"), lambda x: None)
        self.quit_action = Action(curses.KEY_F9, _("Quit"), screen_list.quit)
        self.set_default_actions()
    
    def __init__(self, initscr, theme = None, force_bw=False):
        '''
        Constructor
        '''
        
        if theme is not None:
            self.theme = theme
        else:
            self.theme = ColorTheme(force_bw=force_bw)
        
        self.initscr = initscr
        self.begin_esc_sequence = False
        self.use_esc_sequence = False
        self.reset()
        
    def pause(self):
        self.central_area.window.getch()
    
    def do_update(self):
        curses.doupdate()
        
    def reset(self):
        window_size = self.initscr.getmaxyx()
        win_size_y = window_size[0]
        win_size_x = window_size[1]
        footer_area = WindowArea(1, win_size_x, win_size_y - 1, 0)
        self.footer = InnerWindow(footer_area, color_theme = self.theme, color = self.theme.border)
        self.footer.top = self.initscr.derwin(1, win_size_x, 0, 0)
        self.footer.left = self.initscr.derwin(win_size_y - 2, 1, 1, 0)
        self.footer.right = self.initscr.derwin(win_size_y - 2, 1, 1, win_size_x - 1)
        self.footer._set_color = self.footer._set_footer_color
        self.footer._set_color(self.theme.border)
        header_area = WindowArea(1, win_size_x - 2, 1, 1)
        self.header = InnerWindow(header_area, color_theme = self.theme,
                                                   color = self.theme.header)
        central_winarea = WindowArea(win_size_y - 3, win_size_x - 2, 2, 1) 
        self.central_area = InnerWindow(central_winarea, color_theme = self.theme)

        status_area=WindowArea(1, win_size_x - 2, win_size_y - 2, 1)
        self.status_line = ErrorWindow(status_area,
                                          color_theme=self.theme,
                                          highlight_color=self.theme.status_msg)

        success_area=WindowArea(1, win_size_x - 2, win_size_y - 2, 1)
        self.success_line = ErrorWindow(success_area,
                                          color_theme=self.theme,
                                          highlight_color=self.theme.success_msg)

        error_area = WindowArea(1, win_size_x - 2, win_size_y - 2, 1)
        self.error_line = ErrorWindow(error_area,
                                          color_theme=self.theme,
                                          highlight_color=self.theme.error_msg)

        self._reset_actions()
        
    def clear(self):
        self.header.clear()
        self.footer.clear()
        self.central_area.clear()
        self.error_line.clear_err()
        self.status_line.clear_err()
        self.success_line.clear_err()
        self._reset_actions()
    
    def set_header_text(self, header_text):
        length = len(header_text)
        max_x = self.header.window.getmaxyx()[1]
        if length > max_x:
            raise ValueError, "Header Text exceeds maximum window width"
        start_x = (max_x - length) / 2
        self.header.window.addstr(0, start_x, header_text)
        self.header.window.noutrefresh()
    
    def set_default_actions(self):
        self.actions = {}
        self.actions[self.continue_action.key] = self.continue_action
        self.actions[self.back_action.key] = self.back_action
        self.actions[self.help_action.key] = self.help_action
        self.actions[self.quit_action.key] = self.quit_action
        
    def show_actions(self):
        self.footer.window.clear()
        if InnerWindow.use_esc_sequence:
            prefix = "Esc-"
        else:
            prefix = "F"
        strings = []
        for key in sorted(self.actions.keys()):
            strings.append(" ")
            strings.append(prefix)
            strings.append(str(key - curses.KEY_F0))
            strings.append("_")
            strings.append(self.actions[key].text)
        display_str = "".join(strings)
        max_len = self.footer.window.getmaxyx()[1]
        length = len(display_str)
        if not self.use_esc_sequence:
            length += (len("Esc-") - len("F")) * len(self.actions)
        if length > max_len:
            raise ValueError, "Can't display footer actions"
        self.footer.window.addstr(display_str)
        self.footer.window.noutrefresh()
    
    def getch(self):
        input = self.central_area.getch()
        if InnerWindow.update_footer_text:
            InnerWindow.update_footer_text = False
            self.show_actions()
        return input
    
    def process_input(self, current_screen):
        while True:
            input = self.getch()
            input = self.central_area.process(input)
            if self.actions.has_key(input):
                return self.actions[input].do_action(current_screen)
            self.do_update()
    
    def show_help(self):
        return None
    
    def show(self):
        self.do_update()
        self.header.window.getch()
        raise NotImplementedError, "This method is not intended for general use"
