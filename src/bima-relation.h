/* Generated by GOB (v2.0.13)   (do not edit directly) */

#include <glib.h>
#include <glib-object.h>


#include "bima-attribute.h"
#include "bima-connection.h"
#include "bima-foreign-key.h"

#ifndef __BIMA_RELATION_H__
#define __BIMA_RELATION_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/*
 * Type checking and casting macros
 */
#define BIMA_TYPE_RELATION	(bima_relation_get_type())
#define BIMA_RELATION(obj)	G_TYPE_CHECK_INSTANCE_CAST((obj), bima_relation_get_type(), BimaRelation)
#define BIMA_RELATION_CONST(obj)	G_TYPE_CHECK_INSTANCE_CAST((obj), bima_relation_get_type(), BimaRelation const)
#define BIMA_RELATION_CLASS(klass)	G_TYPE_CHECK_CLASS_CAST((klass), bima_relation_get_type(), BimaRelationClass)
#define BIMA_IS_RELATION(obj)	G_TYPE_CHECK_INSTANCE_TYPE((obj), bima_relation_get_type ())

#define BIMA_RELATION_GET_CLASS(obj)	G_TYPE_INSTANCE_GET_CLASS((obj), bima_relation_get_type(), BimaRelationClass)

/*
 * Main object structure
 */
#ifndef __TYPEDEF_BIMA_RELATION__
#define __TYPEDEF_BIMA_RELATION__
typedef struct _BimaRelation BimaRelation;
#endif
struct _BimaRelation {
	GObject __parent__;
	/*< public >*/
	gchar * id;
	gchar * name;
	gchar * abbreviation;
	gchar * description;
	gchar * module_id;
	GList * attributes;
	gint num_of_attribute;
	GList * foreign_key;
	gint num_of_foreign_key;
	gchar * left_card;
	gchar * right_card;
	gboolean is_rotated;
	gint num_of_connection;
	gint rel_type;
	GList * connections;
};

/*
 * Class definition
 */
typedef struct _BimaRelationClass BimaRelationClass;
struct _BimaRelationClass {
	GObjectClass __parent__;
};


/*
 * Public methods
 */
GType	bima_relation_get_type	(void);
gchar * 	bima_relation_get_id	(BimaRelation * self);
void 	bima_relation_set_id	(BimaRelation * self,
					gchar * val);
gchar * 	bima_relation_get_name	(BimaRelation * self);
void 	bima_relation_set_name	(BimaRelation * self,
					gchar * val);
gchar * 	bima_relation_get_module_id	(BimaRelation * self);
void 	bima_relation_set_module_id	(BimaRelation * self,
					gchar * val);
void 	bima_relation_add_attribute	(BimaRelation * self,
					BimaAttribute * attribute);
int 	bima_relation_get_num_of_attribute	(BimaRelation * self);
GList * 	bima_relation_get_attributes	(BimaRelation * self);
void 	bima_relation_add_foreign_key	(BimaRelation * self,
					BimaForeignKey * fk);
GObject * 	bima_relation_get_nth_attribute	(BimaRelation * self,
					gint n);
void 	bima_relation_add_connection	(BimaRelation * self,
					BimaConnection * conn);
void 	bima_relation_write_to_xml	(BimaRelation * self,
					FILE * ofile);
BimaRelation * 	bima_relation_new	(void);

/*
 * Argument wrapping macros
 */
#if defined(__GNUC__) && !defined(__STRICT_ANSI__)
#define BIMA_RELATION_PROP_ID(arg)    	"id", __extension__ ({gchar *z = (arg); z;})
#define BIMA_RELATION_GET_PROP_ID(arg)	"id", __extension__ ({gchar **z = (arg); z;})
#define BIMA_RELATION_PROP_NAME(arg)    	"name", __extension__ ({gchar *z = (arg); z;})
#define BIMA_RELATION_GET_PROP_NAME(arg)	"name", __extension__ ({gchar **z = (arg); z;})
#define BIMA_RELATION_PROP_MODULE_ID(arg)    	"module_id", __extension__ ({gchar *z = (arg); z;})
#define BIMA_RELATION_GET_PROP_MODULE_ID(arg)	"module_id", __extension__ ({gchar **z = (arg); z;})
#else /* __GNUC__ && !__STRICT_ANSI__ */
#define BIMA_RELATION_PROP_ID(arg)    	"id",(gchar *)(arg)
#define BIMA_RELATION_GET_PROP_ID(arg)	"id",(gchar **)(arg)
#define BIMA_RELATION_PROP_NAME(arg)    	"name",(gchar *)(arg)
#define BIMA_RELATION_GET_PROP_NAME(arg)	"name",(gchar **)(arg)
#define BIMA_RELATION_PROP_MODULE_ID(arg)    	"module_id",(gchar *)(arg)
#define BIMA_RELATION_GET_PROP_MODULE_ID(arg)	"module_id",(gchar **)(arg)
#endif /* __GNUC__ && !__STRICT_ANSI__ */


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
