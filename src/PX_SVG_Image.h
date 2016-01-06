//
//  PX_SVG_Image.h
//  jarc_lib
//
//  Created by Jamaine on 25/07/2015.
//  Copyright (c) 2015 LotsAndLess. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>

@interface PX_SVG_Image : NSObject
{
}
@property (readwrite) double scale;               /* A scaling ratio applied to S.V.G*/

/**
 *  Initialize with S.V.G named
 *
 *  @param name: An S.V.G with filename to be loaded
 *
 *  @return An instance of 'PX_SVG_Image'
 */

-(instancetype)initWithSVGNamed:(NSString *)name;

/**
 *  Initialize with S.V.G named
 *
 *  @param name: An S.V.G with filename to be loaded
 *  @param directory: A Sub-Directory to find S.V.G
 *
 *  @return An instance of 'PX_SVG_Image'
 
 */
-(instancetype)initWithSVGNamed:(NSString *)name inDirectory:(NSString *)directory;

/**
 *  Initialize with S.V.G named
 *
 *  @param directory: A filepath to an S.V.G file
 *
 *  @return An instance of 'PX_SVG_Image'
 */
-(instancetype)initWithSVGAtFilePath:(NSString *)path;

/**
 *  Initialize with S.V.G named
 *
 *  @param name: An S.V.G with filename to be loaded
 *
 *  @return An instance of 'PX_SVG_Image'
 */
+(id)svgNamed:(NSString *)name;

/**
 *  Initialize with S.V.G named
 *
 *  @param name: An S.V.G with filename to be loaded
 *  @param directory: A Sub-Directory to find S.V.G
 *
 *  @return An instance of 'PX_SVG_Image'
 */
+(id)svgNamed:(NSString *)name inDirectory:(NSString *)directory;

/**
 *  Initialize with S.V.G named
 *
 *  @param directory: A filepath to an S.V.G file
 *
 *  @return An instance of 'PX_SVG_Image'
 */
+(id)svgAtPath:(NSString *)path;

/**
 *  Set S.V.G. Renderer frame
 *
 *  @param frame: An S.V.G with filename to be loaded
 *
 */
-(void)setFrame:(CGRect)frame;

/**
 *  Load an S.V.G into memory
 *
 *  @param name: An S.V.G with filename to be loaded
 *  @param directory: A Sub-Directory to find S.V.G
 *
 *  @return A BOOL containing 'YES' on successful load of SVG
 */
-(BOOL)loadSVGNamed:(NSString *)name;

/**
 *  Load an S.V.G into memory
 *
 *  @param name: An S.V.G with filename to be loaded
 *  @param directory: A Sub-Directory to find S.V.G
 *
 *  @return A BOOL containing 'YES' on successful load of SVG
 */
-(BOOL)loadSVGNamed:(NSString *)name inDirectory:(NSString *)directory;

/**
 *  Load an S.V.G into memory
 *
 *  @param path: A filepath pointing to an S.V.G file
 *
 *  @return A BOOL containing 'YES' on successful load of SVG
 */
-(BOOL)loadSVGAtFilePath:(NSString *)path;

/**
 *  Base SVG Size
 *
 *  @return Default size of svg
 */
-(CGSize)size;

/**
 *  Overlay Color Applied to SVG
 *
 *  @param name: A color to overlay S.V.G with
 */
-(void)setOverlayColor:(CGColorRef)color;

/**
 *  Draw S.V.G. In Context
 *
 *  @param context: A Core Graphics context
 */
-(void)drawInContext:(CGContextRef)context;
@end
