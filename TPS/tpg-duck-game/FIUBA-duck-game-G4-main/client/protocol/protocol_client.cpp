#include "protocol_client.h"

ClientProtocol::ClientProtocol(Socket& skt): Protocol(skt) {}

void ClientProtocol::receive_cordinates(Coordinate& coordinate) {
    uint16_t x;
    this->receive_2_bytes(x);
    uint16_t y;
    this->receive_2_bytes(y);
    uint16_t h;
    this->receive_2_bytes(h);
    uint16_t w;
    this->receive_2_bytes(w);
    coordinate = Coordinate(x, y, h, w);
}

void ClientProtocol::receive_sprite(sprite_t& sprite) {
    uint8_t id_texture;  // por ahora este me indica el nro de tile de 0 a 63
    this->receive_byte(id_texture);
    Coordinate coordinate;
    receive_cordinates(coordinate);
    sprite = sprite_t{id_texture, coordinate};
}

void ClientProtocol::receive_floor_sprite(floor_sprite_t& sprite) {
    uint8_t path;
    this->receive_byte(path);
    uint8_t id_sprite;
    this->receive_byte(id_sprite);
    Coordinate coordinate;
    receive_cordinates(coordinate);
    sprite = floor_sprite_t{path, id_sprite, coordinate};
}

void ClientProtocol::send_action(uint8_t& id_jugador, ActionEvent& type_action) {
    std::vector<uint8_t> vector_data;
    vector_data.push_back(HEADER_CLIENT);
    vector_data.push_back(id_jugador);
    vector_data.push_back((int)type_action);
    this->skt.sendall(vector_data.data(), vector_data.size(), &this->was_closed);
}

void ClientProtocol::send_init(const uint8_t& init) { this->send_byte(init); }

void ClientProtocol::recv_init(uint8_t& init) { this->receive_byte(init); }

void ClientProtocol::send_server_name(std::string& name) { this->send_string(name); }


void ClientProtocol::receive_inventory(inventory_t& inventory) {
    uint8_t weapon = 0;  // es el "id_arma"
    uint8_t ammo = 0;
    uint8_t armor = 0;
    uint8_t helmet = 0;

    this->receive_byte(weapon);

    if (weapon != 0) {
        this->receive_byte(ammo);
    }
    this->receive_byte(armor);
    this->receive_byte(helmet);

    inventory = inventory_t{weapon, ammo, armor, helmet};
}

void ClientProtocol::receive_players(VectorPlayers& players) {
    uint8_t cantidad_players;
    this->receive_byte(cantidad_players);

    VectorPlayers players_positions;

    for (size_t i = 0; i < cantidad_players; i++) {
        sprite_t sprite;
        receive_sprite(sprite);

        uint8_t is_looking;
        this->receive_byte(is_looking);

        uint8_t state;  // accion del pato. si es 0x0 no hace nada
        this->receive_byte(state);

        uint8_t frame;
        this->receive_byte(frame);

        inventory_t inventory;
        receive_inventory(inventory);
        player_t player_position{sprite, is_looking, state, frame, inventory};
        players_positions.push_back(player_position);
    }

    players = players_positions;
}

// balas -> recibo cantidad y sigo leyendo
void ClientProtocol::receive_bullets(std::vector<bullet_t>& _bullets) {
    uint16_t cantidad_bullets;
    this->receive_2_bytes(cantidad_bullets);

    for (size_t i = 0; i < cantidad_bullets; i++) {
        sprite_t sprite;
        receive_sprite(sprite);
        uint8_t frame = 0x0;
        uint8_t direction = 0x0;
        this->receive_byte(direction);
        bullet_t bullet{sprite, frame, direction};
        _bullets.push_back(bullet);
    }
}


void ClientProtocol::receive_boxes(std::vector<box_t>& _boxes) {
    uint8_t cantidad_boxes;
    this->receive_byte(cantidad_boxes);

    std::vector<box_t> boxes;
    for (size_t i = 0; i < cantidad_boxes; i++) {
        sprite_t sprite;
        receive_sprite(sprite);
        uint8_t frame;
        this->receive_byte(frame);
        box_t box{sprite, frame};
        boxes.push_back(box);
    }

    _boxes = std::move(boxes);
}

void ClientProtocol::receive_floor_sprites(VectorFloorSprite& _floor_sprites) {
    uint8_t cantidad_floor_sprites;
    this->receive_byte(cantidad_floor_sprites);

    VectorFloorSprite sprites;

    for (size_t i = 0; i < cantidad_floor_sprites; i++) {
        floor_sprite_t sprite;
        receive_floor_sprite(sprite);
        sprites.push_back(sprite);
    }

    _floor_sprites = sprites;
}

zoom_t ClientProtocol::receive_zoom_details() {
    uint16_t zoom_min;
    this->receive_2_bytes(zoom_min);
    uint16_t zoom_max;
    this->receive_2_bytes(zoom_max);
    return zoom_t{zoom_min, zoom_max};
}

void ClientProtocol::receive_weapons(VectorGuns& _weapons) {
    uint8_t cantidad_weapons;
    this->receive_byte(cantidad_weapons);

    for (size_t i = 0; i < cantidad_weapons; i++) {
        sprite_t sprite;
        uint8_t frame;

        receive_sprite(sprite);
        receive_byte(frame);
        _weapons.push_back(gun_t{sprite, frame});
    }
}

void ClientProtocol::receive_statistics(game_statistics_t& statistics) {
    uint8_t rounds = 0;
    uint8_t id_winer = 0xFF;
    this->receive_byte(rounds);
    this->receive_byte(id_winer);
    statistics = {rounds, id_winer};
}


void ClientProtocol::receive_game_state(client_game_state_t& game_state) {
    uint8_t moment = 0xFF;
    this->receive_byte(moment);
    VectorPlayers players;
    receive_players(players);
    std::vector<bullet_t> bullets;
    receive_bullets(bullets);
    std::vector<box_t> boxes;
    receive_boxes(boxes);
    VectorFloorSprite sprites;
    receive_floor_sprites(sprites);
    VectorGuns weapons;
    receive_weapons(weapons);
    game_statistics_t statistics;
    receive_statistics(statistics);
    game_state = client_game_state_t{
            static_cast<GameMoment>(moment), players, bullets, boxes, sprites, weapons, statistics};
}

void ClientProtocol::receive_game_data(game_data_t& data) {
    uint8_t cantidad_players;
    this->receive_byte(cantidad_players);
    data.count_players = cantidad_players;

    for (size_t i = 0; i < cantidad_players; i++) {
        uint8_t id_player;
        receive_byte(id_player);
        data.id_players.push_back(id_player);
    }
}
