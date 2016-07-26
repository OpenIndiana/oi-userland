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

from __init__ import _
import main_window
import commands
from inner_window import InnerWindow
from media_window import Media_Window
from base_screen import BaseScreen
from screen_list import get_next_group
from window_area import WindowArea
from action import Action
import curses
import screen_list as screen_list
import logging
import os
import re
from DDU.ddu_errors import DDUException
from DDU.ddu_package import ddu_package_object
from DDU.ddu_devdata import ddu_dev_data
from DDU.ddu_repo import ddu_repo_object
from DDU.ddu_function import ddu_build_repo_list
from DDU.ddu_function import ddu_devscan
from DDU.ddu_function import ddu_package_lookup
from DDU.ddu_function import ddu_install_package


MAXLENGTH = 10
ABSPATH = "/usr/ddu"
class MediaScreen(BaseScreen):
    '''
    classdocs
    '''
    
    def __init__(self, main_win):
        '''
        Constructor
        '''
        super(MediaScreen, self).__init__(main_win)
    
    def set_actions(self):
        super(MediaScreen, self).set_actions()
        self.main_win.actions.pop(self.main_win.continue_action.key, None)
        self.main_win.actions.pop(self.main_win.back_action.key, None)
        self.main_win.actions.pop(self.main_win.help_action.key, None)

        self.main_win.ok_action = Action(
                                  curses.KEY_F2,
                                  "OK",
                                  screen_list.previous_screen)
        self.main_win.actions[self.main_win.ok_action.key] = \
                             self.main_win.ok_action

        self.main_win.cancel_action = Action(
                                      curses.KEY_F3,
                                      "Cancel",
                                      screen_list.previous_screen)
        self.main_win.actions[self.main_win.cancel_action.key] = \
                              self.main_win.cancel_action

        self.main_win.refresh_action = Action(
                                       curses.KEY_F4,
                                       "Refresh",
                                       screen_list.dummy)
        self.main_win.actions[self.main_win.refresh_action.key] = \
                              self.main_win.refresh_action

        self.main_win.eject_action = Action(
                                     curses.KEY_F5,
                                     "Eject",
                                     screen_list.dummy)

        self.main_win.actions[self.main_win.eject_action.key] = \
                              self.main_win.eject_action

    
    def show(self):
        """
        show media curse window
        """
        self.main_win.clear()
        self.set_actions()
        self.main_win.show_actions()
        self.main_win.set_header_text(_("DDU - Browse Files"))
        self.main_win.central_area.clear()
        self.object_reset()

        win_size_y, win_size_x = self.main_win.central_area.window.getmaxyx()
        self.y_loc = 1

        intro = _('''Select a SVR4, DU or P5i driver file. Use the up/down arrows to highlight a device/directory and press ENTER to select it. Repeat until the desired file has been selected. CDs, DVDs, and USB devices are automatically mounted in /media. USB devices are umounted when unplugged. To umount a CD/DVD, highlight it and press F5.''')

        self.main_win.central_area.add_paragraph(
                      intro, self.y_loc , 1, max_x = win_size_x - 1)
                      
        self.y_loc += 6
        self.main_win.central_area.add_text(
                                   _("/media"), self.y_loc, 3, win_size_x - 1)

        self.end_index = 0
        self.y_loc += 1
        self.main_win.central_area.super_obj = self
        self.items_reset()
        self.main_win.do_update()
        return self.main_win.process_input(self)


    def object_reset(self):
        """
        show intro part of media curse window
        """
        self.main_win.clear()
        self.set_actions()
        self.main_win.show_actions()
        self.main_win.set_header_text(_("DDU - Browse Files"))
        self.main_win.central_area.clear()
        self.main_win.central_area.reset()

        win_size_y, win_size_x = self.main_win.central_area.window.getmaxyx()
        self.y_loc = 1

        intro = _('''Select a SVR4, DU or P5i driver file. Use the up/down arrows to highlight a device/directory and press ENTER to select it. Repeat until the desired file has been selected. CDs, DVDs, and USB devices are automatically mounted in /media. USB devices are umounted when unplugged. To umount a CD/DVD, highlight it and press F5.''')

        self.main_win.central_area.add_paragraph(
                                   intro,
                                   self.y_loc ,
                                   1,
                                   max_x = win_size_x - 1)
        self.y_loc += 6
        self.main_win.central_area.add_text(
                                   _("/media"),
                                   self.y_loc,
                                   3,
                                   win_size_x - 1)

        self.end_index = 0
        self.y_loc += 1
        self.main_win.do_update()

    def object_insert(self, super_obj, display_name):
        """
        show directory/file name 
        """
        win_size_y, win_size_x = self.main_win.central_area.window.getmaxyx()
        menu_item_max_width = 50
        menu_item_offset = 5
        menu_item_desc_offset = menu_item_max_width + menu_item_offset + 1
        menu_item_desc_max = win_size_x - menu_item_desc_offset
        display_strip = display_name.strip('-  ').strip('|  ')
        try:
            option =  Media_Window(WindowArea(
                                   1, menu_item_max_width,
                                   self.y_loc, menu_item_offset),
                                   window = self.main_win.central_area,
                                   end_index = self.end_index,
                                   text = _(display_name))
        except AttributeError:
            pass

        self.main_win.central_area.add_string(display_strip)
        self.end_index += 1
        self.y_loc += 1

    def items_reset(self):
        """
        show mounted media name in media curse window
        """
        menu_item_max_width = 50
        menu_item_offset = 5

        status, detail_output = commands.getstatusoutput(
                                         '%s/scripts/find_media.sh probe_s' %
                                         (ABSPATH))
        output_lines = detail_output.splitlines()

        for line in output_lines:
            media_name = line.split('|')
            if media_name[2] == 'Mounted':
                display_name = media_name[3]
                option =  Media_Window(
                                       WindowArea(
                                       1,
                                       menu_item_max_width,
                                       self.y_loc,
                                       menu_item_offset),
			               window = self.main_win.central_area,
                                       end_index = self.end_index,
                                       text = _(display_name))
                self.main_win.central_area.add_string(display_name)

                self.end_index += 1
                self.y_loc += 1
                self.main_win.central_area.activate_object(option)
        return
