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

package com.oracle.solaris.vp.util.swing;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.swing.layout.*;

@SuppressWarnings({"serial"})
public class DisablableTabTabbedPane extends JTabbedPane
    implements DescendantEnabler {

    //
    // Inner classes
    //

    public class TabComponent extends JPanel {
	//
	// Instance data
	//

	private Component mComponent;
	private JLabel label;
	private JCheckBox checkBox;
	private RowLayout layout;

	//
	// Constructors
	//

	public TabComponent(String title, Component mComponent) {
	    this.mComponent = mComponent;

	    setOpaque(false);

	    label = new JLabel(title);
	    checkBox = new JCheckBox();
	    checkBox.setToolTipText(Finder.getString(
		"tabbedpane.checkbox.tooltip"));

	    checkBox.addActionListener(
		new ActionListener() {
		    @Override
		    public void actionPerformed(ActionEvent e) {
			setSelectedComponent(getMainComponent());
		    }
		});

	    GUIUtil.setEnableStateOnSelect(checkBox, true, true,
		mComponent);

	    // Set label and checkbox font
	    setFont(DisablableTabTabbedPane.this.getFont());

	    layout = new RowLayout(HorizontalAnchor.FILL);
	    RowLayoutConstraint r = new RowLayoutConstraint(
		VerticalAnchor.CENTER, GUIUtil.getHalfGap());
	    r.setLayoutIfInvisible(true);
	    layout.setDefaultConstraint(r);

	    setLayout(layout);
	    add(label, r);
	    add(checkBox, r);
	}

	//
	// Component methods
	//

	@Override
	public void setFont(Font font) {
	    super.setFont(font);
	    try {
		getLabel().setFont(font);
		getCheckBox().setFont(font);
	    } catch (NullPointerException ignore) {
	    }
	}

	//
	// Container methods
	//

	@Override
	public RowLayout getLayout() {
	    return layout;
	}

	//
	// TabComponent methods
	//

	public JCheckBox getCheckBox() {
	    return checkBox;
	}

	public JLabel getLabel() {
	    return label;
	}

	public Component getMainComponent() {
	    return mComponent;
	}
    }

    //
    // Constructors
    //

    public DisablableTabTabbedPane() {
	setTabLayoutPolicy(JTabbedPane.SCROLL_TAB_LAYOUT);
    }

    //
    // Component methods
    //

    @Override
    public void setEnabled(boolean enabled) {
	super.setEnabled(enabled);

	if (!enabled) {
	    for (Component component : getComponents()) {
		GUIUtil.setEnabledRecursive(component, enabled);
	    }
	} else {
	    for (int i = 0, n = getTabCount(); i < n; i++) {
		boolean e = enabled;

		Component tComponent = getTabComponentAt(i);
		if (tComponent != null) {
		    GUIUtil.setEnabledRecursive(tComponent, enabled);
		    if (tComponent instanceof TabComponent) {
			e = ((TabComponent)tComponent).getCheckBox().
			    isSelected();
		    }
		}

		Component component = getComponentAt(i);
		if (component != null) {
		    GUIUtil.setEnabledRecursive(component, e);
		}
	    }
	}
    }

    @Override
    public void setFont(Font font) {
	super.setFont(font);

	for (int i = 0, n = getTabCount(); i < n; i++) {
	    Component tComponent = getTabComponentAt(i);
	    if (tComponent != null) {
		tComponent.setFont(font);
	    }
	}
    }

    //
    // DisablableTabTabbedPane methods
    //

    public TabComponent addDisablableTab(String title, Component component) {
	final int i = getTabCount();
	addTab(null, component);

	TabComponent tComponent = new TabComponent(title, component);
	setTabComponentAt(i, tComponent);

	return tComponent;
    }
}
