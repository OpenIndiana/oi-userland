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

package com.oracle.solaris.vp.panel.swing.view;

import javax.swing.JPanel;
import com.oracle.solaris.vp.panel.common.control.Navigator;
import com.oracle.solaris.vp.util.swing.GUIUtil;
import com.oracle.solaris.vp.util.swing.layout.*;

@SuppressWarnings({"serial"})
public class NavBar extends JPanel {
    //
    // Instance data
    //

    private AddressPanel addrPanel;
    private NavButtonPanel buttonPanel;

    //
    // Constructors
    //

    public NavBar() {
	addrPanel = new AddressPanel();
	buttonPanel = new NavButtonPanel();

	RowLayout layout = new RowLayout(HorizontalAnchor.FILL);

	int gap = GUIUtil.getHalfGap();

	RowLayoutConstraint r =
	    new RowLayoutConstraint(VerticalAnchor.CENTER, gap);

	layout.setDefaultConstraint(r);

	setLayout(layout);
	add(buttonPanel, r);
	add(addrPanel, r.setWeight(1));
    }

    public NavBar(Navigator navigator) {
	this();
	setNavigator(navigator);
    }

    //
    // NavBar methods
    //

    public AddressPanel getAddressPanel() {
	return addrPanel;
    }

    public NavButtonPanel getButtonPanel() {
	return buttonPanel;
    }

    public void setNavigator(Navigator navigator) {
	addrPanel.setNavigator(navigator);
	buttonPanel.setNavigator(navigator);
    }
}
