//
//  PX_SVG_Renderer.h
//  SVG
//
//  Created by Hack Pro on 09/07/2015.
//  Copyright (c) 2015 Jamaine Obeng. All rights reserved.
//

#ifndef __SVG__PX_SVG_Renderer__
#define __SVG__PX_SVG_Renderer__

#include <stdio.h>
#include <string>
#include <math.h>
#include <iostream>

#include "nanosvg.h"

#include <vector>
#include <CoreGraphics/CoreGraphics.h>

enum cubicPoints
{
    e_x0   = 0,
    e_y0,
    e_cpx1,
    e_cpy1,
    e_cpx2,
    e_cpy2,
    e_x1,
    e_y1,
    
    e_NumberOfPoints
};

class PX_SVG_Renderer
{
public:
    /**
     *  Constructor
     */
    PX_SVG_Renderer();
    
    /**
     *  Constructor with file at path and dpi
     */
    PX_SVG_Renderer(std::string path, double dpi = 96);

    /**
     *  Destructor
     */
    ~PX_SVG_Renderer();
    
    /**
     *  Load SVG at path
     *
     *  @param path filepath to load SVG file
     *  @param dpi  Dot's per inch
     *
     *  @return bool value containing 'true' on success
     */
    bool loadSVGAtPath(std::string path, double dpi = 96);
    
    /**
     *  A color to overlay the SVG image
     *
     *  @param color A core graphics color
     */
    void setColorOverlay(CGColorRef color);
    
    /**
     *  The original width of the SVG
     *
     *  @return A floating point width value
     */
    double Width();
    
    /**
     *  The original height of the SVG
     *
     *  @return A floating point height value
     */
    double Height();
    
    /**
     *  Create CGPaths structures for SVG at size of frame
     *
     *  @param rect A frame rect
     */
    void renderSVGInFrame(CGRect rect);

    /**
     *  Render a Shape to a CGPath Object
     *
     *  @param A NanoSVG Shape type
     *  @param A Core Graphics mutabele path to be mutated
     */
    void renderShape(NSVGshape * shape,CGRect frame, CGMutablePathRef cg_path);

    /**
     *  Render a Path to a CGPath Object
     *
     *  @param A NanoSVG path type
     *  @param A Core Graphics mutabele path to be mutated
     */
    void renderPath(NSVGpath * path,   CGRect frame, CGMutablePathRef cg_path);
    
    /**
     *  Draw the SVG Image to the given context
     *
     *  @param A Core Graphics Context to draw the S.V.G. Image to
     */
    void drawInContext(CGContextRef context);

private:
    /**
     *  Free all path / shape data
     */
    void clearPaths();
    
    /**
     *  Get Stroke Color for NanoSVG Shape
     *
     *  @param Nano SVG Shape
     *
     *  @return Core Graphics color
     */
    CGColorRef strokeColorForShape(NSVGshape * shape);
    
    /**
     *  Get Fill Color for NanoSVG Shape
     *
     *  @param Nano SVG Shape
     *
     *  @return Fill Core Graphics color
     */
    CGColorRef fillColorForShape(NSVGshape * shape);
    
    /**
     *  Get Fill Color for NanoSVG Shape
     *
     *  @param Nano SVG Shape
     *
     *  @return Fill Core Graphics color
     */
    CGColorRef createCGColorFromNSVGColor(UInt32 color, float opacity);

    std::vector<CGMutablePathRef> m_Shapes;         /* Vector containing shape paths*/
    NSVGimage *                   m_SVG;            /* Nano SVG pointer */
    CGRect                        m_LastFrame;      /* Last render frame */
    CGColorRef                    m_OverlayColor;   /* A color to overlay/tint SVG */
};
#endif /* defined(__SVG__PX_SVG_Renderer__) */
