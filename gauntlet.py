import subprocess
import sys

times = int(sys.argv[3])
blackwins = 0

for i in range(times):
    p = subprocess.Popen(["./testgame", sys.argv[1], sys.argv[2], "-silent"],
        stdout=subprocess.PIPE, stderr=subprocess.PIPE)


    out, err = p.communicate()
    if "Black" in out:
        blackwins += 1
    
print "Black won %d of %d games" % (blackwins, times)
