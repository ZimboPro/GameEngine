#include <graphics/Window.hpp>
#include <graphics/Shader.hpp>
#include <graphics/buffers/Buffer.hpp>
#include <graphics/buffers/IndexBuffer.hpp>
#include <graphics/buffers/VertexArray.hpp>

#include <graphics/Renderer2d.hpp>
#include <graphics/Batch2dRenderer.hpp>

#include <graphics/Sprite.hpp>

#include <graphics/layers/TileLayer.hpp>
#include <graphics/layers/Group.hpp>

#include <utils/Times.hpp>

#include <graphics/Texture.hpp>

#include <time.h>
#include <iostream>

#define BATCH_RENDERER 1
#define Test_50K_sprites 0
#if 1
int main() {

    GameEngine::graphics::Window window("GameEngine!", 960, 540);
    
	GameEngine::graphics::Shader* s = new GameEngine::graphics::Shader("../src/shader/basicVert.glsl", "../src/shader/basicFrag.glsl");
	GameEngine::graphics::Shader* s2 = new GameEngine::graphics::Shader("../src/shader/basicVert.glsl", "../src/shader/basicFrag.glsl");
	GameEngine::graphics::Shader& shader = *s;
	GameEngine::graphics::Shader& shader2 = *s2;
	shader.enable();
	shader2.enable();
	GameEngine::graphics::TileLayer layer(&shader);
#if Test_50K_sprites
	for (float y = -9.0f; y < 9.0f; y += 0.1)
	{
		for (float x = -16.0f; x < 16.0f; x += 0.1)
		{
			layer.add(new GameEngine::graphics::Sprite(x, y, 0.09f, 0.09f, glm::vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));
		}
	}
#else 
	GameEngine::graphics::Group* group = new GameEngine::graphics::Group(glm::translate(glm::mat4(1.0f), glm::vec3(-15.0f, 5.0f, 0.0f)));
	group->add(new GameEngine::graphics::Sprite(0, 0, 6, 3, 0xffffffff));
	GameEngine::graphics::Group* button = new GameEngine::graphics::Group(glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, 0.0f)));
	group->add(button);
	button->add(new GameEngine::graphics::Sprite(0, 0, 5.0f, 2.0f, 0xff00ffff));
	button->add(new GameEngine::graphics::Sprite(0.5f, 0.5f, 3.0f, 1.0f, 0x334d4dff));
	layer.add(group);
#endif
	GameEngine::graphics::TileLayer layer2(&shader2);
	GameEngine::graphics::Texture texture("wall.jpg");
	layer2.add(new GameEngine::graphics::Sprite(-2, -2, 4, 4, &texture));

	GameEngine::Timer time;
	float timer = 0;
	unsigned int frames = 0;
	double previousTime = glfwGetTime();
	int frameCount = 0;

    while (!window.closed()) {
        window.clear();
		double x, y;
		window.CursorPostion(x, y);
		shader.enable();
		//shader.setUniform2f("light_pos", glm::vec2((float)(x * 32.0f / 960.0f - 16.0f), (float)(9.0f - y * 18.0f / 540.0f)));

		layer.render();

		window.update();
		frames++;
		if (time.elapsed() - timer > 1.0f)
		{
			timer += 1.0f;
			printf("%d fps\n", frames);
			frames = 0;
		}
    }
    return 0;
}

#endif