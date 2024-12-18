#ifndef FORM_H
#define FORM_H

#include <QPainter>
#include <QWidget>
#include <memory>
#include <stdexcept>

#include "../../common/socket.h"
#include "../client.h"
#include "../protocol/protocol_client.h"

#include "constants_lobby.h"
#include "hall.h"

namespace Ui {
class Form;
}

class Form: public QWidget {
    Q_OBJECT

public:
    explicit Form(QWidget* parent = nullptr);
    ~Form();
    void set_type_screen(int type_screen);
    void set_hostname(std::string _hostname);
    void set_servname(std::string _servname);

    void initialize_screen();

private slots:
    void on_buttonContinue_clicked();

    void on_inputHostname_textChanged(const QString& arg1);

    void on_inputPort_textChanged(const QString& arg1);

    void on_spinNumberPlayers_valueChanged(int arg1);

private:
    Ui::Form* ui;
    Hall hall;
    std::string hostname;
    std::string servname;

    std::string port;
    int cant_players;
    int type_screen;
    bool is_initialized = false;

    bool validate_form();
};

#endif  // FORM_H
