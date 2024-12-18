#include <QApplication>
#include <QFontDatabase>
#include <iostream>

#include "lobby.h"
/**

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);

    int id = QFontDatabase::addApplicationFont(
            ":/fonts/fuentes/pixel_digivolve/Pixel_Digivolve.otf");
    std::cout << "id: " << id << "\n";

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


    Lobby w;
    w.show();
    return a.exec();
}
 */
