#include <string.h>
#include "interface.h"

void closeApp(GtkWidget *window, gpointer data)
{
	gtk_main_quit();
}

gboolean delete_event(GtkWidget *widget, GdkEvent *event, gpointer data)//返回TRUE则取消关闭消息
{
	return FALSE;
}

void button_clicked(GtkWidget *button, gpointer data)
{
	printf("ButtonClicked\\n");
}

int InitWindow()
{
	GtkWidget *window;//主窗口指针
	GtkWidget *button;

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "工程向导");
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);

	g_signal_connect(GTK_OBJECT(window), "destroy", GTK_SIGNAL_FUNC(closeApp), NULL);
	g_signal_connect(GTK_OBJECT(window), "delete_event", GTK_SIGNAL_FUNC(delete_event), NULL);

	button = gtk_button_new_with_label("OK");
	
	gtk_container_add(GTK_CONTAINER(window), button);
	
	g_signal_connect(GTK_OBJECT(button), "clicked", GTK_SIGNAL_FUNC(button_clicked), gpointer("OK"));

	gtk_widget_show_all(window);

	gtk_main();

	return 0;
}
