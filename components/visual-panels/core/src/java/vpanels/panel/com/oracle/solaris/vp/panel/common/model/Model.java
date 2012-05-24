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

package com.oracle.solaris.vp.panel.common.model;

import com.oracle.solaris.vp.panel.common.action.*;

public interface Model {
    void init();

    void load() /* throws ActionFailedException, ActionUnauthorizedException */;

    void save() throws ActionFailedException, ActionUnauthorizedException;

    /**
     * Determines if the model is complete; i.e. if a view can display
     * its contents.  This should always return {@code true} after a
     * call to {@code init()} or {@code load()}.
     */
    boolean isInitialized();

    /**
     * Determines if the model is valid; i.e. if the model can be saved.
     *
     * @throws com.oracle.solaris.vp.panel.common.action.ActionFailedException
     */
    void validate() throws ActionFailedException;
}
