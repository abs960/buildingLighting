#pragma once

#include "InteriorObject.h"
#include "../../lights/Light.h"

class LightSource : public InteriorObject {
public:
	virtual void updateShader(Shader* shader);

	void setLight(Light* light);
	Light* getLight();

protected:
	Light* light;
};


