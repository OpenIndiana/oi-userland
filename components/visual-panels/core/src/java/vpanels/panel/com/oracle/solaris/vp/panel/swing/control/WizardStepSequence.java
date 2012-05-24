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
 * Copyright (c) 2008, 2012, Oracle and/or its affiliates. All rights reserved.
 */

package com.oracle.solaris.vp.panel.swing.control;

import java.util.List;
import javax.swing.event.ChangeListener;
import com.oracle.solaris.vp.panel.common.control.Navigable;

/**
 * The {@code WizardStepSequence} describes the sequence of steps that a wizard
 * takes.
 */
public interface WizardStepSequence {
    /**
     * Adds a listener for changes in this {@code WizardStepSequence}.
     */
    void addChangeListener(ChangeListener l);

    /**
     * Asynchronously requests that the wizard be cancelled.
     */
    void cancelWizard();

    /**
     * Gets the index of the current step in the wizard, or -1 if the wizard is
     * not running.
     */
    int getSelectedIndex();

    /**
     * Gets the steps in the wizard, as far as can be determined.  Steps up to
     * and including the {@link #getSelectedIndex current step} have already
     * been visited.  In some wizards, the steps after the current step may not
     * be determinable until some later point (e.g. the user must make a choice
     * of some sort).  In such cases, the last element of the returned {@code
     * List} will be {@code null} to indicate an open-ended step list.
     *
     * @return	    a non-{@code null} {@code List}
     */
    List<Navigable> getSteps();

    /**
     * Asynchronously requess navigation to the given step in the wizard.
     *
     * @param	    index
     *		    an index between 0 and the {@link #getSelectedIndex
     *		    getSelectedIndex()} + 1, inclusive; if the wizard is on the
     *		    last step, an {@code index} of the latter value effectively
     *		    closes the wizard
     *
     * @exception   IndexOutOfBoundsException
     *		    if the given step index is invalid
     */
    void goToStep(int index);

    /**
     * Removes a listener for changes in this {@code WizardStepSequence}.
     */
    void removeChangeListener(ChangeListener l);
}
