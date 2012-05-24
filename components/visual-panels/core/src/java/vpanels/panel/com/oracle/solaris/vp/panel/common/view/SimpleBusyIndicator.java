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

package com.oracle.solaris.vp.panel.common.view;

import javax.swing.Action;

public class SimpleBusyIndicator implements BusyIndicator {
    //
    // Instance data
    //

    private int delay;
    private String message;
    private boolean displayed;
    private Action[] actions;

    //
    // BusyIndicator methods
    //

    @Override
    public Action[] getActions() {
	return actions;
    }

    @Override
    public int getDelay() {
	return delay;
    }

    @Override
    public String getMessage() {
	return message;
    }

    @Override
    public boolean isBusyIndicatorDisplayed() {
	return displayed;
    }

    @Override
    public void setActions(Action... actions) {
	this.actions = actions;
    }

    @Override
    public void setDelay(int delay) {
	this.delay = delay;
    }

    @Override
    public void setBusyIndicatorDisplayed(boolean displayed) {
	this.displayed = displayed;
    }

    @Override
    public void setMessage(String message) {
	this.message = message;
    }
}
