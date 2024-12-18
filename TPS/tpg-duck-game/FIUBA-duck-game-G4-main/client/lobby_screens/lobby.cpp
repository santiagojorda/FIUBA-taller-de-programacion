#include "lobby.h"

#include "./ui_lobby.h"

Lobby::Lobby(std::string hostname, std::string servname, QWidget* parent):
        QWidget(parent), ui(new Ui::Lobby), hostname(hostname), servname(servname) {
    ui->setupUi(this);                          // el actual es index 0
    ui->stackedWidget->insertWidget(1, &form);  // insertamos en index 1
}

Lobby::~Lobby() { delete ui; }

void Lobby::on_buttonExit_clicked() { this->close(); }

void Lobby::on_buttonJoinGame_clicked() {
    form.set_type_screen(NO_HOST);
    form.set_hostname(this->hostname);
    form.set_servname(this->servname);
    form.initialize_screen();
    ui->stackedWidget->setCurrentIndex(1);
}

void Lobby::on_buttonNewGame_clicked() {
    form.set_type_screen(HOST);
    form.set_hostname(this->hostname);
    form.set_servname(this->servname);
    form.initialize_screen();
    ui->stackedWidget->setCurrentIndex(1);
}
