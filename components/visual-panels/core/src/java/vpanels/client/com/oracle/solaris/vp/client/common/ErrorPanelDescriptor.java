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

package com.oracle.solaris.vp.client.common;

import com.oracle.solaris.vp.panel.common.api.panel.CustomPanel;
import com.oracle.solaris.vp.panel.common.model.*;

/**
 * Interface for a generic panel descriptor to be used when all custom
 * panels appropriate to a particular client fail.
 */
public interface ErrorPanelDescriptor<C extends ManagedObject>
    extends PanelDescriptor<C>
{
    /**
     * Adds a new failure to the panel.
     *
     * @param panel the {@code CustomPanel} that failed
     * @param t the cause of the failure
     */
    void addError(CustomPanel panel, Throwable t);

    /**
     * Obtains the number of errors accumulated by the
     * {@code ErrorPanelDescriptor}
     *
     * @return the number of errors accumulated
     */
    int getErrorCount();
}
