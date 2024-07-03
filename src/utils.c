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

    const char * string = "function onDeviceReady() { console.log('Device is ready'); }";
    return string;
}


