#pragma once

/**
 * A sprite is basically an image or an animated sequence of image.
 *
 * Every sprite is fundamentally an rectangle crop of a potentially bigger
 * image containing different frames on rows and columns.
 * In general, the animation is performed on a single row and can loop.
 * Also, every sprite is associated a collision mask, which may or may not
 * coincide with the sprite boundaries.
 *
 * @author Enrico "erolm_a" Trombetta
 * */

#include <SDL_render.h>
#include <SDL_rect.h>
#include <string>
#include "texture.h"

class Sprite
{
    Texture _texture;

    unsigned short _spr_frames {1}; // frame number
    unsigned short _spr_rows {1}; // row number

    SDL_Rect _spr_mask {0, 0, 0, 0};
    SDL_Rect spr_coords {0, 0, 0, 0};
    std::string internal_path;



    // ...

public:
    /** Constructor for empty sprites, i.e. sprites that do not require an
     * image but only a collision mask. Useful for tiles
     *
     * @param x the x-coordinate of the top-left corner
     * @param y the y-coordinate of the top-left corner
     * @param w the width of the collision mask
     * @param h the height of the ocllision mask
     */
    Sprite(int x, int y, int w, int h);

    /** Constructs a sprite given an image, the number or x-frames (or columns) and the number of y-rows
     *
     * @see Sprite::set_sprite
     */
    Sprite(std::string path, unsigned int Xframes = 1,
           unsigned int Yrows = 1);

    ~Sprite();

    /**
     * @brief set_sprite loads a sprite path.
     * @param path the image path
     * @param Xframes the number of frames per row
     * @param Yrows the number of rows
     */
    void set_sprite(std::string path,
                    unsigned int Xframes = 1,
                    unsigned int Yrows = 1);

    /* PHISICAL ATTRIBUTES */

    /**
      The first two values of the collision mask denote the top-left coordinate of
      the mask related to the frame. The latter two represent the width and height,
      respectively. Setting both the x and y coordinate to -1 actually makes the
      mask extend to the whole frame.
    */

    SDL_Rect collision_mask {-1, -1, 0, 0};

    /**
     * depth denotes the priority level of the frame. If the value is lower than
     * another overlapping sprite then this sprite will be in the foreground
     * depth: indica il livello dello sprite rispetto agli altri.
     */
    int depth {0};

    /* Set to true to be visible, false otherwise. This value is ignored if
     * the sprite has no corresponding frame */
    bool visible {true};

    /** speed regulates the frame update rate. If the value is n (n > 0) then
     * the frame get replaced after n window refreshes. That means 1 is the fastest
     * rate available, 2 is half the speed and so on.
     */
    unsigned int speed{};


    int width() const {return _spr_mask.w;}
    int height() const {return _spr_mask.h;}

    int &x = spr_coords.x;
    int &y = spr_coords.y;

    // set_frame cambia il fotogramma. L'argomento è un numero che parte da
    // 0 fino a _spr_frames meno 1.

    /* MAKEUP ATTRIBUTES */

    /**
     * @brief set_frame changes the frame. This does not halt the animation.
     * @param frame the frame number
     */
    void set_frame(unsigned short frame);
    /**
     * @brief set_row
     * @param row
     */
    void set_row(unsigned short row);

    // riflessione dell'immagine
    // nota: l'operazione è pulita, non richiede modifiche alla texture
    void no_flip() {_texture.flip_mode = flipping::none;}
    void flip_vertical() {_texture.flip_mode = flipping::vertical;}
    void flip_horizontal() {_texture.flip_mode = flipping::horizontal;}
    bool is_flipped() const {return _texture.flip_mode != flipping::none;}

    /** SPRITE INTERSECTION */

    /**
     * @brief extract_mask extracts the intersection mask used to check for collisions.
     * @return If the collision mask is not set, return the translated frame size,
     *         else the translated collision mask.
     */
    SDL_Rect extract_mask() const;

    /**
     * @brief collide check whether two sprites are colliding.
     *        This version avoids the overhead of instantiating another
     *        temporary sprite for a check
     * @param other a rectangle denoting the position of an object and its size.
     * @return true if this sprite collides with other, false otherwise
     */
    bool collide (const SDL_Rect& other);


    /** PRIVATE USE FOR RENDERING ONLY */
    void _update_sprite();
    void _draw_sprite(const SDL_Rect &camera);
};

/**
 * @brief collide check whether two sprites are colliding
 * @param a the first sprite
 * @param b the second sprite
 * @return true if colliding, false otherwise
 */
bool collide (const Sprite& a, const Sprite& b);

