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

import java.awt.EventQueue;
import javax.swing.*;
import com.oracle.solaris.vp.panel.swing.view.ChangeIndicator;
import com.oracle.solaris.vp.util.misc.ChangeableAggregator;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.misc.property.*;
import com.oracle.solaris.vp.util.swing.*;
import com.oracle.solaris.vp.util.swing.layout.*;
import com.oracle.solaris.vp.util.swing.property.
    TextComponentPropertySynchronizer;

@SuppressWarnings({"serial"})
public class MimeTypePanel extends SettingsPanel {
    //
    // Instance data
    //

    private MutableProperty<String> typeProperty = new StringProperty();
    private MutableProperty<String> subtypeProperty = new StringProperty();
    private MutableProperty<String[]> extensionsProperty =
	new StringArrayProperty();

    {
	ChangeableAggregator aggregator = getChangeableAggregator();
	aggregator.addChangeables(typeProperty, subtypeProperty,
	    extensionsProperty);
    }

    //
    // Constructors
    //

    public MimeTypePanel() {
	JPanel form = createForm();
	setContent(form, false, false);
    }

    //
    // MimeTypePanel methods
    //

    public MutableProperty<String[]> getExtensionsProperty() {
	return extensionsProperty;
    }

    public MutableProperty<String> getSubtypeProperty() {
	return subtypeProperty;
    }

    public MutableProperty<String> getTypeProperty() {
	return typeProperty;
    }

    public void init(MimeType mimeType) {
	// Sanity check -- the UI should be updated only on the event thread
	assert EventQueue.isDispatchThread();

	if (mimeType != null) {
	    ApacheUtil.update(mimeType.getTypeProperty(), typeProperty);
	    ApacheUtil.update(mimeType.getSubtypeProperty(), subtypeProperty);
	    ApacheUtil.update(mimeType.getExtensionsProperty(),
		extensionsProperty);
	}
    }

    //
    // Private methods
    //

    private JPanel createForm() {
	int gap = GUIUtil.getHalfGap();

	JLabel typeLabel = new JLabel(
	    Finder.getString("mimetype.edit.type"));

	JTextField typeField = GUIUtil.createTextField();
	new TextComponentPropertySynchronizer<String, JTextField>(
	    typeProperty, typeField);
	ChangeIndicator typeChange = new ChangeIndicator();
	typeProperty.addChangeListener(typeChange);

	JLabel subtypeLabel = new JLabel(
	    Finder.getString("mimetype.edit.subtype"));

	JTextField subtypeField = GUIUtil.createTextField();
	new TextComponentPropertySynchronizer<String, JTextField>(
	    subtypeProperty, subtypeField);
	ChangeIndicator subtypeChange = new ChangeIndicator();
	subtypeProperty.addChangeListener(subtypeChange);

	JLabel extensionsLabel = new JLabel(
	    Finder.getString("mimetype.edit.extensions"));

	JTextField extensionsField = GUIUtil.createTextField();
	new TextComponentPropertySynchronizer<String[], JTextField>(
	    extensionsProperty, extensionsField);
	ChangeIndicator extensionsChange = new ChangeIndicator();
	extensionsProperty.addChangeListener(extensionsChange);

	JPanel formPanel = new JPanel();
	formPanel.setOpaque(false);
	Form form = new Form(formPanel, VerticalAnchor.TOP);

	ColumnLayoutConstraint c = new ColumnLayoutConstraint(
	    HorizontalAnchor.FILL, gap);

	HasAnchors a = new SimpleHasAnchors(
	    HorizontalAnchor.LEFT, VerticalAnchor.CENTER);

	form.addTable(3, gap, gap, HorizontalAnchor.LEFT, c);

	form.add(typeLabel, a);
	form.add(typeField, a);
	form.add(typeChange, a);

	form.add(subtypeLabel, a);
	form.add(subtypeField, a);
	form.add(subtypeChange, a);

	form.add(extensionsLabel, a);
	form.add(extensionsField, a);
	form.add(extensionsChange, a);

	return formPanel;
    }
}
