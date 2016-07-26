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
diaplay missing driver device
"""

import curses
import logging

import main_window as main_window
from __init__ import _
import inner_window
from inner_window import InnerWindow
from window_area import WindowArea
from toplist_window import Toplist_Window
from input_window import InputWindow
from base_screen import BaseScreen
from action import Action
from media_window import Media_Window
import screen_list as screen_list
import threading, time
from DDU.ddu_package import ddu_package_object
from DDU.ddu_repo import ddu_repo_object
from DDU.ddu_function import ddu_build_repo_list
from DDU.ddu_function import ddu_devscan
from DDU.ddu_function import ddu_package_lookup
from DDU.ddu_function import ddu_install_package


MAXLENGTH = 10
MISSING_DRIVER_BAK = []

class DeviceScreen(BaseScreen):
    '''
    classdocs
    '''


    def __init__(self, main_win):
        '''
        Constructor
        '''
        
        super(DeviceScreen, self).__init__(main_win)
        self.end_index = 0

    def set_actions(self):
        super(DeviceScreen, self).set_actions()
        self.main_win.actions.pop(self.main_win.continue_action.key, None)
        self.main_win.actions.pop(self.main_win.back_action.key, None)
        self.main_win.actions.pop(self.main_win.help_action.key, None)

        self.main_win.install_action = Action(curses.KEY_F2, "Install",
		                            screen_list.dummy)
        self.main_win.actions[self.main_win.install_action.key] = \
		                            self.main_win.install_action

        self.main_win.auto_search = Action(curses.KEY_F3, "Auto-Search",
		                            screen_list.dummy)
        self.main_win.actions[self.main_win.auto_search.key] = \
		                            self.main_win.auto_search

        self.main_win.continue_action = Action(curses.KEY_F4, "Media",
		                               screen_list.get_next_group)
        self.main_win.actions[self.main_win.continue_action.key] = \
		                            self.main_win.continue_action

        self.main_win.repo_action = Action(curses.KEY_F5,  "Repository",
		                         screen_list.dummy)
        self.main_win.actions[self.main_win.repo_action.key] = \
		                         self.main_win.repo_action


    def information_dsp(self, text, msg_type=None):
        """
        show a information text at the enf of curse window
        """
        if msg_type == "status":
            self.main_win.status_line.display_err(text)
        elif msg_type == "error":
            self.main_win.error_line.display_err(text)
        elif msg_type == "success":
            self.main_win.success_line.display_err(text)

    def look_through(self):
        """
        look up missing driver
        """
        global MISSING_DRIVER_BAK
        global media_path
        win_size_y, win_size_x = self.main_win.central_area.window.getmaxyx()
        if len(MISSING_DRIVER_BAK) > 0:
            missing_driver = MISSING_DRIVER_BAK
        else:
            missing_driver = ddu_devscan()
            MISSING_DRIVER_BAK = missing_driver

        menu_item_max_width = 70
        menu_item_offset = 3
        menu_item_desc_offset = menu_item_max_width - menu_item_offset - 1
        menu_item_desc_max = win_size_x - menu_item_desc_offset
        y_loc = 4
        self.end_index = 0
        try:
            if isinstance(self.main_win.central_area.objects[0], InputWindow):
                pass
        except IndexError:
            return
        
        if isinstance(self.main_win.central_area.objects[0], InputWindow):
            while self.end_index < len(missing_driver):
                option =  Toplist_Window(WindowArea(
                                        1,
                                        menu_item_max_width,
                                        y_loc,
                                        menu_item_offset),
                        	        window = self.main_win.central_area,
                                        text = _(
                                   missing_driver[self.end_index].description),
                                        query_tuple = missing_driver[
                                                      self.end_index]
                                        )

                self.main_win.central_area.add_string (
                              missing_driver[self.end_index].description)

                self.end_index += 1
                y_loc += 1

            if inner_window.media_path != '':
                self.main_win.central_area.activate_object(0)
            else:
                self.main_win.central_area.activate_object(3)

        self.main_win.status_line.clear_err()
        self.main_win.success_line.clear_err()
        self.main_win.error_line.clear_err()
        self.main_win.do_update()

    def setup_layout(self):
        self.main_win.clear()
        self.set_actions()
        self.main_win.show_actions()
        self.main_win.central_area.reset()
        self.main_win.set_header_text(_("Device Driver Utility"))

        win_size_y, win_size_x = self.main_win.central_area.window.getmaxyx()
        y_loc = 1

        intro = _('''The following devices do not have drivers. Select a device, specify a driver location using F3, F4, F5, or typing, then press F2 to install.''')
        self.main_win.central_area.add_paragraph(
                                   intro, y_loc, 1, max_x = win_size_x - 1)

        menu_item_desc_offset = 3
        menu_item_desc_max = win_size_x - menu_item_desc_offset

        y_loc += 2

        y_loc = win_size_y/2
        self.main_win.central_area.add_text(
              _("Driver location: Pathname/URL, or Repository and Package."),
              y_loc, 1, win_size_x - 1)

        menu_item_max_width = 50
        menu_item_offset = 20
        menu_item_desc_offset = 3
        menu_item_desc_max = win_size_x - menu_item_desc_offset

        y_loc += 2
        pathname_option = InputWindow(WindowArea(
                                      1,
                                      menu_item_max_width,
                                      y_loc,
                                      menu_item_offset),
                                      window = self.main_win.central_area)
        if inner_window.media_path != '':
            pathname_option.set_repo(inner_window.media_path)
        self.main_win.central_area.add_text(_("Pathname/URL:"),
                                            y_loc,
                                            menu_item_desc_offset,
                                            menu_item_desc_max)
        y_loc += 1
        self.main_win.central_area.add_text(
                      _("SVR4, DU, or p5i file. F4 to browse media"),
                      y_loc,
                      menu_item_offset,
                      menu_item_desc_max)
        y_loc += 1
        space_chr = '-'  *  (win_size_x-10)

        self.main_win.central_area.add_text(_(space_chr),
                                            y_loc,
                                            menu_item_desc_offset,
                                            menu_item_desc_max)
        y_loc += 1
        repo_option = InputWindow(WindowArea(
                                  1,
                                  menu_item_max_width,
                                  y_loc,
                                  menu_item_offset),
                                  window = self.main_win.central_area)
        self.main_win.central_area.add_text(
                                   _("Repository:"),
                                   y_loc,
                                   menu_item_desc_offset,
                                   menu_item_desc_max)
        y_loc += 1
        self.main_win.central_area.add_text(_("F5 to change or enter URL"),
                                            y_loc,
                                            menu_item_offset,
                                            menu_item_desc_max)

        y_loc += 1
        package_option = InputWindow(WindowArea(
                                     1,
                                     menu_item_max_width,
                                     y_loc,
                                     menu_item_offset),
                                     window = self.main_win.central_area)
        self.main_win.central_area.add_text(
                                   _("Package:"),
                                   y_loc,
                                   menu_item_desc_offset,
                                   menu_item_desc_max)

        self.main_win.central_area.activate_object(pathname_option)

        self.main_win.central_area.super_win = self

    def show(self):
        """
        show device curse window
        """
        global media_path

        self.setup_layout()

        tt = threading.Thread(target = self.information_dsp,
                             args=(">>>Looking for missing driver device...","status"))
        tt.start()

        tdev = threading.Thread(target =  self.look_through,
                                name = "Lookthrough_Thread")
        tdev.start()
	
        self.main_win.do_update()
        return self.main_win.process_input(self)


    def reshow(self):
        """
        redraw device curse window
        """
        global MISSING_DRIVER_BAK
        MISSING_DRIVER_BAK = []
        self.look_through()
