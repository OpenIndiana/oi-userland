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
show submission dialog
"""
import os
import sys
import gtk
import gtk.glade
import gobject
import threading
import httplib
import pango
import gettext

from functions import insert_conf
from functions import insert_one_tag_into_buffer
from functions import insert_col_info
from functions import insert_col
from message_box import MessageBox
from ConfigParser import ConfigParser

try:
    import pygtk
    pygtk.require("2.0")
except ImportError:
    print "Please install pyGTK or GTKv2 or set your PYTHONPATH correctly"
    sys.exit(1)

DDUCONFIG = ConfigParser()
DDUCONFIG.read(os.path.join(os.path.dirname(os.path.realpath( 
               sys.argv[0])),"ddu.conf"))
ABSPATH       = DDUCONFIG.get('general','abspath')
VENDOR_SYSTEM = DDUCONFIG.get('vendor','system')
HCL_ENABLE    = DDUCONFIG.get('hcl','enable')
HCL_SITE      = DDUCONFIG.get('hcl','site')
HCL_CGI       = DDUCONFIG.get('hcl','cgi')

try:
    gettext.bindtextdomain('ddu','%s/i18n' % ABSPATH)
    gettext.textdomain('ddu')
    gtk.glade.bindtextdomain('ddu','%s/i18n' % ABSPATH)
except AttributeError:
    pass

_ = gettext.gettext

class SubmitDlg:
    """
    submit dialog
    """
    __finish = False
    __success = False
    def __init__(self, dev_submit):
        gladepath = ABSPATH + '/data/hdd.glade'
        xml = gtk.glade.XML(gladepath, 'submit_dlg')
        self.submit_dlg = xml.get_widget('submit_dlg')

        if not HCL_ENABLE in ("yes", "true", "t", "1"):
            inst = MessageBox(self.submit_dlg, _('Submit'),
                                  _('Submission disabled'),
                                  _('The '+ VENDOR_SYSTEM +' HCL server is not active'))
            inst.run()
            return

        self.submit_dlg.connect("response", self.on_response)

        conn = httplib.HTTPSConnection(HCL_SITE)
        try:
            conn.request("GET",HCL_CGI)
            resp = conn.getresponse()
            if resp.status != 200:
                inst = MessageBox(self.submit_dlg, _('Submit'),
                                  _('Submission failed'),
                                  _('The server is currently unavailable'))
                inst.run()
                return
        except IOError:
            inst = MessageBox(self.submit_dlg, _('Submit'),
                              _('Submission failed'),
                              _('The server is currently unavailable'))
            inst.run()
            return
        conn.close()

        """Necessary text value"""
        self.submit_notebook = xml.get_widget("submit_notebook")

        self.pro_sub = xml.get_widget('pro_sub')
        self.submit_button = xml.get_widget('submit_button')
        self.submit_button.connect("clicked", self.act_submit)

        self.close_button = xml.get_widget('close_button')
        self.close_button.connect("clicked", 
                                  lambda w:self.submit_dlg.destroy())

        self.save_button = xml.get_widget('submit_save')
        self.save_button.connect("clicked", self.act_save)

        self.manu_text = xml.get_widget('Manuf_name')
        self.manu_modle = xml.get_widget('Manuf_modle')
        self.manu_modle.set_sensitive(False)

        self.cpu_type = xml.get_widget('CPU_type')
        self.firmware_maker = xml.get_widget('Firmware_maker')
        insert_conf(self.manu_text, self.manu_modle, 
                    self.cpu_type, self.firmware_maker)

        self.name_ent = xml.get_widget('Name_ent')
        self.email_ent = xml.get_widget('Email_ent')

        self.server_com = xml.get_widget('Server_com')
        self.server_com.set_active(0)

        self.bios_set = xml.get_widget('Bios_set')

        self.general_ent = xml.get_widget('General_ent')
        self.inform_c = xml.get_widget('Information_c')
        self.label_warning = xml.get_widget('label_warning')

        textbuffer = self.inform_c.get_buffer()
        insert_one_tag_into_buffer(textbuffer, "bold", 
                                   "weight", pango.WEIGHT_BOLD)
	
        ag = gtk.AccelGroup()
        self.submit_dlg.add_accel_group(ag)

        self.submit_button.add_accelerator("clicked", ag, ord('s'), 
                                          gtk.gdk.MOD1_MASK, gtk.ACCEL_VISIBLE)
        self.close_button.add_accelerator("clicked", ag, ord('c'), 
                                          gtk.gdk.MOD1_MASK,gtk.ACCEL_VISIBLE)
        self.save_button.add_accelerator("clicked", ag, ord('a'), 
                                          gtk.gdk.MOD1_MASK,gtk.ACCEL_VISIBLE)

        self.label17 = xml.get_widget('label17')
        self.label17.set_mnemonic_widget(self.server_com)

        self.label15 = xml.get_widget('label15')
        self.label15.set_mnemonic_widget(self.manu_text)

        self.label11 = xml.get_widget('label11')
        self.label11.set_mnemonic_widget(self.firmware_maker)

        self.label9 = xml.get_widget('label9')
        self.label9.set_mnemonic_widget(self.cpu_type)

        self.label7 = xml.get_widget('label7')
        self.label7.set_mnemonic_widget(self.inform_c)

        self.label12 = xml.get_widget('label12')
        self.label12.set_mnemonic_widget(self.name_ent)

        self.label16 = xml.get_widget('label16')
        self.label16.set_mnemonic_widget(self.email_ent)

        self.label19 = xml.get_widget('label19')
        self.label19.set_mnemonic_widget(self.general_ent)

        xml.get_widget('label23').set_alignment(0, 0)

        insert_col_info(self.name_ent, self.email_ent, self.server_com, 
                        self.manu_text, self.manu_modle, self.cpu_type, 
                        self.firmware_maker, self.bios_set, 
                        self.general_ent, self.inform_c)

        self.submit_dlg.set_resizable(True)
        self.status = 1
        self.doc = None
        self.dev_submit = dev_submit
        self.submit_dlg.run()
        return

    def on_response(self, widget, response):
        """quit dialog"""
        del widget
        if response == gtk.RESPONSE_DELETE_EVENT:
            self.submit_dlg.destroy()

    def act_save(self, widget):
        """save submission in a local file"""
        del widget
        dialog = gtk.FileChooserDialog(_("Save..."),
                               None,
                               gtk.FILE_CHOOSER_ACTION_SAVE,
                               (gtk.STOCK_CANCEL, gtk.RESPONSE_CANCEL,
                               gtk.STOCK_SAVE, gtk.RESPONSE_OK))
        dialog.set_default_response(gtk.RESPONSE_OK)
        dialog.set_do_overwrite_confirmation(True)
        dialog.set_current_name("DDU.submit")

        file_filter = gtk.FileFilter()
        file_filter.set_name(_("All files"))
        file_filter.add_pattern("*")
        dialog.add_filter(file_filter)

        response = dialog.run()
        if response == gtk.RESPONSE_OK:
            self.doc = insert_col(self.name_ent, self.email_ent,
                                  self.server_com, self.manu_text,
                                  self.manu_modle, self.cpu_type,
                                  self.firmware_maker, self.bios_set,
                                  self.general_ent, self.inform_c,
                                  self.dev_submit)
            filesave = open(dialog.get_filename(),"w")
            filesave.write(self.doc.toprettyxml())
            filesave.close()
	     
        elif response == gtk.RESPONSE_CANCEL:
            pass
        dialog.destroy()

        return


    def act_submit(self, widget):
        """do submit"""
        del widget
        conn = httplib.HTTPSConnection(HCL_SITE)
        try:
            conn.request("GET",HCL_CGI)
            resp = conn.getresponse()
            if resp.status != 200:
                inst = MessageBox(self.submit_dlg, _('Submit'),
                                  _('Submission failed'),
                                  _('The server is currently unavailable'))
                inst.run()
                return
        except IOError:
            inst = MessageBox(self.submit_dlg, _('Submit'),
                              _('Submission failed'),
                              _('The server is currently unavailable'))
            inst.run()
            return
        conn.close()

        self.submit_notebook.set_current_page(1)
        self.submit_button.set_sensitive(False)
	
        while gtk.gdk.events_pending():
            gtk.main_iteration(False)
        gobject.timeout_add(100, self.pro)
        gobject.timeout_add(20000, self.destroy_actor)
	
        thread = threading.Thread(target = self.submit_run)
        thread.start()
	
        return


    def submit_run(self):
        """submit data"""
        self.doc = insert_col(self.name_ent, self.email_ent, self.server_com,
                              self.manu_text, self.manu_modle, self.cpu_type,
                              self.firmware_maker, self.bios_set,
                              self.general_ent, self.inform_c, self.dev_submit)


        boundary = '------DdU_Post_To_Hcl_BoUnDary$$'
        crlf = '\r\n'
        local_data = []

        local_data.append('--' + boundary)
        local_data.append('Content-Disposition: form-data; name=\"%s\"; \
                          filename=\"%s\"' % ("hclSubmittalXML", "uud.test"))
        local_data.append('')
        local_data.append(str(self.doc.toprettyxml(indent = "")))
        local_data.append('--' + boundary + '--')
        local_data.append('')

        body = crlf.join(local_data)
   
        content_type = 'multipart/form-data; boundary=%s' % boundary

        try:
            http_send = httplib.HTTPS(HCL_SITE)
            http_send.putrequest('POST', HCL_CGI)
            http_send.putheader('User-Agent','DDU 0.1')
            http_send.putheader('content-length', str(len(body)))
            http_send.putheader('content-type', content_type)
            http_send.endheaders()
            http_send.send(body)
            errcode, errmsg, headers = http_send.getreply()
            del errmsg, headers
            statuscode = errcode
            if statuscode != 200:
                self.__success = False
            else:
                self.__success = True
                self.__finish = True

        except IOError:
            self.__success = False
        http_send.close()
        self.__finish = True
        return
    
    def pro(self):
        """display submission result"""
        if self.__finish == False:
            self.pro_sub.pulse()
        else:
            if self.__success == True:
                msg = _('Submission Successful!\n')
                msg += _('Thank you for your submission.\n')
                msg += _('Your submission will now be reviewed before being '
                         'posted to the '+ VENDOR_SYSTEM +' HCL.\n')
                msg += _('To get more '+ VENDOR_SYSTEM +' HCL information, See:\n')
                msg += _(HCL_SITE)
                msg += _('This window will be closed in a few seconds')
            else:
                msg = _("Submission failed")
			
            self.label_warning.set_markup( 
                                   "<span foreground=\"#FF0000\">%s</span>" %
                                   msg)
        return not self.__finish


    def destroy_actor(self):
        """quit dialog"""
        if self.__success == True:
            self.submit_dlg.destroy()
        return not self.__success
