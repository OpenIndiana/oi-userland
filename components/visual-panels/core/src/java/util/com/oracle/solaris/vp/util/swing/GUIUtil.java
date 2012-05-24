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
import java.io.IOException;
import java.lang.reflect.InvocationTargetException;
import java.util.*;
import java.util.List;
import javax.swing.*;
import javax.swing.border.Border;
import com.oracle.solaris.vp.util.misc.*;
import com.oracle.solaris.vp.util.misc.finder.Finder;

public class GUIUtil {
    //
    // Inner classes
    //

    public static interface HasMnemonic {
	String getText();

	void setMnemonic(int i);

	void setMnemonicIndex(int i);

	void setText(String text);
    }

    public static class MnemonicAction implements HasMnemonic {
	//
	// Instance data
	//

	private Action action;

	//
	// Constructors
	//

	public MnemonicAction(Action action) {
	    this.action = action;
	}

	//
	// HasMnemonic methods
	//

	@Override
	public String getText() {
	    Object text = action.getValue(Action.NAME);
	    return text == null ? null : text.toString();
	}

	@Override
	public void setMnemonic(int i) {
	    action.putValue(Action.MNEMONIC_KEY, i);
	}

	@Override
	public void setMnemonicIndex(int i) {
	    action.putValue(Action.DISPLAYED_MNEMONIC_INDEX_KEY, i);
	}

	@Override
	public void setText(String text) {
	    action.putValue(Action.NAME, text);
	}

	//
	// MnemonicAction methods
	//

	public Action getAction() {
	    return action;
	}
    }

    public static class MnemonicButton implements HasMnemonic {
	//
	// Instance data
	//

	private AbstractButton button;

	//
	// Constructors
	//

	public MnemonicButton(AbstractButton button) {
	    this.button = button;
	}

	//
	// HasMnemonic methods
	//

	@Override
	public String getText() {
	    return button.getText();
	}

	@Override
	public void setMnemonic(int i) {
	    button.setMnemonic(i);
	}

	@Override
	public void setMnemonicIndex(int i) {
	    button.setDisplayedMnemonicIndex(i);
	}

	@Override
	public void setText(String text) {
	    button.setText(text);
	}

	//
	// MnemonicButton methods
	//

	public AbstractButton getButton() {
	    return button;
	}
    }

    public static class MnemonicLabel implements HasMnemonic {
	//
	// Instance data
	//

	private JLabel label;

	//
	// Constructors
	//

	public MnemonicLabel(JLabel label) {
	    this.label = label;
	}

	//
	// HasMnemonic methods
	//

	@Override
	public String getText() {
	    return label.getText();
	}

	@Override
	public void setMnemonic(int i) {
	    label.setDisplayedMnemonic(i);
	}

	@Override
	public void setMnemonicIndex(int i) {
	    label.setDisplayedMnemonicIndex(i);
	}

	@Override
	public void setText(String text) {
	    label.setText(text);
	}

	//
	// MnemonicLabel methods
	//

	public JLabel getLabel() {
	    return label;
	}
    }

    //
    // Static data
    //

    public static final Border BORDER_LINE =
	BorderFactory.createLineBorder(Color.GRAY, 1);

    public static final String PROPERTY_COMPONENT_SPACING =
	"toolkit.component.spacing";

    public static final String PROPERTY_BUTTON_SPACING =
	"toolkit.button.spacing";

    public static final TypedPropertiesWrapper prefs =
	new TypedPropertiesWrapper();

    static {
	try {
	    Properties defaultPrefs = new Properties();
	    defaultPrefs.load(
		Finder.getResource("runtime.properties").openStream());
	    prefs.getPropertiesList().add(defaultPrefs);
	} catch (IOException e) {
	    // Unlikely -- the resource should always exist and be accessible
	}
    }

    //
    // Static methods
    //

    /**
     * Adds the given {@code AWTKeyStroke}s to the given {@code Component}'s
     * list of focus traversal keys.
     *
     * @param	    comp
     *		    the {@code Component}
     *
     * @param	    forward
     *		    {@code true} to make {@code keyStrokes} traverse forward,
     *		    {@code false} to traverse backward
     *
     * @param	    keyStrokes
     *		    the {@code AWTKeyStroke}s
     */
    public static void addFocusTraversalKeys(Component comp, boolean forward,
	AWTKeyStroke... keyStrokes) {
	modifyFocusTraversalKeys(comp, forward, true, keyStrokes);
    }

    public static void adjustForMnemonic(HasMnemonic obj) {
	String text = obj.getText();
	String[] groups = TextUtil.match(text, "(.*?)_(([a-zA-Z0-9]).*)");
	if (groups != null) {
	    obj.setText(groups[1] + groups[2]);

	    String mnemonic = groups[3].toUpperCase();
	    KeyStroke mnemonicKey = KeyStroke.getKeyStroke(mnemonic);

	    if (mnemonicKey != null) {
		int mnemonicKeyCode = mnemonicKey.getKeyCode();
		obj.setMnemonic(mnemonicKeyCode);
		obj.setMnemonicIndex(groups[1].length());
	    }
	}
    }

    public static void adjustForMnemonic(Action action) {
	adjustForMnemonic(new MnemonicAction(action));
    }

    public static void adjustForMnemonic(AbstractButton button) {
	adjustForMnemonic(new MnemonicButton(button));
    }

    public static void adjustForMnemonic(JLabel label) {
	adjustForMnemonic(new MnemonicLabel(label));
    }

    public static Border createCompoundBorder(Border... borders) {
	Border border = null;
	for (int i = 0; i < borders.length; i++) {
	    border = i == 0 ? borders[i] :
		BorderFactory.createCompoundBorder(border, borders[i]);
	}
	return border;
    }

    /**
     * Creates and returns a JTextField of the {@link #getTextFieldWidth default
     * width}.
     */
    public static JTextField createTextField() {
	return new JTextField(getTextFieldWidth());
    }

    /**
     * Get the default spacing between buttons, as on a toolbar.
     */
    public static int getButtonGap() {
	return prefs.getInt("toolkit.button.spacing");
    }

    /**
     * Get the default height for button icons.
     */
    public static int getButtonIconHeight() {
	return prefs.getInt("toolkit.button.icon.height");
    }

    public static String getClippedString(
	String text, FontMetrics metrics, int width) {

	if (text == null) {
	    return text;
	}

	int sWidth = metrics.stringWidth(text);
	if (sWidth <= width) {
	    return text;
	}

	String ellipsis = "...";
	width -= metrics.stringWidth(ellipsis);
	char[] chars = text.toCharArray();

	int i;
	for (i = chars.length - 1; i >= 0 && sWidth > width; i--) {
	    sWidth -= metrics.charWidth(chars[i]);
	}

	return text.substring(0, i + 1) + ellipsis;
    }

    public static Border getEmptyBorder() {
	int gap = getGap();
	return BorderFactory.createEmptyBorder(gap, gap, gap, gap);
    }

    public static Border getEmptyHalfBorder() {
	int gap = getHalfGap();
	return BorderFactory.createEmptyBorder(gap, gap, gap, gap);
    }

    /**
     * Gets an icon for the given message type.  An attempt will first be made
     * to retrieve a look-and-feel-specific icon from the {@code JOptionPane}
     * class.  However, some looks and feels (like GTK) don't expose these icons
     * via the API; in this case local defaults will be returned.
     *
     * @param	    messageType
     *		    JOptionPane.ERROR_MESSAGE,
     *		    JOptionPane.INFORMATION_MESSAGE,
     *		    JOptionPane.WARNING_MESSAGE, or
     *		    JOptionPane.QUESTION_MESSAGE.
     *
     * @return	    an {@code Icon}, or {@code null} if no icon could be found
     *		    for the given message type
     */
    public static Icon getIcon(int messageType) {
	Icon icon = null;

	switch (messageType) {
	    case JOptionPane.ERROR_MESSAGE:
		icon = UIManager.getIcon("OptionPane.errorIcon");
		if (icon == null) {
		    icon = Finder.getIcon("images/dialog/dialog-error.png");
		}
		break;


	    case JOptionPane.INFORMATION_MESSAGE:
		icon = UIManager.getIcon("OptionPane.informationIcon");
		if (icon == null) {
		    icon = Finder.getIcon(
			"images/dialog/dialog-information.png");
		}
		break;

	    case JOptionPane.WARNING_MESSAGE:
		icon = UIManager.getIcon("OptionPane.warningIcon");
		if (icon == null) {
		    icon = Finder.getIcon(
			"images/dialog/dialog-warning.png");
		}
		break;

	    case JOptionPane.QUESTION_MESSAGE:
		icon = UIManager.getIcon("OptionPane.questionIcon");
		if (icon == null) {
		    icon = Finder.getIcon(
			"images/dialog/dialog-question.png");
		}
		break;
	}

	return icon;
    }

    /**
     * Get the default spacing between components.
     */
    public static int getGap() {
	return prefs.getInt("toolkit.component.spacing");
    }

    public static int getHalfGap() {
	return getGap() / 2;
    }

    /**
     * Get the default height for menu icons.
     */
    public static int getMenuIconHeight() {
	return prefs.getInt("toolkit.menu.icon.height");
    }

    /**
     * Gets the preferred size of the given {@code Window}.  If the given {@code
     * Window} is a {@code JFrame} or a {@code JDialog}, and its glass pane is
     * visible, the glass pane's preferred size will be accounted for as well
     * ({@code Window.getPreferredSize} does not take the glass pane into
     * consideration).
     */
    public static Dimension getPreferredSize(Window window) {
	Dimension pSize = window.getPreferredSize();

	Component glass = null;
	Component content = null;

	if (window instanceof JFrame) {
	    JFrame frame = (JFrame)window;
	    glass = frame.getGlassPane();
	    content = frame.getContentPane();
	} else if (window instanceof JDialog) {
	    JDialog dialog = (JDialog)window;
	    glass = dialog.getGlassPane();
	    content = dialog.getContentPane();
	}

	if (glass != null && glass.isVisible()) {
	    Dimension cpSize = content.getPreferredSize();
	    content.setPreferredSize(glass.getPreferredSize());

	    Dimension newPSize = window.getPreferredSize();

	    pSize.width = Math.max(pSize.width, newPSize.width);
	    pSize.height = Math.max(pSize.height, newPSize.height);

	    // Restore previous preferred size, if any
	    content.setPreferredSize(cpSize);
	}

	return pSize;
    }

    /**
     * Get the default scroll unit increment.
     */
    public static int getScrollableUnitIncrement() {
	return prefs.getInt("toolkit.scroll.increment.unit");
    }

    /**
     * Get the default width for a textfield.
     */
    public static int getTextFieldWidth() {
	return prefs.getInt("toolkit.textfield.width");
    }

    public static int getTextXOffset(AbstractButton c) {
	int xoffset = c.getPreferredSize().width;

	Border b = c.getBorder();
	if (b != null) {
	    xoffset -= b.getBorderInsets(c).right;
	}

//	Insets m = c.getMargin();
//	if (m != null) {
//	    xoffset -= m.right;
//	}

	String text = c.getText();
	if (text != null) {
	    xoffset -= c.getFontMetrics(c.getFont()).stringWidth(text);
	}

	return xoffset;
    }

    public static Border getTitledBorder(String title) {
	return BorderFactory.createCompoundBorder(
	    BorderFactory.createTitledBorder(
	    BorderFactory.createEtchedBorder(), title), getEmptyBorder());
    }

    /**
     * Get the default margin for toolbar buttons.
     */
    public static int getToolBarButtonMargin() {
	return prefs.getInt("toolkit.toolbar.button.margin");
    }

    public static TypedPropertiesWrapper getUIPreferences() {
	return prefs;
    }

    /**
     * Get the default vertical spacing between a label and its {@code
     * Component} below it.
     */
    public static int getVerticalLabelGap() {
	return prefs.getInt("toolkit.vertical.label.spacing");
    }

    /**
     * Grows the given {@code Window} if its preferred size exceeds its actual
     * size.  Will not shrink the {@code Window}.
     */
    public static void growIfNecessary(Window window) {
	Dimension size = window.getSize();
	Dimension pSize = getPreferredSize(window);

	window.setSize(Math.max(size.width, pSize.width),
	    Math.max(size.height, pSize.height));
    }

    public static void installKeyBinding(JComponent c, int condition,
	String actionName, Action action, KeyStroke... keyStrokes) {

	InputMap iMap = c.getInputMap(condition);
	ActionMap aMap = c.getActionMap();

	for (KeyStroke keyStroke : keyStrokes) {
	    iMap.put(keyStroke, actionName);
	    aMap.put(actionName, action);
	}
    }

    public static void installKeyBinding(JComponent c, int condition,
	String actionName, Action action, int... keyStrokes) {

	KeyStroke[] array = new KeyStroke[keyStrokes.length];
	for (int i = 0; i < array.length; i++) {
	    array[i] = KeyStroke.getKeyStroke(keyStrokes[i], 0);
	}

	installKeyBinding(c, condition, actionName, action, array);
    }

    /**
     * Invokes the given {@code Runnable} on the AWT event dispatching thread
     * (which could be the current thread).  This addresses two
     * disadvantages/annoyances to {@code EventQueue.invokeAndWait}:
     * <ol>
     *	 <li>
     *	   Any {@code RuntimeException}s or {@code Error}s thrown by the given
     *	   {@code Runnable} are thrown in the current thread, rather than as an
     *	   {@code InvocationTargetException}.
     *	 </li>
     *	 <li>
     *	   If the AWT event dispatching thread is interrupted while the given
     *	   {@code Runnable} is running, it will be re-run until it completes.
     *	   If this behavior is not desired, the given {@code Runnable} should
     *	   account for this possibility.
     *	 </li>
     * <ol>
     *
     * @param	    runnable
     *		    a {@code Runnable} to run
     */
    public static void invokeAndWait(final Runnable runnable) {
	if (EventQueue.isDispatchThread()) {
	    runnable.run();
	} else {
	    while (true) {
		try {
		    EventQueue.invokeAndWait(runnable);
		    break;
		} catch (InvocationTargetException e) {
		    Throwable cause = e.getCause();
		    ThrowableUtil.appendStackTrace(cause);

		    if (cause instanceof RuntimeException) {
			throw (RuntimeException)cause;
		    }

		    if (cause instanceof Error) {
			throw (Error)cause;
		    }

		    // It should not be possible to be here -- any Throwable
		    // thrown by run() should have been a RunTimeException or an
		    // Error, since run throws no checked Exceptions.
		    assert (false);
		} catch (InterruptedException e) {
		    // Not bloody likely
		}
	    }
	}
    }

    /**
     * See {@link #invokeAndWait(java.lang.Runnable)}.
     *
     * @return	    the returned object of the given {@code TypedRunnable}
     */
    public static <T> T invokeAndWait(final TypedRunnable<T> runnable) {
	final List<T> t = new ArrayList<T>(1);

	invokeAndWait(
	    new Runnable() {
		@Override
		public void run() {
		    t.add(runnable.run());
		}
	    });

	return t.get(0);
    }

    public static boolean isModifierKeyPressed(InputEvent e) {
	return e.isShiftDown() || e.isControlDown() || e.isAltDown() ||
	    e.isMetaDown() || e.isAltGraphDown();
    }

    /**
     * Returns {@code true} if the given {@code MouseEvent} represents a mouse
     * click with the given number of clicks, button 1, with no modifier keys
     * pressed, or {@code false} otherwise.
     */
    public static boolean isUnmodifiedClick(MouseEvent e, int clickCount) {
	return e.getID() == MouseEvent.MOUSE_CLICKED && e.getButton() == 1 &&
	    e.getClickCount() == clickCount && !isModifierKeyPressed(e);
    }

    public static void propagate(MouseEvent e, Component c) {
	Point p = SwingUtilities.convertPoint(e.getComponent(),
	    e.getX(), e.getY(), c);

	MouseEvent e2;
	if (e instanceof MouseWheelEvent) {
            e2 = new MouseWheelEvent(c, e.getID(), e.getWhen(),
                e.getModifiers(), p.x, p.y, e.getClickCount(),
                e.isPopupTrigger(), ((MouseWheelEvent)e).getScrollType(),
                ((MouseWheelEvent)e).getScrollAmount(),
                ((MouseWheelEvent)e).getWheelRotation());
	} else {
            e2 = new MouseEvent(c, e.getID(), e.getWhen(), e.getModifiers(),
		p.x, p.y, e.getClickCount(), e.isPopupTrigger());
	}

	c.dispatchEvent(e2);
    }

    /**
     * Removes the given {@code AWTKeyStroke}s from the given {@code
     * Component}'s list of focus traversal keys.
     *
     * @param	    comp
     *		    the {@code Component}
     *
     * @param	    forward
     *		    {@code true} if {@code keyStrokes} traverse forward, {@code
     *		    false} if backward
     *
     * @param	    keyStrokes
     *		    the {@code AWTKeyStroke}s
     */
    public static void removeFocusTraversalKeys(Component comp, boolean forward,
	AWTKeyStroke... keyStrokes) {
	modifyFocusTraversalKeys(comp, forward, false, keyStrokes);
    }

    /**
     * Turn on text antialiasing if appropriate for this platform.  Technically
     * this should follow the conventions that Swing uses (matching this setting
     * to the user's desktop settings), but since Swing doesn't expose this
     * functionality, turn it on here unconditionally.
     */
    public static void setAARendering(Graphics2D g) {
	g.setRenderingHint(RenderingHints.KEY_TEXT_ANTIALIASING,
	    RenderingHints.VALUE_TEXT_ANTIALIAS_ON);
    }

    public static void setBorderFromFont(JComponent c) {
	FontMetrics metrics = c.getFontMetrics(c.getFont());
	int top = metrics.getDescent();
	int left = metrics.charWidth(' ');
	c.setBorder(BorderFactory.createEmptyBorder(top, left, top, left));
    }

    public static void setEnableStateOnSelect(final AbstractButton button,
	final boolean recursive, final boolean enabled,
	final Component... toEnable) {

	ItemListener l = new ItemListener() {
	    @Override
	    public void itemStateChanged(ItemEvent e) {
		boolean state = !(button.isSelected() ^ enabled);
		for (Component c : toEnable) {
		    if (recursive) {
			setEnabledRecursive(c, state);
		    } else {
			c.setEnabled(state);
		    }
		}
	    }
	};

	button.addItemListener(l);

	// Set initial state
	l.itemStateChanged(null);
    }

    /**
     * Sets the enabled status of the given {@code Component}'s descendants, if
     * it is a {@code Container}, then of the given {@code Component} itself.
     * <p>
     * If a {@code Container} implementing {@code DescendantEnabler} is
     * encountered along the way, recursion into the {@code Component}
     * hierarchy is aborted.
     */
    public static void setEnabledRecursive(Component parent, boolean enabled) {
	if (parent instanceof Container &&
	    !(parent instanceof DescendantEnabler)) {

	    for (Component c : ((Container)parent).getComponents()) {
		setEnabledRecursive((Container)c, enabled);
	    }
	}

	// A disabled JPanel is ugly
	if (enabled || parent instanceof DescendantEnabler ||
	    !(parent instanceof JPanel)) {

	    parent.setEnabled(enabled);
	}
    }

    /**
     * Sets the left and right margin of an {@code AbstractButton} in a
     * L&amp;F-independent manner (some L&amp;Fs set this value in the margin,
     * while others ignore this property and use the border instead).
     */
    public static void setHorizontalMargin(AbstractButton button, int hMargin) {
	Insets margin = button.getMargin();
	margin.left = margin.right = hMargin;

	Border empty = BorderFactory.createEmptyBorder(
	    margin.top, margin.left, margin.bottom, margin.right);

	Border outer = button.getBorder();
	Border compound = BorderFactory.createCompoundBorder(outer, empty);

	button.setMargin(new Insets(0, 0, 0, 0));
	button.setBorder(compound);
    }

    public static void setMinorFont(Component comp) {
	Font font = comp.getFont();
	font = font.deriveFont(font.getSize() * .85f);
	comp.setFont(font);
    }

    public static void setUIPreferences(Properties p) {
	List<Properties> pList = prefs.getPropertiesList();
	if (pList.size() > 1) {
	    pList.remove(1);
	}
	pList.add(p);
    }

    /**
     * Sets whether the given {@code Component} uses tab and shift-tab as
     * forward/backward focus traversal keys.
     */
    public static void setUseStandardFocusTraversalKeys(Component comp,
	boolean use) {

	modifyFocusTraversalKeys(comp, true, use, KeyStroke.getKeyStroke(
	    KeyEvent.VK_TAB, 0));

	modifyFocusTraversalKeys(comp, false, use, KeyStroke.getKeyStroke(
	    KeyEvent.VK_TAB, InputEvent.SHIFT_DOWN_MASK));
    }

    /**
     * Shows a confirmation message dialog.
     *
     * @param	    component
     *		    a {@code Component} contained within a {@code Frame} for
     *		    which the dialog will be modal, or {@code null} to display a
     *		    non-modal dialog
     *
     * @param	    title
     *		    the title to display in the dialog, or {@code null} to use a
     *		    default
     *
     * @param	    optionType
     *		    a static constant from the {@code JOptionPane} class: {@code
     *		    YES_NO_OPTION}, {@code YES_NO_CANCEL_OPTION}, or {@code
     *		    OK_CANCEL_OPTION}, or {@code null} to use the default
     *		    ({@code OK_CANCEL_OPTION})
     *
     * @param	    message
     *		    the message to display in the dialog
     *
     * @return	    an integer indicating the option selected by the user
     */
    public static int showConfirmation(Component component, String title,
	Object message, Integer optionType) {

	if (title == null) {
	    title = Finder.getString("dialog.title.confirm");
	}

	JOptionPane pane = new ExtOptionPane(
	    message, JOptionPane.QUESTION_MESSAGE);
	pane.setOptionType(JOptionPane.OK_CANCEL_OPTION);

	JDialog dialog = pane.createDialog(component, title);
	dialog.setVisible(true);

	Object selection = pane.getValue();
	if (selection == null) {
	    return JOptionPane.CLOSED_OPTION;
	}

	return (Integer)selection;
    }

    /**
     * Shows an error message dialog.
     *
     * @param	    component
     *		    a {@code Component} contained within a {@code Frame} for
     *		    which the dialog will be modal, or {@code null} to display a
     *		    non-modal dialog
     *
     * @param	    title
     *		    the title to display in the dialog, or {@code null} to use a
     *		    default
     *
     * @param	    message
     *		    the message to display in the dialog
     */
    public static void showError(Component component, String title,
	Object message) {

	if (message != null) {
	    if (title == null) {
		title = Finder.getString("dialog.title.error");
	    }

	    showOptionPane(JOptionPane.ERROR_MESSAGE, component, title,
		message);
	}
    }

    /**
     * Shows an info message dialog.
     *
     * @param	    component
     *		    a {@code Component} contained within a {@code Frame} for
     *		    which the dialog will be modal, or {@code null} to display a
     *		    non-modal dialog
     *
     * @param	    title
     *		    the title to display in the dialog, or {@code null} to use a
     *		    default
     *
     * @param	    message
     *		    the message to display in the dialog
     */
    public static void showInfo(Component component, String title,
	String message) {

	if (title == null) {
	    title = Finder.getString("dialog.title.info");
	}

	showOptionPane(JOptionPane.INFORMATION_MESSAGE, component, title,
	    message);
    }

    /**
     * Shows a width-constrained {@code JOptionPane} with the specified
     * parameters.
     *
     * @see	    ExtOptionPane
     */
    public static void showOptionPane(int messageType, Component component,
	String title, Object message) {

	JOptionPane pane = new ExtOptionPane(message, messageType);
	JDialog dialog = pane.createDialog(component, title);
	dialog.setVisible(true);
    }

    /**
     * Shows an warning message dialog.
     *
     * @param	    component
     *		    a {@code Component} contained within a {@code Frame} for
     *		    which the dialog will be modal, or {@code null} to display a
     *		    non-modal dialog
     *
     * @param	    title
     *		    the title to display in the dialog, or {@code null} to use a
     *		    default
     *
     * @param	    message
     *		    the message to display in the dialog
     */
    public static void showWarning(Component component, String title,
	String message) {

	if (title == null) {
	    title = Finder.getString("dialog.title.warning");
	}

	showOptionPane(JOptionPane.WARNING_MESSAGE, component, title, message);
    }

    //
    // Private static methods
    //

    private static void modifyFocusTraversalKeys(Component comp,
	boolean forward, boolean add, AWTKeyStroke... keyStrokes) {

	int dir = forward ? KeyboardFocusManager.FORWARD_TRAVERSAL_KEYS :
	    KeyboardFocusManager.BACKWARD_TRAVERSAL_KEYS;

	Set<AWTKeyStroke> keys = new HashSet<AWTKeyStroke>(
	    comp.getFocusTraversalKeys(dir));

	for (AWTKeyStroke key : keyStrokes) {
	    if (add) {
		keys.add(key);
	    } else {
		keys.remove(key);
	    }
	}

	comp.setFocusTraversalKeys(dir, keys);
    }
}
