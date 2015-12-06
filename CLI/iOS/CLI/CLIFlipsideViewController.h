//
//  CLIFlipsideViewController.h
//  CLI
//
//  Created by roland on 10/05/13.
//  Copyright (c) 2013 Clan of the CLoud. All rights reserved.
//

#import <UIKit/UIKit.h>

@class CLIFlipsideViewController;

@protocol CLIFlipsideViewControllerDelegate
- (void)flipsideViewControllerDidFinish:(CLIFlipsideViewController *)controller;
@end

@interface CLIFlipsideViewController : UIViewController<UITableViewDataSource, UITableViewDelegate>

@property (weak, nonatomic) id <CLIFlipsideViewControllerDelegate> delegate;

@property IBOutlet UISegmentedControl *envBar;
@property IBOutlet UITableView *table;
@property IBOutlet UIBarButtonItem *btnRefresh;

- (UITableView *)tableView;

- (IBAction)done:(id)sender;
- (IBAction)refresh:(id)sender;
- (IBAction)envChanged:(id)sender;

@end
