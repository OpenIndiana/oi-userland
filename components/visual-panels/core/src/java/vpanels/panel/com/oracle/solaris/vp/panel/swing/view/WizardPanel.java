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
import com.oracle.solaris.vp.util.misc.Stackable;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.swing.*;
import com.oracle.solaris.vp.util.swing.layout.*;

public class WizardPanel extends JPanel {
    //
    // Instance data
    //

    private WizardStepSequence sequence;
    private WizardStepPanel stepPanel;
    private SettingsPanel settingsPanel;
    private Stackable<Component> stack;

    private ActionListener cancelListener =
	new ActionListener() {
	    @Override
	    public void actionPerformed(ActionEvent e) {
		sequence.cancelWizard();
	    }
	};

    private ActionListener prevListener =
	new ActionListener() {
	    @Override
	    public void actionPerformed(ActionEvent e) {
		int selected = sequence.getSelectedIndex();
		sequence.goToStep(selected - 1);
	    }
	};

    private ActionListener forwardListener =
	new ActionListener() {
	    @Override
	    public void actionPerformed(ActionEvent e) {
		int selected = sequence.getSelectedIndex();
		sequence.goToStep(selected + 1);
	    }
	};

    //
    // Constructors
    //

    public WizardPanel(WizardStepSequence sequence) {
	this.sequence = sequence;

	Spacer spacer = new Spacer() {
	    @Override
	    public Dimension getPreferredSize() {
		Dimension d = settingsPanel.getTitlePane().getPreferredSize();
		d.height += GUIUtil.getGap();
		d.width = 0;
		return d;
	    }
	};

	stepPanel = new WizardStepPanel(sequence);

	JPanel leftPanel = new JPanel();
	leftPanel.setLayout(new BorderLayout());
	leftPanel.add(spacer, BorderLayout.NORTH);
	leftPanel.add(stepPanel, BorderLayout.CENTER);

	ReplacingStackPanel stack = new ReplacingStackPanel();
	this.stack = stack;

	settingsPanel = new SettingsPanel();
	settingsPanel.setContent(stack, false, false);

	JLabel titleLabel = settingsPanel.getTitleLabel();
	titleLabel.setForeground(WizardStepPanel.COLOR_ACTIVE);

	SettingsButtonBar bBar = settingsPanel.getButtonBar();
	bBar.getCancelButton().addActionListener(cancelListener);
	bBar.getBackButton().addActionListener(prevListener);

	AbstractButton forward = bBar.getForwardButton();
	forward.addActionListener(forwardListener);

	RowLayout layout = new RowLayout(HorizontalAnchor.FILL);
	RowLayoutConstraint r = new RowLayoutConstraint(VerticalAnchor.FILL,
	    GUIUtil.getGap());

	setLayout(layout);
	add(leftPanel, r);
	add(new JSeparator(SwingConstants.VERTICAL), r);
	add(settingsPanel, r.setWeight(1));

	sequence.addChangeListener(
	    new ChangeListener() {
		@Override
		public void stateChanged(ChangeEvent e) {
		    updateButtons();
		    updateTitle();
		}
	    });
    }

    //
    // WizardPanel methods
    //

    public Stackable<Component> getComponentStack() {
	return stack;
    }

    public String getNextButtonText() {
	int selected = sequence.getSelectedIndex();
	List<Navigable> steps = sequence.getSteps();

	return Finder.getString(selected == steps.size() - 1 ?
	    "buttons.finish.label" : "buttons.forward.label");
    }

    public SettingsPanel getSettingsPanel() {
	return settingsPanel;
    }

    public WizardStepPanel getWizardStepPanel() {
	return stepPanel;
    }

    public WizardStepSequence getWizardStepSequence() {
	return sequence;
    }

    //
    // Private methods
    //

    private void updateButtons() {
	int selected = sequence.getSelectedIndex();
	SettingsButtonBar bBar = settingsPanel.getButtonBar();
	bBar.getBackButton().setEnabled(selected > 0);
	bBar.getForwardButton().setText(getNextButtonText());
    }

    private void updateTitle() {
	String text = null;

	int selected = sequence.getSelectedIndex();
	try {
	    text = sequence.getSteps().get(selected).getName();
	} catch (IndexOutOfBoundsException e) {
	}

	settingsPanel.getTitleLabel().setText(text);
    }
}
