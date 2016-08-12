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
import string
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

help_link= {
	'header' : N_("Get Help"),
	'icon' : "resources.png",
	'url_links' : [ ["http://docs.oracle.com/cd/E53394_01/pdf/E54847.pdf", N_("##What's new## with <b>Oracle Solaris 11.3</b>")], ["http://www.oracle.com/us/support/systems/index.html", N_("##Get world class support## with <b>Oracle Premier Support</b>")], ["https://localhost:6787/", N_("##Explore## the <b>Oracle Solaris Dashboard</b> with system analytics and more")] ],
}

personalize_link= {
	'header' : N_("Personalize"),
	'icon' : "personalize.png",
	'program_links' : [ ["gnome-appearance-properties.desktop", N_("##Change themes## with <b>System > Preferences > Appearance</b>")], ["at-properties.desktop", N_("##Enable Accessibility## with <b>System > Preferences > Assistive Technologies</b>")] ],
}

participate_link= {
	'header' : N_("Participate"),
	'icon' : "participate.png",
	'url_links' : [ ["https://community.oracle.com/community/server_%26_storage_systems/solaris", N_("##Join in on the discussion## of the <b>Oracle Solaris Forums</b>")], ["http://www.oracle.com/technetwork/server-storage/solaris11/community/index.html", N_("##Catch the latest## from the <b>Oracle Solaris Community</b>")] ],
}

ICON_PATH = "/usr/share/os-about/"
DESKTOP_ITEM_PATH = "/usr/share/applications/"

class WindowedLabel (Gtk.Label):
    '''Custom Gtk.Label with an overlapping input-only Gdk.Window'''

    event_window = None

    def __init__ (self, debug = False):
	'''Initialize object and plug all signals'''
	self.debug = debug
	super (WindowedLabel, self).__init__ ()

    def do_realize (self):
	'''Create a custom GDK window with which we will be able to play'''
	Gtk.Label.do_realize (self)
	event_mask = self.get_events () | Gdk.EventMask.BUTTON_PRESS_MASK \
					| Gdk.EventMask.BUTTON_RELEASE_MASK \
					| Gdk.EventMask.KEY_PRESS_MASK
	attr = Gdk.WindowAttr()
	attr.window_type = Gdk.WindowType.CHILD
	attr.wclass = Gdk.WindowWindowClass.INPUT_ONLY
	attr.event_mask = event_mask
	attr.x = self.get_allocation().x
	attr.y = self.get_allocation().y
	attr.width = self.get_allocation().width
	attr.height = self.get_allocation().height

	self.event_window = Gdk.Window (
	    parent = self.get_parent_window (),
	    attributes = attr,
	    attributes_mask = (Gdk.WindowAttributesType.X |
			       Gdk.WindowAttributesType.Y)
	    )
	self.event_window.set_user_data (self)

    def do_unrealize (self):
	'''Destroy event window on unrealize'''
	self.event_window.set_user_data (None)
	self.event_window.destroy ()
	Gtk.Label.do_unrealize (self)

    def do_size_allocate (self, allocation):
	'''Move & resize the event window to fit the Label's one'''
	Gtk.Label.do_size_allocate (self, allocation)
	if self.get_realized():
	    self.event_window.move_resize (allocation.x, allocation.y,
					   allocation.width, allocation.height)

    def do_map (self):
	'''Show event window'''
	Gtk.Label.do_map (self)
	self.event_window.show ()
	'''Raise the event window to make sure it is over the Label's one'''
	self.event_window.raise_ ()

    def do_unmap (self):
	'''Hide event window on unmap'''
	self.event_window.hide ()
	Gtk.Label.do_unmap (self)

GObject.type_register (WindowedLabel)

class HyperLink (WindowedLabel):
    '''Clickable www link label'''

    url		= ""
    is_app_link = False
    menu	= None
    selection	= None

    def __init__ (self, label, url, app_link):
	'''Initialize object'''
	super (HyperLink, self).__init__ ()
	markup = "<b><u>%s</u></b>" % label
	self.set_markup (markup)
	self.set_selectable (True)
	self.url = url
	self.is_app_link = app_link
	self.create_menu ()
	link_color = self.style_get_property ("link-color")
	if not link_color:
	    link_color = default_link_color
	self.modify_fg (Gtk.StateType.NORMAL, link_color)

    def open_url (self, *args):
	'''Use GNOME API to open the url'''
	try:
	    Gtk.show_uri (None, self.url, Gtk.get_current_event_time())
	except Exception, e:
	    print '''Warning: could not open "%s": %s''' % (self.url, e)

    def open_link (self, *args):
	try:
	    ditem = Gio.DesktopAppInfo.new (self.url)
	    ditem.launch ([])
	except Exception, e:
	    print '''Warning: could not execute file "%s" : %s''' % (self.url, e)

    def copy_url (self, *args):
	'''Copy URL to Clipboard'''
	clipboard = Gtk.clipboard_get ("CLIPBOARD")
	clipboard.set_text (self.url)

    def create_menu (self):
	'''Create the popup menu that will be displayed upon right click'''
	self.menu = Gtk.Menu ()
	if self.is_app_link:
		open_item = Gtk.MenuItem (_("_Open Link"), use_underline = True)
		open_item.connect ("activate", self.open_link)
	else:
		open_item = Gtk.MenuItem (_("_Open URL"), use_underline = True)
		open_item.connect ("activate", self.open_url)

	open_item.show ()
	self.menu.append (open_item)
	copy_item = Gtk.MenuItem (_("_Copy URL"), use_underline = True)
	copy_item.connect ("activate", self.copy_url)
	copy_item.show ()
	self.menu.append (copy_item)

    def display_menu (self, button, time, place = False):
	'''Display utility popup menu'''
	if place:
	    alloc = self.get_allocation ()
	    pos = self.event_window.get_origin ()
	    x = pos[0]
	    y = pos[1] + alloc.height
	    func = lambda *a: (x, y, True)
	else:
	    func = None
	self.menu.popup (None, None, func, None, button, time)

    def do_map (self):
	'''Select the HAND2 cursor on map'''
	WindowedLabel.do_map (self)
	cursor = Gdk.Cursor.new(Gdk.CursorType.HAND2)
	self.event_window.set_cursor (cursor)

    def do_button_press_event (self, event):
	'''Update selection bounds infos or display popup menu'''
	if event.button == 1:
	    self.selection = self.get_selection_bounds ()
	elif event.button == 3:
	    self.display_menu (event.button, event.time)
	    return True
	WindowedLabel.do_button_press_event (self, event)

    def do_button_release_event (self, event):
	'''Open url if selection hasn't changed since initial press'''
	if event.button == 1:
	    selection = self.get_selection_bounds ()
	    if selection == self.selection:
		if self.is_app_link:
			self.open_link ()
		else:
			self.open_url ()
		return True
	WindowedLabel.do_button_release_event (self, event)

    def do_key_press_event (self, event):
	'''Open url when Return key is pressed'''
	if event.keyval == Gdk.KEY_Return:
	    if self.is_app_link:
		self.open_link ()
	    else:
		self.open_url ()
	    return True
	elif event.keyval == Gdk.KEY_Menu \
	  or (event.keyval == Gdk.KEY_F10 \
	      and event.get_state() & Gtk.accelerator_get_default_mod_mask() == \
		  Gdk.ModifierType.SHIFT_MASK):
	    self.display_menu (event.keyval, event.time, place = True)
	    return True
	WindowedLabel.do_key_press_event (self, event)

GObject.type_register (HyperLink)
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

				link_button = HyperLink (tmp[1],i[0], True)
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

				link_button = HyperLink (tmp[1], i[0], False)
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
