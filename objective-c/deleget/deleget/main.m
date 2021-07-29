//
//  main.m
//  deleget
//
//  Created by 赵晓晨 on 2021/7/29.
//

#import <Foundation/Foundation.h>

@protocol AClassDelegate <NSObject>         // 创建协议，定义协议名和父类

@required                                   // @requierd为必须实现的方法
-(int)doSomethingWithNumber1:(int)num1 andNumber2:(int)num2;
@end

@interface AClass : NSObject

@property (nonatomic,weak) id<AClassDelegate> delegate;     // delegate属性
-(void)logAnswerWithNumber1:(int)num1 andNumber2:(int)num2;
@end


@implementation AClass
-(void)logAnswerWithNumber1:(int)num1 andNumber2:(int)num2{
    int answer = [self.delegate doSomethingWithNumber1:num1 andNumber2:num2];
    NSLog(@"%d",answer);
}
@end


@interface BClass : NSObject <AClassDelegate>   //遵守协议

@end

@implementation BClass

-(int)doSomethingWithNumber1:(int)num1 andNumber2:(int)num2{
    return num1+num2;
}

@end


int main(int argc, const char * argv[]) {
    @autoreleasepool {
        // insert code here...
        AClass *a = [AClass new];
        BClass *b = [BClass new];
        
        a.delegate = b;         // b 成为 a 的代理
        [a logAnswerWithNumber1:3 andNumber2:5]; //调用 a 的方法

    }
    return 0;
}
