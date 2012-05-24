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

import java.awt.Component;
import java.util.NoSuchElementException;
import javax.swing.*;
import com.oracle.solaris.vp.util.misc.Stackable;
import com.oracle.solaris.vp.util.swing.glass.BlockingGlassPane;

@SuppressWarnings({"serial"})
public class OverlayStackPanel extends JPanel implements Stackable<Component> {
    //
    // Constructors
    //

    public OverlayStackPanel() {
	setLayout(new OverlayLayout(this));
	setOpaque(false);
    }

    //
    // JComponent methods
    //

    @Override
    public boolean isOptimizedDrawingEnabled() {
	return getComponents().length <= 1;
    }

    //
    // Stackable methods
    //

    /**
     * Removes all components from this {@code OverlayStackPanel}.
     */
    @Override
    public void clear() {
	removeAll();
    }

    @Override
    public int getCount() {
	return getComponentCount();
    }

    /**
     * Returns the top-most {@code Component} from this {@code
     * OverlayStackPanel}, or {@code null} if there are no {@code
     * Component}s in this {@code OverlayStackPanel}
     */
    @Override
    public Component peek() {
	try {
	    return peekOrErr();
	} catch (NoSuchElementException e) {
	    return null;
	}
    }

    /**
     * Returns the top-most {@code Component} from this {@code
     * OverlayStackPanel}.
     *
     * @exception   NoSuchElementException
     *		    if there are no {@code Component}s in this {@code
     *		    OverlayStackPanel}
     */
    @Override
    public Component peekOrErr() {
	try {
	    return getComponent(0);
	} catch (IndexOutOfBoundsException e) {
	    throw new NoSuchElementException();
	}
    }

    @Override
    public Component peekOrErr(int n) {
	return getComponent(n);
    }

    /**
     * Removes the top-most {@code Component} from this {@code
     * OverlayStackPanel}.
     *
     * @return	    the removed {@code Component}
     *
     * @exception   NoSuchElementException
     *		    if there are no {@code Component}s in this {@code
     *		    OverlayStackPanel}
     */
    @Override
    public Component pop() {
	Component c = peekOrErr();

	BlockingGlassPane.removeConsumeEventListeners(c);

	try {
	    remove(0);
	} catch (IndexOutOfBoundsException e) {
	    throw new NoSuchElementException();
	}

	revalidate();
	repaint();
	return c;
    }

    /**
     * Adds the given {@code Component} to the top of the {@code Component}
     * stack.
     */
    @Override
    public void push(Component c) {
	BlockingGlassPane.addConsumeEventListeners(c);
	add(c, 0);
	revalidate();
	repaint();
    }
}
