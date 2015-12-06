//
//  GCArraySectionController.m
//  Demo
//
//  Created by Guillaume Campagna on 11-04-21.
//  Copyright 2011 LittleKiwi. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "DictionarySectionController.h"

@interface DictionarySectionController ()

@property (nonatomic, retain) OrderedDictionary* content;

@end

@implementation DictionarySectionController

@synthesize content, title;

- (id)initWithDictionary:(NSDictionary *)dict viewController:(UIViewController *)givenViewController {
	if ((self = [super initWithViewController:givenViewController])) {
		self.content = [OrderedDictionary dictionaryWithDictionary:dict];
		NSMutableArray *keys = self.content.keys;
		NSUInteger index;
		index = [self.content indexForKey:@"countRequest"];
		if (index!= 0 && index != -1 && keys.count>2) [keys exchangeObjectAtIndex:0 withObjectAtIndex:index];
		index = [self.content indexForKey:@"countEvent"];
		if (index!= 1 && index != -1 && keys.count>3) [keys exchangeObjectAtIndex:1 withObjectAtIndex:index];
		index = [self.content indexForKey:@"countNotify"];
		if (index!= 2 && index != -1 && keys.count>4) [keys exchangeObjectAtIndex:2 withObjectAtIndex:index];
	}
	return self;
}

#pragma mark -
#pragma mark Subclass

- (NSUInteger)contentNumberOfRow {
	return [self.content count];
}

- (NSString *)titleContentForRow:(NSUInteger)row {
	NSEnumerator *keysEnum = [self.content keyEnumerator];
	NSArray *keys = [keysEnum allObjects];
	NSString *key = [keys objectAtIndex:row];
	return key;
}

- (void)didSelectContentCellAtRow:(NSUInteger)row {
	[self.tableView deselectRowAtIndexPath:[self.tableView indexPathForSelectedRow]
								  animated:YES];
}


- (UITableViewCell *)cellForRow:(NSUInteger)row {
	UITableViewCell* cell = [super cellForRow:row];
	return cell;
}

- (UITableViewCell *)titleCell {
	UITableViewCell* titleCell = [super titleCell];
	if ([titleCell.textLabel.text isEqualToString:@"global"])
		titleCell.backgroundColor = [UIColor redColor];
	else
		titleCell.backgroundColor = [UIColor colorWithWhite:0.9 alpha:1.0];
   return titleCell;
}

- (UITableViewCell *)contentCellForRow:(NSUInteger)row {
	UITableViewCell* contentCell = [super contentCellForRow:row];

 
	contentCell.accessoryType = UITableViewCellAccessoryNone;
	contentCell.accessoryView = nil;
 	contentCell.indentationLevel = 1;

	NSEnumerator *keysEnum = [self.content keyEnumerator];
	NSArray *keys = [keysEnum allObjects];
	NSString *key = [keys objectAtIndex:row];
	
	NSString *value = [NSString  stringWithFormat:@"%@",[self.content valueForKey:key]];

	if ([key isEqualToString:@"creationdate"])
		value = [value substringToIndex:10];
	else
	{
		static NSNumberFormatter *_numberFormatter;
		if (!_numberFormatter) {
			_numberFormatter = [[NSNumberFormatter alloc] init];
			[_numberFormatter setNumberStyle:NSNumberFormatterDecimalStyle];
		}
		
		NSNumber *number = [NSNumber numberWithLong:atol([value UTF8String])];
		value = [_numberFormatter stringFromNumber:number];
	}
	
//	value = @"99 000 000";
	
	if ([key isEqualToString:@"countEvent"] ||
		[key isEqualToString:@"countNotify"] ||
		[key isEqualToString:@"countRequest"])
		contentCell.detailTextLabel.textColor = [UIColor redColor];
	else
		contentCell.detailTextLabel.textColor = [UIColor blackColor];
		
	contentCell.backgroundColor = [UIColor whiteColor];
		
 	contentCell.detailTextLabel.text = value;
	contentCell.detailTextLabel.font = [UIFont boldSystemFontOfSize:24.];

	contentCell.textLabel.font = [UIFont boldSystemFontOfSize:14.];

	return contentCell;
}

@end
