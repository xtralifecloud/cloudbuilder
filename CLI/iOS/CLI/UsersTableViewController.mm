//
//  RootViewController.m
//  PullToRefresh
//
//  Created by Leah Culver on 7/25/10.
//  Copyright Plancast 2010. All rights reserved.
//

#import "UsersTableViewController.h"

#include "CotCHelpers.h"
#include "CHJSON.h"

using namespace CotCHelpers;

@implementation UsersTableViewController

@synthesize url;

- (void)viewDidLoad {
	[super viewDidLoad];
	
	self.navigationItem.rightBarButtonItem = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemDone target:self action:@selector(Done)];
	
	items = [[NSMutableArray alloc] initWithObjects:nil];
	
	[items addObject:@"Loading users..."];
	
	[self refresh];
}

- (void) Done
{
	NSLog(@"close window");
	[self dismissViewControllerAnimated:YES completion:nil];
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
	return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
	return [items count];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {

	static NSString *CellIdentifier = @"CellIdentifier";
	UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
	if (cell == nil) {
		cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CellIdentifier];
	}

	cell.textLabel.text = [items objectAtIndex:indexPath.row];
	cell.selectionStyle = UITableViewCellSelectionStyleNone;

	return cell;
}

- (void) refresh
{
	NSLog(@"url = %@",self.url);
	
	NSMutableURLRequest *request = [NSMutableURLRequest requestWithURL:
			[NSURL URLWithString:self.url]
			cachePolicy:NSURLRequestReloadIgnoringLocalAndRemoteCacheData
			timeoutInterval:10];

	[request setHTTPMethod: @"GET"];
	
	[NSURLConnection sendAsynchronousRequest:request
		queue:[NSOperationQueue mainQueue]
		completionHandler:^(NSURLResponse *response, NSData *data, NSError *error) {
		if (data)
		{
			NSString *str = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
			NSLog(@"%@",str);
	
			CHJSON *json = CHJSON::parse([str UTF8String]);
			if (json)
			{
				const CHJSON *j = json->Get("users");
				if (j)
				{
					[items removeAllObjects];
					int nb = j->size();
					
					if (nb == 0) [items addObject:@"No users"];
					
					for (int i=0; i<nb; i++)
						[items addObject:[NSString stringWithUTF8String:j->Get(i)->valueString()]];
					
					[self performSelector:@selector(reload)];
				}
				delete json;
			}
		}
		else
			[items addObject:@"Error on request ! Please retry..."];
	}];	
}

- (void)reload {
	[self.tableView reloadData];
	[self stopLoading];
}

@end

