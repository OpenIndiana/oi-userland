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

import java.awt.event.*;
import java.util.*;
import javax.swing.*;
import javax.swing.event.*;
import com.oracle.solaris.vp.panel.common.action.ActionFailedException;
import com.oracle.solaris.vp.panel.swing.view.ChangeIndicator;
import com.oracle.solaris.vp.panels.coreadm.client.swing.path.*;
import com.oracle.solaris.vp.util.misc.*;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.misc.property.*;
import com.oracle.solaris.vp.util.swing.*;
import com.oracle.solaris.vp.util.swing.layout.*;
import com.oracle.solaris.vp.util.swing.property.*;

@SuppressWarnings({"serial"})
public class CoreAdmOptionsPanel extends JPanel {

    //
    // Static data
    //

    private static final Map<Character, String> EXAMPLE_REPLACEMENTS =
	new HashMap<Character, String>();
    static {
	EXAMPLE_REPLACEMENTS.put(CoreUtil.FMT_DIR, "usr/bin");
	EXAMPLE_REPLACEMENTS.put(CoreUtil.FMT_FILE, "badapp");
	EXAMPLE_REPLACEMENTS.put(CoreUtil.FMT_GID, "10");
	EXAMPLE_REPLACEMENTS.put(CoreUtil.FMT_MACHINE, "i86pc");
	EXAMPLE_REPLACEMENTS.put(CoreUtil.FMT_NODE, "myhost");
	EXAMPLE_REPLACEMENTS.put(CoreUtil.FMT_PID, "1234");
	EXAMPLE_REPLACEMENTS.put(CoreUtil.FMT_TIME, "1200550605");
	EXAMPLE_REPLACEMENTS.put(CoreUtil.FMT_UID, "26147");
	EXAMPLE_REPLACEMENTS.put(CoreUtil.FMT_ZONE, "global");
	EXAMPLE_REPLACEMENTS.put(CoreUtil.FMT_PERCENT, "%");
    }

    //
    // Instance data
    //

    private ChangeableAggregator aggregator;
    private BooleanProperty enabledProp = new BooleanProperty();
    private StringProperty pathProp = new StringProperty();
    private BooleanProperty setIDProp = new BooleanProperty();
    private MutableProperty<Set<CoreConfig.ContentType>> contentsProp =
	new BasicMutableProperty<Set<CoreConfig.ContentType>>();

    //
    // Constructors
    //

    public CoreAdmOptionsPanel() {
	setOpaque(false);
	aggregator = new ChangeableAggregator();

	JCheckBox enabledCheckBox = new JCheckBox(Finder.getString(
	    "settings.scheme.custom.options.enabled"));
	new CheckBoxPropertySynchronizer(enabledProp, enabledCheckBox);
	ChangeIndicator enabledChange = new ChangeIndicator();
	enabledProp.addChangeListener(enabledChange);
	aggregator.addChangeables(enabledProp);

	JLabel pathLabel = new JLabel(Finder.getString(
	    "settings.scheme.custom.options.path"));
	final JTextPane pathField = new PathField();
	new TextComponentPropertySynchronizer<String, JTextPane>(
	    pathProp, pathField);
	JScrollPane pathScroll = new TextPaneScrollPane(pathField);

	final JComboBox pathCombo = new TokenComboBox();
	pathCombo.setOpaque(false);
	pathCombo.addActionListener(
	    new ActionListener() {
		@Override
		public void actionPerformed(ActionEvent e) {
		    String token = (String)pathCombo.getSelectedItem();
		    if (token != null) {
			pathField.replaceSelection(token);
		    }
		    pathField.requestFocusInWindow();
		}
	    });

	RowLayout rowLayout = new RowLayout(HorizontalAnchor.FILL);
	JPanel pathPanel = new JPanel(rowLayout);
	pathPanel.setOpaque(false);
	RowLayoutConstraint r = new RowLayoutConstraint(
	    VerticalAnchor.CENTER, GUIUtil.getHalfGap(), 1);
	pathPanel.add(pathScroll, r);
	pathPanel.add(pathCombo, r.setWeight(0));

	ChangeIndicator pathChange = new ChangeIndicator();
	pathProp.addChangeListener(pathChange);
	aggregator.addChangeables(pathProp);

	JLabel exampleLabel = new JLabel(Finder.getString(
	    "settings.scheme.custom.options.example"));
	final String emptyExample = Finder.getString(
	    "settings.scheme.custom.options.example.blank");
	final JLabel exampleField = new JLabel();
	ChangeListener pathListener =
	    new ChangeListener() {
		@Override
		public void stateChanged(ChangeEvent e) {
		    String example = emptyExample;
		    String path = pathField.getText();
		    if (!path.isEmpty())
			example = CoreUtil.mapPath(EXAMPLE_REPLACEMENTS, path);

		    exampleField.setText(example);
		}
	    };
	pathProp.addChangeListener(pathListener);

	// Initialize
	pathListener.stateChanged(null);

	JCheckBox setIDCheckBox = new JCheckBox(Finder.getString(
	    "settings.scheme.custom.options.setid"));
	new CheckBoxPropertySynchronizer(setIDProp, setIDCheckBox);
	ChangeIndicator setIDChange = new ChangeIndicator();
	setIDProp.addChangeListener(setIDChange);
	aggregator.addChangeables(setIDProp);

	JLabel contentsLabel = new JLabel(Finder.getString(
	    "settings.scheme.custom.options.contents"));
	ListSelector contentsSelector = createContentsSelector();

	new NVListSelectorPropertySynchronizer<CoreConfig.ContentType>(
	    contentsProp, contentsSelector, false);

	ChangeIndicator contentsChange = new ChangeIndicator();
	contentsProp.addChangeListener(contentsChange);
	aggregator.addChangeables(contentsProp);

	Form form = new Form(this, VerticalAnchor.TOP);

	int gap = GUIUtil.getHalfGap();

	ColumnLayoutConstraint c = new ColumnLayoutConstraint(
	    HorizontalAnchor.FILL, gap);

	SimpleHasAnchors a = new SimpleHasAnchors(
	    HorizontalAnchor.LEFT, VerticalAnchor.CENTER);

	form.addTable(3, gap, gap, HorizontalAnchor.LEFT, c);

	form.add(enabledChange, a);
	form.add(new Spacer(), a);
	form.add(enabledCheckBox, a);

	form.add(pathChange, a);
	form.add(pathLabel, a);
	form.add(pathPanel, a);

	form.add(new Spacer(), a);
	form.add(exampleLabel, a);
	form.add(exampleField, a);

	form.add(setIDChange, a);
	form.add(new Spacer(), a);
	form.add(setIDCheckBox, a);

	form.add(contentsChange, a.setVerticalAnchor(VerticalAnchor.TOP));
	form.add(contentsLabel, a);
	form.add(contentsSelector, a);
    }

    //
    // CoreAdmOptionsPanel methods
    //

    public ListSelector createContentsSelector() {
	String leftLabel = Finder.getString(
	    "settings.scheme.custom.options.contents.available");

	String rightLabel = Finder.getString(
	    "settings.scheme.custom.options.contents.selected");

	DefaultListModel leftModel = new SortedListModel();
	DefaultListModel rightModel = new SortedListModel();

	for (CoreConfig.ContentType value : CoreConfig.ContentType.values()) {
	    DefaultListModel model =
		CoreConfig.CONTENT_DEFAULT.contains(value) ?
		rightModel : leftModel;

	    model.addElement(new NameValue<CoreConfig.ContentType>(
		value.getName(), value));
	}

	ListSelector selector = new ListSelector(
	    leftModel, rightModel, leftLabel, rightLabel);

	selector.setOpaque(false);
	selector.setWidestCellAsPrototype();

	return selector;
    }

    public ChangeableAggregator getChangeableAggregator() {
	return aggregator;
    }

    public BooleanProperty getEnabledProp() {
	return enabledProp;
    }

    public StringProperty getPathProp() {
	return pathProp;
    }

    public BooleanProperty getSetIDProp() {
	return setIDProp;
    }

    public MutableProperty<Set<CoreConfig.ContentType>> getContentsProp() {
	return contentsProp;
    }

    void init(CoreConfig.ScopeConfig savedconfig, CoreConfig.ScopeConfig config)
    {
	enabledProp.setValue(config.getEnabled());
	enabledProp.setSavedValue(savedconfig.getEnabled());

	setIDProp.setValue(config.getSetid());
	setIDProp.setSavedValue(savedconfig.getSetid());

	pathProp.setValue(config.getPattern());
	pathProp.setSavedValue(savedconfig.getPattern());

	contentsProp.setValue(config.getContent());
	contentsProp.setSavedValue(savedconfig.getContent());
    }

    CoreConfig.ScopeConfig getConfig(boolean global)
	throws ActionFailedException
    {
	String path = pathProp.getValue();
	boolean enabled = enabledProp.getValue();
	boolean empty = path.isEmpty();

	/*
	 * The system could have already been configured incorrectly.
	 * Only complain if an incorrect configuration was due to the
	 * user's changes.
	 */
	if (global && !empty && !path.startsWith("/") &&
	    pathProp.isChanged())
	    throw (new ActionFailedException(
		Finder.getString("error.coreadm.custom.global.absolute")));

	if (empty && enabled &&
	    (pathProp.isChanged() || enabledProp.isChanged()))
	    throw (new ActionFailedException(Finder.getString(global ?
		"error.coreadm.custom.global.empty" :
		"error.coreadm.custom.process.empty")));

	/*
	 * EnumSet.copyOf() fails if the original isn't an EnumSet and is
	 * empty... so we have to go the long way around.
	 */
	EnumSet<CoreConfig.ContentType> types =
	    EnumSet.noneOf(CoreConfig.ContentType.class);
	types.addAll(contentsProp.getValue());
	return (new CoreConfig.ScopeConfig(types, path, enabled,
	    setIDProp.getValue()));
    }
}
