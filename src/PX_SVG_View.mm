//
//  PX_SVG_View.m
//  SVG
//
//  Created by Jamaine Obeng on 07/07/2015.
//  Copyright (c) 2015 Jamaine Obeng. All rights reserved.
//

#import "PX_SVG_View.h"

@implementation PX_SVG_View

#pragma mark - Init

-(instancetype)init
{
    self = [super init];
    if (self)
    {
        #if TARGET_OS_IPHONE
            self.backgroundColor = [UIColor clearColor];
        #else
        #endif
    }
    return self;
}

-(instancetype)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self)
    {
#if TARGET_OS_IPHONE
        self.backgroundColor = [UIColor clearColor];
#else
#endif
    }
    return self;
}

#pragma mark - Dealloc

-(void)dealloc
{
    self.svg = Nil;
}

#pragma mark - Set Frame

-(void)setFrame:(CGRect)frame
{
    [super setFrame:frame];
    
    if (self.svg != NULL )
    {
        [self.svg setFrame:frame];
    }
}

#pragma mark - Display

#if !TARGET_OS_IPHONE
-(void)setNeedsDisplay
{
    [super setNeedsDisplay:YES];
}
#endif

#pragma mark - Load SVG

-(void)setSvg:(PX_SVG_Image *)image
{
    _svg = image;
    [self setFrame:self.frame];
    [self setNeedsDisplay];
}

-(void)loadSVGNamed:(NSString *)name
{
    NSBundle * mb = [NSBundle mainBundle];
    NSString * fp = [mb pathForResource:name ofType:@"svg"];
    
    if (fp != Nil)
    {
        [self loadSVGAtFilePath:fp];
    }
}

-(void)loadSVGNamed:(NSString *)name inDirectory:(NSString *)directory
{
    NSBundle * mb = [NSBundle mainBundle];
    NSString * fp = [mb pathForResource:name ofType:@"svg" inDirectory:directory];
    
    if ( fp != Nil )
    {
        [self loadSVGAtFilePath:fp];
    }
}

#pragma mark - Set Frame

-(void)loadSVGAtFilePath:(NSString *)path
{
    self.svg = [PX_SVG_Image svgAtPath:path];
}

#pragma mark - Drawing

-(CGContextRef)getGraphicContext
{
#if TARGET_OS_IPHONE
    CGContextRef context = UIGraphicsGetCurrentContext();
#else
    CGContextRef context = (CGContextRef)[[NSGraphicsContext currentContext] graphicsPort];
    
    //Flip the the context
    CGContextSetTextMatrix(context, CGAffineTransformIdentity);
    CGContextTranslateCTM(context, 0, self.bounds.size.height);
    CGContextScaleCTM(context, 1.0, -1.0);
#endif
    return context;
}

-(void)drawRect:(CGRect)rect
{
    CGContextRef context = [self getGraphicContext];

    if (self.bitmapImage != Nil)
    {
        CGRect svgFrame = self.bounds;
        svgFrame = CGRectInset(svgFrame, self.frame.size.width * self.svg.scale, self.frame.size.height * self.svg.scale);
        
        [self.bitmapImage drawInRect:svgFrame];
    }
    
    if (self.svg != Nil)
    {
        [self.svg drawInContext:context];
    }
}
@end
