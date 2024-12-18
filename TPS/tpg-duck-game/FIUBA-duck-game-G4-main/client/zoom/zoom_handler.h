#ifndef ZOOM_HANDLER_H
#define ZOOM_HANDLER_H

#include <vector>

#include <SDL2pp/SDL2pp.hh>

#include "../../common/state_duck.h"
#include "../game_state/vector_player.h"

class ZoomHandler {
private:
    int dest_x;
    int dest_y;
    float factor_zoom;
    int scaled_width;
    int scaled_height;

    std::tuple<int, int, int, int> calculate_bounds(const VectorPlayers& players) const;
    void calculate_zoom_factor(int ancho, int altura);

public:
    /*
     * Constructor.
     */
    ZoomHandler();

    void calculate_zoom(const VectorPlayers& players);

    void apply_zoom(SDL2pp::Renderer& renderer, SDL2pp::Texture& texture);

    /*
     * Deshabilitar copias.
     */
    ZoomHandler(const ZoomHandler&) = delete;
    ZoomHandler& operator=(const ZoomHandler&) = delete;
};

#endif  // ZOOM_HANDLER_H
