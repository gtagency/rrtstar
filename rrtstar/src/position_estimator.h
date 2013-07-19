
#ifndef _POSITION_ESTIMATOR_H
#define _POSITION_ESTIMATOR_H

namespace buzzmobile {

	class PositionEstimator {
	private:
		double x;
		double y;
		double heading;

		double xVel;
		double yVel;
		
	public:
		
		PositionEstimator(double initialX, double initialY, double initialHeading, double initialVelocity);
		
		
		
	}

}

#endif //_POSITION_ESTIMATOR_H