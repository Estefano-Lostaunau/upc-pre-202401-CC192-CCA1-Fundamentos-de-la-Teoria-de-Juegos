#include "MainGame.h"
#include "Sprite.h"

MainGame::MainGame()
{
	window = NULL;
	width = 800;
	height = 600;
	gameState = GameState::PLAY;

}

void MainGame::init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	window = new Window();
	window->create("Motor", width, height, 0);

	initShaders();

}

MainGame::~MainGame()
{


}

void MainGame::run()
{
	init();
	sprite.init(-1,-1,1,1,"images/donaldtrump.png");
	sprite2.init(-1, 1, 1, -1,"images/donaldtrump.png");

	sprite3.init(1, 1, -1, -1,"images/donaldtrump.png");


	sprite4.init(1, -1, -1, 1,"images/donaldtrump.png");
	update();
}

void MainGame::draw()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Cambia el color de fondo a blanco
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    program.use();
    GLuint timeLocation = program.getUniformLocation("time");
    glUniform1f(timeLocation, time);
    time += 0.02;
    sprite.draw();
    int ge = SDL_GetTicks();
    cout << "Tiempo transcurrido(milisegundos):" << ge << endl;

    if (ge > 6000)
    {
        sprite2.draw();
    }
    if (ge > 8000)
    {
        sprite3.draw();
    }
    if (ge > 10000)
    {
        sprite4.draw();
    }

    program.unuse();
    window->swapWindow();
}

void MainGame::update()
{
	while (gameState != GameState::EXIT) {
		draw();
		processInput();
	}
}

void MainGame::processInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)){
		switch (event.type) {
		case SDL_QUIT:
			gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			cout << " Posicion en X " << event.motion.x 
			<< " Posicion en Y " << event.motion.y << endl;
			break;
		}
	}
}

void MainGame::initShaders()
{
	program.compileShaders("Shaders/colorShaderVert.txt", "Shaders/colorShaderFrag.txt");
	program.addAtribute("vertexPoistion");
	program.addAtribute("vertexColor");
	program.addAtribute("vertexUV");
	program.linkShader();

}
