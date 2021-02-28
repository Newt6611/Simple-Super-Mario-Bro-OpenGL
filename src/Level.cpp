#include "Level.h"

Level::Level(Game& game, b2World& physicsWorld)
{
	// m => mushroom
	// p => pipe
	// b => brick
	// c => coin brick
	// s => stair brick
	int height = 9;
	int width = 200;
	map = 
		"########################################################################################################################################################################################################"
		"#####################c#############################################################################################c#######################bbcbc########################################################"
		"#################################################################################bbbbbbbbbb####bbbc################################bbb#################################################################s"
		"############################################################################m#########################################################################################################################ss"
		"##############c####bcbcb##################################################bbcbb########################bb#######c##c##c#######b##############bb########s##s##########ss##s#########bbcb##############sss"
		"##################################################################################################b###################################################ss##ss########sss##ss#########################ssss"
		"#####################################################################################################################################################sss##sss######ssss##sss#######################sssss"
		"######################m#######p####m####p######m#####p#####m###p########m######################m###########################################m########ssss##ssss####sssss##ssss###p####m#####p######ssssss";
	
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			char type = map[x + y * width];
			switch (type)
			{
			case 'b':
				objects.push_back(new Brick(game, physicsWorld, { x * 100, (height - y) * 100 + 100 }, { 100,100 }));
				break;
			case 'c':
				objects.push_back(new CoinBrick(game, physicsWorld, { x * 100, (height - y) * 100 + 100 }, { 100,100 }));
				break;
			case 'p':
				objects.push_back(new Pipe(game, physicsWorld, { x * 100, (height - y) * 100 + 50 }, { 200, 200 }));
				break;
			case 'm':
				objects.push_back(new Mushroom(game, physicsWorld, { x * 100, (height - y) * 100 + 100 }, { 100,100 }));
				break;
			case 's':
				objects.push_back(new StairBrick(game, physicsWorld, { x * 100, (height - y) * 100 }, { 100,100 }));
				break;
			default:
				break;
			}
		}
	}
}

Level::~Level()
{
	for (int i = 0; i < objects.size(); i++)
	{
		delete objects[i];
	}
}

void Level::OnUpdate(float ts)
{

}

void Level::OnRender()
{

}

void Level::OnTriggerEnter(IObject* collider)
{

}