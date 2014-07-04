#ifndef __SHADERLAYER_H__
#define __SHADERLAYER_H__

#include "cocos2d.h"
#include <string>
USING_NS_CC;

class ShaderLayer : public cocos2d::Layer
{
	GLProgram* p;
public:
	ShaderLayer();
	~ShaderLayer();

    virtual bool init(
		std::string pixelShaderFile,
		std::string vertexShaderFile = "generic.vsh");  
	static ShaderLayer* create(
		std::string pixelShaderFile,
		std::string vertexShaderFile = "generic.vsh");

	RenderTexture* renderTexture;
	Sprite* rendTexSprite;

	virtual void visit(
		Renderer *renderer,
		const Mat4& parentTransform,
		bool parentTransformUpdated) override;
};

#endif
