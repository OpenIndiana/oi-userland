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

package com.oracle.solaris.vp.panels.usermgr.client.swing;

import java.awt.*;
import java.util.Arrays;
import javax.swing.*;
import com.oracle.solaris.vp.panel.common.action.ActionFailedException;
import com.oracle.solaris.vp.util.misc.finder.Finder;

public class UserMgrUtils {
    //
    // Static data
    //
    private static final int VALID_UID = 100;
    private static final int VALID_HOMEDIRLEN = 2;

    public static void clearPassword(char[] password) {
	if (password != null) {
	    for (int i = 0; i < password.length; i++) {
		password[i] = 0;
	    }
	}
    }

    //
    // Validation methods
    //
    public static void validateUsername(UserMgrPanelDescriptor descriptor,
	String username) throws ActionFailedException {

	// User name must be specified
	if (username.length() == 0) {
	    throw new ActionFailedException(
		Finder.getString("usermgr.error.username.none"));
	}

	// Ensure that the username is valid
	if (!isValidLogin(username)) {
	    throw new ActionFailedException(
		Finder.getString("usermgr.error.username.bad"));
	}

	// Ensure that username does not already exist
	if (descriptor.getUserManagedObject(username) != null) {
	    throw new ActionFailedException(
		Finder.getString("usermgr.error.username.exists",
		    username));
	}
    }

    public static void validateUserDesc(String userdesc)
	throws ActionFailedException {
	// Ensure that the user description, if specified, is valid.
	if (!isValidUserDesc(userdesc)) {
	    throw new ActionFailedException(
		Finder.getString("usermgr.error.userdesc.bad"));
	}
    }

    public static void validatePassword(boolean bNewUser,
	char[] pass1, char[] pass2) throws ActionFailedException {

	// Ensure that the passwords match
	if (!Arrays.equals(pass1, pass2)) {
	    throw new ActionFailedException(
		Finder.getString("usermgr.error.pass.nomatch"));
	}
    }

    public static void validateUID(long uid)
	throws ActionFailedException {
	// Ensure that the UID is valid
	if (uid < VALID_UID) {
	    throw new ActionFailedException(
		Finder.getString("usermgr.error.uid.bad"));
	}
    }

    public static void validateHomeDir(String homedir)
	throws ActionFailedException {
	// Ensure that the homedir is valid
	if (!isValidHomeDir(homedir)) {
	    throw new ActionFailedException(
		Finder.getString("usermgr.error.homedir.bad"));
	}
    }

    //
    // Private methods
    //
    /**
     * Determines if the provided login name is valid.
     *
     * @param username the login name
     * @return {@code true} if the login name is valid, {@code false} if not
     */
    private static boolean isValidLogin(String username) {
	/*
	 * Make sure the username:
	 * - starts with a letter
	 * - consists of letters, numbers, underscores, hypens, and periods
	 * - is between 1 and 8 characters long (arbitrary)
	 */
	return (username.matches(
	    "^\\p{Alpha}[\\-\\p{Alnum}\\._]{0,7}$"));
    }

    /**
     * Determines if the provided user description (a.k.a. full name,
     * GECOS field) is valid.
     *
     * @param userdesc the user description
     * @return {@code true} if the description is valid, {@code false} if not
     */
    private static boolean isValidUserDesc(String userdesc) {
	/*
	 * The GECOS field can't contain newlines or colons, and ampersands
	 * are treated specially.
	 */
	return (userdesc.length() <= 0 || !userdesc.matches(".*[:&\\n]+.*"));
    }

    /**
     * Determines if the provided homedir is valid.
     *
     * @param homedir the home directory
     * @return {@code true} if the home directory is valid, {@code false} if not
     */
    private static boolean isValidHomeDir(String homedir) {
	/*
	 * Make sure the home directory:
	 * - starts with a / (an absolute path)
	 * - is a legal pathname
	 * Do not allow spaces (which is buggy!)
	 */
	return (homedir.length() >= VALID_HOMEDIRLEN &&
	    homedir.matches("^\\/[\\-\\p{Alnum}\\._\\/]+$"));
    }

    public static void removeIcons(JOptionPane pane) {
        Component[] comps = pane.getComponents();

	for (int i = 0; i < comps.length; i++) {
	    Component comp = comps[i];
	    if (comp instanceof JPanel) {
        	Component[] buttons = ((JPanel)comp).getComponents();
		for (int j = 0; j < buttons.length; j++) {
		    if (buttons[j] instanceof JButton) {
			((JButton)buttons[j]).setIcon(null);
		    }
		}
	    }
	}
    }
}
