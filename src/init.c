#include <stdio.h>
#include <stdlib.h>
#include "lvgl/lvgl.h"


/* --- Forward declarations --- */
static void btn_event_cb(lv_event_t * e); // Declare the button callback function


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

    char dest_file[256];
    snprintf(dest_file, sizeof(dest_file), "%s/config.txt", home_env);

    // Check if the destination file already exists
    FILE *dest_check = fopen(dest_file, "r");
    if (dest_check != NULL) {
        // File already exists; no action needed
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
}


/*Initializes the UI*/
void ui_init(void)
{
    // Create a screen
    lv_obj_t * scr = lv_obj_create(NULL);

    // Create a label and add it to the screen
    lv_obj_t * label = lv_label_create(scr);
    lv_label_set_text(label, "Hello, LVGL!");
    lv_obj_align(label, LV_ALIGN_CENTER, 0, -50); // shift label upward slightly

    // Create a clickable button
    lv_obj_t * btn = lv_btn_create(scr);
    lv_obj_align(btn, LV_ALIGN_CENTER, 0, 50); // put it below the label
    lv_obj_add_event_cb(btn, btn_event_cb, LV_EVENT_CLICKED, NULL); // Callback

    // Create a label on the button
    lv_obj_t * btn_label = lv_label_create(btn);
    lv_label_set_text(btn_label, "Click Me!");
    lv_obj_center(btn_label);

    // Load the screen
    lv_scr_load(scr);
}


/* Button event callback */
static void btn_event_cb(lv_event_t * e)
{
    // Just print to console for now
    printf("Button clicked!\n");
}


/*SYSTEM INITIALIZATION*/
void initialize_system()
{
    // Config loading or creation
    config_setup();

    // Future: Database initialization, etc.
    // ...

    // You will need an LVGL loop somewhere in your main,
    // e.g.:
    // while(1) {
    //     lv_timer_handler();
    //     usleep(5 * 1000);
    // }
}
