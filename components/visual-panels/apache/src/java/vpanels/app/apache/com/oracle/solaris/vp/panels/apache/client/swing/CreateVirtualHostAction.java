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

package com.oracle.solaris.vp.panels.apache.client.swing;

import java.awt.Component;
import java.awt.event.*;
import java.util.List;
import javax.swing.*;
import javax.swing.text.JTextComponent;
import com.oracle.solaris.vp.panel.common.action.*;
import com.oracle.solaris.vp.panel.common.control.*;
import com.oracle.solaris.vp.panel.common.model.ManagedObject;
import com.oracle.solaris.vp.panel.swing.action.AddManagedObjectAction;
import com.oracle.solaris.vp.util.misc.ObjectUtil;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.misc.property.StringProperty;
import com.oracle.solaris.vp.util.swing.*;
import com.oracle.solaris.vp.util.swing.layout.*;
import com.oracle.solaris.vp.util.swing.property.
    TextComponentPropertySynchronizer;

@SuppressWarnings({"serial"})
public class CreateVirtualHostAction extends AddManagedObjectAction
    <ManagedObject, CreateVirtualHostAction.Data, VirtualHost> {

    //
    // Inner classes
    //

    protected class Data {
	//
	// Instance data
	//

	public StringProperty domainProperty = new StringProperty();
	public StringProperty docRootProperty = new StringProperty();
	public JOptionPane pane;
	public JDialog dialog;

	//
	// Constructors
	//

	public Data() {
	    ActionListener listener =
		new ActionListener() {
		    @Override
		    public void actionPerformed(ActionEvent e) {
			pane.setValue(JOptionPane.OK_OPTION);
		    }
		};

	    JLabel domainLabel = new JLabel(
		Finder.getString("vhost.general.edit.domain"));
	    JTextField domainField = GUIUtil.createTextField();
	    domainField.addActionListener(listener);
	    new TextComponentPropertySynchronizer<String, JTextField>(
		domainProperty, domainField, false);

	    JLabel docRootLabel = new JLabel(
		Finder.getString("vhost.general.edit.docroot"));

	    BrowsableFilePanel docRootField = new BrowsableFilePanel();
	    docRootField.setOpaque(false);
	    JFileChooser chooser = docRootField.getFileChooser();
	    chooser.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
	    chooser.setFileSystemView(
		control.getPanelDescriptor().getFileSystemView());

	    new TextComponentPropertySynchronizer<String, JTextComponent>(
		docRootProperty, docRootField.getField(), false);

	    JPanel formPanel = new JPanel();
	    formPanel.setOpaque(false);
	    Form form = new Form(formPanel, VerticalAnchor.TOP);

	    int gap = GUIUtil.getHalfGap();

	    ColumnLayoutConstraint c = new ColumnLayoutConstraint(
		HorizontalAnchor.FILL, gap);

	    HasAnchors a = new SimpleHasAnchors(
		HorizontalAnchor.LEFT, VerticalAnchor.CENTER);

	    form.addTable(2, gap, gap, HorizontalAnchor.LEFT, c);

	    form.add(domainLabel, a);
	    form.add(domainField, a);

	    form.add(docRootLabel, a);
	    form.add(docRootField, a);

	    pane = new JOptionPane(formPanel, JOptionPane.PLAIN_MESSAGE,
		JOptionPane.OK_CANCEL_OPTION);

	    dialog = pane.createDialog(getHasComponent().getComponent(),
		Finder.getString("vhosts.action.create.title"));
	}
    }

    //
    // Static data
    //

    private static final String TEXT = Finder.getString(
	"vhosts.action.create.button");

    //
    // Instance data
    //

    private MainControl control;

    //
    // Constructors
    //

    public CreateVirtualHostAction(MainControl control) {
	super(TEXT, null, control);
	this.control = control;
	setLoops(true);
    }

    //
    // StructuredAction methods
    //

    @Override
    public Data getRuntimeInput(List<ManagedObject> selection, Data data)
	throws ActionAbortedException {

	// Since this action navigates to the new object once created, we must
	// first navigate to control so that any outstanding changes in the
	// current Control are handled.
	try {
	    control.getNavigator().goToAsyncAndWait(false, control);
	} catch (NavigationException e) {
	    throw new ActionAbortedException(e);
	}

	if (data == null) {
	    data = new Data();
	}

	// Blocks until dismissed
	data.dialog.setVisible(true);

	if (!ObjectUtil.equals(data.pane.getValue(), JOptionPane.OK_OPTION)) {
	    throw new ActionAbortedException();
	}

	return data;
    }

    //
    // DefaultStructuredAction methods
    //

    @Override
    public VirtualHost workBusy(List<ManagedObject> selection, Data data)
	throws ActionAbortedException, ActionFailedException,
	ActionUnauthorizedException {

	String domain = data.domainProperty.getValue();
	VirtualHost.validateDomainName(domain, null);

	ApachePanelDescriptor descriptor = control.getPanelDescriptor();

	VirtualHost vHost = new VirtualHost(descriptor);
	vHost.getDomainProperty().setFirstValue(domain);

	vHost.getDocRootProperty().setFirstValue(
	    data.docRootProperty.getValue());

	descriptor.addChildren(vHost);

	// Navigate to the new virtual host
	Navigable navigable = new SimpleNavigable(
	    VirtualHostControl.ID, null,
	    VirtualHostControl.PARAM_ID, vHost.getId());

	control.getNavigator().goToAsync(false, control, navigable);

	return vHost;
    }
}
