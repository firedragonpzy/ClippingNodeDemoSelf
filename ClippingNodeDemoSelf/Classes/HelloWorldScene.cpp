#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback) );
    pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 11);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    CCLabelTTF* pLabel = CCLabelTTF::create("ClippingNode Test : firedragonpzy", "Thonburi", 24);

    // ask director the window size
    CCSize size = CCDirector::sharedDirector()->getWinSize();

    // position the label on the center of the screen
    pLabel->setPosition( ccp(size.width / 2, size.height - 20) );

    // add the label as a child to this layer
    this->addChild(pLabel, 11);
    
    
    winSize = CCDirector::sharedDirector()->getWinSize();
    this->setTouchEnabled(true);
    
    __initRole();
    __initGameLayer();
    __setUpClipper();
    
    schedule(schedule_selector(HelloWorld::__updateStencilPos), 0.05);
    
    return true;
}


void HelloWorld::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    if (role->getPositionY() == role->getContentSize().height/2) {
        role->stopAllActions();
        role->runAction(CCJumpBy::create(1, ccp(0,0), 50, 1));
    }
}


void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}



CCNode* HelloWorld::__getMaskedContent()
{
    CCSprite *content = CCSprite::create("pig_mask.png");
    content->setPosition( ccp(250 + content->getContentSize().width/2,content->getContentSize().height/2) );
     content->runAction(CCMoveBy::create(48, ccp(-480,0)));
    return content;
}


CCNode* HelloWorld::__getMaskedContentOther()
{
    CCSprite *content = CCSprite::create("masked_content_1.png");
    content->setPosition( ccp(250 + winSize.width/2 + content->getContentSize().width/2,content->getContentSize().height/2) );
    content->runAction(CCMoveBy::create(48, ccp(-480,0)));
    return content;
}


CCDrawNode* HelloWorld::__getMaskShape()
{
    CCDrawNode *shape = CCDrawNode::create();
    
    CCPoint vertext4[4];
    vertext4[0] = ccp(10,50);
    vertext4[1] = ccp(210,75);
    vertext4[2] = ccp(210,-25);
    vertext4[3] = ccp(10,0);
    
    ccColor4F green = {0,1,0,1};
    
    shape->drawPolygon(vertext4, 4, green, 0, green);
    return shape;
}


CCNode* HelloWorld::__getMaskStencil()
{
    stencil =  __getMaskShape();
    return stencil;
}


CCClippingNode* HelloWorld::__getClipper()
{
    return CCClippingNode::create(__getMaskStencil());
}


void HelloWorld::__setUpClipper()
{
    CCClippingNode *clipper = __getClipper();
    clipper->setAnchorPoint(ccp(0.5, 0.5));
     clipper->setAlphaThreshold(0.05f);
    clipper->setInverted(true);
    this->addChild(clipper);
    
    CCNode *content = __getMaskedContent();
    clipper->addChild(content);
    
//    content = __getMaskedContentOther();
//    clipper->addChild(content);
    
}


void HelloWorld::__initRole()
{
    role = CCSprite::create("grossini.png");
    role->setPosition(ccp(role->getContentSize().width/2,role->getContentSize().height/2));
    this->addChild(role,10);
}


void HelloWorld::__initGameLayer()
{
    m_pGameLayer = CCLayer::create();
    this->addChild(m_pGameLayer);

    CCSprite* pSprite = CCSprite::create("HelloWorld.png");
    pSprite->setPosition( ccp(winSize.width/2, winSize.height/2) );
    pSprite->setScaleX(4);
    m_pGameLayer->addChild(pSprite, 0);
       
    m_pGameLayer->runAction(CCMoveBy::create(48, ccp(-480,0)));
}



void HelloWorld::__updateStencilPos(float dt)
{
    stencil->setPosition(role->getPosition());
}