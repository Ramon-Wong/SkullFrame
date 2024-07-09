#include "functions.h"





WebKitJavascriptResult * g_result;

static void web_view_javascript_finished(GObject * object, GAsyncResult * result, gpointer user_data){

	JSCValue               *value;
	GError                 *error = NULL;

	value = webkit_web_view_evaluate_javascript_finish( webview, result, &error);
	if (!value) {
		g_warning ("Error running javascript: %s", error->message);
		g_error_free (error);
		return;
	}

	if(jsc_value_is_string(value)){
		gchar        *str_value = jsc_value_to_string (value);
		JSCException *exception = jsc_context_get_exception (jsc_value_get_context (value));
		if (exception)
			g_warning ("Error running javascript(Exception): %s", jsc_exception_get_message (exception));
		else
			g_print ("Script result: %s\n", str_value);
		g_free (str_value);
	} else {
		// g_warning ("Error running javascript(jsc_value_is_string): unexpected return value %s", jsc_value_to_string (value));
	}
	webkit_javascript_result_unref (g_result);
}


void C_DestroyWindow(WebKitUserContentManager* manager, WebKitJavascriptResult* result, gpointer user_data){
	g_print("C on Destroy Window\n");
	// gtk_main_quit();

	g_result = result;

	gchar *script = g_strdup_printf("window.onCFunctionReturn('C on Destroy Window');");
	webkit_web_view_evaluate_javascript( webview, script, -1, NULL, NULL, NULL, web_view_javascript_finished, NULL);        
	g_free(script);    
}


// window.webkit.messageHandlers.js_Call.postMessage("test");
void C_HelloWorld1(WebKitUserContentManager* manager, WebKitJavascriptResult* result, gpointer user_data){
	g_print("Hello world, got your call from JavaScript\n");

	g_result = result;

	gchar *script = g_strdup_printf("window.onCFunctionReturn('Happy Motherfucking Every Day');");
	webkit_web_view_evaluate_javascript( webview, script, -1, NULL, NULL, NULL, web_view_javascript_finished, NULL);        
	g_free(script);    
}


// window.webkit.messageHandlers.js_Call.postMessage("test");
void  C_HelloWorld2(WebKitUserContentManager* manager, WebKitJavascriptResult* result, gpointer user_data){
	JSCValue * value = webkit_javascript_result_get_js_value(result);

	// Check if the value is a string
	if (jsc_value_is_string(value)) {
		gchar *message = jsc_value_to_string(value);
		g_print("Received message: %s\n", message);
		SendEventMessage("CFunctionReturn_js_Call", "I got your message!!");
		g_free(message);
	} else {
		g_print("Message is not a string.\n");
	}
}


// window.webkit.messageHandlers.js_Call.postMessage(["Hello from JavaScript", 42, true]);
void C_HelloWorld3(WebKitUserContentManager* manager, WebKitJavascriptResult* result, gpointer user_data){
	JSCValue * value = webkit_javascript_result_get_js_value(result);

	// Check if the value is an array
	if (jsc_value_is_array(value)) {
		JSCValue *item1 = jsc_value_object_get_property_at_index(value, 0);
		JSCValue *item2 = jsc_value_object_get_property_at_index(value, 1);
		JSCValue *item3 = jsc_value_object_get_property_at_index(value, 2);

		if (jsc_value_is_string(item1)) {
			gchar *message = jsc_value_to_string(item1);
			g_print("Received message: %s\n", message);
			g_free(message);
		} else { g_print("First item is not a string.\n"); }

		if (jsc_value_is_number(item2)) {
			int number = jsc_value_to_int32(item2);
			g_print("Received number: %d\n", number);
		} else { g_print("Second item is not a number.\n");}

		if (jsc_value_is_boolean(item3)) {
			gboolean flag = jsc_value_to_boolean(item3);
			g_print("Received boolean: %s\n", flag ? "true" : "false");
		} else { g_print("Third item is not a boolean.\n"); }
	} else {
		g_print("Message is not an array.\n");
	}

	webkit_javascript_result_unref(result);
}


// gboolean dispatch_custom_event(gpointer user_data) {
// 	// WebKitWebView* webview = WEBKIT_WEB_VIEW(user_data);
// 	const gchar* message = "Hello from C!";
// 	gchar* js_code = g_strdup_printf("var event = new CustomEvent('hello_world', { detail: '%s' }); window.dispatchEvent(event);", message);
// 	webkit_web_view_evaluate_javascript( webview, js_code, -1, NULL, NULL, NULL, NULL, NULL);

// 	g_free(js_code);
// 	return TRUE;
// }


void JSCore_Destroy(WebKitUserContentManager* manager, WebKitJavascriptResult* result, gpointer user_data){
	g_print("JSCore_Destroy, got your signal from JavaScript\n");

	g_result = result;

    gtk_widget_destroy(window); 
	gtk_main_quit();
}


void JSCORE_MessageLog(WebKitUserContentManager* manager, WebKitJavascriptResult* result, gpointer user_data){
	JSCValue * value = webkit_javascript_result_get_js_value(result);

	if(jsc_value_is_string(value)){						// Check if the value is a string
		gchar *message = jsc_value_to_string(value);
		g_print("JSCore Message: %s\n", message);

		g_free(message);
	} else {
		g_print("JSCore Message Error: Message is not a string.\n");
	}
}


void inject_Hook_functions(WebKitWebView * _webview){

	g_print("injecting Hook Functions");
	initialize_C_Function( _webview, "js_Call",				G_CALLBACK(C_HelloWorld1),		NULL);
	initialize_C_Function( _webview, "js_FuncCall",			G_CALLBACK(C_HelloWorld2),		NULL);
	initialize_C_Function( _webview, "JSCore_Destroy",		G_CALLBACK(JSCore_Destroy),		NULL);
	initialize_C_Function( _webview, "JSCORE_MessageLog",	G_CALLBACK(JSCORE_MessageLog),	NULL);
}


const char * insert_JSScript(){
	// use for functions.js
	const char * string =
	"//For updates, check on the const char * insert_JSScript() in utils.c \n\n"
	"function onDeviceReady(){ console.log('Device is ready'); }"
	"\n\n"
	"function onCFunctionReturn(result){"
	"\n	console.log('Received from C: ' + result);"
	"\n}"
	"\n\n"
	"function js_Call(){"
	"\n	window.webkit.messageHandlers.js_Call.postMessage({});"
	"\n}"
	"\n\n"
	"//function js_DestroyWindow(){"
	"\n//	window.webkit.messageHandlers.js_DestroyWindow.postMessage({});"
	"\n//}"
	"\n\n"
	"function JSCore_Destroy(){"
	"\n	window.webkit.messageHandlers.JSCore_Destroy.postMessage({});"
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