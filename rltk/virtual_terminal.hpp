#pragma once
/* RLTK (RogueLike Tool Kit) 1.00
 * Copyright (c) 2016-Present, Bracket Productions.
 * Licensed under the LGPL - see LICENSE file.
 *
 * Provides a virtual console
 */

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "font_manager.hpp"
#include "texture.hpp"
#include "color_t.hpp"

namespace rltk {

struct vchar {
	int glyph;
	color_t foreground;
	color_t background;
};

struct virtual_terminal {
public:
	virtual_terminal(const std::string fontt, const int x=0, const int y=0, const bool background=true) : font_tag(fontt), offset_x(x), offset_y(y), has_background(background) {
		font = get_font(fontt);
	}

	void resize_pixels(const int width, const int height);
	void resize_chars(const int width, const int height);
	void clear();
	void clear(const vchar &target);
	inline int at(const int x, const int y) { return ( y * term_width) + x; }
	void set_char(const int idx, const vchar &target);
	inline void set_char(const int x, const int y, vchar target) { set_char(at(x,y), target); }
	void print(const int x, const int y, const std::string &s, const color_t &fg, const color_t &bg);
	void print_center(const int y, const std::string &s, const color_t &fg, const color_t &bg);
	inline void box(const color_t &fg, const color_t &bg, bool double_lines=false) {
		box (0, 0, term_width-1, term_height-1, fg, bg, double_lines);
	}
	void box(const int x, const int y, const int w, const int h, const color_t &fg, const color_t &bg, bool double_lines=false);

	void render(sf::RenderWindow &window);

	inline void set_alpha(const uint8_t new_alpha) { alpha = new_alpha; }
	inline void set_tint(const color_t new_tint) { tint = new_tint; }
	inline void set_offset(int x, int y) { offset_x = x; offset_y = y; };
	inline std::pair<int,int> get_font_size() { return font->character_size; }

	int term_width;
	int term_height;
	bool visible = true;
	bool dirty = true; // Flag for requiring a re-draw

private:
	sf::RenderTexture backing;
	sf::VertexArray vertices;
	std::string font_tag;
	int offset_x;
	int offset_y;
	uint8_t alpha = 255;
	color_t tint{255,255,255};
	bool has_background;
	bitmap_font * font = nullptr;
	sf::Texture * tex = nullptr;
	std::vector<vchar> buffer;

};

}