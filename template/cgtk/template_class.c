#include "@VarEntityFunction@.h"
 
static void @VarModuleFunction@_@VarEntityFunction@_class_init(@VarModuleClass@@VarEntityClass@Class *klass);
static void @VarModuleFunction@_@VarEntityFunction@_init(@VarModuleClass@@VarEntityClass@ *sp);
static void @VarModuleFunction@_@VarEntityFunction@_finalize(GObject *object);

struct _@VarModuleClass@@VarEntityClass@Private {
	/* Place Private Members Here */
};

typedef struct _@VarModuleClass@@VarEntityClass@Signal @VarModuleClass@@VarEntityClass@Signal;
typedef enum _@VarModuleClass@@VarEntityClass@SignalType @VarModuleClass@@VarEntityClass@SignalType;

enum _@VarModuleClass@@VarEntityClass@SignalType {
	/* Place Signal Types Here */
	SIGNAL_TYPE_EXAMPLE,
	LAST_SIGNAL
};

struct _@VarModuleClass@@VarEntityClass@Signal {
	@VarModuleClass@@VarEntityClass@ *object;
};

static guint @VarModuleFunction@_@VarEntityFunction@_signals[LAST_SIGNAL] = { 0 };
static GObjectClass *parent_class = NULL;

GType
@VarModuleFunction@_@VarEntityFunction@_get_type()
{
	static GType type = 0;

	if(type == 0) {
		static const GTypeInfo our_info = {
			sizeof (@VarModuleClass@@VarEntityClass@Class),
			NULL,
			NULL,
			(GClassInitFunc)@VarModuleFunction@_@VarEntityFunction@_class_init,
			NULL,
			NULL,
			sizeof (@VarModuleClass@@VarEntityClass@),
			0,
			(GInstanceInitFunc)@VarModuleFunction@_@VarEntityFunction@_init,
		};

		type = g_type_register_static(G_TYPE_OBJECT, 
			"@VarModuleClass@@VarEntityClass@", &our_info, 0);
	}

	return type;
}

static void
@VarModuleFunction@_@VarEntityFunction@_class_init(@VarModuleClass@@VarEntityClass@Class *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);

	parent_class = g_type_class_peek_parent(klass);
	object_class->finalize = @VarModuleFunction@_@VarEntityFunction@_finalize;
	
	/* Create signals here:
	   @VarModuleFunction@_@VarEntityFunction@_signals[SIGNAL_TYPE_EXAMPLE] = g_signal_new(...)
 	*/
}

static void
@VarModuleFunction@_@VarEntityFunction@_init(@VarModuleClass@@VarEntityClass@ *obj)
{
	//obj->priv = g_new0(@VarModuleClass@@VarEntityClass@Private, 1);
	@VarEntityInit@
	/* Initialize private members, etc. */
}

static void
@VarModuleFunction@_@VarEntityFunction@_finalize(GObject *object)
{
	@VarModuleClass@@VarEntityClass@ *cobj;
	cobj = @VarModuleGType@_@VarEntityGType@(object);
	
	/* Free private members, etc. */
		
	//g_free(cobj->priv);
	G_OBJECT_CLASS(parent_class)->finalize(object);
}

@VarModuleClass@@VarEntityClass@ *
@VarModuleFunction@_@VarEntityFunction@_new()
{
	@VarModuleClass@@VarEntityClass@ *obj;
	
	obj = @VarModuleGType@_@VarEntityGType@(g_object_new(@VarModuleGType@_TYPE_@VarEntityGType@, NULL));
	
	return obj;
}

@VarModuleClass@@VarEntityClass@ *@VarModuleFunction@_@VarEntityFunction@_copy(@VarModuleClass@@VarEntityClass@ *self)
{
	@VarModuleClass@@VarEntityClass@ *obj;
	
	obj = @VarModuleGType@_@VarEntityGType@(g_object_new(@VarModuleGType@_TYPE_@VarEntityGType@, NULL));
	
	return obj;
}


GList *
@VarModuleFunction@_@VarEntityFunction@_get_data_all(GdaConnection *connection, GError **error)
{
	GdaCommand *command;
	GdaDataModel *gdm;
	GValue *gval;
	gchar *sql;
	GList *list=NULL;
	gint row, i;
		
	@VarModuleClass@@VarEntityClass@ *entity;
	
	sql = g_strdup("select * from @VarEntityFunction@");

	command = gda_command_new(sql,GDA_COMMAND_TYPE_SQL, GDA_COMMAND_OPTION_STOP_ON_ERRORS);
	gdm = gda_connection_execute_select_command(connection, command, NULL, error);

	row = gda_data_model_get_n_rows(gdm);

	for ( i = 0 ; i < row ; i++) {
		
		entity = @VarModuleFunction@_@VarEntityFunction@_new() ;
		
		@VarEntityDataAllAssignment@
		
		/*	
		gval = (GValue *)gda_data_model_get_value_at(gdm,0,i);
		entity->number = g_value_get_int(gval);

		gval = (GValue *)gda_data_model_get_value_at(gdm,1,i);
		entity->name = gda_value_stringify(gval);
		*/
		
		list = g_list_append(list, (gpointer) entity);	
	}	

	return list;
}

@VarModuleClass@@VarEntityClass@ *
@VarModuleFunction@_@VarEntityFunction@_get_data_by_key(GdaConnection *connection, @VarKeyParam@, GError **error)
{
	GdaCommand *command;
	GdaDataModel *gdm;

	@VarModuleClass@@VarEntityClass@ *entity = @VarModuleFunction@_@VarEntityFunction@_new() ;
	gchar *sql;
	sql = g_strdup_printf("select * from @VarEntityFunction@ where @VarKeyParamSql@ ",@VarKeyParamStr@);

	command = gda_command_new(sql,GDA_COMMAND_TYPE_SQL, GDA_COMMAND_OPTION_STOP_ON_ERRORS);
	gdm = gda_connection_execute_select_command(connection, command, NULL, error);
	
	@VarEntityDataAssignment@
		
	g_object_unref(gdm);	
	gda_command_free(command);
	
	return entity;
}

gint 
@VarModuleFunction@_@VarEntityFunction@_insert_data(@VarModuleClass@@VarEntityClass@ *entity, GdaConnection *connection,GError **error)
{
	GdaCommand *command;
	GdaDataModel *gdm;
	gint row;
	gchar *sql;

	sql = g_strdup("insert into @VarEntityFunction@ ( @VarEntityAttributeInsertList@ ) ");
	sql = g_strconcat(sql , " values( ", NULL);
	
	@VarEntityAttributeInsertValues@
	
	sql = g_strconcat(sql , " ) ", NULL);

	command = gda_command_new(sql,GDA_COMMAND_TYPE_SQL, GDA_COMMAND_OPTION_STOP_ON_ERRORS);
	row = gda_connection_execute_non_select_command(connection, command, NULL, error);

	gda_command_free(command);

	return row;
}

gint 
@VarModuleFunction@_@VarEntityFunction@_update_data(@VarModuleClass@@VarEntityClass@ *entity, GdaConnection *connection, GError **error)
{
	GdaCommand *command;
	gint *row;
	gchar *sql;

	sql = g_strdup("update @VarEntityFunction@ set ");

	@VarEntityAttributeSetUpadte@

	sql = g_strconcat(sql , g_strdup_printf(" where @VarKeyParamSql@ ", @VarEntityKeyParamStr@), NULL);

	command = gda_command_new(sql,GDA_COMMAND_TYPE_SQL, GDA_COMMAND_OPTION_STOP_ON_ERRORS);
	row = gda_connection_execute_non_select_command(connection, command, NULL, error);

	gda_command_free(command);
	return row;
}

gint 
@VarModuleFunction@_@VarEntityFunction@_delete_data(@VarModuleClass@@VarEntityClass@ *entity, GdaConnection *connection, GError **error)
{
	GdaCommand *command;
	gchar *sql;
	gint row;
	
	sql = g_strdup_printf("delete from @VarEntityFunction@ where @VarKeyParamSql@ ",@VarEntityKeyParamStr@);

	command = gda_command_new(sql,GDA_COMMAND_TYPE_SQL, GDA_COMMAND_OPTION_STOP_ON_ERRORS);
	row = gda_connection_execute_non_select_command(connection, command, NULL, error);

	gda_command_free(command);
	return row;
}

