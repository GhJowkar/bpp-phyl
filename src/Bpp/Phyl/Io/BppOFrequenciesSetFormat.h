//
// File: Bpp0FrequenciesSetFormat.h
// Created by: Laurent Guéguen
// Created on: lundi 9 juillet 2012, à 12h 57
//

/*
  Copyright or © or Copr. Bio++ Development Team, (November 16, 2004)

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

#ifndef _BPPOFREQUENCIESSETFORMAT_H_
#define _BPPOFREQUENCIESSETFORMAT_H_

#include "IoFrequenciesSetFactory.h"

namespace bpp
{

  /**
   * @brief Substitution model I/O in BppO format.
   *
   * Creates a new substitution model object according to model description syntax
   * (see the Bio++ Progam Suite manual for a detailed description of this syntax).
   *
   */
  
  class BppOFrequenciesSetFormat:
    public IFrequenciesSet,
    public OFrequenciesSet
  {
  public:
    BppOFrequenciesSetFormat() {}
    virtual ~BppOFrequenciesSetFormat() {}

  public:
    const std::string getFormatName() const { return "BppO"; }

    const std::string getFormatDescription() const { return "Bpp Options format."; }


    /**
     * @brief Read a frequencies set from a string.
     *
     * @param alphabet         The alpabet to use in the model.
     * @param freqDescription  A string describing the frequencies set.
     * @param unparsedParameterValues [out] a map that will contain
     *                                all the frequencies set parameters names
     *                                and their corresponding unparsed
     *                                value, if they were found.
     * @return A new FrequenciesSet object according to options specified.
     * @throw Exception if an error occured.
     */

    FrequenciesSet* read(const Alphabet* alphabet,
                         const std::string& freqDescription,
                         std::map<std::string, std::string>& unparsedParameterValues);

    /**
     * @brief Write a substitution model to a stream.
     *
     * @param pfreqset A pointer towards a frequencies set object;
     * @param out The output stream;
     * @param writtenNames is the vector of the written
     * parameters so far [in, out];
     */
    
    void write(const FrequenciesSet* pfreqset,
               OutputStream& out,
               std::vector<std::string>& writtenNames) const;

  };

} //end of namespace bpp.

#endif //_BPPOFREQUENCIESSETFORMAT_H_
