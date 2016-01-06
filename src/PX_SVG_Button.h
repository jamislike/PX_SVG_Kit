//
//  PX_SVG_Button.h
//  PX_SVG_Kit
//
//  Created by Jamaine Obeng on 20/11/2015.
//  Copyright © 2015 LotsAndLess. All rights reserved.
//
#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#else
//#import <Cocoa/Cocoa.h>
#endif
#import "PX_SVG_Image.h"
#import "PX_SVG_View.h"

@interface PX_SVG_Button : PX_Button
{
}
@property (strong, nonatomic) PX_SVG_Image * normalSVG;
@property (strong, nonatomic) PX_SVG_Image * selectedSVG;
@property (strong) PX_SVG_View  * svgView;

@end
