#include "principal_screen.h"

#include <QApplication>
#include <QFontDatabase>
#include <iostream>

PrincipalScreen::PrincipalScreen() {}

void PrincipalScreen::show_screen() {
    /*
        int id = QFontDatabase::addApplicationFont(
                ":/fonts/fuentes/pixel_digivolve/Pixel_Digivolve.otf");
        std::cout << "id: " << id << "\n";
        if (id == -1) {
            std::cerr << "Error al cargar la tipografía" << std::endl;
            return;
        }

        QStringList fontFamilies = QFontDatabase::applicationFontFamilies(id);

        if (fontFamilies.isEmpty()) {
            std::cerr << "No se encontró ninguna familia para la tipografía" << std::endl;
            return;
        }

        QString fontFamily = fontFamilies.at(0);
        QFont customFont(fontFamily);
        customFont.setPointSize(16);
        QApplication::setFont(customFont);

        screen.show();*/
}
