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

package com.oracle.solaris.vp.util.swing.time;

import java.awt.*;
import java.awt.event.*;
import java.text.*;
import java.util.*;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.text.DefaultCaret;
import com.oracle.solaris.vp.util.swing.GUIUtil;

@SuppressWarnings({"serial"})
public class TimeSpinnerEditor extends JTextField {
    //
    // Instance data
    //

    private DateFormat format;
    private TimeSpinnerModel model;
    private Date time;
    private boolean ignoreCaretEvents;
    private FieldPosition selected;

    // Map Format.Fields to Calendar fields
    // These are all only fields that TimeSpinnerModel supports.
    private Map<Format.Field, Integer> fieldMap;
    {
	fieldMap = new HashMap<Format.Field, Integer>();
	fieldMap.put(DateFormat.Field.AM_PM, Calendar.AM_PM);
	fieldMap.put(DateFormat.Field.DAY_OF_MONTH, Calendar.DAY_OF_MONTH);
	fieldMap.put(DateFormat.Field.DAY_OF_WEEK, Calendar.DAY_OF_WEEK);
	fieldMap.put(DateFormat.Field.DAY_OF_YEAR, Calendar.DAY_OF_YEAR);
	fieldMap.put(DateFormat.Field.ERA, Calendar.ERA);
	fieldMap.put(DateFormat.Field.HOUR0, Calendar.HOUR);
	fieldMap.put(DateFormat.Field.HOUR1, Calendar.HOUR);
	fieldMap.put(DateFormat.Field.HOUR_OF_DAY0, Calendar.HOUR_OF_DAY);
	fieldMap.put(DateFormat.Field.HOUR_OF_DAY1, Calendar.HOUR_OF_DAY);
	fieldMap.put(DateFormat.Field.MILLISECOND, Calendar.MILLISECOND);
	fieldMap.put(DateFormat.Field.MINUTE, Calendar.MINUTE);
	fieldMap.put(DateFormat.Field.MONTH, Calendar.MONTH);
	fieldMap.put(DateFormat.Field.SECOND, Calendar.SECOND);
	fieldMap.put(DateFormat.Field.TIME_ZONE, Calendar.ZONE_OFFSET);
	fieldMap.put(DateFormat.Field.WEEK_OF_MONTH, Calendar.WEEK_OF_MONTH);
	fieldMap.put(DateFormat.Field.WEEK_OF_YEAR, Calendar.WEEK_OF_YEAR);
	fieldMap.put(DateFormat.Field.YEAR, Calendar.YEAR);
    };

    private FieldPosition[] positions;
    {
	Set<Format.Field> fields = fieldMap.keySet();
	positions = new FieldPosition[fields.size()];
	int i = 0;
	for (Format.Field field : fields) {
	    positions[i++] = new FieldPosition(field);
	}
    }

    private Comparator<FieldPosition> posComparator =
	new Comparator<FieldPosition>() {
	    @Override
	    public int compare(FieldPosition o1, FieldPosition o2) {
		int begin1 = o1.getBeginIndex();
		int begin2 = o2.getBeginIndex();

		if (begin1 < begin2) {
		    return -1;
		} else if (begin1 > begin2) {
		    return 1;
		}

		int end1 = o1.getEndIndex();
		int end2 = o2.getEndIndex();

		if (end1 < end2) {
		    return -1;
		} else if (end1 > end2) {
		    return 1;
		}

		return 0;
	    }
	};

    //
    // Constructors
    //

    public TimeSpinnerEditor(TimeSpinnerModel model, DateFormat format) {
	this.model = model;
	this.format = format;

	setEditable(false);

	model.addChangeListener(
	    new ChangeListener() {
		@Override
		public void stateChanged(ChangeEvent e) {
		    updateFromModel();
		}
	    });

	updateFromModel();

	model.getTimeSelectionModel().addChangeListener(
	    new ChangeListener() {
		@Override
		public void stateChanged(ChangeEvent e) {
		    selectionChanged();
		}
	    });

	addCaretListener(
	    new CaretListener() {
		@Override
		public void caretUpdate(CaretEvent e) {
		    if (!ignoreCaretEvents) {
			EventQueue.invokeLater(
			    new Runnable() {
				@Override
				public void run() {
				    selectFieldAtCaret();
				}
			    });
		    }
		}
	    });

	// Select first field
	selectFieldAtCaret();

	addFocusListener(
	    new FocusListener() {
		@Override
		public void focusGained(FocusEvent e) {
		    if (getModel().getTimeSelectionModel().getSelectedField() ==
			-1) {
			selectFieldAtCaret();
		    }
		}

		@Override
		public void focusLost(FocusEvent e) {
		    if (!e.isTemporary()) {
			getModel().getTimeSelectionModel().setSelectedField(-1);
		    }
		}
	    });

	KeyStroke right = KeyStroke.getKeyStroke(KeyEvent.VK_RIGHT, 0);
	Action focusNextFieldAction =
	    new AbstractAction() {
		@Override
		public void actionPerformed(ActionEvent e) {
		    focusNextField();
		}
	    };
	GUIUtil.installKeyBinding(this, JComponent.WHEN_FOCUSED,
	    "next field", focusNextFieldAction, right);

	KeyStroke tab = KeyStroke.getKeyStroke(KeyEvent.VK_TAB, 0);
	GUIUtil.removeFocusTraversalKeys(this, true, tab);
	Action focusNextFieldOrNextComponentAction =
	    new AbstractAction() {
		@Override
		public void actionPerformed(ActionEvent e) {
		    focusNextFieldOrNextComponent();
		}
	    };
	GUIUtil.installKeyBinding(this, JComponent.WHEN_FOCUSED,
	    "next field or next focus", focusNextFieldOrNextComponentAction,
	    tab);

	KeyStroke left = KeyStroke.getKeyStroke(KeyEvent.VK_LEFT, 0);
	Action focusPreviousFieldAction =
	    new AbstractAction() {
		@Override
		public void actionPerformed(ActionEvent e) {
		    focusPreviousField();
		}
	    };
	GUIUtil.installKeyBinding(this, JComponent.WHEN_FOCUSED,
	    "previous field", focusPreviousFieldAction, left);

	KeyStroke shiftTab = KeyStroke.getKeyStroke(KeyEvent.VK_TAB,
	    InputEvent.SHIFT_DOWN_MASK);
	GUIUtil.removeFocusTraversalKeys(this, false, shiftTab);
	Action focusPreviousFieldOrPreviousComponentAction =
	    new AbstractAction() {
		@Override
		public void actionPerformed(ActionEvent e) {
		    focusPreviousFieldOrPreviousComponent();
		}
	    };
	GUIUtil.installKeyBinding(this, JComponent.WHEN_FOCUSED,
	    "previous field or previous focus",
	    focusPreviousFieldOrPreviousComponentAction, shiftTab);
    }

    public TimeSpinnerEditor(JSpinner spinner) {
	this((TimeSpinnerModel)spinner.getModel(), createDateFormat(spinner));
    }

    //
    // Component methods
    //

    /*
     * Every once in a while a bug comes along that can only be worked around by
     * implementing a truly vile and repulsive hack.  This hack violates several
     * tenets of good programming practice.
     *
     * My hand was forced, however, by the extremely limited implementation of
     * the javax.swing.text.DefaultCaret class.  This class refuses to even
     * consider the possibility that a developer or user might not want every
     * single selection in a JTextComponent (in this class, numerous and
     * frequently changed) to be automatically copied to the system selection.
     * It further complicates the matter with excessively restrictive access
     * control on several methods which might otherwise be easily overridden to
     * change this default behavior.
     *
     * You might think that overriding copy() and paste() would be sufficient,
     * but those methods don't apply to the system selection.
     *
     * A proper fix might implement a Caret class to do exactly what
     * DefaultCaret does, minus the updateSystemSelection method.  However,
     * DefaultCaret.java is ~2000 lines long, and our implementation would need
     * to keep pace with future developements in DefaultCaret.
     *
     * So we are left with this.  Examining a stack trace to see who's calling
     * us is nauseatingly hideous, but surprisingly succinct.  Throwing a
     * SecurityException whose handling we can know about only by examining the
     * DefaultCaret source code (not the API) is the cherry on the icing.
     */
    @Override
    public Toolkit getToolkit() {
	StackTraceElement[] trace = Thread.currentThread().getStackTrace();
	if (trace.length >= 4) {
	    String className = DefaultCaret.class.getName();
	    if (trace[2].getClassName().equals(className) &&
		trace[2].getMethodName().equals("getSystemSelection") &&
		trace[3].getClassName().equals(className) &&
		trace[3].getMethodName().equals("updateSystemSelection")) {
		throw new SecurityException();
	    }
	}
	return super.getToolkit();
    }

    //
    // TimeSpinnerEditor methods
    //

    /**
     * Focusses/highlights the next field in the {@code DateFormat}, if the last
     * field is not already focussed.
     *
     * @return	    {@code true} if the next field was successfully focussed,
     *		    {@code false} if there is no next field
     */
    public boolean focusNextField() {
	for (int i = 0; i < positions.length - 1; i++) {
	    if (positions[i] == selected) {
		int calField = fieldPositionToCalendarField(positions[i + 1]);
		model.getTimeSelectionModel().setSelectedField(calField);
		return true;
	    }
	}
	return false;
    }

    /**
     * Focusses/highlights the previous field in the {@code DateFormat}, if the
     * first field is not already focussed.
     *
     * @return	    {@code true} if the previous field was successfully
     *		    focussed, {@code false} if there is no previous field
     */
    public boolean focusPreviousField() {
	for (int i = positions.length - 1; i > 0; i--) {
	    if (positions[i] == selected) {
		for (i--; i >= 0; i--) {
		    // Does this field actually appear in this format?
		    if (positions[i].getBeginIndex() !=
			positions[i].getEndIndex()) {

			int calField = fieldPositionToCalendarField(
			    positions[i]);
			model.getTimeSelectionModel().setSelectedField(
			    calField);
			return true;
		    }
		}
	    }
	}
	return false;
    }

    /**
     * Gets the {@link TimeSpinnerModel} used by this {@code TimeSpinnerEditor}.
     */
    public TimeSpinnerModel getModel() {
	return model;
    }

    /**
     * Gets the last time that was set in this field.
     */
    public Date getTime() {
	return time;
    }

    /**
     * Sets the time in this field.
     */
    public void setTime(Date time) {
	this.time = time;

	// Don't react to caret events -- setSelectedField will set the
	// selection manually (and then reset this value)
	ignoreCaretEvents = true;

	setText(format.format(time));

	// Set begin/end in each FieldPosition
	StringBuffer buffer = new StringBuffer();
	for (FieldPosition position : positions) {
	    buffer.setLength(0);
	    format.format(time, buffer, position);
	}

	// Sort FieldPositions in the order in which they appear
	Arrays.sort(positions, posComparator);

	// Restore selection, if possible
	setSelectedField(this.selected);
    }

    //
    // Private methods
    //

    private int distance(int begin, int end, int pos) {
	assert begin <= end;
	if (pos <= begin) {
	    return begin - pos;
	}
	return pos - end;
    }

    private void focusNextFieldOrNextComponent() {
	if (!focusNextField() && hasFocus()) {
	    transferFocus();
	}
    }

    private void focusPreviousFieldOrPreviousComponent() {
	if (!focusPreviousField() && hasFocus()) {
	    transferFocusBackward();
	}
    }

    private void selectFieldAtCaret() {
	int caret = getSelectionStart();

	// Find FieldPosition closest to caret
	FieldPosition position = null;
	int minDistance = 0;
	for (int i = positions.length - 1; i >= 0; i--) {
	    int begin = positions[i].getBeginIndex();
	    int end = positions[i].getEndIndex();

	    // Is this field used in this format?
	    if (begin != end) {
		int distance = distance(begin, end, caret);
		if (position == null || distance < minDistance) {
		    position = positions[i];
		    minDistance = distance;
		    if (distance <= 0) {
			break;
		    }
		} else {
		    break;
		}
	    }
	}

	int calField = fieldPositionToCalendarField(position);
	model.getTimeSelectionModel().setSelectedField(calField);
    }

    private FieldPosition calendarFieldToFieldPosition(int calField) {
	if (calField != -1) {
	    for (int i = positions.length - 1; i >= 0; i--) {
		// Is this field used in this format?
		if (positions[i].getBeginIndex() != positions[i].getEndIndex())
		{
		    Format.Field fmtField = positions[i].getFieldAttribute();
		    if (fieldMap.get(fmtField) == calField) {
			return positions[i];
		    }
		}
	    }
	}
	return null;
    }

    private int fieldPositionToCalendarField(FieldPosition position) {
	Format.Field fmtField = position.getFieldAttribute();
	return fieldMap.get(fmtField);
    }

    private void selectionChanged() {
	int calendarField = model.getTimeSelectionModel().getSelectedField();
	FieldPosition position = calendarFieldToFieldPosition(calendarField);
	setSelectedField(position);
    }

    private void setSelectedField(FieldPosition selected) {
	this.selected = selected;

	int newSelStart = 0;
	int newSelEnd = 0;

	if (selected != null) {
	    newSelStart = selected.getBeginIndex();
	    newSelEnd = selected.getEndIndex();
	}

	try {
	    int selStart = getSelectionStart();
	    if (selStart != newSelStart) {
		// Don't recurse
		ignoreCaretEvents = true;
		setCaretPosition(newSelStart);
	    }

	    int selEnd = getSelectionEnd();
	    if (selEnd != newSelEnd) {
		// Don't recurse
		ignoreCaretEvents = true;
		moveCaretPosition(newSelEnd);
	    }

	    if (ignoreCaretEvents) {
		EventQueue.invokeLater(
		    new Runnable() {
			@Override
			public void run() {
			    ignoreCaretEvents = false;
			}
		    });
	    }

	// Thrown by {set,move}CaretPosition -- see 10392
	} catch (IllegalArgumentException ignore) {
	}
    }

    private void updateFromModel() {
	setTime(model.getTimeModel().getCalendar().getTime());
    }

    //
    // Static methods
    //

    protected static DateFormat createDateFormat(JSpinner spinner) {
	Locale locale = spinner.getLocale();

	DateFormat format = DateFormat.getTimeInstance(DateFormat.MEDIUM,
	    locale == null ? Locale.getDefault() : locale);

	if (format instanceof SimpleDateFormat) {
	    padUnits((SimpleDateFormat)format);
	}

	return format;
    }

    protected static void padUnits(SimpleDateFormat format) {
	String pattern = format.toPattern().replaceAll(
	    "\\b([yMwWDdFHkKhmsS])\\b", "$1$1");

	format.applyPattern(pattern);
    }
}
