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
 * Copyright (c) 1998, 2012, Oracle and/or its affiliates. All rights reserved.
 */

package com.oracle.solaris.vp.panels.usermgr.client.swing;


import java.lang.*;
import java.util.*;

/**
 * SMC code adapted for Visual Panels
 *
 * The AuthAttrMgmt class is a User Manager client object that supports
 * the data underlying the Authorizations tab dialog panel.  This class
 * will remotely access the authorizations table for the management scope
 * that User Manager is currently executing in, and cache this list in
 * the VUserMgr object for this client.  If the list has already been
 * read (from a previous property dialog instance), that list is reused
 * (a refresh will clear the list and cause it to be reread when the
 * next instance of this class is created.
 * <p>
 * This object reads the list of authorizations granted to the authenticated
 * principal running User Manager.  The authorization rights entry for the
 * selected target entity in the property dialog is passed to this object
 * in its constructor.  Since authorizations could be assigned to a user,
 * a role, and a profile, the constructor takes an ExtAttrObj instance.
 * With the full list of authorizations, the target and authenticated user
 * authorization entries, a list of AuthAttrModelEntry objects is created
 * and sorted into authorization name order for use in the Authorizations
 * tab dialog.  When the property dialog completes (the OK button pushed),
 * this object will build a new list of authorizations for the selected
 * target user to replace the list in the ExtAttrObj instance passed in
 * the constructor for the this entity (preserving other key/value
 * attributes).
 *
 */

public class AuthAttrMgmt {

    // ========================================================================
    //
    // Public static define constants
    //
    // ========================================================================

    public static final int ATTRMGMT_USER = 0;
    public static final int ATTRMGMT_PROFILE = 1;

    // ========================================================================
    //
    // Private class attributes
    //
    // ========================================================================

    private UserMgrPanelDescriptor panelDesc = null;
    private UserManagedObject userObj = null;
    private ExtAttrObj	    tgt_auth;	// Authorizations for target entity
    private AuthAttrObj []  auth_list;	// List of authorizations
    private AuthAttrModelEntry [] auth_entries; // List of auth model entries
    private int		    tgt_type;	// Type of target: user or profile
    private String	    tgt_name;	// Name of target user, role, profile

    // ========================================================================
    //
    // Constructors
    //
    // ========================================================================

    /**
     * This constructor creates a new authorization management object.	It
     * accepts the reference to the application instance, the attribute
     * authorization object for the user/role/profile, the type of target
     * entity (user or profile), and the name of the target entity.
     * The target attribute authorization object may be null, indicating
     * no previous authorizations exist.
     *
     * @param	theApp	Application instance
     * @param	tgtAttr	UserAttrObj or ProfAttrObj for the target entity
     * @param	tgtType	Type of target: user or profile define constant
     * @param	tgtName	Name of target user, role, or profile
     *
     */
    public AuthAttrMgmt(UserMgrPanelDescriptor panelDesc,
        UserManagedObject userObj) {

	// Save stuff
	this.panelDesc = panelDesc;
	this.userObj = userObj;

	this.auth_list = null;

    }

    // ========================================================================
    //
    // Public methods
    //
    // ========================================================================

    /**
     * The readAuthInfo method reads the full set of authorizations from
     * the authorization table in the current management scope and retrieves
     * the list of granted authorizations for the authenticated user currently
     * running the User Manager tool.  This information is retrieved
     * from the remote management server by the application Content instance
     * and cached there so it can be reused by instances of this object.
     *
     */
    public void readAuthInfo() {

	// See if we have already gotten the list of authorizations.
	// If not, read the list from the application content instance.
	if ((auth_list == null) && (panelDesc != null)) {
	    List<String> auths = panelDesc.getAuths();
	    updateAuths(auths);
            int authsize =  auths.size();
	    auth_list = new AuthAttrObj[authsize];

	    for (int i = 0; i < authsize; i++) {
		auth_list[i] = new AuthAttrObj(auths.get(i));
	    }
	}
    }

    /**
     * Return a list of AuthAttrModelEntry objects for the selected target
     * user.  Each entry object represents an authorization right or an
     * authorization header (if its name ends in a period).  Each entry is
     * marked as to whether it can be granted or revoked in the tab dialog,
     * and whether it is currently granted to the target user.	The list
     * is returned in sorted order by authorization name, so the rights
     * for a particular set are found immediately after the header for the set.
     * For those rights without header entries in the authorization attribute
     * table, a dummy header entry is created.	Header entries are used
     * in the setAuthEntries method to condense the auth entries set for the
     * target user.
     *
     * @return	An array of authorization model entries in sorted order
     *
     */
    public AuthAttrModelEntry [] getAuthEntries() {

	AuthAttrModelEntry [] entrylist;
	AuthAttrModelEntry entry;
	// UserAttrObj tmp_auth;
	Vector<AuthAttrModelEntry> entries;
	String auth_name, hdr_name, str;
	int numauths, i, j;

	// See if we have already gotten the list of authorizations
	// If not, read the list from the management server and save in views.
	if (this.auth_list == null)
	    this.readAuthInfo();

	// Sort the list of authorization objects.  Need at least two entries
	// to require sorting.
	if (auth_list.length > 1) {
	    AuthAttrCompare comp = new AuthAttrCompare();
	    Sort.sort(auth_list, comp);
	}

	// Create a vector of auth model entry objects, one for each auth
	// in the master list.	Check if the current admin running the tool has
	// the right to grant this right.  Check if the target user has this
	// right already granted.
	// If the auth right prefix changes and the
	// next entry is not a header entry, create a dummy header entry for
	// the new right (and any subsequent rights with the same prefix).
	hdr_name = "";
	numauths = auth_list.length;
	entries = new Vector<AuthAttrModelEntry>(numauths);
	Vector authNames = getUserAuths();

	AuthAttrModelEntry prev_entry = null;
	for (i = 0; i < numauths; i++) {
	    auth_name = auth_list[i].getAuthName();

	    // Create a new auth model entry object
	    entry = new AuthAttrModelEntry(auth_list[i]);

	    if (hasObject(auth_name)) {
		if (hasWildAuth(auth_name) && prev_entry != null) {
		    prev_entry.setHeader(true);
		}
	    }
	    prev_entry = entry;

	    // Process explicit header entry
	    // if (auth_name.endsWith(".")) 		// Cannot grant header
	    if (entry.isHeader()) {		// Cannot grant header
		hdr_name = auth_name;
		entries.addElement(entry);		// Add hdr entry to list
		continue;				// and skip the rest...
	    }

	    // Check for and process implicit header entry
	    j = auth_name.lastIndexOf('.');
	    if (j > 0) {
		str = auth_name.substring(0, (j + 1));
		if (! (str.equals(hdr_name))) {
		    hdr_name = str;			// Add dummy hdr entry
		    entries.addElement(
				new AuthAttrModelEntry(hdr_name, "", ""));
		}
	    }

	    // All entries can be granted
	    entry.setToBeGranted();

	    if ((authNames != null) && (checkAuthName(authNames, auth_name)))
		entry.grant();
	    entries.addElement(entry);		// Add rights entry

	}						// End of for loop

	// Turn vector of auth model objects into an array
	entrylist = new AuthAttrModelEntry[entries.size()];
	entries.copyInto((Object [])entrylist);

	// Return the list of model entries for presentation
	return (entrylist);

    }

    /**
     * Update the selected target user list of granted authorizations based
     * upon the list of authorization model entries returned from the Rights
     * tab dialog.  The existing list of authorizations will be deleted and
     * a new list constructed.	Each authorization model entry which is marked
     * granted will be included in the new authorization object.  The new
     * user authorization attribute object is returned.
     * <p>
     * Additionally, if all rights (except the "grant"
     * right) for a common set of rights (all rights with the same prefix)
     * are granted, then replace the set with the "*" right with that same
     * prefix; e.g., if all rights under "com.sun.usermgr.xxx" are granted,
     * set the single right "com.sun.usermgr.*" instead.  This will collapse
     * the granted rights into fewer entries.  Note the com.sun.usermgr.grant
     * right is not included in the com.sun.usermgr.* right, so it will be
     * set separately.
     * <p>
     * This method assumes it is processing the same auth model entry array
     * that was previously returned by the getAuthEntries method; that is,
     * the array of entries is in sorted order by auth right name.
     *
     * @param	auth_entries	Array of authorization model entry objects
     *
     * @return	The new user authorization attribute object for the targer user
     *
     */
    public Vector<String> setAuthEntries(AuthAttrModelEntry [] auth_entries) {

	String [] auth_names;
	Vector<String> v;
	String name;
	int i, last_hdr;
	boolean sw;

	v = new Vector<String>();


	// Walk through the authorization entries. When we encounter a header
	// entry and it is granted, we set the "*" right (the entire common
	// set of rights with the same prefix are granted) and do not set any
	// of the specific rights.  The "grant" right is an exception; that is,
	// it is included in the granted rights if it is granted independently
	// of checking the header entry.
	sw = true;
	for (i = 0; i < auth_entries.length; i++) {
	    name = auth_entries[i].getAuthName();

	    // Process header entry
	    if (auth_entries[i].isHeader()) {
		if (auth_entries[i].isGranted()) {
		    sw = false;

		    for (int j = 0; j < i; j++) {
			if (auth_entries[j].isGranted()) {
			    if (auth_entries[i].getAuthName().startsWith(
				auth_entries[j].getAuthName())) {
				auth_entries[i].revoke();
				break;
			    }
			}
		    }
		    if (auth_entries[i].isGranted()) {
			if (name.endsWith(AuthAttrObj.SOLARIS_DOT)) {
			    v.addElement(name.concat(AuthAttrObj.SOLARIS_ALL));
			} else {
			    v.addElement(name);
			}
		    }
		} else {
		    sw = true;				// Test each right
		}
		continue;
	    }

	    // Process rights entry
	    if (auth_entries[i].isGranted()) {
		if ((sw) || (name.endsWith(AuthAttrObj.SOLARIS_GRANT)))
		    v.addElement(name);
	    }
	}						// End of for loop

	ExtAttrObj new_auth = null;

	// Return the new auth object.
	return (v);

    }

    /**
     * Check if this user account has been granted the specified
     * authorization.
     *
     * @param An authorization name
     *
     */
    public boolean checkAuthName(Vector authNames, String authStr) {

	String authname = authStr;

	if (authNames == null)
	    return (false);
	if (authNames.contains(authname))
	    return true;

	// try to find a wildcard match further up the tree
	StringTokenizer tk = new StringTokenizer(authname,
	    AuthAttrObj.SOLARIS_DOT);
	String matchType;
	int tokCount = tk.countTokens() -1;
	if (tokCount < 1) {
	    // not enough tokens; invalid authname?
	    return false;
	}

	// Grant authorization does not match against "All"
	// However, grant does match another grant further up the tree
	if (authname.endsWith("." + AuthAttrObj.SOLARIS_GRANT))
	    matchType = AuthAttrObj.SOLARIS_GRANT;
	else
	    matchType = AuthAttrObj.SOLARIS_ALL;

	// walk the tree from the root, looking for implicit matches
	String authPath = "";
	for (int i = 0; i < tokCount; i++) {
	    authPath = authPath.concat((String)tk.nextElement() +
					AuthAttrObj.SOLARIS_DOT);
	    if (authNames.contains(authPath.concat(matchType)))
		return true;
	}
	return false;

    }

    private Vector<String> getUserAuths() {
        String auths = userObj.getAuths();
	Vector<String> userAuths = null;

	if (auths != null) {
	    String[] authList = userObj.getAuths().split(",");
	    userAuths = new Vector<String>(authList.length);
	    for (String auth : authList) {
		userAuths.add(auth);
	    }
	}

	return (userAuths);
    }

    private void updateAuths(List<String> auths) {
        Vector<String> uAuths = getUserAuths();
	if (uAuths == null || uAuths.size() == 0) {
	    return;
	}


	for (String uAuth : uAuths) {
	    int idx = uAuth.indexOf(AuthAttrObj.SOLARIS_SLASH);

	    if (idx == -1) {
		continue; // doesn't contain object name
	    }
	    // Contains object name
	    String authStr = uAuth.substring(0, idx);

	    for (int j = 0; j < auths.size(); j++) {
		String auth = auths.get(j);
		if (auth.equals(authStr)) {
		    String nextauth = auths.get(j+1);
		    String wildAuth = getWildAuth(authStr);

		    if (nextauth.equals(wildAuth) == false) {
			auths.add(j+1, wildAuth);
		    }
		    auths.add(j+2, uAuth);
		}
	    }
	}
    }

    /*
     * Translate the authname to authname
     */
    private String getWildAuth(String auth) {
        return (auth + AuthAttrObj.SOLARIS_SLASH + AuthAttrObj.SOLARIS_ALL);
    }

    /**
     * Check if the authname has the wildcard '*'
     */
    private boolean hasWildAuth(String auth) {
        return (auth.endsWith(AuthAttrObj.SOLARIS_SLASH +
		AuthAttrObj.SOLARIS_ALL));
    }

    /**
     * Check if the authname is in the form: auth/<object>
     */
    private boolean hasObject(String auth) {
	if (auth.indexOf(AuthAttrObj.SOLARIS_SLASH) == -1) {
	    return (false);
	} else {
	    return (true);
	}
    }
}
