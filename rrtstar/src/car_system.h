
#ifndef _CAR_SYSTEM_H
#define _CAR_SYSTEM_H

#include <stdarg.h>
#include "region.h"
#include <list>


namespace buzzmobile {

	#define NUM_DIM 2

	#define HEADING_EAST  (0*M_PI/2)
	#define HEADING_SOUTH (1*M_PI/2)
	#define HEADING_WEST  (2*M_PI/2)
	#define HEADING_NORTH (3*M_PI/2)
   
	class CarState {
        
        double _x;
		double _y;
		double _heading;
        
    public:
        
        /*!
         * \brief State constructor
         *
         * More elaborate description
         */
        CarState ();
        
        /*!
         * \brief State desctructor
         *
         * More elaborate description
         */
        ~CarState ();
        
        /*!
         * \brief State copy constructor
         *
         * More elaborate description
         */
        CarState (const CarState& stateIn);
        
        /*!
         * \brief State assignment operator
         *
         * More elaborate description
         */
        CarState& operator= (const CarState& stateIn);
        
        /*!
         * \brief Get the state parameters as a vector
         *
         * More elaborate description
         */
		void getAsVector(int numDimensionsIn, double *vector) const;
		
		/*!
		 * \brief X coordinate of the car position.
		 *
	     */
	    double& x() { return _x; }
 	    double x() const { return _x; }

		/*!
		 * \brief Y coordinate of the car position.
		 *
	     */
		double& y() { return _y; }
 		double y() const { return _y; }
		
		/*!
		 * \brief Heading of the car
		 *
	     */
		double& heading() { return _heading; }
 		double heading() const { return _heading; }
        
//        friend class System;
  //      friend class Trajectory;
	};

   /*!
    * \brief Trajectory Class.
    *
    * A more elaborate description of the State class
    */
   class Trajectory {
       
   public:    

       CarState *endState; 
       double totalVariation;  
       
       /*!
        * \brief Trajectory constructor
        *
        * More elaborate description
        */
       Trajectory ();
       
       /*!
        * \brief Trajectory destructor
        *
        * More elaborate description
        */
       ~Trajectory ();
       
       /*!
        * \brief Trajectory copy constructor
        *
        * More elaborate description
        *
        * \param trajectoryIn The trajectory to be copied.
        *
        */
       Trajectory (const Trajectory& trajectoryIn);
       
       /*!
        * \brief Trajectory assignment constructor
        *
        * More elaborate description
        *
        * \param trajectoryIn the trajectory to be copied.
        *
        */
       Trajectory& operator= (const Trajectory& trajectoryIn);
       
       /*!
        * \brief Returns a reference to the end state of this trajectory.
        *
        * More elaborate description
        */
       CarState& getEndState () {return *endState;}
       
       /*!
        * \brief Returns a reference to the end state of this trajectory (constant).
        *
        * More elaborate description
        */
       CarState& getEndState () const {return *endState;}
       
       /*!
        * \brief Returns the cost of this trajectory.
        *
        * More elaborate description
        */
       double evaluateCost ();
   };
   
   
    /*!
     * \brief System Class.
     *
     * A more elaborate description of the State class
     */
    class CarSystem {
       
	    bool IsInCollision (int numDimensionsIn, const double *stateIn);
       
        CarState rootState;

    public:    
        
        /*!
         * \brief The operating region
         *
         * More elaborate description
         */
        Region regionOperating;

        /*!
         * \brief The goal region
         *
         * More elaborate description
         */
        Region regionGoal;        
       
        /*!
         * \brief The list of all obstacles
         *
         * More elaborate description
         */
        std::list<Region*> obstacles;
        
        /*!
         * \brief System constructor
         *
         * More elaborate description
         */
        CarSystem ();
        
        /*!
         * \brief System destructor
         *
         * More elaborate description
         */
        ~CarSystem ();
        
        /*!
         * \brief Returns the dimensionality of the Euclidean space.
         *
         * A more elaborate description.
         */
        int getNumDimensions () {return NUM_DIM;}
        
        /*!
         * \brief Returns a reference to the root state.
         *
         * A more elaborate description.
         */
        CarState& getRootState () {return rootState;}
        
        /*!
         * \brief Returns the statekey for the given state.
         *
         * A more elaborate description.
         *
         * \param stateIn the given state
         * \param stateKey the key to the state. An array of dimension getNumDimensions()
         *
         */
        int getStateKey (const CarState &stateIn, double *stateKey);
        
        /*!
         * \brief Returns true of the given state reaches the target.
         *
         * A more elaborate description.
         */
        bool isReachingTarget (const CarState &stateIn);
        
        /*!
         * \brief Returns a sample state.
         *
         * A more elaborate description.
         *
         * \param randomStateOut
         *
         */
        int sampleState (CarState &randomStateOut);  

        
        /*!
         * \brief Returns a the cost of the trajectory that connects stateFromIn and
         *        stateTowardsIn. The trajectory is also returned in trajectoryOut.
         *
         * A more elaborate description.
         * 
         * \param stateFromIn Initial state
         * \param stateTowardsIn Final state
         * \param trajectoryOut Trajectory that starts the from the initial state and 
         *                      reaches near the final state.
         * \param exactConnectionOut Set to true if the initial and the final states
         *                           can be connected exactly.
         *
         */
        int extendTo (const CarState &stateFromIn, const CarState &stateTowardsIn, 
                      Trajectory &trajectoryOut, bool &exactConnectionOut); 
        
        /*!
         * \brief Returns the cost of the trajectory that connects stateFromIn and StateTowardsIn.
         *
         * A more elaborate description.
         *
         * \param stateFromIn Initial state
         * \param stateTowardsIn Final state
         * \param exactConnectionOut Set to true if the initial and the final states
         *                           can be connected exactly.
         *
         */
        double evaluateExtensionCost (const CarState &stateFromIn, const CarState &stateTowardsIn, bool &exactConnectionOut);
        
        /*!
         * \brief Returns a lower bound on the cost to go starting from stateIn
         *
         * A more elaborate description.
         *
         * \param stateIn Starting state
         *
         */
        double evaluateCostToGo (const CarState& stateIn);
        
        /*!
         * \brief Returns the trajectory as a list of double arrays, each with dimension getNumDimensions.
         *
         * A more elaborate description.
         *
         * \param stateFromIn Initial state
         * \param stateToIn Final state
         * \param trajectoryOut The list of double arrays that represent the trajectory
         *
         */
        int getTrajectory (const CarState& stateFromIn, const CarState& stateToIn, std::list<double*>& trajectoryOut);
	};
}
#endif //_CAR_SYSTEM_H