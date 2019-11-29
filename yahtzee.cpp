#include <random>
#include <cstdio>

int main()
{
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 eng(rd()); // seed the generator
	std::uniform_int_distribution<> distr(1, 6); // define the range
	int count = 1; //Start with one roll, since first roll happens outside of loop
	int yahtzees = 0;
	int dyahtzees = 0;
	int totalrolls = INT_MAX; //should be 2,147,483,647.  Maybe try a smaller number if you want faster results, i.e.:
	//int totalrolls = 129600000;         //129,600,000

	int **rolls = new int*[2];
	rolls[0] = new int[5];
	rolls[1] = new int[5];
	for (int i = 0; i < 5; i++) { //Throw our first roll
		rolls[0][i] = distr(eng);
	}

	while (count < totalrolls) { //Start loooooop
		count++;
		for (int i = 0; i < 5; i++) { //Roll again
			rolls[1][i] = distr(eng);
		}

		if (rolls[0][0] == rolls[0][1] && rolls[0][1] == rolls[0][2] && rolls[0][2] == rolls[0][3] && rolls[0][3] == rolls[0][4]) { //Is first roll a yahtzee?
			//printf("Yahtzee roll# %d\n", count); //A lot of printing happens here, which slows code down, so commented out.
			yahtzees++;
			if (rolls[1][0] == rolls[1][1] && rolls[1][1] == rolls[1][2] && rolls[1][2] == rolls[1][3] && rolls[1][3] == rolls[1][4]) { //Is second roll a yahtzee?
				printf("DOUBLE YAHTZEE! Rolls %d and %d\n", count - 1, count); //Much less frequent, worth printing so we aren't just staring at a blank screen.
				dyahtzees++;
			}
		}

		for (int i = 0; i < 5; i++) { //Move "second" roll to "first" roll slot before restarting loop
			rolls[0][i] = rolls[1][i];
		}
	}

	printf("After %d rolls there were %d (%f) Yahtzees and %d (%f) Double Yahtzees\n", totalrolls, yahtzees, static_cast<double>(yahtzees) / static_cast<double>(totalrolls) * 100, dyahtzees, static_cast<double>(dyahtzees) / static_cast<double>(totalrolls) * 100);
	printf("Press enter key to exit...");
	std::getchar();
	return 0;
}
