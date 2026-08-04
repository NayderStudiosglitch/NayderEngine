#include "Zombie.h"

int main()
{
    Zombie zombie("Walker_01");

    zombie.SetPosition(0.0f, 0.0f, 0.0f);

    zombie.Update(0.016f);

    zombie.CanSeePlayer(20.0f, 0.0f, 0.0f);

    zombie.Update(0.016f);

    zombie.CanSeePlayer(80.0f, 0.0f, 0.0f);

    zombie.Update(0.016f);

    return 0;
}
