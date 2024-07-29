#include "functions.h"


WebKitJavascriptResult * g_result;





char * ReplaceSpecialCharacters(const char* str) {
	if(str == NULL){	printf("The string is NULL.\n"); return NULL; }

	size_t originalLength		= strlen(str);			// First, count the number of special characters
	size_t newLength			= originalLength;

	for(size_t i = 0; i < originalLength; i++){
		if(str[i] == '\t' || str[i] == '\n' || str[i] == '\'' || str[i] == '\"') {
			newLength += 1; 							// Each special character will be replaced by 2 characters
		}
    }

    // Allocate memory for the new string
	char* newStr = (char*)malloc(newLength + 1);		// +1 for the null terminator
	if(newStr == NULL){	printf("Memory allocation failed\n");return NULL;}

	// Replace special characters
	size_t j = 0;
	for(size_t i = 0; i < originalLength; i++) {
		switch (str[i]) {
			case '\t':	newStr[j++] = '\\';	newStr[j++] = 't';	break;
			case '\n':	newStr[j++] = '\\';	newStr[j++] = 'n';	break;
			case '\'':	newStr[j++] = '\\';	newStr[j++] = '\'';	break;
			case '\"':	newStr[j++] = '\\';	newStr[j++] = '\"';	break;
			default:	newStr[j++] = str[i];					break;
		}
	}

	newStr[j] = '\0';									// Null-terminate the new string

	return newStr;
}


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

			// FILE *file = fopen( path, "rb");
			// if(file == NULL){ 
			// 	perror("Error opening file");	
			// 	SendEventMessage( event, "Cannot find or open the file");
			// 	return;
			// }

			// fseek(file, 0, SEEK_END);	// Determine the file size
			// long fileSize = ftell(file);
			// rewind(file);
			
			// char *buffer = (char *)malloc(fileSize + 1);			// Allocate memory to contain the whole file
			// if(buffer == NULL){	perror("Memory allocation failed");	fclose(file);	return;	}

			// size_t bytesRead = fread(buffer, 1, fileSize, file);	// Read the file into the buffer
			// if(bytesRead != fileSize){ perror("Error reading file"); free(buffer); fclose(file); return;}
			// g_print("%s\n\n", buffer);
			// buffer[fileSize] = '\0';								// Null-terminate the buffer    

			const char * xml0	= "<note>this is a \n \t \r \\ \\ \\ simple string.this is a simple string.this is a simple string.this is a simple string.this is a simple string.</note>";
			// const char * xml1	= "<note><to>Tove</to><from>Jani</from><heading>Reminder</heading><body>Don't forget me this weekend!</body></note>";
			// const char * xml2	= "<note>/n/t<to>Tove</to>/n/t<from>Jani</from>/n/t<heading>Reminder</heading>/n/t<body>Don't forget me this weekend!</body>/n</note>/0";

			// replaceBackslashes(&xml0);
			SendEventMessage( event, xml0);
			

			// free(buffer);

			// fclose(file);			
			g_free(event);
			g_free(path);
		}

	}else{
		g_print("JSCore ReadFile Error: parameters are not valid.\n");
	}
}



// void JSCORE_ReadFile(WebKitUserContentManager* manager, WebKitJavascriptResult* result, gpointer user_data){
// 	JSCValue * value = webkit_javascript_result_get_js_value(result);

// 	if(jsc_value_is_string(value)){						// Check if the value is a string
// 		gchar *message = jsc_value_to_string(value);
// 		g_print("JSCORE Message: %s\n", message);

		// FILE *file = fopen(filename, "rb");

		// if(file == NULL){ perror("Error opening file");	return;}

		// fseek(file, 0, SEEK_END);	// Determine the file size
		// long fileSize = ftell(file);
		// rewind(file);

		// char *buffer = (char *)malloc(fileSize + 1);			// Allocate memory to contain the whole file
		// if(buffer == NULL){	perror("Memory allocation failed");	fclose(file);	return;	}

		// size_t bytesRead = fread(buffer, 1, fileSize, file);	// Read the file into the buffer
		// if(bytesRead != fileSize){ perror("Error reading file"); free(buffer); fclose(file); return;}

		// buffer[fileSize] = '\0';								// Null-terminate the buffer    
		// SendEventMessage("ReadFile", buffer);
		// free(buffer);											// Clean up
		// fclose(file);

// 		g_free(message);
// 	} else {
// 		g_print("JSCore Message Error: Message is not a string.\n");
// 	}	
// }


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
	"function JSCORE_MessageLog(msg){				// MessageLog"
	"\n	window.webkit.messageHandlers.JSCORE_MessageLog.postMessage(msg);"
	"\n}"
	"\n\n"
	"function JSCORE_ReadFile(event, path){			// readfile"
	"\n	window.webkit.messageHandlers.JSCORE_ReadFile.postMessage([event, path]);"
	"\n}"
	"\n\n"
	"function JSCORE_HelloWorld(event, msg){		// don't forget the parameters for the JS functions"
	"\n	window.webkit.messageHandlers.JSCORE_HelloWorld.postMessage([event, msg]);"
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