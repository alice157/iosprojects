#include <stdlib.h>
#import <UIKit/UIKit.h>
#include "recognizer.h"

@interface UIWindowInputCatcher: UIWindow
-(BOOL)pointInside:(CGPoint)point withEvent:(UIEvent *)event;
@end

@implementation UIWindowInputCatcher
-(BOOL)pointInside:(CGPoint)point withEvent:(UIEvent *)event {
	NSLog(@"Touch at %@, %@", point.x, point.y);
	return NO;
}
@end
