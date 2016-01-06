//
//  PX_SVG_Renderer.cpp
//  SVG
//
//  Created by Hack Pro on 09/07/2015.
//  Copyright (c) 2015 Jamaine Obeng. All rights reserved.
//
#define NANOSVG_ALL_COLOR_KEYWORDS  // Include full list of color keywords.
#define NANOSVG_IMPLEMENTATION
#include "PX_SVG_Renderer.h"

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
#pragma mark - Constructor
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
PX_SVG_Renderer::PX_SVG_Renderer()
{
    m_SVG          = NULL;
    m_OverlayColor = NULL;
}


PX_SVG_Renderer::PX_SVG_Renderer(std::string path, double dpi)
: PX_SVG_Renderer()
{
    m_SVG          = NULL;
    m_OverlayColor = NULL;
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
#pragma mark - Destructor
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
PX_SVG_Renderer::~PX_SVG_Renderer()
{
    // Delete Nano SVG object (if set)
    if ( m_SVG != NULL )
    {
        nsvgDelete(m_SVG);
    }
    
    // Release Overlay color (if set)
    if ( m_OverlayColor != NULL )
    {
        CGColorRelease(m_OverlayColor);
        m_OverlayColor = NULL;
    }
    
    //Free all shape objects and empty vector
    this->clearPaths();
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
#pragma mark - Load SVG at file path
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
bool PX_SVG_Renderer::loadSVGAtPath(std::string path, double dpi)
{
    bool result = false;
    
    this->clearPaths();
    
    m_SVG = nsvgParseFromFile(path.c_str(), "px", dpi);
    if (m_SVG != NULL)
    {
#if kDEBUGG
        std::string format = "size: " + path + " %f x %f\n";
        printf(format.c_str(), m_SVG->width, m_SVG->height);
#endif
        result = true;
    }
    
    return result;
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
#pragma mark - Get SVG Size Information
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
double PX_SVG_Renderer::Width()
{
    double width = 0.0;

    if (m_SVG != NULL)
    {
        width = m_SVG->width;
    }
    
    return width;
}

double PX_SVG_Renderer::Height()
{
    double height = 0.0;

    if (m_SVG != NULL)
    {
        height = m_SVG->height;
    }
    
    return height;
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
#pragma mark - Set SVG Color Overlay
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
void PX_SVG_Renderer::setColorOverlay(CGColorRef color)
{
    if ( m_OverlayColor != NULL )
    {
        CGColorRelease(m_OverlayColor);
        m_OverlayColor = NULL;
    }
    
    m_OverlayColor = CGColorCreateCopy(color);
}

void PX_SVG_Renderer::clearPaths()
{
    for (auto shape : m_Shapes)
    {
        CGPathRelease(shape);
    }
    
    m_Shapes.clear();
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
#pragma mark - Render SVG At Frame Size
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
void PX_SVG_Renderer::renderSVGInFrame(CGRect frame)
{
    m_LastFrame = frame;
    
    this->clearPaths();
    
    if (m_SVG != NULL)
    {
        // Scale SVG width and height
        const double width  = m_SVG->width;
        const double height = m_SVG->height;
        
        const double x_Scaling = frame.size.width  * (1.0/width);
        const double y_Scaling = frame.size.height * (1.0/height);
        
        //
        for (NSVGshape * shape = m_SVG->shapes; shape != NULL; shape = shape->next)
        {
            CGRect shapeRect      = CGRectZero;
            shapeRect.origin.x    = frame.origin.x + (shape->bounds[0] * x_Scaling);
            shapeRect.origin.y    = frame.origin.y + (shape->bounds[1] * y_Scaling);
            shapeRect.size.width  = (shape->bounds[2] - shape->bounds[0]) * x_Scaling;
            shapeRect.size.height = (shape->bounds[3] - shape->bounds[1]) * y_Scaling;
            
            CGMutablePathRef superpath = CGPathCreateMutable();
            
            this->renderShape(shape, shapeRect, superpath);
            
            m_Shapes.push_back(superpath);
        }
    }
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
#pragma mark - Color To Core Graphics Color
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
CGColorRef PX_SVG_Renderer::strokeColorForShape(NSVGshape * shape)
{
    NSVGpaint stroke = shape->stroke;
    
    unsigned int color = stroke.color;
    
    return this->createCGColorFromNSVGColor(color, shape->opacity);
}

CGColorRef PX_SVG_Renderer::fillColorForShape(NSVGshape * shape)
{
    NSVGpaint fill = shape->fill;
    
    unsigned int color = fill.color;
    
    return this->createCGColorFromNSVGColor(color, shape->opacity);
}

CGColorRef PX_SVG_Renderer::createCGColorFromNSVGColor(UInt32 color, float opacity)
{
    //Split 32 Bit Unsigned Int Color to CGColorRef
    CGFloat colorBlock[4];
    colorBlock[3] = ((color >> 24) & 0xFF) * (1.0 / 255.0);
    colorBlock[2] = ((color >> 16) & 0xFF) * (1.0 / 255.0);
    colorBlock[1] = ((color >> 8)  & 0xFF) * (1.0 / 255.0);
    colorBlock[0] = (color & 0xFF) * (1.0 / 255.0);
    
    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
    CGColorRef cg_color        = CGColorCreate(colorSpace, colorBlock);
    CGColorSpaceRelease(colorSpace);
    
    return cg_color;
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
#pragma mark - Render Shape/Path To Core Graphics Path
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
void PX_SVG_Renderer::renderShape(NSVGshape * shape,CGRect frame, CGMutablePathRef cg_path)
{
    CGRect shapeRect      = CGRectZero;
    shapeRect.origin.x    = shape->bounds[0];
    shapeRect.origin.y    = shape->bounds[1];
    shapeRect.size.width  = shape->bounds[2] - shapeRect.origin.x;
    shapeRect.size.height = shape->bounds[3] - shapeRect.origin.y;
    
    //
    const double x_Scaling = frame.size.width  * (1.0 / shapeRect.size.width);
    const double y_Scaling = frame.size.height * (1.0 / shapeRect.size.height);
    
    //
    for (NSVGpath * path = shape->paths; path != NULL; path = path->next) {
        
        CGRect pathRect      = CGRectZero;
        pathRect.origin.x    = frame.origin.x + (path->bounds[0] - shapeRect.origin.x) * x_Scaling;
        pathRect.origin.y    = frame.origin.y + (path->bounds[1] - shapeRect.origin.y) * y_Scaling;
        pathRect.size.width  = (path->bounds[2] - path->bounds[0]) * x_Scaling;
        pathRect.size.height = (path->bounds[3] - path->bounds[1]) * y_Scaling;
        
        //
        this->renderPath(path, pathRect, cg_path);
    }
}

void PX_SVG_Renderer::renderPath(NSVGpath * path, CGRect frame, CGMutablePathRef cg_path)
{
    CGRect pathRect      = CGRectZero;
    pathRect.origin.x    = path->bounds[0];
    pathRect.origin.y    = path->bounds[1];
    pathRect.size.width  = path->bounds[2] - pathRect.origin.x;
    pathRect.size.height = path->bounds[3] - pathRect.origin.y;
    
    //
    const double x_Scaling = frame.size.width  * (1.0 / pathRect.size.width);
    const double y_Scaling = frame.size.height * (1.0 / pathRect.size.height);
    
    for (int i = 0; i < path->npts -1; i += 3)
    {
        float * p = &path->pts[i*2];
        double scaledValues[e_NumberOfPoints];
        
        // X
        for (int t = 0; t < e_NumberOfPoints; t+=2)
        {
            scaledValues[t] = frame.origin.x + ((p[t] - pathRect.origin.x) * x_Scaling);
        }
        
        // Y
        for (int t = 1; t < e_NumberOfPoints; t+=2)
        {
            scaledValues[t] = frame.origin.y + ((p[t]  - pathRect.origin.y) * y_Scaling);
        }
        
        // Bézier Points
        const double x0   = scaledValues[e_x0];
        const double y0   = scaledValues[e_y0];
        const double cpx1 = scaledValues[e_cpx1];
        const double cpy1 = scaledValues[e_cpy1];
        const double cpx2 = scaledValues[e_cpx2];
        const double cpy2 = scaledValues[e_cpy2];
        const double x1   = scaledValues[e_x1];
        const double y1   = scaledValues[e_y1];
        
        if (i == 0)
        {
            CGPathMoveToPoint(cg_path, NULL, x0, y0);
        }
        else
        {
            CGPathAddLineToPoint(cg_path, NULL, x0, y0);
        }
        
        CGPathAddCurveToPoint(cg_path, NULL, cpx1, cpy1, cpx2, cpy2, x1, y1);
    }
    
    CGPathCloseSubpath(cg_path);
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
#pragma mark - Draw In Context
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
void PX_SVG_Renderer::drawInContext(CGContextRef context)
{
    if (m_SVG == NULL || m_Shapes.empty())
    {
        return;
    }
    
    int index = 0;
    for (NSVGshape * shape = m_SVG->shapes; shape != NULL; shape = shape->next)
    {
        if ( index >= m_Shapes.size() )
        {
            break;
        }
        
        CGContextSetBlendMode(context, kCGBlendModeNormal);

        //
        CGMutablePathRef path = m_Shapes.at(index);
        
        
        //
        switch (shape->fill.type)
        {
            case NSVG_PAINT_NONE:
                break;
                
            case NSVG_PAINT_COLOR:
            {
                CGColorRef fill   = this->fillColorForShape(shape);
                CGContextSetFillColorWithColor(context, fill);
                CGColorRelease(fill);
                
                //
                CGContextAddPath(context, path);
                CGContextDrawPath(context, kCGPathFill);
            }
                break;
                
            case NSVG_PAINT_LINEAR_GRADIENT:
            {
                CGContextSaveGState(context);

                //
                CGContextAddPath(context, path);
                CGContextClip(context);
                
                CFMutableArrayRef gradArray = CFArrayCreateMutable(kCFAllocatorDefault, 0, &kCFTypeArrayCallBacks);
                
                const int numberOfStops = shape->fill.gradient->nstops;
                CGFloat locations[numberOfStops];
                for (int i = 0; i < numberOfStops; i++)
                {
                    locations[i]    = shape->fill.gradient->stops[i].offset;
                    CGColorRef grad = this->createCGColorFromNSVGColor(shape->fill.gradient->stops[i].color, shape->opacity);
                    CFArrayAppendValue(gradArray, grad);
                    CGColorRelease(grad);
                }
                
                //Create Gradient Refrence
                CGColorSpaceRef rgb = CGColorSpaceCreateDeviceRGB();
                CGGradientRef gradient = CGGradientCreateWithColors(rgb, gradArray, locations);
                CGColorSpaceRelease(rgb);
                
                CFRelease(gradArray);
                
                
                CGRect shapeRect      = CGRectZero;
                shapeRect.origin.x    = shape->bounds[0];
                shapeRect.origin.y    = shape->bounds[1];
                shapeRect.size.width  = shape->bounds[2];
                shapeRect.size.height = shape->bounds[3];
                
                //
                const double x_Scaling = m_LastFrame.size.width  * (1.0 / shapeRect.size.width);
                const double y_Scaling = m_LastFrame.size.height * (1.0 / shapeRect.size.height);

                const double startX = shape->fill.gradient->fx1;
                const double startY = shape->fill.gradient->fy1;

                const double endX = shape->fill.gradient->fx2;
                const double endY = shape->fill.gradient->fy2;

                //
                CGContextDrawLinearGradient(context, gradient, CGPointMake(startX * x_Scaling, startY * y_Scaling), CGPointMake(endX * x_Scaling, endY * y_Scaling),  kCGGradientDrawsBeforeStartLocation|kCGGradientDrawsAfterEndLocation);
                CGGradientRelease(gradient);
                
                CGContextRestoreGState(context);                
            }
                break;
                
            case NSVG_PAINT_RADIAL_GRADIENT:
            {
            
            }
                break;
                
            default:
                break;
        }


        
        /////////////////////////////////////
        //Stroke
        /////////////////////////////////////
        
        switch (shape->stroke.type)
        {
            case NSVG_PAINT_NONE:
                CGContextSetLineWidth(context, 0.0);
                break;
                
            case NSVG_PAINT_COLOR:
            {
                CGContextAddPath(context, path);

                CGContextSetLineWidth(context, shape->strokeWidth);

                CGColorRef stroke = this->strokeColorForShape(shape);
                CGContextSetStrokeColorWithColor(context, stroke);
                CGColorRelease(stroke);
                CGContextStrokePath(context);

            }
                break;
                
                
            case NSVG_PAINT_LINEAR_GRADIENT:
            {
                
            }
                break;
                
            case NSVG_PAINT_RADIAL_GRADIENT:
            {
            }
                break;
                
            default:
                break;
        }
    
        index++;
    }
    
    if (m_OverlayColor)
    {
        CGContextSetBlendMode(context, kCGBlendModeSourceIn);
        CGContextSetFillColorWithColor(context, m_OverlayColor);
        
        CGContextFillRect(context, m_LastFrame);
    }
}