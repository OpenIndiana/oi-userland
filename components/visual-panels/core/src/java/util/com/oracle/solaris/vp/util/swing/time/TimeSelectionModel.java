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

package com.oracle.solaris.vp.util.swing.time;

import javax.swing.event.ChangeListener;

public interface TimeSelectionModel {
    /**
     * Adds a {@code ChangeListener} to be notified upon changes in the
     * selection.
     */
    void addChangeListener(ChangeListener listener);

    /**
     * Gets the selected field.
     *
     * @return	    a field constant defined by the {@code Calendar} class, or
     *		    -1 if no field is selected
     */
    int getSelectedField();

    /**
     * Removes a {@code ChangeListener} from notification.
     */
    void removeChangeListener(ChangeListener listener);

    /**
     * Sets the selected field.
     *
     * @param	    selectedField
     *		    a field constant defined by the {@code Calendar} class, or
     *		    -1 to make no field selected
     */
    void setSelectedField(int selectedField);
}
