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

package com.oracle.solaris.vp.util.swing;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;
import com.oracle.solaris.vp.util.misc.*;
import com.oracle.solaris.vp.util.swing.layout.*;

/**
 * The {@code SettingsPanel} class provides a skeleton for many UI panels.  Its
 * structure follows:
 * <p/>
 * <pre>
 * +-+-----------------------------------------+-+
 * | +-----------------------------------------+ |
 * | | {@link #getTitlePane Title pane}                              | |
 * | +-----------------------------------------+ |
 * | +-----------------------------------------+ |
 * | | {@link #getHelpPane Help pane}                               | |
 * | +-----------------------------------------+ |
 * | +-----------------------------------------+ |
 * | | {@link #getContentPane Content pane}                            | |
 * | +-----------------------------------------+ |
 * | +-----------------------------------------+ |
 * | | {@link #getButtonBar Button bar}                              | |
 * | +-----------------------------------------+ |
 * +-+-----------------------------------------+-+
 * </pre>
 * <p/>
 * Each component is added as part of a {@link ColumnLayout}, so
 * ColumnConstraint attributes for each of the components can be changed as
 * needed.  For example:
 * <pre>
 *     // Remove the spacing between the help and content panes
 *     ColumnLayoutConstraint constraint =
 *	   getLayout().getConstraint(getContentPane());
 *     constraint.setGap(0);
 * </pre>
 */
@SuppressWarnings({"serial"})
public class SettingsPanel extends JPanel {
    //
    // Inner classes
    //

    /**
     * AbstractAction that determines its enabledness based on whether its
     * button is non-null and it and its descendents are all visible.  This is
     * necessary so that the "submit" and "cancel" keybindings can be propagated
     * up the Component hierarchy if they don't apply.
     */
    protected abstract static class ButtonAction extends AbstractAction {
	//
	// ActionListener methods
	//

	@Override
	public void actionPerformed(ActionEvent e) {
	    AbstractButton button = getFirstVisibleButton();
	    if (button != null) {
		button.doClick(0);
	    }
	}

	//
	// Action methods
	//

	@Override
	public boolean isEnabled() {
	    return super.isEnabled() && getFirstVisibleButton() != null;
	}

	//
	// ButtonAction methods
	//

	public abstract AbstractButton[] getButtons();

	//
	// Private methods
	//

	private AbstractButton getFirstVisibleButton() {
	    BUTTONS: for (AbstractButton button : getButtons()) {
		if (button != null) {
		    for (Component c = button; c != null; c = c.getParent()) {
			if (!c.isVisible()) {
			    continue BUTTONS;
			}
		    }
		    return button;
		}
	    }
	    return null;
	}
    }

    //
    // Instance data
    //

    private ChangeableAggregator aggregator;
    private AutoHidePanel titlePane;
    private JLabel titleLabel;
    private AutoHidePanel helpPane;
    private JTextArea helpField;
    private AutoHidePanel contentPane;
    private SettingsButtonBar buttonBar;
    private AbstractButton[] cancelButtons;
    private AbstractButton[] submitButtons;

    //
    // Constructors
    //

    public SettingsPanel() {
	int gap = GUIUtil.getGap();

	helpField = new FlowTextArea();
	AutoHideTextArea.autoHide(helpField);

	helpPane = new AutoHidePanel();
	helpPane.setOpaque(false);
	helpPane.setLayout(new BorderLayout());
	helpPane.add(helpField, BorderLayout.CENTER);

	titleLabel = new AutoHideLabel();
	decorateTitle(titleLabel);
	titlePane = new AutoHidePanel();
	titlePane.setOpaque(false);
	titlePane.setLayout(new BorderLayout());
	titlePane.add(titleLabel, BorderLayout.CENTER);

	contentPane = new AutoHidePanel();
	contentPane.setLayout(new BorderLayout());
	contentPane.setOpaque(false);

	buttonBar = new SettingsButtonBar();

	ChangeListener listener =
	    new ChangeListener() {
		@Override
		public void stateChanged(ChangeEvent e) {
		    buttonBar.setChanged(aggregator.isChanged());
		}
	    };

	aggregator = new ChangeableAggregator(DebugUtil.toBaseName(this));
	aggregator.addChangeListener(listener);

	// Initialize
	listener.stateChanged(null);

	setOpaque(false);

	ColumnLayoutConstraint c = new ColumnLayoutConstraint(
	    HorizontalAnchor.FILL, gap);

	ColumnLayout layout = new ColumnLayout(VerticalAnchor.FILL);
	layout.setDefaultConstraint(c);
	setLayout(layout);

	add(titlePane, c);
	add(helpPane, c);
	add(contentPane, c.clone().setWeight(1));
	add(buttonBar, c);

	// Hitting enter anywhere in panel should submit it
	setSubmitButtons(buttonBar.getApplyButton(), buttonBar.getOkayButton(),
	    buttonBar.getForwardButton(), buttonBar.getCloseButton());
	KeyStroke enter = KeyStroke.getKeyStroke(KeyEvent.VK_ENTER, 0);
	String actName = "submit";
	getInputMap(JComponent.WHEN_ANCESTOR_OF_FOCUSED_COMPONENT).put(
	    enter, actName);
	getActionMap().put(actName,
	    new ButtonAction() {
		@Override
		public AbstractButton[] getButtons() {
		    return getSubmitButtons();
		}
	    });

	// Hitting escape anywhere in panel should cancel it
	setCancelButtons(buttonBar.getCancelButton(),
	    buttonBar.getCloseButton());
	KeyStroke escape = KeyStroke.getKeyStroke(KeyEvent.VK_ESCAPE, 0);
	actName = "cancel";
	getInputMap(JComponent.WHEN_ANCESTOR_OF_FOCUSED_COMPONENT).put(
	    escape, actName);
	getActionMap().put(actName,
	    new ButtonAction() {
		@Override
		public AbstractButton[] getButtons() {
		    return getCancelButtons();
		}
	    });
    }

    //
    // Container methods
    //

    @Override
    public ColumnLayout getLayout() {
	return (ColumnLayout)super.getLayout();
    }

    //
    // SettingsPanel methods
    //

    /**
     * Decorates the given label as a section title.
     * <p/>
     * This default implementation makes the font bold.
     */
    protected void decorateTitle(JLabel label) {
	label.setFont(label.getFont().deriveFont(Font.BOLD));
    }

    /**
     * Gets the button bar for this {@code SettingsPanel}.  The button bar is
     * initialized to be non-opaque.
     * <p/>
     * The button bar is invisible initially, but is made visible when an {@code
     * Action} is added to it.	See {@link SettingsButtonBar}.
     */
    public SettingsButtonBar getButtonBar() {
	return buttonBar;
    }

    /**
     * Gets the buttons to be examined whenever {@code Escape} is pressed
     * anywhere inside this {@code SettingsPanel}.  The first button that is
     * part of a fully-visible component hierarchy will be clicked.
     * <p/>
     * This value is initialized with the {@link #getButtonBar button bar}'s
     * cancel and close buttons.
     *
     * @return	    the buttons to be examined
     */
    public AbstractButton[] getCancelButtons() {
	return cancelButtons;
    }

    /**
     * Gets the content pane for this {@code SettingsPanel}.  The content pane
     * is initialized to be non-opaque with a {@code BorderLayout}.
     */
    public AutoHidePanel getContentPane() {
	return contentPane;
    }

    public ChangeableAggregator getChangeableAggregator() {
	return aggregator;
    }

    /**
     * Gets the {@code JTextField} initially contained in the {@link
     * #getHelpPane help pane}.  Setting the text of this {@code JTextField}
     * automatically sets its visibility (visible if non-{@code null}, invisible
     * otherwise).
     */
    public JTextArea getHelpField() {
	return helpField;
    }

    /**
     * Gets the help pane for this {@code SettingsPanel}.  The help pane is
     * initialized to be non-opaque with a {@code BorderLayout}, containing a
     * {@link #getHelpField JTextArea}.
     * <p/>
     * The help pane is invisible initially since it may not be needed.  Setting
     * the text in the {@link #getHelpField help field} will make it visible
     * automatically.
     */
    public AutoHidePanel getHelpPane() {
	return helpPane;
    }

    /**
     * Gets the buttons to be examined whenever {@code Escape} is pressed
     * anywhere inside this {@code SettingsPanel}.  The first button that is
     * part of a fully-visible component hierarchy will be clicked.
     * <p/>
     * This value is initialized with the {@link #getButtonBar button bar}'s
     * apply, okay, forward, and close buttons.
     *
     * @return	    the buttons to be examined
     */
    public AbstractButton[] getSubmitButtons() {
	return submitButtons;
    }

    /**
     * Gets the {@code JLabel} initially contained in the {@link #getTitlePane
     * title pane}.  Setting the icon or text of this {@code JLabel}
     * automatically sets its visibility (visible if either is non-{@code null},
     * invisible otherwise).
     */
    public JLabel getTitleLabel() {
	return titleLabel;
    }

    /**
     * Gets the title pane for this {@code SettingsPanel}.  The title pane is
     * initialized to be non-opaque with a {@code BorderLayout}, containing a
     * {@link #getTitleLabel JLabel}.
     * <p/>
     * The title pane is invisible initially since it may not be needed.
     * Setting the text/icon in the {@link #getTitleLabel title label} will make
     * it visible automatically.
     */
    public AutoHidePanel getTitlePane() {
	return titlePane;
    }

    /**
     * Sets the buttons to be examined whenever {@code Escape} is pressed
     * anywhere inside this {@code SettingsPanel}.  The first button that is
     * part of a fully-visible component hierarchy will be clicked.
     *
     * @param	    cancelButtons
     *		    the buttons to be examined
     */
    public void setCancelButtons(AbstractButton... cancelButtons) {
	this.cancelButtons = cancelButtons;
    }

    public void setContent(Component content) {
	setContent(content, true, false);
    }

    public void setContent(Component content, boolean center, boolean scroll) {
	contentPane.removeAll();

	if (content != null) {
	    if (center) {
		ColumnLayout layout = new ColumnLayout(VerticalAnchor.CENTER);
		JPanel centered = new JPanel(layout);
		centered.setOpaque(false);

		ColumnLayoutConstraint c =
		    new ColumnLayoutConstraint(HorizontalAnchor.CENTER);

		centered.add(content, c);
		content = centered;
	    }

	    if (scroll) {
		ExtScrollPane scrollPane = new ExtScrollPane(content);
		scrollPane.removeBorder();
		scrollPane.setOpaque(false);
		content = scrollPane;
	    }

	    contentPane.setLayout(new BorderLayout());
	    contentPane.add(content, BorderLayout.CENTER);
	}
    }

    /**
     * Sets the buttons to be examined whenever {@code Escape} is pressed
     * anywhere inside this {@code SettingsPanel}.  The first button that is
     * part of a fully-visible component hierarchy will be clicked.
     *
     * @param	    submitButtons
     *		    the buttons to be examined
     */
    public void setSubmitButtons(AbstractButton... submitButtons) {
	this.submitButtons = submitButtons;
    }
}
