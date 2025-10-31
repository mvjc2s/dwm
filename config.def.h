/* See LICENSE file for copyright and license details. */

#include<X11/XF86keysym.h>

/* Constants */
#define TERMINAL "st"
#define TERMCLASS "st-256color"
#define BROWSER "qutebrowser"

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
  &((Keychord){1, {{MODKEY, KEY}},                          view,           {.ui = 1 << TAG} }), \
  &((Keychord){1, {{MODKEY|ControlMask, KEY}},              toggleview,     {.ui = 1 << TAG} }), \
  &((Keychord){1, {{MODKEY|ShiftMask, KEY}},                tag,            {.ui = 1 << TAG} }), \
  &((Keychord){1, {{MODKEY|ControlMask|ShiftMask, KEY}},    toggletag,      {.ui = 1 << TAG} }),
#define STACKKEYS(MOD,ACTION) \
	&((Keychord){1, {{MOD, XK_j}},     ACTION##stack, {.i = INC(+1) } }), \
	&((Keychord){1, {{MOD, XK_k}},     ACTION##stack, {.i = INC(-1) } }), \
	&((Keychord){1, {{MOD, XK_grave}}, ACTION##stack, {.i = PREVSEL } }), \
	&((Keychord){1, {{MOD, XK_q}},     ACTION##stack, {.i = 0 } }), \
  &((Keychord){1, {{MOD, XK_a}},     ACTION##stack, {.i = 1 } }), \
  &((Keychord){1, {{MOD, XK_z}},     ACTION##stack, {.i = 2 } }), \
  &((Keychord){1, {{MOD, XK_x}},     ACTION##stack, {.i = -1 } }),

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const unsigned int gappih    = 20;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 30;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = {
		"Iosevka Nerd Font:size=12",
		"Hack Nerd Font:size=12",
		"FiraCode Nerd Font:size=12",
		"Noto Sans:size=11",
		"Noto Color Emoji:pixelsize=12:antialias=true:autohint=true"
};
static const char dmenufont[]       = "Iosevka Nerd Font:size=12";
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
static const XPoint stickyicon[]    = { {0,0}, {4,0}, {4,8}, {2,6}, {0,8}, {0,0} }; /* represents the icon as an array of vertices */
static const XPoint stickyiconbb    = {4,8};	/* defines the bottom right corner of the polygon's bounding box (speeds up scaling) */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

/* tagging */
static const char *tags[] = {
  "1:🔍", /* information gathering / identification */
  "2:🎯", /* exploration */
  "3:💻", /* post-exploration (C2, artifacts, evidences) */
  "4:📝", /* report writing and review */
  "5:👨‍💻", /* coding */
  "6:📁", /* others / miscellaneous */
  "7:🛠️", /* system administration */
  "8:🛡️", /* defense stuffs */
  "9:🌐"  /* web browsing */
};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",    NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ BROWSER,   NULL,     NULL,           1 << 8,    0,          0,          -1,        -1 },
	{ TERMCLASS, NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ NULL,      NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static int       attachbelow = 1;    /* 1 means attach after the currently active window */
static const int lockfullscreen = 0; /* 1 will force focus on the fullscreen window */
static const int refreshrate = 120;  /* refresh rate (per second) for client move/resize */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },                          /* layout[0]: tile */
	{ "><>",      NULL },                          /* layout[1]: no layout function = floating behavior */
	{ "[M]",      monocle },                       /* layout[2]: monocle */
	{ "TTT",      bstack },                        /* layout[3]: bottom stack */
	{ "===",      bstackhoriz },                   /* layout[4]: bottom stack horizontal */
	{ "[@]",      spiral },                        /* layout[5]: spiral */
	{ "[\\]",     dwindle },                       /* layout[6]: dwindle */
	{ "H[]",      deck },                          /* layout[7]: deck */
	{ "HHH",      grid },                          /* layout[8]: grid */
	{ "###",      nrowgrid },                      /* layout[9]: n + 1 row grid */
	{ ":::",      gaplessgrid },                   /* layout[10]: gapless grid */
	{ "---",      horizgrid },                     /* layout[11]: horizontal grid */
	{ "|M|",      centeredmaster },                /* layout[12]: centered master */
	{ ">M>",      centeredfloatingmaster },        /* layout[13]: centered floating master */
	{ NULL,       NULL },
};

/* key definitions for calling commands in dwm */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
#define GTKCMD(cmd) { .v = (const char*[]){ "/usr/bin/gtk-launch", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { TERMINAL, NULL };
static const char *tabtermcmd[]  = { "tabbed", "-r", "2", TERMINAL, "-w", "''", NULL };
static const char *flameshotcmd[] = { "flameshot", "gui", NULL };
static const char *layoutmenu_cmd = "layoutmenu.sh";

static const Arg tagexec[] = {
	{ .v = termcmd },
	{ .v = termcmd },
	{ .v = termcmd },
	{ .v = termcmd },
	{ .v = termcmd },
	{ .v = termcmd },
	{ .v = termcmd },
	{ .v = termcmd },
	{ .v = termcmd }
};

static const Keychord *keychords[] = {
	/* modifier     key                                                            function            argument */

  /* spawn keybindings */
  &((Keychord){1, {{MODKEY|ShiftMask, XK_Return}},                               spawn,              {.v = dmenucmd } }),
  &((Keychord){1, {{MODKEY, XK_Return}},                                         spawn,              {.v = termcmd } }),
  &((Keychord){1, {{Mod1Mask, XK_Return}},                                       spawn,              {.v = tabtermcmd } }),
  &((Keychord){1, {{0, XK_Print}},                                               spawn,              {.v = flameshotcmd } }),

  /* dwm control keybindings */
  &((Keychord){2, {{MODKEY, XK_c}, {0, XK_BackSpace}},                           killclient,         {0} }),
  &((Keychord){2, {{MODKEY, XK_c}, {ShiftMask, XK_BackSpace}},                   killclient,         {.ui = 1 } }), /* kill all unselected windows */
  &((Keychord){2, {{MODKEY, XK_c}, {ControlMask|ShiftMask, XK_BackSpace}},       killclient,         {.ui = 2 } }), /* kill all windows */
  &((Keychord){2, {{MODKEY, XK_c}, {0, XK_q}},                                   quit,               {0} }),        /* quit dwm */
  &((Keychord){2, {{MODKEY, XK_c}, {ShiftMask, XK_q}},                           quit,               {1} }),        /* restart dwm */
  &((Keychord){2, {{MODKEY, XK_c}, {0, XK_b}},                                   togglebar,          {0} }),
  &((Keychord){2, {{MODKEY, XK_c}, {0, XK_s}},                                   togglesticky,       {0} }),
  &((Keychord){2, {{MODKEY, XK_c}, {0, XK_a}},                                   toggleAttachBelow,  {0} }),
  &((Keychord){2, {{MODKEY, XK_c}, {0, XK_f}},                                   togglefullscreen,   {0} }),

  /* multi-monitor control keybindings */
  &((Keychord){1, {{MODKEY, XK_m}, {0, XK_f}},                                   focusmon,           {.i = +1 } }),
  &((Keychord){1, {{MODKEY, XK_m}, {ShiftMask, XK_f}},                           focusmon,           {.i = -1 } }),
  &((Keychord){1, {{MODKEY, XK_m}, {0, XK_t}},                                   tagmon,             {.i = +1 } }),
  &((Keychord){1, {{MODKEY, XK_m}, {ShiftMask, XK_t}},                           tagmon,             {.i = -1 } }),
  &((Keychord){1, {{MODKEY, XK_m}, {XK_s}},                                      swapmon,            {0} }),

  /* stack and gaps control keybindings */
  STACKKEYS(MODKEY,                                                              focus)
  STACKKEYS(MODKEY|ShiftMask,                                                    push)
  &((Keychord){1, {{MODKEY, XK_i}},                                              incnmaster,         {.i = +1 } }),
  &((Keychord){1, {{MODKEY, XK_d}},                                              incnmaster,         {.i = -1 } }),
  &((Keychord){1, {{MODKEY, XK_h}},                                              setmfact,           {.f = -0.05} }),
  &((Keychord){1, {{MODKEY, XK_l}},                                              setmfact,           {.f = +0.05} }),
  &((Keychord){2, {{MODKEY, XK_s}, {0, XK_f}},                                   focusmaster,        {0} }),
  &((Keychord){2, {{MODKEY, XK_s}, {0, XK_u}},                                   incrgaps,           {.i = +1 } }),
  &((Keychord){2, {{MODKEY, XK_s}, {ShiftMask, XK_u}},                           incrgaps,           {.i = -1 } }),
  &((Keychord){2, {{MODKEY, XK_s}, {0, XK_i}},                                   incrigaps,          {.i = +1 } }),
  &((Keychord){2, {{MODKEY, XK_s}, {ShiftMask, XK_i}},                           incrigaps,          {.i = -1 } }),
  &((Keychord){2, {{MODKEY, XK_s}, {0, XK_o}},                                   incrogaps,          {.i = +1 } }),
  &((Keychord){2, {{MODKEY, XK_s}, {ShiftMask, XK_o}},                           incrogaps,          {.i = -1 } }),
  &((Keychord){2, {{MODKEY|ShiftMask, XK_s}, {0, XK_i}},                         incrihgaps,         {.i = +1 } }),
  &((Keychord){2, {{MODKEY|ShiftMask, XK_s}, {ShiftMask, XK_i}},                 incrihgaps,         {.i = -1 } }),
  &((Keychord){2, {{MODKEY|ShiftMask, XK_s}, {0, XK_v}},                         incrivgaps,         {.i = +1 } }),
  &((Keychord){2, {{MODKEY|ShiftMask, XK_s}, {ShiftMask, XK_v}},                 incrivgaps,         {.i = -1 } }),
  &((Keychord){2, {{MODKEY|ShiftMask, XK_s}, {0, XK_h}},                         incrohgaps,         {.i = +1 } }),
  &((Keychord){2, {{MODKEY|ShiftMask, XK_s}, {ShiftMask, XK_h}},                 incrohgaps,         {.i = -1 } }),
  &((Keychord){2, {{MODKEY|ShiftMask, XK_s}, {0, XK_o}},                         incrovgaps,         {.i = +1 } }),
  &((Keychord){2, {{MODKEY|ShiftMask, XK_s}, {ShiftMask, XK_o}},                 incrovgaps,         {.i = -1 } }),
  &((Keychord){2, {{MODKEY, XK_s}, {0, XK_g}},                                   togglegaps,         {0} }),
  &((Keychord){2, {{MODKEY, XK_s}, {0, XK_d}},                                   defaultgaps,        {0} }),

  /* layouts keybinds */
  &((Keychord){2, {{MODKEY, XK_l}, {0, XK_t}},                                   setlayout,          {.v = &layouts[0] } }),      /* layout[0]: tile */
  &((Keychord){2, {{MODKEY, XK_l}, {0, XK_f}},                                   setlayout,          {.v = &layouts[1] } }),      /* layout[1]: no layout function = floating behavior */
  &((Keychord){2, {{MODKEY, XK_l}, {0, XK_m}},                                   setlayout,          {.v = &layouts[2] } }),      /* layout[2]: monocle */
  &((Keychord){2, {{MODKEY, XK_l}, {0, XK_b}},                                   setlayout,          {.v = &layouts[3] } }),      /* layout[3]: bottom stack */
  &((Keychord){2, {{MODKEY, XK_l}, {0, XK_b}},                                   setlayout,          {.v = &layouts[4] } }),      /* layout[4]: bottom stack horizontal */
  &((Keychord){2, {{MODKEY, XK_l}, {0, XK_s}},                                   setlayout,          {.v = &layouts[5] } }),      /* layout[5]: spiral */
  &((Keychord){2, {{MODKEY, XK_l}, {0, XK_d}},                                   setlayout,          {.v = &layouts[6] } }),      /* layout[6]: dwindle */
  &((Keychord){2, {{MODKEY, XK_l}, {ShiftMask, XK_d}},                           setlayout,          {.v = &layouts[7] } }),      /* layout[7]: deck */
  &((Keychord){2, {{MODKEY, XK_l}, {0, XK_g}},                                   setlayout,          {.v = &layouts[8] } }),      /* layout[8]: grid */
  &((Keychord){2, {{MODKEY, XK_l}, {ShiftMask, XK_g}},                           setlayout,          {.v = &layouts[9] } }),      /* layout[9]: n + 1 row grid */
  &((Keychord){2, {{MODKEY, XK_l}, {ControlMask, XK_g}},                         setlayout,          {.v = &layouts[10] } }),     /* layout[10]: gapless grid */
  &((Keychord){2, {{MODKEY, XK_l}, {0, XK_h}},                                   setlayout,          {.v = &layouts[11] } }),     /* layout[11]: horizontal grid */
  &((Keychord){2, {{MODKEY, XK_l}, {0, XK_c}},                                   setlayout,          {.v = &layouts[12] } }),     /* layout[12]: centered master */
  &((Keychord){2, {{MODKEY, XK_l}, {ShiftMask, XK_c}},                           setlayout,          {.v = &layouts[13] } }),     /* layout[13]: centered floating master */
  &((Keychord){2, {{MODKEY, XK_l}, {0, XK_space}},                               setlayout,          {0} }),                      /* back to tile layout */
  &((Keychord){2, {{MODKEY, XK_l}, {0, XK_period}},                              cyclelayout,        {.i = +1 } }),
  &((Keychord){2, {{MODKEY, XK_l}, {0, XK_comma}},                               cyclelayout,        {.i = -1 } }),
  &((Keychord){2, {{MODKEY, XK_l}, {0, XK_space}},                               togglefloating,     {0} }),

  /* X11 Keybindings */
  &((Keychord){1, {{0, XF86XK_AudioMute}},                                       spawn,              SHCMD("wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle; kill -44 $(pidof dwmblocks)") }),
  &((Keychord){1, {{0, XF86XK_AudioRaiseVolume}},                                spawn,              SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 0%- && wpctl set-volume @DEFAULT_AUDIO_SINK@ 3%+; kill -44 $(pidof dwmblocks)") }),
  &((Keychord){1, {{0, XF86XK_AudioLowerVolume}},                                spawn,              SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 0%+ && wpctl set-volume @DEFAULT_AUDIO_SINK@ 3%-; kill -44 $(pidof dwmblocks)") }),
  &((Keychord){1, {{0, XF86XK_AudioPrev}},                                       spawn,              {.v = (const char*[]){ "mpc", "prev", NULL } } }),
  &((Keychord){1, {{0, XF86XK_AudioNext}},                                       spawn,              {.v = (const char*[]){ "mpc",  "next", NULL } } }),
  &((Keychord){1, {{0, XF86XK_AudioPause}},                                      spawn,              {.v = (const char*[]){ "mpc", "pause", NULL } } }),
  &((Keychord){1, {{0, XF86XK_AudioPlay}},                                       spawn,              {.v = (const char*[]){ "mpc", "play", NULL } } }),
  &((Keychord){1, {{0, XF86XK_AudioStop}},                                       spawn,              {.v = (const char*[]){ "mpc", "stop", NULL } } }),
  &((Keychord){1, {{0, XF86XK_AudioRewind}},                                     spawn,              {.v = (const char*[]){ "mpc", "seek", "-10", NULL } } }),
  &((Keychord){1, {{0, XF86XK_AudioForward}},                                    spawn,              {.v = (const char*[]){ "mpc", "seek", "+10", NULL } } }),
  &((Keychord){1, {{0, XF86XK_AudioMedia}},                                      spawn,              {.v = (const char*[]){ TERMINAL, "-e", "ncmpcpp", NULL } } }),
  &((Keychord){1, {{0, XF86XK_AudioMicMute}},                                    spawn,              SHCMD("pactl set-source-mute @DEFAULT_SOURCE@ toggle") }),
  &((Keychord){1, {{0, XF86XK_MonBrightnessUp}},                                 spawn,              {.v = (const char*[]){ "brightnessctl", "set", "+10%", NULL } } }),
  &((Keychord){1, {{0, XF86XK_MonBrightnessDown}},                               spawn,              {.v = (const char*[]){ "brightnessctl", "set", "10%-", NULL } } }),

  /* tags control keybindings */
  &((Keychord){1, {{MODKEY, XK_Tab}},                                            view,               {0} }),
  &((Keychord){1, {{MODKEY, XK_0}},                                              view,               {.ui = ~0 } }),
  &((Keychord){1, {{MODKEY|ShiftMask, XK_0}},                                    tag,                {.ui = ~0 } }),

  /* tags keybindings */
	TAGKEYS(XK_1,                                                                  0)
	TAGKEYS(XK_2,                                                                  1)
	TAGKEYS(XK_3,                                                                  2)
	TAGKEYS(XK_4,                                                                  3)
	TAGKEYS(XK_5,                                                                  4)
	TAGKEYS(XK_6,                                                                  5)
	TAGKEYS(XK_7,                                                                  6)
	TAGKEYS(XK_8,                                                                  7)
	TAGKEYS(XK_9,                                                                  8)
};

/* click and button definitions */
/* click can be
   ClkTagBar = tags areas,
   ClkLtSymbol = symbol layout area (from the left of the bar), 
   ClkStatusText = text status area (from the right of the bar), 
   ClkWinTitle = (active window title in the bar), 
   ClkClientWin = client window itself, or
   ClkRootWin = window root. */
/* button can be
   Button1 = left click,
   Button2 = middle click,
   Button3 = right click,
   Button4 = Scroll up,
   Button5 = Scroll down. */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkLtSymbol,          0,              Button3,        layoutmenu,     {0} },
	{ ClkLtSymbol,          0,              Button4,        cyclelayout,    {.i = +1 } },
	{ ClkLtSymbol,          0,              Button5,        cyclelayout,    {.i = -1 } },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkTagBar,            0,              Button2,        spawntag,       {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
};

