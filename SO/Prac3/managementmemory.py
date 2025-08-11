import draw as dr
import copy
import os

# GLOBAL VARIABLES
MEMORY_SIZE = 2000
RED = "\033[91m"
WHITE = "\033[0m"
GREEN = "\033[92m"

# CLASSES
class Process:
    def __init__(self, proc, arr, mem, run):
        self.process = proc
        self.arrival = arr
        self.memory = mem
        self.runtime = run
    def getProcess(self):
        return self.process
    def getArrival(self):
        return self.arrival
    def getMemory(self):
        return self.memory
    def getRuntime(self):
        return self.runtime
    def decrease(self):
        self.runtime = self.runtime - 1
    def checkRun(self):
        if self.getRuntime() == 0:
            return True
        return False
    def isHole(self):
        return False

class Hole:
    def __init__(self, memory):
        self.memory = memory
    def getMemory(self):
        return self.memory
    def isHole(self):
        return True

# FUNCTIONS
# Function to get the initial data
def inputData():
    # os.system("clear")
    print("================================= MEMORY SIMULATOR =================================\n")
    inputFile = input("Introduce the name of the file with the input data:\n>> ")
    try:
        file = open(inputFile, 'r')
        algor = int(input("\nSelect the algorithm you want to use:\n1. Worst fit\n2. Best fit\n>> "))
        while algor < 1 or algor > 2:
            algor = int(input("Select a valid algorythm!\n>> "))
        print("\n")
        return inputFile, algor
    except FileNotFoundError:
        print(f"{RED}ERROR: The file does not exist{WHITE}")
        exit(1)
    except IOError:
        print(f"{RED}An error occurred while accessing the file{WHITE}")
        exit(2)

# Function to manage the memory simulation
def memorySimulation(processes, lastToExit, algor):
    executionHistory = []  # List that keeps track of the state of the memory in every iteration
    memory = []  # List that emulates the memory
    queue = []  # Queue for processes that cannot enter memory
    memory.append(Hole(MEMORY_SIZE))  # Initialize the memory with a Hole space
    added_processes = []  # List to track added processes to avoid repetition

    for time in range(1, lastToExit + 1):  # Iterate over every execution time, inclusive

        # Iterate over the processes and add to the queue those which enter at current time
        for process in processes:
            if process.getArrival() == time and process not in added_processes:
                queue.append(process)
                added_processes.append(process)  # Mark this process as added

        # Iterate over the processes in queue and apply the corresponding algorithm to add them to the memory if there is enough space
        for process in queue[:]:  # Copy of queue to avoid modifying it while iterating
            requiredMem = process.getMemory()  # Minimum memory space the entering process needs
            positionToInsert = 0  # Position in memory where the process is going to be inserted
            memToReplace = 0  # Memory of the hole that is going to be replaced
            diff = 0  # Difference between the memory of the replaced block and the memory of the process
            for block in memory:
                if algor == 1:  # Worst fit algorithm -> Bigger space
                    if block.isHole() and block.getMemory() >= requiredMem:
                        if memToReplace == 0 or memToReplace < block.getMemory():
                            positionToInsert = memory.index(block)
                            memToReplace = block.getMemory()
                else:  # Best fit algorithm -> Smaller space
                    if block.isHole() and block.getMemory() >= requiredMem:
                        if memToReplace == 0 or memToReplace > block.getMemory():
                            positionToInsert = memory.index(block)
                            memToReplace = block.getMemory()
            diff = memToReplace - requiredMem
            if diff > 0:  # A new hole is inserted
                del memory[positionToInsert]
                memory.insert(positionToInsert, queue.pop(queue.index(process)))
                memory.insert(positionToInsert + 1, Hole(diff))
            else:  # No new hole is inserted
                del memory[positionToInsert]
                memory.insert(positionToInsert, queue.pop(queue.index(process)))

        # Iterate over the processes in memory updating their runtime and removing the ones which have finished
        for process in memory[:]:  # Copy to safely modify the memory
            if not process.isHole():
                if process.checkRun():
                    mem = process.getMemory()
                    pos = memory.index(process)
                    del memory[pos]
                    memory.insert(pos, Hole(mem))
                else:
                    process.decrease()

        # Deep copy the memory state and append it to executionHistory
        executionHistory.append(copy.deepcopy(memory))

        # Print the result in the partitions.txt file
        address = 0
        with open("partitions.txt", "a") as output_file:
            output_file.write(f"Time {time} ")  # Add a header for the current time frame
            address = 0
            for block in memory:
                if not block.isHole():
                    # For processes, include their process ID and memory size
                    output_file.write(f"[{address} P{block.getProcess()} {block.getMemory()}] ")
                else:
                    # For holes, just include the memory size
                    output_file.write(f"[{address} Hole {block.getMemory()}] ")
                address += block.getMemory()  # Increment the address
            output_file.write("\n")  # Add a newline for better readability between time frames

    return executionHistory


# VARIABLE DECLARATIONS
processes = []      # List where all the processes will be stored
lastToExit = 0      # This represents the time when the last process leaves the queue

# MAIN PROGRAM
(inputFile, algor) = inputData() # Get the input file and verify if it can be used

# Remove the old partitions.txt file
if os.path.exists("partitions.txt"):
    os.remove("partitions.txt")

with open(inputFile, 'r') as file:  # Read the input file and fulfill the processes list
    counter = 0
    for line in file.readlines():
        data = line.split(" ")
        processes.append(Process(int(data[0]), int(data[1]), int(data[2]), int(data[3])))
        counter = counter + 1
    if counter == 0:
        print(f"{RED}ERROR: The file cannot be empty{WHITE}")
        exit(3)

for process in processes:   # Define lastToExit to know the total duration of the program
    duration = process.getArrival() + process.getRuntime()
    if duration > lastToExit:
        lastToExit = duration

print(">> Executing memory partitions...")
print(">> Storing data...")
memoryHistory = memorySimulation(processes, lastToExit, algor)     # Execute the memory simulation and keep a record of it
print(">> Drawing graphic...")
dr.window(memoryHistory, MEMORY_SIZE)    # Draw the processes graphic
print(">> Goodbye!\n")