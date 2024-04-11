/* Taken from https://github.com/djpohly/dwl/issues/466 */
#define COLOR(hex)                                                             \
  {                                                                            \
    ((hex >> 24) & 0xFF) / 255.0f, ((hex >> 16) & 0xFF) / 255.0f,              \
        ((hex >> 8) & 0xFF) / 255.0f, (hex & 0xFF) / 255.0f                    \
  }
/* appearance */
static const int sloppyfocus = 1; /* focus follows mouse */
static const int bypass_surface_visibility =
    0; /* 1 means idle inhibitors will disable idle tracking even if it's
          surface isn't visible  */
static const unsigned int borderpx = 1; /* border pixel of windows */
static const unsigned int gappx = 8;    /* gap between windows */
static const float rootcolor[] = COLOR(0x475437ff);
static const float bordercolor[] = COLOR(0x1e8b50d9);
static const float focuscolor[] = COLOR(0x90ceaaff);
static const float urgentcolor[] = COLOR(0xecd3a0ff);
/* This conforms to the xdg-protocol. Set the alpha to zero to restore the old
 * behavior */
static const float fullscreen_bg[] = {0.1f, 0.1f, 0.1f,
                                      1.0f}; /* You can also use glsl colors */

/* bar */
static const int showbar = 1; /* 0 means no bar */
static const int topbar = 1;  /* 0 means bottom bar */
static const char *fonts[] = {"CaskaydiaCove Nerd Font Mono:size=12",
                              "monospace:size=12"};
static const char *fontattrs = "dpi=96";
static pixman_color_t selbarfg = {0xc2c2, 0xd8d8, 0x9c9c, 0xffff};
static pixman_color_t selbarbg = {0x4747, 0x5454, 0x3737, 0xffff};
static pixman_color_t normbarfg = {0xc2c2, 0xd8d8, 0x9c9c, 0xffff};
static pixman_color_t normbarbg = {0x6666, 0x8f8f, 0x3131, 0xffff};

/* Autostart */
static const char *const autostart[] = {
    "resetxdgportal.sh",
    NULL,
    "dbus-update-activation-environment",
    "--systemd",
    "WAYLAND_DISPLAY",
    "XDG_CURRENT_DESKTOP",
    NULL, /* for XDPH */
    "dbus-update-activation-environment",
    "--systemd",
    "--all",
    NULL, /* for XDPH */
    "systemctl",
    "--user",
    "import-environment",
    "WAYLAND_DISPLAY",
    "XDG_CURRENT_DESKTOP",
    NULL, /* for XDPH */
    "polkitkdeauth.sh",
    NULL, /* authentication dialogue for GUI apps */
    "dunst",
    NULL, /* start notification demon */
    "wl-paste",
    "--type",
    "text",
    "--watch",
    "cliphist",
    "store",
    NULL, /* clipboard store text data */
    "wl-paste",
    "--type",
    "image",
    "--watch",
    "cliphist",
    "store",
    NULL, /* clipboard store image data */
    "swaybg",
    "-i",
    "/home/denis/Pictures/cosmonaut.png",
    NULL, /* start wallpaper daemon */
    "foot",
    "--server",
    NULL, /* start terminal daemon */
    "gsettings",
    "set",
    "org.gnome.desktop.interface",
    "icon-theme",
    "'Gruvbox-Plus-Dark'",
    NULL,
    "gsettings",
    "set",
    "org.gnome.desktop.interface",
    "gtk-theme",
    "'Gruvbox-Retro'",
    NULL,
    "gsettings",
    "set",
    "org.gnome.desktop.interface",
    "color-scheme",
    "'prefer-dark'",
    NULL,
    "gsettings",
    "set",
    "org.gnome.desktop.interface",
    "cursor-theme",
    "'Gruvbox-Retro'",
    NULL,
    "gsettings",
    "set",
    "org.gnome.desktop.interface",
    "cursor-size",
    "20",
    NULL,
    NULL, /* terminate */
};

/* tagging - TAGCOUNT must be no greater than 31 */
static char *tags[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};

/* logging */
static int log_level = WLR_ERROR;

static const Rule rules[] = {
    /* app_id             title       tags mask     isfloating   monitor */
    {"Gimp", NULL, 0, 1,
     -1}, /* Start on currently visible tags floating, not tiled */
    /* { "firefox_EXAMPLE",  NULL,       1 << 8,       0,           -1 }, */
};

/* layout(s) */
static const Layout layouts[] = {
    /* symbol     arrange function */
    {"[\\]", dwindle}, {"[]=", tile}, {"[M]", monocle},
    {"><>", NULL}, /* no layout function means floating behavior */
    {"[@]", spiral},
};

/* monitors */
/* NOTE: ALWAYS add a fallback rule, even if you are completely sure it won't be
 * used */
static const MonitorRule monrules[] = {
    /* name       mfact  nmaster scale layout       rotate/reflect x    y */
    /* example of a HiDPI laptop monitor:
    { "eDP-1",    0.5f,  1,      2,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL,
    -1,  -1 },
    */
    /* defaults */
    {NULL, 0.55f, 1, 1, &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL, -1, -1},
};

/* keyboard */
static const struct xkb_rule_names xkb_rules = {
    /* can specify fields: rules, model, layout, variant, options */
    /* example:
    .options = "ctrl:nocaps",
    */
    .variant = "intl",
    .options = NULL,
};

static const int repeat_rate = 25;
static const int repeat_delay = 600;

/* Trackpad */
static const int tap_to_click = 1;
static const int tap_and_drag = 1;
static const int drag_lock = 1;
static const int natural_scrolling = 0;
static const int disable_while_typing = 1;
static const int left_handed = 0;
static const int middle_button_emulation = 0;
/* You can choose between:
LIBINPUT_CONFIG_SCROLL_NO_SCROLL
LIBINPUT_CONFIG_SCROLL_2FG
LIBINPUT_CONFIG_SCROLL_EDGE
LIBINPUT_CONFIG_SCROLL_ON_BUTTON_DOWN
*/
static const enum libinput_config_scroll_method scroll_method =
    LIBINPUT_CONFIG_SCROLL_2FG;

/* You can choose between:
LIBINPUT_CONFIG_CLICK_METHOD_NONE
LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS
LIBINPUT_CONFIG_CLICK_METHOD_CLICKFINGER
*/
static const enum libinput_config_click_method click_method =
    LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS;

/* You can choose between:
LIBINPUT_CONFIG_SEND_EVENTS_ENABLED
LIBINPUT_CONFIG_SEND_EVENTS_DISABLED
LIBINPUT_CONFIG_SEND_EVENTS_DISABLED_ON_EXTERNAL_MOUSE
*/
static const uint32_t send_events_mode = LIBINPUT_CONFIG_SEND_EVENTS_ENABLED;

/* You can choose between:
LIBINPUT_CONFIG_ACCEL_PROFILE_FLAT
LIBINPUT_CONFIG_ACCEL_PROFILE_ADAPTIVE
*/
static const enum libinput_config_accel_profile accel_profile =
    LIBINPUT_CONFIG_ACCEL_PROFILE_ADAPTIVE;
static const double accel_speed = 0.0;

/* You can choose between:
LIBINPUT_CONFIG_TAP_MAP_LRM -- 1/2/3 finger tap maps to left/right/middle
LIBINPUT_CONFIG_TAP_MAP_LMR -- 1/2/3 finger tap maps to left/middle/right
*/
static const enum libinput_config_tap_button_map button_map =
    LIBINPUT_CONFIG_TAP_MAP_LRM;

/* If you want to use the windows key for MODKEY, use WLR_MODIFIER_LOGO */
#define MODKEY WLR_MODIFIER_LOGO

#define TAGKEYS(KEY, SKEY, TAG)                                                \
  {MODKEY, KEY, view, {.ui = 1 << TAG}},                                       \
      {MODKEY | WLR_MODIFIER_CTRL, KEY, toggleview, {.ui = 1 << TAG}},         \
      {MODKEY | WLR_MODIFIER_SHIFT, SKEY, tag, {.ui = 1 << TAG}}, {            \
    MODKEY | WLR_MODIFIER_CTRL | WLR_MODIFIER_SHIFT, SKEY, toggletag, {        \
      .ui = 1 << TAG                                                           \
    }                                                                          \
  }

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd)                                                             \
  {                                                                            \
    .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL }                       \
  }

/* commands */
static const char *termcmd[] = {"footclient", NULL};
static const char *menucmd[] = {"wofi", "--show", "drun", NULL};
static const char *ytfzfcmd[] = {"ytfzf", "-D", NULL};
static const char *swaylockcmd[] = {"swaylock", NULL};
static const char *editnotescmd[] = {"/home/denis/.local/bin/editnotes.sh",
                                     NULL};
static const char *screenshotcmd[] = {"grimblast", "copysave", "area", NULL};
static const char *logoutcmd[] = {"wlogout", NULL};
static const char *firefoxcmd[] = {"firefox", NULL};
static const char *qutebrowsercmd[] = {"qutebrowser", NULL};
static const char *mutecmd[] = {
    "/home/denis/.config/hyprdots/scripts/volumecontrol.sh", "-o", "m", NULL};
static const char *lowervolumecmd[] = {
    "/home/denis/.config/hyprdots/scripts/volumecontrol.sh", "-o", "d", NULL};
static const char *raisevolumecmd[] = {
    "/home/denis/.config/hyprdots/scripts/volumecontrol.sh", "-o", "i", NULL};

static const Key keys[] = {
    /* Note that Shift changes certain key codes: c -> C, 2 -> at, etc. */
    /* modifier                  key                 function        argument */
    {MODKEY, XKB_KEY_p, spawn, {.v = menucmd}},
    {MODKEY, XKB_KEY_Return, spawn, {.v = termcmd}},
    {MODKEY | WLR_MODIFIER_CTRL, XKB_KEY_b, togglebar, {0}},
    {MODKEY, XKB_KEY_j, focusstack, {.i = +1}},
    {MODKEY, XKB_KEY_k, focusstack, {.i = -1}},
    {MODKEY, XKB_KEY_i, incnmaster, {.i = +1}},
    {MODKEY, XKB_KEY_d, incnmaster, {.i = -1}},
    {MODKEY, XKB_KEY_h, setmfact, {.f = -0.05f}},
    {MODKEY, XKB_KEY_l, setmfact, {.f = +0.05f}},
    {MODKEY | WLR_MODIFIER_ALT, XKB_KEY_h, incgaps, {.i = +1}},
    {MODKEY | WLR_MODIFIER_ALT, XKB_KEY_l, incgaps, {.i = -1}},
    {MODKEY | WLR_MODIFIER_ALT, XKB_KEY_0, togglegaps, {0}},
    {MODKEY | WLR_MODIFIER_ALT | WLR_MODIFIER_SHIFT,
     XKB_KEY_parenright,
     defaultgaps,
     {0}},
    {MODKEY | WLR_MODIFIER_CTRL, XKB_KEY_Return, zoom, {0}},
    {MODKEY, XKB_KEY_Tab, view, {0}},
    {MODKEY | WLR_MODIFIER_SHIFT, XKB_KEY_C, killclient, {0}},
    {MODKEY, XKB_KEY_b, togglebar, {0}},
    {MODKEY, XKB_KEY_t, setlayout, {.v = &layouts[0]}},
    {MODKEY, XKB_KEY_f, setlayout, {.v = &layouts[1]}},
    {MODKEY, XKB_KEY_m, setlayout, {.v = &layouts[2]}},
    {MODKEY, XKB_KEY_w, setlayout, {.v = &layouts[3]}},
    {MODKEY, XKB_KEY_space, setlayout, {0}},
    {MODKEY | WLR_MODIFIER_SHIFT, XKB_KEY_space, togglefloating, {0}},
    {MODKEY, XKB_KEY_e, togglefullscreen, {0}},
    {MODKEY, XKB_KEY_0, view, {.ui = ~0}},
    {MODKEY | WLR_MODIFIER_SHIFT, XKB_KEY_parenright, tag, {.ui = ~0}},
    {MODKEY, XKB_KEY_comma, focusmon, {.i = WLR_DIRECTION_LEFT}},
    {MODKEY, XKB_KEY_period, focusmon, {.i = WLR_DIRECTION_RIGHT}},
    {MODKEY | WLR_MODIFIER_SHIFT,
     XKB_KEY_less,
     tagmon,
     {.i = WLR_DIRECTION_LEFT}},
    {MODKEY | WLR_MODIFIER_SHIFT,
     XKB_KEY_greater,
     tagmon,
     {.i = WLR_DIRECTION_RIGHT}},
    {MODKEY, XKB_KEY_y, spawn, {.v = ytfzfcmd}},
    {MODKEY | WLR_MODIFIER_CTRL, XKB_KEY_l, spawn, {.v = swaylockcmd}},
    {MODKEY, XKB_KEY_n, spawn, {.v = editnotescmd}},
    {MODKEY, XKB_KEY_s, spawn, {.v = screenshotcmd}},
    {MODKEY, XKB_KEY_b, spawn, {.v = firefoxcmd}},
    {MODKEY, XKB_KEY_q, spawn, {.v = qutebrowsercmd}},
    {MODKEY, XKB_KEY_BackSpace, spawn, {.v = logoutcmd}},
    {0, XKB_KEY_XF86AudioMute, spawn, {.v = mutecmd}},
    {0, XKB_KEY_XF86AudioLowerVolume, spawn, {.v = lowervolumecmd}},
    {0, XKB_KEY_XF86AudioRaiseVolume, spawn, {.v = raisevolumecmd}},
    TAGKEYS(XKB_KEY_1, XKB_KEY_exclam, 0),
    TAGKEYS(XKB_KEY_2, XKB_KEY_at, 1),
    TAGKEYS(XKB_KEY_3, XKB_KEY_numbersign, 2),
    TAGKEYS(XKB_KEY_4, XKB_KEY_dollar, 3),
    TAGKEYS(XKB_KEY_5, XKB_KEY_percent, 4),
    TAGKEYS(XKB_KEY_6, XKB_KEY_asciicircum, 5),
    TAGKEYS(XKB_KEY_7, XKB_KEY_ampersand, 6),
    TAGKEYS(XKB_KEY_8, XKB_KEY_asterisk, 7),
    TAGKEYS(XKB_KEY_9, XKB_KEY_parenleft, 8),
    {MODKEY | WLR_MODIFIER_SHIFT, XKB_KEY_Q, quit, {0}},

    /* Ctrl-Alt-Backspace and Ctrl-Alt-Fx used to be handled by X server */
    {WLR_MODIFIER_CTRL | WLR_MODIFIER_ALT, XKB_KEY_Terminate_Server, quit, {0}},
/* Ctrl-Alt-Fx is used to switch to another VT, if you don't know what a VT is
 * do not remove them.
 */
#define CHVT(n)                                                                \
  {                                                                            \
    WLR_MODIFIER_CTRL | WLR_MODIFIER_ALT, XKB_KEY_XF86Switch_VT_##n, chvt, {   \
      .ui = (n)                                                                \
    }                                                                          \
  }
    CHVT(1),
    CHVT(2),
    CHVT(3),
    CHVT(4),
    CHVT(5),
    CHVT(6),
    CHVT(7),
    CHVT(8),
    CHVT(9),
    CHVT(10),
    CHVT(11),
    CHVT(12),
};

static const Button buttons[] = {
    {ClkLtSymbol, 0, BTN_LEFT, setlayout, {.v = &layouts[0]}},
    {ClkLtSymbol, 0, BTN_RIGHT, setlayout, {.v = &layouts[2]}},
    {ClkTitle, 0, BTN_MIDDLE, zoom, {0}},
    {ClkStatus, 0, BTN_MIDDLE, spawn, {.v = termcmd}},
    {ClkClient, MODKEY, BTN_LEFT, moveresize, {.ui = CurMove}},
    {ClkClient, MODKEY, BTN_MIDDLE, togglefloating, {0}},
    {ClkClient, MODKEY, BTN_RIGHT, moveresize, {.ui = CurResize}},
    {ClkTagBar, 0, BTN_LEFT, view, {0}},
    {ClkTagBar, 0, BTN_RIGHT, toggleview, {0}},
    {ClkTagBar, MODKEY, BTN_LEFT, tag, {0}},
    {ClkTagBar, MODKEY, BTN_RIGHT, toggletag, {0}},
};
