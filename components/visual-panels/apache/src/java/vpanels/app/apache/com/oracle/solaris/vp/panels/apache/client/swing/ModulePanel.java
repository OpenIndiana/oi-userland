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

import java.awt.*;
import javax.swing.*;
import javax.swing.filechooser.FileSystemView;
import javax.swing.text.JTextComponent;
import com.oracle.solaris.vp.panel.swing.view.ChangeIndicator;
import com.oracle.solaris.vp.util.misc.ChangeableAggregator;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.misc.property.*;
import com.oracle.solaris.vp.util.swing.*;
import com.oracle.solaris.vp.util.swing.layout.*;
import com.oracle.solaris.vp.util.swing.property.
    TextComponentPropertySynchronizer;

@SuppressWarnings({"serial"})
public class ModulePanel extends SettingsPanel {
    //
    // Instance data
    //

    private MutableProperty<String> nameProperty = new StringProperty();
    private MutableProperty<String> fileProperty = new StringProperty();

    {
	ChangeableAggregator aggregator = getChangeableAggregator();
	aggregator.addChangeables(nameProperty, fileProperty);
    }

    private JFileChooser fileChooser;

    //
    // Constructors
    //

    public ModulePanel() {
	JPanel form = createForm();
	setContent(form, false, false);
    }

    //
    // ModulePanel methods
    //

    public MutableProperty<String> getFileProperty() {
	return fileProperty;
    }

    public MutableProperty<String> getNameProperty() {
	return nameProperty;
    }

    public void init(Module module) {
	// Sanity check -- the UI should be updated only on the event thread
	assert EventQueue.isDispatchThread();

	FileSystemView fsView;

	if (module == null) {
            fsView = FileSystemView.getFileSystemView();
	} else {
	    ApacheUtil.update(module.getNameProperty(), nameProperty);
	    ApacheUtil.update(module.getFileProperty(), fileProperty);

	    fsView = module.getParent().getApacheInfo().getPanelDescriptor().
		getFileSystemView();
	}

	fileChooser.setFileSystemView(fsView);
    }

    //
    // Private methods
    //

    private JPanel createForm() {
	int gap = GUIUtil.getHalfGap();

	JLabel nameLabel = new JLabel(
	    Finder.getString("module.edit.name"));

	JTextField nameField = GUIUtil.createTextField();
	new TextComponentPropertySynchronizer<String, JTextComponent>(
	    nameProperty, nameField);
	ChangeIndicator nameChange = new ChangeIndicator();
	nameProperty.addChangeListener(nameChange);

	JLabel fileLabel = new JLabel(
	    Finder.getString("module.edit.file"));

	BrowsableFilePanel fileField = new BrowsableFilePanel();
	fileField.setOpaque(false);
	fileChooser = fileField.getFileChooser();

	new TextComponentPropertySynchronizer<String, JTextComponent>(
	    fileProperty, fileField.getField());
	ChangeIndicator fileChange = new ChangeIndicator();
	fileProperty.addChangeListener(fileChange);

	JPanel filePanel = new JPanel(new BorderLayout(gap, 0));
	filePanel.setOpaque(false);
	filePanel.add(fileField, BorderLayout.CENTER);
	filePanel.add(fileChange, BorderLayout.EAST);

	JPanel formPanel = new JPanel();
	formPanel.setOpaque(false);
	Form form = new Form(formPanel, VerticalAnchor.TOP);

	ColumnLayoutConstraint c = new ColumnLayoutConstraint(
	    HorizontalAnchor.FILL, gap);

	HasAnchors a = new SimpleHasAnchors(
	    HorizontalAnchor.LEFT, VerticalAnchor.CENTER);

	form.addTable(3, gap, gap, HorizontalAnchor.LEFT, c);

	form.add(nameLabel, a);
	form.add(nameField, a);
	form.add(nameChange, a);

	form.add(fileLabel, a);
	form.add(filePanel, a);
	form.add(fileChange, a);

	return formPanel;
    }
}
