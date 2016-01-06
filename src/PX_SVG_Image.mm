//
//  PX_SVG_Image.m
//  jarc_lib
//
//  Created by Jamaine on 25/07/2015.
//  Copyright (c) 2015 LotsAndLess. All rights reserved.
//

#import "PX_SVG_Image.h"
#include "PX_SVG_Renderer.h"

@interface PX_SVG_Image ()
@property (readwrite) PX_SVG_Renderer * renderer; /* A C++ Class used to render SVG Data*/
@end

@implementation PX_SVG_Image

-(instancetype)init
{

    self = [super init];
    if (self)
    {
        self.scale = 1.0;
    }
    return self;
}
-(instancetype)initWithSVGNamed:(NSString *)name
{
    self = [self init];
    if (self)
    {
        //If SVG load fails return Nil
        if ([self loadSVGNamed:name] == NO)
        {
            return Nil;
        }
    }
    return self;
}

-(instancetype)initWithSVGNamed:(NSString *)name inDirectory:(NSString *)directory
{
    self = [self init];
    if (self)
    {
        //If SVG load fails return Nil
        if ([self loadSVGNamed:name inDirectory:directory] == NO)
        {
            return Nil;
        }
    }
    return self;
}

-(instancetype)initWithSVGAtFilePath:(NSString *)path
{
    self = [self init];
    if (self)
    {
        //If SVG load fails return Nil
        if ([self loadSVGAtFilePath:path] == NO)
        {
            return Nil;
        }
    }
    return self;
}

+(id)svgNamed:(NSString *)name
{
    PX_SVG_Image * image = [[PX_SVG_Image alloc] initWithSVGNamed:name];
    return image;
}

+(id)svgNamed:(NSString *)name inDirectory:(NSString *)directory
{
    PX_SVG_Image * image = [[PX_SVG_Image alloc] initWithSVGNamed:name inDirectory:directory];
    return image;
}

+(id)svgAtPath:(NSString *)path
{
    PX_SVG_Image * image = [[PX_SVG_Image alloc] initWithSVGAtFilePath:path];
    return image;
}

-(void)dealloc
{
    if ( self.renderer )
    {
        delete(self.renderer);
    }
}

-(CGSize)size
{
    CGSize size = CGSizeZero;

    if (self.renderer != NULL)
    {
        size.width  = self.renderer->Width();
        size.height = self.renderer->Height();
    }
    return size;
}

-(void)setFrame:(CGRect)frame
{
    CGRect svgFrame = frame;
    svgFrame.size.height *= self.scale;
    svgFrame.size.width  *= self.scale;
    
    svgFrame.origin.x = (frame.size.width  - svgFrame.size.width)  * 0.5;
    svgFrame.origin.y = (frame.size.height - svgFrame.size.height) * 0.5;
    
    if (self.renderer != NULL)
    {
        self.renderer->renderSVGInFrame(svgFrame);
    }
}

-(BOOL)loadSVGNamed:(NSString *)name
{
    NSBundle * mb = [NSBundle mainBundle];
    NSString * fp = [mb pathForResource:name ofType:@"svg"];

    BOOL result = NO;
    if (fp)
    {
        result = [self loadSVGAtFilePath:fp];
    }
    return result;
}

-(BOOL)loadSVGNamed:(NSString *)name inDirectory:(NSString *)directory
{
    NSBundle * mb = [NSBundle mainBundle];
    NSString * fp =[mb pathForResource:name ofType:@"svg" inDirectory:directory];
    
    BOOL result = NO;
    if (fp)
    {
        result = [self loadSVGAtFilePath:fp];
    }
    
    return result;
}

-(BOOL)loadSVGAtFilePath:(NSString *)path
{
    if (self.renderer == NULL)
    {
        self.renderer = new PX_SVG_Renderer;
    }
    
    bool result = self.renderer->loadSVGAtPath( [path UTF8String] );
    if (result == false)
    {
        if ( self.renderer )
        {
            delete(self.renderer);
        }
    }
    
    return (BOOL)result;
}

-(void)setOverlayColor:(CGColorRef)color
{
    if (self.renderer != NULL)
    {
        self.renderer->setColorOverlay(color);
    }
}

-(void)drawInContext:(CGContextRef)context
{
    if (self.renderer != NULL)
    {
        self.renderer->drawInContext(context);
    }
}

@end
