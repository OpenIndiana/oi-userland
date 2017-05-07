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
Used for info column
"""
import gtk
import gobject

class CellRendererUrl(gtk.CellRendererText):
    """
    This class used for creating a subclass from gtk.CellRendererText.
    It will be put into a treemodel column and then enabled or disabled
    if the context is useful
    """
    __gproperties__ = { "information": (gobject.TYPE_PYOBJECT,
                                      "information property",
                                      "information property",
                                      gobject.PARAM_READWRITE) }
    def __init__(self):
        self.__gobject_init__()
        gtk.CellRendererText.__init__(self)
        self.set_property("xalign", 0.5)
        self.set_property("mode", gtk.CELL_RENDERER_MODE_ACTIVATABLE)
        self.information = None
        self.table = None

    def do_set_property(self, pspec, value):
        """
        set property
        """
        if pspec.name == "information":
            if callable(value):
                self.information = value
            else:
                raise TypeError("information property must be callable!")
        else:
            raise AttributeError("Unknown property %s" % pspec.name)

    def do_get_property(self, pspec):
        """
        get property
        """
        if pspec.name == "information":
            return self.information
        else:
            raise AttributeError("Unknown property %s" % pspec.name)

    def do_get_size(self, wid, cell_area):
        """
        set object size, for the easist way i set it to 0, then the "info"
        column will be looked as nothing if the controller has a working
        driver attached. Only no-driver/driver working abnormally controller
        will used this object to display a "info" string.
        """
        del wid, cell_area
        return (0, 0, 0, 0)

    def do_render(self, window, wid, bg_area, cell_area, expose_area, flags):
        """
        render this object
        """
        if not window:
            return

        ypad = self.get_property("ypad")

        wid.get_style().paint_box(window, 0, 0, cell_area, wid, "label", 
				  0, 0, 0, 0)
        flags = flags & ~gtk.STATE_SELECTED
        gtk.CellRendererText.do_render(self, window, wid, bg_area, 
                                      (cell_area[0], cell_area[1] + ypad, 
                                      cell_area[2],cell_area[3]), 
                                      expose_area, flags)

    def do_activate(self, event, wid, path, bg_area, cell_area, flags):
        """
        activate widget
        """
        del event, wid, bg_area, cell_area, flags
        cb = self.get_property("information")
        if cb != None :
            cb(path)
        return True

