/* See LICENSE file for copyright and license details. */
/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int snap      = 16;       /* snap pixel */
static const unsigned int gappih    = 26;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 26;       /* vert inner gap between windows */
static const unsigned int gappoh    = 19;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 24;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int user_bh            = 24;      	/* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const int vertpad            = 8;       	/* vertical padding of bar */
static const int sidepad            = 23;       /* horizontal padding of bar */
static const char *fonts[]          = { "Hermit:size=11:style=bold" };
static const char dmenufont[]       = "Hermit:size=11:style=bold";
static const char col_text[] 	    = "#bdbdbd";
static const char col_text_bright[] = "#e8e8e8";
static const char col_navy[]        = "#232731";
static const char col_ice[]         = "#a7c3d9";
static const char col_blue[]        = "#4e8cb7";
static const char col_light_blue[]  = "#68a7d4";
static const char col_orange[]      = "#f28a4a";
static const char *colors[][3]      = {
	/*               	    fg         	      bg         border   */
	[SchemeNorm] 		= { col_text_bright,  col_navy,  col_navy },
	[SchemeSel]  		= { col_text_bright,  col_navy,  col_navy },
	[SchemeStatus]  	= { col_text_bright,  col_navy,  col_navy }, // Statusbar right
	[SchemeTagsSel]  	= { col_light_blue,   col_navy,  col_navy }, // Tagbar left selected
    	[SchemeTagsNorm]  	= { col_text_bright,  col_navy,  col_orange }, // Tagbar left unselected
    	[SchemeInfoSel]  	= { col_text_bright,  col_navy,  col_navy }, // infobar middle selected
    	[SchemeInfoNorm]  	= { col_text_bright,  col_navy,  col_navy }, // infobar middle unselected
};

/* staticstatus */
static const int statmonval = 0;

/* tagging */
static const char *tags[] = { "  ", "  ", "  ", "  ", "  ", "  ", "  ", "  ", "  " };
static const char *tagsalt[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      	 		      	instance     	title       		tags mask    	isfloating monitor */
	{ NULL,					NULL,	 	"/bin/sh",		0,		1,	    -1 },
	{ NULL,					NULL,	 	"/bin/bash",		0,		1,	    -1 },
	{ NULL,					NULL,	 	"ranger",		0,		1,	    -1 },
	{ "feh",				NULL,	    	NULL,			0,		1,	    -1 },
	{ "Surf",				NULL,	    	NULL,			1 << 2,		0,	    -1 },
	{ "firefox",  	 			NULL,       	NULL,      		1 << 2,       	0,          -1 },
	{ "spotify",				NULL,	    	NULL,			1 << 3,		0,	    -1 },
	{ "discord",	 			NULL,	    	NULL,			1 << 4,		0,	    -1 },
	{ "Evince", 	 			NULL,	    	NULL,			1 << 5,		0,	    -1 },
	{ NULL,					NULL,    	"LibreOffice",		1 << 6,		0,	    -1 },
	{ "Gimp",     	 			NULL,       	NULL,       		1 << 6,      	0,          -1 },
	{ "VirtualBox Manager", 		NULL,	    	NULL,			1 << 8,		0,	    -1 },
};

/* layout(s) */
static const float mfact     = 0.485; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ " [] ",      tile },    /* first entry is default */
	{ " [] ",      monocle },
	{ " [] ",      NULL },    /* no layout function means floating behavior */
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
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_navy, "-nf", col_ice, "-sb", col_blue, "-sf", col_navy, topbar ? NULL : "-b", NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *fileexplorecmd[]  = { "st", "-e", "ranger", NULL };
static const char *socialcmd[]  = { "discord", NULL };
static const char *webcmd[]  = { "firefox", NULL };
static const char *musiccmd[]  = { "/bin/sh", "-c", "$HOME/.scripts/spotify.sh", NULL };
static const char *suspendcmd[] = { "/bin/sh", "-c", "$HOME/.scripts/suspend.sh", NULL };
static const char *shutdowncmd[] = { "/bin/sh", "-c", "$HOME/.scripts/shutdown.sh", NULL };
static const char *restartcmd[] = { "/bin/sh", "-c", "$HOME/.scripts/restart.sh", NULL };
static const char *lockcmd[] = { "/bin/sh", "-c", "$HOME/.scripts/lock.sh", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY|ShiftMask,             XK_Home,   quit,           {0} },
	{ MODKEY|ShiftMask,		XK_Delete, spawn,	   {.v = suspendcmd } },
	{ MODKEY|ShiftMask,		XK_Insert, spawn,	   {.v = restartcmd } },
	{ MODKEY|ShiftMask,		XK_End,	   spawn,	   {.v = shutdowncmd } },
	{ MODKEY|ShiftMask,		XK_x,	   spawn,	   {.v = lockcmd } },
	{ MODKEY,             		XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,             		XK_f, 	   spawn,          {.v = fileexplorecmd } },
	{ MODKEY,             		XK_s,      spawn,          {.v = socialcmd } },
	{ MODKEY,             		XK_w,      spawn,          {.v = webcmd } },
	{ MODKEY,             		XK_m,      spawn,          {.v = musiccmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY|ShiftMask,             XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|Mod4Mask,              XK_h,      incrgaps,       {.i = +1 } },
	{ MODKEY|Mod4Mask,              XK_l,      incrgaps,       {.i = -1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_h,      incrogaps,      {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_l,      incrogaps,      {.i = -1 } },
	{ MODKEY|Mod4Mask|ControlMask,  XK_h,      incrigaps,      {.i = +1 } },
	{ MODKEY|Mod4Mask|ControlMask,  XK_l,      incrigaps,      {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_0,      togglegaps,     {0} },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },
	{ MODKEY,                       XK_y,      incrihgaps,     {.i = +1 } },
	{ MODKEY,                       XK_o,      incrihgaps,     {.i = -1 } },
	{ MODKEY|ControlMask,           XK_y,      incrivgaps,     {.i = +1 } },
	{ MODKEY|ControlMask,           XK_o,      incrivgaps,     {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_y,      incrohgaps,     {.i = +1 } },
	{ MODKEY|Mod4Mask,              XK_o,      incrohgaps,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_y,      incrovgaps,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_o,      incrovgaps,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ShiftMask,             XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_n,      togglealttag,   {0} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

