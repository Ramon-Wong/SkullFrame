#include "functions.h"





void on_load_changed(WebKitWebView *web_view, WebKitLoadEvent load_event, gpointer user_data) {

	if(load_event == WEBKIT_LOAD_FINISHED){
		g_print("on_load_changed >>> New Data Source Request has been made.\n");
	}

	if(load_event == WEBKIT_LOAD_REDIRECTED){
		g_print("on_load_changed >>> Data Source received a server redirect.\n");
	}

	if(load_event == WEBKIT_LOAD_COMMITTED){
		g_print("on_load_changed >>> Data Source requirements are stabilished and the load is being performed.\n");
	}

	if(load_event == WEBKIT_LOAD_FINISHED){
		g_print("on_load_changed >>> Data Source requirements are fully loaded and executed.  \n");
	}	
}