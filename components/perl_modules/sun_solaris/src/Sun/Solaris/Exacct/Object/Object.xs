/*
 * Copyright (c) 2002, 2003, Oracle and/or its affiliates. All rights reserved.
 * 
 * Object.xs contains XS code for exacct file manipulation.
 */

#include <strings.h>
#include "../exacct_common.xh"

/* Pull in the file generated by extract_defines. */
#include "ObjectDefs.xi"

/* From Catalog.xs. */
extern char *catalog_id_str(ea_catalog_t catalog);

/*
 * Copy an xs_ea_object_t.  If the perl_obj part is null, we just copy the
 * ea_object_t part.  If the perl_obj part is not null and the Object is an
 * Item it must be because the Item contains an embedded Object, which will be
 * recursively copied.  Otherwise the Object must be a Group, so the Group will
 * be copied, and the list of Objects it contains will be recursively copied.
 */
static SV *
copy_xs_ea_object(SV *src_sv)
{
	xs_ea_object_t	*src, *dst;
	SV		*dst_sv, *dst_rv;

	/* Get the source xs_ea_object_t and make a new one. */
	PERL_ASSERT(src_sv != NULL);
	src_sv = SvRV(src_sv);
	PERL_ASSERT(src_sv != NULL);
	src = INT2PTR(xs_ea_object_t *, SvIV(src_sv));
	PERL_ASSERT(src != NULL);
	New(0, dst, 1, xs_ea_object_t);
	dst->flags = src->flags;

	/* If the Object is a plain Item only the ea_obj part needs copying. */
	if (IS_PLAIN_ITEM(src)) {
		dst->ea_obj = ea_copy_object_tree(src->ea_obj);
		PERL_ASSERT(dst->ea_obj != NULL);
		dst->perl_obj = NULL;

	/*
	 * Otherwise if it is an Item with a perl_obj part, it means that it
	 * must be an Item containing an unpacked nested Object.  In this case
	 * the nested Object can be copied by a recursive call.
	 */
	} else if (IS_EMBED_ITEM(src)) {
		dst->ea_obj = ea_copy_object(src->ea_obj);
		PERL_ASSERT(dst->ea_obj != NULL);
		dst->perl_obj = copy_xs_ea_object(src->perl_obj);

	/*
	 * If we get here it must be a Group, so perl_obj will point to a tied
	 * AV.  We therefore copy the exacct part then create a new tied array
	 * and recursively copy each Item individually.
	 */
	} else {
		MAGIC	*mg;
		AV	*src_av, *dst_av, *tied_av;
		SV	*sv;
		int	i, len;

		/* Copy the exacct part of the Group. */
		dst->ea_obj = ea_copy_object(src->ea_obj);
		PERL_ASSERT(dst->ea_obj != NULL);

		/* Find the AV underlying the tie. */
		mg = mg_find(SvRV(src->perl_obj), 'P');
		PERL_ASSERT(mg != NULL);
		src_av = (AV *)SvRV(mg->mg_obj);
		PERL_ASSERT(src_av != NULL);

		/* Create a new AV and copy across into it. */
		dst_av = newAV();
		len = av_len(src_av) + 1;
		av_extend(dst_av, len);
		for (i = 0; i < len; i++) {
			SV **svp;

			/* undef elements don't need copying. */
			if ((svp = av_fetch(src_av, i, FALSE)) != NULL) {
				sv = copy_xs_ea_object(*svp);
				if (av_store(dst_av, i, sv) == NULL) {
					SvREFCNT_dec(sv);
				}
			}
		}

		/* Create a new AV and tie the filled AV to it. */
		sv = newRV_noinc((SV *)dst_av);
		sv_bless(sv, Sun_Solaris_Exacct_Object__Array_stash);
		tied_av = newAV();
		sv_magic((SV *)tied_av, sv, 'P', Nullch, 0);
		SvREFCNT_dec(sv);
		dst->perl_obj = newRV_noinc((SV *)tied_av);
	}

	/* Wrap the new xs_ea_object_t in a blessed RV and return it.  */
	dst_sv = newSViv(PTR2IV(dst));
	dst_rv = newRV_noinc(dst_sv);
	sv_bless(dst_rv, SvSTASH(src_sv));
	SvREADONLY_on(dst_sv);
	return (dst_rv);
}

/*
 * If an ea_xs_object_t only has the ea_obj part populated, create the
 * corresponding perl_obj part.  For plain Items this is a no-op.  If the
 * object is embedded, the embedded part will be unpacked and stored in the
 * perl part.  If the object is a Group, the linked list of Items will be
 * wrapped in the corresponding perl structure and stored in a tied perl array.
 */
static int
inflate_xs_ea_object(xs_ea_object_t *xs_obj)
{
	ea_object_t	*ea_obj;

	/* Check there is not already a perl_obj part. */
	PERL_ASSERT(xs_obj != NULL);
	PERL_ASSERT(xs_obj->perl_obj == NULL);

	/* Deal with Items containing embedded Objects. */
	if (IS_EMBED_ITEM(xs_obj)) {
		/* unpack & wrap in an xs_ea_object_t. */
		if (ea_unpack_object(&ea_obj, EUP_ALLOC,
		    xs_obj->ea_obj->eo_item.ei_object,
		    xs_obj->ea_obj->eo_item.ei_size) == -1) {
			return (0);
		}
		xs_obj->perl_obj = new_xs_ea_object(ea_obj);

	/* Deal with Groups. */
	} else if (IS_GROUP(xs_obj)) {
		int	i, len;
		AV	*av, *tied_av;
		SV	*rv, *sv;

		/* Create a new array. */
		av = newAV();
		ea_obj = xs_obj->ea_obj;
		len = ea_obj->eo_group.eg_nobjs;
		ea_obj = ea_obj->eo_group.eg_objs;

		/* Copy each object from the old array into the new array. */
		for (i = 0; i < len; i++) {
			rv = new_xs_ea_object(ea_obj);
			if (av_store(av, i, rv) == NULL) {
				SvREFCNT_dec(rv);
			}
			ea_obj = ea_obj->eo_next;
		}

		/* Create a new AV and tie the filled AV to it. */
		rv = newRV_noinc((SV *)av);
		sv_bless(rv, Sun_Solaris_Exacct_Object__Array_stash);
		tied_av = newAV();
		sv_magic((SV *)tied_av, rv, 'P', Nullch, 0);
		SvREFCNT_dec(rv);
		xs_obj->perl_obj = newRV_noinc((SV *)tied_av);
	}
	return (1);
}

/*
 * The XS code exported to perl is below here.  Note that the XS preprocessor
 * has its own commenting syntax, so all comments from this point on are in
 * that form.
 */

MODULE = Sun::Solaris::Exacct::Object PACKAGE = Sun::Solaris::Exacct::Object
PROTOTYPES: ENABLE

 #
 # Define the stash pointers if required and create and populate @_Constants.
 #
BOOT:
	{
	init_stashes();
	define_constants(PKGBASE "::Object", constants);
	}

 #
 # Return a dual-typed SV containing the type of the object.
 #
SV *
type(self)
	xs_ea_object_t	*self;
CODE:
	RETVAL = newSViv(self->ea_obj->eo_type);
	switch (self->ea_obj->eo_type) {
	case EO_ITEM:
		sv_setpv(RETVAL, "EO_ITEM");
		break;
	case EO_GROUP:
		sv_setpv(RETVAL, "EO_GROUP");
		break;
	case EO_NONE:
	default:
		sv_setpv(RETVAL, "EO_NONE");
		break;
	}
	SvIOK_on(RETVAL);
OUTPUT:
	RETVAL

 #
 # Return a copy of the catalog of the object.
 #
SV *
catalog(self)
	xs_ea_object_t	*self;
CODE:
	RETVAL = new_catalog(self->ea_obj->eo_catalog);
OUTPUT:
	RETVAL

 #
 # Return the value of the object.  For simple Items, a SV containing the value
 # of the underlying exacct ea_item_t is returned.  For nested Items or Groups,
 # a reference to the nested Item or Group is returned.  For Groups, in a scalar
 # context a reference to the tied array used to store the objects in the Group
 # is returned; in a list context the objects within the Group are returned on
 # the perl stack as a list.
 #
void
value(self)
	xs_ea_object_t	*self;
PPCODE:
	/*
	 * For Items, return the perl representation
	 * of the underlying ea_object_t.
	 */
	if (IS_ITEM(self)) {
		SV	*retval;

		switch (self->ea_obj->eo_catalog & EXT_TYPE_MASK) {
		case EXT_UINT8:
			retval = newSVuv(self->ea_obj->eo_item.ei_uint8);
			break;
		case EXT_UINT16:
			retval = newSVuv(self->ea_obj->eo_item.ei_uint16);
			break;
		case EXT_UINT32:
			retval = newSVuv(self->ea_obj->eo_item.ei_uint32);
			break;
		case EXT_UINT64:
			retval = newSVuv(self->ea_obj->eo_item.ei_uint64);
			break;
		case EXT_DOUBLE:
			retval = newSVnv(self->ea_obj->eo_item.ei_double);
			break;
		case EXT_STRING:
			retval = newSVpvn(self->ea_obj->eo_item.ei_string,
			    self->ea_obj->eo_item.ei_size - 1);
			break;
		case EXT_RAW:
			retval = newSVpvn(self->ea_obj->eo_item.ei_raw,
			    self->ea_obj->eo_item.ei_size);
			break;
		/*
		 * For embedded objects and Groups, return a ref to the perl SV.
		 */
		case EXT_EXACCT_OBJECT:
			if (self->perl_obj == NULL) {
				/* Make sure the object is inflated. */
				if (! inflate_xs_ea_object(self)) {
					XSRETURN_UNDEF;
				}
			}
			retval = SvREFCNT_inc(self->perl_obj);
			break;
		case EXT_GROUP:
			retval = SvREFCNT_inc(self->perl_obj);
			break;
		case EXT_NONE:
		default:
			croak("Invalid object type");
			break;
		}
		EXTEND(SP, 1);
		PUSHs(sv_2mortal(retval));

	/*
	 * Now we deal with Groups.
	 */
	} else {
		/* Make sure the object is inflated. */
		if (self->perl_obj == NULL) {
			if (! inflate_xs_ea_object(self)) {
				XSRETURN_UNDEF;
			}
		}

		/* In a list context return the contents of the AV. */
		if (GIMME_V == G_ARRAY) {
			MAGIC   *mg;
			AV	*av;
			int	len, i;

			/* Find the AV underlying the tie. */
			mg = mg_find(SvRV(self->perl_obj), 'P');
			PERL_ASSERT(mg != NULL);
			av = (AV *)SvRV(mg->mg_obj);
			PERL_ASSERT(av != NULL);

			/*
			 * Push the contents of the array onto the stack.
			 * Push undef for any empty array slots.
			 */
			len = av_len(av) + 1;
			EXTEND(SP, len);
			for (i = 0; i < len; i++) {
				SV	**svp;

			if ((svp = av_fetch(av, i, FALSE)) == NULL) {
					PUSHs(&PL_sv_undef);
				} else {
					PERL_ASSERT(*svp != NULL);
					PUSHs(sv_2mortal(SvREFCNT_inc(*svp)));
				}
			}

		/* In a scalar context, return a ref to the array of Items. */
		} else {
			EXTEND(SP, 1);
			PUSHs(sv_2mortal(SvREFCNT_inc(self->perl_obj)));
		}
	}

 #
 # Call the ea_match_catalog function.
 #
int
match_catalog(self, catalog)
	xs_ea_object_t	*self;
	SV		*catalog;
CODE:
	RETVAL = ea_match_object_catalog(self->ea_obj, catalog_value(catalog));
OUTPUT:
	RETVAL

 #
 # Destroy an Object.
 #
void
DESTROY(self)
	xs_ea_object_t	*self;
PREINIT:
	ea_object_t	*ea_obj;
	SV		*perl_obj;
CODE:
	/*
	 * Because both libexacct and perl know about the ea_object_t, we have
	 * to make sure that they don't both end up freeing the object.  First
	 * we break any link to the next ea_object_t in the chain.  Next, if
	 * the object is a Group and there is an active perl_obj chain, we will
	 * let perl clean up the Objects, so we zero the eo_group chain.
	 */
	perl_obj = self->perl_obj;
	ea_obj = self->ea_obj;
	ea_obj->eo_next = NULL;
	if (IS_GROUP(self) && perl_obj != NULL) {
		ea_obj->eo_group.eg_nobjs = 0;
		ea_obj->eo_group.eg_objs = NULL;
	}
	ea_free_object(ea_obj, EUP_ALLOC);
	if (perl_obj != NULL) {
		SvREFCNT_dec(perl_obj);
	}
	Safefree(self);

MODULE = Sun::Solaris::Exacct::Object PACKAGE = Sun::Solaris::Exacct::Object::Item
PROTOTYPES: ENABLE

 #
 # Create a new Item.
 #
xs_ea_object_t *
new(class, catalog, value)
	char	*class;
	SV	*catalog;
	SV	*value;
PREINIT:
	ea_object_t	*ea_obj;
	HV		*stash;
CODE:
	/* Create a new xs_ea_object_t and subsiduary structures. */
	New(0, RETVAL, 1, xs_ea_object_t);
	RETVAL->ea_obj = ea_obj = ea_alloc(sizeof (ea_object_t));
	bzero(ea_obj, sizeof (*ea_obj));
	ea_obj->eo_type = EO_ITEM;
	ea_obj->eo_catalog = catalog_value(catalog);
	INIT_PLAIN_ITEM_FLAGS(RETVAL);
	RETVAL->perl_obj = NULL;

	/* Assign the Item's value. */
	switch (ea_obj->eo_catalog & EXT_TYPE_MASK) {
	case EXT_UINT8:
		ea_obj->eo_item.ei_uint8 = SvIV(value);
		ea_obj->eo_item.ei_size = sizeof (uint8_t);
		break;
	case EXT_UINT16:
		ea_obj->eo_item.ei_uint16 = SvIV(value);
		ea_obj->eo_item.ei_size = sizeof (uint16_t);
		break;
	case EXT_UINT32:
		ea_obj->eo_item.ei_uint32 = SvIV(value);
		ea_obj->eo_item.ei_size = sizeof (uint32_t);
		break;
	case EXT_UINT64:
		ea_obj->eo_item.ei_uint64 = SvIV(value);
		ea_obj->eo_item.ei_size = sizeof (uint64_t);
		break;
	case EXT_DOUBLE:
		ea_obj->eo_item.ei_double = SvNV(value);
		ea_obj->eo_item.ei_size = sizeof (double);
		break;
	case EXT_STRING:
		ea_obj->eo_item.ei_string = ea_strdup(SvPV_nolen(value));
		ea_obj->eo_item.ei_size = SvCUR(value) + 1;
		break;
	case EXT_RAW:
		ea_obj->eo_item.ei_size = SvCUR(value);
		ea_obj->eo_item.ei_raw = ea_alloc(ea_obj->eo_item.ei_size);
		bcopy(SvPV_nolen(value), ea_obj->eo_item.ei_raw,
		    (size_t)ea_obj->eo_item.ei_size);
		break;
	case EXT_EXACCT_OBJECT:
		/*
		 * The ea_obj part is initially empty, and will be populated
		 * from the perl_obj part  when required.
		 */
		stash = SvROK(value) ? SvSTASH(SvRV(value)) : NULL;
		if (stash != Sun_Solaris_Exacct_Object_Item_stash &&
		    stash != Sun_Solaris_Exacct_Object_Group_stash) {
			croak("value is not of type " PKGBASE "::Object");
		}
		RETVAL->perl_obj = copy_xs_ea_object(value);
		ea_obj->eo_item.ei_object = NULL;
		ea_obj->eo_item.ei_size = 0;
		INIT_EMBED_ITEM_FLAGS(RETVAL);
		break;
	/*
	 * EXT_NONE is an invalid type,
	 * EXT_GROUP is created by the Group subclass constructor.
	 */
	case EXT_NONE:
	case EXT_GROUP:
	default:
		ea_free(RETVAL->ea_obj, sizeof (RETVAL->ea_obj));
		Safefree(RETVAL);
		croak("Invalid object type");
		break;
	}
OUTPUT:
	RETVAL

MODULE = Sun::Solaris::Exacct::Object PACKAGE = Sun::Solaris::Exacct::Object::Group
PROTOTYPES: ENABLE

xs_ea_object_t *
new(class, catalog, ...)
	char	*class;
	SV	*catalog;
PREINIT:
	ea_catalog_t	tag;
	ea_object_t	*ea_obj;
	AV		*tied_av, *av;
	SV		*sv, *rv;
	int		i;
CODE:
	tag = catalog_value(catalog);
	if ((tag & EXT_TYPE_MASK) != EXT_GROUP) {
		croak("Invalid object type");
	}

	/* Create a new xs_ea_object_t and subsiduary structures. */
	New(0, RETVAL, 1, xs_ea_object_t);
	RETVAL->ea_obj = ea_obj = ea_alloc(sizeof (ea_object_t));
	bzero(ea_obj, sizeof (*ea_obj));
	ea_obj->eo_type = EO_GROUP;
	ea_obj->eo_catalog = tag;
	INIT_GROUP_FLAGS(RETVAL);
	RETVAL->perl_obj = NULL;

	/* Create a new AV and copy in all the passed Items. */
	av = newAV();
	av_extend(av, items - 2);
	for (i = 2; i < items; i++) {
		HV	*stash;
		stash = SvROK(ST(i)) ? SvSTASH(SvRV(ST(i))) : NULL;
		if (stash != Sun_Solaris_Exacct_Object_Item_stash &&
		    stash != Sun_Solaris_Exacct_Object_Group_stash) {
			croak("item is not of type " PKGBASE "::Object");
		}
		av_store(av, i - 2, copy_xs_ea_object(ST(i)));
	}

	/* Bless the copied AV and tie it to a new AV */
	rv = newRV_noinc((SV *)av);
	sv_bless(rv, Sun_Solaris_Exacct_Object__Array_stash);
	tied_av = newAV();
	sv_magic((SV *)tied_av, rv, 'P', Nullch, 0);
	SvREFCNT_dec(rv);
	RETVAL->perl_obj = newRV_noinc((SV *)tied_av);
OUTPUT:
	RETVAL

 #
 # Return the contents of the group as a hashref, using the string value of each
 # item's catalog id as the key.  There are two forms - as_hash() which stores
 # each hash value as a scalar, and should be used when it is known the group
 # does not contain duplicate catalog tags, and as_hashlist wich stores each
 # hash value as an array of values, and can therefore be used when the group
 # may contain duplicate catalog tags.
 #

SV *
as_hash(self)
	xs_ea_object_t	*self;
ALIAS:
	as_hashlist = 1
PREINIT:
	MAGIC   *mg;
	HV	*hv;
	AV	*av;
	int	len, i;
CODE:
	/* Make sure the object is inflated. */
	if (self->perl_obj == NULL) {
		if (! inflate_xs_ea_object(self)) {
			XSRETURN_UNDEF;
		}
	}

	/* Find the AV underlying the tie and create the new HV. */
	mg = mg_find(SvRV(self->perl_obj), 'P');
	PERL_ASSERT(mg != NULL);
	av = (AV *)SvRV(mg->mg_obj);
	PERL_ASSERT(av != NULL);
	hv = newHV();

	/*
	 * Traverse the value array, saving the values in the hash,
	 * keyed by the string value of the catalog id field.
	 */
	len = av_len(av) + 1;
	for (i = 0; i < len; i++) {
		SV		**svp, *val;
		xs_ea_object_t	*xs_obj;
		const char	*key;

		/* Ignore undef values. */
		if ((svp = av_fetch(av, i, FALSE)) == NULL) {
			continue;
		}
		PERL_ASSERT(*svp != NULL);

		/* Figure out the key. */
		xs_obj = INT2PTR(xs_ea_object_t *, SvIV(SvRV(*svp)));
		key = catalog_id_str(xs_obj->ea_obj->eo_catalog);

		/*
		 * For Items, save the perl representation
		 * of the underlying ea_object_t.
		 */
		if (IS_ITEM(xs_obj)) {
			switch (xs_obj->ea_obj->eo_catalog & EXT_TYPE_MASK) {
			case EXT_UINT8:
				val =
				    newSVuv(xs_obj->ea_obj->eo_item.ei_uint8);
				break;
			case EXT_UINT16:
				val =
				    newSVuv(xs_obj->ea_obj->eo_item.ei_uint16);
				break;
			case EXT_UINT32:
				val =
				    newSVuv(xs_obj->ea_obj->eo_item.ei_uint32);
				break;
			case EXT_UINT64:
				val =
				    newSVuv(xs_obj->ea_obj->eo_item.ei_uint64);
				break;
			case EXT_DOUBLE:
				val =
				    newSVnv(xs_obj->ea_obj->eo_item.ei_double);
				break;
			case EXT_STRING:
				val =
				    newSVpvn(xs_obj->ea_obj->eo_item.ei_string,
				    xs_obj->ea_obj->eo_item.ei_size - 1);
				break;
			case EXT_RAW:
				val =
				    newSVpvn(xs_obj->ea_obj->eo_item.ei_raw,
				    xs_obj->ea_obj->eo_item.ei_size);
				break;
			/*
			 * For embedded objects and Groups, return a ref
			 * to the perl SV.
			 */
			case EXT_EXACCT_OBJECT:
				if (xs_obj->perl_obj == NULL) {
					/* Make sure the object is inflated. */
					if (! inflate_xs_ea_object(xs_obj)) {
						SvREFCNT_dec(hv);
						XSRETURN_UNDEF;
					}
				}
				val = SvREFCNT_inc(xs_obj->perl_obj);
				break;
			case EXT_GROUP:
				val = SvREFCNT_inc(xs_obj->perl_obj);
				break;
			case EXT_NONE:
			default:
				croak("Invalid object type");
				break;
			}
		/*
		 * Now we deal with Groups.
		 */
		} else {
			/* Make sure the object is inflated. */
			if (xs_obj->perl_obj == NULL) {
				if (! inflate_xs_ea_object(xs_obj)) {
					SvREFCNT_dec(hv);
					XSRETURN_UNDEF;
				}
			}
			val = SvREFCNT_inc(xs_obj->perl_obj);
		}

		/*
		 * If called as as_hash(), store the value directly in the
		 * hash, if called as as_hashlist(), store the value in an
		 * array within the hash.
		 */
		if (ix == 0) {
			hv_store(hv, key, strlen(key), val, FALSE);
		} else {
			AV *ary;

			/* If the key already exists in the hash. */
			svp = hv_fetch(hv, key, strlen(key), TRUE);
			if (SvOK(*svp)) {
				ary = (AV *)SvRV(*svp);

			/* Otherwise, add a new array to the hash. */
			} else {
				SV *rv;
				ary = newAV();
				rv = newRV_noinc((SV *)ary);
				sv_setsv(*svp, rv);
				SvREFCNT_dec(rv);
			}
			av_push(ary, val);
		}
	}
	RETVAL = newRV_noinc((SV *)hv);
OUTPUT:
	RETVAL

MODULE = Sun::Solaris::Exacct::Object PACKAGE = Sun::Solaris::Exacct::Object::_Array
PROTOTYPES: ENABLE

 #
 # Copy the passed list of xs_ea_object_t.
 #
void
copy_xs_ea_objects(...)
PREINIT:
	int	i;
PPCODE:
	EXTEND(SP, items);
	for (i = 0; i < items; i++) {
		HV	*stash;
		stash = SvROK(ST(i)) ? SvSTASH(SvRV(ST(i))) : NULL;
		if (stash != Sun_Solaris_Exacct_Object_Item_stash &&
		    stash != Sun_Solaris_Exacct_Object_Group_stash) {
			croak("item is not of type " PKGBASE "::Object");
		}
		PUSHs(sv_2mortal(copy_xs_ea_object(ST(i))));
	}
