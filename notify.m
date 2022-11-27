/* Copyright (c) XNSC 2022
   This code is licensed under the MIT license (see LICENSE for details)

   Sends a custom notification to the macOS notification center. */

#import <Foundation/Foundation.h>
#import <objc/runtime.h>

NSString *bundle_id = nil;

@implementation NSBundle(notify)

- (NSString *)
__bundle_id
{
  if (self == [NSBundle mainBundle])
    return bundle_id ? bundle_id : @"com.apple.finder";
  else
    return [self __bundle_id];
}

@end

@interface NotificationCenterDelegate :
  NSObject <NSUserNotificationCenterDelegate>

@property (nonatomic, assign) BOOL keep_running;

@end

@implementation NotificationCenterDelegate

- (void)
userNotificationCenter:(NSUserNotificationCenter *) center
didDeliverNotification:(NSUserNotification *) notification
{
  self.keep_running = NO;
}

@end

static BOOL
install_bundle_hook (void)
{
  Class c = objc_getClass ("NSBundle");
  if (c)
    {
      method_exchangeImplementations
	(class_getInstanceMethod (c, @selector (bundleIdentifier)),
	 class_getInstanceMethod (c, @selector (__bundle_id)));
      return YES;
    }
  return NO;
}

int
main (int argc, char **argv)
{
  @autoreleasepool
    {
      if (install_bundle_hook ())
	{
	  NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
	  NSUserNotificationCenter *nc;
	  NotificationCenterDelegate *delegate;
	  NSUserNotification *note;

	  bundle_id = [defaults stringForKey:@"identifier"];
	  nc = [NSUserNotificationCenter defaultUserNotificationCenter];
	  delegate = [[NotificationCenterDelegate alloc] init];
	  delegate.keep_running = YES;
	  nc.delegate = delegate;
	  note = [[NSUserNotification alloc] init];
	  note.title = [defaults stringForKey:@"title"];
	  note.subtitle = [defaults stringForKey:@"subtitle"];
	  note.informativeText = [defaults stringForKey:@"informativeText"];

	  if (!(note.title || note.subtitle || note.informativeText))
	    printf ("Usage: notify [-identifier <ID>] [-title <TITLE>] "
		    "[-subtitle <SUBTITLE>] [-informativeText <TEXT>]\n");
	  else
	    {
	      [nc deliverNotification:note];
	      while (delegate.keep_running)
		[[NSRunLoop currentRunLoop]
		  runUntilDate:[NSDate dateWithTimeIntervalSinceNow:0.1]];
	    }
	}
    }
  return 0;
}
