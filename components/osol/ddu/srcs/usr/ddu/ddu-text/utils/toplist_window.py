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

from inner_window import InnerWindow
import logging

class Toplist_Window(InnerWindow):
    '''
    classdocs
    '''


    def __init__(self, area, window = None, color_theme = None, color = None,
                highlight_color = None, at_index = None, text = "",
                query_tuple=None):
        '''
        Constructor
        '''
        if color_theme is None:
            color_theme = window.color_theme
        if color is None:
            color = color_theme.default
        if highlight_color is None:
            highlight_color = color_theme.list_field
        
        super(Toplist_Window, self).__init__(area, window, color_theme, 
                color, highlight_color, at_index)
        self.query_tuple = query_tuple

        self.win = window

        self.set_text(text)
    
    def set_text(self, text):
        self.window.clear()
        if len(str(text)) > (70-1):
            self.add_text(str(text)[:70 - len(str(text)) - 1])
        else:
            self.add_text(str(text))

    def on_key_enter(self, input):
        logging.log(5, "toplistWindow.on_key_enter")
        return input

    def on_key_f5(self, input):
        logging.log(5, "toplistWindow.on_key_f5")
        return input
