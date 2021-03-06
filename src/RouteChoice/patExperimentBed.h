/*
 * patExperimentBed.h
 *
 *  Created on: Jul 11, 2012
 *      Author: jchen
 */

#ifndef PATEXPERIMENTBED_H_
#define PATEXPERIMENTBED_H_

#include "patNetworkEnvironment.h"
#include "patTransportMode.h"
#include "patRandomNumber.h"

#include "patNode.h"
#include "patLinkAndPathCost.h"
#include "MHSamplingWeightFunction.h"
#include "patUtilityFunction.h"
#include "patObservation.h"
#include "MHPathGenerator.h"
#include "RWPathGenerator.h"
#include "patMultiModalPath.h"


#include "MHNodeInsertionProbability.h"
#include <map>
#include <vector>
class patExperimentBed {
public:
	patExperimentBed( bool network_real,
			bool observation_real, TransportMode transport_mode, unsigned nbr_observations=INT_MAX);


	void checkExperimentFolder() const;
	void checkChoiceSetFolder() const;
	void checkObservationFolder() const;

	void testNetwork() const;
	/**
	 * Init the network environment m_network_environment.
	 */
	void initiateNetworks();

	/**
	 * Export network to kml and shp formats.
	 */

	void exportNetwork();

	void writeNetworkToDB() const;
	/**
	 * Initiate functions for MH and RW
	 */
	void initCostFunctions();


	/**
	 * Get files in m_observation_folder.
	 */
	vector<string> getObservationFiles();

	/**
	 * Read synthetic observations.
	 */
	void readSyntheticObservations();

	/**
	 * Read real observation.
	 */
	void readRealObservations();


	/**
	 * Read observations in m_observation_folder, and store in m_observations
	 */
	void readObservations();
	void simulateObservationError() ;

	/**
	 * Read universal choice set in "universal_choice_set.kml" if exists.
	 * Read as m_universal_choice_set.
	 * Otherwise m_universal_choice_set is empty.
	 */
	void readUniversalChoiceSet();

	/*
	 * Sample choice set with od.
	 * The od is specified in the configuration file originId, destinationId.
	 * @param, count is the number of chocie sets to be gererated.
	 * The generated choice set will be indexed with integer.
	 * The results will be in m_choice_set_folder
	 */
	void sampleChoiceSetWithOd(const unsigned count);

	/*
	 * Sample choice set according to the observations in m_observation_folder.
	 */
	void sampleChoiceSet();

//	void sampleEqualProbability();
	/**
	 * Simulate observations according to the the specified mh utilities.
	 * Notice: the parameters are in mh, not utility!
	 */
	void simulateObservations();

	/**
	 * Enumerate paths with MH sampling algorithm.
	 * It is only used in real network where the actual universal path set can not be enumerated.
	 * It uses parameters with higher variances (mh_link_scale=0.1).
	 * Record a path whenever a shuffle occurs.
	 * WARMUP_ITERATIONS 0, SAMPLEINTERVAL_ELEMENT 1, SAMPLE_COUNT 1000, 000.
	 *
	 * @return a choice set as universal_choice_set.kml in the observationDirecotry.
	 */
	void enumerateMHPaths();


	/**
	 * Get boudingbox from the GPS files that correspond to the observation file.
	 */
	patGeoBoundingBox getBoundingBoxFromGPS() ;
	void verifySamplingResult()  ;
	/**
	 * Read chocie set (in m_choice_set_folder) and put them in m_observations.
	 */
	void readChoiceSetForObservations();
	virtual ~patExperimentBed();
	void analyzeChoiceSet();
	void writeBiogeme();
	void analyzeOBS();
	void writeChoiceSetSHP();
	void kml2SHP(const string& file_name) const;
	void obs2SHP();
protected:
	 string m_experiment_folder;
	 string m_observation_folder;
	 string m_choice_set_foler;

	bool m_network_real;
	bool m_observation_real;

	unsigned m_nbr_observations;

	const patRandomNumber m_rnd;

	string m_algorithm;

	TransportMode m_transport_mode;
	patLinkAndPathCost* m_mh_router_link_cost;
	MHWeightFunction* m_mh_weight_function;
	MHPathGenerator* m_mh_path_generator;

	patLinkAndPathCost* m_rw_router_link_cost;
	RWPathGenerator* m_rw_path_generator;

	patUtilityFunction* m_utility_function;

	MHNodeInsertionProbability* m_nip_calculator;
	patNetworkEnvironment* m_network_environment;

	std::vector<patObservation> m_observations;


	std::map<const patMultiModalPath, double> m_obs_path_probas;
	std::map<const patMultiModalPath, double> m_path_size;

	patChoiceSet m_universal_choice_set;
};

#endif /* PATEXPERIMENTBED_H_ */
