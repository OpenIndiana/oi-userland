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

import java.awt.Component;
import java.util.List;
import javax.swing.*;
import javax.swing.border.Border;
import com.oracle.solaris.vp.panel.common.control.*;
import com.oracle.solaris.vp.panel.common.model.PanelDescriptor;
import com.oracle.solaris.vp.panel.common.view.PanelIconUtil;
import com.oracle.solaris.vp.util.swing.*;

/**
 * The {@code TabbedControl} displays its child {@link Control}s as tabs within
 * a {@code JTabbedPane}.  Selection of the tabs is coordinated with navigation
 * to the child {@link Control}s, and vice-versa.  The {@code Component} for
 * each tab is determined by the child's {@link HasTabComponent#getTabComponent}
 * method, if it implements {@link HasTabComponent}, or its {@link
 * SwingControl#getComponentCreate} method, if it extends {@link SwingControl}.
 */
public class TabbedControl<P extends PanelDescriptor>
    extends SwingControl<P, JTabbedPane> {

    //
    // Inner classes
    //

    protected class NavTabSelectionModel extends DefaultSingleSelectionModel {
	//
	// SingleSelectionModel methods
	//

	@Override
	public void clearSelection() {
	    // Launch navigation on non-event thread
	    getNavigator().goToAsync(false, TabbedControl.this);
	}

	@Override
	public void setSelectedIndex(int cIndex) {
	    Navigable navigable = new SimpleNavigable(
		children.get(cIndex).getId(), null);

	    getNavigator().goToAsync(false, TabbedControl.this, navigable);
	}

	//
	// NavTabSelectionModel methods
	//

	public void setSelectedIndexDirectly(int index) {
	    super.setSelectedIndex(index);
	}
    }

    public static class TabInsetPanel extends InsetPanel {
	//
	// Constructors
	//

	public TabInsetPanel() {
	}

	public TabInsetPanel(Component comp) {
	    super(comp);
	}

	//
	// InsetPanel methods
	//

	@Override
	protected Border createOuterBorder() {
	    return new ClippedBorder(super.createOuterBorder(),
		false, true, true, true);
	}
    };

    //
    // Static data
    //

    private static final int ICON_HEIGHT_TAB = 16;

    //
    // Instance data
    //

    private NavTabSelectionModel tabSelModel;

    //
    // Constructors
    //

    public TabbedControl(String id, String name, P descriptor) {
	super(id, name, descriptor);
    }

    //
    // Control methods
    //

    @Override
    public void childStarted(Control child) {
	super.childStarted(child);

	int index = children.indexOf(child);
	if (index != -1) {
	    // Set viewable tab directly without going through the Navigator
	    tabSelModel.setSelectedIndexDirectly(index);
	}
    }

    @Override
    public Navigable[] getForwardingPath(boolean childStopped) {
	ensureChildrenCreated();

	if (children.size() > 0) {
	    // Automatically view first tab
	    return new Navigable[] {children.get(0)};
	}

	return null;
    }

    //
    // SwingControl methods
    //

    @Override
    protected JTabbedPane createComponent() {
	ensureChildrenCreated();

	JTabbedPane tabs = new JTabbedPane();
	tabs.setTabLayoutPolicy(JTabbedPane.SCROLL_TAB_LAYOUT);
	SleekTabbedPaneUI ui = new SleekTabbedPaneUI();
	tabs.setUI(ui);
	tabs.setOpaque(false);

	// Add tabs *before* wrapping the model
	for (Control child : children) {
	    Icon icon = PanelIconUtil.getIcon(child, ICON_HEIGHT_TAB, false);

	    Component comp = null;
	    if (child instanceof SwingControl) {
		comp = ((SwingControl)child).getComponentCreate();
	    }

	    Component tabComp = child instanceof HasTabComponent ?
		((HasTabComponent)child).getTabComponent() :
		(comp != null ? comp : new JLabel());

	    if (isInsettable(child)) {
		JPanel panel = new TabInsetPanel(tabComp);
		tabComp = panel;
	    }

	    tabs.addTab(child.getName(), icon, tabComp);
	}

	tabSelModel = new NavTabSelectionModel();
	tabs.setModel(tabSelModel);

	return tabs;
    }

    //
    // TabbedControl methods
    //

    /**
     * Determines whether the given child's {@code Component} should be placed
     * in a bordered inset panel within its tab.  Such a panel visually
     * delineates the tab from other parts of the UI, but may not be
     * appropriate for some {@code Component}s, such as tabs that span the full
     * width of a window.
     * </p>
     * This default implementation returns {@code true}.
     *
     * @param	    child
     *		    a child {@link Control} of this {@code TabbedControl}
     */
    protected boolean isInsettable(Control child) {
	return true;
    }
}
