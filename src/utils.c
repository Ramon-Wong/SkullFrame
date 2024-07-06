#include "functions.h"




// Function to extract the file extension from a path
const gchar* get_file_extension(const gchar* path){
	const gchar* dot = strrchr(path, '.');
	if (!dot || dot == path) return "";
	return dot + 1;
}


void list_resources( GResource * resources, const gchar *path) {
	
	GError *error = NULL;

	// Enumerate children of the specified path
	gchar **children = g_resource_enumerate_children(resources, path, G_RESOURCE_LOOKUP_FLAGS_NONE, &error);
	if (error) {
		g_printerr("Error enumerating resources: %s\n", error->message);
		g_error_free(error);
		return;
	}

	// Print each child
	for (gchar **child = children; *child != NULL; child++) {
		gchar *child_path = g_build_filename(path, *child, NULL);
		g_print("Resource: %s\n", child_path);

		// Recursively list resources if it's a directory
		if (g_str_has_suffix(child_path, "/")) {
			list_resources( resources, child_path);
		}
		// else{ 
		//     g_print(">>>this  is a file: %s \n", child_path);
		// }
		g_free(child_path);
	}

	g_strfreev(children);
}


const gchar* Check_resources(  GResource * resources, const gchar *path, const gchar *keyword) {

	GError *error = NULL;

	// Enumerate children of the specified path
	gchar **children = g_resource_enumerate_children(resources, path, G_RESOURCE_LOOKUP_FLAGS_NONE, &error);
	if (error) {
		g_printerr("Error enumerating resources: %s\n", error->message);
		g_error_free(error);
		return g_strdup("Error enumerating resources");
	}

	for (gchar **child = children; *child != NULL; child++) {
		gchar *child_path = g_build_filename(path, *child, NULL);
		// g_print("Resource: %s\n", child_path);

		if (g_strcmp0(child_path, keyword) == 0) {
			// g_print(" \n %s >> found \n", child_path);
			g_strfreev(children);
			return child_path;
		}

		// Recursively list resources if it's a directory
		if (g_str_has_suffix(child_path, "/")) {
			const gchar *found_path = Check_resources( resources, child_path, keyword);
			if (found_path && g_strcmp0(found_path, "Not found") != 0) {
				g_strfreev(children);
				return found_path;
			}
		}
		g_free(child_path);
	}

	g_strfreev(children);
	return g_strdup("Not found");
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
	"function js_DestroyWindow(){"
	"\n	window.webkit.messageHandlers.js_DestroyWindow.postMessage({});"
	"\n}"
	"\n\n"
	"window.onCFunctionReturn = onCFunctionReturn;";
	return string;
}

// setting up C functions to be call from Javascript, G_CALLBACK(YOUR_FUNCTION_HERE)
void initialize_C_Function(WebKitWebView* _webview, const gchar * js_function_name, GCallback cback, gpointer user_data){
	WebKitUserContentManager* contentManager = webkit_web_view_get_user_content_manager(_webview);
	// Add a script message handler
	gchar * detailed_signal = g_strdup_printf("script-message-received::%s", js_function_name);

	g_signal_connect(contentManager, detailed_signal, cback, user_data);
	webkit_user_content_manager_register_script_message_handler(contentManager, js_function_name);
	g_free(detailed_signal);
}
