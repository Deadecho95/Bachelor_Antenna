// -alpha_dither yes -dither 2 -non_opaque_image_format ARGB8888 -opaque_image_format RGB565 0xcbb90ae1
// Generated by imageconverter. Please, do not edit!

#include <touchgfx/Bitmap.hpp>
#include <BitmapDatabase.hpp>

#ifndef NO_USING_NAMESPACE_TOUCHGFX
using namespace touchgfx;
#endif

extern const unsigned char _blue_buttons_round_edge_icon_button[];
extern const unsigned char _blue_buttons_round_edge_icon_button_pressed[];
extern const unsigned char _blue_buttons_round_edge_small[];
extern const unsigned char _blue_buttons_round_edge_small_pressed[];
extern const unsigned char _blue_progressindicators_bg_medium_progress_indicator_bg_square_90_degrees[];

const touchgfx::Bitmap::BitmapData bitmap_database[] =
{
    { _blue_buttons_round_edge_icon_button, 0, 60, 60, 7, 6, 46, 46, touchgfx::Bitmap::ARGB8888 },
    { _blue_buttons_round_edge_icon_button_pressed, 0, 60, 60, 7, 6, 46, 46, touchgfx::Bitmap::ARGB8888 },
    { _blue_buttons_round_edge_small, 0, 170, 60, 11, 4, 148, 50, touchgfx::Bitmap::ARGB8888 },
    { _blue_buttons_round_edge_small_pressed, 0, 170, 60, 11, 4, 148, 50, touchgfx::Bitmap::ARGB8888 },
    { _blue_progressindicators_bg_medium_progress_indicator_bg_square_90_degrees, 0, 20, 184, 0, 0, 20, 184, touchgfx::Bitmap::RGB565 }
};

namespace BitmapDatabase
{
const touchgfx::Bitmap::BitmapData* getInstance()
{
    return bitmap_database;
}
uint16_t getInstanceSize()
{
    return (uint16_t)(sizeof(bitmap_database) / sizeof(touchgfx::Bitmap::BitmapData));
}
}

