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
import java.util.*;
import java.util.List;
import javax.swing.*;
import javax.swing.filechooser.FileSystemView;
import javax.swing.text.JTextComponent;
import com.oracle.solaris.vp.panel.swing.view.ChangeIndicator;
import com.oracle.solaris.vp.util.misc.ChangeableAggregator;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.misc.property.*;
import com.oracle.solaris.vp.util.swing.*;
import com.oracle.solaris.vp.util.swing.layout.*;
import com.oracle.solaris.vp.util.swing.property.*;

@SuppressWarnings({"serial"})
public class VirtualHostSSLPanel extends SettingsPanel {
    //
    // Instance data
    //

    private MutableProperty<Boolean> enabledProperty = new BooleanProperty();
    private MutableProperty<String> ipProperty = new StringProperty();
    private MutableProperty<Integer> portProperty = new IntegerProperty();
    private MutableProperty<String> certProperty = new StringProperty();
    private MutableProperty<String> keyProperty = new StringProperty();

    {
	ChangeableAggregator aggregator = getChangeableAggregator();
	aggregator.addChangeables(enabledProperty, ipProperty, portProperty,
	    certProperty, keyProperty);
    }

    private List<JFileChooser> fileChoosers = new ArrayList<JFileChooser>();

    //
    // Constructors
    //

    public VirtualHostSSLPanel() {
	JPanel form = createForm();
	setContent(form, false, false);
    }

    //
    // VirtualHostSSLPanel methods
    //

    public MutableProperty<Boolean> getEnabledProperty() {
	return enabledProperty;
    }

    public MutableProperty<String> getIpProperty() {
	return ipProperty;
    }

    public MutableProperty<Integer> getPortProperty() {
	return portProperty;
    }

    public MutableProperty<String> getCertProperty() {
	return certProperty;
    }

    public MutableProperty<String> getKeyProperty() {
	return keyProperty;
    }

    public void init(VirtualHost vHost) {
	// Sanity check -- the UI should be updated only on the event thread
	assert EventQueue.isDispatchThread();

	FileSystemView fsView;

	if (vHost == null) {
            fsView = FileSystemView.getFileSystemView();
	} else {
	    ApacheUtil.update(vHost.getSslEnabledProperty(), enabledProperty);
	    ApacheUtil.update(vHost.getSslIpProperty(), ipProperty);
	    ApacheUtil.update(vHost.getSslPortProperty(), portProperty);
	    ApacheUtil.update(vHost.getSslCertProperty(), certProperty);
	    ApacheUtil.update(vHost.getSslKeyProperty(), keyProperty);

	    fsView = vHost.getParent().getFileSystemView();
	}

	for (JFileChooser c : fileChoosers) {
	    c.setFileSystemView(fsView);
	}
    }

    //
    // Private methods
    //

    private JPanel createForm() {
	JCheckBox enabledCheckBox = new JCheckBox(
	    Finder.getString("vhost.ssl.edit.enable"));

	new CheckBoxPropertySynchronizer(enabledProperty, enabledCheckBox);
	ChangeIndicator enabledChange = new ChangeIndicator();
	enabledProperty.addChangeListener(enabledChange);

	JLabel iPLabel = new JLabel(
	    Finder.getString("vhost.ssl.edit.ip"));
	JTextField iPField = GUIUtil.createTextField();
	new TextComponentPropertySynchronizer<String, JTextComponent>(
	    ipProperty, iPField);
	ChangeIndicator iPChange = new ChangeIndicator();
	ipProperty.addChangeListener(iPChange);

	JLabel portLabel = new JLabel(
	    Finder.getString("vhost.ssl.edit.port"));

	SpinnerNumberModel portModel = new SpinnerNumberModel(0, 0,
	    Short.MAX_VALUE, 1);
	JSpinner portSpinner = new JSpinner(portModel);

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

	JLabel certLabel = new JLabel(
	    Finder.getString("vhost.ssl.edit.certificate"));

	BrowsableFilePanel certPanel = new BrowsableFilePanel();
	certPanel.setOpaque(false);
	fileChoosers.add(certPanel.getFileChooser());

	new TextComponentPropertySynchronizer<String, JTextComponent>(
	    certProperty, certPanel.getField());
	ChangeIndicator certChange = new ChangeIndicator();
	certProperty.addChangeListener(certChange);

	JLabel keyLabel = new JLabel(
	    Finder.getString("vhost.ssl.edit.key"));

	BrowsableFilePanel keyPanel = new BrowsableFilePanel();
	keyPanel.setOpaque(false);
	fileChoosers.add(keyPanel.getFileChooser());

	new TextComponentPropertySynchronizer<String, JTextComponent>(
	    keyProperty, keyPanel.getField());
	ChangeIndicator keyChange = new ChangeIndicator();
	keyProperty.addChangeListener(keyChange);

	JPanel formPanel = new JPanel();
	formPanel.setOpaque(false);

	Form form = new Form(formPanel, VerticalAnchor.TOP);

	int hGap = GUIUtil.getHalfGap();
	int sGap = 3 * hGap;
	int indent = GUIUtil.getTextXOffset(enabledCheckBox);

	ColumnLayoutConstraint c = new ColumnLayoutConstraint(
	    HorizontalAnchor.FILL, hGap);

	RowLayoutConstraint r = new RowLayoutConstraint(
	    VerticalAnchor.CENTER, hGap);

	HasAnchors a = new SimpleHasAnchors(
	    HorizontalAnchor.LEFT, VerticalAnchor.CENTER);

	form.addRow(HorizontalAnchor.LEFT, c);
	form.add(enabledCheckBox, r);
	form.add(enabledChange, r);

	form.addTable(2, hGap, hGap, HorizontalAnchor.LEFT, c.setGap(sGap));
	form.add(iPLabel, a);
	form.add(getRow(hGap, iPField, iPChange), a);
	form.add(portLabel, a);
	form.add(getRow(hGap, portSpinner, portChange), a);
	form.add(certLabel, a);
	form.add(getRow(hGap, certPanel, certChange), a);
	form.add(keyLabel, a);
	form.add(getRow(hGap, keyPanel, keyChange), a);

	return formPanel;
    }

    //
    // Private methods
    //

    private JPanel getRow(int gap, Component comp1, Component comp2) {
	JPanel panel = new JPanel(new BorderLayout(gap, 0));
	panel.setOpaque(false);

	panel.add(comp1, BorderLayout.CENTER);
	panel.add(comp2, BorderLayout.EAST);

	return panel;
    }
}
