//
// File: LLG08_EX2.cpp
// Created by:  Laurent Gueguen
// Created on: mardi 12 octobre 2010, à 09h 43
//

/*
Copyright or © or Copr. CNRS, (November 16, 2004)
This software is a computer program whose purpose is to provide classes
for phylogenetic data analysis.

This software is governed by the CeCILL  license under French law and
abiding by the rules of distribution of free software.  You can  use, 
modify and/ or redistribute the software under the terms of the CeCILL
license as circulated by CEA, CNRS and INRIA at the following URL
"http://www.cecill.info". 

As a counterpart to the access to the source code and  rights to copy,
modify and redistribute granted by the license, users are provided only
with a limited warranty  and the software's author,  the holder of the
economic rights,  and the successive licensors  have only  limited
liability. 

In this respect, the user's attention is drawn to the risks associated
with loading,  using,  modifying and/or developing or reproducing the
software by the user in light of its specific status of free software,
that may mean  that it is complicated to manipulate,  and  that  also
therefore means  that it is reserved for developers  and  experienced
professionals having in-depth computer knowledge. Users are therefore
encouraged to load and test the software's suitability as regards their
requirements in conditions enabling the security of their systems and/or 
data to be ensured and,  more generally, to use and operate it in the 
same conditions as regards security. 

The fact that you are presently reading this means that you have had
knowledge of the CeCILL license and that you accept its terms.
*/

#include "LLG08_EX2.h"
#include "YN98.h"
#include "FrequenciesSet.h"

#include <Bpp/Numeric/NumConstants.h>
#include <Bpp/Numeric/Prob/SimpleDiscreteDistribution.h>

using namespace bpp;

using namespace std;

/******************************************************************************/

LLG08_EX2::LLG08_EX2(const ProteicAlphabet* alpha) : 
  AbstractMixedSubstitutionModel(alpha, "LLG08_EX2."), pmixmodel_(0),
  mapParNamesFromPmodel_(), lParPmodel_()
{
  // build the submodel

  vector<SubstitutionModel*> vpSM;
  vpSM.push_back(new LLG08_EX2::EmbeddedModel(alpha,"EX2_Buried"));
  vpSM.push_back(new LLG08_EX2::EmbeddedModel(alpha,"EX2_Exposed"));

  Vdouble vrate, vproba;
  
  for (unsigned int i=0;i<vpSM.size();i++){
    vproba.push_back((dynamic_cast<LLG08_EX2::EmbeddedModel*> (vpSM[i]))->getProportion());
    vrate.push_back(vpSM[i]->getRate());
  }

  pmixmodel_= new MixtureOfSubstitutionModels(alpha, vpSM, vproba, vrate);

  string name,st;
  ParameterList pl=pmixmodel_->getParameters();
  for (unsigned int i=0;i<pl.size();i++){
    name=pl[i].getName();
    lParPmodel_.addParameter(Parameter(pl[i]));
    st=pmixmodel_->getParameterNameWithoutNamespace(name);
    mapParNamesFromPmodel_[name]=st;
    addParameter_(Parameter("LLG08_EX2."+st,
                            pmixmodel_->getParameterValue(st),
                            pmixmodel_->getParameter(st).hasConstraint()? pmixmodel_->getParameter(st).getConstraint()->clone():0,true));
  }

  updateMatrices();
}

LLG08_EX2::LLG08_EX2(const LLG08_EX2& mod2) : AbstractMixedSubstitutionModel(mod2),
                                              pmixmodel_(new MixtureOfSubstitutionModels(*mod2.pmixmodel_)),
                                              mapParNamesFromPmodel_(mod2.mapParNamesFromPmodel_),
                                              lParPmodel_(mod2.lParPmodel_)
{
  
}

LLG08_EX2& LLG08_EX2::operator=(const LLG08_EX2& mod2)
{
  AbstractMixedSubstitutionModel::operator=(mod2);

  pmixmodel_=new MixtureOfSubstitutionModels(*mod2.pmixmodel_);
  mapParNamesFromPmodel_=mod2.mapParNamesFromPmodel_;
  lParPmodel_=mod2.lParPmodel_;
  
  return *this;
}

LLG08_EX2::~LLG08_EX2()
{
  if (pmixmodel_)
    delete pmixmodel_;
}

void LLG08_EX2::updateMatrices()
{
  for (unsigned int i=0;i<lParPmodel_.size();i++)
    if (hasParameter(mapParNamesFromPmodel_[lParPmodel_[i].getName()]))
      lParPmodel_[i].setValue(getParameter(mapParNamesFromPmodel_[lParPmodel_[i].getName()]).getValue());
  
  pmixmodel_->matchParametersValues(lParPmodel_);
}

void LLG08_EX2::setFreq(std::map<int,double>& m){
  pmixmodel_->setFreq(m);
  matchParametersValues(pmixmodel_->getParameters());
}

void LLG08_EX2::setVRates(Vdouble & vd){
  pmixmodel_->setVRates(vd);
  matchParametersValues(pmixmodel_->getParameters());
}

/**************** sub model classes *///////////

LLG08_EX2::EmbeddedModel::EmbeddedModel(const ProteicAlphabet* alpha, string name) :
  AbstractReversibleSubstitutionModel(alpha, ""), proportion_(1), name_(name)
{
#include "__LLG08_EX2ExchangeabilityCode"
#include "__LLG08_EX2FrequenciesCode"
#include "__LLG08_EX2RatesProps"
  updateMatrices();
}


