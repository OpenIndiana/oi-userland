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
 * Copyright (c) 2000, 2012, Oracle and/or its affiliates. All rights reserved.
 */

package com.oracle.solaris.vp.panels.usermgr.client.swing;

import java.lang.*;


/**
 * SMC code adapted for Visual Panels
 *
 * The AuthAttrModelEntry class encapsulates a single authorization right
 * header entry or grantable right entry.  This class is used to present
 * the authorization rights in the User Manager Authorizations tab dialog.
 * An array of instances of this class represent all the authorization rights
 * in the management scope currently selected for User Manager.
 * <p>
 * The instance contains the name of the authorization right or header,
 * a short description of the right used in the presentation, a reference
 * to a help file or localization resource property file and message id
 * used to present a detailed explanation of the right or set of rights,
 * a boolean grant attribute, and a boolean check attribute.
 * If the grant attribute is true, the authorization can be granted to the
 * selected user; that is, it can be selected in the presentation and checked
 * or unchecked.  If the check attribute is true, the user already has this
 * authorization granted to them.
 *
 */

public class AuthAttrModelEntry {

    // ========================================================================
    //
    // Private class attributes
    //
    // ========================================================================

    private String  name;		// Authorization name
    private String  desc;		// Authorization short description
    private String  help;		// Authorization help file or message id
    private boolean grant;		// True if right can be granted
    private boolean check;		// True if right has been granted
    private boolean header;		// True if is a header
    private boolean visible = true;	// True is visible

    // ========================================================================
    //
    // Constructors
    //
    // ========================================================================

    /**
     * This constructor creates a new authorization right model entry object
     * from an AuthAttrObj object.
     *
     * @param	authAttr    The AuthAttrObj source object.
     *
     */
    public AuthAttrModelEntry(AuthAttrObj authAttr) {

	this.name = authAttr.getAuthName();
	this.desc = authAttr.getShortDesc();
	this.help = authAttr.getLongDescId();
	this.grant = false;
	this.check = false;
	this.header = hasHeader();
    }

    /**
     * This constructor creates a new authorization right model entry object
     * from its parameters.
     *
     * @param	authName    The authorization name.
     * @param	authDesc    The authorization short description.
     * @param	authHelp    The authorization help file or long message file+id
     *
     */
    public AuthAttrModelEntry(String authName, String authDesc,
	String authHelp) {

	this.name = authName;
	this.desc = authDesc;
	this.help = authHelp;
	this.grant = false;
	this.check = false;
	this.header = hasHeader();

    }
    // ========================================================================
    //
    // Public methods
    //
    // ========================================================================

    /**
     * Return the authorizatino name.  If the name ends with a period, it is
     * an authorization set header name; otherwise, it is an authorization
     * grantable right name.
     *
     * @return	The name of the authorization
     *
     */
    public String getAuthName() {

	return (this.name);

    }

    /**
     * Return the authorization name.
     *
     * @return The authorization name
     *
     */
    public String getName() {

	int i = name.indexOf(AuthAttrObj.SOLARIS_SLASH);
	String nameStr;

	if (i >= 0) {
	    nameStr = name.substring(i+1);
	    if (nameStr.equals(AuthAttrObj.SOLARIS_ALL)) {
		nameStr = "All";
	    }
	} else {
	    nameStr = name;
	}
	return (nameStr);

    }

    /**
     * Return the short description of the authorization.  This description
     * is used in the presentation of the authorization in the User Manager
     * Rights tab dialog.
     *
     * @return	The short description of the authorization
     *
     */
    public String getDesc() {

	return (this.desc);

    }

    /**
     * Return the help file name or long description file name and message
     * identifier for the authorization.  If the value returned ends in
     * "html" or "htm", it is a help file relative path name.  Add the
     * path name to the management installation base directory path to get
     * the full path to the help file, then generate a "file" URL from this
     * path for HTML help file renderers.  If the value contains a "+"
     * character, it is a long message file relative path name and messaged
     * identifier combination.	Add the relative path to the installation
     * base directory to get the full path name to the resource bundle
     * property file.  Use the string after the plus sign as the message
     * key in that resource file.
     *
     * @return	The help description file name URL or file name and message id
     *
     */
    public String getHelp() {

	return (this.help);

    }

    /**
     * Determines if this authorization is a special authorization header entry.
     *
     * @return	True if this authorization entry is for a header entry.
     *
     */
    public boolean isHeader() {

	return (header);

    }

    /**
     * Determines if this authorization is a special authorization header entry.
     *
     * @return	True if this authorization entry is for a header entry.
     *
     */
    public boolean hasHeader() {

	return (name.endsWith(AuthAttrObj.SOLARIS_DOT));

    }

    /**
     * Determines if this authorization is a special authorization header entry.
     *
     * @return	True if this authorization entry is for a header entry.
     *
     */
    public void setHeader(boolean val) {
	header = val;
    }

    /**
     * Determines if this authorization can be granted by the administrator
     * currently running the User Manager tool.  If the administrator can
     * grant this authorization right to the selected user, a true value
     * is returned.  If the authorization is a header or cannot be granted,
     * a false value is returned.
     *
     * @return	True if the authorization can be granted
     *
     */
    public boolean canBeGranted() {

	return (this.grant);

    }

    /**
     * Determines if this authorization is currently granted to the selected
     * target user in the User Manager tool.  If the user has this authorization
     * right, a true value is returned; otherwise, a false value is returned.
     *
     * @return	True if the user is granted this authorization right
     *
     */
    public boolean isGranted() {

	return (this.check);

    }

    /**
     * Grant the authorization right to the selected target user in the
     * User Manager tool.  The caller should first test if the authorization
     * is grantable by calling the canBeGranted method.
     *
     */
    public void grant() {

	this.check = true;

    }

    /**
     * Revoke the authorization right for the selected target user in the
     * User Manager tool.  The caller should first test if the authorization
     * is revokable by calling the canBeGranted method.  The administrator
     * must be capable of granting the right in order to revoke it.
     *
     */
    public void revoke() {

	this.check = false;

    }

    /**
     * Set the ability to grant or revoke the authorization right.
     * The administrator running the User Manager tool must have the grant
     * right controlling this authorization.
     *
     */
    public void setToBeGranted() {

	this.grant = true;

    }

    public boolean hasObject() {
	if (name.indexOf(AuthAttrObj.SOLARIS_SLASH) == -1) {
	    return (false);
	} else {
	    return (true);
	}
    }

    /**
     * Set the long descriptions for the authorization.
     * Any existing log descriptions are replaced.
     *
     * @param	An array of long descriptions
     *
     */
    public boolean isVisible() {

	return (visible);
    }

    /**
     * Set the long descriptions for the authorization.
     * Any existing log descriptions are replaced.
     *
     * @param	An array of long descriptions
     *
     */
    public void setVisible(boolean visibility) {

	visible = visibility;
    }

}
