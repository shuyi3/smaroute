patTravlerSet::patTravlerSet(){

}
patTraveler* patTravlerSet::addTraveler(const patTraveler& theTraveler){
	pair<set<patTraveler>::iterator,bool> insertResult = travelerSet.insert(theTraveler);
	return &(*(insertResult->first));
}

patTraveler* patTravlerSet::addTraveler(const patULong& theTravelerId){
	patTraveler* travelerFound = findTraveler(theTravelerId);
	if(travelerFound!=NULL){
		return travelerFound;
	}
	else{
		return addTraveler(patTraveler(theTravelerId));
	}
}

patTraveler* patTravlerSet::findTraveler(const patULong& theTravelerId){
	patTraveler travelerToFind(theTravelerId);
	set<patTravler>::iterator travelerFound = travelerSet.find(travelerToFind);
	if(travelerFound == travelerSet.end()){
		return NULL;
	}
	return &(*travelerFound);
}

set<patTraveler>* patTravlerSet::getAllTravelers(){
	return &travelerSet;
}

patULong patTravlerSet::getNumberofObservations(){
	patULong nbrOfObservations = 0;
	for(set<patTraveler>::iterator travelerIter = travelerSet.begin();
							travelerIter !=travelerSet.end();
							++travelerIter){
		nbrOfObservations += travelerIter->getNumberOfObservations;
	}
	return nbrOfObservations;
}