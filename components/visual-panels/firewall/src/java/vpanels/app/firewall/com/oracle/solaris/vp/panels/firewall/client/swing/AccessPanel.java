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

import java.awt.Dimension;
import java.awt.event.*;
import java.util.*;
import javax.swing.*;
import com.oracle.solaris.vp.panels.firewall.client.swing.AccessPolicy.Type;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.swing.*;
import com.oracle.solaris.vp.util.swing.layout.*;

@SuppressWarnings({"serial"})
public class AccessPanel extends JPanel implements ItemListener {
    //
    // Static data
    //

    private static final String ALLOW_TITLE =
	Finder.getString("policy.table.title.allow");

    private static final String DENY_TITLE =
	Finder.getString("policy.table.title.deny");

    //
    // Instance data
    //

    private Map<AbstractButton, Type> map;
    private Map<AbstractButton, CollapsiblePane> bmap;
    private InfoLabel info;

    private BrowsableFilePanel customFilePanel;
    private PolicyEditPanel allowPanel;
    private PolicyEditPanel denyPanel;
    private CollapsiblePane allowCPane;
    private CollapsiblePane denyCPane;

    //
    // Constructors
    //

    public AccessPanel(boolean hasException, Type... types) {
	setOpaque(false);

	allowPanel = hasException ?
	    new PolicyEditPanel(ALLOW_TITLE, DENY_TITLE) :
	    new PolicyEditPanel(ALLOW_TITLE);

	denyPanel = hasException ?
	    new PolicyEditPanel(DENY_TITLE, ALLOW_TITLE) :
	    new PolicyEditPanel(DENY_TITLE);

	int gap = GUIUtil.getHalfGap();
	ColumnLayoutConstraint c = new ColumnLayoutConstraint(
	    HorizontalAnchor.FILL, gap);
	RowLayoutConstraint r = new RowLayoutConstraint(
	    VerticalAnchor.TOP, gap);
	r.setLayoutIfInvisible(true);

	map = new HashMap<AbstractButton, Type>();
	bmap = new HashMap<AbstractButton, CollapsiblePane>();
	Form form = new Form(this, VerticalAnchor.TOP);

	for (Type type : types) {
	    String message = Finder.getString(
		"service.objects.access.option." + type);

	    final AbstractButton button = new JRadioButton(message);
	    map.put(button, type);

	    form.addRow(HorizontalAnchor.LEFT, c);
	    form.add(button, r);

	    if (type == Type.USE_GLOBAL) {
		info = new InfoLabel("");
		form.add(info, r);
	    } else

	    if (type == Type.DENY || type == Type.ALLOW) {
		int indent = GUIUtil.getTextXOffset(button);
		form.addRow(HorizontalAnchor.LEFT, c);

		PolicyEditPanel epanel = null;
		CollapsiblePane cPane = null;
		switch (type) {
		    case ALLOW:
			epanel = allowPanel;
			allowCPane = new CollapsiblePane(epanel);
			cPane = allowCPane;
			break;

		    case DENY:
			epanel = denyPanel;
			denyCPane = new CollapsiblePane(epanel);
			cPane = denyCPane;
			break;
		}

		epanel.setOpaque(false);
		epanel.setVisibleRowCount(4);
		epanel.adjustSize();

		bmap.put(button, cPane);
		cPane.setOpaque(false);
		cPane.setCollapsed(true);

		button.addItemListener(this);
		form.add(cPane,
		    r.clone().setGap(indent).setIgnoreFirstGap(false));
	    } else

	    if (type == Type.CUSTOM) {
		int indent = GUIUtil.getTextXOffset(button);
		form.addRow(HorizontalAnchor.LEFT, c);

        	customFilePanel = new BrowsableFilePanel();
        	customFilePanel.setOpaque(false);

		GUIUtil.setEnableStateOnSelect(button, true, true,
		    customFilePanel);
		form.add(customFilePanel,
		    r.clone().setGap(indent).setIgnoreFirstGap(false));
	    }
	}
    }

    public AccessPanel(Type... types) {
	this(true, types);
    }

    //
    // ItemListener method
    //

    public void itemStateChanged(ItemEvent e) {
	JRadioButton b = (JRadioButton) e.getItem();
	CollapsiblePane cPane = bmap.get(b);
	cPane.setCollapsed(!b.isSelected());
    }

    //
    // JComponent methods
    //

    @Override
    public Dimension getPreferredSize() {
	Dimension d = super.getPreferredSize();
	if (allowCPane.isCollapsed() && denyCPane.isCollapsed()) {
	    d.height += denyCPane.getView().getPreferredSize().height;
	}
	return d;
    }

    //
    // AccessPanel methods
    //

    public InfoLabel getDefaultInfoLabel() {
	return info;
    }

    public BrowsableFilePanel getCustomFilePanel() {
	return customFilePanel;
    }

    public PolicyEditPanel getAllowPanel() {
	return allowPanel;
    }

    public PolicyEditPanel getDenyPanel() {
	return denyPanel;
    }

    public Map<AbstractButton, Type> getMap() {
	return map;
    }

    public void setPanelDescriptor(FirewallPanelDescriptor descriptor) {
	allowPanel.setPanelDescriptor(descriptor);
	denyPanel.setPanelDescriptor(descriptor);
    }
}
