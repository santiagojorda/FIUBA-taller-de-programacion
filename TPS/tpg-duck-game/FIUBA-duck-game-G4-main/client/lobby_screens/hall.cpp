#include "hall.h"

#include "ui_hall.h"

Hall::Hall(QWidget* parent): QWidget(parent), ui(new Ui::Hall) { ui->setupUi(this); }

void Hall::set_config_game(std::tuple<int, std::string, std::string, int> config) {
    this->type_screen = std::get<0>(config);
    this->hostname = std::get<1>(config);
    this->port = std::get<2>(config);
    this->cant_players = std::get<3>(config);
}

void Hall::call_clients() {
    if (this->type_screen == NO_HOST) {
        data_for_client();
    } else if (this->type_screen == HOST) {
        data_for_host();
    }
}

void Hall::data_for_host() {
    try {
        Socket new_skt(this->hostname.c_str(), this->port.c_str());
        /*ClientProtocol protocol(new_skt);
        std::unique_ptr<ClientReceiverLobby> receiver_lobby =
                std::make_unique<ClientReceiverLobby>(protocol, this->game_data);
        this->set_receiver(std::move(receiver_lobby));
        this->receiver->start();*/
        std::unique_ptr<Client> client = std::make_unique<Client>(std::move(new_skt), cant_players);
        this->set_client(std::move(client));
        this->client->run();

    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        std::cerr << "Error en data_for_host: " << e.what() << "\n";
    }
}

void Hall::set_client(std::unique_ptr<Client>&& client) { this->client = std::move(client); }


void Hall::data_for_client() {
    Socket skt(this->hostname.c_str(), this->port.c_str());
    std::unique_ptr<Client> client = std::make_unique<Client>(std::move(skt), cant_players);
    this->set_client(std::move(client));
    this->client->run();
    this->client->active_drawer();
    QApplication::quit();
}

void Hall::initialize_screen() {
    if (!is_initialized) {
        is_initialized = true;
        if (this->cant_players == 1) {
            ui->containerTwoPlayers->hide();
        } else {
            ui->containerOnlyOnePlayer->hide();
        }

        if (this->type_screen == 1) {
            ui->buttonStartGame->hide();
        } else {
            ui->labelWaiting->hide();
        }
    }
}

Hall::~Hall() { delete ui; }

void Hall::on_buttonStartGame_clicked() {
    Socket skt_dumy(this->hostname.c_str(), this->port.c_str());
    ClientProtocol protocol(skt_dumy);
    protocol.send_init(0xFF);
    close();
    this->client->active_drawer();
}
