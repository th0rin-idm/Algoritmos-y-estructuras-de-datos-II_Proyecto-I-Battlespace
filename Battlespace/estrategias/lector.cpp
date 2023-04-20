

#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

int lector() {
  // Nombres de los archivos XML
  std::vector<std::string> xml_files = {"parte1.xml", "parte2.xml", "parte3.xml", "parte4.xml"};

  // Recorre cada archivo XML
  for (const auto& file : xml_files) {
    // Carga el archivo XML en un objeto ptree
    boost::property_tree::ptree ptree;
    boost::property_tree::read_xml(file, ptree);

    // Obtiene el valor del atributo "nivel" y lo asigna a una variable int
    int nivel = ptree.get<int>("estrategia.poder.<xmlattr>.nivel");

    // Imprime el valor de la variable nivel
    std::cout << "El valor de nivel en " << file << " es: " << nivel << std::endl;
  }

  return 0;
}


