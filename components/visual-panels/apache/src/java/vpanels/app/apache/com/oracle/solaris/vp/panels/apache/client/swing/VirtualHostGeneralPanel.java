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

package com.oracle.solaris.vp.panels.apache.client.swing;

import java.awt.*;
import java.util.*;
import java.util.List;
import javax.swing.*;
import javax.swing.filechooser.FileSystemView;
import javax.swing.text.JTextComponent;
import com.oracle.solaris.vp.panel.common.smf.BasicSmfMutableProperty;
import com.oracle.solaris.vp.panel.swing.view.ChangeIndicator;
import com.oracle.solaris.vp.util.misc.ChangeableAggregator;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.misc.property.*;
import com.oracle.solaris.vp.util.swing.*;
import com.oracle.solaris.vp.util.swing.layout.*;
import com.oracle.solaris.vp.util.swing.property.*;

@SuppressWarnings({"serial"})
public class VirtualHostGeneralPanel extends SettingsPanel {
    //
    // Instance data
    //

    private MutableProperty<Boolean> enabledProperty = new BooleanProperty();
    private MutableProperty<Integer> portProperty = new IntegerProperty();
    private MutableProperty<String> domainProperty = new StringProperty();
    private MutableProperty<String> docRootProperty = new StringProperty();
    private MutableProperty<Boolean> serveHomeDirsProperty =
	new BooleanProperty();
    private MutableProperty<Boolean> customEnabledProperty =
	new BooleanProperty();
    private MutableProperty<String> customFileProperty = new StringProperty();

    {
	ChangeableAggregator aggregator = getChangeableAggregator();
	aggregator.addChangeables(enabledProperty, portProperty, domainProperty,
	    docRootProperty, serveHomeDirsProperty, customEnabledProperty,
	    customFileProperty);
    }

    private List<JFileChooser> fileChoosers = new ArrayList<JFileChooser>();
    private ChangeButton mimeTypesButton;
    private JSpinner portSpinner;

    //
    // Constructors
    //

    public VirtualHostGeneralPanel() {
	JPanel form = createForm();
	setContent(form, false, false);
    }

    //
    // VirtualHostGeneralPanel methods
    //

    public MutableProperty<Boolean> getEnabledProperty() {
	return enabledProperty;
    }

    public MutableProperty<Integer> getPortProperty() {
	return portProperty;
    }

    public MutableProperty<String> getDomainProperty() {
	return domainProperty;
    }

    public MutableProperty<String> getDocRootProperty() {
	return docRootProperty;
    }

    public MutableProperty<Boolean> getServeHomeDirsProperty() {
	return serveHomeDirsProperty;
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

    public void init(VirtualHost vHost) {
	// Sanity check -- the UI should be updated only on the event thread
	assert EventQueue.isDispatchThread();

	FileSystemView fsView;

	if (vHost == null) {
            fsView = FileSystemView.getFileSystemView();
	} else {
	    ApacheUtil.update(vHost.getEnabledProperty(), enabledProperty);
	    ApacheUtil.update(vHost.getPortProperty(), portProperty);
	    ApacheUtil.update(vHost.getDomainProperty(), domainProperty);
	    ApacheUtil.update(vHost.getDocRootProperty(), docRootProperty);
	    ApacheUtil.update(vHost.getServeHomeDirsProperty(),
		serveHomeDirsProperty);

	    ApacheUtil.update(vHost.getCustomEnabledProperty(),
		customEnabledProperty);

	    ApacheUtil.update(vHost.getCustomFileProperty(),
		customFileProperty);

	    fsView = vHost.getParent().getFileSystemView();

            // Enable port field.
            BasicSmfMutableProperty<Boolean> sslEnabledProperty =
                vHost.getSslEnabledProperty();

            boolean sslEnabled = sslEnabledProperty.getFirstValue();
            portSpinner.setEnabled(!sslEnabled);
	}

	for (JFileChooser c : fileChoosers) {
	    c.setFileSystemView(fsView);
	}
    }

    //
    // Private methods
    //

    private JPanel createForm() {
	int hGap = GUIUtil.getHalfGap();

	JCheckBox enableCheckBox = new JCheckBox(
	    Finder.getString("vhost.general.edit.enable"));
	new CheckBoxPropertySynchronizer(enabledProperty, enableCheckBox);
	ChangeIndicator enableChange = new ChangeIndicator();
	enabledProperty.addChangeListener(enableChange);

	JLabel portLabel = new JLabel(
	    Finder.getString("vhost.general.edit.port"));

	SpinnerNumberModel portModel = new SpinnerNumberModel(0, 0,
	    Short.MAX_VALUE, 1);
	portSpinner = new JSpinner(portModel);

	JComponent editor = portSpinner.getEditor();
	if (editor instanceof JSpinner.DefaultEditor) {
	    JTextField field = ((JSpinner.DefaultEditor)editor).getTextField();
	    field.setColumns(5);
	    field.setHorizontalAlignment(JTextField.RIGHT);
	}

	new SpinnerNumberModelPropertySynchronizer(portProperty, portModel,
	    false);
	portProperty.save();

	ChangeIndicator portChange = new ChangeIndicator();
	portProperty.addChangeListener(portChange);

        InfoLabel portHelp = new InfoLabel(
            Finder.getString("vhost.general.edit.port.help"));

	JLabel domainLabel = new JLabel(
	    Finder.getString("vhost.general.edit.domain"));
	JTextField domainField = GUIUtil.createTextField();

	new TextComponentPropertySynchronizer<String, JTextComponent>(
	    domainProperty, domainField);

	ChangeIndicator domainChange = new ChangeIndicator();
	domainProperty.addChangeListener(domainChange);

	JPanel domainPanel = new JPanel(new BorderLayout(hGap, 0));
	domainPanel.setOpaque(false);
	domainPanel.add(domainField, BorderLayout.CENTER);
	domainPanel.add(domainChange, BorderLayout.EAST);

	JLabel docRootLabel = new JLabel(
	    Finder.getString("vhost.general.edit.docroot"));

	BrowsableFilePanel docRootField = new BrowsableFilePanel();
	docRootField.setOpaque(false);
	JFileChooser chooser = docRootField.getFileChooser();
	chooser.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
	fileChoosers.add(chooser);

	new TextComponentPropertySynchronizer<String, JTextComponent>(
	    docRootProperty, docRootField.getField());

	ChangeIndicator docRootChange = new ChangeIndicator();
	docRootProperty.addChangeListener(docRootChange);

	JPanel docRootPanel = new JPanel(new BorderLayout(hGap, 0));
	docRootPanel.setOpaque(false);
	docRootPanel.add(docRootField, BorderLayout.CENTER);
	docRootPanel.add(docRootChange, BorderLayout.EAST);

	JCheckBox serveHomeDirsCheckBox = new JCheckBox(
	    Finder.getString("vhost.general.edit.homedirs"));

	new CheckBoxPropertySynchronizer(serveHomeDirsProperty,
	    serveHomeDirsCheckBox);

	ChangeIndicator serveHomeDirsChange = new ChangeIndicator();
	serveHomeDirsProperty.addChangeListener(serveHomeDirsChange);

        JCheckBox useCustomFileCheckBox = new JCheckBox(
            Finder.getString("vhost.general.edit.customfile"));

        new CheckBoxPropertySynchronizer(customEnabledProperty,
	    useCustomFileCheckBox);
        ChangeIndicator useCustomChange = new ChangeIndicator();
        customEnabledProperty.addChangeListener(useCustomChange);

        InfoLabel useCustomHelp = new InfoLabel(
            Finder.getString("vhost.general.edit.customfile.help"));

        BrowsableFilePanel customFilePanel = new BrowsableFilePanel();
        customFilePanel.setOpaque(false);
        fileChoosers.add(customFilePanel.getFileChooser());

        new TextComponentPropertySynchronizer<String, JTextComponent>(
	    customFileProperty, customFilePanel.getField());

        ChangeIndicator customFileChange = new ChangeIndicator();
        customFileProperty.addChangeListener(customFileChange);

        GUIUtil.setEnableStateOnSelect(useCustomFileCheckBox, true, true,
	    customFilePanel);

	mimeTypesButton = new ChangeButton(Finder.getString(
	    "vhost.general.edit.mimetypes"));

	JPanel formPanel = new JPanel();
	formPanel.setOpaque(false);

	Form form = new Form(formPanel, VerticalAnchor.FILL);

	int gap = GUIUtil.getGap();
	int sGap = 3 * hGap;
	int indent = GUIUtil.getTextXOffset(useCustomFileCheckBox);

	ColumnLayoutConstraint c = new ColumnLayoutConstraint(
	    HorizontalAnchor.FILL, hGap);

	RowLayoutConstraint r = new RowLayoutConstraint(
	    VerticalAnchor.CENTER, hGap);

	HasAnchors a = new SimpleHasAnchors(
	    HorizontalAnchor.LEFT, VerticalAnchor.CENTER);

	form.addRow(HorizontalAnchor.FILL, c);
	form.add(enableCheckBox, r);
	form.add(enableChange, r);
	form.add(portChange, r.clone().setWeight(1).setHorizontalAnchor(
	    HorizontalAnchor.RIGHT));
	form.add(portLabel, r);
	form.add(portSpinner, r);
	form.add(portHelp, r);

	form.addTable(2, hGap, hGap, HorizontalAnchor.LEFT,
	    c.clone().setGap(sGap));
	form.add(domainLabel, a);
	form.add(domainPanel, a);
	form.add(docRootLabel, a);
	form.add(docRootPanel, a);

	form.addRow(HorizontalAnchor.LEFT, c.clone().setGap(sGap));
	form.add(serveHomeDirsCheckBox, r);
	form.add(serveHomeDirsChange, r);
	form.addRow(HorizontalAnchor.LEFT, c);
	form.add(useCustomFileCheckBox, r);
	form.add(useCustomHelp, r);
	form.add(useCustomChange, r);
	form.addRow(HorizontalAnchor.LEFT, c);
	form.add(customFilePanel, r.clone().setGap(indent).
	    setIgnoreFirstGap(false));
	form.add(customFileChange, r);

	form.addRow(HorizontalAnchor.FILL, c.setGap(sGap).setWeight(1).
	    setVerticalAnchor(VerticalAnchor.BOTTOM));
	form.add(mimeTypesButton, r.setHorizontalAnchor(
	    HorizontalAnchor.RIGHT));

	return formPanel;
    }
}
