#include "functions.h"


WebKitJavascriptResult * g_result;



// use this function to inject scripts into main.html, example in my_uri_scheme_request_callback/main.c
void insert_JSscript( const char * script, const gsize length, WebKitURISchemeRequest* request){
	GInputStream* stream = g_memory_input_stream_new_from_data( script, length, NULL);
	webkit_uri_scheme_request_finish( request, stream, length, "application/javascript");
	g_object_unref(stream);	
}


void JSCORE_Destroy(WebKitUserContentManager* manager, WebKitJavascriptResult* result, gpointer user_data){
	g_print("JSCORE_Destroy, got your signal from JavaScript\n");

	g_result = result;

    gtk_widget_destroy(window); 
	gtk_main_quit();
}


void JSCORE_MessageLog(WebKitUserContentManager* manager, WebKitJavascriptResult* result, gpointer user_data){
	JSCValue * value = webkit_javascript_result_get_js_value(result);

	if(jsc_value_is_string(value)){						// Check if the value is a string
		gchar *message = jsc_value_to_string(value);
		g_print("JSCORE Message: %s\n", message);

		g_free(message);
	} else {
		g_print("JSCore Message Error: Message is not a string.\n");
	}
}


void inject_Hook_functions(WebKitWebView * _webview){

	g_print("injecting Hook Functions \n");
	// connect C main events to functions 
	g_signal_connect( window, "delete-event", 				G_CALLBACK(on_destroy_window), NULL);

	// bind C functions to JS > window.webkit.messageHandlers.js_Functions.postMessage({}) 
	initialize_C_Function( _webview, "JSCORE_Destroy",		G_CALLBACK(JSCORE_Destroy),		NULL);
	initialize_C_Function( _webview, "JSCORE_MessageLog",	G_CALLBACK(JSCORE_MessageLog),	NULL);
}

const char * insert_Functions_JS(){
	// use for functions.js
	const char * string =
	"//For updates, check on the const char * insert_Functions_JS() in utils.c \n\n"
	"function onDeviceReady(){ console.log('Device is ready'); }"
	"\n\n"
	"function onCFunctionReturn(result){"
	"\n	console.log('Received from C: ' + result);"
	"\n}"
	"\n\n"
	"function JSCORE_Destroy(){"
	"\n	window.webkit.messageHandlers.JSCORE_Destroy.postMessage({});"
	"\n}"
	"\n\n"
	"function JSCORE_MessageLog(msg){"
	"\n	window.webkit.messageHandlers.JSCORE_MessageLog.postMessage(msg);"
	"\n}"
	"\n\n"
	"window.onCFunctionReturn = onCFunctionReturn;";
	return string;
}


// setting up C functions to be call from Javascript, example in inject_Hook_functions
void initialize_C_Function(WebKitWebView* _webview, const gchar * js_function_name, GCallback cback, gpointer user_data){
	WebKitUserContentManager* contentManager = webkit_web_view_get_user_content_manager(_webview);
	// Add a script message handler
	gchar * detailed_signal = g_strdup_printf("script-message-received::%s", js_function_name);

	g_signal_connect(contentManager, detailed_signal, cback, user_data);
	webkit_user_content_manager_register_script_message_handler(contentManager, js_function_name);
	g_free(detailed_signal);
}


// important function, this function send event message to JSCore
void SendEventMessage(  const gchar * event_name, const gchar * event_data){
	gchar* js_code = g_strdup_printf("var event = new CustomEvent('%s', { detail: '%s' }); window.dispatchEvent(event);", event_name, event_data);
	webkit_web_view_evaluate_javascript( webview, js_code, -1, NULL, NULL, NULL, NULL, NULL);
	g_free(js_code);
}


gboolean on_destroy_window(  GtkWidget *widget, GdkEvent *event, gpointer user_data) {
    g_print("Window is being request to destroyed, sending message to JSCore. \n");
	SendEventMessage( "MAIN_THREAD_DESTROY_REQUEST", "MAIN_THREAD_DESTROY_REQUEST");
	return TRUE;
} 