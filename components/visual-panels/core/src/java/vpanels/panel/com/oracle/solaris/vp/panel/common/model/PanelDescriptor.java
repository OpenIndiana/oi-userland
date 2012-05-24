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

package com.oracle.solaris.vp.panel.common.model;

import javax.help.HelpSet;
import com.oracle.solaris.vp.panel.common.ClientContext;
import com.oracle.solaris.vp.panel.common.control.Control;

public interface PanelDescriptor<C extends ManagedObject>
    extends ManagedObject<C> {

    /**
     * Gets the {@link ClientContext} with which this {@code PanelDescriptor}
     * was initialized.
     */
    ClientContext getClientContext();

    /**
     * Gets the top-most {@code Control} that governs the flow and UI for this
     * {@code PanelDescriptor}.
     *
     * @return	    a non-{@code null} {@code Control}
     */
    Control getControl();

    /**
     * Indicates whether this {@code PanelDescriptor} is providing limited
     * functionality due to insufficient privileges.
     *
     * @return	    {@code true} if no functionality is withheld due to
     *		    insufficient privileges, {@code false} otherwise
     */
    boolean getHasFullPrivileges();

    /**
     * Gets the JavaHelp {@code HelpSet} corresponding to this panel.
     *
     * @return	    a {@code HelpSet}, or {@code null} if this panel has no
     *		    help.
     */
    HelpSet getHelpSet();
}
