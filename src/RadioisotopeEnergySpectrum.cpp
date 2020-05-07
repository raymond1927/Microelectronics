//
// Created by ray on 7/5/20.
//

#include "RadioisotopeEnergySpectrum.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <G4ios.hh>

/*
 *
 */
RadioisotopeEnergySpectrum::RadioisotopeEnergySpectrum(const std::string name) {

}

const std::vector<double> RadioisotopeEnergySpectrum::getEnergyDistribution() {
    std::vector<double> energyDistribution;

    std::ifstream radioisotopeFile("ICRP-07.BET");

    if (!radioisotopeFile.is_open()) throw std::runtime_error("Could not open file");

    std::string line, colname;
    int val;

    if (radioisotopeFile.good()) {
        std::getline(radioisotopeFile, line);

        std::stringstream ss(line);

        while (std::getline(ss, colname, ',')) {
            G4cout<< colname << '\n';
        }
    }

    return energyDistribution;
}