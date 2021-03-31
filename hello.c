#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define GDK_VERSION_MIN_REQUIRED GDK_VERSION_3_4
#define GDK_VERSION_MAX_ALLOWED GDK_VERSION_3_4
#include <gtk/gtk.h>


gboolean draw(GtkWidget *widget, cairo_t *cr, gpointer data)
{
    double x, y, w, h;
    cairo_clip_extents(cr, &x, &y, &w, &h);
    cairo_set_source_rgba (cr, 1., 0., 0., 0.25); //translucent red
    cairo_set_operator(cr, CAIRO_OPERATOR_SOURCE);
    cairo_rectangle(cr, x, y, w, h);
    cairo_fill(cr);

    return FALSE;
}


void fix_visual(GtkWidget *w)
{
    GdkScreen *screen = gtk_widget_get_screen (w);
    GdkVisual *visual = gdk_screen_get_rgba_visual (screen);
    gtk_widget_set_visual(w, visual);
    //FIXME cleanup maybe
}


void screen_changed (GtkWidget *widget, GdkScreen *screen, gpointer user_data)
{
    fix_visual (widget);
}

int main(int argc, char *argv[])
{



    GtkWidget *w;
    GtkWidget *q;

    gtk_init(&argc, &argv);

    w = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(w, "destroy", G_CALLBACK(gtk_main_quit), NULL);


    q = gtk_layout_new(NULL, NULL);

    g_signal_connect(w, "screen-changed", G_CALLBACK(screen_changed), NULL);
    g_signal_connect(q, "draw", G_CALLBACK(draw), NULL);

    gtk_container_add(GTK_CONTAINER(w), q);

    gtk_widget_set_app_paintable (w, TRUE);

    fix_visual (w);

    gtk_widget_show_all(w);


    gtk_main();
    return 0;
}

