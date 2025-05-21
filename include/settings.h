#ifndef SETTINGS_H
# define SETTINGS_H

# define WINDOW_W		1440
# define WINDOW_H		900
# define WINDOW_TITLE	"fdf by Alex Schenk @42 Berlin"

// Set the background color
# define BG_COLOR		BLACK

// Set the default color for the wireframe
# define WIRE_COLOR		SKY_BLUE

// Isometric projection: 30° from horizontal line to x and y axes.
# define ANGLE			30

// Z_SCALE: For example 10 unit x 0.1 = 1 unit (same as x and y)
# define Z_S			0.08

/*
SCREEN_UTILIZATION [0-1]: Minimum space between the projected map and
the edges of the window:
- 1:	No space between the projection and window edges.
- 0.5:	At least 25% of the window size between each side of the projection and
		the window edges.
*/
# define SCREEN_UTIL	0.9

// List of Color Macros

# define BLACK			0x000000
# define WHITE			0xFFFFFF
# define RED			0xFF0000
# define GREEN			0x00FF00
# define BLUE			0x0000FF
# define YELLOW			0xFFFF00
# define MAGENTA		0xFF00FF
# define CYAN			0x00FFFF
# define ORANGE			0xFFA500
# define PURPLE			0x800080
# define PINK			0xFFC0CB
# define BROWN			0xA52A2A
# define GRAY			0x808080
# define LIGHT_GRAY		0xD3D3D3
# define DARK_GRAY		0x696969
# define GOLD			0xFFD700
# define SILVER			0xC0C0C0
# define MAROON			0x800000
# define OLIVE			0x808000
# define NAVY			0x000080
# define TEAL			0x008080
# define INDIGO			0x4B0082
# define TURQUOISE		0x40E0D0
# define VIOLET			0xEE82EE
# define LIME			0x00FF00
# define DARK_GREEN		0x006400
# define LIGHT_GREEN	0x90EE90
# define SKY_BLUE		0x87CEEB
# define ROYAL_BLUE		0x4169E1
# define CORAL			0xFF7F50
# define SALMON			0xFA8072
# define TOMATO			0xFF6347
# define FIREBRICK		0xB22222
# define DARK_ORANGE	0xFF8C00
# define DARK_CYAN		0x008B8B
# define DARK_PURPLE	0x800080
# define DARK_MAGENTA	0x8B008B
# define DARK_YELLOW	0x808000
# define DARK_PINK		0x8B008B
# define DARK_RED		0x8B0000
# define DARK_BLUE		0x00008B
# define DARK_SILVER	0xA9A9A9
# define LIGHT_SILVER	0xD3D3D3

#endif
