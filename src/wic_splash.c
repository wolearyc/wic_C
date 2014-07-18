#include "wic_splash.h"
const WicColor WIC_SPLASH_BACKGROUND_COLOR = {63,63,63,255};
const WicColor WIC_SPLASH_TEXT_COLOR = {253,144,11,255};
enum WicError wic_draw_splash(WicColor background_color, WicColor text_color,
                              WicGame* game)
{
    background_color.alpha = 0;
    text_color.alpha = 0;
    if(game == 0)
        return wic_report_error(WICER_GAME);
    enum WicError result;
    WicQuad background;
    result = wic_init_quad(&background, (WicPair) {0,0}, game->p_dimensions,
                           background_color);
    if(result != WICER_NONE)
        return result;
    double min_dimension = fmin(game->p_dimensions.x, game->p_dimensions.y);
    WicPair scale_multiplier = wic_divide_pairs((WicPair) {min_dimension,
                                                           min_dimension},
                                                (WicPair) {500,500});
    
    unsigned char wic_buffer[] =
    {
        1,0,0,0,1,0,1,0,0,1,1,1,
        1,0,0,0,1,0,1,0,1,0,0,0,
        1,0,1,0,1,0,1,0,1,0,0,0,
        1,1,0,1,1,0,1,0,1,0,0,0,
        1,0,0,0,1,0,1,0,0,1,1,1
    };
    WicTexture wic_texture;
    result = wic_init_texture_from_buffer(&wic_texture, wic_buffer,
                                          (WicPair) {12,5}, WIC_MONO,
                                          WIC_NEAREST, WIC_REPEAT);
    if(result != WICER_NONE)
    {
        wic_free_quad(&background);
        return result;
    }
    WicImage wic;
    WicPair  location = wic_divide_pairs(game->p_dimensions, (WicPair) {2,2});
    result = wic_init_image(&wic, location, &wic_texture);
    if(result != WICER_NONE)
    {
        wic_free_quad(&background);
        wic_free_texture(&wic_texture);
        return result;
    }
    wic.scale = wic_multiply_pairs((WicPair) {10,10}, scale_multiplier);
    wic.center = wic.p_geometric_center;
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
    WicTexture engine_texture;
    result = wic_init_texture_from_buffer(&engine_texture, engine_buffer,
                                          (WicPair) {23,5}, WIC_MONO,
                                          WIC_NEAREST, WIC_REPEAT);
    if(result != WICER_NONE)
    {
        wic_free_quad(&background);
        wic_free_texture(&wic_texture);
        wic_free_image(&wic);
        return result;
    }
    WicImage engine;
    location.x += wic.scale.x * wic_texture.p_dimensions.x / 2;
    location.y -= wic.scale.y * (wic_texture.p_dimensions.y / 2  + 1);
    location = (WicPair) {(int) location.x, (int) location.y};
    result = wic_init_image(&engine, location, &engine_texture);
    if(result != WICER_NONE)
    {
        wic_free_quad(&background);
        wic_free_texture(&wic_texture);
        wic_free_image(&wic);
        wic_free_texture(&engine_texture);
        return result;
    }
    engine.scale = wic_multiply_pairs((WicPair) {2,2}, scale_multiplier);
    engine.center = engine.p_geometric_center;
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
    WicTexture version_texture;
    result = wic_init_texture_from_buffer(&version_texture, version_buffer,
                                          (WicPair) {9,5}, WIC_MONO,
                                          WIC_NEAREST, WIC_REPEAT);
    if(result != WICER_NONE)
    {
        wic_free_quad(&background);
        wic_free_texture(&wic_texture);
        wic_free_image(&wic);
        wic_free_texture(&engine_texture);
        wic_free_image(&engine);
        return result;
    }
    WicImage version;
    location.y -= engine.scale.y * (engine_texture.p_dimensions.y / 2 + 1);
    location.y = (int) location.y;
    result = wic_init_image(&version, location, &version_texture);
    if(result != WICER_NONE)
    {
        wic_free_quad(&background);
        wic_free_texture(&wic_texture);
        wic_free_image(&wic);
        wic_free_texture(&engine_texture);
        wic_free_image(&engine);
        wic_free_texture(&version_texture);
        return result;
    }
    version.scale = wic_multiply_pairs((WicPair) {1.5,1.5}, scale_multiplier);
    version.center = version.p_geometric_center;
    version.center.x *= 2;
    version.center.y *= 2;
    version.draw_centered = true;
    version.color = text_color;
    double time;
    int stage = 0;
    while(wic_updt_game(game))
    {
        if(stage == 0)
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
            if(version.color.alpha == 0)
                break;
        }
        wic_draw_quad(&background, game);
        wic_draw_image(&wic, game);
        wic_draw_image(&engine, game);
        wic_draw_image(&version, game);
    }
    wic_free_image(&version);
    wic_free_texture(&version_texture);
    wic_free_image(&engine);
    wic_free_texture(&engine_texture);
    wic_free_image(&wic);
    wic_free_texture(&wic_texture);
    wic_free_quad(&background);
    return wic_report_error(WICER_NONE);
}
