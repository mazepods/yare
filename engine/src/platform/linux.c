#include "platform.h"
#include "core/log.h"

#include <xcb/xcb.h>
#include <X11/keysym.h>
#include <X11/XKBlib.h>
#include <X11/Xlib.h>
#include <X11/Xlib-xcb.h>

#include <string.h>
#include <stdlib.h>

typedef struct {
    Display *display;
    xcb_connection_t *connection;
    xcb_window_t window;
    xcb_screen_t *screen;
    xcb_atom_t wm_protocols;
    xcb_atom_t wm_delete_win;
} internal_state;

b8 platform_init(
    platform_state* state,
    const char* app_name,
    i32 x,
    i32 y,
    i32 width,
    i32 height) {
        state->internal_state = malloc(sizeof(internal_state));
        internal_state *i_state = (internal_state *)state->internal_state;
        i_state->display = XOpenDisplay(NULL);
        XAutoRepeatOff(i_state->display);
        i_state->connection = XGetXCBConnection(i_state->display);

        if (xcb_connection_has_error(i_state->connection)) {
            LL_FATAL("Failed connection to X server.");
            return FALSE;
        }

        const struct xcb_setup_t *setup = xcb_get_setup(i_state->connection);
        xcb_screen_iterator_t screen_it = xcb_setup_roots_iterator(setup);
        u32 screen_p = 0;
        for (i32 i = screen_p; i > 0; i--) {
            xcb_screen_next(&screen_it);
        }
        i_state->screen = screen_it.data;
        // Generate an ID for the window
        i_state->window = xcb_generate_id(i_state->connection);

        u32 event_mask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
        // Register for event types using event masks
        u32 events = XCB_EVENT_MASK_KEY_PRESS | XCB_EVENT_MASK_KEY_RELEASE |
                     XCB_EVENT_MASK_BUTTON_PRESS | XCB_EVENT_MASK_BUTTON_RELEASE |
                     XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_STRUCTURE_NOTIFY;
        u32 value_list[] = {i_state->screen->black_pixel, events};

        xcb_void_cookie_t cookie = xcb_create_window(
            i_state->connection,            /* Pointer to the xcb_connection_t structure */
            XCB_COPY_FROM_PARENT,           /* Depth of the screen */
            i_state->window,                /* Id of the window */
            i_state->screen->root,          /* Id of an existing window that should be the parent of the new window */
            x,                              /* X position of the top-left corner of the window (in pixels) */
            y,                              /* Y position of the top-left corner of the window (in pixels) */
            width,                          /* Width of the window (in pixels) */
            height,                         /* Height of the window (in pixels) */
            0,                              /* Width of the window's border (in pixels) */
            XCB_WINDOW_CLASS_INPUT_OUTPUT,
            i_state->screen->root_visual,
            event_mask,
            value_list
        );

        xcb_change_property(
            i_state->connection,
            XCB_PROP_MODE_REPLACE,
            i_state->window,
            XCB_ATOM_WM_NAME,
            XCB_ATOM_STRING,
            8,
            strlen(app_name),
            app_name
        );

        xcb_map_window(i_state->connection, i_state->window);

        //Forces any bufered output to be written to the server
        i32 result = xcb_flush(i_state->connection);
        if (result <= 0) {
            LL_FATAL("%d", result);
            return FALSE;
        }
        return TRUE;
    }

void platform_destroy(platform_state* state) {
    internal_state *i_state = (internal_state *)state->internal_state;
    XAutoRepeatOn(i_state->display);

    xcb_destroy_window(i_state->connection, i_state->window);
}

b8 platform_poll_events(platform_state* state) {
    internal_state *i_state = (internal_state *)state->internal_state;
    xcb_generic_event_t *event;

    while (event != 0) {
        event = xcb_poll_for_event(i_state->connection);
        if (event == 0) { break; }
        switch (event->response_type & ~0x80)
        {
        case XCB_KEY_PRESS:
            break;
        case XCB_KEY_RELEASE:
            break;
        case XCB_BUTTON_PRESS:
            break;
        case XCB_BUTTON_RELEASE:
            break;
        case XCB_CONFIGURE_NOTIFY:
            break;
        case XCB_CLIENT_MESSAGE:
            break;
        default:
            break;
        }
        free(event);
    }
    return TRUE;
}