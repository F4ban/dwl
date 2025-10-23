/* Taken from https://github.com/djpohly/dwl/issues/466 */
#define COLOR(hex)    { ((hex >> 24) & 0xFF) / 255.0f, \
                        ((hex >> 16) & 0xFF) / 255.0f, \
                        ((hex >> 8) & 0xFF) / 255.0f, \
                        (hex & 0xFF) / 255.0f }
/* appearance */
static const int sloppyfocus               = 1;  /* focus follows mouse */
static const int bypass_surface_visibility = 0;  /* 1 means idle inhibitors will disable idle tracking even if it's surface isn't visible  */
static const unsigned int borderpx         = 5;  /* border pixel of windows */
static const int showbar                   = 1; /* 0 means no bar */
static const int topbar                    = 1; /* 0 means bottom bar */
static const char *fonts[] 		           = {"Terminus:size=15"};
static const float rootcolor[]             = COLOR(0x000000ff);
static const int smartgaps                 = 0;  /* 1 means no outer gap when there is only one window */
static int enableautoswallow               = 1; /* enables autoswallowing newly spawned clients */
static int gaps                            = 1;  /* 1 means gaps between windows are added */
static const unsigned int gappx            = 25; /* gap pixel between windows */
/* This conforms to the xdg-protocol. Set the alpha to zero to restore the old behavior */
static const float fullscreen_bg[]         = {0.1f, 0.1f, 0.1f, 1.0f}; /* You can also use glsl colors */
static uint32_t colors[][3] = {
    /*               fg          bg          border    */
    [SchemeNorm] = { 0xebdbb2ff, 0x282828ff, 0x504945ff }, 
    [SchemeSel]  = { 0xfbf1c7ff, 0x3c3836ff, 0xaf875fff },
    [SchemeUrg]  = { 0xfbf1c7ff, 0xcc241dff, 0x9d0006ff },
};

/* tagging - TAGCOUNT must be no greater than 31 */
static char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

/* logging */
static int log_level = WLR_ERROR;


static const Env envs[] = {
	/* variable					value */
	{ "XDG_SESSION_TYPE",				"wayland" },
	{ "XDG_CURRENT_DESKTOP",			"sway" },
	{ "XDG_SESSION_DESKTOP",			"sway" },
	{ "QT_AUTO_SCREEN_SCALE_FACTOR",		"1" },
	{ "QT_QPA_PLATFORM",				"wayland;xcb" },
	{ "QT_WAYLAND_DISABLE_WINDOWDECORATION",	"1" },
	{ "GDK_BACKEND",				"wayland,x11" },
	{ "BEMENU_OPTS",				"-i -p 'run' --fb '#282828' --ff '#ebdbb2' --nb '#282828' --nf '#ebdbb2' --tb '#282828' --hb '#282828' --tf '#fabd2f' --hf '#fabd2f' --nf '#ebdbb2' --af '#ebdbb2' --ab '#282828' --fn 'IBMPlexMono 16'"}
};

/* Autostart */
static const char *const autostart[] = {
        "swaybg", "-m", "tile", "-i", "/home/anon/pictures/tile.png", NULL,
        "foot", "--server", NULL,
        "sh", "-c", "/usr/lib/xdg-desktop-portal -r & /usr/lib/xdg-desktop-portal-wlr", NULL,
        "dunst", NULL,
        "sh", "-c", "swayidle -w \
		timeout 600 'swaylock -f -c 000000' \
		timeout 800 'systemctl suspend' before-sleep 'swaylock -f -c 000000' \
		", NULL,
        NULL /* terminate */
};

/* NOTE: ALWAYS keep a rule declared even if you don't use rules (e.g leave at least one example) */
static const Rule rules[] = {
	/* app_id             title       tags mask     isfloating   isterm   noswallow   monitor */
	/* examples: */
	{ "foot",             NULL,       0,            0,           1,       1,          -1 },
	{ "Gimp_EXAMPLE",     NULL,       0,            1,           0,       0,          -1 }, /* Start on currently visible tags floating, not tiled */
	{ "firefox_EXAMPLE",  NULL,       1 << 8,       0,           0,       0,          -1 }, /* Start on ONLY tag "9" */
};

/* layout(s) */
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* monitors */
/* (x=-1, y=-1) is reserved as an "autoconfigure" monitor position indicator
 * WARNING: negative values other than (-1, -1) cause problems with Xwayland clients
 * https://gitlab.freedesktop.org/xorg/xserver/-/issues/899
*/
/* NOTE: ALWAYS add a fallback rule, even if you are completely sure it won't be used */
static const MonitorRule monrules[] = {
	/* name       mfact  nmaster scale layout       rotate/reflect                x    y */
	/* example of a HiDPI laptop monitor:
	{ "eDP-1",    0.5f,  1,      2,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL,   -1,  -1 },
	*/
	/* defaults */
	{ NULL,       0.55f, 1,      1,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL,   -1,  -1 },
};

/* keyboard */
static const struct xkb_rule_names xkb_rules = {
	/* can specify fields: rules, model, layout, variant, options */
	/* example:
	.options = "ctrl:nocaps",
	*/
	.layout = "de",
};

static const int repeat_rate = 30;
static const int repeat_delay = 190;

/* Trackpad */
static const int tap_to_click = 1;
static const int tap_and_drag = 1;
static const int drag_lock = 1;
static const int natural_scrolling = 1;
static const int disable_while_typing = 1;
static const int left_handed = 0;
static const int middle_button_emulation = 0;
/* You can choose between:
LIBINPUT_CONFIG_SCROLL_NO_SCROLL
LIBINPUT_CONFIG_SCROLL_2FG
LIBINPUT_CONFIG_SCROLL_EDGE
LIBINPUT_CONFIG_SCROLL_ON_BUTTON_DOWN
*/
static const enum libinput_config_scroll_method scroll_method = LIBINPUT_CONFIG_SCROLL_2FG;

/* You can choose between:
LIBINPUT_CONFIG_CLICK_METHOD_NONE
LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS
LIBINPUT_CONFIG_CLICK_METHOD_CLICKFINGER
*/
static const enum libinput_config_click_method click_method = LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS;

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
static const enum libinput_config_accel_profile accel_profile = LIBINPUT_CONFIG_ACCEL_PROFILE_ADAPTIVE;
static const double accel_speed = 0.0;

/* You can choose between:
LIBINPUT_CONFIG_TAP_MAP_LRM -- 1/2/3 finger tap maps to left/right/middle
LIBINPUT_CONFIG_TAP_MAP_LMR -- 1/2/3 finger tap maps to left/middle/right
*/
static const enum libinput_config_tap_button_map button_map = LIBINPUT_CONFIG_TAP_MAP_LRM;

/* If you want to use the windows key for MODKEY, use WLR_MODIFIER_LOGO */
#define MODKEY WLR_MODIFIER_LOGO

#define TAGKEYS(KEY,SKEY,TAG) \
	{ MODKEY,                    KEY,            view,            {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_CTRL,  KEY,            toggleview,      {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_SHIFT, SKEY,           tag,             {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_CTRL|WLR_MODIFIER_SHIFT,SKEY,toggletag, {.ui = 1 << TAG} }

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/zsh", "-c", cmd, NULL } }


/* commands */
static const char *screenshotcmd[] = { "sh", "-c", "slurp | grim -g - $(date +'screen_%Y-%m-%d-%H%M%S.png')", NULL };

static const Key keys[] = {
	/* Note that Shift changes certain key codes: c -> C, 2 -> at, etc. */
	/* modifier                  key                 function        argument */
	{ 0, XKB_KEY_XF86AudioMute,                      spawn,          SHCMD("pamixer -t") },
	{ 0, XKB_KEY_XF86AudioMicMute,                   spawn,          SHCMD("pamixer --default-source -t") },
	{ 0, XKB_KEY_XF86AudioRaiseVolume,               spawn,          SHCMD("pamixer -i 5 && pkill -USR1 slstatus") },
	{ 0, XKB_KEY_XF86AudioLowerVolume,               spawn,          SHCMD("pamixer -d 5 && pkill -USR1 slstatus") },
	{ 0, XKB_KEY_XF86MonBrightnessUp,                spawn,          SHCMD("brightnessctl set 5%+") },
	{ 0, XKB_KEY_XF86MonBrightnessDown,              spawn,          SHCMD("brightnessctl set 5%-") },
	{ MODKEY,                    XKB_KEY_d,          spawn,          SHCMD("bemenu-run") },
	{ MODKEY,                    XKB_KEY_n,          spawn,          SHCMD("emacsclient -a '' --create-frame --no-wait")},
	{ MODKEY,		     XKB_KEY_Return,     spawn,          SHCMD("footclient") },
	{ MODKEY,		     XKB_KEY_b,          spawn,          SHCMD("qutebrowser") },
	{ MODKEY, 	             XKB_KEY_r,          spawn,          SHCMD("footclient lf") },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_B,          spawn,          SHCMD("qutebrowser --target private-window") },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_P,          spawn,          {.v = screenshotcmd} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_Q,          spawn,          SHCMD("swaylock -f -c 000000") },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_W,          spawn,          SHCMD("footclient nmtui") },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_M,          spawn,          SHCMD("pamixer --default-source -t") },
	{ MODKEY,                    XKB_KEY_m,          spawn,          SHCMD("footclient ncmpcpp") },
	{ MODKEY,                    XKB_KEY_a,          toggleswallow,  {0} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_A,          toggleautoswallow,{0} },
	{ MODKEY|WLR_MODIFIER_CTRL,  XKB_KEY_b,          togglebar,      {0} },
	{ MODKEY,                    XKB_KEY_g,          togglegaps,     {0} },
	{ MODKEY,                    XKB_KEY_j,          focusstack,     {.i = +1} },
	{ MODKEY,                    XKB_KEY_k,          focusstack,     {.i = -1} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_J,          movestack,      {.i = +1} },
 	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_K,          movestack,      {.i = -1} },
	{ MODKEY,                    XKB_KEY_w,          incnmaster,     {.i = +1} },
	{ MODKEY,                    XKB_KEY_s,          incnmaster,     {.i = -1} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_A,          setmfact,       {.f = -0.05f} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_D,          setmfact,       {.f = +0.05f} },
	{ MODKEY,                    XKB_KEY_h,          setmfact,       {.f = -0.05} },
	{ MODKEY,                    XKB_KEY_l,          setmfact,       {.f = +0.05} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_Return,     zoom,           {0} },
	{ MODKEY,                    XKB_KEY_Tab,        view,           {0} },
	{ MODKEY,                    XKB_KEY_q,          killclient,    {0} },
	{ MODKEY,                    XKB_KEY_t,          setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                    XKB_KEY_f,          setlayout,      {.v = &layouts[1]} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_M,          setlayout,      {.v = &layouts[2]} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_F,          togglefloating, {0} },
	{ MODKEY,                    XKB_KEY_e,          togglefullscreen, {0} },
	{ MODKEY,                    XKB_KEY_0,          view,           {.ui = ~0} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_parenright, tag,            {.ui = ~0} },
	{ MODKEY,                    XKB_KEY_comma,      focusmon,       {.i = WLR_DIRECTION_LEFT} },
	{ MODKEY,                    XKB_KEY_period,     focusmon,       {.i = WLR_DIRECTION_RIGHT} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_less,       tagmon,         {.i = WLR_DIRECTION_LEFT} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_greater,    tagmon,         {.i = WLR_DIRECTION_RIGHT} },
	TAGKEYS(          XKB_KEY_1, XKB_KEY_exclam,                     0),
	TAGKEYS(          XKB_KEY_2, XKB_KEY_quotedbl,                   1),
	TAGKEYS(          XKB_KEY_3, XKB_KEY_section,                    2),
	TAGKEYS(          XKB_KEY_4, XKB_KEY_dollar,                     3),
	TAGKEYS(          XKB_KEY_5, XKB_KEY_percent,                    4),
	TAGKEYS(          XKB_KEY_6, XKB_KEY_ampersand,                  5),
	TAGKEYS(          XKB_KEY_7, XKB_KEY_slash,                      6),
	TAGKEYS(          XKB_KEY_8, XKB_KEY_parenleft,                  7),
	TAGKEYS(          XKB_KEY_9, XKB_KEY_asciicircum,                8),
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_C,          quit,           {0} },

	/* Ctrl-Alt-Backspace and Ctrl-Alt-Fx used to be handled by X server */
	{ WLR_MODIFIER_CTRL|WLR_MODIFIER_ALT,XKB_KEY_Terminate_Server, quit, {0} },
	/* Ctrl-Alt-Fx is used to switch to another VT, if you don't know what a VT is
	 * do not remove them.
	 */
#define CHVT(n) { WLR_MODIFIER_CTRL|WLR_MODIFIER_ALT,XKB_KEY_XF86Switch_VT_##n, chvt, {.ui = (n)} }
	CHVT(1), CHVT(2), CHVT(3), CHVT(4), CHVT(5), CHVT(6),
	CHVT(7), CHVT(8), CHVT(9), CHVT(10), CHVT(11), CHVT(12),
};

static const Button buttons[] = {
	{ ClkLtSymbol, 0,      BTN_LEFT,   setlayout,      {.v = &layouts[0]} },
	{ ClkLtSymbol, 0,      BTN_RIGHT,  setlayout,      {.v = &layouts[2]} },
	{ ClkTitle,    0,      BTN_MIDDLE, zoom,           {0} },
	{ ClkClient,   MODKEY, BTN_LEFT,   moveresize,     {.ui = CurMove} },
	{ ClkClient,   MODKEY, BTN_MIDDLE, togglefloating, {0} },
	{ ClkClient,   MODKEY, BTN_RIGHT,  moveresize,     {.ui = CurResize} },
	{ ClkTagBar,   0,      BTN_LEFT,   view,           {0} },
	{ ClkTagBar,   0,      BTN_RIGHT,  toggleview,     {0} },
	{ ClkTagBar,   MODKEY, BTN_LEFT,   tag,            {0} },
	{ ClkTagBar,   MODKEY, BTN_RIGHT,  toggletag,      {0} },
};
