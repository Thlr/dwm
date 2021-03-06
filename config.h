/* See LICENSE file for copyright and license details. */

/* CONSTANTS */
#define TERMINAL "st"
#define TERMCLASS "St"
#define BROWSER "firefox"
#define BROWSERCLASS "Firefox"
//#define FONT "Cousine Nerd Font Mono:style=Regular:size=13"
//#define FONT "JetBrainsMono Nerd Font Mono:style=Regular:size=12"
//#define FONT "Hack Nerd Font Mono:style=Regular:size=12"
//#define FONT "Ubuntu Nerd Font Mono:style=Regular:size=12"
#define FONT "Noto Mono:style=Regular:size=13"

/* APPEARANCE */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const Bool smartborders      = False;    /* No border when there is only one window */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 3;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const unsigned int gappih    = 8;        /* horiz inner gap between windows */
static const unsigned int gappiv    = 8;        /* vert inner gap between windows */
static const unsigned int gappoh    = 5;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 5;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int user_bh            = 0;        /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */

static const char *fonts[]          = { FONT, "Ubuntu Nerd Font Mono:style=Regular:size=12" };
static const char dmenufont[]       = FONT;
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char col_cyan_light[]  = "#196684";
static const char col_red[] 	    = "#af1b1b";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan_light },
};

typedef struct {
	const char *name;
	const void *cmd;
} Sp;

const char *spcmd1[] = { TERMINAL, "-n", "spterm", "-g", "80x24", NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",      spcmd1},
};

/* TAGS */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

/* RULES */
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class          	instance      title           tags mask  iscentered  isfloating  isterminal  noswallow  monitor */
	{ NULL,    	        NULL,         "Event Tester", 0,         0,          0,          0,          1,        	-1 },
	{ TERMCLASS,   		NULL,         NULL,           0,         0,          0,          1,          0,        	-1 },
	{ "Gnome-calculator",   NULL,         NULL,           0,         1,          1,          0,          1,        	-1 },
	{ "Pavucontrol",   	NULL,         NULL,           0,         1,          1,          0,          1,        	-1 },
	{ "Blueman-manager",    NULL,         NULL,           0,         0,          1,          0,          1,        	-1 },
	{ "MEGAsync",   	NULL,         NULL,           0,         0,          1,          0,          1,        	-1 },
	{ "Transmission-gtk",   NULL,         NULL,           0,         1,          1,          0,          1,        	-1 },
	{ NULL,		        "spterm",     NULL,           SPTAG(0),	 1,	     1,          1,          0,         -1 },
	{ "zoom",               NULL,         NULL,           0,         1,          1,          0,          1,         -1 },
};

/* LAYOUTS */
static const float mfact            = 0.5;  /* factor of master area size [0.05..0.95] */
static const int nmaster            = 1;    /* number of clients in master area */
static const int resizehints        = 1;    /* 1 means respect size hints in tiled resizals */
static const int attachbelow        = 1;    /* 1 means attach after the currently active window */
static const int autoresetlayouts   = 0;    /* Automatically resets layouts when only one client is visible */
static const Bool viewontag         = False; /* Switch view on tag switch */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* Default: Master on left, stack on the right */
	{ "TTT",      bstack }, /* Master on top, stack on bottom */

	{ "[@]",      spiral }, /* Fibonacci spiral */
	{ "[\\]",     dwindle }, /* Decreasing in size right and leftward */

	{ "H[]",      deck }, /* Master on left, monocle stack on the right */
	{ "[M]",      monocle }, /* Everything on top of each other */

	{ "><>",      NULL },    /* no layout function means floating behavior */
};

/* HELPER DEFINITIONS */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} }, \
	{ MODKEY|Mod1Mask,              KEY,      swaptags,       {.ui = 1 << TAG} },
#define STACKKEYS(MOD,ACTION) \
	{ MOD, XK_j,     ACTION##stack, {.i = INC(+1) } }, \
	{ MOD, XK_k,     ACTION##stack, {.i = INC(-1) } }, \
	{ MOD, XK_a,     ACTION##stack, {.i = PREVSEL } }, \
	{ MOD, XK_v,     ACTION##stack, {.i = 0 } },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* COMMANDS */
// dmenu
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };

// terminal
static const char *termcmd[]  = { TERMINAL, NULL };

// system
static const char sessionlockcmd[] = "sessionlock";
static const char sysactcmd[] = "sysact";
static const char sleepcmd[] = "sudo -A zzz";

// screenshots
static const char screenshotcmd[] = "flameshot gui";

// audio
static const char mutecmd[] = "pamixer -t; kill -44 $(pidof dwmblocks)";
static const char incvolcmd[] = "pamixer -i 5; kill -44 $(pidof dwmblocks)";
static const char decvolcmd[] = "pamixer -d 5; kill -44 $(pidof dwmblocks)";
static const char incvolpluscmd[] = "pamixer --allow-boost -i 10; kill -44 $(pidof dwmblocks)";
static const char decvolpluscmd[] = "pamixer --allow-boost -d 10; kill -44 $(pidof dwmblocks)";
static const char micmutecmd[] = "pactl set-source-mute @DEFAULT_SOURCE@ toggle; kill -44 $(pidof dwmblocks)";

//  brightness
static const char incbrightnesscmd[] = "xbacklight -inc 5";
static const char decbrightnesscmd[] = "xbacklight -dec 5";

// touchpad
static const char toggletouchpadcmd[] = "(synclient | grep 'TouchpadOff.*1' && synclient TouchpadOff=0) || synclient TouchpadOff=1";
static const char touchpadoncmd[] = "synclient TouchpadOff=1";
static const char touchpadoffcmd[] = "synclient TouchpadOff=0";

// utilities
static const char calculatorcmd[] = "gnome-calculator";

/* BINDINGS */
#include <X11/XF86keysym.h>
static Key keys[] = {
	/* modifier                 key                       function        argument */

	/* clients */
	STACKKEYS(MODKEY,                                     focus)
	STACKKEYS(MODKEY|ShiftMask,                           push)
	{ MODKEY,                   XK_Return,                spawn,          {.v = termcmd } },
	{ MODKEY,                   XK_h,                     setmfact,       {.f = -0.02} },
	{ MODKEY,                   XK_l,                     setmfact,       {.f = +0.02} },
	{ MODKEY,                   XK_equal,                 setmfact,       {.f = 1 + mfact} }, // reset mfact
	{ MODKEY|ShiftMask,         XK_h,                     setcfact,       {.f = -0.2} },
	{ MODKEY|ShiftMask,         XK_l,                     setcfact,       {.f = +0.2} },
	{ MODKEY|ShiftMask,         XK_equal,                 setcfact,       {.f =  0.00} }, // reset cfact
	{ MODKEY,                   XK_space,                 zoom,           {0} },
	{ MODKEY,             	    XK_f,                     togglefullscr,  {0} },
	{ MODKEY|ShiftMask,         XK_space,                 togglefloating, {0} },
	{ MODKEY, 		    XK_q,                     killclient,     {0} },
	{ MODKEY,                   XK_s,                     togglesticky,   {0} },
        { MODKEY,                   XK_i,                     incnmaster,     {.i = +1 } },
        { MODKEY|ShiftMask,         XK_i,                     incnmaster,     {.i = -1 } },
	{ MODKEY,                   XK_o,                     resetnmaster,   {0} },
	{ MODKEY|ShiftMask,         XK_o,                     resetlayout,    {0} },

	/* layouts */
	{ MODKEY,                   XK_t,                     setlayout,      {.v = &layouts[0]} }, // tile
	{ MODKEY|ShiftMask,         XK_t,                     setlayout,      {.v = &layouts[1]} }, // bstacks
	{ MODKEY,                   XK_y,                     setlayout,      {.v = &layouts[2]} }, // spiral
	{ MODKEY|ShiftMask,         XK_y,                     setlayout,      {.v = &layouts[3]} }, // dwindle
	{ MODKEY,                   XK_u,                     setlayout,      {.v = &layouts[4]} }, // deck
	{ MODKEY|ShiftMask,         XK_u,                     setlayout,      {.v = &layouts[5]} }, // monocle
	{ MODKEY|ShiftMask,         XK_f,                     setlayout,      {.v = &layouts[6]} }, // floating

	/* gaps */
	{ MODKEY,              	    XK_g,                     togglegaps,     {0} },
	{ MODKEY|ShiftMask,         XK_g,                     defaultgaps,    {0} },
	{ MODKEY,                   XK_w,                     incrgaps,       {.i = +3 } },
	{ MODKEY, 	            XK_x,                     incrgaps,       {.i = -3 } },

	/* scratchpads */
	{ MODKEY,                   XK_z,                     togglescratch,  {.ui = 0 } },

	/* system */
	{ MODKEY|ShiftMask,         XK_q,                     quit,           {0} },
	{ MODKEY|ShiftMask,         XK_BackSpace,             spawn,          SHCMD(sysactcmd) },
	{ MODKEY,                   XK_BackSpace,             spawn,          SHCMD(sessionlockcmd) },

	/* dmenu */
	{ MODKEY,                   XK_d,                     spawn,          {.v = dmenucmd } },

	/* multi monitors */
	{ MODKEY,                   XK_comma,                 focusmon,       {.i = -1 } },
	//{ MODKEY,                   XK_period,                focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,         XK_comma,                 tagmon,         {.i = -1 } },
	//{ MODKEY|ShiftMask,         XK_period,                tagmon,         {.i = +1 } },

	/* status bar */
	{ MODKEY,                   XK_b,                     togglebar,      {0} },

	/* tags */
	{ MODKEY,                   XK_Tab,                   view,           {0} },
	TAGKEYS(                    XK_ampersand,                             0)
	TAGKEYS(                    XK_eacute,		               	      1)
	TAGKEYS(                    XK_quotedbl,	               	      2)
	TAGKEYS(                    XK_apostrophe,                            3)
	TAGKEYS(                    XK_parenleft,	                      4)
	TAGKEYS(                    XK_minus,			              5)
	TAGKEYS(                    XK_egrave,		                      6)
	TAGKEYS(                    XK_underscore,                            7)
	TAGKEYS(                    XK_ccedilla,	                      8)
	{ MODKEY,		    XK_agrave,                view,	      {.ui = ~0 } },

	/* toggle touchpad */
	{ MODKEY,                   XK_n,              	      spawn,          SHCMD(toggletouchpadcmd) },

	/* audio */
	{ MODKEY,                   XK_asterisk,              spawn,          SHCMD(incvolcmd) },
	{ MODKEY|ShiftMask,         XK_asterisk,              spawn,          SHCMD(incvolpluscmd) },
	{ MODKEY, 		    XK_ugrave,                spawn,          SHCMD(decvolcmd) },
	{ MODKEY|ShiftMask,	    XK_ugrave,                spawn,          SHCMD(decvolpluscmd) },
	{ MODKEY, 	            XK_m,                     spawn,          SHCMD(mutecmd) },
	{ MODKEY|ShiftMask,	    XK_m,                     spawn,          SHCMD(micmutecmd) },

	/* special keys */
	{ 0, 			    XK_Print,     	      spawn,          SHCMD(screenshotcmd) },
	{ 0,                        XF86XK_AudioMute,         spawn,          SHCMD(mutecmd) },
	{ 0,                        XF86XK_AudioRaiseVolume,  spawn,          SHCMD(incvolcmd) },
	{ 0,                        XF86XK_AudioLowerVolume,  spawn,          SHCMD(decvolcmd) },
	{ 0,                        XF86XK_AudioMicMute,      spawn,          SHCMD(micmutecmd) },
	{ 0,                        XF86XK_PowerOff,          spawn,          SHCMD(sysactcmd) },
	{ 0,                        XF86XK_Calculator,        spawn,          SHCMD(calculatorcmd) },
	{ 0,                        XF86XK_Sleep,     	      spawn,          SHCMD(sleepcmd) },
	{ 0,                        XF86XK_TouchpadToggle,    spawn,          SHCMD(toggletouchpadcmd) },
	{ 0,                        XF86XK_TouchpadOn,        spawn,          SHCMD(touchpadoncmd) },
	{ 0,                        XF86XK_TouchpadOff,       spawn,          SHCMD(touchpadoffcmd) },
	{ 0,                        XF86XK_MonBrightnessUp,   spawn,          SHCMD(incbrightnesscmd) },
	{ 0,                        XF86XK_MonBrightnessDown, spawn,          SHCMD(decbrightnesscmd) },
};

/* BUTTON DEFINITIONS */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
	{ ClkStatusText,        0,              Button4,        sigdwmblocks,   {.i = 4} },
	{ ClkStatusText,        0,              Button5,        sigdwmblocks,   {.i = 5} },
	{ ClkStatusText,        ShiftMask,      Button1,        sigdwmblocks,   {.i = 6} },
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
