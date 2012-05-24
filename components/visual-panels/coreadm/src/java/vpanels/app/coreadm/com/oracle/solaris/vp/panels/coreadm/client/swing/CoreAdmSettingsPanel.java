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

package com.oracle.solaris.vp.panels.coreadm.client.swing;

import java.awt.*;
import java.util.*;
import javax.swing.*;
import javax.swing.border.Border;
import com.oracle.solaris.vp.panel.swing.view.ChangeIndicator;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.misc.property.*;
import com.oracle.solaris.vp.util.swing.*;
import com.oracle.solaris.vp.util.swing.layout.*;

@SuppressWarnings({"serial"})
public class CoreAdmSettingsPanel extends SettingsPanel {
    //
    // Instance data
    //

    private MutableProperty<CoreConfig> configProperty;
    private JButton customEditButton;

    //
    // Constructors
    //

    public CoreAdmSettingsPanel() {
	JPanel form = createForm();
	setContent(form);
    }

    //
    // CoreAdmSettingsPanel methods
    //

    protected JPanel createForm() {
	JPanel mainForm = createMainForm();
	ChangeIndicator choiceChange = new ChangeIndicator();
	configProperty.addChangeListener(choiceChange);

	JPanel formPanel = new JPanel();
	formPanel.setOpaque(false);

	formPanel.setLayout(new RowLayout());

	int hGap = GUIUtil.getHalfGap();

	RowLayoutConstraint r = new RowLayoutConstraint(
	    VerticalAnchor.TOP, hGap);
	r.setLayoutIfInvisible(true);

	formPanel.add(choiceChange, r);
	formPanel.add(mainForm, r);

	return formPanel;
    }

    protected JPanel createMainForm() {
	JPanel formPanel = new JPanel();
	formPanel.setOpaque(false);

	String title = Finder.getString("settings.scheme.title");
	Border empty = GUIUtil.getEmptyHalfBorder();
	Border titled = BorderFactory.createTitledBorder(title);
	Border compound = BorderFactory.createCompoundBorder(titled, empty);
	formPanel.setBorder(compound);

	Form form = new Form(formPanel, VerticalAnchor.TOP);

	int hGap = GUIUtil.getHalfGap();
	int vGap = GUIUtil.getGap();

	ColumnLayoutConstraint c = new ColumnLayoutConstraint(
	    HorizontalAnchor.FILL, vGap);

	RowLayoutConstraint r = new RowLayoutConstraint(
	    VerticalAnchor.TOP, hGap);
	r.setLayoutIfInvisible(true);

	AbstractButton custom = null;
	Map<AbstractButton, CoreConfig> map =
	    new HashMap<AbstractButton, CoreConfig>();

	for (CoreScheme choice : CoreScheme.values()) {
	    String resource =
		"settings.scheme." + choice.toString().toLowerCase();
	    String option = Finder.getString(resource);
	    String caption = Finder.getString(resource + ".caption");

	    AbstractButton button = new JRadioButton(option);
	    if (choice == CoreScheme.CUSTOM) {
		custom = button;
	    }
	    map.put(button, choice.getConfig());

	    form.addRow(HorizontalAnchor.LEFT, c);
	    form.add(button, r);

	    if (caption != null) {
		int indent = GUIUtil.getTextXOffset(button);
		JLabel label = new JLabel(caption);

		Font bFont = button.getFont();
		float size = bFont.getSize() * .85f;
		Font lFont = bFont.deriveFont(size);
		label.setFont(lFont);

		form.addRow(HorizontalAnchor.LEFT, c.clone().setGap(0));
		form.add(label,
		    r.clone().setGap(indent).setIgnoreFirstGap(false));
	    }
	}

	assert custom != null;
	configProperty = new BasicMutableProperty<CoreConfig>();
	new CustomizedChoicePropertySynchronizer<CoreConfig>(configProperty,
	    map, custom);
	getChangeableAggregator().addChangeables(configProperty);

	customEditButton = new JButton(Finder.getString(
	    "settings.scheme.custom.edit"));
        form.addRow(HorizontalAnchor.RIGHT, c);
	form.add(customEditButton, r);

	return formPanel;
    }

    public MutableProperty<CoreConfig> getConfigProperty() {
	return configProperty;
    }

    public JButton getCustomEditButton() {
	return customEditButton;
    }

    public void init(CoreAdmPanelDescriptor descriptor) {
	// Sanity check -- the UI should be updated only on the event thread
	assert EventQueue.isDispatchThread();

	configProperty.setValue(descriptor.getCoreConfig());
	configProperty.save();
    }
}
