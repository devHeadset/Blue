#include "gui.h"
#include "bluetooth.h"

GtkWidget *device_list;

void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Blue");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 350);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    GtkListStore *store = gtk_list_store_new(1, G_TYPE_STRING);
    device_list = gtk_tree_view_new_with_model(GTK_TREE_MODEL(store));

    GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
    GtkTreeViewColumn *column = gtk_tree_view_column_new_with_attributes("Discovered Devices", renderer, "text", 0, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(device_list), column);

    GtkWidget *scroll = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scroll), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_container_add(GTK_CONTAINER(scroll), device_list);
    gtk_box_pack_start(GTK_BOX(vbox), scroll, TRUE, TRUE, 0);

    GtkWidget *button_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 8);
    gtk_box_pack_start(GTK_BOX(vbox), button_box, FALSE, FALSE, 0);

    GtkWidget *scan_button = gtk_button_new_with_label("Scan");
    g_signal_connect(scan_button, "clicked", G_CALLBACK(scan_devices), store);
    gtk_box_pack_start(GTK_BOX(button_box), scan_button, TRUE, TRUE, 0);

    GtkWidget *pair_button = gtk_button_new_with_label("Pair");
    g_signal_connect(pair_button, "clicked", G_CALLBACK(pair_device), NULL);
    gtk_box_pack_start(GTK_BOX(button_box), pair_button, TRUE, TRUE, 0);

    GtkWidget *connect_button = gtk_button_new_with_label("Connect");
    g_signal_connect(connect_button, "clicked", G_CALLBACK(connect_device), NULL);
    gtk_box_pack_start(GTK_BOX(button_box), connect_button, TRUE, TRUE, 0);

    GtkWidget *disconnect_button = gtk_button_new_with_label("Disconnect");
    g_signal_connect(disconnect_button, "clicked", G_CALLBACK(disconnect_device), NULL);
    gtk_box_pack_start(GTK_BOX(button_box), disconnect_button, TRUE, TRUE, 0);

    gtk_widget_show_all(window);
}
