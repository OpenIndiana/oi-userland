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

package com.oracle.solaris.vp.util.misc;

import java.text.DecimalFormat;
import com.oracle.solaris.vp.util.misc.finder.Finder;

public class DataSizeUtil {
    //
    // Inner classes
    //

    public static class DataSize {
	public double value;
	public int unitsIndex;
	public DataSize(double value, int unitsIndex) {
	    this.value = value;
	    this.unitsIndex = unitsIndex;
	}
    }

    //
    // Static methods
    //

    public static String[] getDefaultUnits() {
	return new String[] {
	    Finder.getString("constants.bytes.short"),
	    Finder.getString("constants.kilobytes.short"),
	    Finder.getString("constants.megabytes.short"),
	    Finder.getString("constants.gigabytes.short"),
	    Finder.getString("constants.terabytes.short"),
	    Finder.getString("constants.petabytes.short"),
	    Finder.getString("constants.exabytes.short"),
	};
    }

    /**
     * Gets a DataSize object that represents the most displayable
     * form of the given data size.
     *
     * @param	    bytes
     *		    the size of the data in bytes
     *
     * @param	    precision
     *		    the number of digits to appear after the decimal
     *		    separator
     *
     * @param	    units
     *		    a String array of the units to be shown after the
     *		    size, in the following order:
     *		    <pre>
     *		    index  unit
     *		    ---------------------------
     *		    0	   byte unit string
     *		    1	   kilobyte unit string
     *		    2	   megabyte unit string
     *		    3	   gigabyte unit string
     *		    4	   terabyte unit string
     *		    5	   petabyte unit string
     *		    6	   exabyte unit string
     *		    </pre>
     *		    If null, the default units will be used.
     *
     * @param	    unit
     *		    a string from the units array to force the use of
     *		    a particular unit, or {@code null} to use the
     *		    most appropriate unit for the given size
     *
     * @return	    a DataSize object that represents the most
     *		    displayable form of the given data size.
     */
    public static DataSize getDataSize(
	long bytes, int precision, String[] units, String unit) {

	if (units == null) {
	    units = getDefaultUnits();
	}

	// Handle negative values
	double factor = 1;
	if (bytes < 0) {
	    bytes = -bytes;
	    factor = -1;
	}

	double adjusted;
	long bytesPerUnit = 1;
	int i;

	if (unit == null) {
	    // Determine which units to use
	    double slop = precision > 0 ? .5 : 0;
	    for (i = 0; i < precision; i++) {
		slop /= 10;
	    }

	    adjusted = bytes;

	    for (i = 0; i < units.length; i++) {
		adjusted = (double)bytes / (double)bytesPerUnit;

		if (i == units.length - 1 || adjusted + slop < 1024) {
		    break;
		}

		bytesPerUnit <<= 10;
	    }
	} else {
	    for (i = 0; i < units.length - 1 && ! units[i].equals(unit); i++) {
		bytesPerUnit <<= 10;
	    }

	    adjusted = (double)bytes / (double)bytesPerUnit;
	}

	return new DataSize(factor * adjusted, i);
    }

    /**
     * Gets the given data size in a human-readable format.
     *
     * @param	    bytes
     *		    the size of the data in bytes
     *
     * @param	    precision
     *		    the number of digits to appear after the decimal
     *		    separator
     *
     * @param	    forcePrecision
     *		    whether to keep the decimal portion of the
     *		    output if all digits after the decimal separator
     *		    are 0.  If units are in bytes, the decimal portion
     *		    is never included in the output.
     *
     * @param	    units
     *		    a String array of the units to be shown after the
     *		    size, in the following order:
     *		    <pre>
     *		    index  unit
     *		    ---------------------------
     *		    0	   byte unit string
     *		    1	   kilobyte unit string
     *		    2	   megabyte unit string
     *		    3	   gigabyte unit string
     *		    4	   terabyte unit string
     *		    5	   petabyte unit string
     *		    6	   exabyte unit string
     *		    </pre>
     *		    If null, the default units will be used.
     *
     * @param	    unit
     *		    a string from the units array to force the use of
     *		    a particular unit, or {@code null} to use the
     *		    most appropriate unit for the given size
     *
     * @param	    addSpace
     *		    whether to add a space between the numerical value
     *		    and the units text
     *
     * @param	    useCommas
     *		    whether to separate every third digit with a comma
     *
     * @return	    a data size string in human-readable format
     */
    public static String getHumanReadableDataSize(
	long bytes, int precision, boolean forcePrecision,
	String[] units, String unit, boolean addSpace, boolean useCommas) {

	if (units == null) {
	    units = getDefaultUnits();
	}

	DataSize dataSize = getDataSize(bytes, precision, units, unit);

	// Build format string
	StringBuilder pattern = new StringBuilder();
	pattern.append(useCommas ? "#,##0" : "###0");
	char formatChar =
	    (forcePrecision && dataSize.unitsIndex != 0) ? '0' : '#';
	for (int j = 0; j < precision; j++) {
	    if (j == 0) {
		pattern.append('.');
	    }
	    pattern.append(formatChar);
	}
	DecimalFormat format = new DecimalFormat(pattern.toString());
	String space = addSpace ? " " : "";

	return format.format(dataSize.value) + space +
	    units[dataSize.unitsIndex];
    }

    /**
     * Tries to parse the given string as a human-readable expression
     * of size.  Only enough of the unit string must appear in the
     * given string to uniquely distinguish a single unit string.
     * Parsing is case-insensitive.
     *
     * @param	    text
     *		    the text to parse
     *
     * @param	    units
     *		    a String array of valid units that may appear
     *		    after the size.
     *		    <pre>
     *		    index  unit
     *		    ---------------------------
     *		    0	   byte unit string
     *		    1	   kilobyte unit string
     *		    2	   megabyte unit string
     *		    3	   gigabyte unit string
     *		    4	   terabyte unit string
     *		    5	   petabyte unit string
     *		    6	   exabyte unit string
     *		    </pre>
     *		    If null, the default units will be used.
     *
     * @param	    defaultUnitIndex
     *		    the default units (specified as an index of the
     *		    {@code units} array) to use if no unit text
     *		    is specified as part of the given string
     *
     * @return	    the size in bytes that the given string represents
     *
     * @exception   NumberFormatException
     *		    if the given text does not represent a valid size
     */
    public static long parseHumanReadableDataSize(
	String text, String[] units, int defaultUnitIndex) {

	if (units == null) {
	    units = getDefaultUnits();
	}

	String[] groups = TextUtil.match(
	    text, "^\\s*(\\d+(\\.\\d+)?)\\s*(\\S*)\\s*$");
	if (groups == null) {
	    throw new NumberFormatException(Finder.getString(
		"error.invalidsize", text));
	}

	double value = Double.parseDouble(groups[1]);
	long multiplier = 1;

	// Was a units string specified?
	if (groups[3].isEmpty()) {

	    // No, use default
	    multiplier <<= 10 * defaultUnitIndex;
	} else {

	    // Yes, search for matching units string
	    String matchingUnit = null;
	    String unitText = groups[3].toLowerCase();

	    for (int i = 0; i < units.length; i++) {
		if (units[i].toLowerCase().startsWith(unitText)) {

		    // If we've already found a match, then the given
		    // units text is ambiguous
		    if (matchingUnit != null) {
			throw new NumberFormatException(Finder.getString(
			    "error.ambiguousunits",
			    unitText, matchingUnit, units[i]));
		    }

		    matchingUnit = units[i];
		}

		if (matchingUnit == null) {
		    multiplier <<= 10;
		}
	    }

	    if (matchingUnit == null) {
		throw new NumberFormatException(Finder.getString(
		    "error.invalidunits", unitText));
	    }
	}

	return (long)(value * multiplier);
    }
}
