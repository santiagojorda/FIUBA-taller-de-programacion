#ifndef CLIENT_PROTOCOL_H
#define CLIENT_PROTOCOL_H

#include <string>
#include <vector>

#include "../../common/action_events.h"
#include "../../common/coordinate.h"
#include "../../common/protocol.h"
#include "../../common/socket.h"
#include "../game_state/client_game_state.h"
#include "../lobby/game_data.h"
#include "../zoom/zoom.h"

class ClientProtocol: public Protocol {
private:
    zoom_t receive_zoom_details();

    void receive_weapons(VectorGuns& weapons);

    void receive_cordinates(Coordinate& coordinate);

    void receive_players(VectorPlayers& players);

    void receive_bullets(std::vector<bullet_t>& bullets);

    void receive_boxes(std::vector<box_t>& boxes);

    void receive_floor_sprites(VectorFloorSprite& floor_sprites);

    void receive_sprite(sprite_t& sprite);

    void receive_inventory(inventory_t& inventory);

    void receive_floor_sprite(floor_sprite_t& sprite);

    void receive_statistics(game_statistics_t& statistics);


public:
    /*
     * Constructor.
     */
    explicit ClientProtocol(Socket& skt);

    /*
     * Envia el mensaje de inicio, siendo este la cantidad de jugadores en el juego.
     */
    void send_init(const uint8_t& init);


    /*
     * recive el mensaje de inicio, siendo este la cantidad de jugadores en el juego.
     */
    void recv_init(uint8_t& init);

    /*
     * recive el mensaje de inicio, siendo este la cantidad de jugadores en el juego.
     */
    void send_server_name(std::string& name);

    /*
     *
     */
    void send_action(uint8_t& id_jugador, ActionEvent& type_action);


    /*
     *
     */
    void receive_game_state(client_game_state_t& game_state);

    void receive_game_data(game_data_t& data);

    /*
     * Deshabilitar copias.
     */
    ClientProtocol(const ClientProtocol&) = delete;
    ClientProtocol& operator=(const ClientProtocol&) = delete;
};

#endif  // CLIENT_PROTOCOL_H
