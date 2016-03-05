# genetic.py
# Python file implementing a genetic algorithm for learning an othello
# heuristic.
#
# usage as executable: python genetic.py <prevgen> <nextgen>
# reminder: a generation is every file of weights of the form
# <genname>_<ai#>. So the above command will take the generation
# identified by `prevgen` and use it to breed a new generation
# identified by `nextgen`, which hopefully will be more fit.
#
# A different way to use this is to initialize a random gen, with
# python genetic.py <newgen>

import random
import sys

NUMBER_WEIGHTS = 584
POPULATION_SIZE = 100 # populations go from <gen>_00 to <gen>_99

def randomweights():
    """returns a list of random weights. Used to initialize a raw
    population which can then be bred and stuff."""
    result = []
    for i in range(NUMBER_WEIGHTS):
        weight = random.randint(-3, 3)
        result.append(weight)
    return result

def crossover(aimom, aidad):
    """crosses over the two given network weight files."""

if __name__ == "__main__":
    if len(sys.argv) == 2:
        # random new generation mode
        genname = sys.argv[1]
        for i in range(POPULATION_SIZE):
            filename = "networks/" + genname + "_" + str(i)
            aifile = open(filename, "w")
            for weight in randomweights():
                aifile.write("%d\n" % weight)
            aifile.close()

    elif len(sys.argv) == 3:
        prevgen = sys.argv[1]
        newgen = sys.argv[2]

        # play them against each other and compute a fitness

        # cross over the most fit individuals to a new gen

