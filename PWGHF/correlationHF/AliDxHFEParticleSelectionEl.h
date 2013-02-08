//-*- Mode: C++ -*-
// $Id$

//* This file is property of and copyright by the ALICE Project        * 
//* ALICE Experiment at CERN, All rights reserved.                     *
//* See cxx source for full Copyright notice                           *

/// @file   AliDxHFEParticleSelectionEl.h
/// @author Sedat Altinpinar, Hege Erdal, Matthias Richter
/// @date   2012-03-19
/// @brief  Electron selection for D-HFE correlations
///

#ifndef ALIDXHFEPARTICLESELECTIONEL_H
#define ALIDXHFEPARTICLESELECTIONEL_H

#include "AliDxHFEParticleSelection.h"


// 2012-09-17: there has been a problem in the dictionary generation for par file
// compilation, so we have to include the header files indicated below
//  Generating dictionary ...
//  In file included from $ROOTSYS/include/TObject.h:230:0,
//                   from G__PWGHFcorrelationHF.h:32,
//                   from G__PWGHFcorrelationHF.cxx:17:
//  $ROOTSYS/include/TBuffer.h: In function ‘TBuffer& operator>>(TBuffer&, Tmpl*&) [with Tmpl = AliHFEcuts]’:
//  G__PWGHFcorrelationHF.cxx:1658:15:   instantiated from here
//  $ROOTSYS/include/TBuffer.h:373:47: error: invalid use of incomplete type ‘struct AliHFEcuts’
//  correlationHF/AliDxHFEParticleSelectionEl.h:25:7: error: forward declaration of ‘struct AliHFEcuts’

#include "AliHFEcuts.h" // need to directly include to avoid compilation error in the dictionary
#include "AliHFEpid.h"  // need to directly include to avoid compilation error in the dictionary

class AliPID;
class AliPIDResponse;
class AliHFEvarManager;
class AliHFEpidBase;
class AliHFEtools;
class AliVEvent;
class AliCFManager;
class TH1;
class TH1F;
class TH2F;
/**
 * @class AliDxHFEParticleSelectionEl
 * Electron selection for D-HFE correlations, implements the specific
 * selection criteria.
 */
class AliDxHFEParticleSelectionEl : public AliDxHFEParticleSelection {
  public:
  /// constructor
  AliDxHFEParticleSelectionEl(const char* opt="");
  /// destructor
  virtual ~AliDxHFEParticleSelectionEl();
  
  enum {
    kCutHFE = 0,
    kCutPID = 1,
    kCutPIDTOF = 2,
    kNCuts
  };

  enum {
    kRecKineITSTPC=0,
    kRecPrim,
    kHFEcutsITS,
    kHFEcutsTOF,
    kHFEcutsTPC,
    kPIDTOF,
    kPID,
    kSelected,
    kNCutLabels
  };

  ///overloaded from AliDxHFEParticleSelection: Init
  virtual int Init();

  /// overloaded from AliDxHFEParticleSelection: init the control objects
  virtual int InitControlObjects();
  virtual THnSparse* DefineTHnSparse();

  /// overloaded from AliDxHFEParticleSelection: check particle
  virtual int IsSelected(AliVParticle* p, const AliVEvent* pEvent);

  virtual int HistogramParticleProperties(AliVParticle* p, int selected);

  virtual int FillParticleProperties(AliVParticle* p, Double_t* date, int dimension) const;

  /// set cuts object: a type cast check is implemented in the method
  virtual void SetCuts(TObject* /*cuts*/, int /*level*/=0);
 
  virtual void SetPIDResponse(const AliPIDResponse* const pidresp){fPIDResponse=(AliPIDResponse*)(pidresp);}

 protected:

 private:

  /// copy contructor prohibited
  AliDxHFEParticleSelectionEl(const AliDxHFEParticleSelectionEl&);
  /// assignment operator prohibited
  AliDxHFEParticleSelectionEl& operator=(const AliDxHFEParticleSelectionEl&);
 
  /// check cut of specified step, e.g.
  bool ProcessCutStep(Int_t cutStep, AliVParticle *track);

  AliHFEpid*    fPID;                //! the PID object
  AliHFEpid*    fPIDTOF;             //! the PID TOF object
  THnSparse*    fElectronProperties; // the particle properties of selected particles
  TH1*          fWhichCut;           // effective cut for a rejected particle
  TH2F*         fdEdx;               // dedx plot
  TH2F*         fdEdxCut;            // dedx plot after track cuts
  TH2F*         fdEdxPid;            // dedx plot after pid
  TH2F*         fdEdxPidTOF;         // dedx plot after TOF pid
  TH2F*         fnSigTPC;            // nSigmaTPC vs momentum before track cut
  TH2F*         fnSigTPCCut;         // nSigmaTPC vs momentum after track cut
  TH2F*         fnSigTPCPid;         // nSigmaTPC vs momentum after PID
  TH2F*         fnSigTPCPidTOF;      // nSigmaTPC vs momentum after TOF PID
  TH2F*         fnSigTOF;            // nSigmaTOF vs momentum before track cut
  TH2F*         fnSigTOFCut;         // nSigmaTOF vs momentum after track cut
  TH2F*         fnSigTOFPid;         // nSigmaTOF vs momentum after PID
  TH2F*         fnSigTOFPidTOF;      // nSigmaTOF vs momentum after  TOF PID
  AliPIDResponse* fPIDResponse;      // fPIDResponse
  AliHFEcuts*   fCuts;               //! Cuts for HF electrons
  AliCFManager* fCFM;                //! Correction Framework Manager

  static const char* fgkCutBinNames[]; //! bin labels for cuts histogram

  ClassDef(AliDxHFEParticleSelectionEl, 3);
};

#endif
