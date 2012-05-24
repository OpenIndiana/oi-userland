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

package com.oracle.solaris.vp.panels.time.client.swing;

import java.awt.EventQueue;
import javax.swing.*;
import com.oracle.solaris.vp.panel.common.model.View;
import com.oracle.solaris.vp.panel.swing.view.ChangeIndicator;
import com.oracle.solaris.vp.panels.time.ServerInfo;
import com.oracle.solaris.vp.util.misc.ChangeableAggregator;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.misc.property.*;
import com.oracle.solaris.vp.util.swing.*;
import com.oracle.solaris.vp.util.swing.layout.*;
import com.oracle.solaris.vp.util.swing.property.CheckBoxPropertySynchronizer;

@SuppressWarnings({"serial"})
public class NTPPanel extends SettingsPanel implements View<NTPModel> {
    //
    // Instance data
    //

    private MutableProperty<Boolean> enabledProperty =
	new BooleanProperty();

    private MutableProperty<ServerInfo[]> serversProperty =
	new BasicMutableProperty<ServerInfo[]>();

    {
	ChangeableAggregator aggregator = getChangeableAggregator();
	aggregator.addChangeables(enabledProperty);
	aggregator.addChangeables(serversProperty);
    }

    //
    // Constructors
    //

    public NTPPanel() {
	getHelpField().setText(Finder.getString("ntp.help"));

	JPanel form = createForm();
	setContent(form, false, false);
    }

    //
    // Private methods
    //

    private JPanel createForm() {
	JCheckBox enabledCheckBox = new JCheckBox(
	    Finder.getString("ntp.enable"));
	new CheckBoxPropertySynchronizer(enabledProperty, enabledCheckBox);
	ChangeIndicator enabledChange = new ChangeIndicator();
	enabledProperty.addChangeListener(enabledChange);

	ServersModel serversModel = new ServersModel();
	EditableTablePanel serversPanel = new EditableTablePanel(serversModel);

	ExtTable table = serversPanel.getTable();
	table.setAutoFitColumns(ExtTable.ColumnWidthPolicy.PREFERRED);
	table.setVisibleRowCount(8);

	new ServersPropertySynchronizer(serversProperty, serversModel);
	ChangeIndicator serversChange = new ChangeIndicator();
	serversProperty.addChangeListener(serversChange);

	GUIUtil.setEnableStateOnSelect(
	    enabledCheckBox, true, true, serversPanel);

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
	r.setLayoutIfInvisible(true);

	form.addRow(HorizontalAnchor.LEFT, c);
	form.add(enabledCheckBox, r);
	form.add(enabledChange, r);

	form.addRow(HorizontalAnchor.LEFT, c);
	form.add(serversPanel, r.clone().setGap(indent).
	    setIgnoreFirstGap(false));
	form.add(serversChange, r.setVerticalAnchor(VerticalAnchor.TOP));

	return formPanel;
    }

    //
    // View methods
    //

    public void modelToView(NTPModel model) {
	// Sanity check -- the UI should be updated only on the event thread
	assert EventQueue.isDispatchThread();

	enabledProperty.update(model.isEnabled(), false);
	serversProperty.update(model.getServers(), false);
    }

    public void viewToModel(NTPModel model) {
	model.setEnabled(enabledProperty.getValue());
	model.setServers(serversProperty.getValue());
    }
}
