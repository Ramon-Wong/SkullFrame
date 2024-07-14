#include "functions.h"



void on_load_changed( WebKitWebView *web_view, WebKitLoadEvent load_event, gpointer user_data) {
	g_print("on load changed");

	if(load_event == WEBKIT_LOAD_STARTED){
		// seems like we only get this event
		g_print("on_load_changed >>> New Data Source Request has been made.\n");
		SendEventMessage( "WEBKIT_LOAD_STARTED", "WEBKIT_LOAD_STARTED");
	}

	if(load_event == WEBKIT_LOAD_REDIRECTED){
		// Javascript seems to be redirected, so it was never processed by our script
		g_print("on_load_changed >>> Data Source received a server redirect.\n");
		SendEventMessage( "WEBKIT_LOAD_REDIRECTED", "WEBKIT_LOAD_REDIRECTED");
	}

	if(load_event == WEBKIT_LOAD_COMMITTED){
		// Javascript seems to be committed, before execution
		g_print("on_load_changed >>> Data Source requirements are stabilished and the load is being performed.\n");
		SendEventMessage( "WEBKIT_LOAD_COMMITED", "WEBKIT_LOAD_COMMITED");
	}

	if(load_event == WEBKIT_LOAD_FINISHED){
		// Javascript seems to be finished, after it's finished
		g_print("on_load_changed >>> Data Source requirements are fully loaded and executed.  \n");
		SendEventMessage( "WEBKIT_LOAD_FINISHES", "WEBKIT_LOAD_FINISHES");
	}	
}
