//
//  ViewController.h
//  SVG
//
//  Created by Jamaine Obeng on 07/07/2015.
//  Copyright (c) 2015 Jamaine Obeng. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <PX_SVG_Kit/PX_SVG_Kit.h>

@interface ViewController : NSViewController
{
    __weak IBOutlet NSView *rootView;
    __weak IBOutlet PX_SVG_View * svgView;
}
@property (strong) NSTimer * timer;
@property (strong) NSArray * directoryContents;
@property (readwrite) NSInteger currentIterator;

@end

