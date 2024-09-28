#ifndef _xpbs_h_INCLUDE
#define _xpbs_h_INCLUDE

#include "config.h"

#include <Foundation/Foundation.h>
#include <Foundation/NSUserDefaults.h>
#include <AppKit/NSPasteboard.h>

#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <x11/xdnd.h>
#if HAVE_XFIXES
#include <X11/extensions/Xfixes.h>
#endif

@interface	XPbOwner : NSObject
{
  NSPasteboard	*_pb;
  NSData	*_obj;
  NSString	*_name;
  Atom		_xPb;
  Time		_waitingForSelection;
  Time		_timeOfLastAppend;
  Time		_timeOfSetSelectionOwner;
  BOOL		_ownedByOpenStep;
}

+ (BOOL) _initRunLoop;
+ (BOOL) _initSelections;
+ (BOOL) _initAtoms;

+ (XPbOwner*) ownerByXPb: (Atom)p;
+ (XPbOwner*) ownerByOsPb: (NSString*)p;
+ (void) receivedEvent: (void*)data
                  type: (RunLoopEventType)type
                 extra: (void*)extra
               forMode: (NSString*)mode;
+ (NSDate*) timedOutEvent: (void*)data
                     type: (RunLoopEventType)type
                  forMode: (NSString*)mode;
+ (void) xEvent: (XEvent *)xEvent;
+ (void) xPropertyNotify: (XPropertyEvent*)xEvent;
+ (void) xSelectionClear: (XSelectionClearEvent*)xEvent;
+ (void) xSelectionNotify: (XSelectionEvent*)xEvent;
+ (void) xSelectionRequest: (XSelectionRequestEvent*)xEvent;

- (NSData*) data;
- (id) initWithXPb: (Atom)x osPb: (NSPasteboard*)o;
- (BOOL) ownedByOpenStep;
- (NSPasteboard*) osPb;
- (void) pasteboardChangedOwner: (NSPasteboard*)sender;
- (void) pasteboard: (NSPasteboard*)pb provideDataForType: (NSString*)type;
- (void) setData: (NSData*)obj;
- (void) setOwnedByOpenStep: (BOOL)flag;
- (void) setTimeOfLastAppend: (Time)when;
- (void) setWaitingForSelection: (Time)when;
- (Time) timeOfLastAppend;
- (Time) waitingForSelection;
- (Atom) xPb;
- (void) xSelectionClear;
- (void) xSelectionNotify: (XSelectionEvent*)xEvent;
- (void) xSelectionRequest: (XSelectionRequestEvent*)xEvent;
#if HAVE_XFIXES
+ (void) xFixesSelectionNotify: (XFixesSelectionNotifyEvent*)xEvent;
#endif
- (BOOL) xProvideSelection: (XSelectionRequestEvent*)xEvent;
- (Time) xTimeByAppending;
- (BOOL) xSendData: (NSData*) data format: (int) format 
	     items: (int) numItems type: (Atom) xType
		to: (Window) window property: (Atom) property;
@end

// Special subclass for the drag pasteboard
@interface	XDragPbOwner : XPbOwner
{
}
- (NSArray*) availableTypesForWindow:(Window) window;
@end

@interface	XDNDLocalDragProcess : NSObject
{
  Window src_window;
  NSPasteboard* pboard;
}

- (void) _start:(Window) win pasteboard:(NSPasteboard*) pb;
+ (void) startProcessForWindow:(Window) win pasteboard:(NSPasteboard*) pb;
@end
#endif
