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

class WindowArea(object):
    '''Small class to describe an curses window area
    '''


    def __init__(self, lines = None, columns = None, y_loc = None,
                 x_loc = None, scrollable_lines = None):
        '''
        lines -> height
        columns -> width
        y_loc -> START y location
        x_loc -> START x location
        scrollable_lines -> Size of the scrollable area of this WindowArea.
            This attribute is only relevant for ScrollWindows
        '''
        
        self.lines = lines
        self.columns = columns
        self.y_loc = y_loc
        self.x_loc = x_loc
        self.scrollable_lines = scrollable_lines
    
    def relative_to_absolute(self, window):
        '''Translate coordinates from window relative to absolute
        
        This function will translate coordinates from being relative to
        the passed in curses.window, to being absolute coordinates (based
        against the entire terminal)'''
        
        start_coords = window.getbegyx()
        self.y_loc += start_coords[0]
        self.x_loc += start_coords[1]
    
    def absolute_to_relative(self, window):
        '''Translate coordinates from absolute to window relative
        
        This function translates absolute coordinates (based on entire
        terminal) to coordinates relative to the passed in window.'''
        
        start_coords = window.getbegyx()
        self.y_loc -= start_coords[0]
        self.x_loc -= start_coords[1]
