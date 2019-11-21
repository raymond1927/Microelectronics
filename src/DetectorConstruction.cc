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

#include "DetectorConstruction.hh"
#include "G4SystemOfUnits.hh"
#include "G4Region.hh"
#include "G4ProductionCuts.hh"
#include "G4Material.hh"
#include "G4UnitsTable.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

DetectorConstruction::DetectorConstruction()
        : fPhysiWorld(NULL), fLogicWorld(NULL), fSolidWorld(NULL) {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

DetectorConstruction::~DetectorConstruction() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4VPhysicalVolume *DetectorConstruction::Construct() {
    DefineMaterials();
    return ConstructDetector();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void DetectorConstruction::DefineMaterials() {

    // Silicon is defined from NIST material database
    G4NistManager *man = G4NistManager::Instance();
    G4Material *GaAs = man->FindOrBuildMaterial("G4_GALLIUM_ARSENIDE");

    // Default materials in setup.
    fSiMaterial = GaAs;

    G4double z, a;

    G4Element *Si = new G4Element("Silicon", "Si", z = 14., a = 28.0855 * g / mole);
    G4Element *N = new G4Element("Nitrogen", "N", z = 7., a = 14.01 * g / mole);

    G4double density;
    G4int ncomponents, natoms;
    G4double fractionmass;

    G4Material *SiN = new G4Material("SiN", density = 3.17 * g / cm3, ncomponents = 2);
    SiN->AddElement(Si, natoms = 1);
    SiN->AddElement(N, natoms = 1);

    fSiNMaterial = SiN;
//  G4Element* Al = man->FindElement(13);
//  G4Element* Ga = man->FindElement(31);
//  G4Element* As = man->FindElement(33);
    G4Element *Al = new G4Element("Aluminium", "Al", z = 13., a = 26.9815 * g / mole);
    G4Element *Ga = new G4Element("Gallium", "Ga", z = 31., a = 69.723 * g / mole);
    G4Element *As = new G4Element("Arsenic", "As", z = 33., a = 74.922 * g / mole);
    G4Material *AlGaAs = new G4Material("AlGaAs", density = 2.329 * g / cm3, ncomponents = 3);
    AlGaAs->AddElement(Al, fractionmass = 26.6 * perCent);
    AlGaAs->AddElement(Ga, fractionmass = 36.7 * perCent);
    AlGaAs->AddElement(As, fractionmass = 36.7 * perCent);

    fAlGaAsMaterial = AlGaAs;

    fAirMaterial = man->FindOrBuildMaterial("G4_AIR");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
G4VPhysicalVolume *DetectorConstruction::ConstructDetector() {

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

    // WORLD VOLUME

    fWorldSizeX = 40 * um;
    fWorldSizeY = 40 * um;
    fWorldSizeZ = 4 * um;

    fSolidWorld = new G4Box("World",                     //its name
                            fWorldSizeX * 0.5, fWorldSizeY * 0.5, fWorldSizeZ * 0.5);  //its size


    fLogicWorld = new G4LogicalVolume(fSolidWorld,    //its solid
                                      fAirMaterial,        //its material
                                      "World");        //its name

    fPhysiWorld = new G4PVPlacement(0,            //no rotation
                                    G4ThreeVector(),    //at (0,0,0)
                                    "World",        //its name
                                    fLogicWorld,        //its logical volume
                                    0,            //its mother  volume
                                    false,            //no boolean operation
                                    0);            //copy number

    G4double TargetSizeZ1 = 0.07 * um;
    G4double TargetSizeZ2 = 0.043 * um;
    G4double TargetSizeZ3 = 0.2 * um;
    G4double TargetSizeZ4 = 0.2 * um;
    G4double TargetSizeZ5 = 3 * um;
    G4double TargetSizeZ6 = 0.3 * um;

    G4Box *targetSolid1 = new G4Box("Target1",                     //its name
                                    fWorldSizeX / 2, fWorldSizeY / 2, TargetSizeZ1 / 2);   //its size


    G4LogicalVolume *logicTarget1 = new G4LogicalVolume(targetSolid1,       //its solid
                                                        fSiNMaterial,    //its material
                                                        "Target1");        //its name

    new G4PVPlacement(0,                                           //no rotation
                      G4ThreeVector(0, 0, -2 * um + 0.5 * TargetSizeZ1),
                      "Target1",        //its name
                      logicTarget1,    //its logical volume
                      fPhysiWorld,        //its mother  volume
                      false,        //no boolean operation
                      0);            //copy number

    G4Box *targetSolid2 = new G4Box("Target2",                     //its name
                                    fWorldSizeX / 2, fWorldSizeY / 2, TargetSizeZ2 / 2);   //its size


    G4LogicalVolume *logicTarget2 = new G4LogicalVolume(targetSolid2,       //its solid
                                                        fAlGaAsMaterial,    //its material
                                                        "Target2");        //its name

    new G4PVPlacement(0,                                           //no rotation
                      G4ThreeVector(0, 0, -2 * um + 0.5 * TargetSizeZ2 + TargetSizeZ1),
                      "Target2",        //its name
                      logicTarget2,    //its logical volume
                      fPhysiWorld,        //its mother  volume
                      false,        //no boolean operation
                      0);            //copy number

    G4Box *targetSolid3 = new G4Box("Target3",                     //its name
                                    fWorldSizeX / 2, fWorldSizeY / 2, TargetSizeZ3 / 2);   //its size


    G4LogicalVolume *logicTarget3 = new G4LogicalVolume(targetSolid3,       //its solid
                                                        fSiMaterial,    //its material
                                                        "Target3");        //its name

    new G4PVPlacement(0,                                           //no rotation
                      G4ThreeVector(0, 0, -2 * um + 0.5 * TargetSizeZ3 + TargetSizeZ2 + TargetSizeZ1),
                      "Target3",        //its name
                      logicTarget3,    //its logical volume
                      fPhysiWorld,        //its mother  volume
                      false,        //no boolean operation
                      0);            //copy number

    G4Box *targetSolid4 = new G4Box("Target4",                     //its name
                                    fWorldSizeX / 2, fWorldSizeY / 2, TargetSizeZ4 / 2);   //its size


    G4LogicalVolume *logicTarget4 = new G4LogicalVolume(targetSolid4,       //its solid
                                                        fSiMaterial,    //its material
                                                        "Target4");        //its name

    new G4PVPlacement(0,                                           //no rotation
                      G4ThreeVector(0, 0, -2 * um + 0.5 * TargetSizeZ4 + TargetSizeZ3 + TargetSizeZ2 + TargetSizeZ1),
                      "Target4",        //its name
                      logicTarget4,    //its logical volume
                      fPhysiWorld,        //its mother  volume
                      false,        //no boolean operation
                      0);            //copy number

    G4Box *targetSolid5 = new G4Box("Target5",                     //its name
                                    fWorldSizeX / 2, fWorldSizeY / 2, TargetSizeZ5 / 2);   //its size


    G4LogicalVolume *logicTarget5 = new G4LogicalVolume(targetSolid5,       //its solid
                                                        fSiMaterial,    //its material
                                                        "Target5");        //its name

    new G4PVPlacement(0,                                           //no rotation
                      G4ThreeVector(0, 0, -2 * um + 0.5 * TargetSizeZ5 + TargetSizeZ4 + TargetSizeZ3 + TargetSizeZ2 +
                                          TargetSizeZ1),
                      "Target5",        //its name
                      logicTarget5,    //its logical volume
                      fPhysiWorld,        //its mother  volume
                      false,        //no boolean operation
                      0);            //copy number

    G4Box *targetSolid6 = new G4Box("Target6",                     //its name
                                    fWorldSizeX / 2, fWorldSizeY / 2, TargetSizeZ6 / 2);   //its size


    G4LogicalVolume *logicTarget6 = new G4LogicalVolume(targetSolid6,       //its solid
                                                        fSiMaterial,    //its material
                                                        "Target6");        //its name

    new G4PVPlacement(0,                                           //no rotation
                      G4ThreeVector(0, 0, -2 * um + 0.5 * TargetSizeZ6 + TargetSizeZ5 + TargetSizeZ4 + TargetSizeZ3 +
                                          TargetSizeZ2 + TargetSizeZ1),
                      "Target6",        //its name
                      logicTarget6,    //its logical volume
                      fPhysiWorld,        //its mother  volume
                      false,        //no boolean operation
                      0);            //copy number

    // Visualization attributes
    G4VisAttributes *worldVisAtt = new G4VisAttributes(G4Colour(1.0, 0.0, 0.0));
    worldVisAtt->SetVisibility(true);
    fLogicWorld->SetVisAttributes(worldVisAtt);

    G4VisAttributes *worldVisAtt1 = new G4VisAttributes(G4Colour(1.0, 0.0, 0.0));
    worldVisAtt1->SetVisibility(true);
    logicTarget1->SetVisAttributes(worldVisAtt1);

    G4VisAttributes *worldVisAtt2 = new G4VisAttributes(G4Colour(1.0, 0.0, 0.0));
    worldVisAtt2->SetVisibility(true);
    logicTarget2->SetVisAttributes(worldVisAtt2);

    G4VisAttributes *worldVisAtt3 = new G4VisAttributes(G4Colour(1.0, 0.0, 0.0));
    worldVisAtt3->SetVisibility(true);
    logicTarget3->SetVisAttributes(worldVisAtt3);

    G4VisAttributes *worldVisAtt4 = new G4VisAttributes(G4Colour(1.0, 0.0, 0.0));
    worldVisAtt4->SetVisibility(true);
    logicTarget4->SetVisAttributes(worldVisAtt4);

    G4VisAttributes *worldVisAtt5 = new G4VisAttributes(G4Colour(1.0, 0.0, 0.0));
    worldVisAtt5->SetVisibility(true);
    logicTarget5->SetVisAttributes(worldVisAtt5);

    G4VisAttributes *worldVisAtt6 = new G4VisAttributes(G4Colour(1.0, 0.0, 0.0));
    worldVisAtt6->SetVisibility(true);
    logicTarget6->SetVisAttributes(worldVisAtt6);

    // Create Target G4Region and add logical volume

    fRegion = new G4Region("World");

    G4ProductionCuts *cuts = new G4ProductionCuts();

    G4double defCut = 1 * nanometer;
    cuts->SetProductionCut(defCut, "gamma");
    cuts->SetProductionCut(defCut, "e-");
    cuts->SetProductionCut(defCut, "e+");
    cuts->SetProductionCut(defCut, "proton");

    fRegion->SetProductionCuts(cuts);
    fRegion->AddRootLogicalVolume(logicTarget1);
    fRegion->AddRootLogicalVolume(logicTarget2);
    fRegion->AddRootLogicalVolume(logicTarget3);
    fRegion->AddRootLogicalVolume(logicTarget4);
    fRegion->AddRootLogicalVolume(logicTarget5);
    return fPhysiWorld;
}
