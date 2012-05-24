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
 * Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
 */

package com.oracle.solaris.vp.panels.usermgr.client.swing;

import java.util.ArrayList;
import java.util.List;
import java.util.Vector;
import java.awt.*;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.border.Border;
import com.oracle.solaris.vp.panel.common.action.*;
import com.oracle.solaris.vp.panel.common.control.*;
import com.oracle.solaris.vp.panel.swing.control.*;
import com.oracle.solaris.vp.panel.swing.view.*;
import com.oracle.solaris.vp.util.misc.ChangeableAggregator;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.misc.property.*;
import com.oracle.solaris.vp.util.swing.ClippedBorder;
import com.oracle.solaris.vp.util.swing.SimpleCellRenderer;

/*
 * Dialog for advanced settings. The settings list varies
 * depending on a user or a role. The Roles settings are
 * shown only for the user, not for the role.
 */

public class AdvancedSettingsDialog implements ListSelectionListener {

    //
    // Static data
    //

    private JPanel cards;

    class SettingsRenderer extends SimpleCellRenderer<AdvancedSettings> {
    	public SettingsRenderer() {
	    super();
	}

	@Override
	public Icon getIcon(Component comp, AdvancedSettings value,
		boolean isSelected, boolean hasFocus) {

	    //
	    // Current Visual designer doesn't like any icons.
	    // If needed in future, just call return value.getIcon();

	    return (null);
	}

	public String getText(Component comp, AdvancedSettings value,
		boolean isSelected, boolean hasFocus) {
	    return (value.getLabel());
	}
    }

    //
    // Instance data
    //

    private ManagedObjectTableModel model;
    private UserMgrPanelDescriptor panelDesc;
    private JOptionPane pane;
    private JDialog dialog;
    private AdvancedSettings userSettings[] = {
    	new GroupsSettings(),
    	new RolesSettings(),
    	new RightsSettings(),
    	new AuthsSettings()
    };

    // Role doesn't have roles to assign
    private AdvancedSettings roleSettings[] = {
    	new GroupsSettings(),
    	new RightsSettings(),
    	new AuthsSettings()
    };

    private AdvancedSettings settingsList[];

    private AdvancedSettings curSettings;
    private UserManagedObject userObj;
    private boolean isRole;
    private String title = Finder.getString("usermgr.advanced.title");

    private MutableProperty<String> rightsProperty = new StringProperty();
    private MutableProperty<String> rolesProperty = new StringProperty();
    private MutableProperty<String> groupsProperty = new StringProperty();
    private MutableProperty<String> authsProperty = new StringProperty();


    //
    // Constructors
    //

    public AdvancedSettingsDialog(Component parent,
	    UserMgrPanelDescriptor panelDesc,
	    UserManagedObject userObj) {
        String utitle = title;
	this.userObj = userObj;
	if (panelDesc.isTypeRole()) {
	    settingsList = roleSettings;
	    isRole = true;
	} else {
	    settingsList = userSettings;
	    isRole = false;
	}
        pane = new JOptionPane(createForm(panelDesc),
		JOptionPane.PLAIN_MESSAGE,
		JOptionPane.OK_CANCEL_OPTION);
	UserMgrUtils.removeIcons(pane);
	String name = userObj.getUsername();
	if (name != null) {
	    utitle = title + " (" + userObj.getUsername() + ")";
	}
	// dialog = pane.createDialog(null, utitle);
	dialog = pane.createDialog(parent, utitle);
	dialog.setResizable(true);
    }

    /**
     * Populate various settings from the new user
     */
    public void setUser(UserManagedObject userObj) {
        this.userObj = userObj;
        String utitle = title;
	String name = userObj.getUsername();
	if (name != null) {
	    utitle = title + " (" + userObj.getUsername() + ")";
	}
	dialog.setTitle(utitle);

	for (int i = 0; i < settingsList.length; i++) {
		AdvancedSettings settings = settingsList[i];
		settings.setUser(userObj);
	}
    }

    /**
     * Show the dialog. Block until dismissed
     */
    public void show() {
    	dialog.setVisible(true);
    }

    /**
     * Create the main form/panel.
     */
    private JPanel createForm(UserMgrPanelDescriptor panelDesc) {
    	JPanel form = new JPanel(new BorderLayout());
    	cards = new JPanel(new CardLayout());
	JList list = new JList(settingsList);
	SettingsRenderer renderer = new SettingsRenderer();
	renderer.configureFor(list);
	list.setCellRenderer(renderer);
	list.addListSelectionListener(this);
	Border border = list.getBorder();
	list.setBorder(new ClippedBorder(border, false, true, true, true));
	JScrollPane scrollPane = new JScrollPane(list);

	scrollPane.setVerticalScrollBarPolicy(
		ScrollPaneConstants.VERTICAL_SCROLLBAR_AS_NEEDED);
	scrollPane.setHorizontalScrollBarPolicy(
		ScrollPaneConstants.HORIZONTAL_SCROLLBAR_AS_NEEDED);
	form.add(scrollPane, BorderLayout.WEST);
	for (int i = 0; i < settingsList.length; i++) {
		curSettings = settingsList[i];
		curSettings.init(panelDesc);
		curSettings.setUser(userObj);
		cards.add(curSettings.getPanel(), curSettings.getLabel());
	}
	list.setSelectedIndex(0);
	form.add(cards, BorderLayout.CENTER);
	form.setPreferredSize(new Dimension(700, 400));

    	return form;
    }

    public void valueChanged(ListSelectionEvent e) {
   	JList list = (JList) e.getSource();
   	curSettings = settingsList[list.getSelectedIndex()];
   	CardLayout cl = (CardLayout) cards.getLayout();
	cl.show(cards, curSettings.getLabel());
    }

    public int getValue() {
	Number n;
	int option;
	Object obj = pane.getValue();

	if (obj.getClass().getSuperclass() == Number.class) {
	    n = (Number) obj;
	    option = n.intValue();
	    return option;
	}

	return JOptionPane.CANCEL_OPTION;
    }

    /**
     * Find out if any of the settings is changed
     */
    public boolean isChanged() {
	for (int i = 0; i < settingsList.length; i++) {
	    if (settingsList[i].isChanged()) {
		return (true);
	    }
	}

    	return (false);
    }

    /**
     * Returns the type of user: role or normal user
     */
    public boolean isTypeRole() {
        return isRole;
    }

    /**
     * Update user object based on advanced settings
     */
    public void update() {
	for (int i = 0; i < settingsList.length; i++) {
	    settingsList[i].updateUser();
	}
    }
}
