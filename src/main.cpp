#include <iostream>
#include "MailManager.h"
#include "lectorDeMails.h"


inline void bienvenida();

int main() {
    bienvenida();
    MailManager MM;
    vector<email> mails = load_mm("../test/mails-3001.txt");

    for (int j = 0; j < mails.size(); ++j) {
        MM.addMail(mails[j]);
        mails[j].imprimir(false, false);
        cout << endl << j << endl;
    }

    bool mostContenido = false;
    bool mostID = false;
    int n, i, config, imp;
    unsigned long ID;
    vector<email> v;
    string anio, mes, dia, desde, hasta, rem, pal;
    do {
        cout << endl << "Seleccione una opcion:" << endl
             << " 1)Mostrar mails ordenados por fecha" << endl
             << " 2)Mostrar mails ordenados por fecha (con rango)" << endl
             << " 3)Mostrar mails ordenados por remitentes" << endl
             << " 4)Buscar mails por remitente" << endl
             << " 5)Buscar mails por palabra" << endl
             << " 6)Eliminar mail" << endl
             << " 7)Configuraciones" << endl
             << " 8)Imprimir arboles" << endl
             << " 9)Salir" << endl;
        cin >> n;
        switch (n) {
            case 1:
                v = MM.getSortedByDate();
                if (v.empty())
                    cout << "\nNo hay emails\n";
                else {
                    for (i = 0; i < v.size(); ++i)
                        v[i].imprimir(mostID, mostContenido);
                    cout << i << endl;
                }
                break;

            case 2:
                anio = "0000";
                mes = "00";
                dia = "00";
                desde = "";
                hasta = "";
                cout << endl << "Ingrese desde que fecha buscar:";
                cout << endl << " Ingrese anio: " << endl;
                cin >> anio;
                while (anio.size() < 4)
                    anio = "0" + anio;
                cout << endl << " Ingrese mes: " << endl;
                cin >> mes;
                while (mes.size() < 2)
                    mes = "0" + mes;
                cout << endl << " Ingrese dia: " << endl;
                cin >> dia;
                while (dia.size() < 2)
                    dia = "0" + dia;
                desde += anio;
                desde += mes;
                desde += dia;
                cout << endl << "Ingrese hasta que fecha buscar:";
                cout << endl << " Ingrese anio: " << endl;
                cin >> anio;
                while (anio.size() < 4)
                    anio = "0" + anio;
                cout << endl << " Ingrese mes: " << endl;
                cin >> mes;
                while (mes.size() < 2)
                    mes = "0" + mes;
                cout << endl << " Ingrese dia: " << endl;
                cin >> dia;
                while (dia.size() < 2)
                    dia = "0" + dia;
                hasta += anio;
                hasta += mes;
                hasta += dia;
                try {
                    v = MM.getSortedByDate(desde, hasta);
                    if (v.empty())
                        cout << "\nNo se encontraron mails en este rango\n";
                    else {
                        for (i = 0; i < v.size(); ++i)
                            v[i].imprimir(mostID, mostContenido);
                        cout << i << endl;
                    }
                } catch (int e) {
                    if (e == -50)
                        cout << "\nFechas invalidas\n";
                    if (e == -10)
                        cout << "\nPrimera fecha invalida\n";
                    if (e == -20)
                        cout << "\nSegunda fecha invalida\n";
                    if (e == -8)
                        cout << "\nLas fehcas ingresadas no conforman un rango válido\n";
                }
                break;

            case 3:
                v = MM.getSortedByFrom();
                if (v.empty())
                    cout << "No hay emails\n";
                else {
                    for (i = 0; i < v.size(); ++i)
                        v[i].imprimir(mostID, mostContenido);
                    cout << i << endl;
                }
                break;

            case 4:
                cout << endl << "Ingrese remitente a buscar:" << endl;
                cin >> rem;
                try {
                    v = MM.getByFrom(rem);
                    for (i = 0; i < v.size(); ++i)
                        v[i].imprimir(mostID, mostContenido);
                    cout << i << endl;
                } catch (int e) {
                    if (e == -5)
                        cout << "\nNo hay emails\n";
                    if (e == -1)
                        cout << "\nNo se encontro el remitente buscado\n";
                }
                break;

            case 5:
                cout << endl << "Ingrese palabra a buscar:" << endl;
                cin >> pal;
                try {
                    v = MM.getByQuery(pal);
                    for (i = 0; i < v.size(); ++i)
                        v[i].imprimir(mostID, mostContenido);
                    cout << i << endl;
                } catch (int e) {
                    if (e == -5)
                        cout << "\nNo hay emails\n";
                    if (e == -1)
                        cout << "\nNo se encontro la palabra buscada\n";
                }
                break;

            case 6:
                cout << endl << "Ingrese el id del email a eliminar:" << endl;
                cin >> ID;
                try {
                    MM.deleteMail(ID);
                    cout << "\nMail ID:" << ID << " eliminado\n";
                } catch (int e) {
                    if (e == -5)
                        cout << "\nNo se encontro email con el ID ingresado\n";
                }
                break;

            case 7:
                do {
                    cout << endl << "Seleccione una opcion:" << endl;
                    if (mostContenido)
                        cout << " 1)Ocultar contenido" << endl;
                    else
                        cout << " 1)Mostrar contenido" << endl;
                    if (mostID)
                        cout << " 2)Ocultar ID" << endl;
                    else
                        cout << " 2)Mostrar ID" << endl;
                    cout << " 3)Volver" << endl;
                    cin >> config;
                    switch (config) {
                        case 1:
                            if (mostContenido)
                                mostContenido = false;
                            else
                                mostContenido = true;
                            break;
                        case 2:
                            if (mostID)
                                mostID = false;
                            else
                                mostID = true;
                            break;
                        case 3:
                            break;
                        default:
                            cout << "\nOpcion incorrecta\n";
                            break;
                    }
                } while (config != 3);
                break;

            case 8:
                do {
                    cout << endl << "Seleccione una opcion:" << endl
                         << " 1)Imprimir arbol de IDs" << endl
                         << " 2)Imprimir arbol de Fechas" << endl
                         << " 3)Imprimir arbol de Remitentes" << endl
                         << " 4)Imprimir arbol de Palabras" << endl
                         << " 5)Volver" << endl;
                    cin >> imp;
                    switch (imp) {
                        case 1:
                            cout << endl << endl;
                            MM.printArbolIDs();
                            cout << endl << endl;
                            break;
                        case 2:
                            cout << endl << endl;
                            MM.printArbolFechas();
                            cout << endl << endl;
                            break;
                        case 3:
                            cout << endl << endl;
                            MM.printArbolRemitentes();
                            cout << endl << endl;
                            break;
                        case 4:
                            cout << endl << endl;
                            MM.printArbolPalabras();
                            cout << endl << endl;
                            break;
                        case 5:
                            break;
                        default:
                            cout << "\nOpcion incorrecta\n";
                            break;
                    }
                } while (imp != 5);
                break;
            case 9:
                break;

            default:
                cout << "\nOpcion incorrecta\n";
                break;
        }
    } while (n != 9);
    cout << endl << "-----------------GRACIAS POR USAR HERMES MAIL-----------------" << endl;
    return 0;
}

inline void bienvenida() {
    cout
            << "                                                                                                                                                        \n"
                    " .@@@@@@@@@     +@@@@@@@@@@  @@@@@@@@@@@@@@@@@@.    @@@@@@@@@@@@@@@          @@@@@@@@                @@@@@@@  @@@@@@@@@@@@@@@@@@@          @@@@@@@@@@@  \n"
                    "     @@@            @@@`        @@@+       `;@@.       @@@     `@@@@@`          @@@@@               @@@@@        @@@@        ,;@@        @@@       @@@  \n"
                    "     @@@            @@@`        @@@+          @.       @@@        @@@@          @@@@@               @@@@@        @@@@          @@       @@@         @@  \n"
                    "     @@@            @@@`        @@@+          @.       @@@         @@@@         @@@@@@             :@@@@@        @@@@          ;@      ,@@          @@  \n"
                    "     @@@            @@@`        @@@+          @.       @@@         @@@@         @@@@@@             @@ @@@        @@@@           @      @@@          @@  \n"
                    "     @@@            @@@`        @@@+          @.       @@@          @@@:        @@ @@@@            @' @@@        @@@@           @      @@@              \n"
                    "     @@@            @@@`        @@@+                   @@@          @@@;        @@  @@@           @@  @@@        @@@@                  @@@'             \n"
                    "     @@@            @@@`        @@@+                   @@@          @@@         @@  @@@@         @@;  @@@        @@@@                  @@@@`            \n"
                    "     @@@            @@@`        @@@+      @@           @@@         ;@@@         @@  @@@@         @@   @@@        @@@@       @           @@@@@           \n"
                    "     @@@            @@@`        @@@+      @@           @@@         @@@`         @@   @@@        '@@   @@@        @@@@       @           @@@@@@@+        \n"
                    "     @@@            @@@`        @@@+      @@           @@@        '@@@          @@   @@@@       @@    @@@        @@@@       @            @@@@@@@@@@     \n"
                    "     @@@@@@@@@@@@@@@@@@`        @@@@@@@@@@@@           @@@      +@@@@           @@   @@@@@      @@    @@@        @@@@@@@@@@@@              @@@@@@@@@    \n"
                    "     @@@            @@@`        @@@+      @@           @@@@@@@@@@@@             @@    @@@@     @@     @@@        @@@@       @                ;@@@@@@@@  \n"
                    "     @@@            @@@`        @@@+      @@           @@@    `@@@@             @@    ;@@@    @@#     @@@        @@@@       @                   @@@@@@  \n"
                    "     @@@            @@@`        @@@+      @@           @@@      @@@+            @@     @@@@   @@      @@@        @@@@       @                     ;@@@@ \n"
                    "     @@@            @@@`        @@@+                   @@@      @@@@            @@     @@@@@  @@      @@@        @@@@                               @@@ \n"
                    "     @@@            @@@`        @@@+                   @@@       @@@.           @@      @@@@ .@       @@@        @@@@                               @@@ \n"
                    "     @@@            @@@`        @@@+            '      @@@        @@@;          @@      @@@@ @+       @@@        @@@@            '     @'           @@@ \n"
                    "     @@@            @@@`        @@@+            @      @@@        @@@@          @@      @@@@@@        @@@        @@@@            @     @@           @@@ \n"
                    "     @@@            @@@`        @@@+           @@      @@@         @@@@         @@       @@@@@        @@@        @@@@            @     @@           @@@ \n"
                    "     @@@            @@@`        @@@+           @@      @@@          @@@@        @@        @@@:        @@@        @@@@           @@     @@          `@@  \n"
                    "     @@@            @@@`        @@@+           @@      @@@          @@@@+       @@        @@@         @@@        @@@@           @@     @@@.       '@@#  \n"
                    "   @@@@@@#        @@@@@@@`    @@@@@@@@@@@@@@@@@@@    @@@@@@@;        @@@@@+   '@@@@@      ,@       ,@@@@@@@     @@@@@@@@@@@@@@@@@@     @@@@@@; :@@@@    \n"
                    " .@@@@@@@@@     +@@@@@@@@@@  @@@@@@@@@@@@@@@@@@@#   @@@@@@@@@@       @@@@@@@ @@@@@@@@      @      @@@@@@@@@@  @@@@@@@@@@@@@@@@@@@@       @@@@@@@@@@`    \n"
                    "                                                                                                                                                        \n"
                    "                                                                                                                                                        \n"
                    "                                                                                                                                                        \n"
                    "                              @@@@@@@@               ;@@@@@@@            @@@@@             @@@@@@@@@@  @@@@@@@@@@                                       \n"
                    "                                 @@@@@               @@@@@               @@@@@                @@@,        @@@@                                          \n"
                    "                                 @@@@@@             @@@@@@              .@@@@@'               @@@,        @@@@                                          \n"
                    "                                 @@@@@@             @@@@@@              @@ @@@@               @@@,        @@@@                                          \n"
                    "                                 @@.@@@             @@@@@@              @@  @@@               @@@,        @@@@                                          \n"
                    "                                 @@ @@@@           @@ @@@@             `@   @@@               @@@,        @@@@                                          \n"
                    "                                 @@ @@@@          @@@ @@@@             @@   @@@@              @@@,        @@@@                                          \n"
                    "                                 @@  @@@@         @@  @@@@            +@@   :@@@              @@@,        @@@@                                          \n"
                    "                                 @@  @@@@         @@  @@@@            @@     @@@@             @@@,        @@@@                                          \n"
                    "                                 @@   @@@@       @@   @@@@            @@     +@@@             @@@,        @@@@                                          \n"
                    "                                 @@   @@@@       @    @@@@           ;@@      @@@+            @@@,        @@@@                                          \n"
                    "                                 @@    @@@      .@    @@@@           @@       @@@@            @@@,        @@@@                                          \n"
                    "                                 @@    @@@@     @@    @@@@          '@.        @@@            @@@,        @@@@                                          \n"
                    "                                 @@     @@@     @     #@@@          @@         @@@:           @@@,        @@@@                                          \n"
                    "                                 @@     @@@@   @@     #@@@          @@@@@@@@@@@@@@@           @@@,        @@@@                                          \n"
                    "                                 @@     +@@@  @@,     #@@@          @'         '@@@@          @@@,        @@@@                                          \n"
                    "                                 @@      @@@@ @@      #@@@         @@           @@@@          @@@,        @@@@           `;                             \n"
                    "                                 @@      @@@@;@@      #@@@         @@           @@@@          @@@,        @@@@           @.                             \n"
                    "                                 @@      :@@@@@       #@@@         @             @@@@         @@@,        @@@@           @                              \n"
                    "                                 @@       @@@@+       +@@@        @@             @@@@         @@@,        @@@@           @                              \n"
                    "                                 @@       @@@@        +@@@        @@             @@@@         @@@,        @@@@           @                              \n"
                    "                                 @@        @@@        +@@@       `@;              @@@.        @@@,        @@@@          @@                              \n"
                    "                              @@@@@@@@     `@      @@@@@@@@@@ @@@@@@@@         @@@@@@@@@@  @@@@@@@@@@  @@@@@@@@@@@@@@@@@@@                              \n"
                    "                                                                                                                                                        \n"
                    "                                                                                                                                                        ";
}