//
//  velocity.h
//  gameeng
//
//  Created by Armon Carigiet on 16.04.14.
//  Copyright (c) 2014 Armon Carigiet. All rights reserved.
//

#ifndef __gameeng__velocity__
#define __gameeng__velocity__

#include <iostream>
#include <math.h>

namespace physics{
	namespace velocity{
		
		struct _velocity{
			float x;
			float y;
			float z;
		};
		typedef struct _velocity velocity;
		
		// angle in rad
		physics::velocity::velocity create_velocity(float abs, float alpha, float beta);
		
	}
}

#endif /* defined(__gameeng__velocity__) */
