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
import java.awt.event.*;
import java.util.List;
import javax.swing.*;
import javax.swing.event.*;
import com.oracle.solaris.vp.panel.common.control.Navigable;
import com.oracle.solaris.vp.panel.swing.control.WizardStepSequence;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.swing.*;
import com.oracle.solaris.vp.util.swing.layout.*;

public class WizardStepPanel extends JPanel {
    //
    // Static data
    //

    public static final Color COLOR_ACTIVE = new Color(0x3E, 0x62, 0x7C);
    public static final Color COLOR_INACTIVE = new Color(0x56, 0x56, 0x56);

    //
    // Instance data
    //

    private WizardStepSequence sequence;
    private boolean numbered;
    private JPanel stepList;
    private Form form;
    private JPanel bottomPanel;

    //
    // Constructors
    //

    public WizardStepPanel(WizardStepSequence sequence) {
	this.sequence = sequence;

	stepList = new JPanel();
	form = new Form(stepList, VerticalAnchor.TOP);

	bottomPanel = new JPanel(new BorderLayout());
	bottomPanel.setVisible(false);

	ColumnLayout layout = new ColumnLayout(VerticalAnchor.FILL);
	setLayout(layout);

	int gap = GUIUtil.getHalfGap();

	ColumnLayoutConstraint c = new ColumnLayoutConstraint(
	    HorizontalAnchor.CENTER, gap);

	add(stepList, c);
	add(bottomPanel, c.setWeight(1).setVerticalAnchor(
	    VerticalAnchor.BOTTOM));

	sequence.addChangeListener(
	    new ChangeListener() {
		@Override
		public void stateChanged(ChangeEvent e) {
		    refresh();
		}
	    });
    }

    //
    // WizardStepPanel methods
    //

    protected Component createComponent(List<Navigable> steps, final int index,
	int selected) {

	HyperlinkLabel link = new HyperlinkLabel();
	if (index < selected) {
	    link.addActionListener(
		new ActionListener() {
		    @Override
		    public void actionPerformed(ActionEvent e) {
			sequence.goToStep(index);
		    }
		});
	} else {
	    link.setActive(false);
	}

	String text = steps.get(index).getName();
	if (numbered) {
	    text = Finder.getString("wizard.step.numbered", index + 1, text);
	}

	link.setText(text);
	link.setFont(link.getFont().deriveFont(Font.BOLD));
	link.setColor(index == selected ? COLOR_ACTIVE : COLOR_INACTIVE);

	return link;
    }

    protected Component createIndicator(List<Navigable> steps, int index,
	int selected) {

	String text = index == selected ? "*" : "";
	JLabel label = new JLabel(text);
	label.setFont(label.getFont().deriveFont(Font.BOLD));
	label.setForeground(index == selected ? COLOR_ACTIVE : COLOR_INACTIVE);

	return label;
    }

    /**
     * Gets a panel that sits at the bottom of this {@code WizardStepPanel}.
     * The returned panel is initially invisible with a {@code BorderLayout}.
     */
    public JPanel getBottomPanel() {
	return bottomPanel;
    }

    public boolean getNumbered() {
	return numbered;
    }

    public WizardStepSequence getWizardStepSequence() {
	return sequence;
    }

    public void refresh() {
	stepList.removeAll();

	ColumnLayoutConstraint c = new ColumnLayoutConstraint(
	    HorizontalAnchor.CENTER);

	int gap = GUIUtil.getHalfGap();
	form.addTable(2, gap, gap, HorizontalAnchor.CENTER, c);

	SimpleHasAnchors compAnchor = new SimpleHasAnchors(
	    HorizontalAnchor.LEFT, VerticalAnchor.CENTER);

	SimpleHasAnchors indiAnchor = new SimpleHasAnchors(
	    HorizontalAnchor.RIGHT, VerticalAnchor.CENTER);

	int selected = sequence.getSelectedIndex();
	List<Navigable> steps = sequence.getSteps();

	for (int i = 0, n = steps.size(); i < n; i++) {
	    Component comp = createComponent(steps, i, selected);
	    if (comp != null) {
		Component indicator = createIndicator(steps, i, selected);
		form.add(indicator, indiAnchor);
		form.add(comp, compAnchor);
	    }
	}
    }

    public void setNumbered(boolean numbered) {
	this.numbered = numbered;
    }
}
