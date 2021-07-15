//
//  main.m
//  callback
//
//  Created by 赵晓晨 on 2021/7/14.
//

#import <Foundation/Foundation.h>

@interface Responser : NSObject
-(void) my_callback:(NSString*) sGreeting;
@end

@implementation Responser
-(void) my_callback:(NSString*) sGreeting{
    printf("Responser.my_callback called with greeting: '%s'. \n", [sGreeting cString]);
}
@end

void c_caller(void(* callback)(const char*)){
    printf("c_caller invoking callback\n");
    callback("Hello C");
}

void my_callback(const char* sz){
    Responser* res = [[Responser alloc] init];
    SEL sel = NSSelectorFromString(@"my_callback:");
    [res performSelector:sel withObject:[NSString stringWithUTF8String:sz]];
}

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        // insert code here...
        NSLog(@"Hello, World!");
        
        c_caller(my_callback);
        
    }
    return 0;
}
