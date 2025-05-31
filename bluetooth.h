#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <gtk/gtk.h>

void scan_devices(GtkButton *button, gpointer store);
void connect_device(GtkButton *button, gpointer user_data);
void pair_device(GtkButton *button, gpointer user_data);
void disconnect_device(GtkButton *button, gpointer user_data);

#endif
