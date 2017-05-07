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
import types
import curses
from curses.ascii import ctrl
from copy import copy
import dircache
import re
import os
import threading
import commands
from DDU.ddu_errors import DDUException
from DDU.ddu_package import ddu_package_object
from DDU.ddu_devdata import ddu_dev_data
from DDU.ddu_repo import ddu_repo_object
from DDU.ddu_function import ddu_build_repo_list
from DDU.ddu_function import ddu_devscan
from DDU.ddu_function import ddu_package_lookup
from DDU.ddu_function import ddu_install_package

KEY_ESC = 27
KEY_BS = 127 # Backspace code that curses doesn't translate right
KEY_TAB = ord(ctrl('i'))
KEY_ENTER = ord(ctrl('j'))

media_path = ''
repo_name = ''
MAXLENGTH = 10
ABSPATH = "/usr/ddu"
installation_package = None

class InnerWindow(object):
    '''Wrapper around curses.windows objects providing common functions
    
    An InnerWindow wraps around a curses window, and represents an area
    of the screen. Each InnerWindow requires a parent window. The 'ultimate'
    parent of all InnerWindows is the sole instance of MainWindow.
    
    By default, InnerWindows have functions for adding text, processing input,
    and managing children InnerWindows.
    '''
    
    '''The following variables are used to indicate the status of ESC key
    navigations.
    
    begin_esc_sequence indicates that the next keystroke, if 0-9, should be
    translated to F#
    
    use_esc_sequence indicates that, at some point during program execution,
    ESC has been pressed, and the footer should, for the remainder of program
    execution, print Esc-#_<description> for navigation descriptions. Once set
    to True, it should never be set back to False.
    
    update_footer_text is a flag that indicates that Esc was just hit for the
    first time, and the managing window should immediately update the footer
    text.
    TODO: If we can call MainWindow.show_actions() directly, this flag won't
    be necessary
    '''
    begin_esc_sequence = False
    use_esc_sequence = False
    update_footer_text = False
    just_reshow = False
    
    def no_ut_refresh(self):
        self.window.noutrefresh()
    
    def _set_color(self, color):
        '''Sets the color attributes to 'color'
        
        This private method immediately updates the background color.
        Note that it doesn't reference self.color'''
        self.window.bkgd(ord(' '), color)
        self.no_ut_refresh()
    
    def _get_area(self, window, area):
        '''Create a copy of area, and adjust its coordinates to be absolute
        if needed'''
        area = copy(area)
        if isinstance(window, InnerWindow):
            area.relative_to_absolute(window.window)
        elif window is not None:
            area.relative_to_absolute(window)
        return area
    
    def _init_win(self, window, area):
        '''Create a curses window over the given area
        
        If window is provided, use it to translate area to absolute coords
        If it's none, assume area is already in absolute coords
        '''
        self.window = curses.newwin(area.lines, area.columns, area.y_loc, area.x_loc)
    
    def __init__(self, area, window = None, color_theme = None, color = None,
                 highlight_color = None, at_index = None):
        ''' Build an InnerWindow
        
        area (required): Describes the area to use when building this window.
        Coordinates should be relative to window, if window is given. If window
        is not given, these must be absolute coordinates on the terminal
        
        window (optional): The parent window. If given, area is assumed to indicate
        a location within the parent. Additionally, if window is an InnerWindow,
        window.add_object(self) is called to register this new window with its
        parent
        
        color_theme (required if curses window): The color theme for this window. This property
        gets propagated to subwindows. If None, the parent window's color_theme
        is used. Unless this window requires unique coloring, the
        parent theme should be used.
        
        color (optional): The color attributes for this window. If None,
        color_theme.default is used. In general, this parameter is reserved
        for subclasses of InnerWindow. Other consumers should pass in an
        appropriate color_theme.
        
        highlight_color (optional): Color attributes for this window when
        'selected' or 'highlighted.' Defaults to color (meaning
        no highlighting is used. In general, this parameter is reserved
        for subclasses of InnerWindow. Other consumers should pass in an
        appropriate color_theme
        '''
        area = self._get_area(window, area)
        self.color_theme = color_theme
        if isinstance(window, InnerWindow):
            window.add_object(self, at_index)
            if self.color_theme is None:
                self.color_theme = window.color_theme
        self._init_win(window, area)
        
        if color is not None:
            self.color = color
        else:
            self.color = self.color_theme.default
        
        if highlight_color is not None:
            self.highlight_color = highlight_color
        else:
            self.highlight_color = self.color
        
        self._set_color(self.color)
        
        self.window.keypad(1)
        self.objects = []
        self.texts_full = []
        self.active_object = None
        self._init_key_dict()
        self.directory_start = 0
        self.directory_end = 0
        self.start_point = 0
        self.end_point = MAXLENGTH
        self.repo_index = 0
        self.super_obj = None
        self.super_win = None
        self.InputWindow_FirstIndex = None
        self.objects_full = []
        

    def reset(self):
        self.objects = []
        self.objects_full = []
        self.texts_full = []
        self.active_object = None
        self.InputWindow_FirstIndex = None
        self.start_point = 0
        self.end_point = MAXLENGTH
        self.repo_index = 0
        self.directory_start = 0
        self.directory_end = 0
        self.repo_index = 0

    
    def make_active(self):
        self._set_color(self.highlight_color)
    
    def make_inactive(self):
        self._set_color(self.color)
    
    def _set_footer_color(self, color):
        '''Special private version of _set_color for "footers"
        
        This version sets the color of the four windows that make up the
        footer / border
        '''
        self.color = color
        self.window.bkgd(ord(' '), self.color)
        self.no_ut_refresh()
        self.left.bkgd(ord(' '), color)
        self.left.noutrefresh()
        self.right.bkgd(ord(' '), color)
        self.right.noutrefresh()
        self.top.bkgd(ord(' '), color)
        self.top.noutrefresh()
    
    def activate_object(self, index):
        '''Set a specific object to be the active object.
        
        This function accepts either an integer index,
        or an object reference. If an object reference is
        passed in, it must be an object in this InnerWindow.objects
        list
        
        Integers that are out of bounds of the size of the objects list
        are shifted to be in bounds.
        '''
        if type(index) != types.IntType:
            index = self.objects.index(index)
        else:
            index = index % len(self.objects)
        if self.active_object is not None:
            self.objects[self.active_object].make_inactive()
        self.objects[index].make_active()
        self.active_object = index
   
    def add_text(self, text, start_y = 0, start_x = 0, max_chars = None):
        '''Add a single line of text to the window
        
        'text' must fit within the specified space, or a curses.error will be
        thrown by the underlying calls to addstr.
        '''
        if max_chars is None:
            self.window.addstr(start_y, start_x, text)
        else:
            self.window.addnstr(start_y, start_x, text, max_chars)
        self.no_ut_refresh()
        
    def add_paragraph(self, text, start_y = 0, start_x = 0, max_y = None, max_x = None):
        '''Add a block of text to the window
        
        This function will split a block of text at newline characters (\\n)
        and at whitespace, and add it to the screen. Text that doesn't
        fit in the space indicated is not displayed.
        
        The number of lines used is returned
        '''
        win_size_y, win_size_x = self.window.getmaxyx()
        if max_y is None:
            max_y = win_size_y - start_y
        if max_x is None:
            max_x = win_size_x
        max_chars = max_x - start_x
        
        text_lines = text.expandtabs(4).splitlines()
        y_index = start_y
        
        num_lines = 0
        for line in text_lines:
            if len(line) <= max_chars:
                self.add_text(line, y_index, start_x, max_chars)
            else:
                start_pt = 0
                end_pt = 0
                while end_pt + max_chars < len(line):
                    start_pt = end_pt
                    end_pt = line.rfind(" ", start_pt, start_pt + max_chars)
                    if end_pt == -1:
                        end_pt = start_pt + max_chars
                    self.add_text(line[start_pt:end_pt].lstrip(), y_index, start_x, max_chars)
                    y_index += 1
                    if y_index > max_y:
                        break
                self.add_text(line[end_pt:].lstrip(), y_index, start_x, max_chars)
            y_index += 1
            if y_index > max_y:
                break
        return y_index - start_y
    
    def add_object(self, object, missing_driver_object=None, at_index = None):
        '''Add an object (usually an InnerWindow) to this window's object list
        '''
        if at_index is None:
            at_index = len(self.objects)
        if not object in self.objects:
            self.objects.insert(at_index, object)

    def add_string(self, text, at_index = None ):
        '''
        add text to this windows's object texts list
        '''
        if at_index is None:
            at_index = len(self.texts_full)
        if not text in self.texts_full:
            self.texts_full.insert(at_index, text)

    
    def clear(self):
        '''Remove all objects from this window's list and clear the screen
        
        The background of this window will still be displayed; clear the parent
        if the window should be removed in entirety'''
        for object in self.objects:
            object.clear()
        self.objects = []
        self.active_object = None
        self.window.clear()
        self._set_color(self.color)
    
    def on_key_down(self, input):
        global media_path
        from toplist_window import Toplist_Window
        from media_window import Media_Window
        logging.log(5, "InnerWindow.on_key_down")
        if self.active_object is not None:
            index = self.active_object + 1
            if index > MAXLENGTH and \
            (isinstance(self.objects[self.active_object], Media_Window) or \
             isinstance(self.objects[self.active_object], Toplist_Window)):
                if (self.end_point+1) < len(self.texts_full):
                    self.start_point += 1
                    self.end_point += 1
                    object_index = 0
                    for loop in range(self.start_point, self.end_point+1):
                        if loop == 0:
                            item_space = '-  '
                        elif loop == len(self.texts_full) -1:
                            item_space = '-  '
                        else:
                            item_space = '|  '

                        self.objects[object_index].set_text(
                                           item_space + self.texts_full[loop],
                                           max_chars = 50)
                        object_index += 1
                        self.no_ut_refresh()
                else:
                    pass
                try:
                    if isinstance(self.objects[self.active_object],
                                        Media_Window):
                        media_path = self.texts_full[self.end_point]
                except IndexError:
                    pass
            else:
                self.activate_object(index)
                try:
                    if isinstance(self.objects[self.active_object],
                                        Media_Window):
                        media_path = self.texts_full[self.start_point + index]
                except IndexError:
                    pass
            return None
        else:
            return input
    
    def on_key_up(self, input):
        global media_path
        from media_window import Media_Window
        from toplist_window import Toplist_Window
        logging.log(5, "InnerWindow.on_key_up")
        if self.active_object is not None:
            index = self.active_object - 1
            if index < 0 and \
            ( isinstance(self.objects[self.active_object], Media_Window)  or \
              isinstance(self.objects[self.active_object], Toplist_Window) ) :
                if (self.start_point-1) >= 0:
                    self.start_point -= 1
                    self.end_point -= 1
                    object_index = 0
                    for loop in range(self.start_point, self.end_point+1):
                        if loop == 0:
                            item_space = '-  '
                        elif loop == len(self.texts_full) -1:
                            item_space = '-  '
                        else:
                            item_space = '|  '
                        self.objects[object_index].set_text(
                                            item_space + self.texts_full[loop],
                                            max_chars = 50)

                        object_index += 1
                    self.no_ut_refresh()
                else:
                    pass
                try:
                    if isinstance(self.objects[self.active_object],
                                        Media_Window):
                        media_path = self.texts_full[self.start_point]
                except IndexError:
                    pass
            else:
                self.activate_object(index)
                try:
                    if isinstance(self.objects[self.active_object],
                                        Media_Window):
                        media_path = self.texts_full[self.start_point + index]
                except IndexError:
                    pass
            return None
        else:
            return input

    def on_key_enter(self, input):
        global media_path
        global installation_package
        from toplist_window import Toplist_Window
        from media_window import Media_Window

        if self.active_object is None:
            return input
        if isinstance(self.objects[self.active_object], Media_Window):
            text_full_bak = []
            if self.directory_start == 0 and self.directory_end == 0:
                self.directory_start = self.active_object
                self.directory_end = self.active_object
            if (self.active_object + self.start_point) <= self.directory_start:
                index_start = 0
                while index_start < (self.active_object+ self.start_point):
                    text_full_bak.append(self.texts_full[index_start])
                    index_start += 1
                text_full_bak.append(
                              self.texts_full[self.active_object +
                              self.start_point])
                index_start += 1
                directory_start_bak = index_start
                dircache.reset()
                try:
                    dirlist = dircache.listdir(
                                     self.texts_full[self.active_object +
                                     self.start_point])
                    for diritem in dirlist:
                        if re.search('[^a-z0-9A-Z/_\\- \\.]', diritem) is None:
                            displayname = os.path.join(
                                           self.texts_full[self.active_object +
                                           self.start_point],
                                           diritem)
                            text_full_bak.append(displayname)
                            index_start += 1
                except OSError:
                    pass

                directory_end_bak = index_start-1
                index_start -= 1
                index_start_temp = self.active_object+self.start_point + 1
                while index_start_temp < self.directory_start:
                    if not self.texts_full[index_start_temp] in text_full_bak:
                        text_full_bak.append(self.texts_full[index_start_temp])
                    index_start += 1
                    index_start_temp += 1

                index_start = self.directory_end + 1
                while index_start < len(self.texts_full):
                    if not self.texts_full[index_start] in text_full_bak:
                        text_full_bak.append(self.texts_full[index_start])
                    index_start += 1

            elif (self.active_object+self.start_point) >= self.directory_end:
                index_start = 0
                while index_start < self.directory_start:
                    text_full_bak.append(self.texts_full[index_start])
                    index_start += 1
                index_start_temp = self.directory_end + 1
                while index_start_temp < (self.active_object +
                                          self.start_point):
                    text_full_bak.append(self.texts_full[index_start_temp])
                    index_start += 1
                    index_start_temp += 1
                text_full_bak.append(
                              self.texts_full[self.active_object +
                              self.start_point])
                index_start += 1
		
                directory_start_bak = index_start
                dircache.reset()
                try:
                    dirlist = dircache.listdir(
                                       self.texts_full[self.active_object +
                                       self.start_point])
                    for diritem in dirlist:
                        if re.search('[^a-z0-9A-Z/_\\- \\.]', diritem) is None:
                            displayname = os.path.join(
                                          self.texts_full[self.active_object +
                                          self.start_point],
                                          diritem)
                            text_full_bak.append(displayname)
                            index_start += 1
                except OSError:
                    pass
                directory_end_bak = index_start - 1
                index_start_temp = self.active_object + self.start_point + 1
                while index_start_temp < len(self.texts_full):
                    if not self.texts_full[index_start_temp] in text_full_bak:
                        text_full_bak.append(self.texts_full[index_start_temp])
                    index_start_temp += 1
                    index_start += 1
            else:
                index_start = 0
                while index_start < self.directory_start:
                    text_full_bak.append(self.texts_full[index_start])
                    index_start += 1
                text_full_bak.append(
                              self.texts_full[self.active_object +
                              self.start_point])
                index_start += 1
                directory_start_bak = index_start
                dircache.reset()
                try:
                    dirlist = dircache.listdir(
                                     self.texts_full[self.active_object +
                                     self.start_point])
                    for diritem in dirlist:
                        if re.search('[^a-z0-9A-Z/_\\- \\.]', diritem) is None:
                            displayname = os.path.join(
                                          self.texts_full[self.active_object +
                                          self.start_point],
                                          diritem)
                            text_full_bak.append(displayname)
                            index_start += 1
                except OSError:
                    pass

                directory_end_bak = index_start - 1
                index_start = self.directory_end + 1

                while index_start < len(self.texts_full):
                    if not self.texts_full[index_start] in text_full_bak:
                        text_full_bak.append(self.texts_full[index_start])
                    index_start += 1
		
            self.super_obj.object_reset()
            self.directory_start = directory_start_bak
            self.directory_end = directory_end_bak

            if len(text_full_bak) > MAXLENGTH:
                for index in range(len(text_full_bak)):
                    if index == 0:
                        item_space = '-  '
                    elif index == len(text_full_bak) -1:
                        item_space = '- '
                    else:
                        item_space = '|  '
                    self.super_obj.object_insert(
                                   self.super_obj,
                                   item_space + text_full_bak[index])
            else:
                for index in range(len(text_full_bak)):
                    self.super_obj.object_insert(
                                   self.super_obj,text_full_bak[index])
            self.super_obj.main_win.show_actions()
            self.super_obj.main_win.do_update()
            self.activate_object(self.directory_start-self.start_point)
            try:
                media_path = text_full_bak[self.directory_start]
            except IndexError:
                self.activate_object(
                     self.directory_start - self.start_point - 1)
            self.no_ut_refresh()
        elif isinstance(self.objects[self.active_object], Toplist_Window):
            if self.super_win is not None:
                tt = threading.Thread(
                               target = self.super_win.information_dsp,
                               args = ( ">>>Looking for driver information...","status"
                               ))
                tt.start()
            dev_data = self.objects[self.start_point +
                                    self.active_object].query_tuple
            try:
                package_candi = ddu_package_lookup(dev_data, [])
            except DDUException:
                if self.super_win is not None:
                    tt = threading.Thread(
                                   target =  self.super_win.information_dsp,
                                   args = (
                                   ">>>Looking for driver information failed!","error"
                                   ))
                    tt.start()
                    return None
            if package_candi.get_pkg_type() == 'PKG' or \
               package_candi.get_pkg_type() == 'SVR4':
                self.objects[1].set_repo(package_candi.get_pkg_location())
                self.objects[2].set_repo(package_candi.get_pkg_name())
                self.activate_object(2)
                installation_package = package_candi
                if self.super_win is not None:
                    self.super_win.main_win.status_line.clear_err()
                    return None
            else:
                if self.super_win is not None:
                    tt = threading.Thread(
                       target =  self.super_win.information_dsp,
                       args = (">>>Looking for driver information failed!","error"))
                    tt.start()
                    return None
        return input

    def on_key_f2(self, input):
        global media_path
        global installation_package
        global repo_name
        from toplist_window import Toplist_Window
        from input_window import InputWindow
        from media_window import Media_Window
        install_ok = False

        if isinstance(self, Toplist_Window):
            window_pointer = self.win.super_win
            inner_window_p = self.win
        else:
            window_pointer = self.super_win
            inner_window_p = self
        if InnerWindow.just_reshow == True:
            text0 = ''
            text1 = ''
            text2 = ''

            if  inner_window_p.objects[0].textbox.gather() != '':
                text0="".join(inner_window_p.objects[0].text_buff)
            if  inner_window_p.objects[1].textbox.gather() != '':
                text1="".join(inner_window_p.objects[1].text_buff)
            if  inner_window_p.objects[2].textbox.gather() != '':
                text2="".join(inner_window_p.objects[2].text_buff)

            window_pointer.setup_layout()
            window_pointer.look_through()

            if text0 != '':
                inner_window_p.objects[0].set_repo(str(text0))
                self.activate_object(0)
            if text1 != '':
                inner_window_p.objects[1].set_repo(str(text1))
                self.activate_object(1)
            if text2 != '':
                inner_window_p.objects[2].set_repo(str(text2))
                self.activate_object(2)
            InnerWindow.just_reshow = False
            return

        try:
            if inner_window_p.objects[0].textbox.gather() == '' or \
               inner_window_p.objects[1].textbox.gather() == '' or \
               inner_window_p.objects[2].textbox.gather() == '':
                pass
        except IndexError:
            return input


        if installation_package != None:
            if window_pointer != None:
                tt = threading.Thread(
                             target = window_pointer.information_dsp, 
                             args = (">>>Install driver...","status"))
                tt.start()
            try:
                ddu_install_package(installation_package, "/")
                install_ok = True
            except DDUException:
                install_ok = False

        elif re.search('\w', str(media_path)) != None:
            package_path = str(media_path)
            media = os.path.basename(package_path)
            location = os.path.dirname(package_path)
            if window_pointer != None:
                tt = threading.Thread(
                             target = window_pointer.information_dsp,
                             args = (
			     ">>>Install driver...","status"
                             ))
                tt.start()

            status, output = commands.getstatusoutput(
                             '%s/scripts/file_check.sh UNK "%s" "%s"' %
			     (ABSPATH,media,location))

            if status == 0:
                 install_ok = True
            else:
                try:
                    logfile = open('/tmp/ddu_err.log', 'a')
                    logfile.write(str(output))
                    logfile.close()
                except IOError:
                    pass
          
                install_ok = False

        elif re.search(
                '\w',inner_window_p.objects[0].textbox.gather()) != None:
            package_path = "".join(inner_window_p.objects[0].text_buff)
            inner_window_p.objects[0].text_buff = []
            media = os.path.basename(package_path)
            location = os.path.dirname(package_path)
            if window_pointer != None:
                tt = threading.Thread(
                               target = window_pointer.information_dsp,
                               args = (
			       ">>>Install driver...","status"
                               ))
                tt.start()

            status, output = commands.getstatusoutput(
                             '%s/scripts/file_check.sh UNK "%s" "%s"' % (
			     ABSPATH, media, location))

            if status == 0:
                install_ok = True
            else:
                try:
                    logfile = open('/tmp/ddu_err.log', 'a')
                    logfile.write(str(output))
                    logfile.close()
                except IOError:
                    pass
                install_ok = False

        elif re.search('\w', str(repo_name)) != None and re.search(
                '\w',inner_window_p.objects[2].textbox.gather()) != None:
            repo_name = str(repo_name)
            package_name = self.objects[2].textbox.gather()

            if window_pointer != None:
                tt = threading.Thread(
                               target = window_pointer.information_dsp,
			       args=(">>>Install driver...","status"))
                tt.start()

            status, output = commands.getstatusoutput(
                             '%s/scripts/file_check.sh IPS "%s" "%s"' % (
			     ABSPATH, package_name, repo_name))

            if status == 0:
                install_ok = True
            else:
                try:
                    logfile = open('/tmp/ddu_err.log', 'a')
                    logfile.write(str(output))
                    logfile.close()
                except IOError:
                    pass
                install_ok = False

        elif re.search('\w', inner_window_p.objects[1].textbox.gather()) != \
             None and \
             re.search('\w',inner_window_p.objects[2].textbox.gather()) != \
             None:
            repo_name = inner_window_p.objects[1].textbox.gather().strip()
            package_name = inner_window_p.objects[2].textbox.gather().strip()

            if window_pointer != None:
                tt = threading.Thread(
                               target = window_pointer.information_dsp,
			       args = (">>>Install driver...","status"))
                tt.start()

            status, output = commands.getstatusoutput(
                             '%s/scripts/file_check.sh IPS "%s" "%s"' % (
			     ABSPATH, package_name, repo_name))
            if status == 0:
                install_ok = True
            else:
                try:
                    logfile = open('/tmp/ddu_err.log', 'a')
                    logfile.write(str(output))
                    logfile.close()
                except IOError:
                    pass

                install_ok = False

        installation_package = None
        media_path = ''

        window_pointer.setup_layout()
        if install_ok == True:
            tt = threading.Thread(
                   target = window_pointer.information_dsp,
                   args = (
                 	     ">>>Install driver successfully! rescan device...","success"
                     ))
            tt.start()
        else:
            tt = threading.Thread(
                   target = window_pointer.information_dsp,
                   args = (
                 	     ">>>Install driver fail! rescan device...","error"
                     ))
            tt.start()

        tdev = threading.Thread(target = window_pointer.reshow,
                                              name = "rescan device")
        tdev.start()

        return

    def on_key_f4(self, input):
        logging.debug("F4 comming:%s" % str(media_path))
        return

    def no_action(self, input):
        return input

    def on_key_f5(self, input):
        global repo_name
        from media_window import Media_Window
        if not isinstance(self.active_object, int):
            return None
        if isinstance(self.objects[self.active_object], Media_Window):
            media1 = self.texts_full[self.active_object +
                                     self.start_point].split('/')[1]
            media2 = self.texts_full[self.active_object +
                                     self.start_point].split('/')[2]
            eject_name = '/' + media1 + '/' + media2
            status, output = commands.getstatusoutput(
                             '/usr/bin/eject -l| grep \"%s\"' % eject_name)
            if status == 0:
                eject_media = output.split(" ")[0]
                status, output = commands.getstatusoutput(
                                '/usr/bin/eject -f %s' % eject_media)
            self.super_obj.object_reset()
            self.super_obj.items_reset()
        else:
            try:
                repo_len = len(self.repo_candi)
                if len(self.repo_candi) > 0:
                    self.objects[1].set_repo(
                         str(
                         self.repo_candi[self.repo_index % repo_len].repo_name
                         ))
                    repo_name = str(
                         self.repo_candi[self.repo_index % repo_len].repo_name)
                    self.repo_index += 1
            except AttributeError:
                repo_list = []
                status, output = commands.getstatusoutput(
                                         '%s/scripts/pkg_relate.sh list all' %
                                         ABSPATH)
                if status == 0:
                    output_lines = output.splitlines()
                    for line in output_lines:
                        repo_name_candi = line.split('\t')
                        repo_list.append(
                                  (repo_name_candi[0],repo_name_candi[1]))

                self.repo_candi = ddu_build_repo_list(repo_list)
                repo_len = len(self.repo_candi)
                if len(self.repo_candi) > 0:
                    self.objects[1].set_repo(
                         str(
                         self.repo_candi[self.repo_index % repo_len].repo_name
                         ))
                    repo_name = str(
                                self.repo_candi[self.repo_index %
                                repo_len].repo_name)
                    self.repo_index += 1
            self.activate_object(1)
        return None


    def process(self, input):
        '''Process keyboard input
        
        Keyboard input is handled in a "bottom-up" manner. If this window
        has an active object, the input is passed down to it. If the input isn't
        handled by the object, we try to handle it. If we can't handle it,
        we pass it back up the chain.
        '''
        if self.active_object is not None:
            input = self.objects[self.active_object].process(input)
        handler = self.key_dict.get(input, self.no_action)
        return handler(input)
    
    def _init_key_dict(self):
        '''Map some keystrokes by default:
        
        KEY_DOWN -> InnerWindow.on_key_down
        KEY_UP -> InnerWindow.on_key_up
        '''
        self.key_dict = {}
        self.key_dict[curses.KEY_DOWN] = self.on_key_down
        self.key_dict[curses.KEY_UP] = self.on_key_up
        #self.key_dict[curses.KEY_F3] = self.on_key_enter
        self.key_dict[curses.KEY_F5] = self.on_key_f5
        self.key_dict[curses.KEY_F2] = self.on_key_f2
        self.key_dict[curses.KEY_ENTER] = self.on_key_enter

    def translate_input(self, input):
        '''Translate keyboard input codes
        
        This function will translate keyboard input.
        It's primary job is understanding Esc-# sequences and turning them
        into F# key codes. It also converts 127 to KEY_BACKSPACE, since curses
        does not seem to properly understand it, and converts TAB and ENTER
        to KEY_DOWN (TAB, ENTER, and DOWN all move to the next field)
        '''
        global media_path
        logging.log(5, "Got char input %s" % curses.keyname(input) +
                    " (char code %d)" % input)
        if InnerWindow.begin_esc_sequence:
            logging.log(5, "Ending esc-sequence")
            InnerWindow.begin_esc_sequence = False
            if curses.ascii.isdigit(input):
                logging.log(5, "Valid esc-sequence, converting to KEY_FN")
                return input - ord('0') + curses.KEY_F0
            else:
                logging.log(5, "Invalid esc-sequence, returning raw input")
        elif input == KEY_ESC:
            logging.log(5, "Beginning esc-sequence")
            if not InnerWindow.use_esc_sequence:
                InnerWindow.use_esc_sequence = True
                InnerWindow.update_footer_text = True
            InnerWindow.begin_esc_sequence = True
            return None
        if input == KEY_BS:
            logging.log(5, "Translating char code %d to KEY_BACKSPACE" % input)
            input = curses.KEY_BACKSPACE
        elif input == curses.KEY_ENTER or input == KEY_ENTER:
            logging.log(5, "Translating char code %d to KEY_ENTER" % input)
            input = curses.KEY_ENTER
        elif input == curses.KEY_F5:
            input = curses.KEY_F5
        elif input == curses.KEY_F2:
            input = curses.KEY_F2
        elif input == curses.KEY_F3:
            from toplist_window import Toplist_Window
            from media_window import Media_Window
            if isinstance(self, Toplist_Window):
                input = curses.KEY_ENTER
                return input
            elif isinstance(self, Media_Window):
                media_path = ''
            else:
                return None
        elif input == curses.KEY_F4:
            from toplist_window import Toplist_Window
            from input_window import InputWindow
            from media_window import Media_Window
            if isinstance(self, Toplist_Window) or \
                  isinstance(self, InputWindow):
                pass
            elif isinstance(self, Media_Window):
                self.win.super_obj.object_reset()
                self.win.super_obj.items_reset()
                return None
            else:
                self.super_obj.object_reset()
                self.super_obj.items_reset()
                return None
        elif input == ord(ctrl('L')):
            from toplist_window import Toplist_Window
            from input_window import InputWindow
            from media_window import Media_Window
            if isinstance(self, Toplist_Window) or \
                  isinstance(self, InputWindow):
                InnerWindow.just_reshow = True
                return curses.KEY_F2
            elif isinstance(self, Media_Window):
                self.win.super_obj.object_reset()
                self.win.super_obj.items_reset()
                return None

        return input
    
    def getch(self):
        '''InnerWindow.getch() searches downward to find the active object.
        Once found, the active object's window.getch() function is called.
        
        This function is required to ensure that curses.window.getch() is
        called from the active object. Curses will update the console
        differently based on which window calls getch()'''
        if self.active_object is not None:
            return self.objects[self.active_object].getch()
        else:
            input = self.window.getch()
            return self.translate_input(input)
