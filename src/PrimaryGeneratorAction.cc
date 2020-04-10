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

#include <Randomize.hh>
#include "PrimaryGeneratorAction.hh"
#include "G4SystemOfUnits.hh"
#include <random>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

PrimaryGeneratorAction::PrimaryGeneratorAction() {
    G4int n_particle = 1;
    fParticleGun = new G4ParticleGun(n_particle);

    // default gun parameters
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
    fParticleGun->SetParticlePosition(G4ThreeVector(0., 0., 0));

    G4double sum = 0;
    G4int count = 0;

    for (auto it = ni63Probability.begin(); it != ni63Probability.end(); ++it) {
        sum += it.operator*();
        ++count;
    }

    G4int total_length = 10000;
    ni63Dist.reserve(total_length);

    auto ni63it = ni63Energies.begin();
    for (auto it = ni63Probability.begin(); it != ni63Probability.end(); ++it) {
        G4int amount = std::floor(*it / sum * total_length);

        std::fill_n(std::back_inserter(ni63Dist), amount, ni63it.operator*());

        ++ni63it;
    }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

PrimaryGeneratorAction::~PrimaryGeneratorAction() {
    delete fParticleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void PrimaryGeneratorAction::GeneratePrimaries(G4Event *anEvent) {

    G4int index = std::floor(G4UniformRand() * (ni63Dist.size() - 1));
    G4double energy = ni63Dist.at(index);


    fParticleGun->SetParticleEnergy(energy * MeV);
    fParticleGun->GeneratePrimaryVertex(anEvent);
}

G4double PrimaryGeneratorAction::InverseCumul() {

}
