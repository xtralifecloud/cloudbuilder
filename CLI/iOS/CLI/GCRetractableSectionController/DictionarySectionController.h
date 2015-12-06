//
//  GCArraySectionController.h
//  Demo
//
//  Created by Guillaume Campagna on 11-04-21.
//  Copyright 2011 LittleKiwi. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GCRetractableSectionController.h"
#import "OrderedDictionary.h"

//This is a GCRetractableSectionController that take a NSArray and display it like the simple example did.
//You can use it directly in your project if your retractable controller is simple!

@interface DictionarySectionController : GCRetractableSectionController

@property (nonatomic, copy, readwrite) NSString* title;

- (id)initWithDictionary:(NSDictionary*) dict viewController:(UIViewController *)givenViewController;

@end
