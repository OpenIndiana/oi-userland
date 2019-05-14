#! /usr/bin/python2.7
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
Show a dialog to display hardware detail information
"""

import os
import sys
import gtk
import gtk.glade
import pango
import re
from functions import insert_one_tag_into_buffer
from ConfigParser import ConfigParser
import gettext
try:
    import pygtk
    pygtk.require("2.0")
except ImportError:
    print "Please install pyGTK or GTKv2 or set your PYTHONPATH correctly"
    sys.exit(1)

DDUCONFIG = ConfigParser()
DDUCONFIG.read(os.path.join( 
               os.path.dirname(os.path.realpath(sys.argv[0])),"ddu.conf"))
ABSPATH = DDUCONFIG.get('general','abspath')

try:
    gettext.bindtextdomain('ddu','%s/i18n' % ABSPATH)
    gettext.textdomain('ddu')
    gtk.glade.bindtextdomain('ddu','%s/i18n' % ABSPATH)
except AttributeError:
    pass


_ = gettext.gettext

class DetailInf:
    """
    detail information dialog
    """
    class _impl:
        """ Implementation of the singleton interface """
        def __init__(self):
            pass
        def spam(self):
            """
            make single instance, if detail dialog has shown up and user
            click another hardware item in main window, then that hardware's
            detail information will be displayed directly in detail dialog so
            only one dialog instance exists.
            """
            return id(self)
		
    __instance = None

    def __init__(self, data='', driver='', device='', fg=''):
        if DetailInf.__instance is None:
            DetailInf.__instance = DetailInf._impl()
            self.__setattr__("abspath", ABSPATH)
            self.__setattr__("gladepath", self.__getattr__("abspath") + 
                             '/data/hdd.glade')
            self.__setattr__("detail_inf_inst", gtk.glade.XML(
                             self.__getattr__("gladepath"), 'detail_inf_dlg'))
            self.__setattr__("detail_infdlg", 
                             self.__getattr__("detail_inf_inst").get_widget( 
                             'detail_inf_dlg'))
            self.__setattr__("det_label", self.__getattr__(
                             "detail_inf_inst").get_widget('det_label'))
            self.__getattr__("detail_infdlg").connect(
                             "response",self.on_response)
            self.__getattr__("detail_infdlg").connect( 
                             "focus_out_event", lambda a1, a2:None)
            self.__setattr__("close_button", self.__getattr__( 
                             "detail_inf_inst").get_widget('close_button2'))
            self.__getattr__("close_button").connect( 
                             "clicked", self.on_close)
            self.__setattr__("detailtext_view", self.__getattr__( 
                             "detail_inf_inst").get_widget('detailtext_view'))
            self.__getattr__("detailtext_view").modify_font( 
                             pango.FontDescription('DejaVu Sans mono'))
            self.__setattr__("textbuffer", self.__getattr__( 
                             "detailtext_view").get_buffer())
            insert_one_tag_into_buffer(self.__getattr__("textbuffer"), 
                             "bold", "weight", pango.WEIGHT_BOLD)
            self.data = data

        self.__dict__['_Singleton__instance'] = DetailInf.__instance

        self.__getattr__("textbuffer").delete( 
                         self.__getattr__("textbuffer").get_start_iter(), 
                         self.__getattr__("textbuffer").get_end_iter())

        line_iter = self.__getattr__("textbuffer").get_iter_at_offset (0)
	
        line_iter = self.__getattr__("textbuffer").get_end_iter()
	
        self.__getattr__("det_label").set_markup( 
                         "<span weight=\"bold\">%s</span>" % device)

        if driver != '':
            driverurl = driver
            self.__getattr__("textbuffer").insert_with_tags_by_name( 
                         line_iter,_("Driver URL:"),"bold")
            self.__getattr__("textbuffer").insert( \
                         line_iter,str(driverurl.pkg_location.strip(
                                                 '\t\r\n') + '\n'))

        detail_file = open(data,"r")
        for line in detail_file.readlines():
            line_iter = self.__getattr__("textbuffer").get_end_iter()
            pre_line = re.compile('[a-zA-Z0-9]')
            if pre_line.search(line):
                line_disp = line.split(':')
                if line_disp[0] != '':
                    if len(line_disp) > 1:
                        self.__getattr__(
                             "textbuffer").insert_with_tags_by_name(
                              line_iter,str(
                              line_disp[0].strip('\t\n\r') + ":"), "bold")
                        space_need = 35 - len(line_disp[0])
                        while space_need > 0:
                            self.__getattr__(
                            "textbuffer").insert_with_tags_by_name( 
                            line_iter,str(' '), "bold")
                            space_need = space_need - 1
                    else:
                        self.__getattr__( 
                             "textbuffer").insert_with_tags_by_name(
                             line_iter,str(line_disp[0].strip(
                             '\t\n\r') + "\n"), "bold")
                        line_disp[0].strip('\t\n\r')+":"
			
                    if len(line_disp) > 1:
                        if len(line_disp) < 3:
                            self.__getattr__( 
                                 "textbuffer").insert(
                                  line_iter,str(
                                  line_disp[1]).strip('\t\n\r\ ') + '\n')
                        else:
                            self.__getattr__( 
                                "textbuffer").insert(
                                line_iter,str(
                                line_disp[1]).strip('\t\n\r\ ') + ':')
                index = 2
                while index < len(line_disp):
                    if line_disp[index] != '':
                        self.__getattr__("textbuffer").insert( 
                             line_iter,str( 
                             line_disp[index]).strip('\t\n\r\ ') + '\n')
                        index = index + 1
            else:
                pass
        detail_file.close()
        os.remove(data)
        self.__getattr__("detail_infdlg").show()
        if fg == 'reload':
            self.__getattr__("detail_infdlg").hide()
            self.__getattr__("detail_infdlg").show()
        return

    def __getattr__(self, attr):
        """ Delegate access to implementation """
        return getattr(self.__instance, attr)

    def __setattr__(self, attr, value):
        """ Delegate access to implementation """
        return setattr(self.__instance, attr, value)

    def on_close(self, widget):
        """quit dialog"""
        del widget
        try:
            os.remove(self.data)
        except OSError:
            pass
        self.__getattr__("detail_infdlg").destroy()
        DetailInf.__instance = None
        self.__dict__['_Singleton__instance'] = None
        return

    def on_response(self, widget, response):
        """quit dialog"""
        del widget
        try:
            os.remove(self.data)
        except OSError:
            pass
        if response == gtk.RESPONSE_DELETE_EVENT:
            self.__getattr__("detail_infdlg").destroy()
            DetailInf.__instance = None
            self.__dict__['_Singleton__instance'] = None
        return
