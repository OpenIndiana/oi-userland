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
install driver dialog
"""
import os
import sys
import gtk
import gtk.glade
import gobject
import gettext
from executingterminal import ExecutingTerminal
from ConfigParser import ConfigParser

DDUCONFIG = ConfigParser()
DDUCONFIG.read(os.path.join(os.path.dirname(os.path.realpath( 
                            sys.argv[0])),"ddu.conf"))
ABSPATH = DDUCONFIG.get('general','abspath')

try:
    gettext.bindtextdomain('ddu','%s/i18n' % ABSPATH)
    gettext.textdomain('ddu')
    gtk.glade.bindtextdomain('ddu','%s/i18n' % ABSPATH)
except AttributeError:
    pass

_ = gettext.gettext

class InstDrv:
    """This Class is used to show install driver progress"""
    __finish = False
    __success = False
    def __init__(self, action, **arg):
        self.action = action
        self.arg = arg
        self.install_pid = ''
        gladepath = ABSPATH + '/data/hdd.glade'
        xml = gtk.glade.XML(gladepath, 'Inst_dri_dlg')
        self.inst_dlg = xml.get_widget('Inst_dri_dlg')

        self.label_inst = xml.get_widget('label_inst')
        self.label_list = xml.get_widget('label_list')
        self.progressbar_inst = xml.get_widget('progressbar_inst')
        self.button_ok = xml.get_widget('button_ok')
        self.button_ok.connect('clicked', lambda x: self.inst_dlg.destroy())
        self.expander = xml.get_widget('expander1')
        self.expander.connect("notify::expanded", self.expanded)
        vtebox = xml.get_widget('hbox9')
        self.virterm = ExecutingTerminal()
        vtebox.pack_start(self.virterm)
        vtesb = gtk.VScrollbar(self.virterm.get_adjustment())
        vtebox.pack_start(vtesb, False, False, 0)
        self.inst_dlg.set_resizable(False)
        self.inst_dlg.connect('map_event', self.on_map_event)
        self.inst_dlg.show_all()

    def expanded(self, widget, param_spec, data = None):
        """expand dialog"""
        del param_spec, data
        if widget.get_expanded():
            self.inst_dlg.set_resizable(True)
        else:
            self.inst_dlg.set_resizable(False)

    def run(self):
        """show dialog"""
        self.inst_dlg.run()
        self.inst_dlg.destroy()

    def on_map_event(self, event, param):
        """invoke install session"""
        del event, param
        while gtk.gdk.events_pending():
            gtk.main_iteration(False)
        self.button_ok.set_sensitive(False)

        self.install_pid = self.virterm.execute_command(self.action, self.arg)

        gobject.timeout_add(100, self.pro)
        gobject.timeout_add(12000, self.destroy_actor)
	

    def pro(self):
        """determine whether install succeed"""
        try:
            os.kill(self.install_pid, 0)
            self.progressbar_inst.pulse()
        except OSError:
            status = self.virterm.get_child_exit_status()
            if status == 0:
                errmg = _("Installation Successful!")
                msg = \
            _('Reboot your system after installing the driver if necessary\n')
                msg += _('This window will be closed in a few seconds')
                self.__success = True
            else:
                errmg = _("Installation Failed!")
                msg = _("")
            self.label_list.set_markup( 
                            "<span foreground=\"#FF0000\">%s</span>" % errmg)
            self.label_inst.set_markup( 
                            "<span foreground=\"#FF0000\">%s</span>" % msg)
            self.button_ok.set_sensitive(True)
            self.__finish  = True
        return not self.__finish

    def destroy_actor(self):
        """destroy dialog automatically if install OK"""
        if self.__success == True:
            self.inst_dlg.destroy()
        return not self.__finish
