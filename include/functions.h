#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

#include <webkit2/webkit2.h>
#include <JavaScriptCore/JavaScript.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>

#include <libxml/tree.h>
#include "resources.h"


typedef struct{
	char		name[128];
	int			width;
	int			height;
	gboolean	fix_size;
	char		uriPath[128];
	int			developerEnabled;
} CONFIG;

extern WebKitWebView	* webview;
extern GtkWidget		* window;

// basic C utils 
char 					* ReadFile(const char *);
char 					* ReplaceSpecialCharacters(const char *);	// replace/convert \n,\t,\r characters to

const gchar				* get_file_extension(const gchar *);
void					  list_resources( GResource *, const gchar*); 
const gchar				* Check_resources( GResource *, const gchar *, const gchar *);

void					  inject_Hook_functions(WebKitWebView *);
int						  ReadXMLConfig(const char *, CONFIG *);
const char				* insert_Functions_JS();
void					  insert_JSscript(const char * script, const gsize length, WebKitURISchemeRequest* request);

// events
void					  on_load_changed( WebKitWebView *, WebKitLoadEvent, gpointer);
gboolean				  on_destroy_window( GtkWidget *, GdkEvent *, gpointer);
void					  initialize_C_Function(WebKitWebView *, const gchar *, GCallback, gpointer);
void					  SendEventMessage( const gchar *, const gchar *);
						  
#endif