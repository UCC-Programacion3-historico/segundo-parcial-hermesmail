#include <iostream>
#include <fstream>
#include "MailManager.h"

//Funcion que devuelve un objeto de tipo Email a partir del archivo txt donde se almacena
email LeeEmail(string nombre_txt) {
    nombre_txt = "../Emails/" + nombre_txt + ".txt";
    ifstream txt(nombre_txt, ifstream::in);

    if (!txt.is_open())
        throw -1;

    email R;
    string tmp[6];
    string aux;
    for (int i = 0; i < 6; ++i) {
        getline(txt, aux);
//        while(getc(aux) != '\r' && getc(aux) != '\n' && getc(aux) != '\0')
        int j = 0;
        while (aux[j] != '\r' && aux[j] != '\n' && aux[j] != '\0') {
            tmp[i] += aux[j];
            j++;
        }
//        tmp[i] += '\0';
    }

    R.id = atoi(tmp[0].c_str());
    R.from = tmp[1];
    R.to = tmp[2];
    R.date = tmp[3];
    R.subject = tmp[4];
    R.content = tmp[5];

    txt.close();
    return R;
}

int main() {
    cout << "HERMESMAIL" << endl;
    MailManager MM;

    MM.addMail(LeeEmail("email000"));
    MM.addMail(LeeEmail("email001"));
    MM.addMail(LeeEmail("email002"));
    MM.addMail(LeeEmail("email003"));
    MM.addMail(LeeEmail("email004"));

    int n;
    vector<email> v;
    string anio,mes,dia,desde,hasta,rem,pal;
    do {
        cout << endl << "Seleccione una opcion:" << endl
             << " 1)Mostrar mails ordenados por fecha" << endl
             << " 2)Mostrar mails ordenados por fecha (con rango)" << endl
             << " 3)Mostrar mails ordenados por remitentes" << endl
             << " 4)Buscar mails por remitente" << endl
             << " 5)Buscar mails por palabra" << endl
             << " 6)Eliminar mail" << endl
             << " 7)Salir" << endl;
        cin >> n;
        switch (n) {
            case 1:
                v = MM.getSortedByDate();
                for (int i = 0; i < v.size(); ++i)
                    v[i].imprimir();
                break;

            case 2:
                desde="";
                hasta="";
                cout<<endl<<"Ingrese desde que fecha buscar:";
                cout<<endl<<" Ingrese anio: "<<endl;
                cin>>anio;
                cout<<endl<<" Ingrese mes: "<<endl;
                cin>>mes;
                cout<<endl<<" Ingrese dia: "<<endl;
                cin>>dia;
                desde+=anio;
                desde+=mes;
                desde+=dia;
                cout<<endl<<"Ingrese hasta que fecha buscar:";
                cout<<endl<<" Ingrese anio: "<<endl;
                cin>>anio;
                cout<<endl<<" Ingrese mes: "<<endl;
                cin>>mes;
                cout<<endl<<" Ingrese dia: "<<endl;
                cin>>dia;
                hasta+=anio;
                hasta+=mes;
                hasta+=dia;
                v = MM.getSortedByDate(desde,hasta);
                for (int i = 0; i < v.size(); ++i)
                    v[i].imprimir();
                break;

            case 3:
                v = MM.getSortedByFrom();
                for (int i = 0; i < v.size(); ++i)
                    v[i].imprimir();
                break;

            case 4:
                cout<<endl<<"Ingrese remitente a buscar:"<<endl;
                cin>>rem;
                v = MM.getByFrom(rem);
                for (int i = 0; i < v.size(); ++i)
                    v[i].imprimir();
                break;

            case 5:
                cout<<endl<<"Ingrese palabra a buscar:"<<endl;
                cin>>pal;
                v = MM.getByQuery(pal);
                for (int i = 0; i < v.size(); ++i)
                    v[i].imprimir();
                break;

            case 6:
                for (int i = 0; i < v.size(); ++i)
                    v[i].imprimir();
                break;

            case 7:

                break;

            default:
                cout << "Opcion incorrecta" << endl;
                break;
        }
    } while (n != 7);

    /*vector<email> v1 = MM.getSortedByDate();
    for (int i = 0; i < v1.size(); ++i)
        v1[i].imprimir();

    cout << "\n\n********************Get by Query : aviaci*********************\n";
    vector<email> v2 = MM.getByQuery("aviaci");
    for (int i = 0; i < v2.size(); ++i)
        v2[i].imprimir();

    cout << "\n\n********************Get by Query : oLimpo*********************\n";
    vector<email> v3 = MM.getByQuery("oLimpo");
    for (int i = 0; i < v3.size(); ++i)
        v3[i].imprimir();

    MM.deleteMail(0);
    cout << "\n\nDespues de borrrrrar 0\n";
    v3 = MM.getByQuery("oLimpo");
    for (int i = 0; i < v3.size(); ++i)
        v3[i].imprimir();

    cout << "\n\n********************Get by date : 20171101 y 20171101 *********************\n";
    vector<email> v4 = MM.getSortedByDate("20171101", "20171101");
    for (int i = 0; i < v4.size(); ++i)
        v4[i].imprimir();
*/

//    email uno, dos, tres, cuatro, cinco;
//
////    uno.from = "Zeus";
////    uno.subject = "subject uno";
////    uno.content = "aaa eee   iii";
////    uno.id = 1;
////    uno.date = "201710302214";
////    uno.to = "Poseidon";
////    MM.addMail(uno);
////
////    dos.from = "Hermes";
////    dos.subject = "subject dos";
////    dos.content = "ooo   uuu";
////    dos.id = 2;
////    dos.date = "20191201132526";
////    dos.to = "Poseidon";
////    MM.addMail(dos);
//
//    uno.from = "Zeus";
//    uno.subject = "El Olimpo te necesita";
//    uno.content = "Querido hermano estoy terriblemente preocupado por el posible ataque de Hades al Olimpo. Espero que puedas ayudarme.";
//    uno.id = 0;
//    uno.date = "201710302214";
//    uno.to = "Poseidon";
//    MM.addMail(uno);
//
//    dos.from = "Hermes";
//    dos.subject = "Las computadoras analógicas";
//    dos.content = "Los ordenadores. analógicos comenzaron a construirse a principios del siglo XX. Los primeros modelos realizaban los cálculos mediante ejes y engranajes giratorios. Con estas máquinas se evaluaban las aproximaciones numéricas de ecuaciones demasiado difíciles como para poder ser resueltas mediante otros métodos. Durante las dos guerras mundiales se utilizaron sistemas informáticos analógicos, primero mecánicos y más tarde eléctricos, para predecir la trayectoria de los torpedos en los submarinos y para el manejo a distancia de las bombas en la aviación.";
//    dos.id = 9959;
//    dos.date = "20191201132526";
//    dos.to = "Poseidon";
//    MM.addMail(dos);
//
//    tres.from = "Zeus";
//    tres.subject = "La computadora te necesita";
//    tres.content = "La primera máquina de calcular mecánica, un precursor del ordenador digital, fue inventada en 1642 por el matemático francés Blaise Pascal. Aquel dispositivo utilizaba una serie de ruedas de diez dientes en las que cada uno de los dientes representaba un dígito del 0 al 9. Las ruedas estaban conectadas de tal manera que podían sumarse números haciéndolas avanzar el número de dientes correcto. En 1670 el filósofo y matemático alemán Gottfried Wilhelm Leibniz perfeccionó esta máquina e inventó una que también podía multiplicar.";
//    tres.id = 78998;
//    tres.date = "201710302214";
//    tres.to = "Poseidon";
//    MM.addMail(tres);
//
//    cuatro.from = "Hades";
//    cuatro.subject = "Asalto al Monte Olimpo";
//    cuatro.content = "Avísame cuando tus tropas esten listas para asaltar el monte Olimpo.";
//    cuatro.id = 01;
//    cuatro.date = "20141101212354";
//    cuatro.to = "Poseidon";
//    MM.addMail(cuatro);
//
//    cinco.from = "Afrodita";
//    cinco.subject = "Las computadoras son cheveres";
//    cinco.content = "El inventor francés Joseph Marie Jacquard, al diseñar un telar automático, utilizó delgadas placas de madera perforadas para controlar el tejido utilizado en los diseños complejos. Durante la década de 1880 el estadístico estadounidense Herman Hollerith concibió la idea de utilizar tarjetas perforadas, similares a las placas de Jacquard, para procesar datos. Hollerith consiguió compilar la información estadística destinada al censo de población de 1890 de Estados Unidos mediante la utilización de un sistema que hacía pasar tarjetas perforadas sobre contactos eléctricos.";
//    cinco.id = 9828;
//    cinco.date = "201710302214";
//    cinco.to = "Poseidon";
//    MM.addMail(cinco);
//
//    cout << endl << "-----------------SORTED BY DATE-----------------" << endl;
//    vector<email> v1 = MM.getSortedByDate();
//    for (int i = 0; i < v1.size(); ++i)
//        v1[i].imprimir();
//
//
//    cout << endl << "-----------------SORTED BY FROM-----------------" << endl;
//    vector<email> v2 = MM.getSortedByFrom();
//    for (int i = 0; i < v2.size(); ++i)
//        v2[i].imprimir();
//
//    cout << endl << "-----------------SORTED BY DATE   20171015 , 20171102-----------------" << endl;
//    vector<email> v3 = MM.getSortedByDate("20171015", "20171102");
//    //vector<email> v3 = MM.getSortedByDate("20171031", "20171102");
//    for (int i = 0; i < v3.size(); ++i)
//        v3[i].imprimir();
//
//    cout << endl << "-----------------BY FROM   'Zeus'-----------------" << endl;
//    vector<email> v4 = MM.getByFrom("Zeus");
//    for (int i = 0; i < v4.size(); ++i)
//        v4[i].imprimir();
//
//    cout << endl << "-----------------BY QUERY   'multiplicar'-----------------" << endl;
//    vector<email> v5 = MM.getByQuery("multiplicar");
//    for (int i = 0; i < v5.size(); ++i)
//        v5[i].imprimir();
//
//
//    cout << endl << "-----------------DELETE '0'-----------------" << endl;
//    MM.deleteMail(0);
//
//    cout << endl << "-----------------SORTED BY DATE-----------------" << endl;
//    vector<email> v6 = MM.getSortedByDate();
//    for (int i = 0; i < v6.size(); ++i)
//        v6[i].imprimir();

    cout << endl << "-----------------FINISH-----------------" << endl;
    return 0;
}