#include <gtk/gtk.h> // Required for GTK+ functions: window, widget manipulation, etc.
#include <stdlib.h>  // Used for general utility functions: memory allocation, process control, etc.
#include <string.h>  // Needed for string manipulation functions: copying, concatenation, etc.
#include <ctype.h>   // Necessary for character type functions: character classification.

// Constants for messages in different languages
const char* const MESSAGE_EN = "Adobe no longer supports Flash Player after December 31, 2020,\nand blocked Flash content from running in Flash Player beginning\nJanuary 12, 2021.";
const char* const MESSAGE_FR = "Adobe ne prend plus en charge Flash Player depuis le 31 déc. 2020,\net a bloqué le contenu Flash lors de son exécution dans Flash Player\ndepuis le 12 janvier 2021.";
const char* const MESSAGE_SP = "Adobe no ha ofrecido soporte para Flash Player desde el 31 de dic.\nde 2020, y ha bloqueado el contenido Flash al ejecutarse en Flash\nPlayer desde el 12 de enero de 2021.";

void set_language(const char* lang, const char** message){
   switch(tolower(lang[0])){ // Set the language based on the first character of lang, converted to lowercase
      case 'f': *message = MESSAGE_FR; break; // French
      case 's': *message = MESSAGE_SP; break; // Spanish
      default:  *message = MESSAGE_EN;        // Default to English
   }
}

void close_window(GtkWidget* widget, gpointer data){ // Closes the GTK window
   gtk_window_close(GTK_WINDOW(gtk_widget_get_toplevel(widget)));
}

void activate(GtkApplication* app, gpointer user_data){ // Activates the GTK application
   const char* message = *(const char**)user_data;

   GtkWidget* window = gtk_application_window_new(app); // Create a new GTK window
   gtk_window_set_title(GTK_WINDOW(window), "Adobe Flash Player EOL"); // Set window title
   gtk_window_set_default_size(GTK_WINDOW(window), 400, 200); // Set default window size

   GtkWidget* label = gtk_label_new(message); // Create a label with the message
   GtkWidget* button = gtk_button_new_with_label("OK"); // Create an "OK" button
   g_signal_connect(button, "clicked", G_CALLBACK(close_window), NULL); // Connect the button click to close_window function

   GtkWidget* image = gtk_image_new_from_file("/opt/archbangretro/flash_eol_app/FLASH-PLAYER-DEAD.png"); // Load the image

   GtkWidget* box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10); // Create a vertical box container
   gtk_box_pack_start(GTK_BOX(box), image, TRUE, TRUE, 0); // Add the image to the box
   gtk_box_pack_start(GTK_BOX(box), label, TRUE, TRUE, 0); // Add the label to the box
   gtk_box_pack_start(GTK_BOX(box), button, FALSE, FALSE, 0); // Add the button to the box

   gtk_container_add(GTK_CONTAINER(window), box); // Add the box to the window container

   gtk_widget_show_all(window); // Show all widgets within the window
}

int command_line_handler(GtkApplication* app, GApplicationCommandLine* cmdline, gpointer user_data){ // Handles command line arguments
   gchar **argv = g_application_command_line_get_arguments(cmdline, NULL); // Get command line arguments
   const char** message = (const char**)user_data; // Pointer to message string

   if(argv[1]){ // If there is at least one argument
      set_language(argv[1], message); // Set the language based on the argument
   }

   g_strfreev(argv);

   activate(app, user_data); // Activate the application with the given message

   return 0; // Return 0 to indicate success
}

int main(int argc, char** argv){ // Main function
   const char* message = MESSAGE_EN; // Default message is in English

   GtkApplication* app = gtk_application_new("org.example.flash_eol_app", G_APPLICATION_HANDLES_COMMAND_LINE); // Create new GTK application
   g_signal_connect(app, "activate", G_CALLBACK(activate), (gpointer)&message); // Connect the activate signal
   g_signal_connect(app, "command-line", G_CALLBACK(command_line_handler), (gpointer)&message); // Connect the command-line signal

   int status = g_application_run(G_APPLICATION(app), argc, argv); // Run the application
   g_object_unref(app); // Unreference the application object

   return status; // Return the status
} // Ensure this closing bracket is present to correctly end the main function

