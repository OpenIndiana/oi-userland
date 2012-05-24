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

package com.oracle.solaris.vp.panel.swing.view;

import java.awt.*;
import java.util.Properties;
import javax.swing.*;
import javax.swing.border.Border;
import com.oracle.solaris.vp.panel.common.control.Navigator;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.swing.*;
import com.oracle.solaris.vp.util.swing.layout.*;

@SuppressWarnings({"serial"})
public class PanelFrame extends ExtFrame {
    //
    // Static data
    //

    public static final int HEALTH_ICON_SIZE = 16;

    //
    // Instance data
    //

    private NavBar navBar;
    private ReplacingStackPanel mainPanel;
    private AuthPanel authPanel;
    private JLabel statusLabel;
    private JLabel statusTextLabel;

    //
    // Constructors
    //

    public PanelFrame(Properties hints, Navigator navigator) {
	JPanel header = createHeader();

	// Prevent resizing below preferred size
	getRootPane().setAutoMinSizeEnabled(true);

	mainPanel = new ReplacingStackPanel();
	mainPanel.setOpaque(false);

	JPanel top = new JPanel(new BorderLayout());
	top.setOpaque(false);

	if (hints.getProperty("vpanels.ui.noheader") == null) {
	    top.add(header, BorderLayout.NORTH);
	}

	if (hints.getProperty("vpanels.ui.navbar") != null) {
	    createNavBar(navigator);
	    top.add(navBar, BorderLayout.CENTER);
	}

	JPanel panel = new JPanel(new BorderLayout());
	panel.setOpaque(false);

	if (top.getComponentCount() != 0) {
            top.setBorder(new ClippedBorder(GUIUtil.getEmptyBorder(), true,
		true, false, true));
	    panel.add(top, BorderLayout.NORTH);
	}

	panel.add(mainPanel, BorderLayout.CENTER);

	if (hints.getProperty("vpanels.ui.undecorated") != null) {
	    setUndecorated(true);
	    Border line = BorderFactory.createLineBorder(Color.black, 1);
	    panel.setBorder(line);
	}

	Container contentPane = getContentPane();
	contentPane.setLayout(new BorderLayout());
	contentPane.add(panel, BorderLayout.CENTER);

	pack();

	setDefaultCloseOperation(WindowConstants.DO_NOTHING_ON_CLOSE);
	setInitialFocus(mainPanel);
    }

    //
    // PanelFrame methods
    //

    public AuthPanel getAuthPanel() {
	return authPanel;
    }

    public ReplacingStackPanel getMainPanel() {
	return mainPanel;
    }

    protected NavBar getNavBar() {
	return navBar;
    }

    public void setHealth(Health health) {
	if (health == null) {
	    health = Health.HEALTHY;
	}

	Icon icon = health.getIcon(HEALTH_ICON_SIZE);
	String toolTip = Finder.getString("app.status.tooltip." +
	    health.toString().toLowerCase());

	statusLabel.setIcon(icon);
	statusLabel.setToolTipText(toolTip);
    }

    public void setStatusText(String text) {
	if (text != null) {
	    text = Finder.getString("app.status", text);
	}
	statusTextLabel.setText(text);
    }

    //
    // Private methods
    //

    private JPanel createHeader() {
	statusLabel = new JLabel();
	statusTextLabel = new JLabel();

	authPanel = new AuthPanel();
	RowLayout layout = new RowLayout(HorizontalAnchor.FILL);

	JPanel row = new JPanel(layout);
	row.setOpaque(false);

	int hGap = GUIUtil.getHalfGap();
	int gap = GUIUtil.getGap();

	RowLayoutConstraint r = new RowLayoutConstraint(
	    VerticalAnchor.CENTER, hGap);

	row.add(statusLabel, r);
	row.add(statusTextLabel, r);
	row.add(authPanel, r.setWeight(1).setHorizontalAnchor(
	    HorizontalAnchor.RIGHT));

	return row;
    }

    private void createNavBar(Navigator navigator) {
	navBar = new NavBar(navigator);

	// Let the main part of the window drive the size of the nav bar
	AddressPanel addrPanel = navBar.getAddressPanel();
	Dimension d = addrPanel.getPreferredSize();
	d.width = 0;
	addrPanel.setPreferredSize(d);
    }
}
