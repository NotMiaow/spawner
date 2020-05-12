#include "spawner.h"

int main()
{
    Spawner spawner("relay_bot");
    bool alive = true;
	while(alive)
	{
		std::string command;
		std::getline(std::cin, command);
        if(command == "stop")
        {
            spawner.Stop();
            alive = false;
        }
	}
}