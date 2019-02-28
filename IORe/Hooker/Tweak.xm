#import <SpringBoard/SpringBoard.h>

%hook SpringBoard

-(void)applicationDidFinishLaunching:(id)application {
	%orig;
	
	UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"backboardd is hooked!" 
		message:@"ThLulz" 
		delegate:nil 
		cancelButtonTitle:@"lolol?" 
		otherButtonTitles:nil];
	[alert show];
	[alert release];
}

%end
