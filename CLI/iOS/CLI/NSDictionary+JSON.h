//
//  NSDictionary+JSON.h
//  CryHavoc
//
//  Created by roland on 01/06/13.
//  Copyright (c) 2013 zeOne Company. All rights reserved.
//

#import <Foundation/Foundation.h>

#include "CHJSON.h"

@interface NSDictionary (JSON)

- (CotCHelpers::CHJSON*) toJSON;
+ (NSDictionary *) dictionnaryWithJSON:(const CotCHelpers::CHJSON*)json;

@end
