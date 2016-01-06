//
//  PX_SVG_View.h
//  SVG
//
//  Created by Jamaine Obeng on 07/07/2015.
//  Copyright (c) 2015 Jamaine Obeng. All rights reserved.
//
#include <CoreGraphics/CoreGraphics.h>
#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#else
#import <Cocoa/Cocoa.h>
#endif
#import "PX_SVG_Image.h"
#import "PX_CocoaGraphicsDefines.h"


@interface PX_SVG_View : PX_View
{
}
@property (strong, nonatomic) PX_Image     * bitmapImage; /* A plain old bitmap image to be displayed */
@property (strong, nonatomic) PX_SVG_Image * svg;         /* SVG Image Object*/

/**
 *  Set SVG Views Frame
 *
 *  @param frame Rect
 */
-(void)setFrame:(CGRect)frame;

/**
 *  Initialize with S.V.G named
 *
 *  @param directory: A filepath to an S.V.G file
 *
 *  @return An instance of 'PX_SVG_Image'
 */
-(void)loadSVGNamed:(NSString *)name;

/**
 *  Load an S.V.G into memory
 *
 *  @param name: An S.V.G with filename to be loaded
 *  @param directory: A Sub-Directory to find S.V.G
 *
 *  @return A BOOL containing 'YES' on successful load of SVG
 */
-(void)loadSVGNamed:(NSString *)name inDirectory:(NSString *)directory;

/**
 *  Load an S.V.G into memory and display in view
 *
 *  @param path: A filepath pointing to an S.V.G file
 *
 *  @return A BOOL containing 'YES' on successful load of SVG
 */
-(void)loadSVGAtFilePath:(NSString *)path;
@end
