//
//  ViewController.m
//  JsonVsOCDemo
//
//  Created by bill on 16/9/20.
//  Copyright © 2016年 bill. All rights reserved.
//

#import "ViewController.h"
#import <JavaScriptCore/JavaScriptCore.h>
@interface ViewController ()<UIWebViewDelegate>
@property (weak, nonatomic) IBOutlet UIWebView *webV;

@end

@implementation ViewController

/**
 * 第一种：JS给OC传值。
 
 1. 技术方案：使用JavaScriptCore.framework框架
 2. 使用场景： 网页中代码中的某个方法，比如点击事件方法，将该方法的参数传值给OC，供OC使用。
 比如：携程APP中一个热门景点的网页中，有很多个热门景点，点击某个景点的图片或名称，可以跳转到原生中的该景点详情页控制器。

 */

- (void)viewDidLoad {
    [super viewDidLoad];
    
    
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}

#pragma mark - webview delegate
- (void)webViewDidStartLoad:(UIWebView *)webView {
    
}

- (void)webViewDidFinishLoad:(UIWebView *)webView {\
    /**
     * 第一种：JS给OC传值。
     *  OC里要实现的代码：
     拖入JavaScriptCore.framework静态库，遵守UIWebViewDelegate代理协议。
     在-webViewDidFinishLoad:方法里编写如下代码：
     */
    JSContext *context = [webView valueForKeyPath:@"documentView.webView.mainFrame.javaScriptContext"];
    
    ;
    WeakSelf;
    context[@"passValue"] = ^{   // 其中 passValue 是JS的函数名，得到的 arg数组 里面为JS的 passValue 函数的参数，即 JS要传给OC的参数。
        
        NSArray *arg = [JSContext currentArguments];
        
        for (id obj in arg) {
            
            NSLog(@"obj :  %@", obj);
        
        }
        StrongSelf;
        [self doSomething];
        
    };
    
    
    /*
     JS里要实现的代码：
     
     function testClick()
     {
     var str1 = document.getElementById("text1").value;
     var str2 = document.getElementById("text2").value;
     
     passValue(str1,str2);
     }
     在需要给OC传值的函数里（例如：testClick（））直接调用 passValue（）函数，将值传进去即可。
     
     
     */
    
}

- (void)webView:(UIWebView *)webView didFailLoadWithError:(NSError *)error {
    
    
}

- (BOOL)webView:(UIWebView *)webView shouldStartLoadWithRequest:(NSURLRequest *)request navigationType:(UIWebViewNavigationType)navigationType {
    
    
    return YES;
}

#pragma mark - 测试方法
- (void)doSomething {
    NSLog(@"do  something!");
}

@end
