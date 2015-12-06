//
//  NSDictionary+JSON.m
//  CryHavoc
//
//  Created by roland on 01/06/13.
//  Copyright (c) 2013 zeOne Company. All rights reserved.
//

#import "NSDictionary+JSON.h"
#import "CotCHelpers.h"

@implementation NSDictionary (JSON)

using namespace CotCHelpers;

- (CotCHelpers::CHJSON*) toJSON
{
	CotCHelpers::CHJSON *json = new CHJSON();

	NSError *error; 
	NSData *jsonData = [NSJSONSerialization dataWithJSONObject:self
												   options:kNilOptions
													 error:&error];

	if (!jsonData) {
		NSLog(@"Got an error: %@", error);
	} else {
		NSString *jsonString = [[NSString alloc] initWithData:jsonData encoding:NSUTF8StringEncoding];
		json = CHJSON::parse([jsonString UTF8String]);
		NSLog(@"%s" , json->printFormatted().c_str());
	}
	
	return json;
}

+ (NSDictionary *) dictionnaryWithJSON:(const CotCHelpers::CHJSON*)json
{
	NSString *jsonstring  = [NSString stringWithUTF8String:json->print()];
	NSLog(@"json = '%@'", jsonstring);
	
//	[jsonstring stringByTrimmingCharactersInSet:<#(NSCharacterSet *)#>];
	
	NSError *error;
	NSDictionary *dictionary = [NSJSONSerialization JSONObjectWithData:[jsonstring dataUsingEncoding:NSUTF8StringEncoding] options:kNilOptions error:&error];
	
	NSLog(@"%@", error);
	
	return dictionary;
}

@end
