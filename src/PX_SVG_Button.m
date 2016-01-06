//
//  PX_SVG_Button.m
//  PX_SVG_Kit
//
//  Created by Jamaine Obeng on 20/11/2015.
//  Copyright © 2015 LotsAndLess. All rights reserved.
//

#import "PX_SVG_Button.h"

@implementation PX_SVG_Button

- (instancetype)init
{
    self = [super init];
    if (self) {
        [self setup];
    }
    return self;
}

- (instancetype)initWithCoder:(NSCoder *)coder
{
    self = [super initWithCoder:coder];
    if (self) {
        [self setup];
    }
    return self;
}
- (instancetype)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        [self setup];
    }
    return self;
}

-(void)setup
{
    self.svgView = [[PX_SVG_View alloc] initWithFrame:self.bounds];
    self.svgView.userInteractionEnabled = NO;

    [self addSubview:self.svgView];
    
    
    [self setSelected:self.selected];
    
#if TARGET_OS_IPHONE
    [self addTarget:self action:@selector(buttonPressed)   forControlEvents:UIControlEventTouchDown];
    [self addTarget:self action:@selector(buttonDepressed) forControlEvents:UIControlEventTouchUpInside];
#else
    
#endif
}

- (void)setFrame:(CGRect)frame
{
    [super setFrame:frame];
    
    if (self.selectedSVG)
    {
        [self.selectedSVG setFrame:frame];
    }
    
    if (self.normalSVG)
    {
        [self.normalSVG setFrame:frame];
    }
    
    [self.svgView setFrame:self.bounds];
}

-(void)setSelected:(BOOL)selected
{
#if TARGET_OS_IPHONE
    [super setSelected:selected];
#else
    int sel = (selected == YES) ? 1 : 0;
    [self setState:sel ];
#endif
    
    if (selected)
    {
        self.svgView.svg = self.selectedSVG;
    }
    else
    {
        self.svgView.svg = self.normalSVG;
    }
}

-(void)setNormalSVG:(PX_SVG_Image *)svg
{
    _normalSVG = svg;
    [self setSelected:self.selected];
}

-(void)setSelectedSVG:(PX_SVG_Image *)svg
{
    _selectedSVG = svg;
    [self setSelected:self.selected];
}

- (void)buttonPressed
{
    [self setSelected:YES];
}

- (void)buttonDepressed
{
    [self setSelected:NO];
}

-(void)layoutSubviews
{
    [super layoutSubviews];
    [self.svgView setFrame:self.bounds];
}
@end

