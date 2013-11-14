#include "app.h"

static void
_app_exit(App *app)
{
   INF("Shutdown...");
   elm_exit();
   (void) app;
}

static Eina_Bool
_sigint_handler(void *data, int ev_type EINA_UNUSED, void *ev EINA_UNUSED)
{
   App *app = (App *) data;

   INF("Ctrl-C hit");
   _app_exit(app);

   return EINA_TRUE;
}

static void
_on_del(void *data, Evas_Object *obj EINA_UNUSED, void *evt_inf EINA_UNUSED)
{
   App *app = (App *) data;

   INF("delete,request");
   _app_exit(app);
}

static void
_on_tunnel_signal(void *data, Evas_Object *obj, const char *sig, const char *src)
{
   App *app = (App *) data;

   if (!strcmp(sig, "mouse,move"))
     return;

   INF("recv theme sig : %s - %s (%p)", sig, src, obj);
   if (!strcmp(sig, "tunnel,exit"))
     _app_exit(app);
}

/* EDJE */
static Eina_Bool
_load_edje_group(Evas_Object *evas, const char *group, const char *edje_path)
{
   if (!edje_object_file_set(evas, edje_path, group))
     {
        int err = edje_object_load_error_get(evas);
        const char *errmsg = edje_load_error_str(err);
        ERR("Could not load '%s' group from %s: %s",
                     group, edje_path, errmsg);

        return EINA_FALSE;
     }

   return EINA_TRUE;
}

/* NAVIFRAME */

static void
_on_btn_click(void *data, Evas_Object *obj EINA_UNUSED, void *evt_inf EINA_UNUSED)
{
   App *app = (App *) data;

   INF("clicked");
   app_gui_notify(app, "If you see a light at the end of the tunnel,"
             "<br> it could be a train…");
}

static void
_on_nf_title_clicked(void *data, Evas_Object *obj EINA_UNUSED, void *evt_inf EINA_UNUSED)
{
   App *app = (App *) data;

   INF("title clicked");
   (void) app;
}

static void _page1(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED);
static void _page2(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED);

static void
_page2(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   App *app = (App *) data;
   Elm_Object_Item *it;
   Evas_Object *layout;

   // load and add the elm layout
   /* layout = elm_layout_add(app->nf); */
   /* evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND); */
   /* elm_layout_file_set(layout, app->theme_path, "tunnel_layout"); */

   // load and add the edje layout
   layout = edje_object_add(app->gui.nf);
   if (!_load_edje_group(layout, "tunnel_layout", app->theme_path))
     {
        evas_object_del(layout);
        return;
     }
   evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_win_resize_object_add(app->gui.nf, layout);
   evas_object_show(layout);

   /* edje_object_signal_callback_add(elm_layout_edje_get(layout), "*", "*", _on_theme_signal, app); */
   edje_object_signal_callback_add(layout, "*", "*", _on_tunnel_signal, app);

   it = elm_naviframe_item_push(app->gui.nf, "Tunnel", NULL, NULL, layout, NULL);
   evas_object_data_set(app->gui.nf, "page2", it);
}

static void
_page1(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   App *app = (App *) data;
   Elm_Object_Item *it;
   Evas_Object *box, *lab, *btn, *ic;

   // add a vertical box as a resize object for the window
   // (controls window minimum size and gets resized if window is resized)
   // expands so that the window can be resized
   box = elm_box_add(app->gui.nf);
   elm_box_horizontal_set(box, EINA_FALSE);
   evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_win_resize_object_add(app->gui.nf, box);
   evas_object_show(box);

   // add a label widget, set the text
   // pack it at the end of the box
   // centered has it doesn't fill horizontaly
   lab = elm_label_add(app->gui.nf);
   elm_object_text_set(lab, "Label");
   evas_object_size_hint_weight_set(lab, 0, EVAS_HINT_EXPAND);
   elm_box_pack_end(box, lab);
   evas_object_show(lab);

   // add a button widget, set the text
   // expands and fills the space in both directions
   // pack it at the end of the box
   // call on_click when it is clicked
   btn = elm_button_add(app->gui.nf);
   elm_object_text_set(btn, "OK");
   evas_object_size_hint_weight_set(btn, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   /* evas_object_size_hint_align_set(btn, EVAS_HINT_FILL, EVAS_HINT_FILL); */
   elm_box_pack_end(box, btn);
   evas_object_smart_callback_add(btn, "clicked", _on_btn_click, app);
   elm_object_focus_set(btn, EINA_TRUE);
   evas_object_show(btn);

   // add naviframe button,
   // by default only left button to previous existing frame is set
   btn = elm_button_add(app->gui.nf);
   elm_object_text_set(btn, "Tunnel");
   /* elm_object_tooltip_text_set(btn, "Next naviframe"); */
   /* elm_object_tooltip_window_mode_set(btn, EINA_TRUE); */
   evas_object_size_hint_align_set(btn, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_smart_callback_add(btn, "clicked", _page2, app);

   // add button icon
   ic = elm_icon_add(app->gui.nf);
   elm_icon_standard_set(ic, "arrow_right");
   evas_object_size_hint_aspect_set(ic, EVAS_ASPECT_CONTROL_VERTICAL, 1, 1);
   elm_layout_content_set(btn, "icon", ic);

   it = elm_naviframe_item_push(app->gui.nf, "Simple Page", NULL, btn, box, NULL);
   evas_object_data_set(app->gui.nf, "page1", it);
}

static Evas_Object *
_create_naviframe(App *app, Evas_Object *parent)
{
   Evas_Object *nf;

   app->gui.nf = nf = elm_naviframe_add(parent);
   evas_object_size_hint_weight_set(nf, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_win_resize_object_add(parent, nf);
   evas_object_show(nf);
   evas_object_smart_callback_add(nf, "title,clicked", _on_nf_title_clicked, app);
   _page1(app, NULL, NULL);

   return nf;
}

/* POPUP */

static void
_popup_close_cb(void *data, Evas_Object *obj EINA_UNUSED, void *evt_inf EINA_UNUSED)
{
   App *app = (App *) data;

   evas_object_del(app->gui.popup);
   app->gui.popup = NULL;
}

void
_app_gui_msg(App *app, const char *title, const char *msg, Eina_Bool error,
            float timeout, Evas_Smart_Cb cb)
{
   Evas_Object *popup, *icon, *btn;

   app->gui.popup = popup = elm_popup_add(app->gui.win);

   if (timeout > 0)
     elm_popup_timeout_set(popup, timeout);

   icon = elm_icon_add(popup);
   elm_object_style_set(popup, "transparent");
   elm_icon_standard_set(icon, (error ? "error" : "info"));
   elm_object_part_content_set(popup, "title,icon", icon);

   elm_object_part_text_set(popup, "title,text", title);
   elm_object_text_set(app->gui.popup, msg);
   btn = elm_button_add(popup);
   elm_object_text_set(btn, "Fermer");
   elm_object_part_content_set(popup, "button3", btn);
   evas_object_smart_callback_add(btn, "clicked", cb, app);


   evas_object_show(app->gui.popup);
}

/* APP GUI API */

void
app_gui_notify(App *app, const char *msg)
{
   _app_gui_msg(app, "Info", msg, EINA_FALSE, 5.0, _popup_close_cb);
}

void
app_gui_error(App *app, const char *msg)
{
   _app_gui_msg(app, "Error", msg, EINA_TRUE, 0, _popup_close_cb);
}

EAPI Evas_Object*
app_gui_create(App *app, Eina_Bool fullscreen, Eina_Rectangle geometry)
{
   const char *title = NULL;
   Evas_Object *win, *bg;

   ecore_event_handler_add(ECORE_EVENT_SIGNAL_EXIT, _sigint_handler, NULL);

   /* if (app->extension_path) */
   /*    elm_theme_overlay_add(NULL, app->extension_path); */

   title = edje_file_data_get(app->theme_path, "title");
   if (!title) title = "Missing Title";

   // create window
   app->gui.win = win = elm_win_add(NULL, "hello", ELM_WIN_BASIC);
   /* app->gui.win = win = elm_win_util_standard_add("hello", title); */
   if (!win) return NULL;
   evas_object_smart_callback_add(win, "delete,request", _on_del, NULL);
   elm_win_title_set(win, title);
   elm_win_autodel_set(win, EINA_TRUE);
   elm_win_icon_name_set(win, "elm-skel");
   /* elm_win_focus_highlight_enabled_set(win, EINA_TRUE); */
   evas_object_show(win);

   // add resizing background (done by elm_win_util_standard_add)
   bg = elm_bg_add(win);
   if (!bg) {
        evas_object_del(win);
        return NULL;
   }
   /* elm_bg_color_set(bg, 0, 0, 0); */
   evas_object_size_hint_weight_set(bg, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_win_resize_object_add(win, bg);
   evas_object_show(bg);

   _create_naviframe(app, win);

   // set position and size according to parameters
   if(fullscreen)
     {
        elm_win_fullscreen_set(win, EINA_TRUE);
     }
   else
     {
        evas_object_move(win, geometry.x, geometry.y);
        evas_object_resize(win, geometry.w, geometry.h);
     }
   evas_object_show(win);

   return win;
}

