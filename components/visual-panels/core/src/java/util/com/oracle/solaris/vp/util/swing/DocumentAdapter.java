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

import javax.swing.event.*;

/**
 * The {@code DocumentAdapter} class is a default implementation of the
 * {@code DocumentListener} interface; each method in that interface calls the
 * {@link #docUpdate} method, which, by default, does nothing.
 */
public class DocumentAdapter implements DocumentListener {
    //
    // DocumentListener methods
    //

    @Override
    public void insertUpdate(DocumentEvent e) {
	docUpdate(e);
    }

    @Override
    public void removeUpdate(DocumentEvent e) {
	docUpdate(e);
    }

    @Override
    public void changedUpdate(DocumentEvent e) {
	docUpdate(e);
    }

    //
    // DocumentAdapter methods
    //

    /**
     * Called by {@link #insertUpdate}, {@link #removeUpdate}, and {@link
     * #changedUpdate}.
     * <p/>
     * This default implementation does nothing.
     */
    public void docUpdate(DocumentEvent e) {
    }
}
