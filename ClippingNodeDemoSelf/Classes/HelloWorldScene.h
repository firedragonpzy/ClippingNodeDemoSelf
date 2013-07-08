#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

using namespace cocos2d;

class HelloWorld : public cocos2d::CCLayer
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);

    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(HelloWorld);
    
private:
    CCSprite *role;
    CCLayer *m_pGameLayer;
    CCSize winSize;
    CCNode *stencil;
    
    void __setUpClipper();
    CCClippingNode* __getClipper();
    CCNode* __getMaskStencil();
    CCDrawNode* __getMaskShape();
    CCNode* __getMaskedContent();
    CCNode* __getMaskedContentOther();
    void __updateStencilPos(float dt);
    
    void __initRole();
    
    void __initGameLayer();

};

#endif // __HELLOWORLD_SCENE_H__
