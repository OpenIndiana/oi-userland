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
import java.io.*;
import java.util.*;

/**
 * SMC code adapted for Visual Panels
 *
 * Description:
 * The AuthAttrObj class encapsulates the set of authorizations currently
 * set for the specified user.
 *
 * @return    none.
 */

public class AuthAttrObj extends ExtAttrObj implements Cloneable {

    // Private attributes back stopped by persistent storage
    private String authName = null;	// The authorization name
    private String [] shortDesc = null; // Short description (32 chars)
    private String [] longDesc = null;	// Long description, not localized
    private boolean visible = true;

    // The following is the list of attribute keys that are supported.

    public static final String SOLARIS_AUTH_HELP = "help";
    public static final String SOLARIS_ALL = "*";
    public static final String SOLARIS_DOT = ".";
    public static final String SOLARIS_GRANT = "grant";
    public static final String SOLARIS_SLASH = "/";


    /**
     *	Null constructor.
     *
     */
    public AuthAttrObj() {

	super();

    }

    /**
     * This constructor takes the authorization name.
     *
     */
    public AuthAttrObj(String authName) {

	super();
	this.authName = authName;

    }


    // Public methods

    /**
     * Return a copy of this object.
     *
     * @return	A new copy of this object
     *
     */
    public Object clone() {

	AuthAttrObj newobj = new AuthAttrObj(this.authName);
	newobj.setShortDesc(this.shortDesc);
	newobj.setLongDesc(this.longDesc);

	super.clone(newobj);
	return (newobj);

    }

    /**
     * Check if this instance matches another AuthAttrObj instance.
     * The other instance matches this instance if it has the
     * same authorization name.
     *
     * @param  otherAttr  The other AuthAttrObj instance
     *
     * @returnTrue if the other instance matches this one
     *
     */
    public boolean matches(AuthAttrObj otherAttr) {

	boolean bool = false;
	try {
	    if (this.authName.equals(otherAttr.getAuthName()))
		bool = true;
	} catch (Exception ex) {
	}
	return (bool);

    }

    /**
     * Return the authorization name.
     *
     * @return The authorization name
     *
     */
    public String getAuthName() {

	return (this.authName);

    }

    /**
     * Return the authorization name.
     *
     * @return The authorization name
     *
     */
    public String getName() {

	int i = authName.indexOf(SOLARIS_SLASH);
	String nameStr;

	if (i >= 0) {
	    nameStr = authName.substring(i+1);
	    if (nameStr.equals(SOLARIS_ALL)) {
		nameStr = "All";
	    }
	} else {
	    nameStr = authName;
	}

	return (nameStr);

    }

    /**
     * Set the authorization name.
     *
     * @param	The authorization name
     *
     */
    public void setAuthName(String authName) {

	this.authName = authName;

    }

    /**
     * Return a copy of this object.
     *
     * @return	A new copy of this object
     *
     */
    public String getShortDesc() {

	if (this.shortDesc == null)
	    return (null);
	else
	    return (this.shortDesc[0]);

    }

    /**
     * Return an array of short descriptions for the authorization.
     *
     * @return	An array of short descriptions
     *
     */
    public String [] getShortDescs() {

	if (this.shortDesc == null)
	    return (null);
	else
	    return (this.shortDesc);

    }

    /**
     * Set the short description for this authorizations.
     * Any existing descriptions are replaced.
     *
     * @param	The short description
     *
     */
    public void setShortDesc(String shortDesc) {

	if (this.shortDesc == null)
	    this.shortDesc = new String [1];
	this.shortDesc[0] = shortDesc;

    }

    /**
     * Set an array of short descriptions for the authorization.
     * Any existing descriptions are replaced.
     *
     * @param	The authorization name
     *
     */
    public void setShortDesc(String [] shortDesc) {

	this.shortDesc = shortDesc;

    }

    /**
     * Return a localized short description.
     *
     * @return	A localized short description
     *
     */
    public String getShortDesc(Locale locale) {

	if (this.shortDesc == null)
	    return null;
	else
	    return (this.shortDesc[0]);

    }

    /**
     * Return the relative pathname of the authorization help file
     * on the management server.
     *
     * @return	A help file pathname
     *
     */
    public String getHelpFileName() {

	Vector v = this.getAttribute(SOLARIS_AUTH_HELP);
	if ((v != null) && (v.size() > 0))
	    return ((String) v.elementAt(0));
	else
	    return (null);
    }

    /**
     * Set the relative pathname of the authorization help file
     * on the management server.  Any existing help file pathnames
     * are replaced.
     *
     * @param	A help file pathname
     *
     */
    public void setHelpFileName(String helpFile) {

	this.setAttribute(SOLARIS_AUTH_HELP, helpFile);

    }

    /**
    /**
     * Return the relative pathname of the authorization help file
     * on the management server.
    /**
     * Return the relative pathname of the authorization help file
     * on the management server.
     *
     * @return	A help file pathname
     *
     */
    public String getLongDescId() {

	Vector v = this.getAttribute(SOLARIS_AUTH_HELP);
	if ((v != null) && (v.size() > 0))
	    return ((String) v.elementAt(0));
	else
	    return (null);
    }

    /**
     * Return the relative pathnames of the authorization help files
     * on the management server.
     *
     * @return	An array of help file pathnames
     *
     *
     */
    public String [] getLongDescIds() {

	return (this.getAttributeArray(SOLARIS_AUTH_HELP));

    }

    /**
     * Return the relative pathnames of the authorization help files
     * on the management server.
     *
     * @return	A vector of help file pathnames
     *
     */
    public Vector getLongDescIdsVector() {

	return (this.getAttribute(SOLARIS_AUTH_HELP));

    }

    /**
     * Set the relative pathname of the authorization help file
     * on the management server.  Any existing help file pathnames
     * are replaced.
     *
     * @param	A help file pathname
     *
     */
    public void setLongDescId(String longDescHelp) {

	this.setAttribute(SOLARIS_AUTH_HELP, longDescHelp);

    }

    /**
     * Set the relative pathnames of the authorization help files
     * on the management server.  Any existing help file pathnames
     * are replaced.
     *
     * @param	An array of help file pathnames
     *
     */
    public void setLongDescId(String [] longDescIdArray) {

	this.setAttribute(SOLARIS_AUTH_HELP, longDescIdArray);

    }

    /**
     * Set the relative pathnames of the authorization help files
     * on the management server.  Any existing help file pathnames
     * are replaced.
     *
     * @param	A vector of help file pathnames
     *
     */
    public void setLongDescIdVector(Vector names) {

	this.setAttribute(SOLARIS_AUTH_HELP, names);

    }

    /**
     * Return a long description for the authorization.
     *
     * @return	A long description
     *
     */
    public String getLongDesc() {

	if (this.longDesc == null)
	    return null;
	else
	    return (this.longDesc[0]);

    }

    /**
     * Return an array of long descriptions for the authorization.
     *
     * @return	An array of long descriptions
     *
     */
    public String [] getLongDescs() {

	if (this.longDesc == null)
	    return null;
	else
	    return (this.longDesc);

    }

    /**
     * Return a localized long description for the authorization.
     *
     * @return	A localized long description
     *
     */
    public String getLongDesc(Locale locale) {

	if (this.longDesc == null)
	    return null;
	else
	    return (this.longDesc[0]);

    }

    /**
     * @param	A long description
     *
     */
    public void setLongDesc(String longDesc) {

	if (this.longDesc == null)
	    this.longDesc = new String[1];
	this.longDesc[0] = longDesc;

    }

    /**
     * Set the long descriptions for the authorization.
     * Any existing log descriptions are replaced.
     *
     * @param	An array of long descriptions
     *
     */
    public void setLongDesc(String [] longDesc) {

	this.longDesc = longDesc;

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
