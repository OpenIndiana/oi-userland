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

import java.io.PrintStream;
import java.util.*;
import com.oracle.solaris.scf.common.*;
import com.oracle.solaris.vp.panel.common.smf.*;
import com.oracle.solaris.vp.util.misc.finder.Finder;

/**
 * Wholly encapsulates core file configuration.  Can be constructed
 * manually or from an existing SMF configuration.
 */
public class CoreConfig {

    /**
     * Core file content types, enumerated.
     */
    public enum ContentType {
	ANON("anon"), CTF("ctf"), DATA("data"), DISM("dism"), HEAP("heap"),
	ISM("ism"), RODATA("rodata"), SHANON("shanon"), SHFILE("shfile"),
	SHM("shm"), STACK("stack"), SYMTAB("symtab"), TEXT("text");

	private final String literal_;
	private ContentType(String literal) {
	    literal_ = literal;
	}

	/**
	 * Returns the string the system uses to represent the type.
	 * Should only be needed inside of CoreConfig.
	 *
	 * @return the string the system uses to represent the type
	 */
	private String getLiteral()
	{
	    return (literal_);
	}

	/**
	 * Returns the natural language name of the content type.
	 *
	 * @return the natural language name of the content type.
	 */
	public String getName()
	{
	    return (Finder.getString("coreadm.contents." + literal_));
	}
    }

    /*
     * Ideally this would be unmodifiable, but there is no
     * Collections.umodifiableEnumSet() and the EnumSet-specific
     * interfaces are very useful.
     */

    /**
     * The default set of content types.
     */
    private static final String LITERAL_DEFAULT = "default";
    public static final EnumSet<ContentType> CONTENT_DEFAULT =
	EnumSet.complementOf(EnumSet.of(ContentType.SHFILE));

    private static final String LITERAL_NONE = "none";
    public static final EnumSet<ContentType> CONTENT_NONE =
	EnumSet.noneOf(ContentType.class);

    private static final String LITERAL_ALL = "all";
    public static final EnumSet<ContentType> CONTENT_ALL =
	EnumSet.allOf(ContentType.class);

    /*
     * Constants for SMF representation.
     */
    private static final String CONFIG_PG = "config_params";
    private static final String PROP_LOGGING = "global_log_enabled";

    private static final String PROP_SFX_CONTENT = "_content";
    private static final String PROP_SFX_PATTERN = "_pattern";
    private static final String PROP_SFX_ENABLED = "_enabled";
    private static final String PROP_SFX_SETID = "_setid_enabled";

    private static final String PROP_PFX_GLOBAL = "global";
    private static final String PROP_PFX_PROC = "process";
    /* Needed for content and pattern */
    private static final String PROP_PFX_ALTPROC = "init";

    /**
     * Converts a literal content type into an EnumSet containing
     * the appropriate ContentTypes.
     *
     * @param literal the string to convert to a ContentType
     * @return the EnumSet of corresponding ContentTypes
     * @throws IllegalArugmentException if literal isn't a valid
     * content type literal
     */
    private static EnumSet<ContentType> literalToSet(String literal)
    {
	/*
	 * This isn't the most efficient implementation, but
	 * it does the job.
	 */
	for (ContentType t : ContentType.values())
	    if (t.getLiteral().equals(literal))
		return (EnumSet.of(t));

	if (literal.equals(LITERAL_DEFAULT))
		return (CONTENT_DEFAULT);

	if (literal.equals(LITERAL_NONE))
		return (CONTENT_NONE);

	if (literal.equals(LITERAL_ALL))
		return (CONTENT_ALL);

	throw (new IllegalArgumentException(literal));
    }

    /**
     * Converts a Set of ContentTypes to a comma-separated list of
     * system-recognized type names.
     *
     * @param s the Set of ContentTypes to convert to a String
     * @return the comma-separated String representation of the Set
     */
    private static String setToLiterals(EnumSet<ContentType> s)
    {
	if (s.equals(CONTENT_DEFAULT))
	    return (LITERAL_DEFAULT);

	if (s.equals(CONTENT_ALL))
	    return (LITERAL_ALL);

	if (s.equals(CONTENT_NONE))
	    return (LITERAL_NONE);

	StringBuilder sb = new StringBuilder();
	boolean comma = false;
	for (ContentType t : s) {
	    if (comma)
		sb.append("+");
	    comma = true;
	    sb.append(t.getLiteral());
	}
	return (sb.toString());
    }

    /**
     * Converts a list of content types in string form into a EnumSet
     * of ContentTypes.
     *
     * @param lit the list of content types in string form
     * @return an EnumSet containing the content types
     */
    private static EnumSet<ContentType> literalsToSet(String lit)
    {
        boolean plus = true;
	int offset = 0;
	int max = lit.length();

	EnumSet<ContentType> result = EnumSet.noneOf(ContentType.class);
	for (String s : lit.split("[+-]")) {
	    if (plus)
		result.addAll(literalToSet(s));
	    else
		result.retainAll(EnumSet.complementOf(literalToSet(s)));

	    offset += s.length();
	    if (offset < max)
		plus = lit.charAt(offset) == '+';
	    offset++;
        }
	return (result);
    }

    /**
     * Encapsulates configuration that could apply to either
     * the process or global scope.
     */
    static public class ScopeConfig
    {
	private EnumSet<ContentType> content_;
	private String pattern_;
	private boolean enabled_;
	private boolean setid_;

	public ScopeConfig(EnumSet<ContentType> content,
	    String pattern, boolean enabled, boolean setid)
	{
	    content_ = content;
	    pattern_ = pattern;
	    enabled_ = enabled;
	    setid_ = setid;
	}

	public ScopeConfig()
	{
	    this(CONTENT_DEFAULT.clone(), "", false, false);
	}


	public ScopeConfig(ScopeConfig config)
	{
	    this(config.content_.clone(),
		config.pattern_, config.enabled_, config.setid_);
	}

	public ScopeConfig(ServiceMXBean service, String pfx, String altpfx)
	    throws ScfException, InvalidScfDataException,
	    MissingScfDataException
	{
	    List<String> content = service.getSnapshotPropertyValues(
		ScfConstants.SCF_RUNNING, CONFIG_PG, altpfx + PROP_SFX_CONTENT);
	    List<String> pattern = service.getSnapshotPropertyValues(
		ScfConstants.SCF_RUNNING, CONFIG_PG, altpfx + PROP_SFX_PATTERN);
	    List<String> enabled = service.getSnapshotPropertyValues(
		ScfConstants.SCF_RUNNING, CONFIG_PG, pfx + PROP_SFX_ENABLED);
	    List<String> setid = service.getSnapshotPropertyValues(
		ScfConstants.SCF_RUNNING, CONFIG_PG, pfx + PROP_SFX_SETID);

	    String name = null;
	    String value = null;
	    try {
		name = altpfx + PROP_SFX_CONTENT;
		value = content.get(0);
		content_ = literalsToSet(value);

		name = altpfx + PROP_SFX_PATTERN;
		pattern_ = pattern.get(0);

		name = pfx + PROP_SFX_ENABLED;
		enabled_ = Boolean.parseBoolean(enabled.get(0));

		name = pfx + PROP_SFX_SETID;
		setid_ = Boolean.parseBoolean(setid.get(0));
	    } catch (IndexOutOfBoundsException e) {
		throw new MissingScfDataException(name);
	    } catch (IllegalArgumentException e) {
		throw new InvalidScfDataException(name, value);
	    }
	}

	/*
	 * Object methods.
	 */

	@Override
	public boolean equals(Object o)
	{
	    if (!(o instanceof ScopeConfig))
		return (false);
	    ScopeConfig c = (ScopeConfig)o;
	    return (enabled_ == c.enabled_ && setid_ == c.setid_ &&
		pattern_.equals(c.pattern_) && content_.equals(c.content_));
	}

	@Override
	public int hashCode()
	{
	    int hash = 7;
	    hash = 61 * hash +
		(this.content_ != null ? this.content_.hashCode() : 0);
	    hash = 61 * hash +
		(this.pattern_ != null ? this.pattern_.hashCode() : 0);
	    hash = 61 * hash + (this.enabled_ ? 1 : 0);
	    hash = 61 * hash + (this.setid_ ? 1 : 0);
	    return (hash);
	}

	/*
	 * ScopeConfig methods.
	 */

        void write(ServiceMXBean service, String pfx, String altpfx)
	    throws ScfException
	{
	    service.setPropertyValues(CONFIG_PG, altpfx + PROP_SFX_CONTENT,
		Collections.singletonList(setToLiterals(content_)));
	    service.setPropertyValues(CONFIG_PG, altpfx + PROP_SFX_PATTERN,
		Collections.singletonList(pattern_));
	    service.setPropertyValues(CONFIG_PG, pfx + PROP_SFX_ENABLED,
		Collections.singletonList(Boolean.toString(enabled_)));
	    service.setPropertyValues(CONFIG_PG, pfx + PROP_SFX_SETID,
		Collections.singletonList(Boolean.toString(setid_)));
	}

	EnumSet<ContentType> getContent()
	{
	    return (content_.clone());
	}

	String getPattern()
	{
	    return (pattern_);
	}

	boolean getEnabled()
	{
	    return (enabled_);
	}

	boolean getSetid()
	{
	    return (setid_);
	}

	void setContent(Set<ContentType> content)
	{
	    content_.clear();
	    content_.addAll(content);
	}

	void setPattern(String pattern)
	{
	    pattern_ = pattern;
	}

	void setEnabled(boolean enabled)
	{
	    enabled_ = enabled;
	}

	void setSetid(boolean setid)
	{
	    setid_ = setid;
	}
    }

    ScopeConfig processScope_;
    ScopeConfig globalScope_;
    boolean logging_;

    CoreConfig(ScopeConfig global, ScopeConfig process, boolean logging)
    {
	globalScope_ = global;
	processScope_ = process;
	logging_ = logging;
    }

    CoreConfig()
    {
	this(new ScopeConfig(), new ScopeConfig(), false);
    }

    CoreConfig(String globalPattern, String processPattern,
	boolean global, boolean globalSetid,
	boolean process, boolean processSetid,
	boolean logging)
    {
	this(new ScopeConfig(CONTENT_DEFAULT.clone(),
	    globalPattern, global, globalSetid),
	    new ScopeConfig(CONTENT_DEFAULT.clone(),
	    processPattern, process, processSetid),
	    logging);
    }

    /**
     * Copy constructor.
     *
     * @param cc the CoreConfig object we are copying.
     */
    CoreConfig(CoreConfig cc)
    {
	this(new ScopeConfig(cc.globalScope_),
	    new ScopeConfig(cc.processScope_), cc.logging_);
    }

    CoreConfig(ServiceMXBean service) throws ScfException,
	InvalidScfDataException, MissingScfDataException
    {
	globalScope_ =
	    new ScopeConfig(service, PROP_PFX_GLOBAL, PROP_PFX_GLOBAL);
	processScope_ =
	    new ScopeConfig(service, PROP_PFX_PROC, PROP_PFX_ALTPROC);

	try {
	    List<String> logging = service.getSnapshotPropertyValues(
		ScfConstants.SCF_RUNNING, CONFIG_PG, PROP_LOGGING);
	    logging_ = Boolean.parseBoolean(logging.get(0));
	} catch (IndexOutOfBoundsException e) {
	    throw new MissingScfDataException(PROP_LOGGING);
	}
    }

    void write(ServiceMXBean service) throws ScfException
    {
	globalScope_.write(service, PROP_PFX_GLOBAL, PROP_PFX_GLOBAL);
	processScope_.write(service, PROP_PFX_PROC, PROP_PFX_ALTPROC);
	service.setPropertyValues(CONFIG_PG, PROP_LOGGING,
	    Collections.singletonList(Boolean.toString(logging_)));

	service.refresh();
    }

    ScopeConfig getProcessScope()
    {
	return (processScope_);
    }

    ScopeConfig getGlobalScope()
    {
	return (globalScope_);
    }

    boolean getLogging()
    {
	return (logging_);
    }

    void setLogging(boolean logging)
    {
	logging_ = logging;
    }

    /*
     * Object methods
     */

    @Override
    public boolean equals(Object o)
    {
	if (!(o instanceof CoreConfig))
	    return (false);
	CoreConfig c = (CoreConfig)o;
	return (logging_ == c.logging_ &&
	    globalScope_.equals(c.globalScope_) &&
	    processScope_.equals(c.processScope_));
    }

    @Override
    public int hashCode()
    {
	int hash = 7;
	hash = 97 * hash +
	    (this.processScope_ != null ? this.processScope_.hashCode() : 0);
	hash = 97 * hash +
	    (this.globalScope_ != null ? this.globalScope_.hashCode() : 0);
	hash = 97 * hash + (this.logging_ ? 1 : 0);
	return (hash);
    }

    private String boolToEnabled(boolean b)
    {
	return (b ? "enabled" : "disabled");
    }

    /**
     * Pretty print a CoreConfig coreadm(1M)-style.
     *
     * @param ps the PrintStream to pretty-print to (e.g. System.out)
     */
    public void dump(java.io.PrintStream ps)
    {
	ps.println("     global core file pattern: " +
	    globalScope_.getPattern());
	ps.println("     global core file content: " +
	    setToLiterals(globalScope_.getContent()));
	ps.println("       init core file pattern: " +
	    processScope_.getPattern());
	ps.println("       init core file content: " +
	    setToLiterals(processScope_.getContent()));
	ps.println("            global core dumps: " +
	    boolToEnabled(globalScope_.getEnabled()));
	ps.println("       per-process core dumps: " +
	    boolToEnabled(processScope_.getEnabled()));
	ps.println("      global setid core dumps: " +
	    boolToEnabled(globalScope_.getSetid()));
	ps.println(" per-process setid core dumps: " +
	    boolToEnabled(processScope_.getSetid()));
	ps.println("     global core dump logging: " + boolToEnabled(logging_));
    }
}
