/* Generated by GOB (v2.0.13)   (do not edit directly) */

/* End world hunger, donate to the World Food Programme, http://www.wfp.org */

#define GOB_VERSION_MAJOR 2
#define GOB_VERSION_MINOR 0
#define GOB_VERSION_PATCHLEVEL 13

#define selfp (self->_priv)

#include <string.h> /* memset() */

#include "bima-report.h"

#ifdef G_LIKELY
#define ___GOB_LIKELY(expr) G_LIKELY(expr)
#define ___GOB_UNLIKELY(expr) G_UNLIKELY(expr)
#else /* ! G_LIKELY */
#define ___GOB_LIKELY(expr) (expr)
#define ___GOB_UNLIKELY(expr) (expr)
#endif /* G_LIKELY */
/* self casting macros */
#define SELF(x) BIMA_REPORT(x)
#define SELF_CONST(x) BIMA_REPORT_CONST(x)
#define IS_SELF(x) BIMA_IS_REPORT(x)
#define TYPE_SELF BIMA_TYPE_REPORT
#define SELF_CLASS(x) BIMA_REPORT_CLASS(x)

#define SELF_GET_CLASS(x) BIMA_REPORT_GET_CLASS(x)

/* self typedefs */
typedef BimaReport Self;
typedef BimaReportClass SelfClass;

/* here are local prototypes */
static void ___object_set_property (GObject *object, guint property_id, const GValue *value, GParamSpec *pspec);
static void ___object_get_property (GObject *object, guint property_id, GValue *value, GParamSpec *pspec);
static void bima_report_init (BimaReport * o) G_GNUC_UNUSED;
static void bima_report_class_init (BimaReportClass * c) G_GNUC_UNUSED;

enum {
	PROP_0,
	PROP_ID,
	PROP_NAME,
	PROP_TITLE,
	PROP_PRIMARY_OBJ_ID,
	PROP_DESCRIPTION,
	PROP_SQL_TEXT
};

/* pointer to the class of our parent */
static GObjectClass *parent_class = NULL;

/* Short form macros */
#define self_get_id bima_report_get_id
#define self_set_id bima_report_set_id
#define self_get_name bima_report_get_name
#define self_set_name bima_report_set_name
#define self_get_title bima_report_get_title
#define self_set_title bima_report_set_title
#define self_get_primary_obj_id bima_report_get_primary_obj_id
#define self_set_primary_obj_id bima_report_set_primary_obj_id
#define self_get_description bima_report_get_description
#define self_set_description bima_report_set_description
#define self_get_sql_text bima_report_get_sql_text
#define self_set_sql_text bima_report_set_sql_text
#define self_new bima_report_new
GType
bima_report_get_type (void)
{
	static GType type = 0;

	if ___GOB_UNLIKELY(type == 0) {
		static const GTypeInfo info = {
			sizeof (BimaReportClass),
			(GBaseInitFunc) NULL,
			(GBaseFinalizeFunc) NULL,
			(GClassInitFunc) bima_report_class_init,
			(GClassFinalizeFunc) NULL,
			NULL /* class_data */,
			sizeof (BimaReport),
			0 /* n_preallocs */,
			(GInstanceInitFunc) bima_report_init,
			NULL
		};

		type = g_type_register_static (G_TYPE_OBJECT, "BimaReport", &info, (GTypeFlags)0);
	}

	return type;
}

/* a macro for creating a new object of our type */
#define GET_NEW ((BimaReport *)g_object_new(bima_report_get_type(), NULL))

/* a function for creating a new object of our type */
#include <stdarg.h>
static BimaReport * GET_NEW_VARG (const char *first, ...) G_GNUC_UNUSED;
static BimaReport *
GET_NEW_VARG (const char *first, ...)
{
	BimaReport *ret;
	va_list ap;
	va_start (ap, first);
	ret = (BimaReport *)g_object_new_valist (bima_report_get_type (), first, ap);
	va_end (ap);
	return ret;
}


static void
___finalize(GObject *obj_self)
{
#define __GOB_FUNCTION__ "Bima:Report::finalize"
	BimaReport *self G_GNUC_UNUSED = BIMA_REPORT (obj_self);
	if(G_OBJECT_CLASS(parent_class)->finalize) \
		(* G_OBJECT_CLASS(parent_class)->finalize)(obj_self);
#line 5 "report.gob"
	if(self->id) { g_free ((gpointer) self->id); self->id = NULL; }
#line 121 "bima-report.c"
#line 14 "report.gob"
	if(self->name) { g_free ((gpointer) self->name); self->name = NULL; }
#line 124 "bima-report.c"
#line 24 "report.gob"
	if(self->title) { g_free ((gpointer) self->title); self->title = NULL; }
#line 127 "bima-report.c"
#line 34 "report.gob"
	if(self->primary_obj_id) { g_free ((gpointer) self->primary_obj_id); self->primary_obj_id = NULL; }
#line 130 "bima-report.c"
#line 44 "report.gob"
	if(self->description) { g_free ((gpointer) self->description); self->description = NULL; }
#line 133 "bima-report.c"
#line 54 "report.gob"
	if(self->sql_text) { g_free ((gpointer) self->sql_text); self->sql_text = NULL; }
#line 136 "bima-report.c"
#line 64 "report.gob"
	if(self->template_id) { g_free ((gpointer) self->template_id); self->template_id = NULL; }
#line 139 "bima-report.c"
}
#undef __GOB_FUNCTION__

static void 
bima_report_init (BimaReport * o G_GNUC_UNUSED)
{
#define __GOB_FUNCTION__ "Bima:Report::init"
#line 4 "report.gob"
	o->id =  NULL ;
#line 149 "bima-report.c"
#line 13 "report.gob"
	o->name =  NULL ;
#line 152 "bima-report.c"
#line 13 "report.gob"
	o->title = NULL;
#line 155 "bima-report.c"
#line 33 "report.gob"
	o->primary_obj_id =  NULL ;
#line 158 "bima-report.c"
#line 43 "report.gob"
	o->description =  NULL ;
#line 161 "bima-report.c"
#line 53 "report.gob"
	o->sql_text =  NULL ;
#line 164 "bima-report.c"
#line 63 "report.gob"
	o->template_id =  NULL ;
#line 167 "bima-report.c"
}
#undef __GOB_FUNCTION__
static void 
bima_report_class_init (BimaReportClass * c G_GNUC_UNUSED)
{
#define __GOB_FUNCTION__ "Bima:Report::class_init"
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
		 "id of entity" /* blurb */,
		 NULL /* default_value */,
		 (GParamFlags)(G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (g_object_class,
		PROP_ID,
		param_spec);
	param_spec = g_param_spec_string
		("name" /* name */,
		 "name" /* nick */,
		 "name of entity" /* blurb */,
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
	param_spec = g_param_spec_string
		("primary_obj_id" /* name */,
		 "primary_obj_id" /* nick */,
		 "id of obj" /* blurb */,
		 NULL /* default_value */,
		 (GParamFlags)(G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (g_object_class,
		PROP_PRIMARY_OBJ_ID,
		param_spec);
	param_spec = g_param_spec_string
		("description" /* name */,
		 "description" /* nick */,
		 "description of entity" /* blurb */,
		 NULL /* default_value */,
		 (GParamFlags)(G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (g_object_class,
		PROP_DESCRIPTION,
		param_spec);
	param_spec = g_param_spec_string
		("sql_text" /* name */,
		 "sql_text" /* nick */,
		 "sql_text of view" /* blurb */,
		 NULL /* default_value */,
		 (GParamFlags)(G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (g_object_class,
		PROP_SQL_TEXT,
		param_spec);
    }
}
#undef __GOB_FUNCTION__

static void
___object_set_property (GObject *object,
	guint property_id,
	const GValue *VAL G_GNUC_UNUSED,
	GParamSpec *pspec G_GNUC_UNUSED)
#define __GOB_FUNCTION__ "Bima:Report::set_property"
{
	BimaReport *self G_GNUC_UNUSED;

	self = BIMA_REPORT (object);

	switch (property_id) {
	case PROP_ID:
		{
#line 6 "report.gob"
{ char *old = self->id; self->id = g_value_dup_string (VAL); g_free (old); }
#line 258 "bima-report.c"
		}
		break;
	case PROP_NAME:
		{
#line 15 "report.gob"
{ char *old = self->name; self->name = g_value_dup_string (VAL); g_free (old); }
#line 265 "bima-report.c"
		}
		break;
	case PROP_TITLE:
		{
#line 25 "report.gob"
{ char *old = self->title; self->title = g_value_dup_string (VAL); g_free (old); }
#line 272 "bima-report.c"
		}
		break;
	case PROP_PRIMARY_OBJ_ID:
		{
#line 35 "report.gob"
{ char *old = self->primary_obj_id; self->primary_obj_id = g_value_dup_string (VAL); g_free (old); }
#line 279 "bima-report.c"
		}
		break;
	case PROP_DESCRIPTION:
		{
#line 45 "report.gob"
{ char *old = self->description; self->description = g_value_dup_string (VAL); g_free (old); }
#line 286 "bima-report.c"
		}
		break;
	case PROP_SQL_TEXT:
		{
#line 55 "report.gob"
{ char *old = self->sql_text; self->sql_text = g_value_dup_string (VAL); g_free (old); }
#line 293 "bima-report.c"
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
#define __GOB_FUNCTION__ "Bima:Report::get_property"
{
	BimaReport *self G_GNUC_UNUSED;

	self = BIMA_REPORT (object);

	switch (property_id) {
	case PROP_ID:
		{
#line 6 "report.gob"
g_value_set_string (VAL, self->id);
#line 324 "bima-report.c"
		}
		break;
	case PROP_NAME:
		{
#line 15 "report.gob"
g_value_set_string (VAL, self->name);
#line 331 "bima-report.c"
		}
		break;
	case PROP_TITLE:
		{
#line 25 "report.gob"
g_value_set_string (VAL, self->title);
#line 338 "bima-report.c"
		}
		break;
	case PROP_PRIMARY_OBJ_ID:
		{
#line 35 "report.gob"
g_value_set_string (VAL, self->primary_obj_id);
#line 345 "bima-report.c"
		}
		break;
	case PROP_DESCRIPTION:
		{
#line 45 "report.gob"
g_value_set_string (VAL, self->description);
#line 352 "bima-report.c"
		}
		break;
	case PROP_SQL_TEXT:
		{
#line 55 "report.gob"
g_value_set_string (VAL, self->sql_text);
#line 359 "bima-report.c"
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



#line 6 "report.gob"
gchar * 
bima_report_get_id (BimaReport * self)
#line 379 "bima-report.c"
{
#define __GOB_FUNCTION__ "Bima:Report::get_id"
{
#line 6 "report.gob"
		gchar* val; g_object_get (G_OBJECT (self), "id", &val, NULL); return val;
}}
#line 386 "bima-report.c"
#undef __GOB_FUNCTION__

#line 6 "report.gob"
void 
bima_report_set_id (BimaReport * self, gchar * val)
#line 392 "bima-report.c"
{
#define __GOB_FUNCTION__ "Bima:Report::set_id"
{
#line 6 "report.gob"
		g_object_set (G_OBJECT (self), "id", val, NULL);
}}
#line 399 "bima-report.c"
#undef __GOB_FUNCTION__

#line 15 "report.gob"
gchar * 
bima_report_get_name (BimaReport * self)
#line 405 "bima-report.c"
{
#define __GOB_FUNCTION__ "Bima:Report::get_name"
{
#line 15 "report.gob"
		gchar* val; g_object_get (G_OBJECT (self), "name", &val, NULL); return val;
}}
#line 412 "bima-report.c"
#undef __GOB_FUNCTION__

#line 15 "report.gob"
void 
bima_report_set_name (BimaReport * self, gchar * val)
#line 418 "bima-report.c"
{
#define __GOB_FUNCTION__ "Bima:Report::set_name"
{
#line 15 "report.gob"
		g_object_set (G_OBJECT (self), "name", val, NULL);
}}
#line 425 "bima-report.c"
#undef __GOB_FUNCTION__

#line 25 "report.gob"
gchar * 
bima_report_get_title (BimaReport * self)
#line 431 "bima-report.c"
{
#define __GOB_FUNCTION__ "Bima:Report::get_title"
{
#line 25 "report.gob"
		gchar* val; g_object_get (G_OBJECT (self), "title", &val, NULL); return val;
}}
#line 438 "bima-report.c"
#undef __GOB_FUNCTION__

#line 25 "report.gob"
void 
bima_report_set_title (BimaReport * self, gchar * val)
#line 444 "bima-report.c"
{
#define __GOB_FUNCTION__ "Bima:Report::set_title"
{
#line 25 "report.gob"
		g_object_set (G_OBJECT (self), "title", val, NULL);
}}
#line 451 "bima-report.c"
#undef __GOB_FUNCTION__

#line 35 "report.gob"
gchar * 
bima_report_get_primary_obj_id (BimaReport * self)
#line 457 "bima-report.c"
{
#define __GOB_FUNCTION__ "Bima:Report::get_primary_obj_id"
{
#line 35 "report.gob"
		gchar* val; g_object_get (G_OBJECT (self), "primary_obj_id", &val, NULL); return val;
}}
#line 464 "bima-report.c"
#undef __GOB_FUNCTION__

#line 35 "report.gob"
void 
bima_report_set_primary_obj_id (BimaReport * self, gchar * val)
#line 470 "bima-report.c"
{
#define __GOB_FUNCTION__ "Bima:Report::set_primary_obj_id"
{
#line 35 "report.gob"
		g_object_set (G_OBJECT (self), "primary_obj_id", val, NULL);
}}
#line 477 "bima-report.c"
#undef __GOB_FUNCTION__

#line 45 "report.gob"
gchar * 
bima_report_get_description (BimaReport * self)
#line 483 "bima-report.c"
{
#define __GOB_FUNCTION__ "Bima:Report::get_description"
{
#line 45 "report.gob"
		gchar* val; g_object_get (G_OBJECT (self), "description", &val, NULL); return val;
}}
#line 490 "bima-report.c"
#undef __GOB_FUNCTION__

#line 45 "report.gob"
void 
bima_report_set_description (BimaReport * self, gchar * val)
#line 496 "bima-report.c"
{
#define __GOB_FUNCTION__ "Bima:Report::set_description"
{
#line 45 "report.gob"
		g_object_set (G_OBJECT (self), "description", val, NULL);
}}
#line 503 "bima-report.c"
#undef __GOB_FUNCTION__

#line 55 "report.gob"
gchar * 
bima_report_get_sql_text (BimaReport * self)
#line 509 "bima-report.c"
{
#define __GOB_FUNCTION__ "Bima:Report::get_sql_text"
{
#line 55 "report.gob"
		gchar* val; g_object_get (G_OBJECT (self), "sql_text", &val, NULL); return val;
}}
#line 516 "bima-report.c"
#undef __GOB_FUNCTION__

#line 55 "report.gob"
void 
bima_report_set_sql_text (BimaReport * self, gchar * val)
#line 522 "bima-report.c"
{
#define __GOB_FUNCTION__ "Bima:Report::set_sql_text"
{
#line 55 "report.gob"
		g_object_set (G_OBJECT (self), "sql_text", val, NULL);
}}
#line 529 "bima-report.c"
#undef __GOB_FUNCTION__

#line 66 "report.gob"
BimaReport * 
bima_report_new (void)
#line 535 "bima-report.c"
{
#define __GOB_FUNCTION__ "Bima:Report::new"
{
#line 68 "report.gob"
	
		return GET_NEW;
	}}
#line 543 "bima-report.c"
#undef __GOB_FUNCTION__
