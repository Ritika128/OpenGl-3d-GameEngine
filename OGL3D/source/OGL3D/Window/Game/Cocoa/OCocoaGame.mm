#include <OGL3D/Game/OGame.h>
#include <OGL3D/Window/OWindow.h>
#include <OGL3D/Graphics/OGraphicsEngine.h>
#import <Cocoa/Cocoa.h>


//Cocoa Application Delegate -  It allows to catch the events generated by the Application (NSApplication, the main application class of Cocoa framework)
//---------------------------------------------------
@interface CocoaAppDelegate : NSObject <NSApplicationDelegate>
{
@public
  OGame *app;
}

- (NSApplicationTerminateReply)applicationShouldTerminate:(NSApplication *)sender;
- (void)applicationDidFinishLaunching:(NSNotification *)aNotification;
@end

@implementation CocoaAppDelegate
- (NSApplicationTerminateReply)applicationShouldTerminate:(NSApplication *)sender
{
    app->quit();
    return NSTerminateCancel;
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
}

- (void)applicationWillUpdate:(NSNotification *)aNotification
{
}

@end
//---------------------------------------------------

