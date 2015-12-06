//
//  CLIMainViewController.h
//  CLI
//
//  Created by roland on 10/05/13.
//  Copyright (c) 2013 Clan of the CLoud. All rights reserved.
//

#import "CLIFlipsideViewController.h"
#import "JSMQuayboardBar.h"

@interface CLIMainViewController : UIViewController <CLIFlipsideViewControllerDelegate, UIPopoverControllerDelegate, UITextFieldDelegate, JSMQuayboardBarDelegate>
{
	IBOutlet UITextView *consoleView;
	IBOutlet UITextField *editField;
	UIView *mainView;
	UIView *accessoryView;
}

@property (strong, nonatomic) UIPopoverController *flipsidePopoverController;
@property (strong, nonatomic) IBOutlet UIView *mainView;
@property (strong, nonatomic) IBOutlet UIView *accessoryView;

- (void) Logger:(NSString *)message;
- (void) Logger:(NSString *)message withColor:(UIColor *)color;

+ (void) HandleURL: (NSString *)url source:(NSString*)source;

- (IBAction)upKey:(id)sender;
- (IBAction)downKey:(id)sender;

@end

