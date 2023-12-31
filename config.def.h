/* See LICENSE file for copyright and license details. */

/* Including extra header files */
#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 5;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "", "", "", "", "", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *dmenucmd[] = { "dmenu_run", "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "kitty", NULL };
static const char *rofi[] = { "rofi","-show", "drun", NULL };
static const char *dolphin[] = { "dolphin", NULL};
static const char *browser[] = { "firefox", NULL};

/* Volume Controls */
static const char *inc_vol[] = { "pulsemixer", "--change-volume", "+1", "--max-volume", "100", NULL };
static const char *dec_vol[] = { "pulsemixer", "--change-volume", "-1", NULL };
static const char *mute_vol[] = { "pulsemixer", "--toggle-mute", NULL };

/* Brigtness Controls */
static const char *inc_br[] = { "backlight_control", "+5", NULL };
static const char *dec_br[] = { "backlight_control", "-5", NULL };

/* Playback Controls */
static const char *play_pause[] = { "playerctl", "play-pause", NULL };
static const char *prev[] = { "playerctl", "previous", NULL };
static const char *next[] = { "playerctl", "next", NULL };
static const char *stop[] = { "playerctl", "stop", NULL };

/* Screenshot function */
const char scr_shot[] = "var=~/pix/$(date '+%d%m%y%H%M%S').png; maim -s -u -m 10 $var; if [[ -f $var ]]; then cat $var | xclip -selection clipboard -t image/png; notify-send 'Screenshot captured' -t 3000 -i \"$var\"; fi;";

/* Emoji Selector Function*/
static const char *emoji[] = { "rofi", "-modi", "emoji", "-show", "emoji", "-emoji-mode", "menu", NULL };

/* Lock screen function*/
static const char *lock[] = { "betterlockscreen", "-l", NULL};

static const Key keys[] = {
	/* modifier                     key        function        argument */
    { MODKEY,                       XK_l,      spawn,          {.v = lock} },
    /*Emoji Selector bind*/
    { MODKEY,                       XK_semicolon, spawn,       {.v = emoji} },
    
    /* Screenshot key bind*/
    { 0,                            XK_Print,  spawn,          SHCMD(scr_shot) },
    /* Volume Controlkeys keybinds */
    { 0,                            XF86XK_AudioLowerVolume, spawn, {.v = dec_vol} },
    { 0,                            XF86XK_AudioRaiseVolume, spawn, {.v = inc_vol} },
    { 0,                            XF86XK_AudioMute, spawn,   {.v = mute_vol} },
    
    /* Brightness Control keybinds */
    { 0,                            XF86XK_MonBrightnessUp, spawn, {.v = inc_br} },
    { 0,                            XF86XK_MonBrightnessDown, spawn, {.v = dec_br} },
    
    /* Playback Control keybinds */
    { MODKEY,                       XF86XK_AudioRaiseVolume, spawn, {.v = next} }, /*Laptop*/
    { MODKEY,                       XF86XK_AudioLowerVolume, spawn, {.v = prev} }, /*Laptop*/
    { 0,                            XF86XK_AudioNext, spawn,   {.v = next} },
    { 0,                            XF86XK_AudioPrev, spawn,   {.v = prev} },
    { 0,                            XF86XK_AudioStop, spawn,   {.v = stop} },
    { 0,                            XF86XK_AudioPlay, spawn,   {.v = play_pause} },

    { MODKEY,                       XK_b,      spawn,          {.v = browser} },
    { MODKEY,                       XK_e,      spawn,          {.v = dolphin} },
    { Mod1Mask,                     XK_space,  spawn,          {.v = rofi } },
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_q,      spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_comma,      setmfact,       {.f = -0.01} },
	{ MODKEY,                       XK_period,      setmfact,       {.f = +0.01} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_m,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

