#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

#include <webkit2/webkit2.h>
#include <JavaScriptCore/JavaScript.h>
#include <gtk/gtk.h>
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
const gchar				* get_file_extension(const gchar *);
void					  list_resources( GResource *, const gchar*); 
const gchar				* Check_resources( GResource *, const gchar *, const gchar *);



void					  inject_Hook_functions(WebKitWebView *);

int						  ReadXMLConfig(const char *, CONFIG *);
const char				* insert_JSScript();

// events
void					  on_load_changed( WebKitWebView *, WebKitLoadEvent, gpointer);

#endif