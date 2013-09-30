#include "elm_skel_app.h"
#include "elm_skel.h"

#define MAX_PATH 64

static Eina_Bool sigint_handler(void *data EINA_UNUSED,
                                int ev_type EINA_UNUSED,
                                void *ev EINA_UNUSED)
{
   EINA_LOG_ERR("Ctrl-C hit");
   elm_exit();
   return EINA_TRUE;
}

static void
on_del(void *data EINA_UNUSED,
       Evas_Object *obj EINA_UNUSED,
       void *event_info EINA_UNUSED)
{
   EINA_LOG_INFO("delete,request");
   elm_exit();
}

static void
on_click(void *data EINA_UNUSED,
         Evas_Object *obj EINA_UNUSED,
         void *event_info EINA_UNUSED)
{
   EINA_LOG_INFO("clicked");
   elm_exit();
}

static void
use_layout(Evas_Object *win, const char *theme)
{
   Evas_Object *layout;
   char buf[MAX_PATH];

   // load and add the layout
   layout = elm_layout_add(win);
   evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   snprintf(buf, sizeof(buf), "%s/themes/%s.edj", elm_app_data_dir_get(), theme);
   elm_layout_file_set(layout, buf, "layout");
   elm_win_resize_object_add(win, layout);
   evas_object_show(layout);

   // set the window title from the settings
   const char *title = elm_layout_data_get(layout, "title");
   if (title)
     {
        elm_win_title_set(win, title);
        elm_object_part_text_set(layout, "title", title);
     }
}

static void
set_content(Evas_Object *win)
{
   Evas_Object *box, *lab, *btn;

   // add a vertical box as a resize object for the window
   // (controls window minimum size and gets resized if window is resized)
   // expands so that the window can be resized
   box = elm_box_add(win);
   elm_box_horizontal_set(box, EINA_FALSE);
   evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_win_resize_object_add(win, box);
   evas_object_show(box);

   // add a label widget, set the text
   // pack it at the end of the box
   // centered has it doesn't fill horizontaly
   lab = elm_label_add(win);
   elm_object_text_set(lab, "Label");
   evas_object_size_hint_weight_set(lab, 0, EVAS_HINT_EXPAND);
   elm_box_pack_end(box, lab);
   evas_object_show(lab);

   // add a button widget, set the text
   // expands and fills the space in both directions
   // pack it at the end of the box
   // call on_click when it is clicked
   btn = elm_button_add(win);
   elm_object_text_set(btn, "OK");
   evas_object_size_hint_weight_set(btn, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(btn, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_box_pack_end(box, btn);
   evas_object_smart_callback_add(btn, "clicked", on_click, NULL);
   elm_object_focus_set(btn, EINA_TRUE);
   evas_object_show(btn);
}

EAPI Evas_Object*
elm_skel_app(Eina_Bool fullscreen, Eina_Rectangle geometry, const char* theme)
{
   ecore_event_handler_add(ECORE_EVENT_SIGNAL_EXIT, sigint_handler, NULL);

   Evas_Object *win, *bg;

   // create window
   win = elm_win_add(NULL, "hello", ELM_WIN_BASIC);
   /* win = elm_win_util_standard_add("hello", elm_skel_hello()); */
   if (!win) return NULL;
   evas_object_smart_callback_add(win, "delete,request", on_del, NULL);
   elm_win_focus_highlight_enabled_set(win, EINA_TRUE);
   elm_win_autodel_set(win, EINA_TRUE);
   evas_object_show(win);

   // add resizing background (done by elm_win_util_standard_add)
   bg = elm_bg_add(win);
   if (!bg) {
        evas_object_del(win);
        return NULL;
   }
   evas_object_size_hint_weight_set(bg, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_win_resize_object_add(win, bg);
   evas_object_show(bg);

   // feed the window
   if(theme)
     {
        elm_bg_color_set(bg, 0, 0, 0);
        use_layout(win, theme);
     }
   else
     {
        set_content(win);
        elm_win_title_set(win, elm_skel_hello());
     }

   // set position and size according to parameters
   if(fullscreen)
     {
        elm_win_fullscreen_set(win, EINA_TRUE);
     }
   else
     {
        evas_object_resize(win, geometry.w, geometry.h);
        evas_object_move(win, geometry.x, geometry.y);
     }

   return win;
}

