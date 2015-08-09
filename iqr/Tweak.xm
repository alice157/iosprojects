#include <stdlib.h>
#import <UIKit/UIKit.h>

%hook SBBannerController
-(id)_bannerView {
	*bannerView = %orig;
	NSArray *subviews = [bannerView subviews]
	if ([subviews count] == 0]) return bannerView;
	for (UIView *subview in subviews) {
		NSLog(@"ChompSMS DEBUG _bannerView/subviews:\t%@", subview);
	}
	return bannerView;
}	
%end
