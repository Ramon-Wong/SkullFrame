#include "functions.h"


GResource 			* gresources;
WebKitWebView		* webview;
GtkWidget			* window;
CONFIG 				  Global_Config;


void my_uri_scheme_request_callback(WebKitURISchemeRequest* request, gpointer user_data) {
	// const gchar* uri = webkit_uri_scheme_request_get_uri(request);
	const gchar* path = webkit_uri_scheme_request_get_path(request);
	
	const gchar* data = NULL;
	gsize data_length = 0;
	const gchar* mime_type = "text/html";

	// insert functions.js script into our project..
	if( g_strcmp0( "/myapp/web/script/functions.js", path) == 0){
		g_print("\tInserting Functions.js script to main.html \n"); 

		insert_JSscript( insert_Functions_JS(), strlen(insert_Functions_JS()), request);
	}

	if( g_strcmp0( Check_resources( gresources, "/", path), path) == 0){
		g_print("found: %s in resources", path); 

		GBytes *bytes = g_resource_lookup_data( gresources,  path, G_RESOURCE_LOOKUP_FLAGS_NONE, NULL);       

		if(bytes){
			data = (const gchar*) g_bytes_get_data( bytes, &data_length);
			// g_print("%s", data);
			g_bytes_unref(bytes);

			const gchar* file_extension = get_file_extension(path);
			if (g_strcmp0(file_extension, "html") == 0) {               mime_type = "text/html";				g_print(".HTML");	data_length = strlen(data);
				} else if (g_strcmp0(file_extension, "js") == 0) {      mime_type = "application/javascript";	g_print(".JS");		data_length = strlen(data);
				} else if (g_strcmp0(file_extension, "css") == 0) {     mime_type = "text/css";					g_print(".CSS");		data_length = strlen(data);
				} else if (g_strcmp0(file_extension, "jpg") == 0 || g_strcmp0(file_extension, "jpeg") == 0) {	g_print(".JPEG");
				} else if (g_strcmp0(file_extension, "png") == 0) {		g_print(".PNG");
				} else if (g_strcmp0(file_extension, "gif") == 0) {		g_print(".GIF");
			}
			g_print("\n");
		}else{
			g_print("Failed to load resource.\n");
		}
	}

	if (data) {
		GInputStream* stream = g_memory_input_stream_new_from_data(data, data_length, NULL);
		webkit_uri_scheme_request_finish(request, stream, data_length, mime_type);
		g_object_unref(stream);
	}
}


int main(int argc, char** argv) {
	gtk_init(&argc, &argv);
	
	if (argc >= 2) {
		printf("\n\nArgument: %s\n", argv[1]);
		ReadXMLConfig(argv[1], &Global_Config);
	} else {
		printf("\n\nNo arguments provided.\n");
	}

	WebKitWebContext* context = webkit_web_context_new();
	const gchar* scheme = "resources";
	webkit_web_context_register_uri_scheme(context, scheme, my_uri_scheme_request_callback, NULL, NULL);

	webview						= WEBKIT_WEB_VIEW(webkit_web_view_new_with_context(context));
	window						= gtk_window_new(GTK_WINDOW_TOPLEVEL);
	
	gtk_window_set_title(GTK_WINDOW(window), Global_Config.name);
	gtk_window_set_default_size(GTK_WINDOW(window), Global_Config.width, Global_Config.height);
	gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(webview));
	gtk_window_set_resizable(GTK_WINDOW(window), Global_Config.fix_size);
	
	// Check if Developer mode is enable
	if(Global_Config.developerEnabled == 1){
		WebKitSettings *settings					= webkit_web_view_get_settings(WEBKIT_WEB_VIEW(webview));
		webkit_settings_set_enable_developer_extras(settings, TRUE);

    	WebKitHardwareAccelerationPolicy policy		= webkit_settings_get_hardware_acceleration_policy(settings);
		g_print("Checking Hardware Acceleration Policies \n");

    	switch (policy) {
        case WEBKIT_HARDWARE_ACCELERATION_POLICY_ALWAYS:
			g_print("Hardware acceleration is always enabled.\n");
			break;
		case WEBKIT_HARDWARE_ACCELERATION_POLICY_ON_DEMAND:
			g_print("Hardware acceleration is enabled on demand.\n");
			break;
		case WEBKIT_HARDWARE_ACCELERATION_POLICY_NEVER:
			g_print("Hardware acceleration is disabled.\n");
			break;
		default:
			g_print("Unknown hardware acceleration policy.\n");
		}
	}	
 
	inject_Hook_functions(webview);
	webkit_web_view_load_uri(webview, Global_Config.uriPath);

	// Connect the document-loaded signal to the callback function
	gresources = resources_get_resource();
	g_resources_register(gresources);

	list_resources( gresources, "/");

	gtk_widget_show_all(window);
	gtk_main();

	return 0;
}