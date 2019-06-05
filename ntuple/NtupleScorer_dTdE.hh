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

#ifndef NtupleScorer_dTdE_hh
#define NtupleScorer_dTdE_hh

#include "TsVNtupleScorer.hh"

#include <map>
using std::map;
using std::vector;

class NtupleScorer_dTdE : public TsVNtupleScorer
{
public:
	NtupleScorer_dTdE(TsParameterManager* pM, TsMaterialManager* mM, TsGeometryManager* gM, TsScoringManager* scM, TsExtensionManager* eM,
				G4String scorerName, G4String quantity, G4String outFileName, G4bool isSubScorer);

	virtual ~NtupleScorer_dTdE();

	G4bool ProcessHits(G4Step*,G4TouchableHistory*);

protected:
        // Output variables
        G4float fPosX;
        G4float fPosY;
        G4float fPosZ;
        G4float fEnergy;
        G4float fTimeOfFlight;
        //G4int fPType;
        //G4String fOriginProcessName;
        
        uint64_t lastEvent;
        
        struct PromptGamma {
	G4float x, y, z, E, tof;
	//G4int ptype;
	//G4String process;
	};

	map<G4int,vector<PromptGamma>> pgbuffer;
	map<G4float,G4float> ptofbuffer;
};
#endif
