//
//  CLIFlipsideViewController.m
//  CLI
//
//  Created by roland on 10/05/13.
//  Copyright (c) 2013 Clan of the CLoud. All rights reserved.
//

#import "CLIFlipsideViewController.h"
#import "NSDictionary+JSON.h"
#import "GCRetractableSectionController.h"
#import "DictionarySectionController.h"
#import "TTTQuadrantControl.h"
#import "UsersTableViewController.h"

#define SANDBOX 0
#define SANDBOX_URL @"https://controller-sandbox.clanofthecloud.mobi:4000/analytics/yJxtpGCdC9Z1RrRsJkB8/"

//#define SANDBOX_URL @"https://localhost:4000/analytics/yJxtpGCdC9Z1RrRsJkB8/"

#define PROD 1
#define PROD_URL @"https://controller-prod.clanofthecloud.mobi:4000/analytics/yJxtpGCdC9Z1RrRsJkB8/"

using namespace CotCHelpers;

#import "MBProgressHUD.h"

@interface CLIFlipsideViewController () {
	NSDictionary *stats;
	NSDictionary *xau;
	NSArray *retractableControllers;
}
@end

@implementation CLIFlipsideViewController

- (UITableView *)tableView;
{
	return self.table;
}

- (void)awakeFromNib
{
	self.contentSizeForViewInPopover = CGSizeMake(320.0, 680.0);
	[super awakeFromNib];
}

- (void)viewDidLoad
{
	[super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
	[self.envBar setSelectedSegmentIndex:SANDBOX];
		
	retractableControllers = [NSArray array];
	stats = [NSDictionary dictionary];
	xau = [NSDictionary dictionary];
	
	[self sendGetDatas];

}

-(void) getDatas
{
	// @"https://controller-sandbox.clanofthecloud.mobi:4000/analytics/yJxtpGCdC9Z1RrRsJkB8/stats"
	
	NSString *url = [NSString stringWithFormat:@"%@",
		self.envBar.selectedSegmentIndex==SANDBOX ? SANDBOX_URL : PROD_URL ];
	
	NSString *stats_url = [url stringByAppendingString:@"stats"];
	CHJSON *json  = [self getStats:stats_url];
	if (json != nil)
	{
		stats = [NSDictionary dictionnaryWithJSON:json->Get("metrics")];
		NSLog(@"stats dict = %@", stats);

		
		NSMutableArray *arr = [NSMutableArray arrayWithCapacity:10];
			
		NSEnumerator *games = [stats keyEnumerator];
		while (NSString *name = [games nextObject])
		{
			NSDictionary *gamestats = [stats valueForKey:name];
			DictionarySectionController* arrayController = [[DictionarySectionController alloc]
								initWithDictionary:gamestats
								viewController:self];
			arrayController.title = name;
			if ([name isEqualToString:@"global"])
				[arr insertObject:arrayController atIndex:0];
			else
				[arr addObject:arrayController];
		}

		retractableControllers = [NSArray arrayWithArray:arr];
				
		xau = [NSDictionary dictionnaryWithJSON:json->Get("xau")];
		NSLog(@"xau dict = %@", xau);

		delete json;
	}
	else
	{
		retractableControllers = [NSArray array];
		stats = [NSDictionary dictionary];
		xau = [NSDictionary dictionary];	
	}
	
}

-(void) sendGetDatas
{	
	[MBProgressHUD showHUDAddedTo:self.tableView animated:YES];

	NSString *url = [NSString stringWithFormat:@"%@",
		self.envBar.selectedSegmentIndex==SANDBOX ? SANDBOX_URL : PROD_URL ];
	
	NSString *stats_url = [url stringByAppendingString:@"stats"];
	
	[self getStatsAsync:stats_url];
}

-(void) hasNewDatas: (CHJSON *)json
{
	[MBProgressHUD hideHUDForView:self.tableView animated:YES];
	
	if (json != nil)
	{
		stats = [NSDictionary dictionnaryWithJSON:json->Get("metrics")];
		NSLog(@"stats dict = %@", stats);
		
		NSMutableArray *arr = [NSMutableArray arrayWithCapacity:10];
			
		NSEnumerator *games = [stats keyEnumerator];
		while (NSString *name = [games nextObject])
		{
			NSDictionary *gamestats = [stats valueForKey:name];
			DictionarySectionController* arrayController = [[DictionarySectionController alloc]
								initWithDictionary:gamestats
								viewController:self];
			arrayController.title = name;
			if ([name isEqualToString:@"global"])
				[arr insertObject:arrayController atIndex:0];
			else
				[arr addObject:arrayController];
		}

		retractableControllers = [NSArray arrayWithArray:arr];
				
		xau = [NSDictionary dictionnaryWithJSON:json->Get("xau")];
		NSLog(@"xau dict = %@", xau);
	}
	else
	{
		retractableControllers = [NSArray array];
		stats = [NSDictionary dictionary];
		xau = [NSDictionary dictionary];	
	}
	
	[self.tableView reloadData];
}

- (void)didReceiveMemoryWarning
{
	[super didReceiveMemoryWarning];
	// Dispose of any resources that can be recreated.
}

#pragma get remote data

- (CHJSON *) getStats : (NSString *)serverAddress
{
	NSMutableURLRequest *request = [NSMutableURLRequest requestWithURL:
			[NSURL URLWithString:serverAddress]
			cachePolicy:NSURLRequestReloadIgnoringLocalAndRemoteCacheData
			timeoutInterval:10];

	[request setHTTPMethod: @"GET"];

	NSError *requestError;
	NSURLResponse *urlResponse = nil;


	NSData *response = [NSURLConnection sendSynchronousRequest:request returningResponse:&urlResponse error:&requestError];
	
	NSString *str = [[NSString alloc] initWithData:response encoding:NSUTF8StringEncoding];
	NSLog(@"%@",str);
	
	CHJSON *json = CHJSON::parse([str UTF8String]);
	
	return json;
}

- (void) getStatsAsync : (NSString *)serverAddress
{
	NSMutableURLRequest *request = [NSMutableURLRequest requestWithURL:
			[NSURL URLWithString:serverAddress]
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
			[self hasNewDatas:json];
			delete json;
		}
	}];	
}


- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
	return retractableControllers.count;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
	GCRetractableSectionController* sectionController = [retractableControllers objectAtIndex:section];
	return sectionController.numberOfRow;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
	GCRetractableSectionController* sectionController = [retractableControllers objectAtIndex:indexPath.section];
	return [sectionController cellForRow:indexPath.row];
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
	GCRetractableSectionController* sectionController = [retractableControllers objectAtIndex:indexPath.section];
	return [sectionController didSelectCellAtRow:indexPath.row];
}

- (CGFloat)tableView:(UITableView *)tableView heightForFooterInSection:(NSInteger)section
{
	return 90.;
}

- (UIView *)tableView:(UITableView *)tableView viewForFooterInSection:(NSInteger)section
{
	GCRetractableSectionController* sectionController = [retractableControllers objectAtIndex:section];
	
	NSDictionary *gamexau = [xau valueForKey:sectionController.title];

	NSString *str;
	str = [NSString stringWithFormat:@"%@", [gamexau valueForKey:@"ccu"]];
	NSNumber *CCU = [NSNumber numberWithLong:atol([str UTF8String])];
	str = [NSString stringWithFormat:@"%@", [gamexau valueForKey:@"dau"]];
	NSNumber *DAU = [NSNumber numberWithLong:atol([str UTF8String])];
	str = [NSString stringWithFormat:@"%@", [gamexau valueForKey:@"mau"]];
	NSNumber *MAU = [NSNumber numberWithLong:atol([str UTF8String])];
	str = [NSString stringWithFormat:@"%@", [gamexau valueForKey:@"nbusers"]];
	NSNumber *Users = [NSNumber numberWithLong:atol([str UTF8String])];
	
	CGRect frame = CGRectMake(0, 0, tableView.bounds.size.width, 90);
	UIView *footerView = [[UIView alloc] initWithFrame:frame];
	CGRect frame2 = CGRectMake(10, 0, tableView.bounds.size.width-20, 90);
	TTTQuadrantControl * quadrantControl = [[TTTQuadrantControl alloc] initWithFrame:frame2];
	
	quadrantControl.delegate = self;
	quadrantControl.userData = sectionController.title;
	
	[quadrantControl setNumber:CCU
							caption:@"CCU"
							 action:@selector(actionCCU:)
						forLocation:TopLeftLocation];
	
	[quadrantControl setNumber:MAU
							caption:@"MAU" 
							 action:@selector(actionMAU:)
						forLocation:TopRightLocation];
	
	[quadrantControl setNumber:Users
							caption:@"users" 
							 action:nil
						forLocation:BottomLeftLocation];
	
	[quadrantControl setNumber:DAU
							caption:@"DAU" 
							 action:@selector(actionDAU:)
						forLocation:BottomRightLocation];	

	[footerView addSubview:quadrantControl];
	footerView.userInteractionEnabled = YES;
	return footerView;
}

-(void) actionCCU:(TTTQuadrantControl*)quadrant
{
	NSLog(@"%@", quadrant.userData);
	
	NSString *title = [NSString stringWithFormat:@"ccu:%@", quadrant.userData];	
	[self showusers:title];	
}

-(void) actionDAU:(TTTQuadrantControl*)quadrant
{
	NSLog(@"%@", quadrant.userData);	
	NSDate *date = [NSDate date];
	NSCalendarUnit unitFlags = NSYearCalendarUnit | NSMonthCalendarUnit | NSDayCalendarUnit;
	NSCalendar *calendar = [[NSCalendar alloc] initWithCalendarIdentifier:NSGregorianCalendar];
	NSDateComponents *comps = [calendar components:unitFlags fromDate:date];
	NSString *datedau = [NSString stringWithFormat:@"%04d-%02d-%02d", comps.year, comps.month, comps.day];
	
	NSString *title = [NSString stringWithFormat:@"dau:%@:%@", quadrant.userData, datedau];
	[self showusers:title];
}

-(void) actionMAU:(TTTQuadrantControl*)quadrant
{
	NSLog(@"%@", quadrant.userData);	
	NSDate *date = [NSDate date];
	NSCalendarUnit unitFlags = NSYearCalendarUnit | NSMonthCalendarUnit | NSDayCalendarUnit;
	NSCalendar *calendar = [[NSCalendar alloc] initWithCalendarIdentifier:NSGregorianCalendar];
	NSDateComponents *comps = [calendar components:unitFlags fromDate:date];
	NSString *datemau = [NSString stringWithFormat:@"%04d-%02d", comps.year, comps.month];
	
	NSString *title = [NSString stringWithFormat:@"mau:%@:%@", quadrant.userData, datemau];
	[self showusers:title];
}

-(void) showusers:(NSString*) title
{
	UsersTableViewController *tc = [[UsersTableViewController alloc] init];
	tc.title = title;
	
	NSString *url = [NSString stringWithFormat:@"%@",
		self.envBar.selectedSegmentIndex==SANDBOX ? SANDBOX_URL : PROD_URL ];
	
	url = [url stringByAppendingString:@"users/"];
	tc.url = [url stringByAppendingString:title];
	
	UINavigationController *navigationController = [[UINavigationController alloc] initWithRootViewController:tc];
	[self presentViewController:navigationController animated:YES completion:nil];
}


#pragma mark - Actions

- (void)envChanged:(id)sender
{
	[self refresh:nil];
}

- (IBAction)done:(id)sender
{
	[self.delegate flipsideViewControllerDidFinish:self];
}

- (IBAction)refresh:(id)sender
{
	[self sendGetDatas];
//	[self.tableView reloadData];
}

@end
