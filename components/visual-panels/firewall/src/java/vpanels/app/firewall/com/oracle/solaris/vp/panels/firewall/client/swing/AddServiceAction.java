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

package com.oracle.solaris.vp.panels.firewall.client.swing;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.util.List;
import javax.swing.*;
import javax.swing.event.*;
import com.oracle.solaris.vp.panel.common.action.*;
import com.oracle.solaris.vp.panel.common.control.*;
import com.oracle.solaris.vp.panel.common.model.ManagedObject;
import com.oracle.solaris.vp.panel.swing.action.AddManagedObjectAction;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.swing.*;

@SuppressWarnings({"serial"})
public class AddServiceAction extends AddManagedObjectAction<ManagedObject,
    ServiceManagedObject, ServiceManagedObject> {

    //
    // Static data
    //

    private static final String BUTTON_TEXT = Finder.getString(
	"service.action.add.button");

    //
    // Instance data
    //

    private MainControl control;

    //
    // Constructors
    //

    public AddServiceAction(MainControl control) {
	super(BUTTON_TEXT, null, control);
	this.control = control;
	setLoops(true);
    }

    //
    // StructuredAction methods
    //

    @Override
    public ServiceManagedObject invoke(ServiceManagedObject rtInput)
	throws ActionAbortedException, ActionFailedException {
	List<ManagedObject> svcList = new ArrayList<ManagedObject>(
	    control.getPanelDescriptor().getAllServices());

	setPresetInput(svcList);
	return super.invoke(rtInput);
    }

    @Override
    public ServiceManagedObject getRuntimeInput(
	List<ManagedObject> selection, ServiceManagedObject rtInput)
	throws ActionAbortedException {

        Object response = getInput(selection);
        if (response == null)
            throw new ActionAbortedException();

        return (ServiceManagedObject) response;
    }

    //
    // DefaultStructuredAction methods
    //

    @Override
    public ServiceManagedObject workBusy(List<ManagedObject> selection,
	ServiceManagedObject svc) throws ActionAbortedException,
	ActionFailedException, ActionUnauthorizedException {

	FirewallPanelDescriptor descriptor = control.getPanelDescriptor();
	descriptor.addChildren(svc);

	// Navigate to the new service
	Navigable navigable = new SimpleNavigable(
	    ServiceEditControl.ID, null,
	    ServiceEditControl.PARAM_SVC, svc.getId());

	control.getNavigator().goToAsync(false, control, navigable);

	return svc;
    }

    //
    // A custom inputDialog method as the static JOptionPane.showInputDialog()
    // treats input value as valid even when user selected the cancel option.
    //
    private Object getInput(List<ManagedObject> selection) {
	SettingsPanel panel = new SettingsPanel();
	panel.setBorder(GUIUtil.getEmptyBorder());
	panel.getHelpField().setText(
            Finder.getString("service.action.add.message"));

        SettingsButtonBar bar = panel.getButtonBar();
	final JButton okayButton = bar.getOkayButton();

        final JList list = new JList(selection.toArray());
        list.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
        list.setVisibleRowCount(10);
        list.addListSelectionListener(
            new ListSelectionListener() {
                public void valueChanged(ListSelectionEvent e) {
		    okayButton.setEnabled(!list.isSelectionEmpty());
                }
	    });

        JScrollPane scroll = new JScrollPane(list);
	panel.setContent(scroll, false, false);

	Window pWin = SwingUtilities.getWindowAncestor(
	    getHasComponent().getComponent());
        final JDialog dialog = new JDialog(pWin,
	    Dialog.ModalityType.DOCUMENT_MODAL);

        okayButton.addActionListener(
	    new ActionListener() {
                public void actionPerformed(ActionEvent e) {
                    dialog.setVisible(false);
                }
	    });

        bar.getCancelButton().addActionListener(
	    new ActionListener() {
		public void actionPerformed(ActionEvent e) {
                    list.clearSelection();
		    dialog.setVisible(false);
		}
	    });

        // Allow double-clicking to add a service
        list.addMouseListener(
            new MouseAdapter() {
		@Override
		public void mouseClicked(MouseEvent e) {
		    if (e.getClickCount() >= 2) {
			dialog.setVisible(false);
		    }
		}
	    });

	Container cont = dialog.getContentPane();
	cont.setLayout(new BorderLayout());
	cont.add(panel, BorderLayout.CENTER);

        dialog.pack();
	dialog.setLocationRelativeTo(pWin);
        dialog.setVisible(true);
        dialog.dispose();

	return list.getSelectedValue();
    }
}
