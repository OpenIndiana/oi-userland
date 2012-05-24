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

package com.oracle.solaris.vp.panels.sysmon.client.swing;

import java.awt.EventQueue;
import java.util.*;
import javax.swing.*;
import javax.swing.event.*;
import com.oracle.solaris.vp.panel.common.action.*;
import com.oracle.solaris.vp.panel.common.control.*;
import com.oracle.solaris.vp.panel.swing.action.LaunchManagedObjectAction;
import com.oracle.solaris.vp.panel.swing.control.*;
import com.oracle.solaris.vp.panel.swing.view.ManagedObjectTableModel;
import com.oracle.solaris.vp.util.misc.finder.Finder;

public class SysMonListControl
    extends SettingsControl<SysMonPanelDescriptor, SysMonListPanel> {

    //
    // Static data
    //

    public static final String ID = "list";
    public static final String NAME = Finder.getString("list.name");

    //
    // Instance data
    //

    private StructuredAction<List<MonitoredResource>, ?, ?> launcher =
	new LaunchManagedObjectAction<MonitoredResource>(this) {

	@Override
	public Navigable[] getRuntimeInput(List<MonitoredResource> selection,
	    Navigable[] path) {

	    // Assume valid selection
	    MonitoredResource monitored = selection.get(0);
	    return monitored.getPanelAddress();
	}
    };

    //
    // Constructors
    //

    public SysMonListControl(SysMonPanelDescriptor descriptor) {
	super(ID, NAME, descriptor);
    }

    //
    // SwingControl methods
    //

    @Override
    protected void configComponent(SysMonListPanel panel) {
	super.configComponent(panel);
	addDefaultCloseAction(false);
    }

    @Override
    protected SysMonListPanel createComponent() {
	ListModel model = new ManagedObjectTableModel<MonitoredResource>(
	    getPanelDescriptor());
	SysMonListPanel panel = new SysMonListPanel(model);

	final JList list = panel.getList();
	list.getSelectionModel().addListSelectionListener(
	    new ListSelectionListener() {
		@Override
		public void valueChanged(ListSelectionEvent e) {
		    if (!e.getValueIsAdjusting()) {
                        MonitoredResource monitored =
			    (MonitoredResource)list.getSelectedValue();

			if (monitored != null) {
			    launchAsync(monitored);
                        }
		    }
		}
	    });

	return panel;
    }

    //
    // Private methods
    //

    private void launchAsync(final MonitoredResource monitored) {
	launcher.asyncExec(
	    new Runnable() {
		@Override
		public void run() {
		    List<MonitoredResource> selection =
			new ArrayList<MonitoredResource>(1);

		    selection.add(monitored);
		    launcher.setPresetInput(selection);

		    try {
			launcher.invoke();

			// Dismiss frame
			getNavigator().goToAsync(false, SysMonListControl.this,
			    Navigator.PARENT_NAVIGABLE);

		    // Thrown by invoke()
		    } catch (ActionException ignore) {
		    }

		    EventQueue.invokeLater(
			new Runnable() {
			    @Override
			    public void run() {
				getComponent().getList().clearSelection();
			    }
			});
		}
	    });
    }
}
