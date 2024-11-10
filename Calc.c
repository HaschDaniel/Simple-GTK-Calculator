#include <ctype.h>
#include <gtk/gtk.h>
#include <stdbool.h>
#include <math.h>

#define WINWIDTH 300
#define WINHEIGHT 400

GtkWidget *label;

double preNum = 0.0;
double curNum = 0.0;
char operator;
char number[32] = {0};
int count = 1;
bool is_decimal = false;
bool math_error = false;

typedef struct {
    GtkWidget *button;
    gchar* label;
} buttons;

buttons button_list[] = {
    {NULL, "C"},
    {NULL, "sqrt"},
    {NULL, "x^2"},
    {NULL, "/"},
    {NULL, "7"},
    {NULL, "8"},
    {NULL, "9"},
    {NULL, "*"},
    {NULL, "4"},
    {NULL, "5"},
    {NULL, "6"},
    {NULL, "-"},
    {NULL, "1"},
    {NULL, "2"},
    {NULL, "3"},
    {NULL, "+"},
    {NULL, "0"},
    {NULL, "."},
    {NULL, "="}
};

static void clear() {
    preNum = 0.0;
    curNum = 0.0;
    operator = '\0';
    strcpy(number, "");
    count = 0;
    is_decimal = false;
    math_error = false;
    gtk_label_set_text(GTK_LABEL(label), "0");
}

static void operatorCount() {
    switch (operator) {
        case '+':
            preNum += curNum;
            break;
        case '-':
            preNum -= curNum;
            break;
        case '*':
            preNum *= curNum;
            break;
        case '/':
            if (curNum == 0.0) {
                math_error = true;
            }
            preNum /= curNum;
            break;
        case 's':
            if (preNum < 0) {
                math_error = true;
                break;
            }
            preNum = sqrt(preNum);
            break;
        case 'x':
            preNum *= preNum;
            break;
        case '=':
            break;
        default:
            preNum = curNum;
    }
}

static void calculate(const gchar* str) {
    curNum = atof(number);
    operatorCount();
    operator = str[0];
}

static void clicked(GtkButton *button, gpointer data) {
    const gchar *str = gtk_button_get_label(button);

    if (strcmp (str, "C") == 0) {
        clear();
    }
    else if (isdigit(str[0])) {
        if (count < 16) {
            strcat(number, str);
            count ++;
        }
        gtk_label_set_text(GTK_LABEL(label), number);
    }
    else if (strcmp (str, ".") == 0) {
        if (!is_decimal) {
            strcat(number, ",");
            count ++;
            is_decimal = true;
        }
        gtk_label_set_text(GTK_LABEL(label), number);
    }
    else {
        calculate(str);
        if (math_error) {
            gtk_label_set_text(GTK_LABEL(label), "MATH ERROR");
        }
        else {
            gcvt(preNum, 12, number);
            gtk_label_set_text(GTK_LABEL(label), number);
            strcpy(number, "");
        }
        is_decimal = false;
        count = 0;
    }
}

GtkWidget *CreateButton(GtkWidget *grid, int index, char* label, int x, int y) {
    GtkWidget *button = gtk_button_new_with_label(label);
    g_signal_connect(button, "clicked", G_CALLBACK(clicked), label);
    gtk_grid_attach(GTK_GRID(grid), button, x, y, 1, 1);
    return button;
}

static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *grid;

    window = gtk_application_window_new(app);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(window), "Calculator");
    gtk_window_set_default_size(GTK_WINDOW(window), WINWIDTH, WINHEIGHT);

    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);

    label = gtk_label_new("0");
    gtk_widget_set_name(label, "label");

    gtk_grid_attach (GTK_GRID (grid), label, 0, 0, 4, 1);

    for (int i = 0; i < 19; i++) {
        button_list[i].button = CreateButton(grid, i, button_list[i].label, i % 4, i / 4 + 1);
    }

    gtk_widget_show_all(window);
}

int main(int argc, char **argv) {
    GtkApplication *app;
    int status;

    app = gtk_application_new("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return (status);
}