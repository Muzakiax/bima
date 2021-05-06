
#ifndef __BIMA_PHPWEB_PLUGIN_H__
#define __BIMA_PHPWEB_PLUGIN_H__

#include <glib.h>
#include <glib-object.h>


#include <stdio.h>
#include <stdlib.h>
#include <bima-plugin.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/*
 * Type checking and casting macros
 */
#define BIMA_PHPWEB_PLUGIN(obj)	G_TYPE_CHECK_INSTANCE_CAST((obj), get_plugin_type(), BimaPhpWebPlugin)

/*
 * Main object structure
 */
#ifndef __TYPEDEF_BIMA_PHPWEB_PLUGIN__
#define __TYPEDEF_BIMA_PHPWEB_PLUGIN__
typedef struct _BimaPhpWebPlugin BimaPhpWebPlugin;
#endif


struct _BimaPhpWebPlugin {
	BimaPlugin __parent__;
	/*< public >*/
	gchar * name;
	gchar * author;
};

/*
 * Class definition
 */
typedef struct _BimaPhpWebPluginClass BimaPhpWebPluginClass;
struct _BimaPhpWebPluginClass {
	BimaPluginClass __parent__;
};


/*
 * Public methods
 */

G_MODULE_EXPORT GType get_plugin_type (void);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
