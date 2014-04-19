//
//  acceleration.cpp
//  gameeng
//
//  Created by Armon Carigiet on 17.04.14.
//  Copyright (c) 2014 Armon Carigiet. All rights reserved.
//

#include "acceleration.h"

physics::acceleration::acceleration create_acceleration(float abs, float alpha, float beta){
	physics::acceleration::acceleration a={
		abs*cosf(alpha)*cosf(beta),
		abs*sinf(alpha),
		abs*cosf(alpha)*cosf(M_PI-beta)
	};
	return a;
}
