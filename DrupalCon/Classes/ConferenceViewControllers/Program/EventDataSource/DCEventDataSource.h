/**********************************************************************************
 *
 *  The MIT License (MIT)
 *  Copyright (c) 2015 Lemberg Solutions Limited
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to
 *  deal in the Software without restriction, including without limitation the
 *  rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 *  sell copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *   The above copyright notice and this permission notice shall be included in
 *   all  copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM,  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 *  IN THE SOFTWARE.
 *
 *
 *****************************************************************************/

#import <Foundation/Foundation.h>
#import "NSArray+DC.h"
#import "DCEventStrategy.h"
#import "DCTimeRange+DC.h"
#import "DCTime.h"
#import "NSDate+DC.h"
#import "DCEvent+DC.h"

@import UIKit;

extern NSString* kDCTimeslotKEY;
extern NSString* kDCTimeslotEventKEY;

@class DCEventStrategy, DCEvent, DCTimeRange, DCEventDataSource;

@protocol DCDayEventSourceDelegate<NSObject>

- (void)dataSourceStartUpdateEvents:(DCEventDataSource*)dataSource;
- (void)dataSourceEndUpdateEvents:(DCEventDataSource*)dataSource;

@end

@protocol DCDayEventSourceProtocol<NSObject>

- (void)reloadEvents;
- (DCEvent*)eventForIndexPath:(NSIndexPath*)indexPath;
- (DCTimeRange*)timeRangeForSection:(NSInteger)section;
- (NSIndexPath*)actualEventIndexPath;
- (NSString*)titleForSectionAtIdexPath:(NSInteger)section;

@end


/**
 *  @class DCEventDataSource is the base data source for all days events,
 */

@interface DCEventDataSource
    : NSObject<UITableViewDataSource, DCDayEventSourceProtocol>

@property(copy, nonatomic) UITableViewCell* (^prepareBlockForTableView)
    (UITableView* tableView, NSIndexPath* indexPath);

@property(strong, nonatomic) DCEventStrategy* eventStrategy;
@property(strong, nonatomic) NSDate* selectedDay;
@property(strong, nonatomic) NSArray* eventsByTimeRange;

@property(weak, nonatomic) UITableView* tableView;

@property(weak, nonatomic) id<DCDayEventSourceDelegate> delegate;

- (instancetype)initWithTableView:(UITableView*)tableView
                    eventStrategy:(DCEventStrategy*)eventStrategy
                             date:(NSDate*)date;
- (void)updateActualEventIndexPathForTimeRange:(NSArray*)array;
- (NSArray*)eventsSortedByTimeRange:(NSArray*)events
                withUniqueTimeRange:(NSArray*)unqueTimeRange;
// Callbacks for update delegate methods
- (void)dataSourceStartUpdateEvents;
- (void)dataSourceEndUpdateEvents;
@end