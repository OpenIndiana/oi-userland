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

import javax.swing.JPanel;
import com.oracle.solaris.vp.panel.swing.view.ChangeIndicator;
import com.oracle.solaris.vp.panels.firewall.client.swing.AccessPolicy.Type;
import com.oracle.solaris.vp.util.misc.ChangeableAggregator;
import com.oracle.solaris.vp.util.swing.*;
import com.oracle.solaris.vp.util.swing.layout.*;

@SuppressWarnings({"serial"})
public class CommonEditPanel extends SettingsPanel {
    //
    // Instance data
    //

    private AccessProperty accessProperty;

    //
    // Constructors
    //

    public CommonEditPanel(boolean doDefault, String panelDesc) {
	getHelpField().setText(panelDesc);
	if (doDefault)
	    setUpDefaultPanel();
    }

    //
    // CommonEditPanel methods
    //

    protected JPanel createForm() {
	ChangeableAggregator aggregator = getChangeableAggregator();

	ChangeIndicator accessChange = new ChangeIndicator();
	accessProperty.addChangeListener(accessChange);
	aggregator.addChangeables(accessProperty);

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
	form.add(accessProperty.getPanel(), r);
	form.add(accessChange, r);

	return formPanel;
    }

    protected void setUpPanel(Type... types) {
	accessProperty = new AccessProperty(types);

	JPanel form = createForm();
	setContent(form, false, true);
    }

    protected void setUpDefaultPanel() {
	setUpPanel(Type.USE_GLOBAL, Type.DENY, Type.ALLOW, Type.NONE);
    }

    public void setAccessProperty(AccessProperty accessProperty) {
	this.accessProperty = accessProperty;
    }

    public AccessProperty getAccessProperty() {
	return accessProperty;
    }

    public void init(AccessPolicy policy) {
	accessProperty.update(policy, false);
    }

    public void setPanelDescriptor(FirewallPanelDescriptor descriptor) {
	accessProperty.setPanelDescriptor(descriptor);
    }
}
