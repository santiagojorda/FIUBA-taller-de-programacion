#ifndef HALL_H
#define HALL_H

#include <QWidget>

#include "../../common/queue.h"
#include "../../common/socket.h"
#include "../client.h"
#include "../lobby/game_data.h"
#include "../protocol/protocol_client.h"

#include "constants_lobby.h"

namespace Ui {
class Hall;
}

class Hall: public QWidget {
    Q_OBJECT

public:
    explicit Hall(QWidget* parent = nullptr);
    ~Hall();
    void set_config_game(std::tuple<int, std::string, std::string, int> config);
    void initialize_screen();
    void data_for_host();
    void data_for_client();
    void set_client(std::unique_ptr<Client>&& client);
    void set_receiver(std::unique_ptr<ClientReceiverLobby>&& receiver);

    void call_clients();


private slots:
    void on_buttonStartGame_clicked();

private:
    Ui::Hall* ui;
    int type_screen;
    std::string hostname;
    std::string port;
    int cant_players;
    bool is_initialized = false;
    std::unique_ptr<Client> client;
    // std::unique_ptr<ClientReceiverLobby> receiver;
    Queue<game_data_t> game_data;
    // std::unique_ptr<ClientProtocol> protocol;
};

#endif  // HALL_H
