#include <OGL3D/Graphics/OGraphicsEngine.h>
#import <Cocoa/Cocoa.h>
#include <glad/glad.h>
#include <assert.h>
#include <OGL3D/Window/OWindow.h>
#include <stdexcept>

OGraphicsEngine::OGraphicsEngine()
{
    //Create Dummy Cocoa Window and Dummy OpenGL Context in order to initialize Glad------------
    //-----------------------------------------------------------------------------
    NSUInteger windowStyle = 0;

    NSRect screenRect = [[NSScreen mainScreen] frame];
    NSRect viewRect = NSMakeRect(0, 0, 1, 1);
    NSRect windowRect = NSMakeRect(NSMidX(screenRect) - NSMidX(viewRect),
                                   NSMidY(screenRect) - NSMidY(viewRect),
                                   viewRect.size.width,
                                   viewRect.size.height);

    NSWindow * window = [[NSWindow alloc] initWithContentRect:windowRect
                                                              styleMask:windowStyle
                                                              backing:NSBackingStoreBuffered
                                                              defer:NO];

    assert(window);

    //Unfortunately, the last version of OpenGL supported on macOS is the 4.1.
    NSOpenGLPixelFormatAttribute windowedAttrs[] =
    {
        NSOpenGLPFAMultisample,
        NSOpenGLPFASampleBuffers, 0,
        NSOpenGLPFASamples, 0,
        NSOpenGLPFAAccelerated,
        NSOpenGLPFADoubleBuffer,
        NSOpenGLPFAColorSize, 32,
        NSOpenGLPFADepthSize, 24,
        NSOpenGLPFAAlphaSize, 8,
        NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion4_1Core,
        0
    };

    NSOpenGLPixelFormat* pf = [[NSOpenGLPixelFormat alloc] initWithAttributes:windowedAttrs];
    assert(pf);

    NSOpenGLContext*  _context = [[NSOpenGLContext alloc] initWithFormat: pf shareContext: NULL];
    assert(_context);


     [_context makeCurrentContext];

    if (!gladLoadGL())
        throw std::runtime_error("OCocoaGraphicsEngine - gladLoadGL failed");

    [_context release];
    [pf release];
    [window release];
}


OGraphicsEngine::~OGraphicsEngine()
{
}
