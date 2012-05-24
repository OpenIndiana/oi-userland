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

import java.util.*;
import java.util.logging.Level;
import javax.management.ObjectName;
import javax.swing.Icon;
import com.oracle.solaris.adr.Stability;
import com.oracle.solaris.rad.ObjectException;
import com.oracle.solaris.vp.panel.common.*;
import com.oracle.solaris.vp.panel.common.action.*;
import com.oracle.solaris.vp.panel.common.api.panel.MBeanUtil;
import com.oracle.solaris.vp.panel.common.control.*;
import com.oracle.solaris.vp.panel.common.model.*;
import com.oracle.solaris.vp.panel.swing.control.PanelFrameControl;
import com.oracle.solaris.vp.panel.swing.model.SwingPanelDescriptor;
import com.oracle.solaris.rad.usermgr.*;
import com.oracle.solaris.vp.util.misc.*;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.misc.property.*;
import com.oracle.solaris.vp.util.swing.HasIcons;

public class UserMgrPanelDescriptor
    extends AbstractPanelDescriptor<UserManagedObject>
    implements SwingPanelDescriptor<UserManagedObject>, HasIcons {

    //
    // Static data
    //

    // Constants needed for registering the MBean
    public static final String INTERFACE_NAME =
    	"com.oracle.solaris.rad.usermgr";
    public static final ObjectName OBJECT_NAME =
        MBeanUtil.makeObjectName(INTERFACE_NAME, "UserMgr");

    public static final String USER_TYPE_NORMAL = "normal";
    public static final String SCOPE_FILES = "files";
    public static final String MATCH_ALL = "*";

    //
    // Instance data
    //

    private MainControl mc;
    private DefaultControl control;
    private MXBeanTracker<UserMgrMXBean> beanTracker;
    private UserType uType;

    private String scopeStr = SCOPE_FILES;
    private String typeStr = USER_TYPE_NORMAL;
    private String matchStr = MATCH_ALL;

    private List<UserManagedObject> deleteList =
	new ArrayList<UserManagedObject> ();
    private List<UserManagedObject> addList =
	new ArrayList<UserManagedObject> ();

    private MutableProperty<Integer> addedProperty =
	new IntegerProperty();
    private MutableProperty<Integer> deletedProperty =
	new IntegerProperty();
    {
	getChangeableAggregator().addChangeables(
	    addedProperty, deletedProperty);
    }

    //
    // Constructors
    //

    /**
     * Constructs a {@code UserMgrPanelDescriptor}.
     *
     * @param	    id
     *		    a unique identifier for this Panel, taken from the panel
     *		    registration
     *
     * @param	    context
     *		    a handle to interact with the Visual Panels client
     */
    public UserMgrPanelDescriptor(String id, ClientContext context)
	throws TrackerException {

        super(id, context);

	beanTracker = new MXBeanTracker<UserMgrMXBean>(
	    OBJECT_NAME, UserMgrMXBean.class, Stability.PRIVATE, context);

	setComparator(SimpleHasId.COMPARATOR);

	// Initialize list of users
	initUsers(SCOPE_FILES, USER_TYPE_NORMAL, MATCH_ALL);

	// Keep track of users added/deleted
	addedProperty.update(0, true);
	deletedProperty.update(0, true);

        control = new PanelFrameControl<UserMgrPanelDescriptor>(this);
        mc = new MainControl(this);
	control.addChildren(mc);
    }

    //
    // PanelDescriptor methods
    //

    /**
     * Returns the top-most Control for this PanelDescriptor.
     */
    @Override
    public Control getControl() {
        return control;
    }

    //
    // HasIcons methods
    //

    /**
     * Returns a list of icons.
     */
    @Override
    public List<? extends Icon> getIcons() {
	return UserManagedObject.userIcons;
    }

    //
    // ManagedObject methods
    //

    /**
     * Stops monitoring the connection to the remote host.
     */
    @Override
    public void dispose() {
	beanTracker.dispose();
	super.dispose();
    }

    /**
     * Returns the name of this Managed Object.
     */
    @Override
    public String getName() {
	return Finder.getString("panel.usermgr.name");
    }

    //
    // AbstractManagedObject methods
    //

    @Override
    public void addChildren(UserManagedObject... toAdd) {
	super.addChildren(toAdd);

	ChangeableAggregator aggregator = getChangeableAggregator();
	for (UserManagedObject umo : toAdd) {
	    aggregator.addChangeables(umo.getChangeableAggregator());
	}
    }

    //
    // UserMgrPanelDescriptor methods
    //

    public void removeChildren(UserManagedObject toRemove) {
	super.removeChildren(toRemove);

	ChangeableAggregator aggregator = getChangeableAggregator();
	aggregator.removeChangeable(toRemove.getChangeableAggregator());
    }

    public void removeAllChildren() {
	super.clearChildren();
	ChangeableAggregator aggregator = getChangeableAggregator();
	aggregator.reset();
    }

    public UserMgrMXBean getUserMgrBean() {
        return beanTracker.getBean();
    }

    public UserManagedObject getUserManagedObject(String id) {

	SimpleHasId tmpHasId = new SimpleHasId();
	synchronized (children) {
	    tmpHasId.setId(id);
	    int index = Collections.binarySearch(children, tmpHasId,
		SimpleHasId.COMPARATOR);

	    if (index >= 0) {
		return children.get(index);
	    }

	    return null;
	}
    }

    public void deleteUserManagedObject(UserManagedObject toRemove) {
	removeChildren(toRemove);
    }

    public void addUserManagedObject(UserManagedObject toAdd) {
	addChildren(toAdd);
    }

    public void addToAddList(UserManagedObject toAdd) {
	addedProperty.setValue(addedProperty.getValue() + 1);
	addList.add(toAdd);
    }

    public void addToDeleteList(UserManagedObject toRemove) {
	deletedProperty.setValue(deletedProperty.getValue() + 1);
	deleteList.add(toRemove);
    }

    public void saveDeletedUsers() throws ActionAbortedException,
	ActionFailedException, ActionUnauthorizedException {

	Iterator<UserManagedObject> it = deleteList.iterator();
	while (it.hasNext()) {
	    UserManagedObject umo = it.next();
	    try {
		getUserMgrBean().deleteUser(umo.getName());
		deleteUserManagedObject(umo);
		it.remove();
		deletedProperty.setValue(deletedProperty.getValue() - 1);
	    } catch (SecurityException se) {
		throw new ActionUnauthorizedException(se);
	    } catch (ObjectException e) {
		UserMgrError ume = e.getPayload(UserMgrError.class);
		String msg = Finder.getString("usermgr.error.invalidData");
		String err = Finder.getString(
		    "usermgr.error.delete", umo.getUsername());
		getLog().log(Level.SEVERE, err + msg, e);
		throw new ActionFailedException(err + msg);
	    // Any other remaining exceptions
	    } catch (Exception e) {
		String msg = Finder.getString("usermgr.error.system");
		String err = Finder.getString(
		    "usermgr.error.delete", umo.getUsername());
		getLog().log(Level.SEVERE, err + msg, e);
		throw new ActionFailedException(err + msg);
	    }
	}
    }

    public void saveAddedUsers() throws ActionAbortedException,
	ActionFailedException, ActionUnauthorizedException {

	Iterator<UserManagedObject> it = addList.iterator();
	while (it.hasNext()) {
	    UserManagedObject umo = it.next();
	    try {
		char[] password = umo.getPassword();
		User user = getUserMgrBean().addUser(
		    umo.getNewUser(), password);
		addUserManagedObject(umo);
		Arrays.fill(password, (char)0);

		it.remove();
		addedProperty.setValue(addedProperty.getValue() - 1);
		umo.updateUser(user);
	    } catch (SecurityException se) {
		throw new ActionUnauthorizedException(se);
	    } catch (ObjectException e) {
		e.printStackTrace();
		UserMgrError ume = e.getPayload(UserMgrError.class);
		String msg;
		UserMgrErrorType error = (ume != null) ?
		    ume.getErrorCode() : UserMgrErrorType.INVALIDDATA;
		switch (error) {
		    case USEREXISTS:
			msg = Finder.getString("usermgr.error.userExists");
			break;
		    case PASSERROR:
			msg = Finder.getString("usermgr.error.passError");
			break;
		    default: // Invalid Data
			msg = Finder.getString("usermgr.error.invalidData");
			break;
		}
		String err = Finder.getString("usermgr.error.add",
		    umo.getUsername());
		getLog().log(Level.SEVERE, err + msg, e);
    		deleteUserManagedObject(umo);
		throw new ActionFailedException(err + msg);
	    // Any other remaining exceptions
	    } catch (Exception e) {
		String msg = Finder.getString("usermgr.error.system");
		String err = Finder.getString(
		    "usermgr.error.add", umo.getUsername());
		getLog().log(Level.SEVERE, err + msg, e);
		throw new ActionFailedException(err + msg);
	    }
	    umo.getChangeableAggregator().save();
	}
    }

    public void saveModifiedUsers() throws ActionAbortedException,
	ActionFailedException, ActionUnauthorizedException {

	List<UserManagedObject> kids = getChildren();
	for (UserManagedObject umo : kids) {
	    if (umo.getChangeableAggregator().isChanged()) {
		User user = umo.getModifiedUser();
		UserChangeFields changes = umo.getModifiedChanges();
		try {
		    if (user != null) {
			char[] password = null;
			if (umo.getPassProperty().isChanged())
			    password = umo.getPassword();
			getUserMgrBean().modifyUser(user, password, changes);
			if (password != null)
			    Arrays.fill(password, (char)0);
		    }
		} catch (SecurityException se) {
		    throw new ActionUnauthorizedException(se);
		} catch (ObjectException e) {
		    UserMgrError ume = e.getPayload(UserMgrError.class);
		    String msg;
		    UserMgrErrorType error = (ume != null) ?
			ume.getErrorCode() : UserMgrErrorType.INVALIDDATA;
		    switch (error) {
			case PASSERROR:
			    msg = Finder.getString("usermgr.error.passError");
			    break;
			default:
			    msg = Finder.getString("usermgr.error.invalidData");
			    break;
		    }
		    String err = Finder.getString(
			"usermgr.error.modify", umo.getUsername());
		    getLog().log(Level.SEVERE, err + msg, e);
		    throw new ActionFailedException(err + msg);
		// Any other remaining exceptions
		} catch (Exception e) {
		    String msg = Finder.getString("usermgr.error.system");
		    String err = Finder.getString(
			"usermgr.error.modify", umo.getUsername());
		    getLog().log(Level.SEVERE, err + msg, e);
		    throw new ActionFailedException(err + msg);
		}
		umo.getChangeableAggregator().save();
	    }
	}
    }

    public List<Group> getGroups() {
	try {
	    return getUserMgrBean().getgroups();
        } catch (ObjectException e) {
            getLog().log(Level.SEVERE, "Error getting group list.", e);
	}
	return null;
    }

    public List<String> getSupplGroups() {
	try {
	    return getUserMgrBean().getsupplGroups();
        } catch (ObjectException e) {
            getLog().log(Level.SEVERE,
	    "Error getting supplementary group list.", e);
	}
	return null;
    }

    public List<String> getShells() {
	try {
	    return getUserMgrBean().getshells();
        } catch (ObjectException e) {
            getLog().log(Level.SEVERE, "Error getting shell list.", e);
	}
	return null;
    }

    public List<String> getScopes() {
	try {
	    return getUserMgrBean().getscopes();
        } catch (ObjectException e) {
            getLog().log(Level.SEVERE, "Error getting  scopes list.", e);
	}
	return null;
    }

    public List<String> getProfiles() {
	try {
	    return getUserMgrBean().getprofiles();
        } catch (ObjectException e) {
            getLog().log(Level.SEVERE, "Error getting profiles list.", e);
	}
	return null;
    }

    public List<String> getAuths() {
	try {
	    return getUserMgrBean().getauths();
        } catch (ObjectException e) {
            getLog().log(Level.SEVERE, "Error getting authorizations list.", e);
	}
	return null;
    }

    public List<String> getRoles() {
	try {
	    return getUserMgrBean().getroles();
        } catch (ObjectException e) {
            getLog().log(Level.SEVERE, "Error getting roles list.", e);
	}
	return null;
    }

    public void setScope(String scope) {
        ScopeType sType;
	if (scope.equals(SCOPE_FILES)) {
	    sType = ScopeType.FILES;
	} else {
	    sType = ScopeType.LDAP;
	}

	try {
	    getUserMgrBean().setScope(sType);
        } catch (Exception e) {
            getLog().log(Level.SEVERE, "Error setting  scope.", e);
	}
    }

    public UserImpl getDefaultUser() {
	try {
	    User defUser = getUserMgrBean().getdefaultUser();
	    return new UserImpl(
		"", 0L, defUser.getGroupID(),
		"", "", defUser.getDefaultShell(),
		0, 0, 0, 0,
		"", "", "", "", "", "",
		"", "", "", "", "", "",
		null, null, null, null, null, null);
	} catch (ObjectException e) {
	    getLog().log(Level.SEVERE, "Error getting default user.", e);
	}

	return null;
    }

    public void initUsers(String scopeStr,
    		String typeStr, String matchStr) {
	int count = 0;
	String statusStr;
	String listTitle;

	this.scopeStr = scopeStr;
	this.typeStr = typeStr;
	this.matchStr = matchStr;

	setScope(scopeStr);

	statusStr = Finder.getString("usermgr.status.scope") +
	    " " + scopeStr;
	if (typeStr.equals(USER_TYPE_NORMAL)) {
	    uType = UserType.NORMAL;
	    listTitle = Finder.getString("usermgr.list.title.user");
	} else {
	    uType = UserType.ROLE;
	    listTitle = Finder.getString("usermgr.list.title.role");
	}

	setFilter(uType, matchStr);
	List<User> users = getUsers();

	removeAllChildren();
	try {
	    boolean uTypeSet = false;
	    for (User user : users) {
		String username = user.getUsername();
		UserMgrMXBean bean = getUserMgrBean();
		if (uTypeSet == false) {
		    uType = bean.getUserType(username);
		    uTypeSet = true;
		}

		UserManagedObject umo = new UserManagedObject(this,
		    user, uType, null, false);
		addChildren(umo);
	    }

	} catch (ObjectException e) {
	    getLog().log(Level.SEVERE, "Error creating user list.", e);
	} finally {
	    setStatusText(statusStr);
	    if (mc != null) {
		mc.setListTitle(listTitle);
	    }
        }
    }

    public boolean isTypeRole() {
        return (uType == UserType.ROLE ? true : false);
    }

    public String getTypeString() {
        return (uType == UserType.ROLE ? "role" : "user");
    }

    public String getScope() {
        return (scopeStr);
    }

    public String getType() {
        return (typeStr);
    }


    public String getMatch() {
        return (matchStr);
    }

    //
    // Private methods
    //

    private List<User> getUsers() {
	List<User> users = null;
	try {
	    users = getUserMgrBean().getusers();
        } catch (ObjectException e) {
            getLog().log(Level.SEVERE, "Error getting user list.", e);
	}
	return users;
    }

    private void setFilter(UserType utype, String search) {
	try {
	    getUserMgrBean().setFilter(utype, search);
        } catch (Exception e) {
            getLog().log(Level.SEVERE, "Error setting filter.", e);
	}
    }
}
