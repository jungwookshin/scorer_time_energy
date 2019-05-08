// Scorer for NtupleScorer_dTdE
//
// ********************************************************************
// *                                                                  *
// *                                                                  *
// * This file was obtained from Topas MC Inc under the license       *
// * agreement set forth at http://www.topasmc.org/registration       *
// * Any use of this file constitutes full acceptance of              *
// * this TOPAS MC license agreement.                                 *
// *                                                                  *
// ********************************************************************
//

#include "NtupleScorer_dTdE.hh"

#include "G4PSDirectionFlag.hh"

NtupleScorer_dTdE::NtupleScorer_dTdE(TsParameterManager* pM, TsMaterialManager* mM, TsGeometryManager* gM, TsScoringManager* scM, TsExtensionManager* eM,
						  G4String scorerName, G4String quantity, G4String outFileName, G4bool isSubScorer)
						 : TsVNtupleScorer(pM, mM, gM, scM, eM, scorerName, quantity, outFileName, isSubScorer)
{
	SetSurfaceScorer(); //Scorer or volume? 
        fpM->SetNeedsSteppingAction(); //is this needed?

        fNtuple->RegisterColumnF(&fPosX, "Position X", "cm");
        fNtuple->RegisterColumnF(&fPosY, "Position Y", "cm");
        fNtuple->RegisterColumnF(&fPosZ, "Position Z", "cm");
        fNtuple->RegisterColumnF(&fEnergy, "Energy", "MeV");
        fNtuple->RegisterColumnF(&fTimeOfFlight, "Time of flight", "MeV");
        fNtuple->RegisterColumnI(&fPType, "Particle Type (in PDG Format)");
        fNtuple->RegisterColumnS(&fOriginProcessName, "Origin Process");
}


NtupleScorer_dTdE::~NtupleScorer_dTdE() {;}


G4bool NtupleScorer_dTdE::ProcessHits(G4Step* aStep,G4TouchableHistory*)
{
	if (!fIsActive) {
		fSkippedWhileInactive++;
		return false;
	}

	ResolveSolid(aStep);

        if (IsSelectedSurface(aStep)) {
            G4StepPoint* theStepPoint=0;
            G4int direction = GetDirection();
            if (direction == fFlux_In) theStepPoint = aStep->GetPreStepPoint();
            else if (direction == fFlux_Out) theStepPoint = aStep->GetPostStepPoint();
            else return false;

                    G4ThreeVector pos       = theStepPoint->GetPosition();
                    fPosX           = pos.x();
                    fPosY           = pos.y();
                    fPosZ           = pos.z();

                    fEnergy	    = theStepPoint->GetKineticEnergy();
                    fTimeOfFlight   = theStepPoint->GetTimeofFlight();
                    fPType          = aStep->GetTrack()->GetDefinition()->GetPDGEncoding();

                    const G4VProcess* originProcess = aStep->GetTrack()->GetCreatorProcess();
                    if (originProcess)
                            fOriginProcessName = originProcess->GetProcessName();
                    else
                            fOriginProcessName = "Primary";

            fNtuple->Fill();
            return true;
        }
	return false;
}
