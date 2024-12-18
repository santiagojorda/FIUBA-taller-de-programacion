#include "form.h"

#include <chrono>
#include <thread>

#include "../lobby/client_receiver_lobby.h"
#include "../lobby/game_data.h"

#include "ui_form.h"

Form::Form(QWidget* parent):
        QWidget(parent), ui(new Ui::Form), hostname(""), servname(""), port(""), cant_players(0) {

    ui->setupUi(this);
    ui->stackedWidgetForm->insertWidget(1, &hall);
    ui->labelErrorHostname->clear();
    ui->labelErrorPort->clear();
    ui->labelErrorNumberPlayers->clear();
}

void Form::set_type_screen(int type_screen) { this->type_screen = type_screen; }

void Form::set_hostname(std::string _hostname) { this->hostname = _hostname; }

void Form::set_servname(std::string _servname) { this->servname = _servname; }

Form::~Form() { delete ui; }

bool Form::validate_form() {
    QString _hostname = ui->inputHostname->text();
    QString _port = ui->inputPort->text();
    this->cant_players = ui->spinNumberPlayers->value();
    this->hostname = _hostname.toStdString();
    this->port = _port.toStdString();
    bool is_valid = true;

    if (hostname == "") {
        ui->labelErrorHostname->setText("Ingrese un hostname");
        is_valid = false;
    } else {
        ui->labelErrorHostname->clear();
    }

    if (port == "") {
        ui->labelErrorPort->setText("Ingrese port");
        is_valid = false;
    } else {
        ui->labelErrorPort->clear();
    }

    if (cant_players == 0) {
        ui->labelErrorNumberPlayers->setText("Ingrese un numero de jugadores");
        is_valid = false;
    } else if (cant_players > 2) {
        ui->labelErrorNumberPlayers->setText("Cantidad maxima de jugadores: 2");
        is_valid = false;
    } else {
        ui->labelErrorNumberPlayers->clear();
    }

    return is_valid;
}

void Form::on_buttonContinue_clicked() {
    if (validate_form()) {
        hall.set_config_game(
                std::make_tuple(this->type_screen, this->hostname, this->port, this->cant_players));
        hall.initialize_screen();

        Socket skt(this->hostname.c_str(), this->servname.c_str());
        ClientProtocol protocol(skt);

        if (this->type_screen == HOST) {
            protocol.send_init(0);                  // se une como host
            protocol.send_server_name(this->port);  // le mando el server ingresado por pantalla
        } else {                                    // es cliente normal
            uint8_t byte_commad = 1;
            protocol.send_init(byte_commad);  // se une
            protocol.recv_init(
                    byte_commad);  // cantidad de partidas abiertas (falta envio de puertos)
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));
        hall.call_clients();
        ui->stackedWidgetForm->setCurrentIndex(1);
    }
}

void Form::initialize_screen() {
    if (!is_initialized) {
        is_initialized = true;
    }
}

void Form::on_inputHostname_textChanged(const QString& arg1) {
    (void)arg1;
    ui->labelErrorHostname->clear();
}


void Form::on_inputPort_textChanged(const QString& arg1) {
    (void)arg1;
    ui->labelErrorPort->clear();
}


void Form::on_spinNumberPlayers_valueChanged(int arg1) {
    (void)arg1;
    ui->labelErrorNumberPlayers->clear();
}
