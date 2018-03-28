#! /usr/bin/python2.7
#

#
#
# Copyright (c) 2008, 2010, Oracle and/or its affiliates. All rights reserved.
#
"""
This is the main file for DDU GUI part
"""

import sys
import os
from xml.dom import minidom
from xml.dom import Node
import commands

try:
    import pygtk
    pygtk.require("2.0")
except ImportError:
    print "Please install pyGTK or GTKv2 or set your PYTHONPATH correctly"
    sys.exit(1)

import gtk
import gtk.glade
import gobject
import pango
import threading
import gettext
import pynotify
import webbrowser
import subprocess
from DDU.ddu_errors import DDUException
from DDU.ddu_function import ddu_devscan
from DDU.ddu_function import ddu_package_lookup
from DDU.ddu_function import ddu_install_package
from DDU.ddu_package import ddu_package_object
from ConfigParser import ConfigParser

DDUCONFIG = ConfigParser()

DDUCONFIG.read(os.path.join(os.path.dirname( 
            os.path.realpath(sys.argv[0])),"ddu.conf"))
ABSPATH = DDUCONFIG.get('general','abspath')
VENDOR_EMAIL = DDUCONFIG.get('vendor','email')

try:
    gettext.bindtextdomain('ddu','%s/i18n' % ABSPATH)
    gettext.textdomain('ddu')
    gtk.glade.bindtextdomain('ddu','%s/i18n' % ABSPATH)
except AttributeError:
    pass

os.putenv('LD_LIBRARY_PATH', '/usr/ddu/lib')
from utils import DetailInf
from utils import SubmitDlg
from utils import InstDrv
from utils import MessageBox
from utils import CellRendererUrl
from utils import BrowseDlg
from utils import RepoDlg

gobject.type_register(CellRendererUrl)


gtk.glade.textdomain('ddu')
_ = gettext.gettext

COND = threading.Condition()

class _IdleObject(gobject.GObject):
    """
    prototype of a thread class witch emit event to main thread
    """
    def __init__(self):
        gobject.GObject.__init__(self)

    def emit(self, *args):
        """
        emit event to main thread, because of pygtk issue, all GTK even should
        be handled in main thread, so this class  and  its subclass will
        redirect the GTK request to main thread.
        the arguments includes GTK action and the arguments for this action.
        GTK actions include:
        clear: clear device tree
        append: append a item to device tree
        remove: remove a item from device tree
        update: update a item property from device tree
        insert_after: insert a a item after another item to device tree
        get_path:get a item path from the device tree 
        """
        gobject.idle_add(gobject.GObject.emit, self, *args)
	
class DeviceTree(threading.Thread, _IdleObject):
    """
    Main class for building device tree
    """
    #register new GObject signals:
    #clear:clear device tree
    #append:append a item to device tree. it's used for the first controller
    #       in each hardware categoey.
    #       arguments include: category name, controller ID,
    #                          controller icon name, controller description,
    #                          controller driver name/package type,
    #                          information tag, whole line state,
    #                          info tag state.
    #       information tag: If contrller has a driver working normally,
    #                        then this field will display nothing, otherwise it
    #                        will display "info"
    #       whole line state: If controller has not a driver or the driver
    #                         working abnormally, then the whole line in device
    #                         tree will be displayed in pink.
    #       info tag state:If controler has not a driver but a useful driver
    #                      has been found on repo or from driver DB, then the
    #                      "info" text in information tag field will be
    #                      enabled.
    #remove:remove a item from device tree
    #update: update a item property from device tree
    #insert_after: insert a a item after another item in device tree, which is
    #              similar to append action, only the arguments should provide
    #              parent item which it will attached to
    #get_path: after a item has been added to device tree, this action will get
    #          its path in device tree.
    
    __gsignals__ =  {
        "clear":(gobject.SIGNAL_RUN_LAST, gobject.TYPE_NONE, []),
        "append":(gobject.SIGNAL_RUN_LAST, gobject.TYPE_NONE, 
                 [gobject.TYPE_STRING,gobject.TYPE_STRING, 
                 gobject.TYPE_STRING,gobject.TYPE_STRING,gobject.TYPE_STRING, 
                 gobject.TYPE_STRING,gobject.TYPE_BOOLEAN, 
                 gobject.TYPE_BOOLEAN]),
        "remove":(gobject.SIGNAL_RUN_LAST, gobject.TYPE_NONE,[]),
        "update":(gobject.SIGNAL_RUN_LAST, gobject.TYPE_NONE, 
                 [gobject.TYPE_PYOBJECT,gobject.TYPE_INT,gobject.TYPE_STRING]),
        "insert_after":(gobject.SIGNAL_RUN_LAST,gobject.TYPE_NONE, 
                 [gobject.TYPE_PYOBJECT,gobject.TYPE_STRING, 
                 gobject.TYPE_STRING,gobject.TYPE_STRING,gobject.TYPE_STRING, 
                 gobject.TYPE_STRING,gobject.TYPE_STRING,gobject.TYPE_STRING, 
                 gobject.TYPE_BOOLEAN,gobject.TYPE_BOOLEAN]),
        "get_path":(gobject.SIGNAL_RUN_LAST, gobject.TYPE_NONE, 
                 [gobject.TYPE_PYOBJECT])
    }
    myiter = None
    tempiter = None
    parentiter = None
    dev_package = {}
    def __init__(self, cond):
        threading.Thread.__init__(self)
        _IdleObject.__init__(self)
        self.finish = False
        self.cond = cond
        self.dev_tree = {}
        self.certdata = None
        self.dev_submit = {}
        self.dev_package = {}
        status, self.default_repo = commands.getstatusoutput(
            '%s/scripts/pkg_relate.sh list default | cut -f 1' % ABSPATH)
        if status != 0:
            sys.exit(1)

    def run(self):
        """
        Build device tree and try to install driver if missing driver found on
        main repo
        """
        status, output = commands.getstatusoutput( 
            '%s/scripts/probe.sh init' % ABSPATH)
        if status != 0:
            print output
            sys.exit(1)
       #step1:build device tree
        self.dev_tree, self.certdata, self.dev_submit = \
            self.insert_row()
        if len(self.dev_package) > 0:
            #step2:if no-driver controller has been found on step1,
            #then look for their driver and then re-build device tree
            self.mani_package()
            self.dev_tree = {}
            self.dev_tree, self.certdata, self.dev_submit = \
                self.insert_row()
        self.finish = True
			
    def mani_package(self):
        """
        Try to look up missing drivers and install them if possible.
        """
        for dev_id in self.dev_package:
            try:
                package_candi = ddu_package_lookup(self.dev_package[dev_id][0], [])
            except DDUException:
                continue
            self.dev_package[dev_id].append(package_candi)
            if package_candi.pkg_type == 'PKG':
                driver_repo = package_candi.pkg_location
                if self.default_repo == driver_repo:
                    self.cond.acquire()
                    #update component property in device tree, field 5 is
                    #driver state field, for that no-driver component,
                    #this column will display "searching" and then ddu look for
                    #its driver. If the driver was found on main repo,
                    #then this driver will be installed automatically and this
                    #driver state field will be changed to "installing"
                    self.emit( 
                             "update",
                              self.dev_tree[dev_id][0],
                              5,
                              "installing")
                    self.cond.notify()
                    self.cond.release()
                    try:
                        ddu_install_package(package_candi,"/")
                    except DDUException:
                        pass


    def insert_row(self):
        """This function handle the TreeStore in the Treeview of the main
           window. 
           The files for probe output:
           For Controller:
           F0:ID;F1:Parent ID;F2:Controller Name;F3:DeviceID;F4:ClassCode;
           F5:DevPath;F6:Drvier;F7:Instance;F8:Attach status;F9:VendorID
           For Device:
           F0:ID;F1:Parent ID;F2:Device Name;F3:Binding name;F4:DevPath;
           F5:Driver;F6:Instance;F7:Attach status
	"""
        self.cond.acquire()
        dev_submit = {}
		
        self.emit("clear")
        self.cond.notify()
        self.cond.wait()

        systemxml = minidom.parse('%s/data/hdd.xml' % ABSPATH)

        category = systemxml.getElementsByTagName('category')
        #abnormal_path used to store fist no-driver or driver worked abnormally
        #component item in device tree, when the whole device tree has been
        #created, then on GUI the scrollbar will roll to this item.
        abnormal_path = ''
        
        for catelist in category:
            catename = catelist.attributes["name"].value
            self.emit("append", catename, 'category', 
                      None, '', '', '', False, False)
            self.cond.notify()
            self.cond.wait()

            first_iter = True
            dev_submit[catename] = []

            probehook = catelist.getElementsByTagName('probe')[0]
		
            for probedata in probehook.childNodes:
                #Get The probe script for each category
                if probedata.nodeType == Node.TEXT_NODE:
                    probedata.data = probedata.data.split(' ')[1]
                    probe_list = ddu_devscan(False, probedata.data)
                    if len(probe_list) > 0:
                    #if components exists under certain category, then they will
                    #be attached under this category on GUI,
                    #otherwise this catogory will be deleted from GUI
                        for line in probe_list:
                        #get each component under certain category
                        #and display it on GUI
                            if line.parent_item_id == '':
                            #for each component it could be a device or
                            #controller, now I handle controller type,
                            #later will handle device type.
                                if line.driver_name == '' :
                                #handles controller which missing driver
                                    if self.dev_package.has_key(
                                                        str(line.item_id)):
                                    #dev_package store controllers which have
                                    #missing driver and later will try to look
                                    #for driver for them,
                                    #if the controller's driver is found on
                                    #main repo, then that driver will be
                                    #installed by DDU automatically. If the
                                    #controller's driver is not on main repo
                                    #or is not a PKG format, then only package
                                    #information will be stored in dev_package.
                                    #possible package type would be:
                                    #PKG, SVR4 and UNK

                                        #if for some reaseon the package lookup
                                        #does not return properly we are left 
                                        #with missing data, hack around for now
                                        if (len(self.dev_package[str(line.item_id)]) == 1):
                                            device_compatible = \
                                                self.dev_package[str(line.item_id)][0].get_compatible_name_string()
                                            device_descriptor = \
                                                self.dev_package[str(line.item_id)][0].get_description()
                                            self.dev_package[str(line.item_id)].append( \
                                                ddu_package_object(pkg_type = "UNK",
                                                                   pkg_name = "",
                                                                   pkg_location = "",
                                                                   inf_link = "",
                                                                   compatible_name = device_compatible,
                                                                   flags_64bit = "",
                                                                   device_descriptor = device_descriptor,
                                                                   third_party_from_search = False))
                                        
                                        if first_iter == True:
                                        #first controller under certain
                                        #category will be displayed together
                                        #with a icon for this category, so this
                                        #category's icon will be removed
                                        #firstly and then displayed with the
                                        #first controller's information
                                            self.emit("remove")
                                            self.cond.notify()
                                            self.cond.wait()
                                            catename = \
                                            catelist.attributes["name"].value

                                            if self.dev_package[\
                                            str(line.item_id)][1].pkg_type == \
                                            'PKG':
                                                self.emit(
                                                    "append",
                                                    catename,
                                                    str(line.item_id),
                                                    None,
                                                    line.description,
                                                    'IPS',
                                                    _('Info'),
                                                    True,
                                                    True)
                                            elif self.dev_package[\
                                            str(line.item_id)][1].pkg_type == \
                                            'SVR4':
                                                self.emit(
                                                    "append",
                                                    catename,str(line.item_id),
                                                    None,
                                                    line.description,
                                                    'SVR4',
                                                    _('Info'),
                                                    True,
                                                    True)
                                            elif self.dev_package[\
                                            str(line.item_id)][1].pkg_type == \
                                            'UNK' and self.dev_package[ \
                                            str(line.item_id)][1].pkg_name != \
                                            "" and self.dev_package[ \
                                            str(line.item_id)] \
                                            [1].pkg_location != "":
                                                self.emit(
                                                    "append",
                                                    catename,
                                                    str(line.item_id),
                                                    None,
                                                    line.description,
                                                    'UNK',
                                                    _('Info'),
                                                    True,
                                                    True)
                                            else:
                                                self.emit(
                                                    "append",
                                                    catename,
                                                    str(line.item_id),
                                                    None,
                                                    line.description,
                                                    'UNK',
                                                    _('Info'),
                                                    True,
                                                    False)

                                            self.cond.notify()
                                            self.cond.wait()
                                            self.dev_tree[ \
                                                str(line.item_id)] = \
                                                [self.myiter,line, \
                                                'c', self.dev_package[str(line.item_id)][1]]
                                        else:
                                        #not the first contrller, which on GUI
                                        #will be displayed after category item
                                            if self.dev_package[ \
                                            str(line.item_id)][1].pkg_type == \
                                            'PKG':
                                                self.emit(
                                                     "insert_after",
                                                     self.myiter,None,'',
                                                     str(line.item_id),
                                                     None,
                                                     line.description,
                                                     'IPS',
                                                     _('Info'),
                                                     True,
                                                     True)
                                            elif self.dev_package[ \
                                            str(line.item_id)][1].pkg_type == \
                                            'SVR4':
                                                self.emit(
                                                     "insert_after",
                                                     self.myiter,
                                                     None,
                                                     '',
                                                     str(line.item_id),
                                                     None,
                                                     line.description,
                                                     'SVR4',
                                                     _('Info'),
                                                     True,
                                                     True)
                                            elif self.dev_package[ \
                                            str(line.item_id)][1].pkg_type == \
                                            'UNK' and \
                                            self.dev_package[ \
                                            str(line.item_id)] \
                                            [1].pkg_name !="" and \
                                            self.dev_package[ \
                                            str(line.item_id)] \
                                            [1].pkg_location != "":
                                                self.emit(
                                                     "insert_after",
                                                     self.myiter,
                                                     None,
                                                     '',
                                                     str(line.item_id),
                                                     None,
                                                     line.description,
                                                     'UNK',
                                                     _('Info'),
                                                     True,
                                                     True)
                                            else:
                                                self.emit(
                                                     "insert_after",
                                                     self.myiter,
                                                     None,
                                                     '',
                                                     str(line.item_id),
                                                     None,
                                                     line.description,
                                                     'UNK',
                                                     _('Info'),
                                                     True,
                                                     False)
                                            self.cond.notify()
                                            self.cond.wait()
                                            self.dev_tree[ \
                                            str(line.item_id)]=[ \
                                            self.tempiter,line,'c', \
                                            self.dev_package[str(line.item_id)][1]]
                                    else:
                                    #if a controller has not a driver attached
                                    #then firstly store it in the dev_package,
                                    #and the driver filed on GUI will display
                                    #"searching" 
                                    #later each controller in dev_package will
                                    #be handled: looking for driver information
                                    #and maybe installed.
                                        self.dev_package[str(line.item_id)] = \
                                        [line]
                                        if first_iter == True:
                                            self.emit("remove")
                                            self.cond.notify()
                                            self.cond.wait()
                                            catename = catelist.attributes[ \
                                                       "name"].value
                                            self.emit(
                                                 "append",
                                                 catename,
                                                 str(line.item_id),
                                                 None,
                                                 line.description,
                                                 'searching',
                                                 '',
                                                 True,
                                                 True)
                                            self.cond.notify()
                                            self.cond.wait()
                                            self.dev_tree[ \
                                                 str(line.item_id)] = [ \
                                                 self.myiter,line,'c']
                                        else:
                                            self.emit(
                                                 "insert_after",
                                                 self.myiter,
                                                 None,
                                                 '',
                                                 str(line.item_id),
                                                 None,
                                                 line.description,
                                                 'searching',
                                                 '',
                                                 True,
                                                 True)
                                            self.cond.notify()
                                            self.cond.wait()
                                            self.dev_tree[ \
                                                 str(line.item_id)] = [ \
                                                 self.tempiter,line,'c']

                                    if abnormal_path == '':
                                        if first_iter == True:
                                            self.emit("get_path", self.myiter)
                                            self.cond.notify()
                                            self.cond.wait()
                                            abnormal_path = self.myiter
                                            first_iter = False
                                        else:
                                            self.emit("get_path",
                                                      self.tempiter)
                                            self.cond.notify()
                                            self.cond.wait()
                                            abnormal_path = self.tempiter
                                    else:
                                        if first_iter == True:
                                            first_iter = False

                                elif int(line.instance_id) < 0 and \
                                line.attach_status == 'Detached':
                                #handle controller which has a driver attached
                                #but misconfigured.
                                    if first_iter == True:
                                        self.emit("remove")
                                        self.cond.notify()
                                        self.cond.wait()

                                        catename = \
                                        catelist.attributes["name"].value
                                        self.emit(
                                            "append",
                                            catename,
                                            str(line.item_id),
                                            None,
                                            line.description,
                                            str("Misconfigured:[" + 
                                                line.driver_name + "]"),
                                            _('Info'),
                                            True,
                                            False)
                                        self.cond.notify()
                                        self.cond.wait()
                                        self.dev_tree[str(
                                                      line.item_id)] = [
                                                      self.myiter,line,'c']

                                    else:
                                        self.emit( 
                                             "insert_after",
                                             self.myiter,
                                             None,
                                             '',
                                             str(line.item_id),
                                             None,
                                             line.description,
                                             str("Misconfigured:[" + 
                                                 line.driver_name+"]"),
                                             _('Info'),
                                             True,
                                             False)
                                        self.cond.notify()
                                        self.cond.wait()
                                        self.dev_tree[str(line.item_id)] = \
                                        [self.tempiter,line,'c']

                                    if abnormal_path == '':
                                        if first_iter == True:
                                            self.emit("get_path", self.myiter)
                                            self.cond.notify()
                                            self.cond.wait()
                                            abnormal_path = self.myiter
                                            first_iter = False
                                        else:
                                            self.emit( 
                                            "get_path", self.tempiter)
                                            self.cond.notify()
                                            self.cond.wait()
                                            abnormal_path = self.tempiter
                                    else:
                                        if first_iter == True:
                                            first_iter = False
                                else:
                                #handle controller which has a driver attached
                                #and working normally.
                                    if first_iter == True:
                                        self.emit("remove")
                                        self.cond.notify()
                                        self.cond.wait()
                                        catename = \
                                        catelist.attributes["name"].value
                                        self.emit(
                                             "append",
                                             catename,
                                             str(line.item_id),
                                             None,
                                             line.description,
                                             line.driver_name,
                                             '',
                                             False,
                                             False)
                                        self.cond.notify()
                                        self.cond.wait()
                                        self.dev_tree[str(line.item_id)] = \
                                        [self.myiter,line,'c']
                                        first_iter = False
                                    else:
                                        self.emit( 
                                             "insert_after",
                                             self.myiter,
                                             None,
                                             '',
                                             str(line.item_id),
                                             None,
                                             line.description,
                                             line.driver_name,
                                             '',
                                             False,
                                             False)
                                        self.cond.notify()
                                        self.cond.wait()
                                        self.dev_tree[str(line.item_id)] = \
                                        [self.tempiter,line,'c']
                                dev_submit[catename].append((line.pci_path, 
                                           line.class_code,line.description))
                            else:
                            #handle device type here, not for contrller type
                                self.parentiter = self.dev_tree[str(
                                                       line.parent_item_id)][0]
                                self.emit(
                                     "insert_after",
                                     self.parentiter,
                                     None,
                                     '',
                                     str(line.item_id),
                                     None,
                                     line.description,
                                     line.driver_name,
                                     '',
                                     False,
                                     False)
                                self.cond.notify()
                                self.cond.wait()
                                self.dev_tree[str(line.item_id)] = \
                                [self.tempiter,line,'d']
                                dev_submit[catename].append((line.pci_path, 
                                "",line.description))
                    else:
                        self.emit("remove")
                        self.cond.notify()
                        self.cond.wait()

        self.cond.notify()
        self.cond.release()
        """Get The driver handling script"""
        certhook = systemxml.getElementsByTagName('trydrv')[0]

        certaction = None
        for certdata in certhook.childNodes:
            if certdata.nodeType == Node.TEXT_NODE:
                certaction = certdata
        return self.dev_tree, certaction.data, dev_submit
  

class HDDgui:
    """
    HDDgui is the main GUI window.
    main Variables:
    __dev_tree representens the tree information for treeview
    __disp_data represents the selected node in treeview
    __certdata try driver action
    """	
    __dev_tree = {}
    __disp_data = ''
    __certdata = ''
    __rescan = False
    __success = False
    detail_inf_run = None
    myiter = None
    tempiter = None
    abnormal_path = ''
    repo_listdic = {}
	
    def __init__(self):
        xmlpath = ABSPATH + "/data/hdd.glade"
        xml = gtk.glade.XML(xmlpath, root = 'topbox_main', domain='ddu')
        self.window = xml.get_widget('topbox_main')
        self.window.connect("destroy", self.main_destroy)
        self.window.set_default_size(630, 700)
        self.window.set_resizable(True)

        #devtree_view is the area for displaying the device tree
        self.devtreeview = xml.get_widget('devtree_view')
        self.devtreemodel = gtk.ListStore( 
        gtk.gdk.Pixbuf, gobject.TYPE_STRING, 
        gobject.TYPE_STRING, gtk.gdk.Pixbuf, gobject.TYPE_STRING, 
        gobject.TYPE_STRING, gobject.TYPE_STRING, gobject.TYPE_PYOBJECT, 
        'gboolean', 'gboolean')

        self.devtreeview.set_model(self.devtreemodel)
        self.devtreeview.set_headers_visible(True)

        menuxml = gtk.glade.XML(xmlpath, 'detail_menu')
        self.popup_menu = menuxml.get_widget('detail_menu')
        self.detail_information = menuxml.get_widget('detail_information')
        self.install_driver = menuxml.get_widget('install_driver')
        self.power_management = menuxml.get_widget('power_management')

        self.detail_information.connect('activate', self.on_detail_activate)

        self.devtreeview.connect('button-press-event', self.on_popup_menu)
	
        col0 = gtk.TreeViewColumn()
        col0.set_title(_('Types'))
        col0.set_property("alignment", 0.5)
        render_pixbuf0 = gtk.CellRendererPixbuf()
        render_pixbuf0.set_property('cell-background', 'pink')
        col0.pack_start(render_pixbuf0, expand = False)
        col0.add_attribute(render_pixbuf0, 'pixbuf', 0)
        col0.add_attribute(render_pixbuf0, 'cell_background_set', 8)


        render_text0 = gtk.CellRendererText()
        render_text0.set_property('cell-background', 'pink')
        col0.pack_start(render_text0, expand=True)
        col0.add_attribute(render_text0, 'text', 1)
        col0.add_attribute(render_text0, 'cell_background_set', 8)

        render_key1 = gtk.CellRendererText()
        render_key1.set_property('visible', False)
        col0.pack_start(render_key1, expand = True)
        col0.add_attribute(render_key1, 'text', 2)

        col0.set_resizable(True)

        col1 = gtk.TreeViewColumn()
        col1.set_title(_('Device'))
        col1.set_property("alignment", 0.5)
        render_pixbuf0 = gtk.CellRendererPixbuf()
        render_pixbuf0.set_property('cell-background', 'pink')
        col1.pack_start(render_pixbuf0, expand=False)

        col1.add_attribute(render_pixbuf0, 'pixbuf', 3)
        col1.add_attribute(render_pixbuf0, 'cell_background_set', 8)

        render_text1 = gtk.CellRendererText()
        render_text1.set_property('cell-background', 'pink')
        col1.pack_start(render_text1, expand=True)
        render_text1.set_property('xalign', 0)
        col1.add_attribute(render_text1, 'text', 4)
        col1.add_attribute(render_text1, 'cell_background_set', 8)

        col1.set_sizing(gtk.TREE_VIEW_COLUMN_FIXED)
        col1.set_expand(True)
        col1.set_resizable(True)

        col2 = gtk.TreeViewColumn()
        col2.set_title(_('Driver'))
        col2.set_property("alignment", 0.5)

        render_type = gtk.CellRendererText()
        render_type.set_property('cell-background', 'pink')
        render_type.set_property('xalign', 0.5)

        render_text0 = gtk.CellRendererText()
        render_text0.set_property('cell-background', 'pink')
        render_text0.set_property('xalign', 0.5)
        render_text0.set_property('underline', pango.UNDERLINE_SINGLE)
        render_text0.set_property('foreground-gdk', gtk.gdk.Color('blue'))

        render_label = CellRendererUrl()
        render_label.set_property('cell-background', 'pink')

        col2.pack_start(render_type, expand=True)
        col2.pack_start(render_text0, expand=True)
        col2.pack_start(render_label, expand=True)
        col2.add_attribute(render_type, 'text', 5)
        col2.add_attribute(render_type, 'cell_background_set', 8)
        col2.add_attribute(render_text0, 'text', 6)
        col2.add_attribute(render_text0, 'cell_background_set', 8)
        col2.add_attribute(render_label, 'information', 7)
        col2.add_attribute(render_label, 'cell_background_set', 8)
        col2.add_attribute(render_text0, 'foreground_set', 9)

        col2.set_resizable(True)


        self.devtreeview.append_column(col0)
        self.devtreeview.append_column(col1)
        self.devtreeview.append_column(col2)

        self.devtreeview.expand_all()

        self.scrolledwindow_dev = xml.get_widget('scrolledwindow_dev')
	
        self.devtreeview.show()
        self.scrolledwindow_dev.show()

        selection = self.devtreeview.get_selection()
        selection.set_mode(gtk.SELECTION_SINGLE)
        selection.connect('changed', self.on_selection_changed)

        #rescan_clicked handle the rescan action
        self.rescan_button = xml.get_widget('button_rescan')
        self.rescan_button.connect("clicked", self.rescan_clicked)


        close_button = xml.get_widget('button_close')
        close_button.connect("clicked", self.main_destroy)

        #drv_clicked handle the drv installation action
        self.drv_button = xml.get_widget('button_drv_detect')
        self.drv_button.connect("clicked", self.drv_clicked)
        self.drv_button.set_sensitive(True)

        self.help_button = xml.get_widget('help_button')
        self.help_button.connect("clicked", self.help_clicked)

        self.submit_button = xml.get_widget('button_submit')
        self.submit_button.connect("clicked", self.submit_clicked)
        self.submit_button.set_sensitive(False)

        self.button_browser = xml.get_widget('button_browser')
        self.button_browser.connect("clicked", self.browser_cliked)

        ag = gtk.AccelGroup()
        self.window.add_accel_group(ag)

        self.rescan_button.add_accelerator("clicked", ag, ord('r'), 
        gtk.gdk.MOD1_MASK,gtk.ACCEL_VISIBLE)
        close_button.add_accelerator("clicked", ag, ord('c'), 
        gtk.gdk.MOD1_MASK,gtk.ACCEL_VISIBLE)
        self.drv_button.add_accelerator("clicked", ag, ord('i'), 
        gtk.gdk.MOD1_MASK,gtk.ACCEL_VISIBLE)
        self.submit_button.add_accelerator("clicked", ag, ord('s'), 
        gtk.gdk.MOD1_MASK,gtk.ACCEL_VISIBLE)
        self.button_browser.add_accelerator("clicked", ag, ord('b'), 
        gtk.gdk.MOD1_MASK,gtk.ACCEL_VISIBLE)
	
        self.dev_view = xml.get_widget("dev_view")
        self.hbox_msg = xml.get_widget("hbox_msg")

        self.dev_viewport = xml.get_widget("dev_viewport")
        self.devstatview = xml.get_widget("dev_stat")
        self.devstatview.set_size_request(30, 0)
        self.devstatview.connect('expose-event', self.drawstat)
        self.dev_text = xml.get_widget("dev_text")

        self.statusbar = xml.get_widget("statusbar1")
        context_id = self.statusbar.get_context_id("feedback alias")
        self.statusbar.push(context_id, _("Feedback alias: " + VENDOR_EMAIL))

        xml.get_widget('label10').set_alignment(0, 0)
        xml.get_widget('label18').set_alignment(0, 0)

        self.server_com = xml.get_widget('combobox_ips')
        self.server_com.set_active(0)
        self.repo_listdic[self.server_com.get_active_text()]=0
        self.lenth = 0
        self.lookup_repo()
        self.server_com.connect('changed', self.changed_cb)

        self.entry_ips_info = xml.get_widget('entry1')
        self.entry_file_info = xml.get_widget('entry2')

        self.entry_ips_info.connect("changed", self.ipsenter_callback)
        self.entry_file_info.connect("changed", self.fileeenter_callback)

        self.radio_ips_info = xml.get_widget('radiobutton1')
        self.radio_file_info = xml.get_widget('radiobutton2')

        def size_allocate_cb(wid, allocation):
            """handle window size"""
            pass

        self.dev_submit = {}
        self.location = None
        self.wid_get = None
        self.dev_pbar = None
        self.event_c = None
        self.rescan_thread = None
        self.align = None
        self.window.connect('size-allocate', size_allocate_cb)
        self.rescan_button.emit("clicked")

        self.window.show_all()

    def ipsenter_callback(self, widget):
        """change radio_ips_info when user input"""
        del widget
        self.radio_ips_info.emit("clicked")

    def fileeenter_callback(self, widget):
        """change radio_file_info when user input"""
        del widget
        self.radio_file_info.emit("clicked")

    def model_clear(self, thread):
        """delete device tree"""
        del thread
        COND.acquire()
        self.devtreemodel.clear()
        COND.notify()
        COND.release()

    def model_append(self, thread, catename, category, data1, data2, data3, 
                     data4, condition_back,condition_for):
        """append a item to device tree"""
        COND.acquire()
        iconfile0 = gtk.gdk.pixbuf_new_from_file('%s/data/%s.png' % 
                                                 (ABSPATH,catename))
        self.myiter = self.devtreemodel.append([iconfile0, _(catename),
                                               category, data1, data2, data3,
                                               data4, self.callback,
                                               condition_back,condition_for])

        thread.myiter = self.devtreemodel.get_path(self.myiter)
        COND.notify()
        COND.release()

    def model_remove(self, thread):
        """remove a item from device tree"""
        del thread
        COND.acquire()
        self.devtreemodel.remove(self.devtreemodel.get_iter( 
        self.rescan_thread.myiter))
        COND.notify()
        COND.release()

    def model_update(self, thread, update_iter, position, data1):
        """update a item property in device tree"""
        del thread
        COND.acquire()
        candi_iter = self.devtreemodel.get_iter(update_iter)
        self.devtreemodel.set_value(candi_iter, position, data1)
        COND.notify()
        COND.release()


    def model_insert_after(self, thread, insert_iter, data1, data2, data3, 
               data4, data5, data6, data7, condition_back, condition_for):
        """insert a item to device tree after another item"""
        COND.acquire()
        insert_iter = self.devtreemodel.get_iter(insert_iter)
        self.tempiter = self.devtreemodel.insert_after(
                                                      insert_iter,
                                                      [data1,
                                                      data2,
                                                      data3,
                                                      data4,
                                                      data5,
                                                      data6,
                                                      data7,
                                                      self.callback,
                                                      condition_back,
                                                      condition_for])
        thread.tempiter = self.devtreemodel.get_path(self.tempiter)
        COND.notify()
        COND.release()

    def model_getpath(self, thread, myiter):
        """get a item path from device tree"""
        del thread
        COND.acquire()
        self.abnormal_path = myiter
        COND.notify()
        COND.release()

    def browser_cliked(self, widget):
        """invoke a file browser dialog"""
        del widget
        browser = BrowseDlg()
        result, location = browser.run()

        if result == gtk.RESPONSE_OK:
            self.location = location
            self.radio_file_info.emit("clicked")
            self.entry_file_info.set_text(location)
            self.entry_ips_info.set_text("")

    def changed_cb(self, entry):
        """handle ips combox change event"""
        pkgaction = entry.get_active_text()
        if pkgaction == _("Add repository..."):
            repo = RepoDlg()
            repo.run()
            self.lookup_repo()

    def lookup_repo(self):
        """fetch repo list"""
        status, output = commands.getstatusoutput( 
        '%s/scripts/pkg_relate.sh list all' % ABSPATH)
        index = 1
        if status == 0:
            output_lines = output.splitlines()
            for line in output_lines:
                repo_name = line.split('\t')
                if not self.repo_listdic.has_key(repo_name[0]):
                    self.server_com.prepend_text(repo_name[0])
                    self.repo_listdic[repo_name[0]] = index
                    index = index + 1
            self.server_com.set_active(0)
            self.lenth = len(self.repo_listdic.keys()) - 1
        else:
            self.drv_button.set_sensitive(False)
            self.server_com.set_sensitive(False)

    def callback(self, path) :
        """show package info when user click info tag"""
        tree_index = self.devtreemodel.get_value( 
        self.devtreemodel.get_iter(path), 2)
        try:
            driver_type = self.__dev_tree[tree_index][3].pkg_type
            driver_name = self.__dev_tree[tree_index][3].pkg_name
            driver_location = self.__dev_tree[tree_index][3].pkg_location
            if (driver_type  == "PKG"):
                if (driver_name != ""):
                    self.radio_ips_info.emit("clicked")
                    self.entry_ips_info.set_text(driver_name)
                    self.entry_file_info.set_text("")
                    self.server_com.set_active(self.lenth -
                                    self.repo_listdic[driver_location])
            elif (driver_type == "SVR4"):
                if (driver_name != ""):
                    self.radio_file_info.emit("clicked")
                    self.entry_file_info.set_text(driver_location+driver_name)
                    self.entry_ips_info.set_text("")
            elif (driver_name != ""):
                driver_info = self.__dev_tree[tree_index][3].inf_link
                if (driver_info != ""):
                    webaction = lambda:webbrowser.open("%s" % driver_info)
                    t_start = threading.Thread(target=webaction)
                    t_start.setDaemon(True)
                    t_start.start()
            else:
                self.entry_ips_info.set_text("")
                self.entry_file_info.set_text("")
        except (UnboundLocalError, IndexError, DDUException):
            self.entry_ips_info.set_text("")
            self.entry_file_info.set_text("")

    def main_destroy(self, widget, data = None):
        """quit main thread"""
        del widget
        del data
 
        subprocess.Popen(["/bin/pkill", "-TERM", "-g", str(os.getpid())])
        gtk.main_quit()

    def on_popup_menu(self, item_tree, event=None):
        """show device tree context"""
        model, iter1 = item_tree.get_selection().get_selected()

        if event:
            if event.button != 3:
                return False
            if iter1 != None:
                data = model.get_value(iter1, 2)
                if data == 'category':
                    return False
            button = event.button
            event_time = event.time
            info = item_tree.get_path_at_pos(int(event.x), int(event.y))
            if info != None:
                self.detail_information.set_sensitive(True)
                path, col, cellx, celly = info
                del cellx, celly
                item_tree.grab_focus()
                item_tree.set_cursor(path, col, 0)
            else:
                self.detail_information.set_sensitive(False)
        else:
            path = model.get_path(iter1)
            button = 0
            event_time = 0
            item_tree.grab_focus()
            item_tree.set_cursor(path, item_tree.get_columns()[0], 0)

        self.popup_menu.popup(None, None, None, button, event_time)
        return True

    def on_detail_activate(self, menu):
        """show device detail info"""
        del menu
        model, item_iter = self.devtreeview.get_selection().get_selected()

        data = model.get_value(item_iter, 2)

        if data != 'category':
            tobe_handle = self.__dev_tree[data]
            disp_collection = tobe_handle[1]

            if tobe_handle != '':
                if tobe_handle[2] == 'c':
                    devpath = str(disp_collection.pci_path)
                    classcode = str(disp_collection.class_code)
                    device = str(disp_collection.description)
                    if len(tobe_handle) > 3:
                        driver_info = tobe_handle[3]
                    else:
                        driver_info = ''
                elif tobe_handle[2] == 'd':
                    devpath = str(disp_collection.pci_path)
                    device = str(disp_collection.description)
                    classcode = ''
                    driver_info = ''
                scriptsdir = ABSPATH + '/scripts'
                status, detail_output = commands.getstatusoutput( 
                '%s/det_info.sh %s CLASS=%s' % 
                (scriptsdir, devpath, classcode))
                if status == 0:
                    self.detail_inf_run = DetailInf(detail_output, 
                    driver_info, device, fg = 'reload')

    def submit_clicked(self, widget):
        """show submit dialog"""
        if widget != None:
            SubmitDlg(self.dev_submit)

    def help_clicked(self, widget):
        """show help dialog"""
        del widget
        subprocess.Popen(["yelp", "ghelp://%s/help/gnome/help/ddu/C/ddu.xml" % (ABSPATH) ])

    def drv_clicked(self, widget):
        """
        This Function handles the driver installation
        """
        del widget
        action = os.path.join(ABSPATH, self.__certdata)
        if self.radio_ips_info.get_active():
            if self.entry_ips_info.get_text().strip() == "":
                msg_dlg = MessageBox(self.window, _('Add Driver'), 
                _('Driver not installed'), _('The driver package is empty.'))
                msg_dlg.run()
            else:
                inst_dlg = InstDrv(action, install_method = "IPS", 
                install_media = self.entry_ips_info.get_text().strip(), 
                install_server = self.server_com.get_active_text())
                inst_dlg.run()
                self.__rescan = True
                self.rescan_button.emit("clicked")

        elif self.radio_file_info.get_active():
            if self.entry_file_info.get_text().strip() == "":
                msg_dlg = MessageBox(self.window, _('Add Driver'), 
                _('Driver not installed'), _('The driver path is empty.'))
                msg_dlg.run()
            else:
                entry_text = self.entry_file_info.get_text().strip()
                media = os.path.basename(entry_text)
                location = os.path.dirname(entry_text)
                inst_dlg = InstDrv(action, install_method = "UNK", 
                install_media = media, install_server = location)
                inst_dlg.run()
                self.__rescan = True
                self.rescan_button.emit("clicked")

    def rescan_clicked(self, widget):
        """handle rescan event"""
        del widget
        self.__disp_data = ''
        self.draw_devdisc()

        self.devtreeview.collapse_all()
        self.devtreeview.queue_draw()
        while gtk.events_pending():
            gtk.main_iteration()

        self.devtreeview.set_sensitive(False)
        self.drv_button.set_sensitive(False)

        self.__rescan = True
        self.dev_view.remove(self.hbox_msg)

        self.align = gtk.Alignment(0.5, 0.5, 1, 0)
        self.dev_pbar = gtk.ProgressBar()
        self.align.add(self.dev_pbar)
        self.dev_pbar.show()
        self.align.show()

        self.dev_view.add(self.align)

        gobject.timeout_add(1000, self.profunc)

        self.rescan_button.set_sensitive(False)

        self.rescan_thread = DeviceTree(COND)
        self.rescan_thread.connect("clear", self.model_clear)
        self.rescan_thread.connect("append", self.model_append)
        self.rescan_thread.connect("remove", self.model_remove)
        self.rescan_thread.connect("update", self.model_update)
        self.rescan_thread.connect("insert_after", self.model_insert_after)
        self.rescan_thread.connect("get_path", self.model_getpath)
        self.rescan_thread.setDaemon(True)
        self.rescan_thread.start()

    def profunc(self):
        """
        main function of waiting device tree in main thread and show a progress
        bar
        """
        if self.rescan_thread.finish == False:
            new_val = self.dev_pbar.get_fraction() + 0.01
            if new_val > 1.0:
                new_val = 1.0
            self.dev_pbar.set_fraction(new_val)
        else:
            self.__dev_tree = self.rescan_thread.dev_tree
            self.__certdata = self.rescan_thread.certdata
            self.dev_submit = self.rescan_thread.dev_submit
		
            self.devtreeview.expand_all()
            self.devtreeview.set_sensitive(True)

            if self.abnormal_path != '':
                self.devtreeview.scroll_to_cell( 
                self.abnormal_path,None,True,0.5,0)
            self.__rescan = False

            self.dev_view.remove(self.align)

            self.hbox_msg = gtk.HBox(False, 0)
            self.dev_view.add(self.hbox_msg)
            self.dev_viewport = gtk.Viewport()
            self.dev_viewport.set_shadow_type(gtk.SHADOW_NONE)
            self.hbox_msg.pack_start(self.dev_viewport, False, False, 0)
            self.devstatview = gtk.DrawingArea()
            self.devstatview.set_size_request(30, 0)
            self.devstatview.connect('expose-event', self.drawstat)
            self.dev_viewport.add(self.devstatview)

            self.dev_text = gtk.Label("")
            self.hbox_msg.pack_start(self.dev_text, False, False, 0)

            self.dev_view.show_all()
            self.rescan_button.set_sensitive(True)
            self.drv_button.set_sensitive(True)
			
        return self.__rescan


    def drawstat(self, widget, event):
        """handle driver statistics info"""
        self.wid_get = widget
        self.event_c = event
        self.__drawstat()

    def __drawstat(self):
        """show driver statistics info"""
        crd = self.wid_get.window.cairo_create()

        yes_driver = 0
        no_driver = 0
        all_driver = 0
        for iternum, iterdata in self.__dev_tree.iteritems():
            del iternum
            disp_type = iterdata[2]
            disp_collection = iterdata[1]
            if disp_type == 'c':
                if disp_collection.driver_name == '' or (
                (int(disp_collection.instance_id) < 0) and (
                disp_collection.attach_status == 'Detached'
                )):
                    no_driver += 1
                else:
                    yes_driver += 1
            all_driver += 1

        del all_driver, yes_driver
        if self.__rescan == False:
            drawable = self.wid_get.window
            drawable.clear()
		
            if no_driver > 0:
                iconfile = gtk.gdk.pixbuf_new_from_file(
                                          '%s/data/Missing-1.png' % ABSPATH)
            else:
                iconfile = gtk.gdk.pixbuf_new_from_file( 
                                          '%s/data/info.png' % ABSPATH)
            crd.set_source_pixbuf(iconfile, 0, 15)
            crd.paint()
            crd.stroke()
            self.submit_button.set_sensitive(True)

        status_str = str(_("<b>Driver Problems: %s</b>") % str(no_driver))
        self.dev_text.set_markup(status_str)
        if no_driver == 0:
            self.drv_button.set_sensitive(False)

    def draw_devdisc(self):
        """change drv_button automatically"""
        if self.__disp_data != '':
            if self.__disp_data[2] == 'c':
                disp_collection = self.__disp_data[1].split(':')
                if len(disp_collection) > 10:
                    self.drv_button.set_sensitive(True)
                else:
                    self.drv_button.set_sensitive(False)
            elif self.__disp_data[2] == 'd':
                self.drv_button.set_sensitive(True)

    def on_selection_changed(self, *args):
        """
        This function handles the selection action in the device treeview
        It just sets the __disp_data which will be used for
        drawdev/draw_devdisc, this action will affect displaying package
        information and diaplying detail information
        """
        scriptsdir = ABSPATH + '/scripts'

        model, item_iter = args[0].get_selected()
        selection = self

        if item_iter != None:
            data = model.get_value(item_iter, 2)
            if data != 'category':
                self.__disp_data = self.__dev_tree[data]
                disp_collection = self.__dev_tree[data][1]
                if self.__dev_tree[data][2] == "c":
                    devpath = str(disp_collection.pci_path)
                    classcode = str(disp_collection.class_code)
                    device = str(disp_collection.description)
                    try:
                        #only handle no-driver controller, if its driver has
                        #been found, then driver detail information will be
                        #displayed accordingly.
                        if len(self.__dev_tree[data]) > 3:
                            driver_info = str( 
                            self.__dev_tree[data][3].inf_link)
                            driver_type = str( 
                            self.__dev_tree[data][3].pkg_type)
                        if (driver_type  == "PKG"):
                            driver_package = str( 
                            self.__dev_tree[data][3].pkg_name)
                            driver_repo = str( 
                            self.__dev_tree[data][3].pkg_location)
                            selection.radio_ips_info.emit("clicked")
                            selection.entry_ips_info.set_text(driver_package)
                            selection.entry_file_info.set_text("")
                            selection.server_com.set_active( 
                            selection.lenth - \
                            selection.repo_listdic[driver_repo])
                        elif (driver_type == "SVR4"):
                            driver_package = str( 
                            self.__dev_tree[data][3].pkg_name)
                            selection.radio_file_info.emit("clicked")
                            selection.entry_file_info.set_text(driver_package)
                            selection.entry_ips_info.set_text("")
                        elif driver_type  == '':
                            selection.entry_ips_info.set_text('')
                            selection.entry_file_info.set_text('')
                    except (UnboundLocalError, DDUException):
                        driver_info = ''
                        selection.entry_ips_info.set_text('')
                        selection.entry_file_info.set_text('')
                elif self.__dev_tree[data][2] == "d":
                    devpath = str(disp_collection.pci_path)
                    device = str(disp_collection.class_code)
                    classcode = ''
                    driver_info = ''
                try:
                    if selection.detail_inf_run.spam():
                        status, detail_output = commands.getstatusoutput( 
                        '%s/det_info.sh %s CLASS=%s' % 
                        (scriptsdir, devpath, classcode))
                        del status
                        selection.detail_inf_run = DetailInf( 
                        detail_output, driver_info, device)
                except AttributeError:
                    pass
            else:
                selection.__disp_data = ''

def callback(icon):
    """handle notification event"""
    if NOTIFICATION != None:
        try:
            NOTIFICATION.close()
        except gobject.GError:
            pass
        icon.set_visible(False)
        HDDgui()
        gobject.threads_init()
        gtk.gdk.threads_init()
        gtk.gdk.threads_enter()
        gtk.main()
        gtk.gdk.threads_leave()
        sys.exit(0)

if __name__ == '__main__':
    try:
        gtk.init_check()
    except RuntimeError, e:
        print _("Unable to initialize gtk")
        print str(e)
        sys.exit(1)
    if len(sys.argv) >= 2 and sys.argv[1].startswith('--'):
        if sys.argv[1][2:]  == "silent":
            pynotify.init("DDU project")
            FIND_MISSING_DRIVER = False
            STATUS, OUTPUT = commands.getstatusoutput( 
            '%s/scripts/probe.sh init' % ABSPATH)

            SYSTEMXML = minidom.parse('%s/data/hdd.xml' % ABSPATH)

            CATEGORY = SYSTEMXML.getElementsByTagName('category')
   
            for catelist in CATEGORY:
                catename = catelist.attributes["name"].value
                probehook = catelist.getElementsByTagName('probe')[0]
		
                for probedata in probehook.childNodes:
                    #Get The probe script for each category
                    if probedata.nodeType == Node.TEXT_NODE:
                        probecmd = ABSPATH + '/' + probedata.data
                        STATUS, OUTPUT = commands.getstatusoutput(probecmd)
                        if len(OUTPUT) > 0 and OUTPUT.find("0x") > 0:
                            output_lines = OUTPUT.splitlines()
                            for line in output_lines:
                            #lookup components in a category
                                component_disc = line.split(':')
                                if(component_disc[1] == '') and \
                                component_disc[6] == 'unknown':
                                    FIND_MISSING_DRIVER = True
                                    break
            if FIND_MISSING_DRIVER == True:
                NOTIFICATION = pynotify.Notification(
                              "Missing Device Drivers",
                               "Click this box to display the devices\n"
                               "and to install the missing drivers.",
                               "%s/data/noti-dialog.png" % ABSPATH)
                NOTIFICATION.set_urgency(pynotify.URGENCY_NORMAL)
                NOTIFICATION.set_timeout(pynotify.EXPIRES_NEVER)

                ICON = gtk.status_icon_new_from_file( 
                                                "%s/data/icon.png" % ABSPATH)
                ICON.connect('activate', callback)
                NOTIFICATION.attach_to_status_icon(ICON)
                NOTIFICATION.show()
            else:
                sys.exit(0)
            gtk.main()
    else:
        HDDgui()
        gobject.threads_init()
        gtk.gdk.threads_init()
        gtk.gdk.threads_enter()
        gtk.main()
        gtk.gdk.threads_leave()
