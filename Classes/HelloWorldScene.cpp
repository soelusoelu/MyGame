/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "AudioEngine.h"

USING_NS_CC;


Scene* HelloWorld::createScene() {
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename) {
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init() {
    //////////////////////////////
    // 1. super init first
    if (!Scene::init()) {
        return false;
    }

    experimental::AudioEngine::play2d("bgm.mp3", true);

    Sprite* mario = Sprite::create("mario_run.png");
    mario->setScale(0.2f);
    mario->setPosition(Vec2(100.f, 100.f));
    Sprite* kuppa = Sprite::create("kuppa.png");
    kuppa->setScale(0.4f);
    kuppa->setPosition(Vec2(1000.f, 150.f));

    this->addChild(mario);
    this->addChild(kuppa);

    /***************Main**********************/
    MoveBy* initToJump = MoveBy::create(3.f, Vec2(650.f, 0.f));
    JumpBy* jumpToKuppaHead = JumpBy::create(1.f, Vec2(150.f, 200.f), 100.f, 1);
    MoveTo* kuppaHeadToUp = MoveTo::create(0.1f, Vec2(900.f, 400.f));
    MoveTo* kuppaHeadToBottom = MoveTo::create(0.1f, Vec2(900.f, 300.f));
    Sequence* upBottom = Sequence::create(kuppaHeadToUp, kuppaHeadToBottom, nullptr);
    Repeat* stepOn = Repeat::create(upBottom, 10);
    Sequence* seq1 = Sequence::create(initToJump, jumpToKuppaHead, stepOn, nullptr);
    mario->runAction(seq1);

    DelayTime* delay = DelayTime::create(6.5f);
    TintTo* deadKuppa = TintTo::create(1.f, Color3B(255, 0, 0));
    RotateBy* kuppaDown = RotateBy::create(1.f, 90.f);
    FadeOut* fadeKuppa = FadeOut::create(1.f);
    Sequence* seq2 = Sequence::create(delay, deadKuppa, kuppaDown, fadeKuppa, nullptr);
    kuppa->runAction(seq2);
    /***************Main**********************/

    this->scheduleUpdate();

    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender) {
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}

void HelloWorld::update(float delta) {
}

