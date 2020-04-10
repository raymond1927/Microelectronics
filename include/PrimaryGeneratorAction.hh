//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// -------------------------------------------------------------------
// -------------------------------------------------------------------

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
public:

    PrimaryGeneratorAction();

    ~PrimaryGeneratorAction();

    void GeneratePrimaries(G4Event *);

    G4double InverseCumul();

private:

    G4ParticleGun *fParticleGun;

    const std::vector<G4double> ni63Energies = std::vector<G4double>{
            0.0001,
            0.00011,
            0.00012,
            0.00013,
            0.00014,
            0.00015,
            0.00016,
            0.00018,
            0.0002,
            0.00022,
            0.00024,
            0.00026,
            0.00028,
            0.0003,
            0.00032,
            0.00036,
            0.0004,
            0.00045,
            0.0005,
            0.00055,
            0.0006,
            0.00065,
            0.0007,
            0.00075,
            0.0008,
            0.00085,
            0.0009,
            0.001,
            0.0011,
            0.0012,
            0.0013,
            0.0014,
            0.0015,
            0.0016,
            0.0018,
            0.002,
            0.0022,
            0.0024,
            0.0026,
            0.0028,
            0.003,
            0.0032,
            0.0036,
            0.004,
            0.0045,
            0.005,
            0.0055,
            0.006,
            0.0065,
            0.007,
            0.0075,
            0.008,
            0.0085,
            0.009,
            0.01,
            0.011,
            0.012,
            0.013,
            0.014,
            0.015,
            0.016,
            0.018,
            0.02,
            0.022,
            0.024,
            0.026,
            0.028,
            0.03,
            0.032,
            0.036,
            0.04,
            0.045,
            0.05,
            0.055,
            0.06,
            0.065
    };

    const std::vector<G4double> ni63Probability = std::vector<G4double>{
            42.1,            42.09,            42.08,            42.07,            42.06,            42.05,
            42.03,            42.01,            41.99,            41.96,            41.94,            41.92,
            41.89,            41.87,            41.85,            41.8,            41.75,            41.69,
            41.64,            41.58,            41.52,            41.46,            41.4,            41.34,
            41.28,            41.23,            41.17,            41.05,            40.93,            40.82,
            40.7,            40.59,            40.47,            40.36,            40.12,            39.89,
            39.66,            39.44,            39.21,            38.98,            38.75,            38.52,
            38.07,            37.64,            37.11,            36.58,            36.06,            35.53,
            35.01,            34.5,            33.98,            33.47,            32.96,            32.46,
            31.46,            30.47,            29.5,            28.54,            27.6,            26.66,
            25.75,            23.95,            22.21,            20.53,            18.9,            17.33,
            15.81,            14.35,            12.95,            10.34,            7.979,            5.411,
            3.299,            1.676,            0.5791,            0.04642

    };

    std::vector<G4double> ni63Dist;
};

#endif
