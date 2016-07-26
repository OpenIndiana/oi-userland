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
import curses
from curses.textpad import Textbox
from curses.ascii import isprint, ctrl

from inner_window import InnerWindow

class InputWindow(InnerWindow):
    '''InputWindow represent editable text areas on the screen
    
    At any time, the text of the object can be accessed by
    referencing an InputWindow's 'text' parameter (edit_field.text).
    Note that this returns a list of character codes.
    '''


    def __init__(self, area, window = None, text = "", masked = False, 
                 color_theme = None, at_index = None):
        '''Unlike InnerWindow, this constructor WILL NOT TAKE
        curses.window objects for the window parameter - they must
        be InnerWindows.
        
        In general, specifying a specific color_theme is unnecessary, unless
        this instance requires a theme other than that of the rest of the
        program 
        
        window (required): A parent InnerWindow
        
        area (required): Describes the area within the parent window to be used.
        area.lines is overridden to 1.
        
        text (optional): The text in this field, before it is edited by
        the user. Defaults to empty string.
        
        masked (optional): If True, then this field will display bullets when
        the user types into it, instead of echo'ing the text
        
        color_theme (optional): The color_theme for this edit field. By default
        the parent window's theme is used. color_theme.edit_field is used
        as the background color; color_theme.highlight_edit is the background
        when this InputWindow is active.
        '''
        if color_theme is None:
            color_theme = window.color_theme
        color = color_theme.edit_field
        highlight_color = color_theme.highlight_edit
        
        area.lines = 1
        super(InputWindow, self).__init__(area, window, color_theme, 
                color, highlight_color, at_index)
        self.masked = masked
        self.masked_char = ord('*')
        self.old_cursor_state = 0

        self.textbox = Textbox(self.window)
        self.textbox.stripspaces = True
        self.set_text(text)

        self.text_buff = []
    
    def set_text(self, text):
        self.text = []
        for char in text:
            self.textbox.do_command(self.handle_input(ord(char)))
        self.no_ut_refresh()
    
    def set_repo(self, text):
        self.text = []
        self.textbox.do_command(ord(ctrl('a')))
        self.textbox.do_command(ord(ctrl('k')))
        for char in text:
            self.textbox.do_command(self.handle_input(ord(char)))
        self.no_ut_refresh()

    def handle_input(self, input):
        input = self.translate_input(input)
        if input in range(curses.KEY_F0, curses.KEY_F10) or \
                input == curses.KEY_UP or input == curses.KEY_DOWN:
            logging.debug("Got special key, breaking")
            self.input = input
            return ord(ctrl('g'))
        else:
            self.input = None
        if isprint(input):
            self.text_buff.append(chr(input))
            self.text.append(input)
            if not self.is_valid():
                if len(self.text) > 0:
                    self.text.pop()
                    length = len(self.text_buff)
                    temp_buff = self.text_buff[:length-49]
                    self.set_repo(self.text_buff[length-49:])
                    length = len(self.text_buff)
                    self.text_buff = temp_buff + self.text_buff[length-49:]
            if self.masked:
                input = self.masked_char
        elif input == curses.KEY_BACKSPACE or input == ord(ctrl('H')):
            if len(self.text) > 0:
                self.text.pop()
                self.text_buff.pop()
      
        return input
    
    def process(self, input):
        try:
            self.old_cursor_state = curses.curs_set(2)
        except curses.error:
            logging.debug("Got curses.error when enabling cursor")
        
        # Put input back on stack so that textbox.edit can read it
        try:
            curses.ungetch(input)
        except TypeError:
            pass

        self.textbox.do_command(ord(ctrl('e')))
        self.textbox.edit(self.handle_input)
        
        try:
            self.old_cursor_state = curses.curs_set(self.old_cursor_state)
        except curses.error:
            logging.debug("Got curses.error when reverting cursor")
        logging.debug("Returning: " + str(self.input))
        return self.input
    
    def is_special_char(self, input_key):
        '''Check to see if this is a keystroke that should break us out of
        adding input to the Textbox and return control to the parent window
        
        '''
        if (input_key in range(curses.KEY_F0, curses.KEY_F10) or
            input_key in self.key_dict):
            return True
        else:
            return False
        
    def is_valid(self):
        win_size_x = self.window.getmaxyx()[1]
        return len(self.text) < win_size_x
