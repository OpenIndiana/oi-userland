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
import javax.swing.*;
import com.oracle.solaris.vp.panel.common.model.AbstractManagedObject;
import com.oracle.solaris.rad.usermgr.*;
import com.oracle.solaris.vp.util.misc.*;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.misc.property.*;
import com.oracle.solaris.vp.util.swing.HasIcon;

/**
 * User Managed Object represents user object
 */
@SuppressWarnings({"serial"})
public class UserManagedObject
    extends AbstractManagedObject<UserManagedObject> implements HasIcon {

    //
    // Static data
    //
    public static final String PASSWORD = "PASSWORD";
    public static final String NOTACTIVE = "NOTACTIVATED";


    // Icons - for user, roles
    protected static final List<ImageIcon> userIcons = Finder.getIcons(
	"images/user-24.png");

    protected static final List<ImageIcon> roleIcons = Finder.getIcons(
	"images/role-24.png");

    //
    // Instance data
    //

    private UserMgrPanelDescriptor descriptor;
    private UserType type = UserType.NORMAL;
    private boolean isNewUser = false;
    private UserChangeFieldsImpl modChanges = null;

    private MutableProperty<Long> groupIdProperty =
	new LongProperty();

    private MutableProperty<String> homeDirProperty =
	new StringProperty();

    private MutableProperty<String> rightsProperty =
	new StringProperty();

    private MutableProperty<String> rolesProperty =
	new StringProperty();

    private MutableProperty<String> groupsProperty =
	new StringProperty();

    private MutableProperty<String> authsProperty =
	new StringProperty();

    private MutableProperty<String> shellProperty =
	new StringProperty();

    private MutableProperty<String> userDescProperty =
	new StringProperty();

    private MutableProperty<Long> userIdProperty =
	new LongProperty();

    private MutableProperty<String> userNameProperty =
	new StringProperty();

    private MutableProperty<String> accountStatusProperty =
	new StringProperty();

    private MutableProperty<char[]> passProperty =
	new BasicMutableProperty<char[]>();
    {
        ChangeableAggregator aggregator = getChangeableAggregator();
	aggregator.addChangeables(groupIdProperty, homeDirProperty,
	    passProperty, shellProperty,
	    rolesProperty, rightsProperty, authsProperty, groupsProperty,
	    userDescProperty, userIdProperty, userNameProperty);
    }

    //
    // Constructors
    //

    UserManagedObject(UserMgrPanelDescriptor descriptor,
	User user, UserType type,
	char[] password, boolean bNewUser) {

	this.descriptor = descriptor;
	this.type = type;
	this.isNewUser = bNewUser;

	userNameProperty.update(user.getUsername(), true);
	userDescProperty.update(user.getDescription(), true);
	userIdProperty.update(user.getUserID(), true);
	groupIdProperty.update(user.getGroupID(), true);
	homeDirProperty.update(user.getHomeDirectory(), true);
	shellProperty.update(user.getDefaultShell(), true);

	rolesProperty.update(listToString(user.getRoles()), true);
	rightsProperty.update(listToString(user.getProfiles()), true);
	authsProperty.update(listToString(user.getAuths()), true);
	groupsProperty.update(listToString(user.getGroups()), true);
	accountStatusProperty.update(user.getAccountStatus() == null ? ""
		: user.getAccountStatus(), true);

	if (password != null) {
	    passProperty.update(password, true);
        }
    }

    UserManagedObject(UserMgrPanelDescriptor descriptor,
	User user, char[] password) {
	this(descriptor, user, UserType.NORMAL, password, true);
    }

    //
    // HasIcon methods
    //

    @Override
    public Icon getIcon(int height) {
	List<ImageIcon> icons = (getUserType() == UserType.NORMAL) ?
	    userIcons : roleIcons;
	return IconUtil.getClosestIcon(icons, height);
    }

    //
    // AbstractManagedObject methods
    //

    @Override
    public String getName() {
	return userNameProperty.getValue();
    }

    @Override
    public String getId() {
	return userNameProperty.getValue();
    }

    @Override
    public String toString() {
	StringBuilder sb = new StringBuilder();
	sb.append("\n\tname: ").append(getUsername())
	    .append("\n\tuid: ").append(getUserId())
	    .append("\n\tgid: ").append(getGroupId())
	    .append("\n\tdescription: ").append(getUserDescription())
	    .append("\n\thome dir: ").append(getHomedir())
	    .append("\n\tshell: ").append(getShell())
	    .append("\n\ttype: ")
	    .append(type == UserType.NORMAL ? "user" : "role")
	    .append("\n\trights: ").append(getRights())
	    .append("\n\tauths: ").append(getAuths())
	    .append("\n\tgroups: ").append(getGroups())
	    .append("\n\troles: ").append(getRoles())
	    .append("\n\tstatus: ").append(getAccountStatus());
	return sb.toString();
    }

    public void setUser(User user, char[] password) {

	userNameProperty.update(user.getUsername(), true);
	userDescProperty.update(user.getDescription(), true);
	userIdProperty.update(user.getUserID(), true);
	groupIdProperty.update(user.getGroupID(), true);
	homeDirProperty.update(user.getHomeDirectory(), true);
	shellProperty.update(user.getDefaultShell(), true);

	passProperty.update(password, true);
    }

    //
    // UserManagedObject methods
    //

    public MutableProperty<Long> getGroupIdProperty() {
	return groupIdProperty;
    }

    public MutableProperty<String> getHomeDirProperty() {
	return homeDirProperty;
    }


    public MutableProperty<String> getRightsProperty() {
	return rightsProperty;
    }

    public MutableProperty<String> getRolesProperty() {
	return rolesProperty;
    }

    public MutableProperty<String> getGroupsProperty() {
	return groupsProperty;
    }

    public MutableProperty<String> getAuthsProperty() {
	return authsProperty;
    }

    public MutableProperty<String> getUserDescProperty() {
	return userDescProperty;
    }

    public MutableProperty<char[]> getPassProperty() {
	return passProperty;
    }

    public MutableProperty<String> getShellProperty() {
	return shellProperty;
    }

    public MutableProperty<Long> getUserIdProperty() {
	return userIdProperty;
    }

    public MutableProperty<String> getUserNameProperty() {
	return userNameProperty;
    }

    public UserMgrPanelDescriptor getPanelDescriptor() {
	return descriptor;
    }

    public String getUsername() {
	return userNameProperty.getValue();
    }

    public String getUserDescription() {
	return userDescProperty.getValue();
    }

    public long getUserId() {
	return userIdProperty.getValue();
    }

    public long getGroupId() {
	return groupIdProperty.getValue();
    }

    public String getHomedir() {
	return homeDirProperty.getValue();
    }

    public char[] getPassword() {
	return passProperty.getValue();
    }

    public String getShell() {
	return shellProperty.getValue();
    }

    public UserType getUserType() {
	return type;
    }

    public String getRights() {
	return rightsProperty.getValue();
    }

    public String getRoles() {
	return rolesProperty.getValue();
    }

    public String getGroups() {
	return groupsProperty.getValue();
    }

    public String getAuths() {
	return authsProperty.getValue();
    }

    public String getAccountStatus() {
	return accountStatusProperty.getValue();
    }

    public boolean isUserNormal() {
	return type == UserType.NORMAL;
    }

    public boolean isRole() {
	return type == UserType.ROLE;
    }

    public boolean isNewUser() {
	return isNewUser;
    }

    public boolean hasPassword() {
        if (getAccountStatus().equals(PASSWORD)) {
	    return (true);
	}

	return (false);
    }

    // Update the "auto-generated" properties for the newly created user
    public void updateUser(User user) {
	userIdProperty.update(user.getUserID(), true);
	homeDirProperty.update(user.getHomeDirectory(), true);
	this.isNewUser = false;
    }

    // Construct a new User object from the defined properties
    public User getNewUser() {

	UserImpl newUser = new UserImpl();
	newUser.setUsername(getUsername());
	newUser.setUserID(getUserId());
	newUser.setGroupID(getGroupId());
	newUser.setDescription(getUserDescription());
	if (homeDirProperty.isChanged())
	    newUser.setHomeDirectory(getHomedir());
	else // must be null
	    newUser.setHomeDirectory(null);

	newUser.setDefaultShell(getShell());

	if (getRights() != null) {
	    // System.out.println("new user rights:" + getRights());
	    newUser.setProfiles(stringToList(getRights()));
	}

	if (getRoles() != null) {
	    // System.out.println("new user roles:" + getRoles());
	    newUser.setRoles(stringToList(getRoles()));
	}

	if (getAuths() != null) {
	    newUser.setAuths(stringToList(getAuths()));
	}

	if (getGroups() != null) {
	    newUser.setGroups(stringToList(getGroups()));
	}

	return newUser;
    }

    // Construct a User object with only modified properties set
    public User getModifiedUser() {
	boolean bChanged = false;
	UserImpl modUser = new UserImpl();
	modChanges = new UserChangeFieldsImpl();

	// check each property for changes
	if (userDescProperty.isChanged()) {
	    modUser.setDescription(getUserDescription());
	    bChanged = true;
	}
	if (shellProperty.isChanged()) {
	    modUser.setDefaultShell(getShell());
	    bChanged = true;
	}
	if (groupIdProperty.isChanged()) {
	    modUser.setGroupID(getGroupId());
	    bChanged = true;
	}
	if (passProperty.isChanged()) {
	    bChanged = true;
	}

	if (rightsProperty.isChanged()) {
	    // System.out.println("mod user rights " + getRights());
	    modUser.setProfiles(stringToList(getRights()));
	    modChanges.setProfilesChanged(true);
	    bChanged = true;
	}

	if (rolesProperty.isChanged()) {
	    // System.out.println("mod user roles " + getRoles());
	    modUser.setRoles(stringToList(getRoles()));
	    modChanges.setRolesChanged(true);
	    bChanged = true;
	}

	if (authsProperty.isChanged()) {
	    // System.out.println("mod user auths " + getAuths());
	    modUser.setAuths(stringToList(getAuths()));
	    modChanges.setAuthsChanged(true);
	    bChanged = true;
	}

	if (groupsProperty.isChanged()) {
	    // System.out.println("mod user groups " + getGroups());
	    modUser.setGroups(stringToList(getGroups()));
	    modChanges.setGroupsChanged(true);
	    bChanged = true;
	}

	if (bChanged) {
	    modUser.setUsername(getUsername());
	} else {
	    modUser = null;
	}

	return modUser;
    }

    public String listToString(List<String> list) {
	String str;

	if (list == null) {
	    return ("");
	}

	if (list.size() > 0) {
		str = list.get(0);
	} else {
		str = "";
	}

	for (int i = 1; i < list.size(); i++) {
	    str = str.concat(",");
	    str = str.concat(list.get(i));
        }

	return (str);
    }

    public List<String> stringToList(String str) {
	List<String> list = new ArrayList<String>();
	String[] strings = str.split(",");

	for (String s : strings) {
	    list.add(s);
        }

	return (list);
    }

    public UserChangeFieldsImpl getModifiedChanges() {
        return (modChanges);
    }
}
