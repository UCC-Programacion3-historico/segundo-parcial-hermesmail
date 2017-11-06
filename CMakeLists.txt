cmake_minimum_required(VERSION 3.8)
project(MailManager)

set(CMAKE_CXX_STANDARD 14)


add_subdirectory(test)

set(SOURCE_FILES src/main.cpp src/MailManager.cpp src/MailManager.h src/email.cpp src/email.h src/Estructuras_Datos/Lista.h src/Estructuras_Datos/ArbolConLista.h src/Estructuras_Datos/Nodo.h src/Estructuras_Datos/NodoArbolConLista.h)
add_executable(MailManager ${SOURCE_FILES})