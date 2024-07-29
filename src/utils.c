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


char * ReadFile(const char * path){											// this function needs to go to the default utils?
	FILE * tFile	= fopen( path, "rt");
	char * buffer	= NULL;

	if(tFile){		
		fseek(tFile , 0 , SEEK_END);
		int lSize = ftell (tFile);
		rewind (tFile);		
		
		buffer = (char*) malloc(sizeof(char) * (lSize + 1));
		
		if(buffer){ 														// Check if memory allocation was successful
			fread(buffer, 1, lSize, tFile);		buffer[lSize] = '\0';		// Null-terminate the string
        } else {
            printf("Memory allocation failed\n");
        }

		fclose(tFile);		
		
	}else{
		printf("\n\nError at opening file: %s\n", path);
	}

	return buffer;
}


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