//
//  CLIMainViewController.m
//  CLI
//
//  Created by roland on 10/05/13.
//  Copyright (c) 2013 Clan of the CLoud. All rights reserved.
//

#import "CLIMainViewController.h"
#import "MBProgressHUD.h"
#include "cli.h"

#define kTabBarHeight 0
#define kKeyboardAnimationDuration 0.3

@interface UITextField (Selection)
- (NSRange) selectedRange;
- (void) setSelectedRange:(NSRange) range;
@end

@implementation UITextField (Selection)
- (NSRange) selectedRange
{
	UITextPosition* beginning = self.beginningOfDocument;

	UITextRange* selectedRange = self.selectedTextRange;
	UITextPosition* selectionStart = selectedRange.start;
	UITextPosition* selectionEnd = selectedRange.end;

	const NSInteger location = [self offsetFromPosition:beginning toPosition:selectionStart];
	const NSInteger length = [self offsetFromPosition:selectionStart toPosition:selectionEnd];

	return NSMakeRange(location, length);
}

- (void) setSelectedRange:(NSRange) range
{
	UITextPosition* beginning = self.beginningOfDocument;

	UITextPosition* startPosition = [self positionFromPosition:beginning offset:range.location];
	UITextPosition* endPosition = [self positionFromPosition:beginning offset:range.location + range.length];
	UITextRange* selectionRange = [self textRangeFromPosition:startPosition toPosition:endPosition];

	[self setSelectedTextRange:selectionRange];
  }

@end


@interface CLIMainViewController ()
{
	BOOL mReady;
	NSMutableArray *mCmdList;
	int mCurrentCmd;
	bool keyboardIsShown;
}

- (void) status:(eErrorCode)ec;
@end

MBProgressHUD *HUD = NULL;

class MyCLI : public CLI {
public:
	MyCLI(CLIMainViewController* w) : CLI() { wind = w; };
	virtual void logger(const char *message, typelog kind);
	virtual void stopActivity(eErrorCode ec);
	virtual void getBasePath(char *path) {
		strcpy(path, [[NSString stringWithFormat:@"%@/", [[NSBundle mainBundle] bundlePath]] UTF8String]);
		strcat(path, "scripts/");
	}

	CLIMainViewController *wind;
};

void MyCLI::logger (const char *message, typelog kind)
{
	switch (kind)
	{
		case kLOG:
			[wind Logger:[NSString stringWithUTF8String:message]];
		break;
		case kERR:
			[wind Logger:[NSString stringWithUTF8String:message] withColor:[UIColor redColor]];
		break;
		case kCMD:
			[wind Logger:[NSString stringWithFormat:@"> %s", message] withColor:[UIColor greenColor]];
		break;
		case kSCRIPT:
			[wind Logger:[NSString stringWithFormat:@">> %s", message] withColor:[UIColor greenColor]];
		break;
	}
	
}

void MyCLI::stopActivity (eErrorCode ec)
{
	[wind status:ec];
}


MyCLI *mCLI;

@implementation CLIMainViewController

@synthesize mainView, accessoryView;


- (void)viewDidLoad
{
	[super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.

	mReady = YES;

	mCLI = new MyCLI(self);
		
	[NSThread detachNewThreadSelector:@selector(idletask) toTarget:self withObject:nil];

	mCmdList = [NSMutableArray arrayWithCapacity:10];
	mCurrentCmd = -1;

	keyboardIsShown = NO;

	// Create the Quayboard bar
	JSMQuayboardBar *textViewAccessory = [[JSMQuayboardBar alloc] initWithFrame:CGRectMake(0, 0, self.view.bounds.size.width, 44)];
	textViewAccessory.delegate = self;
	
	editField.inputAccessoryView = textViewAccessory;

	// Maybe a key whose labels and values aren't the same
	JSMQuayboardButton *previousButton = [textViewAccessory addKeyWithTitle:@"↑" andValue:@"previous"];
	previousButton.accessibilityValue = previousButton.value;
	
	JSMQuayboardButton *nextButton = [textViewAccessory addKeyWithTitle:@"↓" andValue:@"next"];
	nextButton.accessibilityValue = nextButton.value;

	JSMQuayboardButton *leftButton = [textViewAccessory addKeyWithTitle:@"←" andValue:@"go left"];
	leftButton.accessibilityValue = leftButton.value;

	JSMQuayboardButton *rightButton = [textViewAccessory addKeyWithTitle:@"→" andValue:@"go right"];
	rightButton.accessibilityValue = rightButton.value;
	
	// Or build and add a custom key
	JSMQuayboardButton *customKey = [[JSMQuayboardButton alloc] initWithFrame:CGRectZero];
	customKey.title = @"▾";
	customKey.accessibilityValue = NSLocalizedString(@"Hide Keyboard",@"Accessibility value for key in Quayboard that hides the keyboard.");
	[customKey addTarget:self action:@selector(clearTextView:) forControlEvents:UIControlEventTouchUpInside];
	[textViewAccessory addKey:customKey];
	
	// Deal with events and changes
	[NSNotificationCenter.defaultCenter addObserver:self selector:@selector(keyboardWillShow:) name:UIKeyboardWillShowNotification object:nil];
	[NSNotificationCenter.defaultCenter addObserver:self selector:@selector(keyboardWillHide:) name:UIKeyboardWillHideNotification object:nil];

}

- (IBAction)clearTextView:(id)sender {
	[editField resignFirstResponder];
}

#pragma mark - Quayboard Bar Delegate

- (void)quayboardBar:(JSMQuayboardBar *)quayboardBar keyWasPressed:(JSMQuayboardButton *)key {
	// Find the range of the selected text
	NSRange range = editField.selectedRange;
	
	if ([key.value isEqualToString:@"go left"])
	{
		// Move the selection to 1 car left
		range.location -= 1;
		range.length = 0;
		editField.selectedRange = range;
	}
	else if ([key.value isEqualToString:@"go right"])
	{
		// Move the selection to 1 car left
		range.location += 1;
		range.length = 0;
		editField.selectedRange = range;
	}
	else if ([key.value isEqualToString:@"previous"])
	{
		[self upKey:self];
	}
	else if ([key.value isEqualToString:@"next"])
	{
		[self downKey:self];
	}
	else
	{
		// Get the relevant strings
		NSString *firstHalfString = [editField.text substringToIndex:range.location];
		NSString *insertingString = key.value;
		NSString *secondHalfString = [editField.text substringFromIndex:range.location+range.length];
		
		// Update the textView's text
		editField.text = [NSString stringWithFormat: @"%@%@%@", firstHalfString, insertingString, secondHalfString];

		// Move the selection to after our inserted text
		range.location += insertingString.length;
		range.length = 0;
		editField.selectedRange = range;
	}
}

#pragma mark - Respond to the keyboard being displayed and hidden

- (void)keyboardWillHide:(NSNotification *)n
{
	NSDictionary* userInfo = [n userInfo];

	// get the size of the keyboard
	CGSize keyboardSize = [[userInfo objectForKey:UIKeyboardFrameBeginUserInfoKey] CGRectValue].size;


//	UIDeviceOrientation or = [UIDevice currentDevice].orientation;
//	if (or == UIDeviceOrientationLandscapeLeft ||
//		or == UIDeviceOrientationLandscapeRight)
	if(keyboardSize.height > keyboardSize.width)
	{
		CGFloat a = keyboardSize.height;
		keyboardSize.height = keyboardSize.width;
		keyboardSize.width = a;
	}

	// resize the scrollview
	CGRect viewFrame = self.mainView.frame;
	// I'm also subtracting a constant kTabBarHeight because my UIScrollView was offset by the UITabBar so really only the portion of the keyboard that is leftover pass the UITabBar is obscuring my UIScrollView.
	viewFrame.size.height += (keyboardSize.height - kTabBarHeight);

	[UIView beginAnimations:nil context:NULL];
	[UIView setAnimationBeginsFromCurrentState:YES];
	// The kKeyboardAnimationDuration I am using is 0.3
	[UIView setAnimationDuration:kKeyboardAnimationDuration];
	[self.mainView setFrame:viewFrame];
	[UIView commitAnimations];

	keyboardIsShown = NO;
}


- (void)keyboardWillShow:(NSNotification *)n
{
	// This is an ivar I'm using to ensure that we do not do the frame size adjustment on the `UIScrollView` if the keyboard is already shown.  This can happen if the user, after fixing editing a `UITextField`, scrolls the resized `UIScrollView` to another `UITextField` and attempts to edit the next `UITextField`.  If we were to resize the `UIScrollView` again, it would be disastrous.  NOTE: The keyboard notification will fire even when the keyboard is already shown.
	if (keyboardIsShown) {
		return;
	}

	NSDictionary* userInfo = [n userInfo];

	// get the size of the keyboard
	CGSize keyboardSize = [[userInfo objectForKey:UIKeyboardFrameBeginUserInfoKey] CGRectValue].size;
	
	//UIDeviceOrientation or = [UIDevice currentDevice].orientation;
	//if (or == UIDeviceOrientationLandscapeLeft ||
	//	or == UIDeviceOrientationLandscapeRight)
	if(keyboardSize.height > keyboardSize.width)
	{
		CGFloat a = keyboardSize.height;
		keyboardSize.height = keyboardSize.width;
		keyboardSize.width = a;
	}
		
	CGRect viewFrame = self.mainView.frame;
	// resize the noteView
	// I'm also subtracting a constant kTabBarHeight because my UIScrollView was offset by the UITabBar so really only the portion of the keyboard that is leftover pass the UITabBar is obscuring my UIScrollView.
	viewFrame.size.height -= (keyboardSize.height - kTabBarHeight);

	[UIView beginAnimations:nil context:NULL];
	[UIView setAnimationBeginsFromCurrentState:YES];
	// The kKeyboardAnimationDuration I am using is 0.3
	[UIView setAnimationDuration:kKeyboardAnimationDuration];
	[self.mainView setFrame:viewFrame];
	[UIView commitAnimations];

	keyboardIsShown = YES;
}


- (void)viewDidUnload
{
	// unregister for keyboard notifications while not visible.
	[[NSNotificationCenter defaultCenter] removeObserver:self name:UIKeyboardWillShowNotification object:nil];
	// unregister for keyboard notifications while not visible.
	[[NSNotificationCenter defaultCenter] removeObserver:self name:UIKeyboardWillHideNotification object:nil];
}

- (void)didReceiveMemoryWarning
{
	[super didReceiveMemoryWarning];
	// Dispose of any resources that can be recreated.
}

- (BOOL)textFieldShouldBeginEditing:(UITextField *)aTextField {

/**
	if (aTextField.inputAccessoryView == nil) {
		[[NSBundle mainBundle] loadNibNamed:@"AccessoryView" owner:self options:nil];
		// Loading the AccessoryView nib file sets the accessoryView outlet.
		aTextField.inputAccessoryView = accessoryView;	
		// After setting the accessory view for the text view, we no longer need a reference to the accessory view.
		self.accessoryView = nil;
	}
***/

	return YES;
}

- (BOOL)textFieldShouldReturn:(UITextField *)textField
{
//	[textField resignFirstResponder];
	if (mReady)
	{
		[self setReady: NO];

		[self AddCmd: textField.text];
		[self Logger:[NSString stringWithFormat:@"> %@", textField.text] withColor:[UIColor greenColor]];
		
		eErrorCode ec = mCLI->execute([textField.text UTF8String]);
		
		if (ec!=enNoErr)
		{
			[self Logger:[NSString stringWithUTF8String:errorString(ec)] withColor:[UIColor redColor]];
			[self setReady: YES];
		}
			
		textField.text = @"";
	}
	return YES;
}

- (void)textFieldDidEndEditing:(UITextField *)textField
{
	NSLog(@"%@", [NSString stringWithString:textField.text]);
}

- (void) AddCmd:(NSString *)cmd
{
	mCurrentCmd = -1;
	[mCmdList insertObject:cmd atIndex:0];
}

- (NSString *) PreviousCmd
{
	if (mCurrentCmd <= -1)
		return [mCmdList objectAtIndex:++mCurrentCmd];
	else if (mCurrentCmd<mCmdList.count-1)
		return [mCmdList objectAtIndex:++mCurrentCmd];
	else
		return NULL;
}

- (NSString *) NextCmd
{
	if (mCurrentCmd>0)
		return [mCmdList objectAtIndex:--mCurrentCmd];
	else if (mCurrentCmd==0)
		mCurrentCmd=-1;
	
	return @"";
}

- (IBAction)upKey:(id)sender
{
	NSString *cmd = [self PreviousCmd];
	if (cmd)
	{
		editField.text= cmd;
	}
}

- (IBAction)downKey:(id)sender
{
	NSString *cmd = [self NextCmd];
	if (cmd)
	{
		editField.text= cmd;
	}
}

- (void) Logger:(NSString *)message withColor:(UIColor *)color
{
	[consoleView setEditable: YES];
	unsigned textLength = (unsigned) [[consoleView text] length];

	[consoleView setSelectedRange:NSMakeRange(textLength, 0)];
	[consoleView insertText:message];
	[consoleView insertText:@"\n"];
//	[consoleView setTextColor:color range:NSMakeRange(textLength, message.length)];
	[consoleView setEditable: NO];

	textLength = (unsigned) [[consoleView text] length];
	[consoleView scrollRangeToVisible:NSMakeRange(textLength, 0)];

}


- (void) Logger:(NSString *)message
{
	[self Logger:message withColor:[UIColor whiteColor]];
}

- (void) popNextCallback
{
	mCLI->idle();
}

- (void) idletask
{
	while (true)
	{
		usleep(100000);
		[self performSelectorOnMainThread:@selector(popNextCallback) withObject:self waitUntilDone:YES];
	}
}

- (void) status:(eErrorCode)ec
{
	[self setReady: YES];
	if (ec)
		[self Logger:[NSString stringWithUTF8String:errorString(ec)] withColor:[UIColor redColor]];
	else
		[self Logger:[NSString stringWithFormat:@"Done. (in %lu ms)",mCLI->millisecondsElapsedSinceLastExecute()]withColor:[UIColor greenColor]];
}

- (void) setReady:(bool) state
{
	mReady = state;
	if (HUD==NULL)
	{
		HUD = [[MBProgressHUD alloc] initWithView:consoleView];
		[self.view addSubview:HUD];
		
		HUD.labelText = @"waiting...";
		HUD.minSize = CGSizeMake(135.f, 135.f);
		HUD.dimBackground = YES;
		HUD.graceTime = 0.5;
	}

	if (state)
	{
		[HUD hide:YES];
		HUD.taskInProgress  = NO;
	}
	else
	{
		HUD.taskInProgress  = YES;
		[HUD show:YES];
	}


}

+ (void) HandleURL: (NSString *)url source:(NSString*)source
{
	if (mCLI) {
		CHJSON j;
		j.Put("url", [url UTF8String]);
		j.Put("source", [source UTF8String]);
		mCLI->HandleURL(&j);
	}
}

#pragma mark - Flipside View Controller

- (void)flipsideViewControllerDidFinish:(CLIFlipsideViewController *)controller
{
	if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
		[self dismissViewControllerAnimated:YES completion:nil];
	} else {
		[self.flipsidePopoverController dismissPopoverAnimated:YES];
		self.flipsidePopoverController = nil;
	}
}

- (void)popoverControllerDidDismissPopover:(UIPopoverController *)popoverController
{
	self.flipsidePopoverController = nil;
}

- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
	if ([[segue identifier] isEqualToString:@"showAlternate"]) {
		[(CLIFlipsideViewController*) [segue destinationViewController] setDelegate:self];
		
		if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPad) {
			UIPopoverController *popoverController = [(UIStoryboardPopoverSegue *)segue popoverController];
			self.flipsidePopoverController = popoverController;
			popoverController.delegate = self;
		}
	}
}

- (IBAction)togglePopover:(id)sender
{
	if (self.flipsidePopoverController) {
		[self.flipsidePopoverController dismissPopoverAnimated:YES];
		self.flipsidePopoverController = nil;
	} else {
		[self performSegueWithIdentifier:@"showAlternate" sender:sender];
	}
}

@end
