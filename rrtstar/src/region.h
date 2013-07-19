
#ifndef _REGION_H
#define _REGION_H

#include <iostream>
using namespace std;

/*!
 * \brief region class
 *
 * More elaborate description
 */
class Region {

private:
    int numDimensions;
    
   /*!
    * \brief Cartesian coordinates of the center of the region
    *
    * More elaborate description
    */
   double *center;
   
   /*!
    * \brief Size of the region in cartesian coordinates
    *
    * More elaborate description
    */
   double *size;
   
public:    
    
   Region(int numDimensionsIn, ...);

    /*!
     * \brief region constructor
     *
     * More elaborate description
     */
    Region ();
    
    /*!
     * \brief region destructor
     *
     * More elaborate description
     */
    ~Region ();
	 
	 Region& operator= (const Region& regionIn);

	 bool contains(int numDimensionsIn, const double *vector);  

	 void getCenterAsVector(int numDimensionsIn, double *vector);

	 void getSizeAsVector(int numDimensionsIn, double *vector);

	 friend ostream& operator << (std::ostream &o, const Region &a);
};

ostream& operator << (std::ostream &o, const Region &a);

#endif //_REGION_H