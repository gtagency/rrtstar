#define LIBBOT_PRESENT 0

#include <iostream>
#include <ctime>

#include "rrts.hpp"
//#include "system_single_integrator.h"
#include "car_system.h"
#include "publisher.h"

using namespace RRTstar;
using namespace buzzmobile;

using namespace std;

typedef Planner<CarState,Trajectory,CarSystem> planner_t;
typedef Vertex<CarState,Trajectory,CarSystem> vertex_t;
/*
int min(int a, int b);
void printXY(double *values);
void updateSearchRoot(planner_t& planner, System& system, double *waypoint, double delta);
void updateIncrementalRegionGoal(System& system, double *goal, double *step);

void updateIncrementalRegionGoal(System& system, double *goal, double *step) {	
    system.regionGoal.center[0] = min(system.regionGoal.center[0] + step[0], goal[0]);
    system.regionGoal.center[1] = min(system.regionGoal.center[1] + step[1], goal[1]);
    //system.regionGoal.center[2] = 1.0;
    system.regionGoal.size[0] = 1.0;
    system.regionGoal.size[1] = 1.0;
    //system.regionGoal.size[2] = 10;
}

void updateSearchRoot(planner_t& planner, System& system, double *waypoint, double delta) {
	State& rootState = system.getRootState();
	double angle = atan2(waypoint[0] - rootState[0], waypoint[1] - rootState[1]);
	double deltaX = delta * sin(angle);
	double deltaY = delta * cos(angle);
	double newRoot[] = {rootState[0] + deltaX, rootState[1] + deltaY};
	rootState[0] = newRoot[0];
	rootState[1] = newRoot[1];
	
	system.setHeading(2 * M_PI - angle);

    // (Re) Initialize the planner
	cout << "Reiniting the planner" << endl;
    planner.initialize ();
}
*/
int min(int a, int b) {
	return a < b ? a : b;
}

void printXY(string prefix, double *values) {
	cout << prefix << "y: " << values[0] << ", x: " << values[1] << endl;	
}

int main () {

    planner_t rrts;
    
    cout << "RRTstar is alive" << endl;
    
	Publisher<planner_t, CarSystem> publisher;

    // Create the dynamical system
    CarSystem system;
    
    // Define the operating region
	system.regionOperating = Region(2, 0, 0, 50, 50);
    
    // Define the goal region
    int step = 4;
	system.regionGoal = Region(2, 0, 0, 20, 20);
	
	double st[] = {4.0, 4.0};
	//updateIncrementalRegionGoal(system, goal, st);

	cout << "Starting goal: " << system.regionGoal;
    
    // Define the obstacle region
	
	// Block in lane
    system.obstacles.push_front(new Region(2, 5, 3, 2, 2));

	// Block in open
    system.obstacles.push_front(new Region(2, 10, 10, 2, 2));

	// Middle wall
    system.obstacles.push_front(new Region(2, -4, 2, 16, 2));
	
	// Right wall
    system.obstacles.push_front(new Region(2, 0, -2, 24, 2));

	// Top wall
    system.obstacles.push_front(new Region(2, 11, 3, 2, 8));

	// Left wall
    system.obstacles.push_front(new Region(2, 0, 7, 24, 2));

	// Bottom wall
    system.obstacles.push_front(new Region(2, -12, 0, 2, 6));

    publisher.publishEnvironment (system.regionOperating, system.regionGoal, system.obstacles);

    // Add the system to the planner
    rrts.setSystem (system);
    
    // Set up the starting position
	double startPos[] = {-8.0, 0.0};
    CarState &myState = system.getRootState();
	myState.x() = startPos[0];
	myState.y() = startPos[1];
	myState.heading() = HEADING_NORTH;

    // Initialize the planner
    rrts.initialize ();
    
    // This parameter should be larger than 1.5 for asymptotic 
    //   optimality. Larger values will weigh on optimization 
    //   rather than exploration in the RRT* algorithm. Lower 
    //   values, such as 0.1, should recover the RRT.
    rrts.setGamma (1.5);

    clock_t start = clock();
	
	int steps = 0;
	int maxSteps = 200;
	
	double velocity = 2.2352; //m /s = 5mph
	double *waypoint = new double[2];
	do {
		
	    clock_t move_start = clock();
		
		int iters = 0;
		while (&rrts.getBestVertex() == NULL) {
	        rrts.iteration();
			if (++iters % 1000 == 0) {
			    publisher.publishTree (rrts, system);    
			}
		}
		cout << "Iterations: " << iters << endl;
		
	    publisher.publishTree (rrts, system);    
		publisher.publishTraj (rrts, system);
		
		list<double*> stateList;
		rrts.getBestTrajectory(stateList);
		cout << "States: " << stateList.size() << endl;
		int trajInx = 0;
		
	    for (list<double*>::iterator iter = stateList.begin(); iter != stateList.end(); iter++) {
	        double* stateRef = *iter;
			if (trajInx++ == 1) {
				waypoint[0] = stateRef[0];
				waypoint[1] = stateRef[1];
			}
	        printXY("Trajectory: ", stateRef);
			
	        delete [] stateRef;
	    }

	    clock_t move_end = clock();    		
		
		double elapsed = ((double)(move_end-move_start))/CLOCKS_PER_SEC;
		printXY("Navigating to: ", waypoint);
		cout << "Moved: " << velocity * elapsed << endl;
/*		updateSearchRoot(rrts, system, waypoint, velocity * elapsed);
		
		bool atRef = system.isReachingTarget(system.getRootState());
		if (atRef) {
			updateIncrementalRegionGoal(system, goal, st);
		}
		*/
		double rs[] = {system.getRootState().y(), system.getRootState().x()};
		printXY("New Root: ", rs);
		cout << "New Heading: " << system.getRootState().heading() << endl;
		cout << "New Goal: " << system.regionGoal;
	    clock_t finish = clock();
	    cout << "Time : " << ((double)(finish-start))/CLOCKS_PER_SEC << endl;

		//usleep(1000*1000);
	} while (++steps < maxSteps);

	while (&rrts.getBestVertex() == NULL) {
        rrts.iteration();
	}
	
	/*
	
    // Run the algorithm for 10000 iteartions
    for (int i = 0; i < 10000; i++) {
        rrts.iteration ();
	    publisher.publishTree (rrts, system);
    
	    publisher.publishTraj (rrts, system);
		if (&rrts.getBestVertex() != NULL) {
			cout << "Found best vertex in " << i << " iterations" << endl;
			break;
		}
		//usleep(100 * 1000);
    }
	*/
    clock_t finish = clock();
    cout << "Time : " << ((double)(finish-start))/CLOCKS_PER_SEC << endl;
    
    publisher.publishTree (rrts, system);
    publisher.publishTraj (rrts, system);
    
	list<double*> stateList;
	rrts.getBestTrajectory(stateList);
	cout << "States: " << stateList.size() << endl;
	int trajInx = 0;
	
    for (list<double*>::iterator iter = stateList.begin(); iter != stateList.end(); iter++) {
        double* stateRef = *iter;
        printXY("Trajectory: ", stateRef);
		
        delete [] stateRef;
    }
	
    return 1;
}
