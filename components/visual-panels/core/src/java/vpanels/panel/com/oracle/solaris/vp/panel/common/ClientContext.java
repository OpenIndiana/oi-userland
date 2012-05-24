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

package com.oracle.solaris.vp.panel.common;

import java.util.Properties;
import javax.help.HelpBroker;
import com.oracle.solaris.vp.panel.common.action.*;
import com.oracle.solaris.vp.panel.common.control.Navigator;
import com.oracle.solaris.vp.panel.common.view.HasBusyIndicator;

public interface ClientContext extends HasBusyIndicator {
    //
    // ClientContext methods
    //

    /**
     * Adds a {@link ConnectionListener} to be notified of any {@link
     * ConnectionEvent}s on the client.
     */
    void addConnectionListener(ConnectionListener listener);

    /**
     * Closes this instance of the client, subject to arbitrary conditions.
     * Note that this may not necessarily close all instances, or stop the JVM.
     *
     * @param	    isCancel
     *		    {@code true} if this instance is being stopped as part
     *		    of a {@code cancel} operation, {@code false} otherwise
     *
     * @exception   ActionAbortedException
     *		    if the close operation could not or should not complete
     */
    void closeInstance(boolean isCancel) throws ActionAbortedException;

    /**
     * Gets the {@link ConnectionInfo} for the client.
     */
    ConnectionInfo getConnectionInfo();

    /**
     * Gets a handle to the help subsystem used by the client.
     */
    HelpBroker getHelpBroker();

    /**
     * Gets the navigator for this instance.
     */
    Navigator getNavigator();

    /**
     * Gets any runtime properties that provide hints to execution.
     */
    Properties getRuntimeHints();

    /**
     * Request that the client establish or re-use a connection matching the
     * criteria in the given {@code LoginRequest}, prompting the user to amend
     * any editable {@link LoginProperty}s therein.
     * <p/>
     * For security purposes, the client may choose to prompt the user to
     * confirm the connection, even if there is an open connection matching the
     * given criteria.
     * <p/>
     * If a connection is made to a different host or {@code forceNewContext} is
     * {@code true}, a new {@code ClientContext} will be created, leaving the
     * connection to this {@code ClientContext} unchanged.  The resulting new
     * {@code ClientContext} will NOT have any specific navigation path
     * pre-loaded.
     *
     * @param	    request
     *		    the {@link LoginRequest} encapsulating the preset values and
     *		    editability of each core {@link LoginProperty}, or {@code
     *		    null} to use a read-only {@code LoginRequest} based this
     *		    {@code ClientContext}'s {@link #getConnectionInfo current
     *		    connection}
     *
     * @param	    forceNewContext
     *		    {@code true} to force the creation of a new {@code
     *		    ClientContext}
     *
     * @return	    the {@link ClientContext} for the new instance, if created,
     *		    or this {@link ClientContext} otherwise
     *
     * @exception   ActionAbortedException
     *		    if the user cancels the operation
     *
     * @exception   ActionFailedException
     *		    if the given request fails
     */
    ClientContext login(LoginRequest request, boolean forceNewContext)
	throws ActionAbortedException, ActionFailedException;

    /**
     * Removes a {@link ConnectionListener} from notification.
     */
    boolean removeConnectionListener(ConnectionListener listener);

    /**
     * Displays the {@link #getHelpBroker HelpBroker}'s help.
     */
    void showHelp();

    /**
     * Gets the login history associated with connection manager.
     */
    LoginHistory getLoginHistory();
}
