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

package com.oracle.solaris.vp.panels.firewall.client.swing;

import java.awt.EventQueue;
import javax.swing.*;
import javax.swing.filechooser.FileSystemView;
import com.oracle.solaris.vp.panel.swing.view.ChangeIndicator;
import com.oracle.solaris.vp.panels.firewall.client.swing.AccessPolicy.Type;
import com.oracle.solaris.vp.util.misc.ChangeableAggregator;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.misc.property.*;
import com.oracle.solaris.vp.util.swing.*;
import com.oracle.solaris.vp.util.swing.layout.*;
import com.oracle.solaris.vp.util.swing.property.CheckBoxPropertySynchronizer;

@SuppressWarnings({"serial"})
public class FirewallSettingsPanel extends CommonEditPanel {
    //
    // Instance data
    //

    private FileSystemView fsView_;
    private MutableProperty<Boolean> enabledProperty;

    //
    // Constructors
    //

    public FirewallSettingsPanel(FileSystemView fsView, String panelDesc,
        Type... types) {
	super(false, panelDesc);
	fsView_ = fsView;
	setUpPanel(types);
    }

    public FirewallSettingsPanel(FileSystemView fsView, String panelDesc) {
	this(fsView, panelDesc, Type.DENY, Type.ALLOW, Type.NONE, Type.CUSTOM);
    }

    //
    // CommonEditPanel methods
    //

    @Override
    protected void setUpPanel(Type... types) {
	if (fsView_ == null)
	    setAccessProperty(new AccessProperty(false, types));
	else
	    setAccessProperty(new AccessProperty(types));

	JPanel form;
	if (fsView_ != null)
	    form = getDefaultForm();
	else
	    form = createForm();

	setContent(form, false, true);
    }

    //
    // FirewallSettingsPanel methods
    //

    public MutableProperty<Boolean> getEnableProperty() {
	return enabledProperty;
    }

    public JPanel getDefaultForm() {
	ChangeableAggregator aggregator = getChangeableAggregator();

	AccessProperty accessProperty = getAccessProperty();
	aggregator.addChangeables(accessProperty);

	ChangeIndicator accessChange = new ChangeIndicator();
	accessProperty.addChangeListener(accessChange);

	enabledProperty = new BooleanProperty();
	JCheckBox enableCheckBox = new JCheckBox(
	    Finder.getString("settings.objects.default.enable"));
	new CheckBoxPropertySynchronizer(enabledProperty, enableCheckBox);
	aggregator.addChangeables(enabledProperty);

	ChangeIndicator enableChange = new ChangeIndicator();
	enabledProperty.addChangeListener(enableChange);

	JPanel formPanel = new JPanel();
	formPanel.setOpaque(false);
	Form form = new Form(formPanel, VerticalAnchor.TOP);

	int gap = GUIUtil.getHalfGap();

	ColumnLayoutConstraint c = new ColumnLayoutConstraint(
	    HorizontalAnchor.FILL, gap);
	RowLayoutConstraint r = new RowLayoutConstraint(
	    VerticalAnchor.TOP, gap);
	r.setLayoutIfInvisible(true);

	form.addRow(HorizontalAnchor.LEFT, c);
	form.add(enableCheckBox, r);
	form.add(enableChange, r);

	form.addRow(HorizontalAnchor.LEFT, c);
	form.add(accessProperty.getPanel(), r.clone().setGap(0));
	form.add(accessChange, r);

        return formPanel;
    }

    public void init(FirewallPanelDescriptor desc) {
	// Sanity check -- the UI should be updated only on the event thread
	assert EventQueue.isDispatchThread();

	//
	// This is a global default panel so initialize custom file
	// as well as enabled value.
	//
	AccessPanel p = getAccessProperty().getPanel();
	p.getCustomFilePanel().getFileChooser().setFileSystemView(fsView_);

	enabledProperty.update(
	    desc.getEnabledProperty().getSavedValue(), false);
	super.init(desc.getAccessPolicy());
    }
}
