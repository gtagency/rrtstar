
#include "region.h"

Region::Region (int numDimensionsIn, ...) {
    
    numDimensions = numDimensionsIn;
    
	va_list ap;
	va_start(ap, numDimensionsIn);
	
    center = new double[numDimensions];
	for (int ii = 0; ii < numDimensions; ii++) {
		center[ii] = va_arg(ap, double);
	}
    size = new double[numDimensions];
	for (int ii = 0; ii < numDimensions; ii++) {
		size[ii] = va_arg(ap, double);
	}
}


Region::~Region () {
    
    if (center)
        delete [] center;
    if (size)
        delete [] size;
}

Region& operator= (const Region& regionIn) {
	numDimensions = regionIn.numDimensions;

	if (center) {
		delete [] center;
		center = NULL;
	}
	
    center = new double[numDimensions];
	for (int ii = 0; ii < numDimensions; ii++) {
		center[ii] = regionIn.center[ii];
	}

	if (size) {
		delete [] size;
		size = NULL;
	}

    size = new double[numDimensions];
	for (int ii = 0; ii < numDimensions; ii++) {
		size[ii] = regionIn.size[ii];
	}
}

bool Region::contains(int numDimensionsIn, double *vector) {
	//TODO: if the dimensions don't match, we need to do some fancy projections
    for (int i = 0; i < numDimensions; i++) {
        
        if (fabs(stateIn.x[i] - regionGoal.center[i]) > regionGoal.size[i]/2.0 ) 
            return false;
    }
    
    return true;
}

void Region::getCenterAsVector(int numDimensionsIn, double *vector) {
	
}

void Region::getSizeAsVector(int numDimensionsIn, double *vector) {
	
}

std::ostream& operator << (std::ostream &o, const Region &a) {
    o << "center.x: " << a.x() << "\tcenter.y: " << a.y();
    return o;
}
