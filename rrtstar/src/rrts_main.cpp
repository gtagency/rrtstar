#define LIBBOT_PRESENT 0

#include <iostream>
#include <ctime>

#include <bot_core/bot_core.h>

#include <lcm/lcm.h>

#include <lcmtypes/lcmtypes.h>

#include "rrts.hpp"
#include "system_single_integrator.h"


using namespace RRTstar;
using namespace SingleIntegrator;

using namespace std;



typedef Planner<State,Trajectory,System> planner_t;
typedef Vertex<State,Trajectory,System> vertex_t;

int min(int a, int b);
void printXY(double *values);
void updateSearchRoot(planner_t& planner, System& system, double *waypoint, double delta);
void updateIncrementalRegionGoal(System& system, double *goal, double *step);

int publishTree (lcm_t *lcm, planner_t& planner, System& system);
int publishTraj (lcm_t *lcm, planner_t& planner, System& system);
int publishEnvironment (lcm_t *lcm, region& regionOperating, region& regionGoal, list<region*>& obstacles);

void updateIncrementalRegionGoal(System& system, double *goal, double *step) {	
    system.regionGoal.center[0] = min(system.regionGoal.center[0] + step[0], goal[0]);
    system.regionGoal.center[1] = min(system.regionGoal.center[1] + step[1], goal[1]);
    //system.regionGoal.center[2] = 1.0;
    system.regionGoal.size[0] = 1.0;
    system.regionGoal.size[1] = 1.0;
    //system.regionGoal.size[2] = 10;
}

void updateSearchRoot(planner_t& planner, System& system, double *waypoint, double delta) {
/*    vertex_t &root = planner.getRootVertex();  
    State &rootState = root.getState();
	double newRoot[] = {min(waypoint[0], rootState[0] + delta), min(waypoint[1], rootState[1] + delta)};
	rootState[0] = newRoot[0];
	rootState[1] = newRoot[1];
//	rootState[2] = position[2];
    // (Re) Initialize the planner
	cout << "Reiniting the planner" << endl;
    planner.initialize ();
	return waypoint[0] == newRoot[0] && waypoint[1] == newRoot[1];*/
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

int min(int a, int b) {
	return a < b ? a : b;
}

void printXY(string prefix, double *values) {
	cout << prefix << "y: " << values[0] << ", x: " << values[1] << endl;	
}

int main () {
    
    
    planner_t rrts;
    
    cout << "RRTstar is alive" << endl;
    
    
    // Get lcm
    lcm_t *lcm = bot_lcm_get_global (NULL);
    
    // Create the dynamical system
    System system;
    
    // Three dimensional configuration space
    system.setNumDimensions (2);
    
    // Define the operating region
    system.regionOperating.setNumDimensions(2);
    system.regionOperating.center[0] = 0.0;
    system.regionOperating.center[1] = 0.0;
//    system.regionOperating.center[2] = 0.0;
    system.regionOperating.size[0] = 50.0;
    system.regionOperating.size[1] = 50.0;
  //  system.regionOperating.size[2] = 50.0;
    
    // Define the goal region
    int step = 4;
	double goal[] = {20.0, 20.0};
    system.regionGoal.setNumDimensions(2);
	system.regionGoal.center[0] = 0;
	system.regionGoal.center[1] = 0;
	
	double st[] = {4.0, 4.0};
	updateIncrementalRegionGoal(system, goal, st);

	printXY("Starting goal: ", system.regionGoal.center);
    
    // Define the obstacle region
	
    region *obstacle;
    
    obstacle = new region;
    obstacle->setNumDimensions(2);
    obstacle->center[0] = 10;
    obstacle->center[1] = 10;
  //  obstacle->center[2] = 2;
    obstacle->size[0] = 2;
    obstacle->size[1] = 2;
//    obstacle->size[2] = 2;
    
    system.obstacles.push_front (obstacle);  // Add the obstacle to the list

    obstacle = new region;
    obstacle->setNumDimensions(2);
    obstacle->center[0] = -4;
    obstacle->center[1] = 2;
  //  obstacle->center[2] = 2;
    obstacle->size[0] = 16;
    obstacle->size[1] = 2;
//    obstacle->size[2] = 2;
    
    system.obstacles.push_front (obstacle);  // Add the obstacle to the list
	
    obstacle = new region;
    obstacle->setNumDimensions(2);
    obstacle->center[0] = 0;
    obstacle->center[1] = -2;
  //  obstacle->center[2] = 2;
    obstacle->size[0] = 24;
    obstacle->size[1] = 2;
//    obstacle->size[2] = 2;

    system.obstacles.push_front (obstacle);  // Add the obstacle to the list

    obstacle = new region;
    obstacle->setNumDimensions(2);
    obstacle->center[0] = 11;
    obstacle->center[1] = 3;
  //  obstacle->center[2] = 2;
    obstacle->size[0] = 2;
    obstacle->size[1] = 8;
//    obstacle->size[2] = 2;

    system.obstacles.push_front (obstacle);  // Add the obstacle to the list

    obstacle = new region;
    obstacle->setNumDimensions(2);
    obstacle->center[0] = 0;
    obstacle->center[1] = 7;
  //  obstacle->center[2] = 2;
    obstacle->size[0] = 24;
    obstacle->size[1] = 2;
//    obstacle->size[2] = 2;

    system.obstacles.push_front (obstacle);  // Add the obstacle to the list

    obstacle = new region;
    obstacle->setNumDimensions(2);
    obstacle->center[0] = -12;
    obstacle->center[1] = 0;
  //  obstacle->center[2] = 2;
    obstacle->size[0] = 2;
    obstacle->size[1] = 6;
//    obstacle->size[2] = 2;

    system.obstacles.push_front (obstacle);  // Add the obstacle to the list
    publishEnvironment (lcm, system.regionOperating, system.regionGoal, system.obstacles);

    // Add the system to the planner
    rrts.setSystem (system);
    
    // Set up the root vertex
	
	double rootPos[] = {-8.0, 0.0};
//	updateSearchRoot(rrts, rootPos, 0);
//    vertex_t &root = rrts.getRootVertex();  
    State &rootState = system.getRootState();
	rootState[0] = rootPos[0];
	rootState[1] = rootPos[1];
//	rootState[2] = position[2];
	system.setHeading(3*M_PI/2);
    // (Re) Initialize the planner
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
			    publishTree (lcm, rrts, system);    
			}
		}
	    publishTree (lcm, rrts, system);    
	    publishTraj (lcm, rrts, system);

		
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
		updateSearchRoot(rrts, system, waypoint, velocity * elapsed);
		
		bool atRef = system.isReachingTarget(system.getRootState());
		if (atRef) {
			updateIncrementalRegionGoal(system, goal, st);
		}

		double rs[] = {rrts.getRootVertex().getState()[0], rrts.getRootVertex().getState()[1]};
		printXY("New Root: ", rs);
		cout << "New Heading: " << system.getHeading() << endl;
		printXY("New Goal: ", system.regionGoal.center);
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
	    publishTree (lcm, rrts, system);
    
	    publishTraj (lcm, rrts, system);
		if (&rrts.getBestVertex() != NULL) {
			cout << "Found best vertex in " << i << " iterations" << endl;
			break;
		}
		//usleep(100 * 1000);
    }
	*/
    clock_t finish = clock();
    cout << "Time : " << ((double)(finish-start))/CLOCKS_PER_SEC << endl;
    
    publishTree (lcm, rrts, system);
    
    publishTraj (lcm, rrts, system);
    
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



int publishEnvironment (lcm_t *lcm, region& regionOperating, region& regionGoal, list<region*>& obstacles) {
    
    // Publish the environment
    lcmtypes_environment_t *environment = (lcmtypes_environment_t*) malloc (sizeof(lcmtypes_environment_t));
    
    environment->operating.center[0] = regionOperating.center[0];
    environment->operating.center[1] = regionOperating.center[1];
    //environment->operating.center[2] = regionOperating.center[2];
    environment->operating.size[0] = regionOperating.size[0];
    environment->operating.size[1] = regionOperating.size[1];
    //environment->operating.size[2] = regionOperating.size[2];

    environment->goal.center[0] = regionGoal.center[0];
    environment->goal.center[1] = regionGoal.center[1];
    //environment->goal.center[2] = regionGoal.center[2];
    environment->goal.size[0] = regionGoal.size[0];
    environment->goal.size[1] = regionGoal.size[1];
    //environment->goal.size[2] = regionGoal.size[2];
    
    
    environment->num_obstacles = obstacles.size();
    
    if (environment->num_obstacles > 0) 
        environment->obstacles = (lcmtypes_region_3d_t *) malloc (sizeof(lcmtypes_region_3d_t));
    
    int idx_obstacles = 0;
    for (list<region*>::iterator iter = obstacles.begin(); iter != obstacles.end(); iter++){
        
        region* obstacleCurr = *iter;
        
        environment->obstacles[idx_obstacles].center[0] = obstacleCurr->center[0];
        environment->obstacles[idx_obstacles].center[1] = obstacleCurr->center[1];
       // environment->obstacles[idx_obstacles].center[2] = obstacleCurr->center[2];
        environment->obstacles[idx_obstacles].size[0] = obstacleCurr->size[0];
        environment->obstacles[idx_obstacles].size[1] = obstacleCurr->size[1];
        //environment->obstacles[idx_obstacles].size[2] = obstacleCurr->size[2];
        
        idx_obstacles++;
    }
    
    lcmtypes_environment_t_publish (lcm, "ENVIRONMENT", environment);
    
    return 1;
}


int publishTraj (lcm_t *lcm, planner_t& planner, System& system) {
    
    
    cout << "Publishing trajectory -- start" << endl;
    
    vertex_t& vertexBest = planner.getBestVertex ();
    
    if (&vertexBest == NULL) {
        cout << "No best vertex" << endl;
        return 0;
    }
    
    list<double*> stateList;
    
    planner.getBestTrajectory (stateList);
    
    lcmtypes_trajectory_t *opttraj = (lcmtypes_trajectory_t *) malloc (sizeof (lcmtypes_trajectory_t));
    
    opttraj->num_states = stateList.size();
    opttraj->states = (lcmtypes_state_t *) malloc (opttraj->num_states * sizeof (lcmtypes_state_t));
    
    int stateIndex = 0;
    for (list<double*>::iterator iter = stateList.begin(); iter != stateList.end(); iter++) {
        
        double* stateRef = *iter;
        opttraj->states[stateIndex].x = stateRef[0];
        opttraj->states[stateIndex].y = stateRef[1];
        if (system.getNumDimensions() > 2)
            opttraj->states[stateIndex].z = stateRef[2];
        else
            opttraj->states[stateIndex].z = 0.0;
        
        delete [] stateRef;
        
        stateIndex++;
    }
    
    
    lcmtypes_trajectory_t_publish (lcm, "TRAJECTORY", opttraj);
    
    lcmtypes_trajectory_t_destroy (opttraj);
    
    cout << "Publishing trajectory -- end" << endl;
    
    
    
    return 1;
}




int publishTree (lcm_t *lcm, planner_t& planner, System& system) {
    
    
    cout << "Publishing the tree -- start" << endl;
    
    bool plot3d = (system.getNumDimensions() > 2);
    
    lcmtypes_graph_t *graph = (lcmtypes_graph_t *) malloc (sizeof (lcmtypes_graph_t));
    graph->num_vertices = planner.numVertices; 
    
    
    if (graph->num_vertices > 0) {    
        
        graph->vertices = (lcmtypes_vertex_t *) malloc (graph->num_vertices * sizeof(lcmtypes_vertex_t));
        
        int vertexIndex = 0;
        for (list<vertex_t*>::iterator iter = planner.listVertices.begin(); iter != planner.listVertices.end(); iter++) {
            
            
            vertex_t &vertexCurr = **iter;
            State &stateCurr = vertexCurr.getState ();
            
            graph->vertices[vertexIndex].state.x = stateCurr[0];
            graph->vertices[vertexIndex].state.y = stateCurr[1];
            if (plot3d) 
                graph->vertices[vertexIndex].state.z = stateCurr[2];
            else 
                graph->vertices[vertexIndex].state.z = 0.0;
            
            vertexIndex++;
            
        }
        
    }
    else {
        graph->vertices = NULL;
    }
    
    if (graph->num_vertices > 1) {
        
        graph->num_edges = graph->num_vertices - 1;
        graph->edges = (lcmtypes_edge_t *) malloc (graph->num_edges * sizeof(lcmtypes_edge_t));
        
        
        int edgeIndex = 0;
        for (list<vertex_t*>::iterator iter = planner.listVertices.begin(); iter != planner.listVertices.end(); iter++) {
            
            vertex_t &vertexCurr = **iter;
            
            vertex_t &vertexParent = vertexCurr.getParent();
            
            if ( &vertexParent == NULL ) 
                continue;
            
            State &stateCurr = vertexCurr.getState ();
            State &stateParent = vertexParent.getState();
            
            
            graph->edges[edgeIndex].vertex_src.state.x = stateParent[0];
            graph->edges[edgeIndex].vertex_src.state.y = stateParent[1];
            if (plot3d)
                graph->edges[edgeIndex].vertex_src.state.z = stateParent[2];
            else 
                graph->edges[edgeIndex].vertex_src.state.z = 0.0;
            
            
            graph->edges[edgeIndex].vertex_dst.state.x = stateCurr[0];
            graph->edges[edgeIndex].vertex_dst.state.y = stateCurr[1];
            if (plot3d)
                graph->edges[edgeIndex].vertex_dst.state.z = stateCurr[2];
            else 
                graph->edges[edgeIndex].vertex_dst.state.z = 0.0;
            
            graph->edges[edgeIndex].trajectory.num_states = 0;
            graph->edges[edgeIndex].trajectory.states = NULL;
            
            edgeIndex++;
        }
        
    }
    else {
        graph->num_edges = 0;
        graph->edges = NULL;
    }
    
    lcmtypes_graph_t_publish (lcm, "GRAPH", graph);
    
    lcmtypes_graph_t_destroy (graph);
    
    cout << "Publishing the tree -- end" << endl;
    
    return 1;
}

