from parseExperiments import parseFile
from matplotlib import pyplot as plt
import numpy as np

Es = parseFile("blockSize.txt")
Es1 =  [e for e in Es if e.numberOfCores ==  1]  
Es48 = [e for e in Es if e.numberOfCores == 48]  

# P = 1
smallBlockSize1   = [(e.averageTime, e.blockSize, e.inputType) for e in Es1 if e.algorithmType == "BERKMAN_VISHKIN" and e.blockSize <= 64]
mediumBlockSize1  = [(e.averageTime, e.blockSize, e.inputType) for e in Es1 if e.algorithmType == "BERKMAN_VISHKIN" and 64 <= e.blockSize <= 10000]
largeBlockSize1   = [(e.averageTime, e.blockSize, e.inputType) for e in Es1 if e.algorithmType == "BERKMAN_VISHKIN"]

# P = 48
smallBlockSize48  = [(e.averageTime, e.blockSize, e.inputType) for e in Es48 if e.algorithmType == "BERKMAN_VISHKIN" and e.blockSize <= 64]
mediumBlockSize48 = [(e.averageTime, e.blockSize, e.inputType) for e in Es48 if e.algorithmType == "BERKMAN_VISHKIN" and 64 <= e.blockSize <= 10000]
largeBlockSize48  = [(e.averageTime, e.blockSize, e.inputType) for e in Es48 if e.algorithmType == "BERKMAN_VISHKIN"]

Cmap = {"RANDOM": "blue", "SORTED":"green", "MERGE": "red"}



def plotBlockSize(TBs, title, logScale=False,):
    _, ax = plt.subplots()
    T = np.array([t for t, _, _ in TBs])
    B = np.array([b for _, b, _ in TBs])
    C = np.array([Cmap[c] for _, _, c in TBs])
    for inputType, color in Cmap.items():
        ix = np.where(C == color)
        ax.scatter(B[ix], T[ix], c = color, label = inputType, s = 10)

    if logScale: plt.xscale('log')
    plt.xlabel('Block Size')
    plt.ylabel('Average Running Time')
    plt.title(title)
    ax.legend()
    plt.show()

# P = 1
# plotBlockSize(smallBlockSize1, "Block Size vs. Average Running Time (n = xxx, P = 1)")
# plotBlockSize(mediumBlockSize1, "Block Size vs. Average Running Time (n = xxx, P = 1)")
plotBlockSize(largeBlockSize1, "Block Size vs. Average Running Time (n = xxx, P = 1)", logScale=True)

# P = 48
# plotBlockSize(smallBlockSize48, "Block Size vs. Average Running Time (n = xxx, P = 48)")
# plotBlockSize(mediumBlockSize48, "Block Size vs. Average Running Time (n = xxx, P = 48)")
plotBlockSize(largeBlockSize48, "Block Size vs. Average Running Time (n = xxx, P = 48)", logScale=True)