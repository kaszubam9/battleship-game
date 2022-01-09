#ifndef RANDOM_H
#define RANDOM_H

#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include<string>
#include<random>


///////////////////////////////////////////////////////////
//	This function generates random integer
///////////////////////////////////////////////////////////
//		
// INPUT:
//		const int kFrom  - minimum number
//		const int kTo    - maximum number
// 
// OUTPUT:
//		Random integer between minimum and maximum number
//

int    RandN(const int kFrom, const int kTo);

#endif