//
//  ViewController.m
//  SVG
//
//  Created by Jamaine Obeng on 07/07/2015.
//  Copyright (c) 2015 Jamaine Obeng. All rights reserved.
//

#import "ViewController.h"

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    // Load SVG named "" in local bundle (Will return Nil on fail)
    PX_SVG_Image * svg = [[PX_SVG_Image alloc] initWithSVGNamed:@"Roundicons-28" inDirectory:@"TEST_SVGS"];
    [svgView setSvg:svg];
    
    self.directoryContents = [self getTestSVGPaths];


    self.timer = [NSTimer scheduledTimerWithTimeInterval:2.0 target:self selector:@selector(handleTimer:) userInfo:nil repeats:YES];
}

- (void)setRepresentedObject:(id)representedObject {
    [super setRepresentedObject:representedObject];

    // Update the view, if already loaded.
}

-(NSArray *)getTestSVGPaths {
    NSString * resourcePath = [[NSBundle mainBundle] resourcePath];
    resourcePath = [resourcePath stringByAppendingPathComponent:@"TEST_SVGS"];
    
    NSError * err;
    return [[NSFileManager defaultManager] contentsOfDirectoryAtPath:resourcePath error:&err];
}

-(void)handleTimer:(id)timer {
    
    NSString * filename = [self.directoryContents objectAtIndex:self.currentIterator];
    filename = [filename stringByDeletingPathExtension];
    
    PX_SVG_Image * svg = [[PX_SVG_Image alloc] initWithSVGNamed:filename inDirectory:@"TEST_SVGS"];
    [svgView setSvg:svg];
    
    self.currentIterator++;
    if ( self.currentIterator >= [self.directoryContents count] )
    {
        self.currentIterator = 0;
    }
}

@end
