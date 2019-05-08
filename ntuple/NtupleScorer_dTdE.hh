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

class NtupleScorer_dTdE : public TsVNtupleScorer
{
public:
	NtupleScorer_dTdE(TsParameterManager* pM, TsMaterialManager* mM, TsGeometryManager* gM, TsScoringManager* scM, TsExtensionManager* eM,
				G4String scorerName, G4String quantity, G4String outFileName, G4bool isSubScorer);

	virtual ~NtupleScorer_dTdE();

	G4bool ProcessHits(G4Step*,G4TouchableHistory*);

protected:
};
#endif
