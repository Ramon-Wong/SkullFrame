
// uri_path "/resources:///myapp/web/script/functions.js"

void unique_Function_Name(WebKitURISchemeRequest* request, gpointer user_data, const char * uri_path, const gchar * data, gsize data_length) {
	const gchar* path = webkit_uri_scheme_request_get_path(request);
	
	// Check if the request path matches the path for the static script
	if (g_strcmp0(path, uri_path) == 0 && data) {
		if (data) {
			GInputStream* stream = g_memory_input_stream_new_from_data(data, data_length, NULL);
			webkit_uri_scheme_request_finish(request, stream, data_length, "application/javascript");
			g_object_unref(stream);
		} else {
			// Handle not found or error response
			webkit_uri_scheme_request_finish_error(request, g_error_new_literal(G_IO_ERROR, G_IO_ERROR_NOT_FOUND, "Resource not found"));
		}
	} else {
		g_print("Failed to load resource.\n");		  
	}	
}



void unique_Function_Name(WebKitURISchemeRequest* request, gpointer user_data) {
    const gchar* path = webkit_uri_scheme_request_get_path(request);

    const gchar* data = NULL;
    gsize data_length = 0;
    const gchar* mime_type = "application/javascript";

    // Check if the request path matches the path for the static script
    if (g_strcmp0(path, "/resources:///myapp/web/script/functions.js") == 0) {
        data = functions_js_content;
        data_length = functions_js_length;
    } else {
        // Existing logic for serving resources from gresources, but only for JavaScript
        if (g_strcmp0(Check_resources(gresources, "/", path), path) == 0) {
            g_print("found: %s in resources", path); 

            GBytes *bytes = g_resource_lookup_data(gresources, path, G_RESOURCE_LOOKUP_FLAGS_NONE, NULL);       

            if (bytes) {
                data = (const gchar*) g_bytes_get_data(bytes, &data_length);
                g_bytes_unref(bytes);
            } else {
                g_print("Failed to load resource.\n");
            }
        }
    }

    if (data) {
        GInputStream* stream = g_memory_input_stream_new_from_data(data, data_length, NULL);
        webkit_uri_scheme_request_finish(request, stream, data_length, mime_type);
        g_object_unref(stream);
    } else {
        // Handle not found or error response
        webkit_uri_scheme_request_finish_error(request, g_error_new_literal(G_IO_ERROR, G_IO_ERROR_NOT_FOUND, "Resource not found"));
    }
}



void unique_Function_Name(WebKitURISchemeRequest* request, gpointer user_data) {
    const gchar* request_path = webkit_uri_scheme_request_get_path(request);
    const gchar* data = NULL;
    gsize data_length = 0;
    const gchar* mime_type = NULL;

    // Check if the request path matches the path for the static script
    if (g_strcmp0(request_path, "/path/to/static/script.js") == 0) {
        data = functions_js_content;
        data_length = functions_js_length;
        mime_type = "application/javascript";
    } else {
        g_print("Failed to load resource: %s\n", request_path);
    }

    if (data) {
        GInputStream* stream = g_memory_input_stream_new_from_data(data, data_length, NULL);
        webkit_uri_scheme_request_finish(request, stream, data_length, mime_type);
        g_object_unref(stream);
    } else {
        // Handle not found or error response
        GError* error = g_error_new_literal(G_IO_ERROR, G_IO_ERROR_NOT_FOUND, "Resource not found");
        webkit_uri_scheme_request_finish_error(request, error);
        g_error_free(error);
    }
}



// void insert_JSScript(WebKitURISchemeRequest* request, gpointer user_data, const char * uri_path, const gchar * data, gsize data_length) {
//     const gchar* path = webkit_uri_scheme_request_get_path(request);

//     // Check if the request path matches the path for the static script
//     if (g_strcmp0(path, uri_path) == 0 && data) {
//         GInputStream* stream = g_memory_input_stream_new_from_data(data, data_length, NULL);
//         webkit_uri_scheme_request_finish(request, stream, data_length, "application/javascript");
//         g_object_unref(stream);
//     } else {
//         // Handle not found or error response
//         GError* error = g_error_new_literal(G_IO_ERROR, G_IO_ERROR_NOT_FOUND, "Resource not found");
//         webkit_uri_scheme_request_finish_error(request, error);
//         g_error_free(error);
//         g_print("Failed to load resource: %s\n", path);
//     }
// }
