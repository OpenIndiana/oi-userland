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
import java.util.NoSuchElementException;
import javax.swing.JPanel;
import com.oracle.solaris.vp.util.misc.*;

@SuppressWarnings({"serial"})
public class ReplacingStackPanel extends JPanel implements Stackable<Component>
{
    //
    // Instance data
    //

    private StackList<Component> components = new StackList<Component>();

    //
    // Constructors
    //

    public ReplacingStackPanel() {
	super(new BorderLayout());
	setOpaque(false);
    }

    //
    // Stackable methods
    //

    /**
     * Removes all components from this {@code ReplacingStackPanel}.
     */
    @Override
    public void clear() {
	components.clear();
	removeAll();
    }

    @Override
    public int getCount() {
	return components.getCount();
    }

    /**
     * Returns the top-most {@code Component} from this {@code
     * ReplacingStackPanel}, or {@code null} if there are no {@code Component}s
     * in this {@code ReplacingStackPanel}
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
     * ReplacingStackPanel}.
     *
     * @exception   NoSuchElementException
     *		    if there are no {@code Component}s in this {@code
     *		    ReplacingStackPanel}
     */
    @Override
    public Component peekOrErr() {
	return components.peekOrErr();
    }

    @Override
    public Component peekOrErr(int n) {
	return components.peekOrErr(n);
    }

    /**
     * Removes the top-most {@code Component} from this {@code
     * ReplacingStackPanel}.
     *
     * @return	    the removed {@code Component}
     *
     * @exception   NoSuchElementException
     *		    if there are no {@code Component}s in this {@code
     *		    ReplacingStackPanel}
     */
    @Override
    public Component pop() {
	Component c = components.pop();
	removeAll();

	try {
	    add(peekOrErr(), BorderLayout.CENTER);
	} catch (NoSuchElementException ignore) {
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
	removeAll();
	add(c, BorderLayout.CENTER);
	components.push(c);
	revalidate();
	repaint();
    }
}
