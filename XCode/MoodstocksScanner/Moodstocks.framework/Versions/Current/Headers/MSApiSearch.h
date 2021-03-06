//
//  Copyright (c) 2014 Moodstocks. All rights reserved.
//

#import <Foundation/Foundation.h>

@class MSScanner;
@class MSImage;
@class MSResult;

/** The `MSApiSearch` class represents a server-side image matching operation. Unless you
 * know what you are doing, you should use [MSScanner apiSearchInBackgroundWithQuery:block:] instead.
 */
@interface MSApiSearch : NSOperation

/** The operation error.
 *
 * This must be checked as soon as the result block is called. If the operation succeeded
 * the error is `nil`. If the operation has been cancelled the error code is `MSErrorAbort`.
 * Otherwise an appropriate error code is set.
 *
 * @see setCompletedBlock:
 */
@property (nonatomic, readonly, strong) NSError *error;

/** The operation result.
 *
 * This provides the scan result, or `nil` if no match found or error.
 *
 * @see setCompletedBlock:
 */
@property (nonatomic, readonly, strong) MSResult *result;

///---------------------------------------------------------------------------------------
/// @name Initialization
///---------------------------------------------------------------------------------------

/** Initializes a server-side search operation.
 *
 * The caller is responsible to provide a scanner successfully opened.
 *
 * @param scanner the scanner to be used for server-side search.
 * @param query the query image.
 * @return the operation instance.
 * @see [MSScanner openWithPath:key:secret:error:]
 */
- (id)initWithScanner:(MSScanner *)scanner
                query:(MSImage *)query;

///---------------------------------------------------------------------------------------
/// @name Operation life-cycle
///---------------------------------------------------------------------------------------

/** Register to the operation progress.
 *
 * @param progressBlock the block that triggers the progress events.
 */
- (void)setProgressBlock:(void (^)(NSInteger percentDone))progressBlock;

/** Register to the operation cancelling.
 *
 * In most cases, the operation is cancelled when the caller calls `NSOperation` `cancelAllOperations`
 * on the operation queue that holds this operation.
 *
 * @param cancelBlock the block that is called as soon as the operation is cancelled.
 */
- (void)setCancelBlock:(void (^)(id operation))cancelBlock;

/** Register to the operation completion.
 *
 * @param completedBlock the block that is called when the operation is completed.
 * @see error
 */
- (void)setCompletedBlock:(void (^)(id operation, NSError *error))completedBlock;

@end
