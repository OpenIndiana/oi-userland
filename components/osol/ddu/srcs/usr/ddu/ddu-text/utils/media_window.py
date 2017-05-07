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
import string
import os
import re

MAXLENGTH = 10
objects_text = []
class Media_Window(InnerWindow):
    '''
    classdocs
    '''


    def __init__(self, area, window, end_index, color_theme = None, color = None,
                highlight_color = None, at_index = None, text = ""):
        '''
        Constructor
        '''
        if color_theme is None:
            color_theme = window.color_theme
        if color is None:
            color = color_theme.default
        if highlight_color is None:
            highlight_color = color_theme.list_field
        
        super(Media_Window, self).__init__(area, window, color_theme, 
                color, highlight_color, at_index)

        self.objects = []
        self.objects_full = []
        self.start_index = 0
        self.end_index = end_index
        self.start_point = 0
        self.win = window
        
        self.set_text(text)

    def set_text(self, text, start_y = 0, start_x = 0, max_chars = 0):
        """
        Media window item for display directory/file name
        """
        strip_text = text.strip('-  ').strip('|  ')
        objects_text.insert(len(objects_text), strip_text)
        self.window.clear()
        if self.end_index <= MAXLENGTH:
            base_name = os.path.basename(strip_text)
            first_slash_position = text.find('/')
            head_dsp = text[0:first_slash_position]
            directory_depth = len(re.findall('/', strip_text)) - 2
            item_space = ""
            for index_item in range(0, directory_depth):
                item_space += "  "
            disp_name = head_dsp+item_space+base_name
            if len(str(disp_name)) > (50-1):
                self.add_text(str(disp_name)[:50-len(str(disp_name))-1])
            else:
                self.add_text(str(disp_name))
        else:
            pass

    def on_key_enter(self, input):
        logging.log(5, "ZY mediaWindow.on_key_enter")
        return input

    def on_key_f5(self, input):
        logging.log(5, "ZY mediaWindow.on_key_f5")
        return input

    def on_key_f2(self, input):
        logging.log(5, "ZY mediaWindow.on_key_f2")
        trans_input = input + 1
        return trans_input
