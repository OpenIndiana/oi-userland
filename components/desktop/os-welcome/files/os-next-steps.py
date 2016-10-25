#!/usr/bin/python2.7
# -*- coding: utf-8 -*-

#
# Copyright (c) 2008, 2016, Oracle and/or its affiliates. All rights reserved.
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

import locale
import gettext
from gettext import gettext as _
import os
import socket
import string
import subprocess
import re

import gi
gi.require_version('Gtk', '3.0')
from gi.repository import GObject, Gtk, Gdk, GdkPixbuf, Gio

def N_(message): return message

PACKAGE	  = "os-next-steps"
VERSION	  = "12"
GETTEXT_PACKAGE	  = "os-welcome"
LOCALEDIR = "/usr/share/locale"

release_string = "Oracle Solaris 12"

# There's probably a nicer way of including UTF-8 strings than this
bullet_point = u'\u2022'

default_link_color = Gdk.Color (0, 0, 65535)

# This needs to stay in sync with the method in /lib/svc/method/svc-webui-server
# for generating the hostname used in the site certificate to avoid TLS errors.
def get_solaris_dashboard_url():
	hostname = socket.gethostname()
	if hostname != '':
		p = subprocess.Popen(["/usr/sbin/host", hostname],
				     stdin=None, stdout=subprocess.PIPE,
				     stderr=None, shell=False, close_fds=True,
				     bufsize=-1)
		(stdoutdata, stderrdata) = p.communicate()
		if p.returncode == 0:
			hostname = stdoutdata.split(' ', 1)[0]
	if hostname == '':
		hostname = "localhost"
	return "https://%s:6787/" % hostname

help_link= {
	'header' : N_("Learn More about Oracle Solaris"),
	'icon' : "resources.png",
	'url_links' : [ ["http://docs.oracle.com/cd/E53394_01/pdf/E54847.pdf", N_("##What's new## with <b>Oracle Solaris 11.3</b>")], ["http://www.oracle.com/us/support/systems/index.html", N_("##Get world class support## with <b>Oracle Premier Support</b>")], [get_solaris_dashboard_url(), N_("##Explore## the <b>Oracle Solaris Dashboard</b> with system analytics and more")] ],
}

personalize_link= {
	'header' : N_("Use the GNOME Desktop"),
	'icon' : "gnome.png",
	'program_links' : [  ["yelp.desktop", N_("##Get Help## using the <b>GNOME Desktop</b>")], ["gnome-control-center.desktop", N_("##Change desktop settings## with <b>GNOME Control Center</b>")], ["gnome-universal-access-panel.desktop", N_("##Enable Accessibility## with <b>Settings > Universal Access</b>")] ],
}

participate_link= {
	'header' : N_("Participate"),
	'icon' : "participate.png",
	'url_links' : [ ["https://community.oracle.com/community/server_%26_storage_systems/solaris", N_("##Join in on the discussion## of the <b>Oracle Solaris Forums</b>")], ["http://www.oracle.com/technetwork/server-storage/solaris11/community/index.html", N_("##Catch the latest## from the <b>Oracle Solaris Community</b>")] ],
}

ICON_PATH = "/usr/share/os-about/"
DESKTOP_ITEM_PATH = "/usr/share/applications/"

class DialogOSNextSteps(Gtk.Dialog):
	def __init__(self, parent=None):
		Gtk.Dialog.__init__(self, self.__class__.__name__, parent, 0, None)

		self.connect('destroy', lambda *w: Gtk.main_quit())

		Gtk.Window.set_default_icon_from_file ("/usr/share/os-about/about-os-window-icon.png")

		self.modify_bg(Gtk.StateType.NORMAL, Gdk.color_parse('white'))

		# Set the dialog default spacing for about
		self.set_title(_("Start here with Oracle Solaris 12"))
		self.set_border_width(5)
		self.set_resizable(False)
		self.vbox.set_border_width(2)
		self.action_area.set_border_width(5)

		vbox = Gtk.VBox(False, 8)
		vbox.set_border_width(5)
		self.vbox.pack_start(vbox, False, False, 0)

		# Logo
		logo = Gtk.Image()
		pixbuf = GdkPixbuf.Pixbuf.new_from_file (ICON_PATH + "about-os-logo.png")

#		scale = 48.0 / pixbuf.get_height()
#		width_scale = pixbuf.get_width() * scale
#		height_scale = pixbuf.get_height() * scale
#		pixbuf = pixbuf.scale_simple (int(width_scale), int(height_scale), GdkPixbuf.InterpType.BILINEAR)
		logo.set_from_pixbuf (pixbuf)
		logo_hbox = Gtk.HBox(True, 0)
		logo_hbox.pack_start(logo, False, False, 0)
		vbox.pack_start(logo_hbox, False, False, 0)

		close_button=self.add_button(Gtk.STOCK_CLOSE,Gtk.ResponseType.CANCEL)
		self.set_default_response (Gtk.ResponseType.CANCEL)
		close_button.grab_default()
		close_button.grab_focus()
		close_button.connect('clicked', lambda *w: Gtk.main_quit())

		self.create_section(help_link, vbox)
		self.create_section(personalize_link, vbox)
		self.create_section(participate_link, vbox)

		self.show_all()

	def create_section(self, section_link, vbox):
		section_hbox = Gtk.HBox(False, 10)
		vbox.pack_start(section_hbox, True, True, 10)

		header = Gtk.Image()
		header.set_from_file (ICON_PATH + section_link['icon'])
		section_hbox.pack_start(header, False, False, 2)

		header_vbox = Gtk.VBox(False, 0)
		section_hbox.pack_start(header_vbox, False, False, 0)

		label = Gtk.Label()
		label.set_alignment(0, 0)
		label.set_markup("<span><b>%s</b></span>" % _(section_link['header']))
		label.set_justify(Gtk.Justification.LEFT)
		header_vbox.pack_start(label, False, False, 2)

		detail_vbox = Gtk.VBox(False, 0)
		detail_vbox.set_spacing(2)
		header_vbox.pack_start(detail_vbox, False, False, 0)
		self.fill_section(section_link, detail_vbox)

	def launch_app(self,label,uri):
		try:
			ditem = Gio.DesktopAppInfo.new (uri)
			ditem.launch ([])
		except Exception, e:
			print '''Warning: could not execute file "%s" : %s''' % (uri, e)

		return True

	def fill_section (self, section_link, vbox):

		if 'program_links' in section_link:
			for i in section_link['program_links']:
				hbox = Gtk.HBox(False, 0)
				label = Gtk.Label()
				label.set_markup(bullet_point + " ")
				label.set_justify(Gtk.Justification.LEFT)
				hbox.pack_start(label, False, False, 0)

				tmp = _(i[1]).split('##')

				label = Gtk.Label()
				label.set_markup(tmp[0])
				hbox.pack_start(label, False, False, 0)

				link_button = Gtk.Label()
				link_button.connect("activate-link", self.launch_app)
                                markup = "<b><a href='%s'>%s</a></b>" % (i[0],tmp[1])
                                link_button.set_markup(markup)

				hbox.pack_start(link_button, False, False, 0)

				label = Gtk.Label()
				label.set_markup(tmp[2])
				hbox.pack_start(label, False, False, 0)

				vbox.pack_start(hbox, False, False, 0)

		if 'url_links' in section_link:
			for i in section_link['url_links']:
				hbox = Gtk.HBox(False, 0)
				label = Gtk.Label()
				label.set_markup(bullet_point + " ")
				label.set_justify(Gtk.Justification.LEFT)
				hbox.pack_start(label, False, False, 0)

				tmp = _(i[1]).split('##')

				label = Gtk.Label()
				label.set_markup(tmp[0])
				hbox.pack_start(label, False, False, 0)

				link_button = Gtk.Label()
				markup = "<b><a href='%s'>%s</a></b>" % (i[0],tmp[1])
				link_button.set_markup(markup)
				hbox.pack_start(link_button, False, False, 0)

				label = Gtk.Label()
				label.set_markup(tmp[2])
				hbox.pack_start(label, False, False, 0)

				vbox.pack_start(hbox, False, False, 0)


def main():
	locale.setlocale (locale.LC_ALL, "")
	gettext.textdomain (GETTEXT_PACKAGE)
	gettext.install (GETTEXT_PACKAGE, LOCALEDIR)

	style_provider = Gtk.CssProvider()
	css = """
	GtkDialog {
	  background-image: url('/usr/share/os-about/about-os-background.jpg');
	  background-position: left top;
	}
	"""
	style_provider.load_from_data(css)

	Gtk.StyleContext.add_provider_for_screen(
		Gdk.Screen.get_default(),
		style_provider,
		Gtk.STYLE_PROVIDER_PRIORITY_APPLICATION
	)

	DialogOSNextSteps()
	Gtk.main()

if __name__ == '__main__':
	main()
