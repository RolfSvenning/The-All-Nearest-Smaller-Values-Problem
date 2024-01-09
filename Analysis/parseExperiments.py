import re

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
