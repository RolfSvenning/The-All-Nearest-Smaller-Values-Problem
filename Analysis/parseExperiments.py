import re
from matplotlib import pyplot as plt

class E:
    def __init__(self, algorithmType, inputType, numberOfCores, n, blockSize, usingHeuristic, times):
        self.algorithmType  = algorithmType
        self.inputType      = inputType
        self.numberOfCores  = int(numberOfCores)
        self.n              = int(n)
        self.blockSize      = int(blockSize)
        self.usingHeuristic = bool(usingHeuristic)
        self.times          = [float(t) for t in times]
        self.averageTime    = sum(times) / len(times)
        self.maxTime        = max(times)
        self.minTimes       = min(times)

        assert 1 <= self.numberOfCores <= 48
        assert self.times
        assert 1 <= self.n
        assert all(t >= 0 for t in self.times)

    def __repr__(self):
        return (
            f"\nAlgorithm Type: {self.algorithmType}\n"
            f"Input Type: {self.inputType}\n"
            f"Number of Cores: {self.numberOfCores}\n"
            f"N: {self.n}\n"
            f"Block Size: {self.blockSize}\n"
            f"Using Heuristic: {self.usingHeuristic}\n"
            f"Times: {self.times}\n"
            f"Average Time: {self.averageTime}\n"
            f"Max Time: {self.maxTime}\n"
            f"Min Time: {self.minTimes})\n"
        )


def parseExperiment(e):
    algorithmType, inputType, _, numberOfCores = re.findall("=(\w+)", e)
    n, blockSize, usingHeuristic = re.findall("\d+", e.split("\n")[3])
    times = [float(t) for t in re.findall("Total time: ([\d|.]+)", e)]
    return E(algorithmType, inputType, numberOfCores, n, blockSize, usingHeuristic, times)

def parseFile(fileName):
    Es = [parseExperiment(e) for e in open("Experiments/Results/blockSize.txt").read().split("Date")[1:]]# TODO[1:]
    return Es


Es = parseFile("blockSize.txt")
# print(Es[30])

Es1 =  [e for e in Es if e.numberOfCores ==  1]  
Es64 = [e for e in Es if e.numberOfCores == 48]  


# P = 1
smallBlockSize1  = [(e.averageTime, e.blockSize, e.inputType) for e in Es1 if e.algorithmType == "BERKMAN_VISHKIN" and e.blockSize <= 64]
mediumBlockSize1 = [(e.averageTime, e.blockSize, e.inputType) for e in Es1 if e.algorithmType == "BERKMAN_VISHKIN" and 64 <= e.blockSize <= 10000]
largeBlockSize1  = [(e.averageTime, e.blockSize, e.inputType) for e in Es1 if e.algorithmType == "BERKMAN_VISHKIN"]

# P = 48
smallBlockSize48  = [(e.averageTime, e.blockSize, e.inputType) for e in Es1 if e.algorithmType == "BERKMAN_VISHKIN" and e.blockSize <= 64]
mediumBlockSize48 = [(e.averageTime, e.blockSize, e.inputType) for e in Es1 if e.algorithmType == "BERKMAN_VISHKIN" and 64 <= e.blockSize <= 10000]
largeBlockSize48  = [(e.averageTime, e.blockSize, e.inputType) for e in Es1 if e.algorithmType == "BERKMAN_VISHKIN"]

Cmap = {"RANDOM": "blue", "SORTED":"green", "MERGE": "red"}

def plotBlockSize(TBs, logScale=False):
    # Separate x and y coordinates
    T = [t for t, _, _ in TBs]
    B = [b for _, b, _ in TBs]
    C = [Cmap[c] for _, _, c in TBs]
    plt.scatter(B, T, color=C)
    if logScale: plt.xscale('log')  # Set x-axis to logarithmic scale
    plt.xlabel('blockSize')
    plt.ylabel('average running time')
    plt.show()

# P = 1
plotBlockSize(smallBlockSize1)
plotBlockSize(mediumBlockSize1)
plotBlockSize(largeBlockSize1, logScale=True)

# P = 48
plotBlockSize(smallBlockSize48)
plotBlockSize(mediumBlockSize48)
plotBlockSize(largeBlockSize48, logScale=True)