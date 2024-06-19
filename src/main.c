#include <webkit2/webkit2.h>
#include <gtk/gtk.h>
#include <pthread.h>

#include <arpa/inet.h>
#include <sys/socket.h>


// gcc -o embedded-webkit src/main.c `pkg-config --cflags --libs gtk+-3.0 webkit2gtk-4.0`


int counter = 0;
gboolean Continue_Services(void *arg){
    // do nothing for now.
    counter += 1;
    printf("\n Counter: %i", counter);

    return G_SOURCE_CONTINUE; // Continue calling this function
}


void *Start_Services(void *arg){

    // printf("\n Start Other Background Services: ");
}


void *background_task(void *arg) {
    pthread_t secondary_thread;

    if (pthread_create(&secondary_thread, NULL, Start_Services, NULL) != 0) {
        fprintf(stderr, "Failed to create server thread\n");
        return NULL;
    }

    while (1) {
        g_usleep(10000000);
        g_idle_add( Continue_Services, NULL);
    }
    g_print("Background task loop broken\n");

    return NULL;
}


gboolean on_delete_event(GtkWidget *widget, GdkEvent *event, gpointer data) {
    g_print("Window close signal received\n");


    // Perform any necessary cleanup or prompt the user before closing
    g_application_quit(G_APPLICATION(data));
    return TRUE; // Returning TRUE prevents the default handler from running
}


static void activate(GtkApplication* app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *webview;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Embedded WebKit Example");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);

    // getting kill signal.
    g_signal_connect(window, "delete-event", G_CALLBACK(on_delete_event), app);    

    webview = webkit_web_view_new();
    gtk_container_add(GTK_CONTAINER(window), webview);

    // Get WebKit settings and optimize them
    WebKitSettings *settings = webkit_web_view_get_settings(WEBKIT_WEB_VIEW(webview));
    webkit_settings_set_enable_javascript(settings, TRUE);  // Set to FALSE if JavaScript is not needed
    webkit_settings_set_hardware_acceleration_policy(settings, WEBKIT_HARDWARE_ACCELERATION_POLICY_ALWAYS);

    webkit_web_view_load_uri(WEBKIT_WEB_VIEW(webview), "https://www.w3schools.com/");

    gtk_widget_show_all(window);

    pthread_t thread;

    if (pthread_create(&thread, NULL, background_task, NULL) != 0) {
        fprintf(stderr, "Failed to create background thread\n");
        return;
    }    
}


int main(int argc, char **argv) {
    GtkApplication *app;
    int status;

    app = gtk_application_new("com.example.EmbeddedWebKit", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}


