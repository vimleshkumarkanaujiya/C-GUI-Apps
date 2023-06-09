#include <gtk/gtk.h>
#include <iostream>
#include <sstream>

// Global variables
GtkWidget *result_label;

// Function prototypes
void on_button_clicked(GtkButton *button, gpointer data);
void on_clear_clicked(GtkButton *button, gpointer data);

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Calculator");
    gtk_window_set_default_size(GTK_WINDOW(window), 200, 300);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    result_label = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(grid), result_label, 0, 0, 4, 1);

    const gchar *buttons[] = {
        "7", "8", "9", "/",
        "4", "5", "6", "*",
        "1", "2", "3", "-",
        "0", ".", "=", "+"
    };

    GtkWidget *button;
    int row = 1;
    int col = 0;

    for (int i = 0; i < 16; i++) {
        button = gtk_button_new_with_label(buttons[i]);
        gtk_grid_attach(GTK_GRID(grid), button, col, row, 1, 1);
        g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), result_label);

        col++;
        if (col > 3) {
            col = 0;
            row++;
        }
    }

    GtkWidget *clear_button = gtk_button_new_with_label("Clear");
    gtk_grid_attach(GTK_GRID(grid), clear_button, 0, row, 4, 1);
    g_signal_connect(clear_button, "clicked", G_CALLBACK(on_clear_clicked), result_label);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}

void on_button_clicked(GtkButton *button, gpointer data) {
    const gchar *label = gtk_button_get_label(button);
    const gchar *result = gtk_label_get_label(GTK_LABEL(data));

    std::string expression(result);

    if (strcmp(label, "+") == 0 || strcmp(label, "-") == 0 ||
        strcmp(label, "*") == 0 || strcmp(label, "/") == 0) {
        gchar *new_result = g_strdup_printf("%s %s ", result, label);
        gtk_label_set_text(GTK_LABEL(data), new_result);
    } else if (strcmp(label, "=") == 0) {
        std::istringstream iss(expression);
        std::string number, operation;
        int total = 0;

        while (iss >> number) {
            if (number == "+" || number == "-" || number == "*" || number == "/") {
                operation = number;
            } else {
                int num;
                std::istringstream(number) >> num;

                if (operation == "+") {
                    total += num;
                } else if (operation == "-") {
                    total -= num;
                } else if (operation == "*") {
                    total *= num;
                } else if (operation == "/") {
                    total /= num;
                } else {
                    total = num;
                }
            }
        }

        gtk_label_set_text(GTK_LABEL(data), g_strdup_printf("%d", total));
    } else {
        gchar *new_result = g_strdup_printf("%s%s", result, label);
        gtk_label_set_text(GTK_LABEL(data), new_result);
    }
}

void on_clear_clicked(GtkButton *button, gpointer data) {
    gtk_label_set_text(GTK_LABEL(data), "");
}
