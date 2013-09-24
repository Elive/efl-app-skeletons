#include "elm_skel_app.h"
#include "elm_skel.h"

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

EAPI Evas_Object*
elm_skel_app()
{
   ecore_event_handler_add(ECORE_EVENT_SIGNAL_EXIT, sigint_handler, NULL);

   Evas_Object *win, *box, *lab, *btn;

   win = elm_win_util_standard_add("hello", elm_skel_hello());
   evas_object_smart_callback_add(win, "delete,request", on_del, NULL);

   // add a vertical box as a resize object for the window
   // (controls window minimum size and gets resized if window is resized)
   box = elm_box_add(win);
   elm_box_horizontal_set(box, EINA_TRUE);
   elm_win_resize_object_add(win, box);
   evas_object_show(box);

   // add a label widget, set the text
   // pack it at the end of the box
   lab = elm_label_add(win);
   elm_object_text_set(lab, "Label");
   elm_box_pack_end(box, lab);
   evas_object_show(lab);

   // add a button widget, set the text
   // pack it at the end of the box
   // call on_click when it is clicked
   btn = elm_button_add(win);
   elm_object_text_set(btn, "OK");
   elm_box_pack_end(box, btn);
   evas_object_show(btn);
   evas_object_smart_callback_add(btn, "clicked", on_click, NULL);
   elm_object_focus_set(btn, EINA_TRUE);

   return win;
}
