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
UI Component for displaying error messages
'''

import curses
import logging

from inner_window import InnerWindow


class ErrorWindow(InnerWindow):
    '''Simple subclass of InnerWindow for displaying and hiding errors
    
    This window is only intended for use with text content (adding subwindows
    to this class is undefined)
    
    '''
    
    FLASH_TIME = 250
    
    def __init__(self, area, window=None, color_theme=None, color=None,
                 highlight_color=None, centered=True, **kwargs):
        '''
        See InnerWindow.__init__
        
        color - defaults to color_theme.default
        highlight_color - defaults to color_theme.error_msg
        '''
        self.visible = False
        if color_theme is None:
            color_theme = window.color_theme
        if color is None:
            color = color_theme.default
        if highlight_color is None:
            highlight_color = color_theme.error_msg
        super(ErrorWindow, self).__init__(area, window, color_theme, color,
                                          highlight_color, **kwargs)
        self.window.timeout(ErrorWindow.FLASH_TIME)
    
    def display_err(self, text):
        '''Display error 'text'. Will also flash
        the error text if this box was already visible, to draw
        the user's attention to the new (or existing) error
        
        Restores cursor location after updating
        
        '''
        cursor_loc = curses.getsyx()
        self.clear()
        self.add_text(text)
        self.make_active()
        curses.setsyx(cursor_loc[0], cursor_loc[1])
        curses.doupdate()
        if self.visible:
            self.flash()
        self.visible = True
    
    def clear_err(self):
        '''Clear error text and mark this window inactive
        
        Restores cursor location after updating
        '''
        if self.visible:
            cursor_loc = curses.getsyx()
            self.clear()
            self.make_inactive()
            curses.setsyx(cursor_loc[0], cursor_loc[1])
            curses.doupdate()
            self.visible = False
    
    def flash(self):
        '''Flash this error window'''
        if self.visible:
            cursor_loc = curses.getsyx()
#            flash_color = self.highlight_color ^ curses.A_REVERSE
#            self.set_color(flash_color)
            curses.setsyx(cursor_loc[0], cursor_loc[1])
            curses.doupdate()
            gotch = self.window.getch()
            if gotch != -1:
                curses.ungetch(gotch)
#            self.set_color(self.highlight_color)
            curses.setsyx(cursor_loc[0], cursor_loc[1])
            curses.doupdate()
