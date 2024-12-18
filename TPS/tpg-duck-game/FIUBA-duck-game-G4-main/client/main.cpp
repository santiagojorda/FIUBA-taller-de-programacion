#include <exception>
#include <iostream>
#include <QApplication>
#include <QFontDatabase>
#include "lobby_screens/lobby.h"
#include "client_host.h"

#define ARGS_EXPECTED_CLIENT 3
#define SUCCESS 0
#define ERROR -1

int main(int argc, char* argv[]) {
    try {
        if (argc != ARGS_EXPECTED_CLIENT) {
            std::cerr << "Cantidad de argumentos inválido" << std::endl;
            return ERROR;
        }
        
        std::string hostname = argv[1];
        std::string servname = argv[2];
        QApplication a(argc, argv);

        int id = QFontDatabase::addApplicationFont(
                ":/fonts/fuentes/pixel_digivolve/Pixel_Digivolve.otf");

        if (id == -1) {
            std::cerr << "Error al cargar la tipografía" << std::endl;
            return -1;
        }

        QStringList fontFamilies = QFontDatabase::applicationFontFamilies(id);

        if (fontFamilies.isEmpty()) {
            std::cerr << "No se encontró ninguna familia para la tipografía" << std::endl;
            return -1;
        }

        QString fontFamily = fontFamilies.at(0);
        QFont customFont(fontFamily);
        customFont.setPointSize(16);
        QApplication::setFont(customFont);

        Lobby w(hostname, servname);
        w.show();
        return a.exec();
    } catch (const std::exception& e) {
        std::cerr << "Ocurrió un problema: " << e.what() << '\n';
        return ERROR;
    } catch (...) {
        std::cerr << "Ocurrió un problema y una excepción desconocida fue capturada.\n";
        return ERROR;
    }
}
