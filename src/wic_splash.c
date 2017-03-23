#include "wic_splash.h"
const WicColor WIC_SPLASH_BACKGROUND_COLOR = {63,63,63,255};
const WicColor WIC_SPLASH_TEXT_COLOR = {253,144,11,255};
struct WicGame
{
    GLFWwindow* window;
    WicPair dimensions;
    WicPair pixel_density;
    double seconds_per_frame;
    double previous_time;
    double delta;
    FT_Library freetype_library;
    
};
bool wic_draw_splash(WicColor background_color, WicColor text_color,
                     WicGame* game)
{
    if(!game)
        wic_throw_error(WIC_ERRNO_NULL_GAME);
        
    background_color.alpha = 0;
    text_color.alpha = 0;
    
    WicRect background;
    if(!wic_init_rect(&background, (WicPair) {0,0}, game->dimensions,
                      background_color))
       return false;
    double min_dim = fmin(game->dimensions.x, game->dimensions.y);
    WicPair scale_multiplier = wic_divide_pairs((WicPair) {min_dim, min_dim},
                                                (WicPair) {500,500});
    
    unsigned char wic_buffer[] =
    {
        1,0,0,0,1,0,1,0,0,1,1,1,
        1,0,0,0,1,0,1,0,1,0,0,0,
        1,0,1,0,1,0,1,0,1,0,0,0,
        1,1,0,1,1,0,1,0,1,0,0,0,
        1,0,0,0,1,0,1,0,0,1,1,1
    };
    WicTexture* wic_texture = wic_init_texture_from_buffer(wic_buffer,
                                                           (WicPair) {12,5},
                                                           WIC_MONO,
                                                           WIC_NEAREST,
                                                           WIC_REPEAT);
    if(!wic_texture)
       return false;

    WicImage wic;
    WicPair location = wic_divide_pairs(game->dimensions, (WicPair) {2,2});
    if(!wic_init_image(&wic, location, wic_texture))
    {
        wic_free_texture(wic_texture);
        return false;
    }
    wic.scale = wic_multiply_pairs((WicPair) {10,10}, scale_multiplier);
    wic.center = wic_image_get_geo_center(&wic);
    wic.draw_centered = true;
    wic.color = text_color;
    unsigned char engine_buffer[] =
    {
        1,1,1,0,1,0,0,1,0,0,1,1,0,1,0,1,0,0,1,0,1,1,1,
        1,0,0,0,1,1,0,1,0,1,0,0,0,1,0,1,1,0,1,0,1,0,0,
        1,1,1,0,1,0,1,1,0,1,0,1,0,1,0,1,0,1,1,0,1,1,1,
        1,0,0,0,1,0,0,1,0,1,0,1,0,1,0,1,0,0,1,0,1,0,0,
        1,1,1,0,1,0,0,1,0,0,1,1,0,1,0,1,0,0,1,0,1,1,1
    };
    WicTexture* engine_texture = wic_init_texture_from_buffer(engine_buffer,
                                                              (WicPair) {23,5},
                                                              WIC_MONO,
                                                              WIC_NEAREST,
                                                              WIC_REPEAT);
    if(!engine_texture)
    {
        wic_free_texture(wic_texture);
        return false;
    }
    WicImage engine;
    location.x += wic.scale.x * wic_texture_get_dimensions(wic_texture).x / 2;
    location.y -= wic.scale.y * (wic_texture_get_dimensions(wic_texture).y / 2
                                 + 1);
    location = (WicPair) {(int) location.x, (int) location.y};
    if(!wic_init_image(&engine, location, engine_texture))
    {
        wic_free_texture(wic_texture);
        wic_free_texture(engine_texture);
        return false;
    }
    engine.scale = wic_multiply_pairs((WicPair) {2,2}, scale_multiplier);
       engine.center = wic_image_get_geo_center(&engine);
    engine.center.x *= 2;
    engine.draw_centered = true;
    engine.color = text_color;
    unsigned char version_buffer[] =
    {
        0,0,0,1,1,0,0,1,1,
        0,0,0,0,1,0,0,0,1,
        0,0,0,0,1,0,0,0,1,
        1,0,1,0,1,0,0,0,1,
        0,1,0,0,1,0,1,0,1,
    };
    WicTexture* version_texture = wic_init_texture_from_buffer(version_buffer,
                                                               (WicPair) {9,5},
                                                               WIC_MONO,
                                                               WIC_NEAREST,
                                                               WIC_REPEAT);
    if(!version_texture)
    {
        wic_free_texture(wic_texture);
        wic_free_texture(engine_texture);
        return false;
    }
    WicImage version;
    location.y -= engine.scale.y * (wic_texture_get_dimensions(engine_texture).y
                                    / 2 + 1);
    location.y = (int) location.y;
    if(!wic_init_image(&version, location, version_texture))
    {
        wic_free_texture(wic_texture);
        wic_free_texture(engine_texture);
        wic_free_texture(version_texture);
        return false;
    }
    version.scale = wic_multiply_pairs((WicPair) {1.5,1.5}, scale_multiplier);
    version.center = wic_image_get_geo_center(&version);
    version.center.x *= 2;
    version.center.y *= 2;
    version.draw_centered = true;
    version.color = text_color;
    double time;
    int stage = 0;
    while(wic_updt_game(game) == WIC_GAME_CONTINUE)
    {
        if(!stage)
        {
            background.color.alpha += 3;
            wic.color.alpha        += 3;
            engine.color.alpha     += 3;
            version.color.alpha    += 3;
            if(version.color.alpha == 255)
            {
                time = wic_get_time();
                stage++;
            }
        }
        else if(stage == 1 && wic_get_time() - time >= 1.0)
            stage++;
        else if(stage == 2)
        {
            background.color.alpha -= 3;
            wic.color.alpha        -= 3;
            engine.color.alpha     -= 3;
            version.color.alpha    -= 3;
            if(!version.color.alpha)
                break;
        }
        wic_draw_rect(&background, game);
        wic_draw_image(&wic, game);
        wic_draw_image(&engine, game);
        wic_draw_image(&version, game);
    }
    wic_free_texture(version_texture);
    wic_free_texture(engine_texture);
    wic_free_texture(wic_texture);
    return true;
}
