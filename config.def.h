/* See LICENSE file for copyright and license details. */

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
static const char *tags[] = { "🎯", "🔍", "💻", "📊", "🌐", "📝", "🔧", "📡", "🛡️" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     			instance  title           tags mask  isfloating		x, 		y, 		w, 		h	 			isterminal  noswallow  monitor */
	{ "Gimp",    			NULL,     NULL,           0,         1,			    -1,		-1,		-1,		-1,         	0,          0,        -1 },
	{"Qalculate-gtk",		NULL,	  NULL,			  0,		 1,				.35,	35,		.3,		.5,				0,			0,		  -1 },
	{ "Firefox", 			NULL,     NULL,           1 << 8,    0,				-1,		-1,		-1,		-1, 			0,         -1,        -1 },
	{ "st-256color",      	NULL,     NULL,           0,         0,				-1,		-1,		-1,		-1,				1,          0,        -1 },
	{ NULL,      			NULL,     "Event Tester", 0,         0,				-1,		-1,		-1,		-1,				0,          1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int attachbelow = 1;    /* 1 means attach after the currently active window */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
static const int refreshrate = 120;  /* refresh rate (per second) for client move/resize */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },							/* layout[0]: tile */
	{ "><>",      NULL },							/* layout[1]: no layout function = floating behavior */
	{ "[M]",      monocle },						/* layout[2]: monocle */
	{ "TTT",      bstack },							/* layout[3]: bottom stack */
	{ "===",      bstackhoriz },					/* layout[4]: bottom stack horizontal */
	{ "[@]",      spiral },							/* layout[5]: spiral */
	{ "[\\]",     dwindle },						/* layout[6]: dwindle */
	{ "H[]",      deck },							/* layout[7]: deck */
	{ "HHH",      grid },							/* layout[8]: grid */
	{ "###",      nrowgrid },						/* layout[9]: n + 1 row grid */
	{ ":::",      gaplessgrid },					/* layout[10]: gapless grid */	
	{ "---",      horizgrid },						/* layout[11]: horizontal grid */
	{ "|M|",      centeredmaster },					/* layout[12]: centered master */
	{ ">M>",      centeredfloatingmaster },			/* layout[13]: centered floating master */
	{ NULL,       NULL },
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

/* helper for launching gtk application */
#define GTKCMD(cmd) { .v = (const char*[]){ "/usr/bin/gtk-launch", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *layoutmenu_cmd = "layoutmenu.sh";
static const scratchpad qalculate = {.class = "Qalculate-gtk", .v = (char *[]){"qalculate-gtk", NULL}};

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

static const Key keys[] = {
	/* modifier                     key				   function        argument */

    /* spawn keybindings */
	{ MODKEY,                       XK_p,			   spawn,          {.v = dmenucmd } },
	{ MODKEY,             			XK_Return,		   spawn,          {.v = termcmd } },

    /* dwm control keybindings */
    { MODKEY,             			XK_q,			   killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_q,      		   quit,		   {0} },
	{ MODKEY|ControlMask|ShiftMask, XK_q,      		   quit,           {1} }, 
	{ MODKEY,                       XK_b,			   togglebar,      {0} },

	/* stack control keybindings */
    { MODKEY,                       XK_j,			   focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,			   focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,			   incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,			   incnmaster,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,      		   rotatestack,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,              rotatestack,    {.i = -1 } },
	{ MODKEY,                       XK_h,			   setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,			   setmfact,       {.f = +0.05} },
    { MODKEY|ShiftMask,             XK_Return,		   zoom,           {0} },

	/* layouts keybinds */
	{ MODKEY,                       XK_t,			   setlayout,      {.v = &layouts[0] } },		/* layout[0]: tile */                                   
	{ MODKEY,                       XK_f,			   setlayout,      {.v = &layouts[1] } },		/* layout[1]: no layout function = floating behavior */
	{ MODKEY,                       XK_m,			   setlayout,      {.v = &layouts[2] } },		/* layout[2]: monocle */
	{ MODKEY|ShiftMask,             XK_b,      		   setlayout,      {.v = &layouts[3] } },		/* layout[3]: bottom stack */
	{ MODKEY|ControlMask|ShiftMask, XK_b,      		   setlayout,      {.v = &layouts[4] } },		/* layout[4]: bottom stack horizontal */
	{ MODKEY,                       XK_r,      		   setlayout,      {.v = &layouts[5] } },		/* layout[5]: spiral */
	{ MODKEY|ShiftMask,             XK_t,      		   setlayout,      {.v = &layouts[6] } },		/* layout[6]: dwindle */
	{ MODKEY|ShiftMask,             XK_d,			   setlayout,      {.v = &layouts[7] } },		/* layout[7]: deck */
	{ MODKEY,                       XK_g,			   setlayout,      {.v = &layouts[8] } },		/* layout[8]: grid */
	{ MODKEY|ShiftMask,             XK_g,			   setlayout,      {.v = &layouts[9] } },		/* layout[9]: n + 1 row grid */
	{ MODKEY|ControlMask|ShiftMask, XK_g,			   setlayout,      {.v = &layouts[10] } },		/* layout[10]: gapless grid */
	{ MODKEY|ShiftMask,             XK_h,      		   setlayout,      {.v = &layouts[11] } },		/* layout[11]: horizontal grid */ 
	{ MODKEY,                       XK_c,			   setlayout,	   {.v = &layouts[12] } },		/* layout[12]: centered master */
	{ MODKEY|ShiftMask,             XK_c,      		   setlayout,      {.v = &layouts[13] } },		/* layout[13]: centered floating master */
	{ MODKEY|ControlMask,			XK_comma,  		   cyclelayout,    {.i = -1 } },
	{ MODKEY|ControlMask,           XK_period, 		   cyclelayout,    {.i = +1 } },
	{ MODKEY,                       XK_space,		   setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,		   togglefloating, {0} },

	/* multi-monitor keybinds */
	{ MODKEY,                       XK_Left,		   focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_Right,		   focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_Left,		   tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_Right,		   tagmon,         {.i = +1 } },
    { MODKEY,             			XK_backslash,      swapmon,   	   {0} },

	/* gaps control keybindings */
    { MODKEY|Mod1Mask,              XK_u,			   incrgaps,       {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_u,			   incrgaps,       {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_i,			   incrigaps,      {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_i,			   incrigaps,      {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_o,			   incrogaps,      {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_o,			   incrogaps,      {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_6,			   incrihgaps,     {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_6,			   incrihgaps,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_7,			   incrivgaps,     {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_7,			   incrivgaps,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_8,			   incrohgaps,     {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_8,			   incrohgaps,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_9,			   incrovgaps,     {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_9,			   incrovgaps,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_equal,		   togglegaps,     {0} },
	{ MODKEY|ShiftMask,    			XK_minus,		   defaultgaps,    {0} },


	/* scratchpads */
	{ControlMask,					XK_s,			   togglescratch,  {.v = &qalculate } },

    /* tags keys */
	TAGKEYS(                        XK_1,							   0)
	TAGKEYS(                        XK_2,							   1)
	TAGKEYS(                        XK_3,							   2)
	TAGKEYS(                        XK_4,							   3)
	TAGKEYS(                        XK_5,							   4)
	TAGKEYS(                        XK_6,							   5)
	TAGKEYS(                        XK_7,							   6)
	TAGKEYS(                        XK_8,							   7)
	TAGKEYS(                        XK_9,							   8)

	/* tags control keybindings */
	{ MODKEY,                       XK_0,			   view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,			   tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_Tab,			   view,           {0} },
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
	{ ClkLtSymbol,          0,              Button3,        layoutmenu,     {0} },
	{ ClkLtSymbol,          0,              Button4,        cyclelayout,    {.i = +1 } },
	{ ClkLtSymbol,          0,              Button5,        cyclelayout,    {.i = -1 } },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button2,        spawntag,       {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

