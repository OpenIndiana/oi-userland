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
import com.oracle.solaris.vp.panel.swing.view.ChangeIndicator;
import com.oracle.solaris.vp.util.misc.ChangeableAggregator;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.misc.property.*;
import com.oracle.solaris.vp.util.swing.*;
import com.oracle.solaris.vp.util.swing.layout.*;
import com.oracle.solaris.vp.util.swing.property.*;

@SuppressWarnings({"serial"})
public class GlobalPanel extends SettingsPanel {
    //
    // Instance data
    //

    private MutableProperty<Boolean> enabledProperty = new BooleanProperty();
    private MutableProperty<Boolean> customEnabledProperty =
	new BooleanProperty();
    private MutableProperty<String> customFileProperty = new StringProperty();
    private JFileChooser fileChooser;

    {
	ChangeableAggregator aggregator = getChangeableAggregator();
        aggregator.addChangeables(enabledProperty, customEnabledProperty,
	    customFileProperty);
    }

    private ChangeButton mimeTypesButton;
    private ChangeButton modulesButton;

    //
    // Constructors
    //

    public GlobalPanel() {
	JPanel form = createForm();
	setContent(form, false, false);
    }

    //
    // GlobalPanel methods
    //

    public MutableProperty<Boolean> getEnabledProperty() {
	return enabledProperty;
    }

    public MutableProperty<Boolean> getCustomEnabledProperty() {
	return customEnabledProperty;
    }

    public MutableProperty<String> getCustomFileProperty() {
	return customFileProperty;
    }

    public ChangeButton getMimeTypesButton() {
	return mimeTypesButton;
    }

    public ChangeButton getModulesButton() {
	return modulesButton;
    }

    public void init(ApachePanelDescriptor descriptor) {
	// Sanity check -- the UI should be updated only on the event thread
	assert EventQueue.isDispatchThread();

	FileSystemView fsView;

	if (descriptor == null) {
            fsView = FileSystemView.getFileSystemView();
	} else {
	    ApacheUtil.update(descriptor.getEnabledProperty(), enabledProperty);

	    ApacheUtil.update(descriptor.getCustomEnabledProperty(),
		customEnabledProperty);

	    ApacheUtil.update(descriptor.getCustomFileProperty(),
		customFileProperty);

	    fsView = descriptor.getFileSystemView();
	}

	fileChooser.setFileSystemView(fsView);
    }

    //
    // Private methods
    //

    private JPanel createForm() {
	JCheckBox enableCheckBox = new JCheckBox(
	    Finder.getString("global.edit.enable"));
	new CheckBoxPropertySynchronizer(enabledProperty, enableCheckBox);
	ChangeIndicator enableChange = new ChangeIndicator();
	enabledProperty.addChangeListener(enableChange);

	JCheckBox customEnabledFileCheckBox = new JCheckBox(
	    Finder.getString("global.edit.customfile"));

	new CheckBoxPropertySynchronizer(customEnabledProperty,
	    customEnabledFileCheckBox);
	ChangeIndicator customEnabledChange = new ChangeIndicator();
	customEnabledProperty.addChangeListener(customEnabledChange);

	InfoLabel customEnabledHelp = new InfoLabel(
	    Finder.getString("global.edit.customfile.help"));

	BrowsableFilePanel customFilePanel = new BrowsableFilePanel();
	customFilePanel.setOpaque(false);
	fileChooser = customFilePanel.getFileChooser();

	new TextComponentPropertySynchronizer<String, JTextField>(
	    customFileProperty, customFilePanel.getField());
	ChangeIndicator customFileChange = new ChangeIndicator();
	customFileProperty.addChangeListener(customFileChange);

	GUIUtil.setEnableStateOnSelect(
	    customEnabledFileCheckBox, true, true, customFilePanel);

	mimeTypesButton = new ChangeButton(Finder.getString(
	    "global.edit.mimetypes"));
	modulesButton = new ChangeButton(Finder.getString(
	    "global.edit.modules"));

	int bGap = GUIUtil.getButtonGap();

	JPanel buttonPanel = new JPanel(new GridLayout(1, 2, bGap, 0));
	buttonPanel.setOpaque(false);
	buttonPanel.add(mimeTypesButton);
	buttonPanel.add(modulesButton);

	JPanel formPanel = new JPanel();
	formPanel.setOpaque(false);
	Form form = new Form(formPanel, VerticalAnchor.FILL);

	int hGap = GUIUtil.getHalfGap();
	int sGap = 3 * hGap;
	int indent = GUIUtil.getTextXOffset(customEnabledFileCheckBox);

	ColumnLayoutConstraint c = new ColumnLayoutConstraint(
	    HorizontalAnchor.FILL, hGap);

	RowLayoutConstraint r = new RowLayoutConstraint(
	    VerticalAnchor.CENTER, hGap);
	r.setLayoutIfInvisible(true);

	form.addRow(HorizontalAnchor.LEFT, c);
	form.add(enableCheckBox, r);
	form.add(enableChange, r);

	form.addRow(HorizontalAnchor.LEFT, c.clone().setGap(sGap));
	form.add(customEnabledFileCheckBox, r);
	form.add(customEnabledHelp, r);
	form.add(customEnabledChange, r);

	form.addRow(HorizontalAnchor.LEFT, c);
	form.add(customFilePanel, r.clone().setGap(indent).
	    setIgnoreFirstGap(false));
	form.add(customFileChange, r);

	form.addRow(HorizontalAnchor.FILL, c.setGap(sGap).setWeight(1).
	    setVerticalAnchor(VerticalAnchor.BOTTOM));

	form.add(buttonPanel, r.clone().setWeight(1).setHorizontalAnchor(
	    HorizontalAnchor.RIGHT));

	return formPanel;
    }
}
