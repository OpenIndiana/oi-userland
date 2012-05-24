/*
 * CDDL HEADER START
 *
 * The contents of this file are subject to the terms of the
 * Common Development and Distribution License (the "License").
 * You may not use this file except in compliance with the License.
 *
 * You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
 * or http://www.opensolaris.org/os/licensing.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 *
 * When distributing Covered Code, include this CDDL HEADER in each
 * file and include the License file at usr/src/OPENSOLARIS.LICENSE.
 * If applicable, add the following below this CDDL HEADER, with the
 * fields enclosed by brackets "[]" replaced with your own identifying
 * information: Portions Copyright [yyyy] [name of copyright owner]
 *
 * CDDL HEADER END
 */

/*
 * Copyright (c) 2010, 2012, Oracle and/or its affiliates. All rights reserved.
 */

package com.oracle.solaris.vp.panels.usermgr.client.swing;

import java.util.List;
import java.util.Map;
import javax.swing.*;
import javax.swing.event.*;
import java.awt.event.*;
import javax.swing.border.Border;
import com.oracle.solaris.vp.panel.common.action.*;
import com.oracle.solaris.vp.panel.common.control.*;
import com.oracle.solaris.vp.panel.swing.control.*;
import com.oracle.solaris.vp.panel.swing.view.*;
import com.oracle.solaris.vp.util.misc.ChangeableAggregator;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.swing.ClippedBorder;

/**
 * Main User Manager Control
 */
public class MainControl extends ListSelectorControl
    <UserMgrPanelDescriptor, ListSelectorPanel, UserManagedObject> {

    //
    // Static data
    //

    public static final String ID = "main";

    //
    // Instance data
    //

    private ManagedObjectTableModel model;
    private ListSelectorPanel panel;
    private UserMgrBasicControl control = null;

    //
    // Constructors
    //

    public MainControl(UserMgrPanelDescriptor descriptor) {
	super(ID, null, descriptor);
    }

    //
    // Control methods
    //

    @Override
    public String getHelpMapID() {
        return "usermgr-mainpanel";
    }

    @Override
    protected void save() throws ActionAbortedException, ActionFailedException,
	ActionUnauthorizedException {

	// First delete any users, then add new users, then modify users
	getPanelDescriptor().saveDeletedUsers();

	getPanelDescriptor().saveAddedUsers();

	getPanelDescriptor().saveModifiedUsers();
	control.clearChanges();

	super.save();
    }

    //
    // DefaultControl methods
    //

    @Override
    protected void ensureChildrenCreated() {
	if (children.size() == 0) {
	    control = new UserMgrBasicControl(getPanelDescriptor());
	    addChildren(control);
	    addToLayout(control);
	}
    }

    //
    // Create the Users List
    //
    @Override
    protected ListSelectorPanel createComponent() {
	panel = new ListSelectorPanel();
	panel.setSelectionTitle(Finder.getString("usermgr.list.title.user"));

	Border border = panel.getBorder();
	panel.setBorder(new ClippedBorder(border, false, true, true, true));

	JList list = panel.getSelectionComponent();
	list.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
	ManagedObjectCellRenderer<UserManagedObject> renderer =
	    new ManagedObjectCellRenderer<UserManagedObject>();
	renderer.configureFor(list);
	list.setCellRenderer(renderer);

	panel.getChangeableAggregator().addChangeables(
	    getPanelDescriptor().getChangeableAggregator());

	// Add actions to create/delete/filter users
	addAction(panel, new AddUserAction(this), true, true);
	addAction(panel, new DeleteUserAction(this), true, true);
	addAction(panel, new FilterUserAction(this), true, true);

	setDefaultContentView(new UserMgrEmptyPanel());

	return panel;
    }

    @Override
    protected void configComponent(ListSelectorPanel panel) {
	super.configComponent(panel);
	addDefaultApplyAction();
	addDefaultCancelAction(true);
	addDefaultOkayAction(true);
	addDefaultHelpAction();
    }

    @Override
    public void descendantStarted(Control[] path) {
	super.descendantStarted(path);

	// Start monitoring descendants for changes
	Control control = path[path.length - 1];
	if (control instanceof SwingControl) {
	    ChangeableAggregator aggregator =
		((SwingControl)control).getChangeableAggregator();

	    if (aggregator != null) {
		getComponent().getChangeableAggregator().addChangeables(
		    aggregator);
	    }
	}
    }

    @Override
    public void descendantStopped(Control[] path) {
	super.descendantStopped(path);

	// Stop monitoring stopped descendant for changes
	Control control = path[path.length - 1];
	if (control instanceof SwingControl) {
	    ChangeableAggregator aggregator =
		((SwingControl)control).getChangeableAggregator();

	    if (aggregator != null) {
		getComponent().getChangeableAggregator().removeChangeable(
		    aggregator);
	    }
	}
    }

     //
     // Selector Control methods
     //

    /**
     * Construct a Navigable path to the selected Control
     */
    @Override
    protected Navigable[] getPathForSelection(
        List<UserManagedObject> selection) {

	if (selection.isEmpty()) {
	    return null;
	}
	UserManagedObject uobj = selection.get(0);
	Navigable navigable = new SimpleNavigable(UserMgrBasicControl.ID,
	    uobj.getName(), UserMgrBasicControl.PARAM_USER, uobj.getId());
 	return new Navigable[] {navigable};
    }

    //
    // ListSelectorControl methods
    //

    /**
     * Get the index of a given Control
     */
    @Override
    protected int getListIndexOf(Control child) {
   	UserManagedObject umo =
		((UserMgrBasicControl)child).getUserManagedObject();
  	int uIndex = getPanelDescriptor().indexOf(umo);

 	UserManagedObject utemp = (UserManagedObject) getComponent().
	    getSelectionComponent().getModel().getElementAt(uIndex);
 	assert (utemp.getId().equals(umo.getId()));

 	return uIndex;
    }

    /**
     * Get the model to use in the Users list
     */
    @Override
    protected ListModel getListModel() {
	if (model == null) {
	    model = new ManagedObjectTableModel<UserManagedObject>
		(getPanelDescriptor());
	}
	return model;
    }

    /**
     * Get the model to use in the Users list
     */
    public void setListTitle(String listTitle) {
        if (panel != null)
	    panel.setSelectionTitle(listTitle);
    }


    @Override
    protected void addDefaultCancelAction(final boolean quit) {
	getComponent().getButtonBar().getCancelButton().addActionListener(
	    new ActionListener() {
		@Override
		public void actionPerformed(ActionEvent e) {
		    Control.UnsavedChangesAction action;
		    ChangeableAggregator aggregator =
			getComponent().getChangeableAggregator();
		    if (aggregator != null && aggregator.isChanged()) {
			action = getUnsavedChangesAction();
		    } else {
			action = Control.UnsavedChangesAction.DISCARD;
		    }
		    switch (action) {
		    case SAVE:
			doSaveAndQuit();
			break;
		    case DISCARD:
			doQuit();
			break;
		    case CANCEL:
			break;
		    }
		}
	    });
    }
}
