
#include <iostream>
#include "pugixml.hpp"

int extraer_nivel_poder_xml(const char* archivo_xml) {
    pugi::xml_document doc;
    if (!doc.load_file(archivo_xml)) {
        std::cout << "No se pudo abrir el archivo XML" << std::endl;
        return -1;
    }
    
    pugi::xml_node nodo = doc.child("estrategia").child("poder");
    int nivel_poder = nodo.attribute("nivel").as_int();
    
    return nivel_poder;
}


