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

import java.awt.*;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.plaf.basic.BasicSeparatorUI;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.swing.*;
import com.oracle.solaris.vp.util.swing.layout.*;

/**
 * The {@code ObjectsToolBar} provides various user controls to the {@code
 * ObjectsPanel}.
 */
@SuppressWarnings({"serial"})
public class ObjectsToolBar extends SettingsToolBar {
    //
    // Inner classes
    //

    protected static class Separator extends JSeparator {
    //
	// Constructors
	//

	public Separator() {
	    super(SwingConstants.VERTICAL);
	    setUI(new BasicSeparatorUI());
	}

	//
	// Component methods
	//

	@Override
	public Dimension getPreferredSize() {
	    Dimension d = super.getPreferredSize();
	    d.height = 12;
	    return d;
	}
    }

    //
    // Instance data
    //

    private ComboBoxModel viewModel;
    private FilterField filterField;
    private Component viewControl;
    private boolean actionAdded = false;
    private boolean filterVisible = false;

    //
    // Constructors
    //

    public ObjectsToolBar(ComboBoxModel viewModel, Action... actions) {

	this.viewModel = viewModel;

	setOpaque(false);

	viewControl = createViewControl();
	filterField = new FilterField(15);

	RowLayoutConstraint r = getDefaultConstraint();
	r.setGap(GUIUtil.getHalfGap());

	add(viewControl, r, 0);
	addActions(actions);
	add(filterField, r);

	setViewControlVisible();
	setFilterControlVisible();
    }

    //
    // SettingsToolBar methods
    //

    @Override
    protected void setVisible() {
	setVisible(actionAdded || viewControl.isVisible() ||
	    filterField.isVisible());
    }

    //
    // ObjectsToolBar methods
    //

    public void addActions(Action... actions) {
	int sIndex = getSpacerIndex();
	int bMargin = GUIUtil.getToolBarButtonMargin();

	for (int i = 0; i < actions.length; i++) {
	    Action action = actions[i];

	    Component comp;

	    if (action == null) {
		comp = new Separator();
	    } else {
		JButton button = new JButton(action);
		GUIUtil.setHorizontalMargin(button, bMargin);

		comp = button;
	    }

	    actionAdded = true;
	    add(comp, sIndex + i);
	}
    }

    public void setFilterVisible(boolean visible) {
	filterVisible = visible;
	setFilterControlVisible();
    }


    //
    // Private methods
    //

    private Component createViewControl() {
	JComboBox viewCombo = new JComboBox(viewModel);
	viewCombo.setOpaque(false);

	viewModel.addListDataListener(
	    new ListDataListener() {
		@Override
		public void contentsChanged(ListDataEvent e) {
		    setViewControlVisible();
		}

		@Override
		public void intervalAdded(ListDataEvent e) {
		    setViewControlVisible();
		}

		@Override
		public void intervalRemoved(ListDataEvent e) {
		    setViewControlVisible();
		}
	    });

	JLabel label = new JLabel(Finder.getString(
	    "objects.header.view.label"));
	RowLayout layout = new RowLayout();
	RowLayoutConstraint r = new RowLayoutConstraint(
	    VerticalAnchor.CENTER, GUIUtil.getHalfGap());

	JPanel panel = new JPanel(layout);
	panel.setOpaque(false);
	panel.add(label, r);
	panel.add(viewCombo, r);

	return panel;
    }

    private void setFilterControlVisible() {
	filterField.setVisible(filterVisible);

	// Update overall visibility
	setVisible();
    }

    private void setViewControlVisible() {
	viewControl.setVisible(viewModel.getSize() > 1);

	// Update overall visibility
	setVisible();
    }

    public FilterField getFilterField() {
	return (filterField);
    }
}
