#include <gtk/gtk.h>
#include "gui.h"

int main(int argc, char **argv) {
    GtkApplication *app = gtk_application_new("org.bt.manager", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}
