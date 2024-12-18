#include "zoom_handler.h"

#define WINDOW_HEIGHT 500
#define WINDOW_WIDTH 800

#define OFFSET 100

ZoomHandler::ZoomHandler(): dest_x(0), dest_y(0), factor_zoom(0.0) {}

void ZoomHandler::calculate_zoom(const VectorPlayers& players) {
    if (players.empty())
        return;

    auto [min_x, max_x, min_y, max_y] = calculate_bounds(players);
    int ancho = max_x - min_x;
    int altura = max_y - min_y;

    calculate_zoom_factor(ancho, altura);

    scaled_width = WINDOW_WIDTH * factor_zoom;
    scaled_height = WINDOW_HEIGHT * factor_zoom;
    int center_x = (min_x + max_x) / 2;
    int center_y = (min_y + max_y) / 2;
    dest_x = WINDOW_WIDTH / 2 - (center_x * factor_zoom);
    dest_y = WINDOW_HEIGHT / 2 - (center_y * factor_zoom);
}

void ZoomHandler::apply_zoom(SDL2pp::Renderer& renderer, SDL2pp::Texture& texture) {
    SDL2pp::Rect zoom_rect(dest_x, dest_y, scaled_width, scaled_height);
    renderer.Copy(texture, SDL2pp::NullOpt, zoom_rect);
}

std::tuple<int, int, int, int> ZoomHandler::calculate_bounds(const VectorPlayers& players) const {
    int min_x = players[0].sprite.coordinate.get_x();
    int max_x = players[0].sprite.coordinate.get_x();
    int min_y = players[0].sprite.coordinate.get_y();
    int max_y = players[0].sprite.coordinate.get_y();

    for (const auto& player: players) {
        // No tiene en cuenta a los patos muertos
        if (static_cast<DuckStateType>(player.state) == DuckStateType::DEAD) {
            continue;
        }
        int x = player.sprite.coordinate.get_x();
        int y = player.sprite.coordinate.get_y();
        min_x = std::min(min_x, x);
        max_x = std::max(max_x, x);
        min_y = std::min(min_y, y);
        max_y = std::max(max_y, y);
    }
    return {min_x, max_x, min_y, max_y};
}

void ZoomHandler::calculate_zoom_factor(int ancho, int altura) {
    float zoom_x = ancho != 0 ? static_cast<float>(WINDOW_WIDTH) / (ancho + OFFSET) : 0;
    float zoom_y = altura != 0 ? static_cast<float>(WINDOW_HEIGHT) / (altura + OFFSET) : 0;

    if (zoom_x != 0 && zoom_y != 0) {
        factor_zoom = std::min(zoom_x, zoom_y);
    } else {
        factor_zoom = (zoom_x == 0) ? zoom_y : zoom_x;
    }

    if (factor_zoom == 0 || factor_zoom >= 2.5f) {
        factor_zoom = 2.5f;
    }
}
