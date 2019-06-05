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

//#include "G4PSDirectionFlag.hh"
#include "G4VProcess.hh"
//#include "TsTrackInformation.hh"

NtupleScorer_dTdE::NtupleScorer_dTdE(TsParameterManager* pM, TsMaterialManager* mM, TsGeometryManager* gM, TsScoringManager* scM, TsExtensionManager* eM,
						  G4String scorerName, G4String quantity, G4String outFileName, G4bool isSubScorer)
						 : TsVNtupleScorer(pM, mM, gM, scM, eM, scorerName, quantity, outFileName, isSubScorer)
						 , lastEvent(0)
{
	//SetSurfaceScorer(); //Scorer or volume? 
        //pM->SetNeedsTrackingAction();// Activates creation of the TsTrackInformation object
        //~ pM->SetNeedsSteppingAction();// Activates creation of the extra part of the TsTrackInformation object that contains information on what volumes were traversed
        

        fNtuple->RegisterColumnF(&fPosX, "x", "");
        fNtuple->RegisterColumnF(&fPosY, "y", "");
        fNtuple->RegisterColumnF(&fPosZ, "z", "");
        fNtuple->RegisterColumnF(&fEnergy, "E", "");
        fNtuple->RegisterColumnF(&fTimeOfFlight, "tof", "");
        //fNtuple->RegisterColumnI(&fPType, "ptype");
        //fNtuple->RegisterColumnS(&fOriginProcessName, "process");
}


NtupleScorer_dTdE::~NtupleScorer_dTdE() {;}


G4bool NtupleScorer_dTdE::ProcessHits(G4Step* aStep,G4TouchableHistory*)
{
	if (!fIsActive) {
		fSkippedWhileInactive++;
		return false;
	}

	ResolveSolid(aStep);

        //~ if (IsSelectedSurface(aStep)) {
	if (aStep) {
		//~ G4int direction = GetDirection();
		//~ if (direction == fFlux_In) theStepPoint = aStep->GetPreStepPoint();
		//~ else if (direction == fFlux_Out) theStepPoint = aStep->GetPostStepPoint();
		//~ else return false;
		//~ if(aStep->GetPostStepPoint()->GetStepStatus() == fGeomBoundary) return false;//IsLeaving

		G4int eventID = GetEventID();
		if(eventID!=lastEvent)//TODO add: or thisEventID is lastEvent and thisTrackID==0
		{
			for (auto const& pgs : pgbuffer)
			{
				//~ G4float ptof=pgs.second.front().tof;
				//~ for(auto const& pg: pgs.second)
				//~ {
					//~ std::cout << lastEvent << " " << pgs.first << " " << pg.tof << " " << pg.z << std::endl;
				//~ }
				auto const& pg = pgs.second.front();
				fPosX           = pg.x;
				fPosY           = pg.y;
				fPosZ           = pg.z;
				fEnergy	    	= pg.E;
				fTimeOfFlight   = ptofbuffer[pg.z];
				//fOriginProcessName = pg.process;
				fNtuple->Fill();
			}
			
			pgbuffer.clear();
			ptofbuffer.clear();
		}
		lastEvent=eventID;

		if(aStep->GetTrack()->GetDefinition()->GetPDGEncoding()==2212)
		{
			G4StepPoint* const theStepPoint=aStep->GetPreStepPoint();
			if(!theStepPoint) return false;
			ptofbuffer[theStepPoint->GetPosition().z()]=aStep->GetTrack()->GetGlobalTime();
			//~ std::cout << "p " << lastEvent << " " << trackID << " " << ptofbuffer[trackID] << " " << theStepPoint->GetPosition().z() << std::endl;
		}
		else
		if(aStep->GetTrack()->GetDefinition()->GetPDGEncoding()==22 && aStep->GetTrack()->GetCreatorProcess()->GetProcessName()=="protonInelastic")
		{
			G4StepPoint* const theStepPoint=aStep->GetPreStepPoint();
			if(!theStepPoint) return false;
			
			G4ThreeVector pos       = theStepPoint->GetPosition();
			PromptGamma pg;
			pg.x = pos.x();
			pg.y = pos.y();
			pg.z = pos.z();
			pg.E = theStepPoint->GetKineticEnergy();
			pg.tof = aStep->GetTrack()->GetGlobalTime();
			
			G4int trackID = aStep->GetTrack()->GetTrackID();
			pgbuffer[trackID].push_back(pg);	
		}
		return true;
	}
	return false;
}
