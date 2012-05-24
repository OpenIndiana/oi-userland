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

package com.oracle.solaris.vp.panel.common.action;

import java.awt.EventQueue;
import java.util.logging.Logger;
import javax.swing.JOptionPane;
import com.oracle.solaris.vp.panel.common.*;
import com.oracle.solaris.vp.panel.common.api.auth.*;
import com.oracle.solaris.vp.util.misc.*;
import com.oracle.solaris.vp.util.misc.finder.Finder;

/**
 * The {@code DefaultStructuredAction} is a {@link StructuredAction} that uses a
 * {@link ClientContext} to handle errors and show a busy indicator while work
 * is being done.
 * <p/>
 * Subclasses should implement {@link #workBusy}, and optionally {@link
 * #getRuntimeInput} if they need to interact with the user prior to running.
 */
public class DefaultStructuredAction<P, I, O>
    extends StructuredAction<P, I, O> {

    //
    // Instance data
    //

    private ClientContext context;

    //
    // Constructors
    //

    public DefaultStructuredAction(String text, P pInput,
	ClientContext context) {

	super(text, pInput);
	this.context = context;
    }

    public DefaultStructuredAction(String text, ClientContext context) {
	this(text, null, context);
    }

    //
    // StructuredAction methods
    //

    /**
     * Calls {@link #setBusyAndWork}, then catches, displays, and re-throws any
     * resulting {@link ActionFailedException}s, and catches any resulting
     * {@link ActionUnauthorizedException}s and prompts the user to change his
     * login before retrying.
     * <p>
     * Note: See {@link #setBusyAndWork} for the note about calling this method
     * on the Swing event thread.
     *
     * @param	    pInput
     *		    see {@link StructuredAction#work}
     *
     * @param	    rtInput
     *		    see {@link StructuredAction#work}
     *
     * @return	    see {@link StructuredAction#work}
     *
     * @exception   ActionAbortedException
     *		    thrown by {@link #setBusyAndWork} or {@link
     *		    ClientContext#login}
     *
     * @exception   ActionFailedException
     *		    see {@link StructuredAction#work}
     */
    @Override
    public O work(P pInput, I rtInput) throws ActionAbortedException,
	ActionFailedException {

	LoginRequest request = null;

	while (true) {
	    try {
		if (request != null) {
		    try {
			context.login(request, false);
		    } finally {
			request = null;
		    }
		}

		return setBusyAndWork(pInput, rtInput);

	    } catch (ActionFailedException e) {
		showError(e);
		throw e;

	    } catch (ActionUnauthorizedException e) {
		String eMessage = e.getMessage();
		if (eMessage == null) {
		    eMessage = Finder.getString("error.server.permission");
		}

		String userVal = null;
		String roleVal = null;

		// Prioritize users over roles (more user-friendly)
		PrincipalHintList hints = e.getHints();
		UserHint uhint = hints.getFirstHint(UserHint.class);
		if (uhint != null) {
		    userVal = uhint.getUsername();
		} else {
		    RoleHint rhint = hints.getFirstHint(RoleHint.class);
		    if (rhint != null) {
			roleVal = rhint.getRolename();
		    }
		}

		// Log in with a different user/role and try again
		ConnectionInfo info = context.getConnectionInfo();
		LoginProperty<String> host =
		    new LoginProperty<String>(info.getHost(), false);
		LoginProperty<String> user =
		    new LoginProperty<String>(userVal != null ?
		    userVal : info.getUser(), true);
		LoginProperty<String> role =
		    new LoginProperty<String>(roleVal != null ?
		    roleVal : info.getRole(), true);

		DialogMessage message = new DialogMessage(
		    eMessage, JOptionPane.WARNING_MESSAGE);

		request = new LoginRequest(host, user, role, message);
	    }
	}
    }

    //
    // DefaultStructuredAction methods
    //

    public ClientContext getClientContext() {
	return context;
    }

    /**
     * Sets the busy state of this {@code DefaultStructuredAction}'s {@link
     * ClientContext}, then calls {@link #workBusy}, preventing the user from
     * interacting with the application until {@link #workBusy} is complete.
     * <p>
     * Note: in a Swing context, this method should not be called on the event
     * thread, since a) it calls {@link #workBusy} which may perform intensive
     * non-UI work, and b) it displays the {@link ClientContext#getBusyIndicator
     * ClientContext's busy indicator}, which may invoke UI effects that would
     * not be displayed until after this method is done (when the event thread
     * is free).
     *
     * @param	    pInput
     *		    see {@link StructuredAction#work}
     *
     * @param	    rtInput
     *		    see {@link StructuredAction#work}
     *
     * @return	    see {@link StructuredAction#work}
     *
     * @exception   ActionAbortedException
     *		    see {@link StructuredAction#work}
     *
     * @exception   ActionFailedException
     *		    see {@link StructuredAction#work}
     *
     * @exception   ActionUnauthorizedException
     *		    see {@link #workBusy}
     */
    public O setBusyAndWork(P pInput, I rtInput) throws ActionAbortedException,
	ActionFailedException, ActionUnauthorizedException {

	assert (!EventQueue.isDispatchThread());

	context.getBusyIndicator().setBusyIndicatorDisplayed(true);

	try {
	    return workBusy(pInput, rtInput);
	} finally {
	    context.getBusyIndicator().setBusyIndicatorDisplayed(false);
	}
    }

    protected void setClientContext(ClientContext context) {
	this.context = context;
    }

    /**
     * Handles {@link ActionFailedException}s thrown by {@link #work}.
     * <p/>
     * This default implementation logs ({@code Level.FINE}) the error to the
     * {@link ClientContext} log.
     */
    protected void showError(ActionFailedException e) {
	Logger.getLogger(getClass().getPackage().getName()).fine(
	    ThrowableUtil.getTrueMessage(e));
    }

    /**
     * Does the core work of this action.
     * <p>
     * This default implementation does nothing and returns {@code null}.
     *
     * @param	    pInput
     *		    see {@link StructuredAction#work}
     *
     * @param	    rtInput
     *		    see {@link StructuredAction#work}
     *
     * @return	    see {@link StructuredAction#work}
     *
     * @exception   ActionAbortedException
     *		    see {@link StructuredAction#work}
     *
     * @exception   ActionFailedException
     *		    see {@link StructuredAction#work}
     *
     * @exception   ActionUnauthorizedException
     *		    if the current user has insufficient privileges for this
     *		    operation
     */
    public O workBusy(P pInput, I rtInput)
	throws ActionAbortedException, ActionFailedException,
	ActionUnauthorizedException {

	return null;
    }
}
