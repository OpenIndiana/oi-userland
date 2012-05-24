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

package com.oracle.solaris.vp.panel.common;

import java.beans.*;
import java.util.*;
import javax.swing.event.*;

/**
 * The {@code LoginHistory} interface defines common login history
 * functionality.
 */
public interface LoginHistory {
    /**
     * Clears login history.
     */
    public void clearLogins();

    /**
     * Gets a list of {@code LoginInfo} objects.
     */
    public List<LoginInfo> getLogins();

    /**
     * Gets a list of {@code LoginInfo} objects.
     *
     * @param size The number of most recently used {@code LoginInfo} objects
     * to return.
     */
    public List<LoginInfo> getLogins(int size);

    /**
     * Adds a {@code ChangeListener} to be notified upon changes in state.
     *
     * @param listener The {@code ChangeListener} to add.
     */
    public void addChangeListener(ChangeListener listener);

    /**
     * Removes a {@code ChangeListener} from notification.
     *
     * @param listener The {@code ChangeListener} to remove.
     */
    public void removeChangeListener(ChangeListener listener);
}
