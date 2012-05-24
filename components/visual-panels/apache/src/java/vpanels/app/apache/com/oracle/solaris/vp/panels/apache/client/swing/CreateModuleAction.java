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
import javax.swing.filechooser.FileSystemView;
import com.oracle.solaris.vp.panel.common.action.*;
import com.oracle.solaris.vp.panel.common.control.*;
import com.oracle.solaris.vp.panel.swing.action.AddManagedObjectAction;
import com.oracle.solaris.vp.util.misc.ObjectUtil;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.misc.property.StringProperty;
import com.oracle.solaris.vp.util.swing.*;
import com.oracle.solaris.vp.util.swing.layout.*;
import com.oracle.solaris.vp.util.swing.property.
    TextComponentPropertySynchronizer;

@SuppressWarnings({"serial"})
public class CreateModuleAction extends AddManagedObjectAction
    <Module, CreateModuleAction.Data, Module> {

    //
    // Inner classes
    //

    protected class Data {
	//
	// Instance data
	//

	public StringProperty nameProperty = new StringProperty();
	public StringProperty fileProperty = new StringProperty();
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

	    JLabel nameLabel = new JLabel(
		Finder.getString("module.edit.name"));
	    JTextField nameField = GUIUtil.createTextField();
	    nameField.addActionListener(listener);
	    new TextComponentPropertySynchronizer<String, JTextField>(
		nameProperty, nameField);

	    JLabel fileLabel = new JLabel(
		Finder.getString("module.edit.file"));

	    BrowsableFilePanel fileField = new BrowsableFilePanel();
	    fileField.setOpaque(false);

	    FileSystemView fsView =
		control.getPanelDescriptor().getFileSystemView();
	    fileField.getFileChooser().setFileSystemView(fsView);

	    new TextComponentPropertySynchronizer<String, JTextField>(
		fileProperty, fileField.getField());

	    JPanel formPanel = new JPanel();
	    formPanel.setOpaque(false);
	    Form form = new Form(formPanel, VerticalAnchor.TOP);

	    int gap = GUIUtil.getHalfGap();

	    ColumnLayoutConstraint c = new ColumnLayoutConstraint(
		HorizontalAnchor.FILL, gap);

	    HasAnchors a = new SimpleHasAnchors(
		HorizontalAnchor.LEFT, VerticalAnchor.CENTER);

	    form.addTable(2, gap, gap, HorizontalAnchor.LEFT, c);

	    form.add(nameLabel, a);
	    form.add(nameField, a);

	    form.add(fileLabel, a);
	    form.add(fileField, a);

	    pane = new JOptionPane(formPanel, JOptionPane.PLAIN_MESSAGE,
		JOptionPane.OK_CANCEL_OPTION);

	    dialog = pane.createDialog(getHasComponent().getComponent(),
		Finder.getString("modules.action.create.title"));
	}
    }

    //
    // Static Data
    //

    private static final String TEXT = Finder.getString(
	"modules.action.create.button");

    //
    // Instance Data
    //

    private ModulesControl control;

    //
    // Constructors
    //

    public CreateModuleAction(ModulesControl control) {
	super(TEXT, null, control);
	this.control = control;
	setLoops(true);
    }

    //
    // StructuredAction methods
    //

    @Override
    public Data getRuntimeInput(List<Module> selection, Data data)
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
    public Module workBusy(List<Module> selection, Data data)
	throws ActionAbortedException, ActionFailedException,
	ActionUnauthorizedException {

	String name = data.nameProperty.getValue();
	String file = data.fileProperty.getValue();

	// Throws ActionFailedException
	ModuleControl.validate(name, file);

	Modules modules = control.getHasModules().getModules();

	if (modules.getModule(name) != null) {
	    throw new ActionFailedException(Finder.getString(
		"module.error.duplicate", name));
	}

	Module module = new Module(modules);
	module.getNameProperty().setValue(name);
	module.getFileProperty().setValue(file);

	modules.addChildren(module);

	// Navigate to the new module
	Navigable navigable = new SimpleNavigable(
	    ModuleControl.ID, null,
	    ModuleControl.PARAM_MODULE, module.getId());

	control.getNavigator().goToAsync(false, control, navigable);

	return module;
    }
}
