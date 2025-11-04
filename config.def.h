/* See LICENSE file for copyright and license details. */

// XF86 Key symbols definition for X11 keybindings
#include<X11/XF86keysym.h>

/* Program standard and class constants */
// Suckless programs
#define TERM         "st"                       // Terminal
#define TERMCLASS    "st-256color"              // Terminal class
#define FTERMI       "floatterm"                // Float terminal instance
#define TABTERM      "tabbed"                   // Tabbing
#define LSCR         "slock"                    // Lock screen
#define SYSMENU      "dmenu_run"                // System menu
#define LAYOUTMENU   "layoutmenu.sh"            // Layout menu
// Common usable programs
#define BROWSER      "qutebrowser"              // Browser
#define PRTSCR       "flameshot"                // Screenshot
#define EAPP         "nvim"                     // Text editor
#define EAPPI        "editor"                   // Text editor instance
#define CAPP         "lazyvim"                  // Coding
#define CAPPI        "coding"                   // Coding instance
#define NAPP         "logseq"                   // Notes
#define NAPPCLASS    "Logseq"                   // Notes class
#define PAPP         "gimp"                     // Photoshop
#define PAPPCLASS    "Gimp"                     // Photoshop class
// Network programs
#define WS           "wireshark"                // Network analysis
#define WSCLASS      "Wireshark"                // Network analysis class
// Sound and media control programs
#define SNDCTL       "wpctl"                    // Sound control
#define MPCTL        "mpc"                      // Media player command control
#define MPM          "ncmpcpp"                  // Media player manager
#define MPMI         "music"                    // Media player instance
#define PA           "pactl"                    // Pulseaudio control
// Brightness and system control programs
#define BCTL         "brightnessctl"            // Brightness control
#define PCTL         "htop"                     // Process control
#define PCTLI        "process"                  // Process control instance

// MODKEY, TAGKEYS and STACKKEYS definitions
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

// Appearance variables
static const unsigned int borderpx      = 1;        // border pixel of windows
static const unsigned int snap          = 32;       // snap pixel
static const unsigned int gappih        = 20;       // horiz inner gap between windows
static const unsigned int gappiv        = 10;       // vert inner gap between windows
static const unsigned int gappoh        = 10;       // horiz outer gap between windows and screen edge
static const unsigned int gappov        = 30;       // vert outer gap between windows and screen edge
static const unsigned int ulinepad      = 5;        // horizontal padding between the underline and tag
static const unsigned int ulinestroke   = 2;        // thickness / height of the underline
static const unsigned int ulinevoffset  = 0;        // how far above the bottom of the bar the line should appear
static const int ulineall               = 0;        // 1 to show underline on all tags, 0 for just the active ones
static const int swallowfloating        = 0;        // 1 means swallow floating windows by default
static const int nmaster                = 1;        // number of clients in master area
static const int resizehints            = 1;        // 1 means respect size hints in tiled resizals
static const int showbar                = 1;        // 0 means no bar
static const int topbar                 = 1;        // 0 means bottom bar
static const int sidepad                = 10;       // horizontal padding of bar
static const int vertpad                = 10;       // vertical padding of bar
static const int horizpadbar            = 1;        // horizontal padding for statusbar
static const int vertpadbar             = 0;        // vertical padding for statusbar
static const int lockfullscreen         = 0;        // 1 will force focus on the fullscreen window
static const int refreshrate            = 120;      // refresh rate (per second) for client move/resize
static       int attachbelow            = 1;        // 1 means attach after the currently active window
static       int smartgaps              = 0;        // 1 means no outer gap when there is only one window
static const float mfact                = 0.55;     // factor of master area size [0.05..0.95]
static const XPoint stickyicon[]        = { {0,0}, {4,0}, {4,8}, {2,6}, {0,8}, {0,0} }; // represents the icon as an array of vertices
static const XPoint stickyiconbb        = {4,8};    // defines the bottom right corner of the polygon's bounding box (speeds up scaling)

// Colors variables
static char normbgcolor[]     = "#222222";
static char normbordercolor[] = "#444444";
static char normfgcolor[]     = "#bbbbbb";
static char selfgcolor[]      = "#eeeeee";
static char selbordercolor[]  = "#005577";
static char selbgcolor[]      = "#005577";
static char *colors[][3] = {
  /*               fg           bg           border   */
  [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
  [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
}; 

// Xrdb colors
static char termcol0[]   = "#000000"; /* black   */
static char termcol1[]   = "#ff0000"; /* red     */
static char termcol2[]   = "#33ff00"; /* green   */
static char termcol3[]   = "#ff0099"; /* yellow  */
static char termcol4[]   = "#0066ff"; /* blue    */
static char termcol5[]   = "#cc00ff"; /* magenta */
static char termcol6[]   = "#00ffff"; /* cyan    */
static char termcol7[]   = "#d0d0d0"; /* white   */
static char termcol8[]   = "#808080"; /* black   */
static char termcol9[]   = "#ff0000"; /* red     */
static char termcol10[]  = "#33ff00"; /* green   */
static char termcol11[]  = "#ff0099"; /* yellow  */
static char termcol12[]  = "#0066ff"; /* blue    */
static char termcol13[]  = "#cc00ff"; /* magenta */
static char termcol14[]  = "#00ffff"; /* cyan    */
static char termcol15[]  = "#ffffff"; /* white   */
static char *termcolor[] = {
  termcol0,
  termcol1,
  termcol2,
  termcol3,
  termcol4,
  termcol5,
  termcol6,
  termcol7,
  termcol8,
  termcol9,
  termcol10,
  termcol11,
  termcol12,
  termcol13,
  termcol14,
  termcol15,
};

// Font variables
static const char *fonts[] = {
	"FiraCode Nerd Font:size=12",
  "JetBrains Mono:size=12:antialias=true:autohint=true",
	"Iosevka Nerd Font:size=12",
	"Hack Nerd Font:size=12",
	"Noto Sans:size=12",
	"Noto Color Emoji:pixelsize=12:antialias=true:autohint=true",
};
static const char dmenufont[] = "FiraCode Nerd Font:size=12:antialias=true:autohint=true";
 
 // Vanity gaps definitions
 #define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
 #define ICONSIZE 16   /* icon size */
 #define ICONSPACING 5 /* space between icon and title */
 #include "vanitygaps.c"
 
// Tagging
static const char *tags[] = {
  "1:🔍", /* information gathering / identification */
  "2:🎯", /* exploration */
  "3:💻", /* post-exploration (C2, artifacts, evidences) */
  "4:📝", /* notations, report writing and review */
  "5:👨‍💻", /* coding */
  "6:📁", /* others / miscellaneous */
  "7:🛠️", /* system administration */
  "8:🛡️", /* defense stuffs */
  "9:🌐"  /* web browsing */
};

// Window Manager Rules
static const Rule rules[] = {
  /* Useful table
    * Program type         isterminal    noswallow     Why?
    * Normal terminal      1             0             CAN swallow GUI's
    * Specific terminal    1             0             CAN swallow if needed
    * Browser              0             -1            CAN swallow popups/dialogs, etc
    * Normal GUI           0             0             CAN BE swallowed
    * Debug tools          0             1             NEVER swallow
    * Complex editors      0             1             NEVER swallow, some temporary windows
    * Players/visualizers  0             0             CAN BE swallowed
  */

  /* xprop(1):
    *  WM_CLASS(STRING) = instance, class
    *  WM_NAME(STRING) = title
    *  tags mask = bit mask
    *  noswallow = {
    *            0 → CAN BE swallowed by a terminal (normal behavior)
    *            1 → NEVER will be swallowed (useful for xev, debug programs like gdb, etc)
    *            -1 → CAN BE swallowed AND also CAN swallow others clients (useful for browsers)
    *            }
    *  monitor   = {
    *            -1 (any monitor selected),
    *            0 (main monitor),
    *            1 (secondary monitor),
    *            2 (tertiary monitor)
    *            ...
    *            }
  */

  /* class       instance      title             tags mask    switchtotag    isfloating    isterminal    noswallow    monitor */
  // tag 1
  // tag 2
  // tag 3

  // tag 4
  { NAPPCLASS,   NULL,         NULL,             1 << 3,      1,             0,            0,             0,          -1 },

  // tag 5
  { TERMCLASS,   CAPPI,        NULL,             1 << 4,      1,             0,            1,             0,          -1 },

  // tag 6
  { PAPPCLASS,   NULL,         NULL,             1 << 5,      1,             0,            0,             1,          -1 },
  { TERMCLASS,   MPMI,         NULL,             1 << 5,      1,             0,            1,             0,          -1 },

  // tag 7
  { WSCLASS,     NULL,         NULL,             1 << 6,      1,             0,            0,             0,          -1 },
  { TERMCLASS,   PCTLI,        NULL,             1 << 6,      1,             0,            1,             0,          -1 },

  // tag 8

  // tag 9
  { BROWSER,     NULL,         NULL,             1 << 8,      1,             0,            0,            -1,          -1 },

  // any tag
  { TERMCLASS,   NULL,         NULL,             0,           0,             0,            1,             0,          -1 },
  { TERMCLASS,   FTERMI,       NULL,             0,           0,             1,            1,             0,          -1 },

  // xev
  { NULL,        NULL,         "Event Tester",   0,           0,             0,            0,             1,          -1 },
};

// Layouts variables
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

// Dwmblocks definition
#define STATUSBAR "dwmblocks"

// Key definitions for calling commands/scripts in dwm
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
#define GTKCMD(cmd) { .v = (const char*[]){ "/usr/bin/gtk-launch", cmd, NULL } }

// Suckless command variables
static char dmenumon[2]                 = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]           = { SYSMENU, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbordercolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]            = { TERM, NULL };
static const char *floattermcmd[]       = { TERM, "-n", FTERMI, "-g", "120x34", NULL };
static const char *tabtermcmd[]         = { TABTERM, "-r", "2", TERM, "-w", "''", NULL };
static const char *lockscrcmd[]         = { LSCR, NULL };
static const char *layoutmenu_cmd       = LAYOUTMENU;

// Common usable command variables
static const char *browsercmd[]         = { BROWSER, NULL };
static const char *editorappcmd[]       = { TERM, "-n", EAPPI, "-e", EAPP, NULL };
static const char *codeappcmd[]         = { TERM, "-n", CAPPI, "-e", "sh", "-c", CAPP, NULL };
static const char *noteappcmd[]         = { NAPP, NULL };
static const char *flameshotcmd[]       = { PRTSCR, "gui", NULL };
static const char *photoshopcmd[]       = { PAPP, NULL };

// Network command variables
static const char *wiresharkcmd[]       = { WS, NULL };

// Volume and microphone control command variables
static const char *mutecmd[]            = {
  "/bin/sh", "-c",
  SNDCTL " set-mute @DEFAULT_AUDIO_SINK@ toggle ; kill -44 $(pidof dwmblocks)",
  NULL
};
static const char *raisevolcmd[]        = {
  "/bin/sh", "-c",
  SNDCTL " set-volume @DEFAULT_AUDIO_SINK@ 0%- && wpctl set-volume @DEFAULT_AUDIO_SINK@ 3%+ ; kill -44 $(pidof dwmblocks)",
  NULL
};
static const char *lowervolcmd[]        = {
  "/bin/sh", "-c",
  SNDCTL " set-volume @DEFAULT_AUDIO_SINK@ 0%+ && wpctl set-volume @DEFAULT_AUDIO_SINK@ 3%- ; kill -44 $(pidof dwmblocks)",
  NULL
};
static const char *micmutecmd[]         = { PA, "set-source-mute", "@DEFAULT_SOURCE@", "toggle", NULL };

// Media player and control command variables
static const char *mpcnextcmd[]         = { MPCTL, "next", NULL };
static const char *mpcprevcmd[]         = { MPCTL, "prev", NULL };
static const char *mpcplaycmd[]         = { MPCTL, "play", NULL };
static const char *mpcpausecmd[]        = { MPCTL, "pause", NULL };
static const char *mpcstopcmd[]         = { MPCTL, "stop", NULL };
static const char *mpcfwdcmd[]          = { MPCTL, "seek", "+10", NULL };
static const char *mpcrwdcmd[]          = { MPCTL, "seek", "-10", NULL };
static const char *sndmediacmd[]        = { TERM, "-n", MPMI, "-e", MPM, NULL };

// Brightness and system control command variables
static const char *brightnessupcmd[]    = { BCTL, "set", "+10%", NULL };
static const char *brightnessdowncmd[]  = { BCTL, "set", "10%-", NULL };
static const char *processctlcmd[]      = { TERM, "-n", PCTLI, "-e", PCTL, NULL };

// Spawntag pertag
static const Arg tagexec[] = {
	{ .v = termcmd },  // tag 1
	{ .v = termcmd },  // tag 2
	{ .v = termcmd },  // tag 3
	{ .v = termcmd },  // tag 4
	{ .v = termcmd },  // tag 5
	{ .v = termcmd },  // tag 6
	{ .v = termcmd },  // tag 7
	{ .v = termcmd },  // tag 8
	{ .v = termcmd }   // tag 9
};

// Keychord variables for keybindings
static const Keychord *keychords[] = {
	// modifier     key                                                            function            argument
  // Quick spawn keybindings
  &((Keychord){1, {{MODKEY, XK_Return}},                                         spawn,              {.v = termcmd } }),              // terminal command
  &((Keychord){1, {{MODKEY|ShiftMask, XK_Return}},                               spawn,              {.v = dmenucmd } }),             // dmenu command
  &((Keychord){1, {{Mod1Mask, XK_Return}},                                       spawn,              {.v = tabtermcmd } }),           // tabbed terminal command
  &((Keychord){1, {{0, XK_Print}},                                               spawn,              {.v = flameshotcmd } }),         // flameshot command
  &((Keychord){1, {{MODKEY, XK_b}},                                              spawn,              {.v = browsercmd } }),           // browser command
  &((Keychord){1, {{MODKEY, XK_n}},                                              spawn,              {.v = noteappcmd } }),           // note app command
  &((Keychord){2, {{MODKEY, XK_p}, {0, XK_c}},                                   spawn,              {.v = codeappcmd } }),           // coding command
  &((Keychord){2, {{MODKEY, XK_p}, {0, XK_e}},                                   spawn,              {.v = editorappcmd } }),         // coding command                                                                                                                                     // editor command
  &((Keychord){2, {{MODKEY, XK_p}, {0, XK_f}},                                   spawn,              {.v = floattermcmd } }),         // float terminal command
  &((Keychord){2, {{MODKEY, XK_p}, {0, XK_g}},                                   spawn,              {.v = photoshopcmd } }),         // photoshop command
  &((Keychord){2, {{MODKEY, XK_p}, {0, XK_m}},                                   spawn,              {.v = sndmediacmd } }),          // media|music client
  &((Keychord){2, {{MODKEY, XK_p}, {0, XK_s}},                                   spawn,              {.v = processctlcmd } }),        // process control command
  &((Keychord){2, {{MODKEY, XK_p}, {0, XK_w}},                                   spawn,              {.v = wiresharkcmd } }),         // wireshark command
  &((Keychord){2, {{MODKEY, XK_s}, {0, XK_t}},                                   spawn,              SHCMD("switch-theme") }),        // switch-theme script

  // DWM control keybindings
  &((Keychord){2, {{MODKEY, XK_c}, {0, XK_q}},                                   quit,               {0} }),                          // quit dwm
  &((Keychord){2, {{MODKEY, XK_c}, {0, XK_r}},                                   quit,               {1} }),                          // restart dwm
  &((Keychord){2, {{MODKEY, XK_c}, {0, XK_b}},                                   togglebar,          {0} }),                          // toggle dwm bar
  &((Keychord){2, {{MODKEY, XK_c}, {0, XK_F5}},                                  xrdb,               {.v = NULL } }),                 // reload xrdb
  &((Keychord){2, {{MODKEY, XK_c}, {0, XK_l}},                                   spawn,              {.v = lockscrcmd } }),           // lock screen command

  // Multi-monitor control keybindings
  &((Keychord){2, {{MODKEY, XK_f}, {0, XK_j}},                                   focusmon,           {.i = +1 } }),                   // focus next monitor
  &((Keychord){2, {{MODKEY, XK_f}, {0, XK_k}},                                   focusmon,           {.i = -1 } }),                   // focus previous monitor
  &((Keychord){2, {{MODKEY, XK_t}, {0, XK_j}},                                   tagmon,             {.i = +1 } }),                   // tag select window to the next monitor
  &((Keychord){2, {{MODKEY, XK_t}, {0, XK_k}},                                   tagmon,             {.i = -1 } }),                   // tag select window to the previous monitor
  &((Keychord){2, {{MODKEY, XK_s}, {0, XK_m}},                                   swapmon,            {0} }),                          // swap windows between monitors

  // Stack keybindings
  STACKKEYS(MODKEY,                                                              focus)                                               // focus stack function
  STACKKEYS(MODKEY|ShiftMask,                                                    push)                                                // push stack function
  &((Keychord){1, {{MODKEY, XK_i}},                                              incnmaster,         {.i = +1 } }),                   // increase numbers of master windows
  &((Keychord){1, {{MODKEY, XK_d}},                                              incnmaster,         {.i = -1 } }),                   // decrease numbers of master windows
  &((Keychord){1, {{MODKEY, XK_l}},                                              setmfact,           {.f = +0.05} }),                 // increase the maximum factor of a selected window
  &((Keychord){1, {{MODKEY, XK_h}},                                              setmfact,           {.f = -0.05} }),                 // decrease the maximum factor of a selected window
  &((Keychord){2, {{MODKEY, XK_f}, {0, XK_m}},                                   focusmaster,        {0} }),                          // focus master window
  &((Keychord){2, {{MODKEY, XK_t}, {0, XK_a}},                                   toggleAttachBelow,  {0} }),                          // toggle attachbelow stack

  // Gaps control keybindings
  &((Keychord){2, {{MODKEY, XK_g}, {0, XK_t}},                                   togglegaps,         {0} }),                          // toggle gaps
  &((Keychord){2, {{MODKEY, XK_g}, {0, XK_d}},                                   defaultgaps,        {0} }),                          // reset to the default gaps configuration
  &((Keychord){2, {{MODKEY, XK_g}, {0, XK_e}},                                   incrgaps,           {.i = +1 } }),                   // increase every gaps
  &((Keychord){2, {{MODKEY, XK_g}, {ShiftMask, XK_e}},                           incrgaps,           {.i = -1 } }),                   // decrease every gaps
  &((Keychord){2, {{MODKEY, XK_g}, {0, XK_i}},                                   incrigaps,          {.i = +1 } }),                   // increase inner gaps
  &((Keychord){2, {{MODKEY, XK_g}, {ShiftMask, XK_i}},                           incrigaps,          {.i = -1 } }),                   // decrease inner gaps
  &((Keychord){2, {{MODKEY, XK_g}, {0, XK_o}},                                   incrogaps,          {.i = +1 } }),                   // increase outer gaps
  &((Keychord){2, {{MODKEY, XK_g}, {ShiftMask, XK_o}},                           incrogaps,          {.i = -1 } }),                   // decrease outer gaps
  &((Keychord){2, {{MODKEY, XK_h}, {0, XK_i}},                                   incrihgaps,         {.i = +1 } }),                   // increase horizontal inner gaps
  &((Keychord){2, {{MODKEY, XK_h}, {ShiftMask, XK_i}},                           incrihgaps,         {.i = -1 } }),                   // decrease horizontal inner gaps
  &((Keychord){2, {{MODKEY, XK_h}, {0, XK_o}},                                   incrohgaps,         {.i = +1 } }),                   // increase horizontal outer gaps
  &((Keychord){2, {{MODKEY, XK_h}, {ShiftMask, XK_o}},                           incrohgaps,         {.i = -1 } }),                   // decrease horizontal outer gaps
  &((Keychord){2, {{MODKEY, XK_v}, {0, XK_i}},                                   incrivgaps,         {.i = +1 } }),                   // increase vertical inner gaps
  &((Keychord){2, {{MODKEY, XK_v}, {ShiftMask, XK_i}},                           incrivgaps,         {.i = -1 } }),                   // decrease vertical inner gaps
  &((Keychord){2, {{MODKEY, XK_v}, {0, XK_o}},                                   incrovgaps,         {.i = +1 } }),                   // increase vertical outer gaps
  &((Keychord){2, {{MODKEY, XK_v}, {ShiftMask, XK_o}},                           incrovgaps,         {.i = -1 } }),                   // decrease vertical outer gaps

  // Windows layouts keybindings
  &((Keychord){2, {{MODKEY, XK_w}, {0, XK_BackSpace}},                           killclient,         {0} }),                          // kill selected window
  &((Keychord){2, {{MODKEY, XK_w}, {ShiftMask, XK_BackSpace}},                   killclient,         {.ui = 1 } }),                   // kill all unselected windows
  &((Keychord){2, {{MODKEY, XK_w}, {ControlMask|ShiftMask, XK_BackSpace}},       killclient,         {.ui = 2 } }),                   // kill all windows
  &((Keychord){2, {{MODKEY, XK_w}, {0, XK_t}},                                   setlayout,          {.v = &layouts[0] } }),          // layout[0]: tile
  &((Keychord){2, {{MODKEY, XK_w}, {0, XK_f}},                                   setlayout,          {.v = &layouts[1] } }),          // layout[1]: no layout function = floating behavior
  &((Keychord){2, {{MODKEY, XK_w}, {0, XK_m}},                                   setlayout,          {.v = &layouts[2] } }),          // layout[2]: monocle
  &((Keychord){2, {{MODKEY, XK_w}, {0, XK_b}},                                   setlayout,          {.v = &layouts[3] } }),          // layout[3]: bottom stack
  &((Keychord){2, {{MODKEY, XK_w}, {ShiftMask, XK_b}},                           setlayout,          {.v = &layouts[4] } }),          // layout[4]: bottom stack horizontal
  &((Keychord){2, {{MODKEY, XK_w}, {0, XK_s}},                                   setlayout,          {.v = &layouts[5] } }),          // layout[5]: spiral
  &((Keychord){2, {{MODKEY, XK_w}, {0, XK_d}},                                   setlayout,          {.v = &layouts[6] } }),          // layout[6]: dwindle
  &((Keychord){2, {{MODKEY, XK_w}, {ShiftMask, XK_d}},                           setlayout,          {.v = &layouts[7] } }),          // layout[7]: deck
  &((Keychord){2, {{MODKEY, XK_w}, {0, XK_g}},                                   setlayout,          {.v = &layouts[8] } }),          // layout[8]: grid
  &((Keychord){2, {{MODKEY, XK_w}, {ShiftMask, XK_g}},                           setlayout,          {.v = &layouts[9] } }),          // layout[9]: n + 1 row grid
  &((Keychord){2, {{MODKEY, XK_w}, {ControlMask, XK_g}},                         setlayout,          {.v = &layouts[10] } }),         // layout[10]: gapless grid
  &((Keychord){2, {{MODKEY, XK_w}, {0, XK_h}},                                   setlayout,          {.v = &layouts[11] } }),         // layout[11]: horizontal grid
  &((Keychord){2, {{MODKEY, XK_w}, {0, XK_c}},                                   setlayout,          {.v = &layouts[12] } }),         // layout[12]: centered master
  &((Keychord){2, {{MODKEY, XK_w}, {ShiftMask, XK_c}},                           setlayout,          {.v = &layouts[13] } }),         // layout[13]: centered floating master
  &((Keychord){2, {{MODKEY, XK_w}, {0, XK_space}},                               setlayout,          {0} }),                          // back to tile layout
  &((Keychord){2, {{MODKEY, XK_w}, {0, XK_j}},                                   cyclelayout,        {.i = +1 } }),                   // cycle to the next layout
  &((Keychord){2, {{MODKEY, XK_w}, {0, XK_k}},                                   cyclelayout,        {.i = -1 } }),                   // cycle to the previous layout
  &((Keychord){2, {{MODKEY, XK_w}, {ShiftMask, XK_m}},                           layoutmenu,         {0} }),                          // toggle layoutmenu
  &((Keychord){2, {{MODKEY, XK_t}, {0, XK_s}},                                   togglesticky,       {0} }),                          // toggle sticky window
  &((Keychord){2, {{MODKEY, XK_t}, {0, XK_f}},                                   togglefloating,     {0} }),                          // toggle floating window
  &((Keychord){2, {{MODKEY, XK_t}, {ShiftMask, XK_f}},                           togglefullscreen,   {0} }),                          // toggle fullscreen in selected window

  // X11 keybindings
  &((Keychord){1, {{0, XF86XK_AudioMute}},                                       spawn,              {.v = mutecmd } }),              // mute sound command
  &((Keychord){1, {{0, XF86XK_AudioRaiseVolume}},                                spawn,              {.v = raisevolcmd } }),          // raise sound command
  &((Keychord){1, {{0, XF86XK_AudioLowerVolume}},                                spawn,              {.v = lowervolcmd } }),          // lower sound command
  &((Keychord){1, {{0, XF86XK_AudioNext}},                                       spawn,              {.v = mpcnextcmd } }),           // next media command
  &((Keychord){1, {{0, XF86XK_AudioPrev}},                                       spawn,              {.v = mpcprevcmd } }),           // previous media command
  &((Keychord){1, {{0, XF86XK_AudioPlay}},                                       spawn,              {.v = mpcplaycmd } }),           // play media command
  &((Keychord){1, {{0, XF86XK_AudioPause}},                                      spawn,              {.v = mpcpausecmd } }),          // pause media command
  &((Keychord){1, {{0, XF86XK_AudioStop}},                                       spawn,              {.v = mpcstopcmd } }),           // stop media command
  &((Keychord){1, {{0, XF86XK_AudioForward}},                                    spawn,              {.v = mpcfwdcmd } }),            // forward audio command
  &((Keychord){1, {{0, XF86XK_AudioRewind}},                                     spawn,              {.v = mpcrwdcmd } }),            // rewind audio command
  &((Keychord){1, {{0, XF86XK_AudioMedia}},                                      spawn,              {.v = sndmediacmd } }),          // media|music client
  &((Keychord){1, {{0, XF86XK_AudioMicMute}},                                    spawn,              {.v = micmutecmd } }),           // mute microphone command
  &((Keychord){1, {{0, XF86XK_MonBrightnessUp}},                                 spawn,              {.v = brightnessupcmd } }),      // brightness up command
  &((Keychord){1, {{0, XF86XK_MonBrightnessDown}},                               spawn,              {.v = brightnessdowncmd } }),    // brightness down command

  // Tags control keybindings
  &((Keychord){1, {{MODKEY, XK_Tab}},                                            view,               {0} }),                          // view across current and previous tag
  &((Keychord){1, {{MODKEY, XK_0}},                                              view,               {.ui = ~0 } }),                  // view all tags
  &((Keychord){1, {{MODKEY|ShiftMask, XK_0}},                                    tag,                {.ui = ~0 } }),                  // tag all tags

  // Tags keybindings
	TAGKEYS(XK_1,                                                                  0)                                                   // go to the tag 1
	TAGKEYS(XK_2,                                                                  1)                                                   // go to the tag 2
	TAGKEYS(XK_3,                                                                  2)                                                   // go to the tag 3
	TAGKEYS(XK_4,                                                                  3)                                                   // go to the tag 4
	TAGKEYS(XK_5,                                                                  4)                                                   // go to the tag 5
	TAGKEYS(XK_6,                                                                  5)                                                   // go to the tag 6
	TAGKEYS(XK_7,                                                                  6)                                                   // go to the tag 7
	TAGKEYS(XK_8,                                                                  7)                                                   // go to the tag 8
	TAGKEYS(XK_9,                                                                  8)                                                   // go to the tag 9
};

// Click and button definitions
/* 1) click can be:
   ClkTagBar = tags areas,
   ClkLtSymbol = symbol layout area (from the left of the bar), 
   ClkStatusText = text status area (from the right of the bar), 
   ClkWinTitle = (active window title in the bar), 
   ClkClientWin = client window itself, or
   ClkRootWin = window root. */
/* 2) button can be:
   Button1 = left click,
   Button2 = middle click,
   Button3 = right click,
   Button4 = Scroll up,
   Button5 = Scroll down. */
static const Button buttons[] = {
	// click                event mask      button          function        argument
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
	{ ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3} },
	{ ClkTagBar,            0,              Button2,        spawntag,       {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
};

