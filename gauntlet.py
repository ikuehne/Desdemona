# gauntlet.py
# executable that allows for an easy check of how good a neural network
# othello player is. just plays two AIs against each other over and over,
# telling you the score breakdown.
#
# usage: python gauntlet.py <AI1> <AI2> <# games>
# AIs can be either a file of weights like `basicweightsint.txt` or the
# default `simpleplayer`, `betterplayer`, etc.

import subprocess
import sys

def fight(ai1, ai2, times):
    """fights two given ais against each other some number of
    times, returning a tuple (blackwins, whitewins) of the result."""
    blackwins = 0
    whitewins = 0

    for i in range(times):
        p = subprocess.Popen(["./nettestgame", ai1, ai2, "-silent"],
            stdout=subprocess.PIPE, stderr=subprocess.PIPE)


        out, err = p.communicate()
        if "Black" in out:
            blackwins += 1
        elif "White" in out:
            whitewins += 1

    return (blackwins, whitewins)

if __name__ == "__main__":
    times = int(sys.argv[3])
    b, w = fight(sys.argv[1], sys.argv[2], times)

    print "Black won %d of %d games" % (b, times)
    print "and White won %d games." % w
