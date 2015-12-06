/*
	 File: MailWindowController.m 
 Abstract: Custom NSWindowController subclass used for managing the mail-style window.
  
  Version: 1.0 
  
 Disclaimer: IMPORTANT:  This Apple software is supplied to you by Apple 
 Inc. ("Apple") in consideration of your agreement to the following 
 terms, and your use, installation, modification or redistribution of 
 this Apple software constitutes acceptance of these terms.  If you do 
 not agree with these terms, please do not use, install, modify or 
 redistribute this Apple software. 
  
 In consideration of your agreement to abide by the following terms, and 
 subject to these terms, Apple grants you a personal, non-exclusive 
 license, under Apple's copyrights in this original Apple software (the 
 "Apple Software"), to use, reproduce, modify and redistribute the Apple 
 Software, with or without modifications, in source and/or binary forms; 
 provided that if you redistribute the Apple Software in its entirety and 
 without modifications, you must retain this notice and the following 
 text and disclaimers in all such redistributions of the Apple Software. 
 Neither the name, trademarks, service marks or logos of Apple Inc. may 
 be used to endorse or promote products derived from the Apple Software 
 without specific prior written permission from Apple.  Except as 
 expressly stated in this notice, no other rights or licenses, express or 
 implied, are granted by Apple herein, including but not limited to any 
 patent rights that may be infringed by your derivative works or by other 
 works in which the Apple Software may be incorporated. 
  
 The Apple Software is provided by Apple on an "AS IS" basis.  APPLE 
 MAKES NO WARRANTIES, EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION 
 THE IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY AND FITNESS 
 FOR A PARTICULAR PURPOSE, REGARDING THE APPLE SOFTWARE OR ITS USE AND 
 OPERATION ALONE OR IN COMBINATION WITH YOUR PRODUCTS. 
  
 IN NO EVENT SHALL APPLE BE LIABLE FOR ANY SPECIAL, INDIRECT, INCIDENTAL 
 OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
 SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 INTERRUPTION) ARISING IN ANY WAY OUT OF THE USE, REPRODUCTION, 
 MODIFICATION AND/OR DISTRIBUTION OF THE APPLE SOFTWARE, HOWEVER CAUSED 
 AND WHETHER UNDER THEORY OF CONTRACT, TORT (INCLUDING NEGLIGENCE), 
 STRICT LIABILITY OR OTHERWISE, EVEN IF APPLE HAS BEEN ADVISED OF THE 
 POSSIBILITY OF SUCH DAMAGE. 
  
 Copyright (C) 2011 Apple Inc. All Rights Reserved. 
  
 */

#include "cli.h"

#import "MailWindowController.h"

@interface MailWindowController ()
- (void) status:(eErrorCode)ec;
@end

MailWindowController *gMain;

CClan *MyCLI::GetClan()
{
	return CClan::Instance();
}

void MyCLI::logger (const char *message, typelog kind)
{
	switch (kind)
	{
		case kLOG:
			[wind Logger:[NSString stringWithUTF8String:message]];
		break;
		case kERR:
			[wind Logger:[NSString stringWithUTF8String:message] withColor:[NSColor redColor]];
		break;
		case kCMD:
			[wind Logger:[NSString stringWithFormat:@"> %s", message] withColor:[NSColor greenColor]];
		break;
		case kSCRIPT:
			[wind Logger:[NSString stringWithFormat:@">> %s", message] withColor:[NSColor greenColor]];
		break;
	}
	
}

void MyCLI::stopActivity (eErrorCode ec)
{
	[wind status:ec];
}

@implementation NSTextViewCommand

- (NSArray *)completionsForPartialWordRange:(NSRange)charRange indexOfSelectedItem:(NSInteger *)index
{
	
	NSAttributedString * attString = [self attributedSubstringFromRange:charRange];
	NSString * str = [attString string];

	const char **cmds = [gMain GetCLI]->getcommands([str UTF8String]);
	
	NSMutableArray *arr = [NSMutableArray arrayWithCapacity:100];
	
	for (const char **p=cmds; *p!= NULL; p++)
		[arr addObject:[NSString stringWithUTF8String:*p]];
		
	*index= 0;
	return arr;
}

@end

@implementation MailWindowController

-(MyCLI*) GetCLI
{
	return mCLI;
}

NSString *MPDataRootDirectory()
{
	static NSString *path = nil;
	if (!path)
	{
		NSArray *paths =
		NSSearchPathForDirectoriesInDomains(NSApplicationSupportDirectory,
											NSUserDomainMask, YES);
		NSCAssert(paths.count > 0,
				  @"Cannot find directory for NSApplicationSupportDirectory.");
		NSDictionary *infoDictionary = [NSBundle mainBundle].infoDictionary;
		path = [NSString pathWithComponents:@[paths[0],
											  infoDictionary[@"CFBundleName"]]];
	}
	return path;
}

NSString *MPDataDirectory(NSString *relativePath)
{
	if (!relativePath)
		return MPDataRootDirectory();
	return [NSString pathWithComponents:@[MPDataRootDirectory(), relativePath]];
}

NSString *MPPathToDataFile(NSString *name, NSString *dirPath)
{
	return [NSString pathWithComponents:@[MPDataDirectory(dirPath),
										  name]];
}


- (void)copyFiles
{
	NSFileManager *manager = [NSFileManager defaultManager];
	NSString *root = MPDataDirectory(nil);
	if (![manager fileExistsAtPath:root])
	{
		[manager createDirectoryAtPath:root
		   withIntermediateDirectories:YES attributes:nil error:NULL];
	}
	
	NSBundle *bundle = [NSBundle mainBundle];
	for (NSString *key in @[@"scripts"])
	{
		NSURL *dirSource = [bundle URLForResource:key withExtension:@""];
		NSURL *dirTarget = [NSURL fileURLWithPath:MPDataDirectory(key)];
		
		// If the directory doesn't exist, just copy the whole thing.
		if (![manager fileExistsAtPath:dirTarget.path])
		{
			[manager copyItemAtURL:dirSource toURL:dirTarget error:NULL];
			continue;
		}
		
		// Check for existence of each file and copy if it's not there.
		NSArray *contents = [manager contentsOfDirectoryAtURL:dirSource
								   includingPropertiesForKeys:nil options:0
														error:NULL];
		for (NSURL *fileSource in contents)
		{
			NSString *name = fileSource.lastPathComponent;
			NSURL *fileTarget = [dirTarget URLByAppendingPathComponent:name];
			if (![manager fileExistsAtPath:fileTarget.path])
				[manager copyItemAtURL:fileSource toURL:fileTarget error:NULL];
		}
	}
}


// -------------------------------------------------------------------------------
//	awakeFromNib:
// -------------------------------------------------------------------------------
- (void)awakeFromNib
{
	[verticalSplitView setDelegate:self];	// we want a chance to affect the vertical split view coverage
	
	gMain = self;
	
	char *path = getcwd(NULL, 0);
	NSLog(@"Cur path : %s", path);
	mCLI = new MyCLI(self);

	mCmdList = [[NSMutableArray arrayWithCapacity:10] retain];
	mCurrentCmd = -1;
	
	commandView.delegate = self;
	[commandView setAutomaticQuoteSubstitutionEnabled:NO];
	[commandView setAutomaticDashSubstitutionEnabled:NO];
	[commandView setAutomaticSpellingCorrectionEnabled:NO];
	[commandView setAutomaticTextReplacementEnabled:NO];
	[commandView setAutomaticLinkDetectionEnabled:NO];
	[commandView setFont:[NSFont fontWithName:@"Monaco" size:11]];
	
	[NSThread detachNewThreadSelector:@selector(idletask) toTarget:self withObject:nil];

	[self copyFiles];
	
	if (strcmp(path, "/")==0) {
		[self execute:[NSString stringWithFormat:@"cd \"%@\"", MPDataDirectory(@"scripts") ]];
	}

	[self execute:@"cmd"];

}

// -------------------------------------------------------------------------------
//	splitView:effectiveRect:effectiveRect:forDrawnRect:ofDividerAtIndex
// -------------------------------------------------------------------------------
- (NSRect)splitView:(NSSplitView *)splitView effectiveRect:(NSRect)proposedEffectiveRect forDrawnRect:(NSRect)drawnRect ofDividerAtIndex:(NSInteger)dividerIndex
{
	NSRect effectiveRect = drawnRect;
	
	if (splitView == verticalSplitView)
	{
		// don't steal as much from the scroll bar as NSSplitView normally would
		effectiveRect.origin.x -= 2.0;
		effectiveRect.size.width += 6.0;
		
	}
	
	return effectiveRect;
}

// -------------------------------------------------------------------------------
//	splitView:additionalEffectiveRectOfDividerAtIndex:dividerIndex:
// -------------------------------------------------------------------------------
- (NSRect)splitView:(NSSplitView *)splitView additionalEffectiveRectOfDividerAtIndex:(NSInteger)dividerIndex
{
	// we have a divider handle next to one of the split views in the window
	if (splitView == verticalSplitView)
		return [dividerHandleView convertRect:[dividerHandleView bounds] toView:splitView];
	else
		return NSZeroRect;
}

// -------------------------------------------------------------------------------
//	constrainMinCoordinate:proposedCoordinate:index
// -------------------------------------------------------------------------------
- (CGFloat)splitView:(NSSplitView *)splitView constrainMinCoordinate:(CGFloat)proposedCoordinate ofSubviewAt:(NSInteger)index
{
	CGFloat constrainedCoordinate = proposedCoordinate;
	if (splitView == verticalSplitView)
	{
		// the primary vertical split view is asking for a constrained size
		constrainedCoordinate = proposedCoordinate + 120.0;
	}
	else if (splitView == horizontalSplitView)
	{
		// the horizontal split view between mailboxes and activity view
		constrainedCoordinate = proposedCoordinate + 200.0;
	}

	return constrainedCoordinate;
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
		[self Logger:[NSString stringWithUTF8String: CloudBuilder::errorString(ec)] withColor:[NSColor redColor]];
	else
		[self Logger:[NSString stringWithFormat:@"Done. (in %lu ms.)", mCLI->millisecondsElapsedSinceLastExecute()] withColor:[NSColor greenColor]];
}

- (void) setReady:(bool) state
{
	mReady = state;
	[commandView setEditable: mReady];
	if (state)
		[progress stopAnimation:nil];
	else
		[progress startAnimation:nil];
}

- (void) Logger:(NSString *)message withColor:(NSColor *)color
{
	[consoleView setEditable: YES];
	unsigned textLength = [[consoleView string] length];
	[consoleView setSelectedRange:NSMakeRange(textLength, 0)];
	[consoleView insertText:message];
	[consoleView insertText:@"\n"];
	[consoleView setTextColor:color range:NSMakeRange(textLength, message.length)];
	[consoleView setEditable: NO];
}


- (void) Logger:(NSString *)message
{
	[self Logger:message withColor:[NSColor whiteColor]];
}

- (void) AddCmd:(NSString *)cmd
{
	mCurrentCmd = -1;
	[mCmdList insertObject:[cmd retain]
	 atIndex:0];
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

- (void) execute:(NSString*)command
{
	[self AddCmd: command];
	[self Logger:[NSString stringWithFormat:@"> %@", command] withColor:[NSColor greenColor]];
	
	[self setReady: NO];
	
	eErrorCode ec = mCLI->execute([command UTF8String]);
	
	if (ec!=enNoErr)
	{
		if ((int)ec!= -1)
			[self Logger:[NSString stringWithUTF8String:errorString(ec)] withColor:[NSColor redColor]];
		[self setReady: YES];
	}
	
}

- (BOOL)textView:(NSTextView *)textView doCommandBySelector:(SEL)commandSelector {
	BOOL retval = NO;
	// When return is entered, record and color the newly committed text
	
	if (textView==commandView && @selector(insertNewline:) == commandSelector)
	{
		NSString *command = [NSString stringWithString:[textView string]];
		unsigned textLength = [command length];
		[textView setSelectedRange:NSMakeRange(0, textLength)];
		[textView insertText:@""];
		
		command = [command stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]];
		
		[self execute : command];
		
		retval = YES;
	}

	if (textView==commandView && @selector(moveUp:) == commandSelector)
	{
		NSString *cmd = [self PreviousCmd];
		if (cmd)
		{
			NSString *command = [NSString stringWithString:[textView string]];
			unsigned textLength = [command length];
			[textView setSelectedRange:NSMakeRange(0, textLength)];
			[textView insertText:cmd];
		}
		retval = YES;
	}
	
	if (textView==commandView && @selector(moveDown:) == commandSelector)
	{
		NSString *cmd = [self NextCmd];
		if (cmd)
		{
			NSString *command = [NSString stringWithString:[textView string]];
			unsigned textLength = [command length];
			[textView setSelectedRange:NSMakeRange(0, textLength)];
			[textView insertText:cmd];
		}
		retval = YES;
	}

	if (textView==commandView && @selector(insertTab:) == commandSelector)
	{
		[textView complete:self];
		retval = YES;
	}

	return retval;
}

@end
