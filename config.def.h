/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 5;        /* border pixel of windows */
static const unsigned int gappx     = 15;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 10;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char scratchpadname[]  = "scratchpad";
static const char *scratchpadcmd[]  = { "st", "-t", scratchpadname, "-g", "160x45", NULL };
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */

/* Mononoki Nerd Font must be installed from AUR nerd-fonts-complete.
 * Otherwise, your default font will be Hack which is found in the standard
 * Arch repos and is listed as a dependency for this build. JoyPixels is also
 * a hard dependency and makes colored fonts and emojis possible.
 */
static const char *fonts[]            = {"Mononoki Nerd Font:size=12:antialias=true:autohint=true",
                                         "Hack:size=8:antialias=true:autohint=true",
                                         "JoyPixels:size=10:antialias=true:autohint=true"
										};

// background color
static const char col_bg[]       		= "#222222";
// inactive window border color
static const char col_inactive_win[]	= "#444444";
// font color
static const char col_font[]       		= "#ffffff";
// current tag and current window font color
static const char col_curr_win[]       	= "#ffffff";
// top bar second color and active window border color
static const char col_curr_win_border[] = "#aa0000";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_font, col_bg, col_inactive_win },
	[SchemeSel]  = { col_curr_win, col_curr_win_border,  col_curr_win_border  },
};

/* tagging */
static const char *tags[] = { "", "", "", "", "" };
// static const char *tags[] = { "", "", "", "", "", "", "", "", "" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class         instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",        NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "Firefox",     NULL,     NULL,           1 << 8,    0,          0,          -1,        -1 },
	{ "St",          NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ "Alacritty",   NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ "xdman-Main",  NULL,     NULL,           1 << 8,    1,          0,           0,        -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "|||",      col },
};

/* key definitions */
#define MODKEY Mod4Mask
#define ALT Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "" };
static const char *termcmd[]  = { "st -c 'St'", NULL };

static const int gapDelta = 3;

#include "shiftview.c"
#include <X11/XF86keysym.h>
static Key keys[] = {
	/* modifier                     key        function        argument */
	// Dmenu prompts
	{ ALT,                       	XK_r,      spawn,          SHCMD("dmenu_run -i -p 'Run: '") },
	{ ALT,                       	XK_space,  spawn,          SHCMD("j4-dmenu-desktop --no-generic --dmenu=\"dmenu -i -p 'Launch: '\" --term='alacritty'") },

	// Layout management
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,      rotatestack,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      rotatestack,    {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY|ShiftMask,             XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Tab,    view,           {0} },

	// Layout selection
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_u,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_o,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_c,      setlayout,      {.v = &layouts[5]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	// { MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	// { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },

	// Monitor management
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },

	// Layout navigation
	{ MODKEY,                       XK_n, shiftview,       	   {.i = +1 } },
	{ MODKEY,                       XK_b, shiftview,       	   {.i = -1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)

	// Gap management
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -gapDelta } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +gapDelta } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },

	// DWM management
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY|ShiftMask,             XK_b,      togglebar,      {0} },
	{ MODKEY,             			XK_l,      spawn,      	   SHCMD("i3lock") },

	// Media keys
	{ 0, XF86XK_MonBrightnessUp, 	   		   spawn,          SHCMD("xbacklight -inc 5") },
	{ 0, XF86XK_MonBrightnessDown, 	   		   spawn,          SHCMD("xbacklight -dec 5") },
	{ 0, XF86XK_AudioMute, 	   		   		   spawn,          SHCMD("$HOME/scripts/audio/volume.zsh mute") },
	{ 0, XF86XK_AudioRaiseVolume, 	   		   spawn,          SHCMD("$HOME/scripts/audio/volume.zsh up") },
	{ 0, XF86XK_AudioLowerVolume, 	   		   spawn,          SHCMD("$HOME/scripts/audio/volume.zsh down") },

	// Dmenu scripts run with ctrl alt
	{ ControlMask|ALT,              XK_e, 	   spawn,          SHCMD("$HOME/scripts/dmenu/dmenu-edit-configs.sh") },
	{ ControlMask|ALT,              XK_w, 	   spawn,          SHCMD("$HOME/scripts/dmenu/dmenu-set-wallpaper.sh") },
	{ ControlMask|ALT,              XK_v, 	   spawn,          SHCMD("$HOME/scripts/dmenu/dmenu-show-vms.sh") },
	{ ControlMask|ALT,              XK_s, 	   spawn,          SHCMD("$HOME/scripts/wallpaper/safe_wallpaper.sh") },


	// Applications
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_x,  	   togglescratch,  {.v = scratchpadcmd } },
	{ MODKEY,             			XK_x, 	   spawn,          SHCMD("st -c 'St'") },
	{ MODKEY,             			XK_e, 	   spawn,          SHCMD("st -e ranger") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
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
