#include <iostream>
#include "MapDriver.h"
#include "Map.h"

using std::string;
using std::cout;
using std::endl;

void testLoadMaps(){

    MapLoader maploader;

    string map_valid_canada = "../map_files/canada_valid.map";
    string map_valid_abc = "../map_files/abc_valid.map";
    string map_invalid_missing_section  = "../map_files/canada_invalid_missing_section.map";
    string map_invalid_empty = "../map_files/canada_invalid_empty.map";
    string map_invalid_not_exist = "nonexistentfile.map";
    string map_invalid_disconnected_territories = "../map_files/canada_invalid_disconnected_territories.map";
    string map_invalid_disconnected_continents = "../map_files/canada_invalid_disconnected_continents.map";

    cout << "****************************************" << endl;
    cout << "*              MAP TEST                *" << endl;
    cout << "****************************************" << endl;

    cout << "***********************************" << endl;
    cout << "INVALID MAP: MISSING SECTION" << endl;
    cout << "***********************************" << endl;
    Map* m1 = maploader.readMapFile(map_invalid_missing_section);
    cout << endl;

    cout << "***********************************" << endl;
    cout << "INVALID MAP: EMPTY FILE" << endl;
    cout << "***********************************" << endl;
    Map* m2 = maploader.readMapFile(map_invalid_empty);
    cout << endl << endl;

    cout << "***********************************" << endl;
    cout << "INVALID MAP: NON-EXISTENT FILE" << endl;
    cout << "***********************************" << endl;
    Map* m3 = maploader.readMapFile(map_invalid_not_exist);
    cout << endl << endl;

    cout << "***********************************" << endl;
    cout << "INVALID MAP: DISCONNECTED TERRITORIES" << endl;
    cout << "***********************************" << endl;
    Map* m4 = maploader.readMapFile(map_invalid_disconnected_territories);
    m4->validate();
    cout << endl << endl;

    cout << "***********************************" << endl;
    cout << "INVALID MAP: DISCONNECTED CONTINENTS" << endl;
    cout << "***********************************" << endl;
    Map* m5 = maploader.readMapFile(map_invalid_disconnected_continents);
    m5->validate();
    cout << endl << endl;

    cout << "***********************************" << endl;
    cout << "VALID MAP: CANADA" << endl;
    cout << "***********************************" << endl;
    Map* m6 = maploader.readMapFile(map_valid_canada);
    m6->validate();
    cout << endl << endl;

    cout << "***********************************" << endl;
    cout << "VALID MAP: ABC MAP" << endl;
    cout << "***********************************" << endl;
    Map* m7 = maploader.readMapFile(map_valid_abc);
    m7->validate();
    cout << endl << endl;


    delete m1;
    delete m2;
    delete m3;
    delete m4;
    delete m5;
    delete m6;
    delete m7;


}