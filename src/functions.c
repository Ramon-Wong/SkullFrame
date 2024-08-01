#include "functions.h"


WebKitJavascriptResult * g_result;




// use this function to inject scripts into main.html, example in my_uri_scheme_request_callback/main.c
void insert_JSscript( const char * script, const gsize length, WebKitURISchemeRequest* request){
	GInputStream* stream = g_memory_input_stream_new_from_data( script, length, NULL);
	webkit_uri_scheme_request_finish( request, stream, length, "application/javascript");
	g_object_unref(stream);	
}


void JSCORE_HelloWorld(WebKitUserContentManager* manager, WebKitJavascriptResult* result, gpointer user_data){
	JSCValue * value = webkit_javascript_result_get_js_value(result);

	if(jsc_value_is_array(value)){
		JSCValue * msgValue1			= jsc_value_object_get_property(value, "0");
		JSCValue * msgValue2			= jsc_value_object_get_property(value, "1");

		if(jsc_value_is_string(msgValue1) && jsc_value_is_string(msgValue2)){
			gchar * event				= jsc_value_to_string(msgValue1);
			gchar * msg					= jsc_value_to_string(msgValue2);

			g_print("JSCORE Hello World: %s / %s \n", event, msg);
			SendEventMessage( event, "HELLO WORLD, ROFL, ROFL, ROFL!!");
			g_free(event);
			g_free(msg);
		}

	}else{
		g_print("JSCore Hello World Error: parameters are not valid.\n");
	}
}


void JSCORE_ReadFile(WebKitUserContentManager* manager, WebKitJavascriptResult* result, gpointer user_data){
	JSCValue * value = webkit_javascript_result_get_js_value(result);

	if(jsc_value_is_array(value)){
		JSCValue * msgValue1			= jsc_value_object_get_property(value, "0");
		JSCValue * msgValue2			= jsc_value_object_get_property(value, "1");

		if(jsc_value_is_string(msgValue1) && jsc_value_is_string(msgValue2)){
			gchar * event				= jsc_value_to_string(msgValue1);
			gchar * path				= jsc_value_to_string(msgValue2);

			g_print("JSCORE ReadFile: %s / %s \n", event, path);

			char * data 				= ReadFile(path);

			if(data){
				char * processedString	= ReplaceSpecialCharacters(data);
				SendEventMessage( event, processedString);					// send the processed string
				free(processedString);										// free the processed string				
			}else{
				char message[128];
									
				sprintf( message, "{\"event\": \"%s\", \"path\": \"%s\", \"reason\": \"Cannot open or read from the filepath\"}", event, path);
				SendEventMessage( event, "NULL");							// for now we just send 'NULL'	remember to use \' or \"
				SendEventMessage( "WEBKIT_ERROR_MSG", message);				// WEBKIT_ERROR_MSG
			}

			free(data);														// free the stuff we just read

			// fclose(file);			
			g_free(event);
			g_free(path);
		}

	}else{
		g_print("JSCore ReadFile Error: parameters are not valid.\n");
	}
}


void JSCORE_WriteFile(WebKitUserContentManager* manager, WebKitJavascriptResult* result, gpointer user_data){
	JSCValue * value = webkit_javascript_result_get_js_value(result);

	if(jsc_value_is_array(value)){
		// How to write onto a file
		// 1. unique event name
		// 2. filename.
		// 3. string/content.
		// 4. write/append?

		JSCValue * msg1			= jsc_value_object_get_property(value, "0");
		JSCValue * msg2			= jsc_value_object_get_property(value, "1");
		JSCValue * msg3			= jsc_value_object_get_property(value, "2");
		JSCValue * msg4			= jsc_value_object_get_property(value, "3");

		if(jsc_value_is_string(msg1) && jsc_value_is_string(msg2) && jsc_value_is_string(msg3) && jsc_value_is_string(msg4)){

			gchar * values[4]			= {	jsc_value_to_string(msg1),
											jsc_value_to_string(msg2),
											jsc_value_to_string(msg3),
											jsc_value_to_string(msg4)};

			g_print("WriteFile: %s // %s // %s // %s", values[0], values[1], values[2], values[3]);
		}
	}
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
    // g_signal_connect( webview, "load-changed", G_CALLBACK(on_load_changed), NULL);	

	// bind C functions to JS > window.webkit.messageHandlers.js_Functions.postMessage({}) 
	initialize_C_Function( _webview, "JSCORE_Destroy",		G_CALLBACK(JSCORE_Destroy),		NULL);
	initialize_C_Function( _webview, "JSCORE_MessageLog",	G_CALLBACK(JSCORE_MessageLog),	NULL);
	initialize_C_Function( _webview, "JSCORE_ReadFile",		G_CALLBACK(JSCORE_ReadFile),	NULL);
	initialize_C_Function( _webview, "JSCORE_WriteFile",	G_CALLBACK(JSCORE_WriteFile),	NULL);
	initialize_C_Function( _webview, "JSCORE_HelloWorld",	G_CALLBACK(JSCORE_HelloWorld),	NULL);
	// can we get a C read
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
	"function JSCORE_MessageLog(msg){							// MessageLog"
	"\n	window.webkit.messageHandlers.JSCORE_MessageLog.postMessage(msg);"
	"\n}"
	"\n\n"
	"function JSCORE_HelloWorld(event, msg){		// don't forget the parameters for the JS functions"
	"\n	window.webkit.messageHandlers.JSCORE_HelloWorld.postMessage([event, msg]);"
	"\n}"
	"\n\n"
	"function JSCORE_ReadFile(event, path){						// readfile"
	"\n	window.webkit.messageHandlers.JSCORE_ReadFile.postMessage([event, path]);"
	"\n}"
	"\n\n"
	"function JSCORE_WriteFile(value1, value2, value3, value4){	// Writefile, testing purposes"
	"\n	window.webkit.messageHandlers.JSCORE_WriteFile.postMessage([value1, value2, value3, value4]);"
	"\n}"
	"\n\n"
	"\n\n"
	"\n\n"
	"\n\n"
	"function readFileAsync(event_name, file_path) {			// Read file asynchronously"
	"\n	return new Promise((resolve, reject) => {	// Add event listeners for success and error and make promises"
	"\n		window.addEventListener( event_name, (event) => { if(event.detail !== 'NULL'){resolve(event.detail);}}, { once: true });"
	"\n		window.addEventListener(\"WEBKIT_ERROR_MSG\", (event) => {"
	"\n			const errObj = JSON.parse(event.detail);"
	"\n			if(errObj.event === event_name){ reject(new Error(errObj.reason));}"
	"\n		},{ once: true });"
	"\n		JSCORE_ReadFile(event_name, file_path);	// Call the C function"
    "\n	});"
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