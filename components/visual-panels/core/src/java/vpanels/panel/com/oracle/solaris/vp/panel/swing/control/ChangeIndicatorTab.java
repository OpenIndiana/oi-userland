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

package com.oracle.solaris.vp.panel.swing.control;

import javax.swing.*;
import com.oracle.solaris.vp.panel.swing.view.ChangeIndicator;
import com.oracle.solaris.vp.util.misc.ChangeableAggregator;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.swing.GUIUtil;
import com.oracle.solaris.vp.util.swing.layout.*;

@SuppressWarnings({"serial"})
public class ChangeIndicatorTab extends JPanel {
    //
    // Static data
    //

    private static final String TOOLTIP =
	Finder.getString("settings.changed.tab");

    //
    // Instance data
    //

    private ChangeIndicator change;
    private JLabel label;

    //
    // Constructors
    //

    public ChangeIndicatorTab(String title, JTabbedPane tabs, int index,
	ChangeableAggregator aggregator) {

	setOpaque(false);

	label = new JLabel(title);
	label.setFont(tabs.getFont());

	RowLayout layout = new RowLayout(HorizontalAnchor.FILL);
	RowLayoutConstraint r = new RowLayoutConstraint(
	    VerticalAnchor.CENTER, GUIUtil.getHalfGap());
	r.setLayoutIfInvisible(true);
	layout.setDefaultConstraint(r);

	change = new ChangeIndicator();
	change.setToolTipText(TOOLTIP);

	setLayout(layout);
	add(change, r);
	add(label, r);

	aggregator.addChangeListener(change);
	tabs.setTabComponentAt(index, this);
    }

    //
    // TabComponent methods
    //

    public ChangeIndicator getChangeIndicator() {
	return change;
    }

    public JLabel getLabel() {
	return label;
    }
}
