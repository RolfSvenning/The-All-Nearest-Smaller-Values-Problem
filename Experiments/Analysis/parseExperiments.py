import re

class E:
    def __init__(self, algorithmType, inputType, numberOfCores, n, blockSize, usingHeuristic, times, T_tree, T_local, T_merging):
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
        self.T_tree         = -1 if len(T_tree)    == 0 else sum(T_tree)    / len(T_tree)
        self.T_local        = -1 if len(T_local)   == 0 else sum(T_local)   / len(T_local)
        self.T_merging      = -1 if len(T_merging) == 0 else sum(T_merging) / len(T_merging)

        assert 1 <= self.numberOfCores <= 48
        assert self.times
        assert 1 <= self.n
        assert all(t >= 0 for t in self.times)
        # if not (self.minTimes <= self.averageTime <= self.maxTime):
        #     print(self.minTimes, self.averageTime, self.maxTime)
        # assert self.minTimes <= self.averageTime <= self.maxTime

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
    T_tree = [float(t) for t in re.findall("Binary tree: ([\d|.]+)", e)]
    T_local = [float(t) for t in re.findall("Local matches: ([\d|.]+)", e)]
    T_merging = [float(t) for t in re.findall("Merging: ([\d|.]+)", e)]
    T_treeTraversal = [float(t) for t in re.findall("Tree traversal: ([\d|.]+)", e)]
    return E(algorithmType, inputType, numberOfCores, n, blockSize, usingHeuristic, times, T_tree, T_local, T_merging + T_treeTraversal)

# Binary tree: 0.001024
# Local matches: 0.015288
# Merging: 0.011013
# Total time: 0.027328

def parseFile(fileName):
    Es = [parseExperiment(e) for e in open("Experiments/Results/" + fileName).read().split("Date")[1:]]# TODO[1:]
    return Es
