#include "bluetooth.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

extern GtkWidget *device_list;

static int extract_mac(const char *entry, char *mac, size_t mac_size) {
    // extract MAC from a line like: "Device XX:XX:XX:XX:XX:XX Name"
    return sscanf(entry, "Device %17s", mac) == 1;
}

void scan_devices(GtkButton *button, gpointer store_ptr) {
    system("bluetoothctl scan on & sleep 5; bluetoothctl scan off; bluetoothctl devices > /tmp/blue_devices");

    FILE *fp = fopen("/tmp/blue_devices", "r");
    if (!fp) return;

    GtkListStore *store = GTK_LIST_STORE(store_ptr);
    gtk_list_store_clear(store);

    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        GtkTreeIter iter;
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter, 0, line, -1);
    }

    fclose(fp);
}

void connect_device(GtkButton *button, gpointer user_data) {
    GtkTreeSelection *selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(device_list));
    GtkTreeModel *model;
    GtkTreeIter iter;
    if (!gtk_tree_selection_get_selected(selection, &model, &iter)) return;

    gchar *entry;
    gtk_tree_model_get(model, &iter, 0, &entry, -1);

    char mac[18] = {0};
    if (extract_mac(entry, mac, sizeof(mac))) {
        char cmd[256];
        snprintf(cmd, sizeof(cmd), "bluetoothctl connect %s", mac);
        system(cmd);
    }

    g_free(entry);
}

void pair_device(GtkButton *button, gpointer user_data) {
    GtkTreeSelection *selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(device_list));
    GtkTreeModel *model;
    GtkTreeIter iter;
    if (!gtk_tree_selection_get_selected(selection, &model, &iter)) return;

    gchar *entry;
    gtk_tree_model_get(model, &iter, 0, &entry, -1);

    char mac[18] = {0};
    if (extract_mac(entry, mac, sizeof(mac))) {
        char cmd[256];
        snprintf(cmd, sizeof(cmd), "bluetoothctl pair %s", mac);
        system(cmd);
    }

    g_free(entry);
}

void disconnect_device(GtkButton *button, gpointer user_data) {
    GtkTreeSelection *selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(device_list));
    GtkTreeModel *model;
    GtkTreeIter iter;
    if (!gtk_tree_selection_get_selected(selection, &model, &iter)) return;

    gchar *entry;
    gtk_tree_model_get(model, &iter, 0, &entry, -1);

    char mac[18] = {0};
    if (extract_mac(entry, mac, sizeof(mac))) {
        char cmd[256];
        snprintf(cmd, sizeof(cmd), "bluetoothctl disconnect %s", mac);
        system(cmd);
    }

    g_free(entry);
}
