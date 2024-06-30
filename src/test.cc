void parseAndPrintConfig(const char *filename) {
    // Load the XML document
    xmlDoc *document = xmlReadFile(filename, NULL, 0);
    if (document == NULL) {
        printf("Could not parse the XML file: %s\n", filename);
        return;
    }

    // Get the root element node
    xmlNode *root = xmlDocGetRootElement(document);

    // Iterate over the XML tree
    for (xmlNode *node = root->children; node; node = node->next) {
        if (node->type == XML_ELEMENT_NODE && xmlStrcmp(node->name, (const xmlChar *)"gtkwindow") == 0) {
            // Get the attributes of the gtkwindow element
            char *name = (char *)xmlGetProp(node, (const xmlChar *)"name");
            char *width = (char *)xmlGetProp(node, (const xmlChar *)"width");
            char *height = (char *)xmlGetProp(node, (const xmlChar *)"height");

            printf("GTK Window:\n");
            printf("  Name: %s\n", name);
            printf("  Width: %s\n", width);
            printf("  Height: %s\n", height);

            // Free the attribute values
            xmlFree(name);
            xmlFree(width);
            xmlFree(height);

            // Find the uri element within gtkwindow
            for (xmlNode *child = node->children; child; child = child->next) {
                if (child->type == XML_ELEMENT_NODE && xmlStrcmp(child->name, (const xmlChar *)"uri") == 0) {
                    char *path = (char *)xmlGetProp(child, (const xmlChar *)"path");
                    printf("  URI Path: %s\n", path);
                    xmlFree(path);
                }
            }
        }
    }

    // Free the document
    xmlFreeDoc(document);
    xmlCleanupParser();
}