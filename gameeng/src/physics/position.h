//
//  position.h
//  gameeng
//
//  Created by Armon Carigiet on 17.04.14.
//  Copyright (c) 2014 Armon Carigiet. All rights reserved.
//

#ifndef __gameeng__position__
#define __gameeng__position__

#include <iostream>

namespace physics {
	namespace position{
		struct _position{
			float x;
			float y;
			float z;
		};
		typedef struct _position position;
	}
}


#endif /* defined(__gameeng__position__) */
