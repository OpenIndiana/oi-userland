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

package com.oracle.solaris.vp.util.swing.glass;

import java.awt.*;
import javax.swing.*;
import javax.swing.border.*;
import org.jdesktop.animation.timing.Animator;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.swing.*;

@SuppressWarnings({"serial"})
public class BusyGlassPane extends BlockingGlassPane {
    //
    // Static data
    //

    private static final int _DELAY = 2000;
    private static final String _MESSAGE = Finder.getString("busy.message");

    //
    // Instance data
    //

    private String message;
    private JProgressBar progressBar;
    private WrappingText messageLabel;
    private FadablePanel fadePanel;
    private SettingsPanel mainPanel;
    private JButton[] buttons;
    private Action[] actions;

    //
    // Constructors
    //

    public BusyGlassPane() {
	progressBar = new JProgressBar();
	progressBar.setIndeterminate(true);
	progressBar.setOpaque(false);
	progressBar.setBorderPainted(false);

	// A WrappingText must be used here instead of a FlowTextArea because
	// the latter requires a pack() before it can correctly return its
	// preferred size (thus two pack()s are needed for it to display
	// at the correct size).
	messageLabel = new WrappingText();

	createMainPanel();

	JPanel shadowPanel = new ShadowPanel();
	shadowPanel.setOpaque(false);
	shadowPanel.setLayout(new BorderLayout());
	shadowPanel.add(mainPanel, BorderLayout.CENTER);
	int gap = GUIUtil.getGap();
	Border border = BorderFactory.createEmptyBorder(gap, gap, gap, gap);
	shadowPanel.setBorder(border);

	fadePanel = new FadablePanel(shadowPanel);
	fadePanel.setSyncFadeWithVisibility(true);

	setLayout(new GridBagLayout());
	add(fadePanel);

	reset();
    }

    //
    // SimpleGlassPane methods
    //

    @Override
    public void componentHidden() {
	reset();
    }

    //
    // BusyGlassPane methods
    //

    public Action[] getActions() {
	return actions;
    }

    public int getDelay() {
	return fadePanel.getAnimator().getStartDelay();
    }

    public String getMessage() {
	return message;
    }

    public JProgressBar getProgressBar() {
	return progressBar;
    }

    protected void reset() {
	setActions();
	setDelay(_DELAY);
	setMessage(null);
	progressBar.setIndeterminate(true);
	fadePanel.setFaded(true, false);
    }

    public void setActions(Action... actions) {
	SettingsButtonBar buttonBar = mainPanel.getButtonBar();
	if (buttons != null) {
	    for (JButton button : buttons) {
		buttonBar.remove(button);
	    }
	}

	buttons = new JButton[actions.length];
	for (int i = 0; i < actions.length; i++) {
	    buttons[i] = new JButton(actions[i]);
	    buttonBar.add(buttons[i]);
	}

	this.actions = actions;
    }

    public void setDelay(int delay) {
	Animator animator = fadePanel.getAnimator();
	animator.stop();
	animator.setStartDelay(delay);
    }

    public void setMessage(String message) {
	this.message = message;

	String m = message == null ? _MESSAGE : message;
	messageLabel.setText(m);
	messageLabel.setPreferredWidthInColumns(25);
	messageLabel.setVisible(m != null && !m.isEmpty());
    }

    //
    // Private methods
    //

    private void createMainPanel() {
	// Override paintComponent and set non-opaque to avoid bug wherein the
	// progress bar appears well before the rest of the panel has faded in
	mainPanel = new SettingsPanel() {
	    @Override
	    public void paintComponent(Graphics g) {
		int w = getWidth();
		int h = getHeight();

		g.setColor(getBackground());
		g.fillRect(0, 0, w, h);
	    }
	};
	mainPanel.setOpaque(false);

	mainPanel.setCursor(Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR));

	Border empty = GUIUtil.getEmptyBorder();
	Color color = ColorUtil.darker(getBackground(), .5f);
	Border compound = BorderFactory.createCompoundBorder(
	    new LineBorder(color), empty);
	compound = BorderFactory.createCompoundBorder(
	    compound, new EtchedBorder());
	compound = BorderFactory.createCompoundBorder(
	    compound, empty);
	mainPanel.setBorder(compound);

	JPanel helpPane = mainPanel.getHelpPane();
	helpPane.removeAll();
	helpPane.add(progressBar, BorderLayout.CENTER);

        mainPanel.getContentPane().add(messageLabel, BorderLayout.CENTER);
    }
}
