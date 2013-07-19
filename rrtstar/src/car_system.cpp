
#include "car_system.h"
#include <stdarg.h>
#include <cmath>
#include <cstdlib>

#include <iostream>

using namespace buzzmobile;

#define DISCRETIZATION_STEP 0.01

/**
 *	CarState
 */

CarState::CarState () {

	x() = 0;
	y() = 0;
	heading() = 0;
}


CarState::~CarState () {
}


CarState::CarState (const CarState &stateIn) {
	x() = stateIn.x();
	y() = stateIn.y();
	heading() = stateIn.heading();
}


CarState& CarState::operator=(const CarState &stateIn){
    
    if (this == &stateIn)
        return *this;
    
	x() = stateIn.x();
	y() = stateIn.y();
	heading() = stateIn.heading();
    
    return *this;
}


void CarState::getAsVector(int numDimensionsIn, double *vector) const {
	vector[0] = x();
	vector[1] = y();
}

/**
 *	Trajectory
 */

Trajectory::Trajectory () {
    
    endState = NULL;
}


Trajectory::~Trajectory () {
    
    if (endState)
        delete endState;
}


Trajectory::Trajectory (const Trajectory &trajectoryIn) {
    
    endState = new CarState (trajectoryIn.getEndState()); 

}


Trajectory& Trajectory::operator=(const Trajectory &trajectoryIn) {
    
    if (this == &trajectoryIn)
        return *this;
    
    if (endState)
        delete endState;
    
    
    endState = new CarState (trajectoryIn.getEndState());
    
    totalVariation = trajectoryIn.totalVariation;
    
    return *this;
}


double Trajectory::evaluateCost () {
    
    return totalVariation;
}

CarSystem::CarSystem () {
}


CarSystem::~CarSystem () {   
}

int CarSystem::getStateKey (const CarState& stateIn, double* stateKey) {
    
	stateIn.getAsVector(getNumDimensions(), stateKey);
	double *opSize = new double[getNumDimensions()];
	regionOperating.getSizeAsVector(getNumDimensions(), opSize);
    for (int i = 0; i < getNumDimensions(); i++) 
        stateKey[i] =  stateKey[i] / opSize[i];
    
	delete [] opSize;
    return 1;
}

bool CarSystem::isReachingTarget (const CarState &stateIn) {

	double *vector = new double[getNumDimensions()];
	stateIn.getAsVector(getNumDimensions(), vector);
    bool reached = regionGoal.contains(getNumDimensions(), vector);
	delete [] vector;
	return reached;
}

bool CarSystem::IsInCollision (int numDimensionsIn, const double *stateIn) {
    
	bool collision = false;
    for (list<Region*>::iterator iter = obstacles.begin(); iter != obstacles.end(); iter++) {
        
        Region *obstacleCurr = *iter;
        bool collisionFound = true;
        
        if (obstacleCurr->contains(numDimensionsIn, stateIn)) {
            collision = true;
			break;
        }
    }
    return collision;
} 

int CarSystem::sampleState (CarState &randomStateOut) {
    /*
    randomStateOut.setNumDimensions (numDimensions);
    
    for (int i = 0; i < numDimensions; i++) {
        if (i == 1 || true) {
	        randomStateOut.x[i] = (double)rand()/(RAND_MAX + 1.0)*regionOperating.size[i] 
		    - regionOperating.size[i]/2.0;
		} else {
	        randomStateOut.x[i] = (double)rand()/(RAND_MAX + 1.0)*regionOperating.size[i]/2;
		}
    }
    
	//rotate to fit within our search window
	//NOTE: currently assumes 2D coordinates
//	double heading = 0;//3.5 * M_PI / 2;
	double oldX = randomStateOut.x[1];
	double oldY = randomStateOut.x[0];
//	randomStateOut.x[1] = oldX * sin(heading) + oldY * cos(heading) + regionOperating.center[1];
//	randomStateOut.x[0] = oldX * cos(heading) - oldY * sin(heading) + regionOperating.center[0];
	
    if (IsInCollision (numDimensions, randomStateOut))
        return 0;
    */
    return 1;
}

int CarSystem::extendTo (const CarState &stateFromIn, const CarState &stateTowardsIn, Trajectory &trajectoryOut, bool &exactConnectionOut) {
    
	int numDimensions = getNumDimensions(); // for convenience
	
    double *stateVec = new double[numDimensions];
	stateTowardsIn.getAsVector(numDimensions, stateVec);
    if (IsInCollision (numDimensions, stateVec))
        return 0;

    double *dists = new double[numDimensions];
	//NOTE: reuse dists, for efficiency
	stateFromIn.getAsVector(numDimensions, dists);
    for (int i = 0; i < numDimensions; i++) 
        dists[i] = stateVec[i] - dists[i];
    
    double distTotal = 0.0;
    for (int i = 0; i < numDimensions; i++) 
        distTotal += dists[i]*dists[i];
    distTotal = sqrt (distTotal);
    
    double incrementTotal = distTotal/DISCRETIZATION_STEP;
    
    // normalize the distance according to the discretization step
    for (int i = 0; i < numDimensions; i++)
        dists[i] /= incrementTotal;
    
    int numSegments = (int)floor(incrementTotal);
    
	stateFromIn.getAsVector(numDimensions, stateVec);
    
    for (int i = 0; i < numSegments; i++) {
        
        if (IsInCollision (numDimensions, stateVec))  
            return 0;
        
        for (int i = 0; i < numDimensions; i++)
            stateVec[i] += dists[i];
    }
    
	if (trajectoryOut.endState) {
		delete trajectoryOut.endState;
		trajectoryOut.endState = NULL;
	}
    trajectoryOut.endState = new CarState (stateTowardsIn);
    trajectoryOut.totalVariation = distTotal;
    
    delete [] dists;
    delete [] stateVec;
    
    exactConnectionOut = true;
    
    return 1;
}


double CarSystem::evaluateExtensionCost (const CarState& stateFromIn, const CarState& stateTowardsIn, bool &exactConnectionOut) {
    
    
    exactConnectionOut = true;
    
    double distTotal = 0.0;
    double *arrFrom = new double[getNumDimensions()];
	stateFromIn.getAsVector(getNumDimensions(), arrFrom);
    double *arrTowards = new double[getNumDimensions()];
	stateTowardsIn.getAsVector(getNumDimensions(), arrTowards);
    for (int i = 0; i < getNumDimensions(); i++) {
        double distCurr = arrTowards[i] - arrFrom[i];
        distTotal += distCurr*distCurr;
    }
    
	delete [] arrFrom;
	
	delete [] arrTowards;
    return sqrt(distTotal);
    
}


int CarSystem::getTrajectory (const CarState& stateFromIn, const CarState& stateToIn, list<double*>& trajectoryOut) {
    
    double *stateArr = new double[getNumDimensions()];
	stateToIn.getAsVector(getNumDimensions(), stateArr);
    trajectoryOut.push_front (stateArr);
    
    return 1;
    
}


double CarSystem::evaluateCostToGo (const CarState& stateIn) {
    
    double radius = 0.0;
    double *arr = new double[getNumDimensions()];
	regionGoal.getSizeAsVector(getNumDimensions(), arr);
    for (int i = 0; i < getNumDimensions(); i++) 
        radius += arr[i] * arr[i];
    radius = sqrt(radius);

    double dist = 0.0;
	regionGoal.getCenterAsVector(getNumDimensions(), arr);
    double *stateArr = new double[getNumDimensions()];
	stateIn.getAsVector(getNumDimensions(), stateArr);
	
    for (int i = 0; i < getNumDimensions(); i++) 
        dist += (stateArr[i] - arr[i])*(stateArr[i] - arr[i]);
    dist = sqrt(dist);
    
	delete [] arr;
	delete [] stateArr;
    return dist - radius;
}
