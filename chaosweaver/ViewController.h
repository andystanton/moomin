//
//  ViewController.h
//  chaosweaver
//
//  Created by Andy Stanton on 08/06/2014.
//
//

#import <UIKit/UIKit.h>
#import <GLKit/GLKit.h>

#include "model/PhysicsHelper.hpp"
#include "drawing/WorldRenderer.hpp"

@interface ViewController : GLKViewController
- (void)clipVec2Pair:(Vec2 *)lowerLeft :(Vec2 *)upperRight;
@end
