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

package com.oracle.solaris.vp.util.swing;

import java.awt.*;
import java.awt.event.ActionListener;
import java.util.*;
import java.util.List;
import javax.swing.*;
import com.oracle.solaris.vp.util.misc.finder.*;

@SuppressWarnings({"serial"})
public class SettingsButtonBar extends SettingsToolBar {
    //
    // Inner classes
    //

    public class SettingsButton extends JButton {
	//
	// Constructors
	//

	public SettingsButton(String name, Icon icon) {
	    super(name, icon);
	    setVisible(false);
	}

	//
	// Component methods
	//

	@Override
	public Dimension getPreferredSize() {
	    Dimension d = new Dimension();
	    for (SettingsButton button : buttons) {
		if (button.isVisible()) {
		    Dimension pref = button.getTruePreferredSize();
		    d.height = Math.max(d.height, pref.height);
		    d.width = Math.max(d.width, pref.width);
		}
	    }
	    return d;
	}

	@Override
	public void setVisible(boolean visible) {
	    super.setVisible(visible);
	    SettingsButtonBar.this.setVisible();
	}

	//
	// AbstractButton methods
	//

	@Override
	public void addActionListener(ActionListener listener) {
	    super.addActionListener(listener);

	    if (!isVisible()) {
		setVisible(true);
	    }
	}

	//
	// SettingsButton methods
	//

	protected Dimension getTruePreferredSize() {
	    return super.getPreferredSize();
	}
    };

    private class LocalSettingsButton extends SettingsButton {
	public LocalSettingsButton(String resource, String iName, boolean force)
	{
	    super(Finder.getString(resource),
		GnomeUtil.getIcon(iName, GUIUtil.getButtonIconHeight(), force));
	    GUIUtil.adjustForMnemonic(this);
	}
    }

    //
    // Instance data
    //

    private boolean changed;
    private SettingsButton quitButton;
    private SettingsButton helpButton;
    private SettingsButton applyButton;
    private SettingsButton backButton;
    private SettingsButton forwardButton;
    private SettingsButton cancelButton;
    private SettingsButton resetButton;
    private SettingsButton okayButton;
    private SettingsButton closeButton;
    protected List<SettingsButton> buttons = new LinkedList<SettingsButton>();
    private List<SettingsButton> roButtons =
	Collections.unmodifiableList(buttons);

    //
    // Constructors
    //

    public SettingsButtonBar() {
	quitButton = new LocalSettingsButton(
	    "buttons.quit.label", "quit", true);
	buttons.add(quitButton);

	helpButton = new LocalSettingsButton(
	    "buttons.help.label", "gtk-help", true);
	buttons.add(helpButton);

	applyButton = new LocalSettingsButton(
	    "buttons.apply.label", "dialog-ok", false);
	buttons.add(applyButton);

	backButton = new LocalSettingsButton(
	    "buttons.back.label", "back", true);
	buttons.add(backButton);

	forwardButton = new LocalSettingsButton(
	    "buttons.forward.label", "forward", true);
	buttons.add(forwardButton);

	cancelButton = new LocalSettingsButton(
	    "buttons.cancel.label", "gtk-cancel", true);
	buttons.add(cancelButton);

	resetButton = new LocalSettingsButton(
	    "buttons.reset.label", "undo", true);
	buttons.add(resetButton);

	okayButton = new LocalSettingsButton(
	    "buttons.okay.label", "dialog-ok", false);
	buttons.add(okayButton);

	closeButton = new LocalSettingsButton(
	    "buttons.close.label", "dialog-ok", false);
	buttons.add(closeButton);

	int gap = GUIUtil.getButtonGap();

	add(quitButton, 0);
	add(helpButton, 1);

	int index = getSpacerIndex() + 1;
	add(applyButton, index++);
	add(cancelButton, index++);
	add(resetButton, index++);
	add(backButton, index++);
	add(forwardButton, index++);
	add(okayButton, index++);
	add(closeButton, index++);

	setBorder(null);
	setOpaque(false);
	setVisible();
    }

    //
    // SettingsToolBar methods
    //

    @Override
    protected void setVisible() {
	int index = getSpacerIndex();
	Component[] comps = getComponents();
	boolean visible = false;

	for (int i = 0; i < comps.length; i++) {
	    if (i != index && comps[i].isVisible()) {
		visible = true;
		break;
	    }
	}

	setVisible(visible);
    }

    //
    // SettingsButtonBar methods
    //

    /**
     * Gets an unmodifiable list of the buttons supported by this
     * {@code SettingsButtonBar}.
     */
    public List<SettingsButton> getButtons() {
	return roButtons;
    }

    public SettingsButton getApplyButton() {
	return applyButton;
    }

    public SettingsButton getBackButton() {
	return backButton;
    }

    public SettingsButton getCancelButton() {
	return cancelButton;
    }

    public SettingsButton getCloseButton() {
	return closeButton;
    }

    public SettingsButton getForwardButton() {
	return forwardButton;
    }

    public SettingsButton getHelpButton() {
	return helpButton;
    }

    public SettingsButton getOkayButton() {
	return okayButton;
    }

    public SettingsButton getQuitButton() {
	return quitButton;
    }

    public SettingsButton getResetButton() {
	return resetButton;
    }

    public boolean isChanged() {
	return changed;
    }

    public void setChanged(boolean changed) {
	this.changed = changed;
	getResetButton().setEnabled(changed);
	getApplyButton().setEnabled(changed);
	getOkayButton().setEnabled(changed);
    }
}
