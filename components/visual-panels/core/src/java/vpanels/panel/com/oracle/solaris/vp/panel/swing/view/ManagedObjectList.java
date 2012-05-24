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
 * Copyright (c) 2009, 2012, Oracle and/or its affiliates. All rights reserved.
 */

package com.oracle.solaris.vp.panel.swing.view;

import java.awt.EventQueue;
import java.awt.event.*;
import javax.swing.*;
import com.oracle.solaris.vp.panel.common.model.ManagedObject;
import com.oracle.solaris.vp.util.swing.*;

@SuppressWarnings({"serial"})
public class ManagedObjectList extends ExtList {
    //
    // Instance data
    //

    private JPopupMenu popup;
    private Action dAction;

    //
    // Constructors
    //

    public ManagedObjectList(ManagedObjectTableModel model, JPopupMenu popup,
	Action dAction, boolean iconView) {

	// Cindy Crawford was always my favorite
	super(model);

	this.popup = popup;
	this.dAction = dAction;

	ListSelectionModel lsModel = new ExtListSelectionModel();
	lsModel.setSelectionMode(
	    ListSelectionModel.MULTIPLE_INTERVAL_SELECTION);
	setSelectionModel(lsModel);

	if (iconView) {
	    setLayoutOrientation(JList.HORIZONTAL_WRAP);
	    setVisibleRowCount(0);
	}

	SimpleCellRenderer renderer =
	    new ManagedObjectCellRenderer<ManagedObject>();
	renderer.configureFor(this);

	setCellRenderer(renderer);

	addMouseListener(
	    new MouseAdapter() {
		@Override
		public void mouseReleased(final MouseEvent e) {
		    if (e.isPopupTrigger()) {
			EventQueue.invokeLater(
			    new Runnable() {
				@Override
				public void run() {
				    showPopup(e.getX(), e.getY());
				}
			    });
		    }
		}

		@Override
		public void mousePressed(final MouseEvent e) {
		    if (e.isPopupTrigger()) {
			// By default, the JList doesn't select on right-clicks.
			// If right-clicks are a popup trigger, modify selection
			// before popping up the menu.
			if (e.getButton() == MouseEvent.BUTTON3) {
			    int index = locationToIndex(e.getPoint());
			    if (index >= 0) {
				if (!isSelectedIndex(index)) {
				    clearSelection();
				    setSelectedIndex(index);
				};
			    }
			}

			// Invoke later so that events resulting from any
			// change in selection above can be processed before the
			// popup is shown.
			EventQueue.invokeLater(
			    new Runnable() {
				@Override
				public void run() {
				    showPopup(e.getX(), e.getY());
				}
			    });
		    }
		}

		@Override
		public void mouseClicked(MouseEvent e) {
		    final Action dAction = getDefaultAction();

		    // Invoke default action (if non-null) on double-click
		    if (dAction != null && GUIUtil.isUnmodifiedClick(e, 2) &&
			dAction.isEnabled()) {

			EventQueue.invokeLater(
			    new Runnable() {
				@Override
				public void run() {
				    ActionEvent ae = new ActionEvent(
					ManagedObjectList.this,
					ActionEvent.ACTION_PERFORMED,
					"default");
				    dAction.actionPerformed(ae);
				}
			    });
		    }
		}
	    });
    }

    //
    // ManagedObjectList methods
    //

    public Action getDefaultAction() {
	return dAction;
    }

    public JPopupMenu getPopupMenu() {
	return popup;
    }

    public void setDefaultAction(Action dAction) {
	this.dAction = dAction;
    }

    public void showPopup(int x, int y) {
	JPopupMenu popup = getPopupMenu();
	if (popup != null) {
	    popup.show(this, x, y);
	}
    }
}
