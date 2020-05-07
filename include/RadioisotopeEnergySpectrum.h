//
// Created by ray on 7/5/20.
//

#ifndef MICROELECTRONICS_RADIOISOTOPEENERGYSPECTRUM_H
#define MICROELECTRONICS_RADIOISOTOPEENERGYSPECTRUM_H

#include <vector>
#include <string>

class RadioisotopeEnergySpectrum {
private:
    std::vector<double> radioisotopeEnergies;
public:
    RadioisotopeEnergySpectrum(const std::string);
    const std::vector<double> getEnergyDistribution();
};

#endif //MICROELECTRONICS_RADIOISOTOPEENERGYSPECTRUM_H
