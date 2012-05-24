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


import java.util.List;
import java.util.Map;
import com.oracle.solaris.rad.usermgr.*;
import com.oracle.solaris.vp.panel.common.action.*;
import com.oracle.solaris.vp.panel.common.control.*;
import com.oracle.solaris.vp.panel.swing.control.*;
import com.oracle.solaris.vp.util.misc.finder.Finder;

public class UserMgrBasicControl
    extends SettingsControl<UserMgrPanelDescriptor, UserMgrBasicPanel> {

    //
    // Static data
    //
    public static final String ID = "usermgr";
    public static final String PARAM_USER = "user";
    private UserMgrPanelDescriptor descriptor;

    //
    // Instance data
    //

    private UserManagedObject userMO;

    public UserMgrBasicControl(UserMgrPanelDescriptor descriptor) {
        super(ID, PARAM_USER, descriptor);
	this.descriptor = descriptor;
    }

    //
    // Control methods
    //

    @Override
    public boolean isBrowsable() {
	// This control requires init parameters
	return false;
    }

    @Override
    protected boolean isChanged() {
	return true;
    }


    @Override
    protected UnsavedChangesAction getUnsavedChangesAction() {
	// Always save changes on the client
	return UnsavedChangesAction.SAVE;
    }

    @Override
    protected void save() throws ActionAbortedException,
        ActionFailedException, ActionUnauthorizedException {

	UserMgrBasicPanel panel = getComponent();
	UserManagedObject umo = getUserManagedObject();

	setPropertyChangeIgnore(true);

	// Set changed values from the panel
	if (panel.getGroupProperty().isChanged()) {
	    umo.getGroupIdProperty().setValue(toGid(
		panel.getGroupProperty().getValue()));
	}

	if (panel.getShellProperty().isChanged()) {
	    umo.getShellProperty().setValue(
		panel.getShellProperty().getValue());
	}

	// Set the values from the panel
	if (panel.getDescProperty().isChanged()) {
	    String userdesc = panel.getDescProperty().getValue();
	    UserMgrUtils.validateUserDesc(userdesc);
	    umo.getUserDescProperty().setValue(userdesc);
	 }

	 if (panel.getHomeProperty().isChanged()) {
	    String homeDir = panel.getHomeProperty().getValue();
	    UserMgrUtils.validateHomeDir(homeDir);
	    umo.getHomeDirProperty().setValue(homeDir);
	 }

	 if (panel.getPassProperty().isChanged() ||
	    panel.getPassConfirmProperty().isChanged()) {
	    char[] pass1 = panel.getPassProperty().getValue();
	    char[] pass2 = panel.getPassConfirmProperty().getValue();
	    UserMgrUtils.validatePassword(umo.isNewUser(), pass1, pass2);
	    umo.getPassProperty().setValue(pass1);
	 }
    }

    //
    // SwingControl Methods
    //

    @Override
    protected UserMgrBasicPanel createComponent() {
        UserMgrBasicPanel panel = new UserMgrBasicPanel(descriptor);
        return panel;
    }

    @Override
    protected void initComponent() {
	UserMgrBasicPanel panel = getComponent();
	UserManagedObject umo = getUserManagedObject();

	// Initialize the panel
	panel.init(getPanelDescriptor(), umo);
    }

    private long toGid(String gName) {
	List<Group> groups = getPanelDescriptor().getGroups();
 	for (Group g : groups) {
	    if (gName.equals(g.getGroupName()))
 		return (g.getGroupID());
 	}
 	return 1L;
    }

    @Override
    public void start(Navigator navigator, Map<String, String> parameters)
	throws NavigationAbortedException, InvalidParameterException,
	NavigationFailedException {

	String param = getParameter(parameters, PARAM_USER);
  	UserManagedObject umo =
	    getPanelDescriptor().getUserManagedObject(param);
	if (umo == null) {
	    throw new InvalidParameterException(getId(), PARAM_USER, param);
  	}

  	setUserManagedObject(umo);

 	super.start(navigator, parameters);
    }

    @Override
    public void stop(boolean isCancel) throws NavigationAbortedException {
 	super.stop(isCancel);
 	setUserManagedObject(null);
    }

    //
    // UserMgrControl methods
    //

    public UserManagedObject getUserManagedObject() {
	return userMO;
    }

    //
    // Private methods
    //

    private void setUserManagedObject(UserManagedObject umo) {
	this.userMO = umo;
	setName(umo == null ? null : umo.getName());
    }

    /**
     * Clear the advanced settings change state.
     */
    public void clearChanges() {
        getComponent().clearChanges();
    }
}
