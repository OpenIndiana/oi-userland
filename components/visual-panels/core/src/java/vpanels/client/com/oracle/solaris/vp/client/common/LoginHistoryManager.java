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

package com.oracle.solaris.vp.client.common;

import java.io.*;
import java.util.*;
import java.util.logging.*;
import javax.swing.event.*;
import com.oracle.solaris.vp.panel.common.*;
import com.oracle.solaris.vp.util.misc.TextUtil;
import com.oracle.solaris.vp.util.swing.event.ChangeListeners;

public class LoginHistoryManager implements LoginHistory {
    //
    // Instance data
    //

    // Used to format logins as host:user:role
    private static final String LOGIN_DELIMITER = ":";

    // Default login history size.
    private static final int LOGIN_SIZE = 256;

    // Login history size.
    private int loginSize;

    // File used to persist login history.
    private File loginFile;

    // List used to maintain login history.
    private LinkedList<LoginInfo> logins = new LinkedList<LoginInfo>();

    // ConnectionManager used for logins.
    private ConnectionManager connManager = null;

    // login history listeners.
    private ChangeListeners listeners = new ChangeListeners();

    // ConnectionManager listener.
    private ConnectionListListener connListener =
	new ConnectionListListener() {
	    @Override
	    public void connectionRemoved(ConnectionEvent event) {
		// Nothing to do here.
	    }

	    @Override
	    public void connectionAdded(ConnectionEvent event) {
		connectionChanged(event);
	    }

	    @Override
	    public void connectionSelected(ConnectionEvent event) {
		connectionChanged(event);
	    }

	    private void connectionChanged(ConnectionEvent event) {
		LoginInfo info = (LoginInfo) event.getConnectionInfo();
		addLogin(info);
		writeLogins();
		fireStateChanged();
	    }
	};

    //
    // Constructors
    //

    /**
     * Create an instance of this class.
     *
     * @param manager The {@code ConnectionManager} associated with logins.
     * @param file The {@code File} used to persist login history.
     */
    public LoginHistoryManager(ConnectionManager manager, File file) {
	this(manager, file, LOGIN_SIZE);
    }

    /**
     * Create an instance of this class.
     *
     * @param manager The {@code ConnectionManager} associated with logins.
     * @param file The {@code File} used to persist login history.
     * @param size The size of the persisted login history.
     */
    public LoginHistoryManager(ConnectionManager manager, File file, int size) {
	loginFile = file;
	connManager = manager;
	connManager.addConnectionListListener(connListener);
	setSize(size);
	readLogins();
    }

    //
    // LoginHistory methods
    //

    @Override
    public void clearLogins() {
	logins.clear();
	loginFile.delete();
	fireStateChanged();
    }

    @Override
    public List<LoginInfo> getLogins() {
	return new ArrayList<LoginInfo>(logins);
    }

    @Override
    public List<LoginInfo> getLogins(int size) {
	List<LoginInfo> list = getLogins();
	try {
	    return list.subList(0, size);
	} catch (IndexOutOfBoundsException e) {
	    return list;
	}
    }

    @Override
    public void addChangeListener(ChangeListener listener) {
	listeners.add(listener);
    }

    @Override
    public void removeChangeListener(ChangeListener listener) {
	listeners.remove(listener);
    }

    //
    // LoginHistoryManager methods
    //

    /**
     * Get the size of persisted login history.
     */
    public int getSize() {
	return loginSize;
    }

    /**
     * Set the size of persisted login history. If size is negative, the default
     * size shall be used.
     *
     * @param size The login history size.
     */
    public void setSize(int size) {
	loginSize = (size < 0) ? LOGIN_SIZE : size;

	if (logins.size() > loginSize) {
	    for (int i = logins.size() - 1; i >= loginSize; i--) {
		logins.remove(i);
	    }
	    writeLogins();
	    fireStateChanged();
	}
    }

    //
    // Private methods
    //

    // Add logins in FIFO order.
    private void addLogin(LoginInfo info) {
	removeLogin(info);
	logins.addFirst(info);
	if (logins.size() > loginSize) {
	    logins.removeLast();
	}
    }

    // Fire property change event.
    private void fireStateChanged() {
	listeners.stateChanged(new ChangeEvent(this));
    }

    private static String nullIfEmpty(String s) {
	return s.length() > 0 ? s : null;
    }

    // Push logins in LIFO order.
    private void pushLogin(LoginInfo info) {
	removeLogin(info);
	logins.addLast(info);
	if (logins.size() > loginSize) {
	    logins.removeFirst();
	}
    }

    // Remove existing login.
    private void removeLogin(LoginInfo info) {
	for (int i = 0; i < logins.size(); i++) {
	    LoginInfo login = logins.get(i);
	    if (info.matches(login)) {
		logins.remove(i);
		return;
	    }
	}
    }

    // Read persistent login history.
    private void readLogins() {
	if (!loginFile.exists()) {
	    return;
	}

	if (!loginFile.canRead()) {
	    String message = "cannot read login history: " +
		loginFile.getAbsolutePath();
	    Logger.getLogger(getClass().getName()).log(
		Level.WARNING, message);
	    return;
	}

	try {
	    BufferedReader reader = new BufferedReader(
		new FileReader(loginFile));

	    int i = 0;
	    String line;

	    while ((line = reader.readLine()) != null && i++ < loginSize) {
		String[] fields = line.split(LOGIN_DELIMITER);

		String host = null;
		String user = null;
		String role = null;
		String zone = null;
		String zoneUser = null;
		String zoneRole = null;

		try {
		    host = nullIfEmpty(fields[0]);
		    user = nullIfEmpty(fields[1]);
		    role = nullIfEmpty(fields[2]);
		    zone = nullIfEmpty(fields[3]);
		    zoneUser = nullIfEmpty(fields[4]);
		    zoneRole = nullIfEmpty(fields[5]);
		} catch (ArrayIndexOutOfBoundsException stop) {
		}

		if (host != null && user != null) {
		    ConnectionInfo info = new ConnectionInfo(
			host, user, role, zone, zoneUser, zoneRole, null);
		    pushLogin(info);
		}
	    }
	    reader.close();
	} catch (IOException e) {
	    String message = "error reading login history";
	    Logger.getLogger(getClass().getName()).log(
		Level.WARNING, message, e);
	}
    }

    // Write persistent login history.
    private void writeLogins() {
	File loginDir = loginFile.getParentFile();

	// Ensure directory exists.
	if (!loginDir.exists() && !loginDir.mkdirs()) {
	    String message = "Cannot create login history directory: " +
		loginDir.getAbsolutePath();
	    Logger.getLogger(getClass().getName()).log(
		Level.WARNING, message);
	    return;
	}

	try {
	    File tmpFile = File.createTempFile(loginFile.getName(), ".tmp",
		loginDir);
	    PrintWriter writer = new PrintWriter(new FileWriter(tmpFile));

	    for (LoginInfo login : logins) {
                writer.println(TextUtil.join(LOGIN_DELIMITER, login.getHost(),
		    login.getUser(), login.getRole(), login.getZone(),
		    login.getZoneUser(), login.getZoneRole()));
	    }
	    tmpFile.renameTo(loginFile);
	    writer.close();
	} catch (IOException e) {
	    String message = "Cannot persist login history";
	    Logger.getLogger(getClass().getName()).log(
		Level.WARNING, message, e);
	}
    }
}
