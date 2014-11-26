#include "ShaderLayer.h"
using namespace std;

ShaderLayer::ShaderLayer()
{
	p = nullptr;
}

ShaderLayer::~ShaderLayer()
{
}

ShaderLayer* ShaderLayer::create(string pixelShaderFile, string vertexShaderFile)
{
	ShaderLayer *pRet = new ShaderLayer();
	if (pRet && pRet->init(pixelShaderFile, vertexShaderFile))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

bool ShaderLayer::init(string pixelShaderFile, string vertexShaderFile)
{
    if ( !Layer::init() )
    {
        return false;
    }
	
	p = GLProgram::createWithFilenames(vertexShaderFile, pixelShaderFile);

	Size visibleSize = Director::getInstance()->getVisibleSize();

	renderTexture = RenderTexture::create(visibleSize.width, visibleSize.height);
	addChild(renderTexture);
	
	rendTexSprite = Sprite::create();
	rendTexSprite->setTexture(renderTexture->getSprite()->getTexture());
	rendTexSprite->setTextureRect(Rect(0, 0, rendTexSprite->getTexture()->getContentSize().width, rendTexSprite->getTexture()->getContentSize().height));
	rendTexSprite->setPosition(Point::ZERO);
	rendTexSprite->setAnchorPoint(Point::ZERO);
	rendTexSprite->setFlippedY(true);
	addChild(rendTexSprite);

	rendTexSprite->setGLProgram(p);
	
    return true;
}

void ShaderLayer::visit(
	Renderer *renderer,
	const Mat4& parentTransform,
	uint32_t parentFlags)
{
	renderTexture->beginWithClear(0, 0, 0, 0);
	for (auto child : getChildren())
	{
		if (child != renderTexture && child != rendTexSprite)
			child->visit(renderer, parentTransform, parentFlags);
	}
	renderTexture->end();

	rendTexSprite->visit(renderer, parentTransform, parentFlags);
}
