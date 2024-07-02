#include "functions.h"



int ReadXMLConfig(const char * filename, CONFIG * Config){

	xmlDoc *document = xmlReadFile( filename, NULL, 0);
	if(document == NULL) {
		printf("Could not parse the XML file: %s\n", filename);
		printf("Will use the default config instead.\n");

		strcpy( Config->name, "GTK Default Window"); 
		Config->width				= 800;		
		Config->height				= 600;
		Config->fix_size			= FALSE;
		strcpy( Config->uriPath, "resources:///myapp/web/main.html");
		Config->developerEnabled	= 0;

		return 0;
	}	

	printf("Proceed to use config.xml\n\n");
	xmlNode *root = xmlDocGetRootElement(document);

	for(xmlNode *node = root->children; node; node = node->next){
		if(node->type == XML_ELEMENT_NODE && xmlStrcmp(node->name, (const xmlChar *)"gtkwindow") == 0){

			char *name = (char *)xmlGetProp(node, (const xmlChar *)"name");
			char *width = (char *)xmlGetProp(node, (const xmlChar *)"width");
			char *height = (char *)xmlGetProp(node, (const xmlChar *)"height");
			char *fixsize = (char *)xmlGetProp(node, (const xmlChar *)"nofix");

			strcpy( Config->name, name);
			Config->width    = atoi(width);
			Config->height   = atoi(height);

			// if( strcmp( fixsize, "FALSE") == 0 || strcmp( fixsize, "false") == 0){
			// 	Config->fix_size = FALSE;
			// 	printf("FALSE in fix size:\n");
			// }

			if( strcmp( fixsize, "TRUE") == 0 || strcmp( fixsize, "true") == 0){
				Config->fix_size = TRUE;
				printf("TRUE in fix size:\n");
			}


			// Free the attribute values
			xmlFree(name);
			xmlFree(width);
			xmlFree(height);

			// Find the uri element within gtkwindow
			for(xmlNode *child = node->children; child; child = child->next) {
				if(child->type == XML_ELEMENT_NODE && xmlStrcmp(child->name, (const xmlChar *)"uri") == 0) {
					char *path = (char *)xmlGetProp(child, (const xmlChar *)"path");
					strcpy( Config->uriPath, path);                    
					xmlFree(path);
				}else if(child->type == XML_ELEMENT_NODE && xmlStrcmp(child->name, (const xmlChar *)"developer") == 0) {
					char *enable = (char *)xmlGetProp(child, (const xmlChar *)"enable");
					Config->developerEnabled = (strcmp(enable, "true") == 0 || strcmp(enable, "1") == 0);
					xmlFree(enable);
				}
			}

			printf("GTK Window:\n");
			printf("	Name: %s\n", Config->name);
			printf("	Width: %i\n", Config->width);
			printf("	Height: %i\n", Config->height);
			if(Config->fix_size){
				printf("	fix window\n");
			}else{
				printf("	no fix window\n");
			}
			printf("	URI Path: %s\n", Config->uriPath);
			printf("	Developer Enabled: %s\n", Config->developerEnabled ? "true" : "false");
		}
	}

	xmlFreeDoc(document);
	return 1;
}

