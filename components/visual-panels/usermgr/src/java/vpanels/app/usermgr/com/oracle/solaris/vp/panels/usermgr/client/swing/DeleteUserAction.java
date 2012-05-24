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

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.util.List;
import javax.swing.JOptionPane;
import com.oracle.solaris.vp.panel.common.action.*;
import com.oracle.solaris.vp.panel.common.control.Control;
import com.oracle.solaris.vp.panel.swing.action.DeleteManagedObjectAction;
import com.oracle.solaris.vp.panel.swing.control.SwingControl;
import com.oracle.solaris.vp.util.misc.*;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.swing.GUIUtil;

/**
 * Delete a user or role
 */
@SuppressWarnings({"serial"})
public class DeleteUserAction extends DeleteManagedObjectAction
    <UserManagedObject, UserManagedObject, List<UserManagedObject>> {

    //
    // Static data
    //

    private static final String DELETE_TEXT = Finder.getString(
	"usermgr.action.delete.button");

    //
    // Instance data
    //

    private SwingControl control;

    //
    // Constructors
    //

    public DeleteUserAction(SwingControl control) {
	super(DELETE_TEXT, null, control);
        ActionString actStr = new ActionString(
	    "usermgr.action.delete.button");
	putValue(Action.NAME, actStr.getString());
	putValue(Action.MNEMONIC_KEY, actStr.getMnemonic());
	this.control = control;
    }

    //
    // StructuredAction methods
    //

    @Override
    public UserManagedObject getRuntimeInput(List<UserManagedObject> selection,
	UserManagedObject input) throws ActionAbortedException {

	if (selection.isEmpty()) {
	    throw new ActionAbortedException();
	}
	UserMgrPanelDescriptor descriptor = (UserMgrPanelDescriptor)
	    control.getPanelDescriptor();

	String message = Finder.getString("usermgr.action.delete.confirm." +
		descriptor.getTypeString(), selection.get(0).getName());

	JOptionPane pane = new JOptionPane(message,
	    JOptionPane.QUESTION_MESSAGE, JOptionPane.OK_CANCEL_OPTION);
	 UserMgrUtils.removeIcons(pane);
	 JDialog dialog = pane.createDialog(getHasComponent().getComponent(),
		Finder.getString("usermgr.action.delete.title." +
		descriptor.getTypeString()));

	dialog.setVisible(true);

	if (!ObjectUtil.equals(pane.getValue(), JOptionPane.OK_OPTION)) {
	    throw new ActionAbortedException();
        }

	return null;
    }

    //
    // DefaultStructuredAction methods
    //

    @Override
    public List<UserManagedObject> workBusy(List<UserManagedObject> selection,
	UserManagedObject input) throws ActionAbortedException,
	ActionFailedException, ActionUnauthorizedException {

	if (!selection.isEmpty()) {
	    UserMgrPanelDescriptor descriptor = (UserMgrPanelDescriptor)
		control.getPanelDescriptor();
	    descriptor.addToDeleteList(selection.get(0));
	    descriptor.saveDeletedUsers();
	    // If the running Control is a UserMgrControl for a just-deleted
	    // service, reset the Control and navigate back to its parent
	    Control child = control.getRunningChild();
	    if (child instanceof UserMgrBasicControl) {
		UserManagedObject umo =
		    ((UserMgrBasicControl)child).getUserManagedObject();

		if (selection.contains(umo)) {
		    child.doCancel();
		}
	    }
	}

	return selection;
    }
}
