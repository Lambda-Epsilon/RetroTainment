#include <stdio.h>
#include <stdlib.h>
#include "lvgl/lvgl.h"


/*INITILIZATION FUNCTIONS*/


/*Creates and moves the config to the home directory, if it doesn't exist*/
void config_setup()
{
    // Path to the template file in the templates directory
    const char *template_file = "../templates/config_template.txt";
    const char *home_env = getenv("HOME");

    if (home_env == NULL) {
        fprintf(stderr, "Error: HOME environment variable not set. Report this to the developer.\n");
        return;
    }

    /*printf("Using template file path: %s\n", template_file);*/
    /*printf("HOME environment variable: %s\n", home_env);*/

    char dest_file[256];
    snprintf(dest_file, sizeof(dest_file), "%s/config.txt", home_env);

    // Check if the destination file already exists
    FILE *dest_check = fopen(dest_file, "r");
    if (dest_check != NULL) {
        // File already exists
        /*printf("File %s already exists. No action taken.\n", dest_file);*/
        fclose(dest_check);
        return;
    }

    // Proceed with copying if the file does not exist
    FILE *source = fopen(template_file, "r");
    if (source == NULL) {
        perror("Error opening template config file. Report this to the developer.");
        return;
    }

    FILE *dest = fopen(dest_file, "w");
    if (dest == NULL) {
        perror("Error opening destination file. Report this to the developer.");
        fclose(source);
        return;
    }

    char buffer[1024];
    size_t bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), source)) > 0) {
        fwrite(buffer, 1, bytes, dest);
    }

    fclose(source);
    fclose(dest);
    
    /*printf("File copied to %s\n", dest_file);*/
}

/*Initializes the UI*/
void ui_init(void)
{
    // Create a screen
    lv_obj_t * scr = lv_obj_create(NULL); // Create a new screen object

    // Create a label and add it to the screen
    lv_obj_t * label = lv_label_create(scr); // Create a label object
    lv_label_set_text(label, "Hello, LVGL!"); // Set the label text
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0); // Center the label

    // Load the screen
    lv_scr_load(scr); // Set the created screen as the active screen
}


/*SYSTEM INITIALIZATION*/

void initialize_system()
{
    /*Init functions*/

    /*Config loading or creation*/
    config_setup();

    /*Database initialization*/

    /*while(1) { */
        /* Event loop */
    /*}*/
}