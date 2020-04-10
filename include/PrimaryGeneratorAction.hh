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
            0.0001,            0.00011,            0.00012,            0.00013,            0.00014,            0.00015,            0.00016,            0.00018,            0.0002,            0.00022,            0.00024,            0.00026,            0.00028,            0.0003,            0.00032,            0.00036,            0.0004,            0.00045,            0.0005,            0.00055,            0.0006,            0.00065,            0.0007,            0.00075,            0.0008,            0.00085,            0.0009,            0.001,            0.0011,            0.0012,            0.0013,            0.0014,            0.0015,            0.0016,            0.0018,            0.002,            0.0022,            0.0024,            0.0026,            0.0028,            0.003,            0.0032,            0.0036,            0.004,            0.0045,            0.005,            0.0055,            0.006,            0.0065,            0.007,            0.0075,            0.008,            0.0085,            0.009,            0.01,            0.011,            0.012,            0.013,            0.014,            0.015,            0.016,            0.018

    };

    const std::vector<G4double> ni63Probability = std::vector<G4double>{
            83.39,            83.56,            83.74,            83.91,            84.1,            84.28,            84.47,            84.84,            85.23,            85.61,            86,            86.38,            86.76,            87.14,            87.51,            88.25,            88.96,            89.82,            90.65,            91.44,            92.2,            92.92,            93.61,            94.26,            94.88,            95.47,            96.04,            97.08,            98.01,            98.85,            99.59,            100.3,            100.8,            101.3,            102.1,            102.7,            103,            103.2,            103.1,            102.9,            102.5,            102,            100.6,            98.84,            96.06,            92.81,            89.17,            85.22,            81.02,            76.62,            72.07,            67.43,            62.72,            57.99,            48.59,            39.49,            30.89,            23.01,            16.03,            10.11,            5.418,            0.2967


    };

    std::vector<G4double> ni63Dist;
};

#endif
