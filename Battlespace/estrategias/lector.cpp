#include "/usr/local/include/pugixml.hpp"
#include <iostream>

int main()
{
    pugi::xml_document doc;
    
    // Cargar archivo XML
    if (!doc.load_file("estrategia1.xml"))
    {
        std::cerr << "Error al cargar archivo XML" << std::endl;
        return 1;
    }

    // Acceder a los elementos del archivo XML
    pugi::xml_node estrategia = doc.child("estrategia");
    pugi::xml_node poderes = estrategia.child("poderes");

    // Imprimir información de la estrategia y poderes
    std::cout << "Estrategia: " << estrategia.attribute("nombre").value() << std::endl;
    std::cout << "Poder 1: " << poderes.child("poder1").attribute("nombre").value() << std::endl;
    std::cout << "Poder 2: " << poderes.child("poder2").attribute("nombre").value() << std::endl;

    return 0;
}