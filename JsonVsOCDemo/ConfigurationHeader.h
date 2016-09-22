//
//  ConfigurationHeader.h
//  JsonVsOCDemo
//
//  Created by bill on 16/9/22.
//  Copyright © 2016年 bill. All rights reserved.
//


#ifndef ConfigurationHeader_h
#define ConfigurationHeader_h

#import "EXTScope.h"
#define WeakSelf @weakify(self)
#define StrongSelf @strongify(self)

#endif 

/*
 http://blog.csdn.net/u012131827/article/details/51097564
 使用Block时何时需要WeakSelf和StrongSelf?

 现在我们用 Objective-C 写代码时已经越来越多地用到了block，相比delegate的回调方式，block更直观易用。相信每个使用过block的人都遇到过block中使用self时需要weakself的情况，以下就是非常典型的一段代码：
 
 __weak __typeof(self)weakSelf = self;
 
 [self.context performBlock:^{
 
 __strong __typeof(weakSelf)strongSelf = weakSelf;
 
 [strongSelf doSomething];
 
 }];
 
 对于小白的我一般越到这种情况就是直接拷贝上面这个模板到需要的代码中去，而不知个中原委。但作为一个合格的程序员，是需要完完全全明白自己写的每一行代码是在做什么的，所以现在就简单说明一下这个 WeakSelf 和 StrongSelf 到底是什么。首先看下面这段代码：
 
 [UIView animateWithDuration:0.2 animations:^{
 
 self.myView.alpha = 1.0;

 }];
 
 在ARC环境下的，每个block在创建时，编译器会对里面用到的所有对象自动增加一个reference count，然后当block执行完毕时，再释放这些reference。针对上面的代码，在animations block执行期间，self（假设这里的self是个view controller）的引用数会被加1，执行完后再次减1。但这种情况下为什么我们一般不会去weakify self呢？因为这个block的生命周期是明确可知的，在这个block执行期间当前的view controller一般是不会被销毁的，所以不存在什么风险。现在我们看下面这个例子：
 
 NSBlockOperation *op = [[[NSBlockOperation alloc] init] autorelease];
 
 [op addExecutionBlock:^ {
 
 [self doSomething];
 
 [self doMoreThing];
 
 }];
 
 在这种情况下，我们并不知道这个execution block什么时候会执行完毕，所以很有可能发生的情况是，我在block还没执行完毕时就想销毁当前对象（比方说用户关闭了当前页面），这时就会因为block还对self有一个reference而没有立即销毁，这会引起很多问题，比方说你写在 - (void)dealloc {} 中的代码并不能马上得到执行。所以为了避免这种情况，我们会在block前加上 __weak __typeof(self)weakSelf = self; 的定义来使block对self获取一个弱引用（也就是refrence count不会加1）。
 
 那block中的StrongSelf又是做什么的呢？还是上面的例子，当你加了WeakSelf后，block中的self随时都会有被释放的可能，所以会出现一种情况，在调用doSomething的时候self还存在，在doMoreThing的时候self就变成nil了，所以为了避免这种情况发生，我们会重新strongify self。一般情况下，我们都建议这么做，这没什么风险，除非你不关心self在执行过程中变成nil，或者你确定它不会变成nil（比方说所以block都在main thread执行）。
 
 好了，简要的说明到此结束，想要详细了解的可以自行google，这类文章很多。前面代码中的WeakSelf、StrongSelf转换看起来很冗长，不利于阅读代码，下面介绍一个超好用的宏定义代码，它是这个开源库的一部分： libextobjc 。把它加入到项目中后，就可以用以下如此简洁的格式来完成转换啦：
 
 #import "EXTScope.h"
 
 @weakify(self)
 
 [self.context performBlock:^{
 
 @strongify(self)
 
 [self doSomething];
 
 }];
 
 自己的理解:
 
 进入Block之前加一遍__weak 让self的引用计数不-1 。这样的话self会随着当前控件的释放而释放。如果不写的话，block块中默认会将里面所有内容的引用计数+1.有可能当前控件释放了，但是self还没有释放。
 
 进入Block之后加一遍__strong 让self的引用计数+1 ，这样的话，self就不会再离开block的时候被释放。
 
 */