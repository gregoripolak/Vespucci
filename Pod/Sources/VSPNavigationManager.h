//
//  VSPNavigationManager.h
//  Wondermall
//
//  Created by Sash Zats on 3/30/15.
//  Copyright (c) 2015 Wondermall Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "VSPNavigationNode.h"


extern NSString *const VSPNavigationManagerWillNavigateNotification;
extern NSString *const VSPNavigationManagerDidFinishNavigationNotification;
extern NSString *const VSPNavigationManagerDidFailNavigationNotification;
extern NSString *const VSPNavigationManagerNotificationDestinationNodeKey;
extern NSString *const VSPNavigationManagerNotificationSourceNodeKey;

extern NSString *const VSPHostingRuleAnyNodeId;

@class JLRoutes;
@class RACSignal;
@interface VSPNavigationManager : NSObject

@property (nonatomic, readonly) JLRoutes *router;

@property (nonatomic, readonly) VSPNavigationNode *root;

- (instancetype)initWithURLScheme:(NSString *)URLScheme NS_DESIGNATED_INITIALIZER;

- (BOOL)handleURL:(NSURL *)URL;

- (RACSignal *)navigateToURL:(NSURL *)URL;

- (RACSignal *)navigateWithNewNavigationTree:(VSPNavigationNode *)tree;

@end


@interface VSPNavigationManager (Compatibility)

// TODO: Refactor me into a regular setter of root property
- (void)setNavigationRoot:(VSPNavigationNode *)navigationRoot;

@end


typedef RACSignal *(^VSPNavigationNodeViewControllerMountHandler)(VSPNavigationNode *parent, VSPNavigationNode *child, BOOL animated);

typedef RACSignal *(^VSPNavigationNodeViewControllerDismountHandler)(VSPNavigationNode *parent, VSPNavigationNode *child, BOOL animated);

typedef UIViewController *(^VSPViewControllerFactory)(VSPNavigationNode *node);


@interface VSPNavigationManager (NodeHosting)

- (void)registerNavigationForRoute:(NSString *)route handler:(VSPNavigationNode *(^)(NSDictionary *parameters))handler;

- (void)addRuleForHostNodeId:(NSString *)hostNodeId childNodeId:(NSString *)childNodeId mountBlock:(VSPNavigationNodeViewControllerMountHandler)mountBlock unmounBlock:(VSPNavigationNodeViewControllerDismountHandler)dismountBlock;

/*
 * Allows you to register view controller factory called upon node with specified
 * id is about to be inserted into navigation stack.
 */
- (void)registerFactoryForNodeId:(NSString *)nodeId factory:(VSPViewControllerFactory)factory;

@end