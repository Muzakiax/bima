#ifndef __@VarModuleGType@_@VarEntityGType@_H__
#define __@VarModuleGType@_@VarEntityGType@_H__

#include <glib.h>
#include <glib-object.h>
#include <libgda/libgda.h>

#define @VarModuleGType@_TYPE_@VarEntityGType@         (@VarModuleFunction@_@VarEntityFunction@_get_type ())
#define @VarModuleGType@_@VarEntityGType@(o)           (G_TYPE_CHECK_INSTANCE_CAST ((o), @VarModuleGType@_TYPE_@VarEntityGType@, @VarModuleClass@@VarEntityClass@))
#define @VarModuleGType@_@VarEntityGType@_CLASS(k)     (G_TYPE_CHECK_CLASS_CAST((k), @VarModuleGType@_TYPE_@VarEntityGType@, @VarModuleClass@@VarEntityClass@Class))
#define @VarModuleGType@_IS_@VarEntityGType@(o)        (G_TYPE_CHECK_INSTANCE_TYPE ((o), @VarModuleGType@_TYPE_@VarEntityGType@))
#define @VarModuleGType@_IS_@VarEntityGType@_CLASS(k)  (G_TYPE_CHECK_CLASS_TYPE ((k), @VarModuleGType@_TYPE_@VarEntityGType@))
#define @VarModuleGType@_@VarEntityGType@_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS ((o), @VarModuleGType@_TYPE_@VarEntityGType@, @VarModuleClass@@VarEntityClass@Class))

typedef struct _@VarModuleClass@@VarEntityClass@ @VarModuleClass@@VarEntityClass@;
typedef struct _@VarModuleClass@@VarEntityClass@Private @VarModuleClass@@VarEntityClass@Private;
typedef struct _@VarModuleClass@@VarEntityClass@Class @VarModuleClass@@VarEntityClass@Class;

struct _@VarModuleClass@@VarEntityClass@ {
	GObject parent;
	@VarEntityAttribute@
	//@VarModuleClass@@VarEntityClass@Private *priv;
};

struct _@VarModuleClass@@VarEntityClass@Class {
	GObjectClass parent_class;
	/* Add Signal Functions Here */
};

GType @VarModuleFunction@_@VarEntityFunction@_get_type();
@VarModuleClass@@VarEntityClass@ *@VarModuleFunction@_@VarEntityFunction@_new();
@VarModuleClass@@VarEntityClass@ *@VarModuleFunction@_@VarEntityFunction@_copy(@VarModuleClass@@VarEntityClass@ *self);

GList *@VarModuleFunction@_@VarEntityFunction@_get_data_all(GdaConnection *connection, GError **error);
@VarModuleClass@@VarEntityClass@ *@VarModuleFunction@_@VarEntityFunction@_get_data_by_key(@VarKeyParam@);

@VarModuleClass@@VarEntityClass@ *@VarModuleFunction@_@VarEntityFunction@_get_data_by_key(GdaConnection *connection, @VarKeyParam@, GError **error);
GList *@VarModuleFunction@_@VarEntityFunction@_get_all_data(GdaConnection *connection, GError **error);
gint @VarModuleFunction@_@VarEntityFunction@_insert_data(@VarModuleClass@@VarEntityClass@ *entity, GdaConnection *connection,GError **error);
gint @VarModuleFunction@_@VarEntityFunction@_update_data(@VarModuleClass@@VarEntityClass@ *entity, GdaConnection *connection, GError **error);
gint @VarModuleFunction@_@VarEntityFunction@_delete_data(@VarModuleClass@@VarEntityClass@ *entity, GdaConnection *connection, GError **error);

#endif
