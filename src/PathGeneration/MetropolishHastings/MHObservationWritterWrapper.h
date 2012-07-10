/*
 * MHObservationWritterWrapper.h
 *
 *  Created on: Jul 5, 2012
 *      Author: jchen
 */

#ifndef MHOBSERVATIONWRITTERWRAPPER_H_
#define MHOBSERVATIONWRITTERWRAPPER_H_

#include "patObservationWritter.h"
#include "MHStateProcessor.h"
#include "MHPath.h"
class MHObservationWritterWrapper: public patObservationWritter, public MHStateProcessor<
		MHPath> {
public:
	MHObservationWritterWrapper();
	virtual ~MHObservationWritterWrapper();

	MHObservationWritterWrapper(std::string folder, const int sampleInterval) :
		patObservationWritter::patObservationWritter(folder, sampleInterval) {

	}
	;
	void end(){
		patObservationWritter::end();
	};

	void processState(const MHPath& path, const double log_weight){
		patObservationWritter::processState(path,log_weight);
	}
	;
	void start(){
		patObservationWritter::start();
	};

};


#endif /* MHOBSERVATIONWRITTERWRAPPER_H_ */