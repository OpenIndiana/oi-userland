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

import java.util.List;
import javax.swing.*;
import com.oracle.solaris.vp.panel.swing.view.ChangeIndicator;
import com.oracle.solaris.vp.util.misc.ChangeableAggregator;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.misc.property.BasicMutableProperty;
import com.oracle.solaris.vp.util.swing.*;
import com.oracle.solaris.vp.util.swing.layout.*;

@SuppressWarnings({"serial"})
public class FirewallOpenPortsPanel extends SettingsPanel {

    //
    // Static data
    //

    private static final String TAB_TITLE =
	Finder.getString("openports.table.title");

    //
    // Instance data
    //

    private BasicMutableProperty<List<String>> pListProperty =
	new BasicMutableProperty<List<String>>();
    private OpenPortsTablePanel epanel;

    //
    // Constructors
    //

    public FirewallOpenPortsPanel() {
	epanel = new OpenPortsTablePanel();

	pListProperty = new BasicMutableProperty<List<String>>();
	new TablePanelPropertySynchronizer<String>(pListProperty, epanel);

	getHelpField().setText(Finder.getString(
	    "description.policy.openports"));

	JPanel form = createForm();
	setContent(form, false, true);
    }

    //
    // CommonEditPanel methods
    //

    protected JPanel createForm() {
	ChangeableAggregator aggregator = getChangeableAggregator();

	JLabel tabLabel = new JLabel(TAB_TITLE);

	ChangeIndicator pListChange = new ChangeIndicator();
	pListProperty.addChangeListener(pListChange);
	aggregator.addChangeables(pListProperty);

	JPanel formPanel = new JPanel();
	formPanel.setOpaque(false);
	Form form = new Form(formPanel, VerticalAnchor.FILL);

	int hGap = GUIUtil.getHalfGap();
	int sGap = 3 * hGap;

	ColumnLayoutConstraint c = new ColumnLayoutConstraint(
	    HorizontalAnchor.FILL, hGap);

	RowLayoutConstraint r = new RowLayoutConstraint(
	    VerticalAnchor.TOP, hGap);
	r.setLayoutIfInvisible(true);

	form.addRow(HorizontalAnchor.LEFT, c.clone().setGap(sGap));
	form.add(tabLabel, r);
	form.add(pListChange, r);

	form.addRow(HorizontalAnchor.LEFT, c);
	form.add(epanel, r);

	return formPanel;
    }

    public void setOpenPortListProperty(BasicMutableProperty<List<String>>
	pListProperty) {
	this.pListProperty = pListProperty;
    }

    public BasicMutableProperty<List<String>> getOpenPortsListProperty() {
	return pListProperty;
    }

    public void init(AccessPolicy p) {
	pListProperty.update(
	    ((SimpleAccessPolicy) p).getSavedOpenPortList(), false);
    }
}
