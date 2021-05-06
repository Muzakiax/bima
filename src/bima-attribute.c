/* Generated by GOB (v2.0.13)   (do not edit directly) */

/* End world hunger, donate to the World Food Programme, http://www.wfp.org */

#define GOB_VERSION_MAJOR 2
#define GOB_VERSION_MINOR 0
#define GOB_VERSION_PATCHLEVEL 13

#define selfp (self->_priv)

#include <string.h> /* memset() */

#include "bima-attribute.h"

#ifdef G_LIKELY
#define ___GOB_LIKELY(expr) G_LIKELY(expr)
#define ___GOB_UNLIKELY(expr) G_UNLIKELY(expr)
#else /* ! G_LIKELY */
#define ___GOB_LIKELY(expr) (expr)
#define ___GOB_UNLIKELY(expr) (expr)
#endif /* G_LIKELY */
/* self casting macros */
#define SELF(x) BIMA_ATTRIBUTE(x)
#define SELF_CONST(x) BIMA_ATTRIBUTE_CONST(x)
#define IS_SELF(x) BIMA_IS_ATTRIBUTE(x)
#define TYPE_SELF BIMA_TYPE_ATTRIBUTE
#define SELF_CLASS(x) BIMA_ATTRIBUTE_CLASS(x)

#define SELF_GET_CLASS(x) BIMA_ATTRIBUTE_GET_CLASS(x)

/* self typedefs */
typedef BimaAttribute Self;
typedef BimaAttributeClass SelfClass;

/* here are local prototypes */
static void ___object_set_property (GObject *object, guint property_id, const GValue *value, GParamSpec *pspec);
static void ___object_get_property (GObject *object, guint property_id, GValue *value, GParamSpec *pspec);
static void bima_attribute_init (BimaAttribute * o) G_GNUC_UNUSED;
static void bima_attribute_class_init (BimaAttributeClass * c) G_GNUC_UNUSED;

enum {
	PROP_0,
	PROP_ID,
	PROP_NAME,
	PROP_TITLE,
	PROP_NOT_NULL,
	PROP_FIELD_TYPE,
	PROP_LENGTH,
	PROP_CONTROL_TYPE,
	PROP_PARAMETER,
	PROP_DESCRIPTION
};

/* pointer to the class of our parent */
static GObjectClass *parent_class = NULL;

/* Short form macros */
#define self_get_id bima_attribute_get_id
#define self_set_id bima_attribute_set_id
#define self_get_name bima_attribute_get_name
#define self_set_name bima_attribute_set_name
#define self_get_title bima_attribute_get_title
#define self_set_title bima_attribute_set_title
#define self_get_not_null bima_attribute_get_not_null
#define self_set_not_null bima_attribute_set_not_null
#define self_get_field_type bima_attribute_get_field_type
#define self_set_field_type bima_attribute_set_field_type
#define self_get_length bima_attribute_get_length
#define self_set_length bima_attribute_set_length
#define self_get_control_type bima_attribute_get_control_type
#define self_set_control_type bima_attribute_set_control_type
#define self_get_parameter bima_attribute_get_parameter
#define self_set_parameter bima_attribute_set_parameter
#define self_get_description bima_attribute_get_description
#define self_set_description bima_attribute_set_description
#define self_copy bima_attribute_copy
#define self_write_to_xml bima_attribute_write_to_xml
#define self_new bima_attribute_new
GType
bima_attribute_get_type (void)
{
	static GType type = 0;

	if ___GOB_UNLIKELY(type == 0) {
		static const GTypeInfo info = {
			sizeof (BimaAttributeClass),
			(GBaseInitFunc) NULL,
			(GBaseFinalizeFunc) NULL,
			(GClassInitFunc) bima_attribute_class_init,
			(GClassFinalizeFunc) NULL,
			NULL /* class_data */,
			sizeof (BimaAttribute),
			0 /* n_preallocs */,
			(GInstanceInitFunc) bima_attribute_init,
			NULL
		};

		type = g_type_register_static (G_TYPE_OBJECT, "BimaAttribute", &info, (GTypeFlags)0);
	}

	return type;
}

/* a macro for creating a new object of our type */
#define GET_NEW ((BimaAttribute *)g_object_new(bima_attribute_get_type(), NULL))

/* a function for creating a new object of our type */
#include <stdarg.h>
static BimaAttribute * GET_NEW_VARG (const char *first, ...) G_GNUC_UNUSED;
static BimaAttribute *
GET_NEW_VARG (const char *first, ...)
{
	BimaAttribute *ret;
	va_list ap;
	va_start (ap, first);
	ret = (BimaAttribute *)g_object_new_valist (bima_attribute_get_type (), first, ap);
	va_end (ap);
	return ret;
}


static void
___finalize(GObject *obj_self)
{
#define __GOB_FUNCTION__ "Bima:Attribute::finalize"
	BimaAttribute *self G_GNUC_UNUSED = BIMA_ATTRIBUTE (obj_self);
	if(G_OBJECT_CLASS(parent_class)->finalize) \
		(* G_OBJECT_CLASS(parent_class)->finalize)(obj_self);
#line 38 "attribute.gob"
	if(self->id) { g_free ((gpointer) self->id); self->id = NULL; }
#line 132 "bima-attribute.c"
#line 47 "attribute.gob"
	if(self->name) { g_free ((gpointer) self->name); self->name = NULL; }
#line 135 "bima-attribute.c"
#line 56 "attribute.gob"
	if(self->title) { g_free ((gpointer) self->title); self->title = NULL; }
#line 138 "bima-attribute.c"
#line 78 "attribute.gob"
	if(self->field_type) { g_free ((gpointer) self->field_type); self->field_type = NULL; }
#line 141 "bima-attribute.c"
#line 97 "attribute.gob"
	if(self->control_type) { g_free ((gpointer) self->control_type); self->control_type = NULL; }
#line 144 "bima-attribute.c"
#line 107 "attribute.gob"
	if(self->parameter) { g_free ((gpointer) self->parameter); self->parameter = NULL; }
#line 147 "bima-attribute.c"
#line 116 "attribute.gob"
	if(self->description) { g_free ((gpointer) self->description); self->description = NULL; }
#line 150 "bima-attribute.c"
#define parent (self->parent)
#define VAR parent
	{
#line 125 "attribute.gob"
	
			parent = NULL;
		}
#line 158 "bima-attribute.c"
	memset(&parent, 0, sizeof(parent));
#undef VAR
#undef parent
}
#undef __GOB_FUNCTION__

static void 
bima_attribute_init (BimaAttribute * o G_GNUC_UNUSED)
{
#define __GOB_FUNCTION__ "Bima:Attribute::init"
#line 24 "attribute.gob"
	o->id = NULL;
#line 171 "bima-attribute.c"
#line 24 "attribute.gob"
	o->name = NULL;
#line 174 "bima-attribute.c"
#line 24 "attribute.gob"
	o->title = NULL;
#line 177 "bima-attribute.c"
#line 24 "attribute.gob"
	o->is_key = FALSE;
#line 180 "bima-attribute.c"
#line 24 "attribute.gob"
	o->is_weak = FALSE;
#line 183 "bima-attribute.c"
#line 24 "attribute.gob"
	o->is_derived = FALSE;
#line 186 "bima-attribute.c"
#line 24 "attribute.gob"
	o->is_multivalued = FALSE;
#line 189 "bima-attribute.c"
#line 24 "attribute.gob"
	o->not_null = FALSE;
#line 192 "bima-attribute.c"
#line 77 "attribute.gob"
	o->field_type =  g_strdup("varchar");;
#line 195 "bima-attribute.c"
#line 77 "attribute.gob"
	o->length = 25;
#line 198 "bima-attribute.c"
#line 96 "attribute.gob"
	o->control_type =  g_strdup("Text");;
#line 201 "bima-attribute.c"
#line 96 "attribute.gob"
	o->parameter = NULL;
#line 204 "bima-attribute.c"
#line 96 "attribute.gob"
	o->description = NULL;
#line 207 "bima-attribute.c"
#line 96 "attribute.gob"
	o->parent = NULL;
#line 210 "bima-attribute.c"
#line 125 "attribute.gob"
	o->attribute_type = ATTRIBUTE;
#line 213 "bima-attribute.c"
}
#undef __GOB_FUNCTION__
static void 
bima_attribute_class_init (BimaAttributeClass * c G_GNUC_UNUSED)
{
#define __GOB_FUNCTION__ "Bima:Attribute::class_init"
	GObjectClass *g_object_class G_GNUC_UNUSED = (GObjectClass*) c;

	parent_class = g_type_class_ref (G_TYPE_OBJECT);

	g_object_class->finalize = ___finalize;
	g_object_class->get_property = ___object_get_property;
	g_object_class->set_property = ___object_set_property;
    {
	GParamSpec   *param_spec;

	param_spec = g_param_spec_string
		("id" /* name */,
		 "id" /* nick */,
		 "id of attribute" /* blurb */,
		 NULL /* default_value */,
		 (GParamFlags)(G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (g_object_class,
		PROP_ID,
		param_spec);
	param_spec = g_param_spec_string
		("name" /* name */,
		 "name" /* nick */,
		 "name of attribute" /* blurb */,
		 NULL /* default_value */,
		 (GParamFlags)(G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (g_object_class,
		PROP_NAME,
		param_spec);
	param_spec = g_param_spec_string
		("title" /* name */,
		 "title" /* nick */,
		 "title of attribute" /* blurb */,
		 NULL /* default_value */,
		 (GParamFlags)(G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (g_object_class,
		PROP_TITLE,
		param_spec);
	param_spec = g_param_spec_boolean
		("not_null" /* name */,
		 "not_null" /* nick */,
		 "not_null of attribute" /* blurb */,
		 NULL /* default_value */,
		 (GParamFlags)(G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (g_object_class,
		PROP_NOT_NULL,
		param_spec);
	param_spec = g_param_spec_string
		("field_type" /* name */,
		 "field_type" /* nick */,
		 "field_type of attribute" /* blurb */,
		 NULL /* default_value */,
		 (GParamFlags)(G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (g_object_class,
		PROP_FIELD_TYPE,
		param_spec);
	param_spec = g_param_spec_int
		("length" /* name */,
		 "length" /* nick */,
		 "length of attribute" /* blurb */,
		 G_MININT /* minimum */,
		 G_MAXINT /* maximum */,
		 NULL /* default_value */,
		 (GParamFlags)(G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (g_object_class,
		PROP_LENGTH,
		param_spec);
	param_spec = g_param_spec_string
		("control_type" /* name */,
		 "control_type" /* nick */,
		 "control_type of attribute" /* blurb */,
		 NULL /* default_value */,
		 (GParamFlags)(G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (g_object_class,
		PROP_CONTROL_TYPE,
		param_spec);
	param_spec = g_param_spec_string
		("parameter" /* name */,
		 "parameter" /* nick */,
		 "parameter of attribute" /* blurb */,
		 NULL /* default_value */,
		 (GParamFlags)(G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (g_object_class,
		PROP_PARAMETER,
		param_spec);
	param_spec = g_param_spec_string
		("description" /* name */,
		 "description" /* nick */,
		 "description of attribute" /* blurb */,
		 NULL /* default_value */,
		 (GParamFlags)(G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (g_object_class,
		PROP_DESCRIPTION,
		param_spec);
    }
}
#undef __GOB_FUNCTION__

static void
___object_set_property (GObject *object,
	guint property_id,
	const GValue *VAL G_GNUC_UNUSED,
	GParamSpec *pspec G_GNUC_UNUSED)
#define __GOB_FUNCTION__ "Bima:Attribute::set_property"
{
	BimaAttribute *self G_GNUC_UNUSED;

	self = BIMA_ATTRIBUTE (object);

	switch (property_id) {
	case PROP_ID:
		{
#line 39 "attribute.gob"
{ char *old = self->id; self->id = g_value_dup_string (VAL); g_free (old); }
#line 333 "bima-attribute.c"
		}
		break;
	case PROP_NAME:
		{
#line 48 "attribute.gob"
{ char *old = self->name; self->name = g_value_dup_string (VAL); g_free (old); }
#line 340 "bima-attribute.c"
		}
		break;
	case PROP_TITLE:
		{
#line 57 "attribute.gob"
{ char *old = self->title; self->title = g_value_dup_string (VAL); g_free (old); }
#line 347 "bima-attribute.c"
		}
		break;
	case PROP_NOT_NULL:
		{
#line 69 "attribute.gob"
self->not_null = g_value_get_boolean (VAL);
#line 354 "bima-attribute.c"
		}
		break;
	case PROP_FIELD_TYPE:
		{
#line 79 "attribute.gob"
{ char *old = self->field_type; self->field_type = g_value_dup_string (VAL); g_free (old); }
#line 361 "bima-attribute.c"
		}
		break;
	case PROP_LENGTH:
		{
#line 88 "attribute.gob"
self->length = g_value_get_int (VAL);
#line 368 "bima-attribute.c"
		}
		break;
	case PROP_CONTROL_TYPE:
		{
#line 98 "attribute.gob"
{ char *old = self->control_type; self->control_type = g_value_dup_string (VAL); g_free (old); }
#line 375 "bima-attribute.c"
		}
		break;
	case PROP_PARAMETER:
		{
#line 108 "attribute.gob"
{ char *old = self->parameter; self->parameter = g_value_dup_string (VAL); g_free (old); }
#line 382 "bima-attribute.c"
		}
		break;
	case PROP_DESCRIPTION:
		{
#line 117 "attribute.gob"
{ char *old = self->description; self->description = g_value_dup_string (VAL); g_free (old); }
#line 389 "bima-attribute.c"
		}
		break;
	default:
/* Apparently in g++ this is needed, glib is b0rk */
#ifndef __PRETTY_FUNCTION__
#  undef G_STRLOC
#  define G_STRLOC	__FILE__ ":" G_STRINGIFY (__LINE__)
#endif
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}
#undef __GOB_FUNCTION__

static void
___object_get_property (GObject *object,
	guint property_id,
	GValue *VAL G_GNUC_UNUSED,
	GParamSpec *pspec G_GNUC_UNUSED)
#define __GOB_FUNCTION__ "Bima:Attribute::get_property"
{
	BimaAttribute *self G_GNUC_UNUSED;

	self = BIMA_ATTRIBUTE (object);

	switch (property_id) {
	case PROP_ID:
		{
#line 39 "attribute.gob"
g_value_set_string (VAL, self->id);
#line 420 "bima-attribute.c"
		}
		break;
	case PROP_NAME:
		{
#line 48 "attribute.gob"
g_value_set_string (VAL, self->name);
#line 427 "bima-attribute.c"
		}
		break;
	case PROP_TITLE:
		{
#line 57 "attribute.gob"
g_value_set_string (VAL, self->title);
#line 434 "bima-attribute.c"
		}
		break;
	case PROP_NOT_NULL:
		{
#line 69 "attribute.gob"
g_value_set_boolean (VAL, self->not_null);
#line 441 "bima-attribute.c"
		}
		break;
	case PROP_FIELD_TYPE:
		{
#line 79 "attribute.gob"
g_value_set_string (VAL, self->field_type);
#line 448 "bima-attribute.c"
		}
		break;
	case PROP_LENGTH:
		{
#line 88 "attribute.gob"
g_value_set_int (VAL, self->length);
#line 455 "bima-attribute.c"
		}
		break;
	case PROP_CONTROL_TYPE:
		{
#line 98 "attribute.gob"
g_value_set_string (VAL, self->control_type);
#line 462 "bima-attribute.c"
		}
		break;
	case PROP_PARAMETER:
		{
#line 108 "attribute.gob"
g_value_set_string (VAL, self->parameter);
#line 469 "bima-attribute.c"
		}
		break;
	case PROP_DESCRIPTION:
		{
#line 117 "attribute.gob"
g_value_set_string (VAL, self->description);
#line 476 "bima-attribute.c"
		}
		break;
	default:
/* Apparently in g++ this is needed, glib is b0rk */
#ifndef __PRETTY_FUNCTION__
#  undef G_STRLOC
#  define G_STRLOC	__FILE__ ":" G_STRINGIFY (__LINE__)
#endif
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}
#undef __GOB_FUNCTION__



#line 39 "attribute.gob"
gchar * 
bima_attribute_get_id (BimaAttribute * self)
#line 496 "bima-attribute.c"
{
#define __GOB_FUNCTION__ "Bima:Attribute::get_id"
{
#line 39 "attribute.gob"
		gchar* val; g_object_get (G_OBJECT (self), "id", &val, NULL); return val;
}}
#line 503 "bima-attribute.c"
#undef __GOB_FUNCTION__

#line 39 "attribute.gob"
void 
bima_attribute_set_id (BimaAttribute * self, gchar * val)
#line 509 "bima-attribute.c"
{
#define __GOB_FUNCTION__ "Bima:Attribute::set_id"
{
#line 39 "attribute.gob"
		g_object_set (G_OBJECT (self), "id", val, NULL);
}}
#line 516 "bima-attribute.c"
#undef __GOB_FUNCTION__

#line 48 "attribute.gob"
gchar * 
bima_attribute_get_name (BimaAttribute * self)
#line 522 "bima-attribute.c"
{
#define __GOB_FUNCTION__ "Bima:Attribute::get_name"
{
#line 48 "attribute.gob"
		gchar* val; g_object_get (G_OBJECT (self), "name", &val, NULL); return val;
}}
#line 529 "bima-attribute.c"
#undef __GOB_FUNCTION__

#line 48 "attribute.gob"
void 
bima_attribute_set_name (BimaAttribute * self, gchar * val)
#line 535 "bima-attribute.c"
{
#define __GOB_FUNCTION__ "Bima:Attribute::set_name"
{
#line 48 "attribute.gob"
		g_object_set (G_OBJECT (self), "name", val, NULL);
}}
#line 542 "bima-attribute.c"
#undef __GOB_FUNCTION__

#line 57 "attribute.gob"
gchar * 
bima_attribute_get_title (BimaAttribute * self)
#line 548 "bima-attribute.c"
{
#define __GOB_FUNCTION__ "Bima:Attribute::get_title"
{
#line 57 "attribute.gob"
		gchar* val; g_object_get (G_OBJECT (self), "title", &val, NULL); return val;
}}
#line 555 "bima-attribute.c"
#undef __GOB_FUNCTION__

#line 57 "attribute.gob"
void 
bima_attribute_set_title (BimaAttribute * self, gchar * val)
#line 561 "bima-attribute.c"
{
#define __GOB_FUNCTION__ "Bima:Attribute::set_title"
{
#line 57 "attribute.gob"
		g_object_set (G_OBJECT (self), "title", val, NULL);
}}
#line 568 "bima-attribute.c"
#undef __GOB_FUNCTION__

#line 69 "attribute.gob"
gboolean 
bima_attribute_get_not_null (BimaAttribute * self)
#line 574 "bima-attribute.c"
{
#define __GOB_FUNCTION__ "Bima:Attribute::get_not_null"
{
#line 69 "attribute.gob"
		gboolean val; g_object_get (G_OBJECT (self), "not_null", &val, NULL); return val;
}}
#line 581 "bima-attribute.c"
#undef __GOB_FUNCTION__

#line 69 "attribute.gob"
void 
bima_attribute_set_not_null (BimaAttribute * self, gboolean val)
#line 587 "bima-attribute.c"
{
#define __GOB_FUNCTION__ "Bima:Attribute::set_not_null"
{
#line 69 "attribute.gob"
		g_object_set (G_OBJECT (self), "not_null", val, NULL);
}}
#line 594 "bima-attribute.c"
#undef __GOB_FUNCTION__

#line 79 "attribute.gob"
gchar * 
bima_attribute_get_field_type (BimaAttribute * self)
#line 600 "bima-attribute.c"
{
#define __GOB_FUNCTION__ "Bima:Attribute::get_field_type"
{
#line 79 "attribute.gob"
		gchar* val; g_object_get (G_OBJECT (self), "field_type", &val, NULL); return val;
}}
#line 607 "bima-attribute.c"
#undef __GOB_FUNCTION__

#line 79 "attribute.gob"
void 
bima_attribute_set_field_type (BimaAttribute * self, gchar * val)
#line 613 "bima-attribute.c"
{
#define __GOB_FUNCTION__ "Bima:Attribute::set_field_type"
{
#line 79 "attribute.gob"
		g_object_set (G_OBJECT (self), "field_type", val, NULL);
}}
#line 620 "bima-attribute.c"
#undef __GOB_FUNCTION__

#line 88 "attribute.gob"
gint 
bima_attribute_get_length (BimaAttribute * self)
#line 626 "bima-attribute.c"
{
#define __GOB_FUNCTION__ "Bima:Attribute::get_length"
{
#line 88 "attribute.gob"
		gint val; g_object_get (G_OBJECT (self), "length", &val, NULL); return val;
}}
#line 633 "bima-attribute.c"
#undef __GOB_FUNCTION__

#line 88 "attribute.gob"
void 
bima_attribute_set_length (BimaAttribute * self, gint val)
#line 639 "bima-attribute.c"
{
#define __GOB_FUNCTION__ "Bima:Attribute::set_length"
{
#line 88 "attribute.gob"
		g_object_set (G_OBJECT (self), "length", val, NULL);
}}
#line 646 "bima-attribute.c"
#undef __GOB_FUNCTION__

#line 98 "attribute.gob"
gchar * 
bima_attribute_get_control_type (BimaAttribute * self)
#line 652 "bima-attribute.c"
{
#define __GOB_FUNCTION__ "Bima:Attribute::get_control_type"
{
#line 98 "attribute.gob"
		gchar* val; g_object_get (G_OBJECT (self), "control_type", &val, NULL); return val;
}}
#line 659 "bima-attribute.c"
#undef __GOB_FUNCTION__

#line 98 "attribute.gob"
void 
bima_attribute_set_control_type (BimaAttribute * self, gchar * val)
#line 665 "bima-attribute.c"
{
#define __GOB_FUNCTION__ "Bima:Attribute::set_control_type"
{
#line 98 "attribute.gob"
		g_object_set (G_OBJECT (self), "control_type", val, NULL);
}}
#line 672 "bima-attribute.c"
#undef __GOB_FUNCTION__

#line 108 "attribute.gob"
gchar * 
bima_attribute_get_parameter (BimaAttribute * self)
#line 678 "bima-attribute.c"
{
#define __GOB_FUNCTION__ "Bima:Attribute::get_parameter"
{
#line 108 "attribute.gob"
		gchar* val; g_object_get (G_OBJECT (self), "parameter", &val, NULL); return val;
}}
#line 685 "bima-attribute.c"
#undef __GOB_FUNCTION__

#line 108 "attribute.gob"
void 
bima_attribute_set_parameter (BimaAttribute * self, gchar * val)
#line 691 "bima-attribute.c"
{
#define __GOB_FUNCTION__ "Bima:Attribute::set_parameter"
{
#line 108 "attribute.gob"
		g_object_set (G_OBJECT (self), "parameter", val, NULL);
}}
#line 698 "bima-attribute.c"
#undef __GOB_FUNCTION__

#line 117 "attribute.gob"
gchar * 
bima_attribute_get_description (BimaAttribute * self)
#line 704 "bima-attribute.c"
{
#define __GOB_FUNCTION__ "Bima:Attribute::get_description"
{
#line 117 "attribute.gob"
		gchar* val; g_object_get (G_OBJECT (self), "description", &val, NULL); return val;
}}
#line 711 "bima-attribute.c"
#undef __GOB_FUNCTION__

#line 117 "attribute.gob"
void 
bima_attribute_set_description (BimaAttribute * self, gchar * val)
#line 717 "bima-attribute.c"
{
#define __GOB_FUNCTION__ "Bima:Attribute::set_description"
{
#line 117 "attribute.gob"
		g_object_set (G_OBJECT (self), "description", val, NULL);
}}
#line 724 "bima-attribute.c"
#undef __GOB_FUNCTION__

#line 131 "attribute.gob"
BimaAttribute * 
bima_attribute_copy (BimaAttribute * self)
#line 730 "bima-attribute.c"
{
#define __GOB_FUNCTION__ "Bima:Attribute::copy"
#line 131 "attribute.gob"
	g_return_val_if_fail (self != NULL, (BimaAttribute * )0);
#line 131 "attribute.gob"
	g_return_val_if_fail (BIMA_IS_ATTRIBUTE (self), (BimaAttribute * )0);
#line 737 "bima-attribute.c"
{
#line 133 "attribute.gob"
	
		BimaAttribute* attr = GET_NEW;
		attr->id = g_strdup(self->id);
		attr->name = g_strdup(self->name);
		attr->is_key = self->is_key ;
		attr->is_weak = self->is_weak ;
		attr->not_null = self->not_null ;
		attr->field_type = g_strdup(self->field_type) ;
		attr->length = self->length ;
		attr->control_type = g_strdup(self->control_type);
		attr->attribute_type = self->attribute_type;
		
		if (self->title)
			attr->title = g_strdup(self->title);
		
		if (self->parameter)
			attr->parameter = g_strdup(self->parameter);

		if (self->description)
			attr->description = g_strdup(self->description);
			
		return attr;
	}}
#line 763 "bima-attribute.c"
#undef __GOB_FUNCTION__

#line 157 "attribute.gob"
void 
bima_attribute_write_to_xml (BimaAttribute * self, FILE * ofile)
#line 769 "bima-attribute.c"
{
#define __GOB_FUNCTION__ "Bima:Attribute::write_to_xml"
#line 157 "attribute.gob"
	g_return_if_fail (self != NULL);
#line 157 "attribute.gob"
	g_return_if_fail (BIMA_IS_ATTRIBUTE (self));
#line 776 "bima-attribute.c"
{
#line 159 "attribute.gob"
	
		fprintf(ofile, "\t\t\t<Attribute id=\"%s\" name=\"%s\" is_key=\"%d\" is_weak=\"%d\" not_null=\"%d\" field_type=\"%s\" length=\"%d\" control_type=\"%s\">\n", \ 
			self->id , self->name, self->is_key, self->is_weak, self->not_null, self->field_type , self->length, self->control_type);

		if (self->title)
			fprintf(ofile, "\t\t\t\t<Title>%s</Title>\n", self->title);
		
		if (self->parameter)
			fprintf(ofile, "\t\t\t\t<Parameter>%s</Parameter>\n", self->parameter);

		if (self->description)
			fprintf(ofile, "\t\t\t\t<Description>%s</Description>\n", self->description);
			
		fprintf(ofile, "\t\t\t</Attribute>\n");
	}}
#line 794 "bima-attribute.c"
#undef __GOB_FUNCTION__

#line 175 "attribute.gob"
BimaAttribute * 
bima_attribute_new (void)
#line 800 "bima-attribute.c"
{
#define __GOB_FUNCTION__ "Bima:Attribute::new"
{
#line 177 "attribute.gob"
	
		return GET_NEW;
	}}
#line 808 "bima-attribute.c"
#undef __GOB_FUNCTION__
