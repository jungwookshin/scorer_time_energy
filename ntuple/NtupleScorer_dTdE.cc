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

}


NtupleScorer_dTdE::~NtupleScorer_dTdE() {;}


G4bool NtupleScorer_dTdE::ProcessHits(G4Step* aStep,G4TouchableHistory*)
{
	if (!fIsActive) {
		fSkippedWhileInactive++;
		return false;
	}

	ResolveSolid(aStep);


	return false;
}
