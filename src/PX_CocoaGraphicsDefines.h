//
//  PX_Defines.h
//  jarc_lib
//
//  Created by Jamaine on 11/11/2015.
//  Copyright © 2015 Vintage Confiture. All rights reserved.
//

#ifndef PX_Defines_h
#define PX_Defines_h

#if TARGET_OS_IPHONE
//iOS
#import <UIKit/UIkit.h>
typedef UIView  PX_View;
typedef UIImage PX_Image;
#else
// Mac OS X
#import <Cocoa/Cocoa.h>
typedef NSView  PX_View;
typedef NSImage PX_Image;
#endif

#endif /* PX_Defines_h */
