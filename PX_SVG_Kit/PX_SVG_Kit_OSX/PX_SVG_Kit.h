//
//  PX_SVG_Kit_OSX.h
//  PX_SVG_Kit_OSX
//
//  Created by Jamaine Obeng on 13/11/2015.
//  Copyright © 2015 LotsAndLess. All rights reserved.
//

#import <Cocoa/Cocoa.h>

//! Project version number for PX_SVG_Kit_OSX.
FOUNDATION_EXPORT double PX_SVG_KitVersionNumber;

//! Project version string for PX_SVG_Kit_OSX.
FOUNDATION_EXPORT const unsigned char PX_SVG_KitVersionString[];

// In this header, you should import all the public headers of your framework using statements like #import <PX_SVG_Kit_OSX/PublicHeader.h>
#import <PX_SVG_Kit/PX_SVG_View.h>
#import <PX_SVG_Kit/PX_SVG_Renderer.h>
#import <PX_SVG_Kit/PX_SVG_Image.h>
#if TARGET_OS_IPHONE
#import <PX_SVG_Kit/PX_SVG_Button.h>
#endif