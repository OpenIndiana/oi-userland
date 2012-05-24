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
import java.awt.event.*;
import javax.swing.JPanel;

/**
 * The {@code AutoHidePanel} is a {@code JPanel} whose visibility is
 * automatically set to {@code false} when it contains no visible child {@code
 * Component}s, {@code true} otherwise.
 */
@SuppressWarnings({"serial"})
public class AutoHidePanel extends JPanel {
    public static class AutoHideListener implements ContainerListener {
	//
	// Instance data
	//

	private ComponentListener CHILD_LISTENER =
	    new ComponentAdapter() {
		@Override
		public void componentHidden(ComponentEvent event) {
		    Component comp = event.getComponent();
		    setVisible(comp.getParent());
		}

		@Override
		public void componentShown(ComponentEvent event) {
		    Component comp = event.getComponent();
		    setVisible(comp.getParent());
		}
	    };

	//
	// ContainerListener methods
	//

	@Override
	public void componentAdded(ContainerEvent event) {
	    event.getChild().addComponentListener(CHILD_LISTENER);
	    setVisible(event.getContainer());
	}

	@Override
	public void componentRemoved(ContainerEvent event) {
	    event.getChild().removeComponentListener(CHILD_LISTENER);
	    setVisible(event.getContainer());
	}

	//
	// AutoHideListener methods
	//

	public void deinit(Container container) {
	    container.removeContainerListener(this);
	    for (Component comp : container.getComponents()) {
		comp.removeComponentListener(CHILD_LISTENER);
	    }
	}

	public void init(Container container) {
	    container.addContainerListener(this);
	    for (Component comp : container.getComponents()) {
		comp.addComponentListener(CHILD_LISTENER);
	    }
	    setVisible(container);
	}

	//
	// Private methods
	//

	/**
	 * Sets the visibility of the given {@code Container} based on whether
	 * it has any visible child {@code Component}s.
	 */
	private void setVisible(Container container) {
	    boolean visible = false;
	    for (Component comp : container.getComponents()) {
		if (comp.isVisible()) {
		    visible = true;
		    break;
		}
	    }
	    container.setVisible(visible);
	}
    }

    //
    // Static data
    //

    private static final AutoHideListener LISTENER = new AutoHideListener();

    //
    // Constructors
    //

    public AutoHidePanel() {
	init();
    }

    public AutoHidePanel(boolean isDoubleBuffered) {
	super(isDoubleBuffered);
	init();
    }

    public AutoHidePanel(LayoutManager layout) {
	super(layout);
	init();
    }

    public AutoHidePanel(LayoutManager layout, boolean isDoubleBuffered) {
	super(layout, isDoubleBuffered);
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
     * Add an {@link AutoHideListener} to the given {@code Container} to
     * automatically set its visibility whenever its text or icon properties
     * change.
     *
     * @return	    the added {@link AutoHideListener}
     */
    public static AutoHideListener autoHide(Container container) {
	LISTENER.init(container);
	return LISTENER;
    }
}
