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

import java.beans.*;
import javax.swing.*;

/**
 * The {@code AutoHideLabel} is a {@code JLabel} whose visibility is
 * automatically set to {@code false} when its text and icon are {@code null} or
 * empty, {@code true} otherwise.
 */
@SuppressWarnings({"serial"})
public class AutoHideLabel extends JLabel {
    public static class AutoHideListener implements PropertyChangeListener {
	//
	// PropertyChangeListener methods
	//

	@Override
	public void propertyChange(PropertyChangeEvent event) {
	    setVisible((JLabel)event.getSource());
	}

	//
	// AutoHideListener methods
	//

	public void deinit(JLabel label) {
	    label.removePropertyChangeListener("text", this);
	    label.removePropertyChangeListener("icon", this);
	}

	public void init(JLabel label) {
	    label.addPropertyChangeListener("text", this);
	    label.addPropertyChangeListener("icon", this);
	    setVisible(label);
	}

	//
	// Private methods
	//

	/**
	 * Sets the visibility of the given {@code label} based on whether it
	 * has a non-{@code null}/empty icon or text.
	 */
	private void setVisible(JLabel label) {
	    String text = label.getText();
	    label.setVisible((text != null && !text.isEmpty()) ||
		label.getIcon() != null);
	}
    }

    //
    // Static data
    //

    private static final AutoHideListener LISTENER = new AutoHideListener();

    //
    // Constructors
    //

    public AutoHideLabel() {
	init();
    }

    public AutoHideLabel(Icon icon) {
	super(icon);
	init();
    }

    public AutoHideLabel(Icon icon, int horizontalAlignment) {
	super(icon, horizontalAlignment);
	init();
    }

    public AutoHideLabel(String text) {
	super(text);
	init();
    }

    public AutoHideLabel(String text, Icon icon, int horizontalAlignment) {
	super(text, icon, horizontalAlignment);
	init();
    }

    public AutoHideLabel(String text, int horizontalAlignment) {
	super(text, horizontalAlignment);
	init();
    }

    //
    // Private methods
    //

    private void init() {
	autoHide(this);
    }

    //
    // Static methods
    //

    /**
     * Add an {@link AutoHideListener} to the given {@code JLabel} to
     * automatically set its visibility whenever its text or icon properties
     * change.
     *
     * @return	    the added {@link AutoHideListener}
     */
    public static AutoHideListener autoHide(JLabel label) {
	LISTENER.init(label);
	return LISTENER;
    }
}
