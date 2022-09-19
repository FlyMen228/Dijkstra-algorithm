#include <iostream>
#include <vector>
#include <fstream>

int const inf = INT_MAX - 100;

std::vector <std::vector <int> > inputAdjacencyMatrixFromFile()
{
	std::ifstream reader("input.txt");
	if (!reader.is_open())
		std::cout << "Input file alert!";
	else
	{
		int numOfVertex;
		reader >> numOfVertex;
		std::vector <std::vector <int> > adjacencyMatrix(numOfVertex, std::vector <int> (numOfVertex));
		for (int i = 0; i < numOfVertex; ++i)
			for (int j = 0; j < numOfVertex; ++j)
				if (!reader.eof())
					reader >> adjacencyMatrix[i][j];
				else
					break;
		return adjacencyMatrix; 
	}
}

std::vector<int> dijkstraAlgorithm(std::vector<std::vector<int>> adjacencyMatrix)
{
	int startVertex, demensionOfMatrix = adjacencyMatrix.size();
	std::cout << "Enter start point: ";
	std::cin >> startVertex;
	std::vector <int> resultArray(demensionOfMatrix, inf);
	std::vector <bool> visitedVertexes(demensionOfMatrix, false);
	resultArray[startVertex] = 0;
	int indexOfMinDistance{};
	for (int i = 0; i < demensionOfMatrix; ++i)
	{
		int currentMinimalDistance = inf;
		for (int j = 0; j < demensionOfMatrix; ++j)
			if (!visitedVertexes[j] && resultArray[j] <= currentMinimalDistance)
			{
				currentMinimalDistance = resultArray[j];
				indexOfMinDistance = j;
			}
		visitedVertexes[indexOfMinDistance] = true;
		for (int j = 0; j < demensionOfMatrix; ++j)
			if (!visitedVertexes[j] && adjacencyMatrix[indexOfMinDistance][j] && resultArray[indexOfMinDistance] != inf
				&& resultArray[indexOfMinDistance] + adjacencyMatrix[indexOfMinDistance][j] < resultArray[j])
				resultArray[j] = resultArray[indexOfMinDistance] + adjacencyMatrix[indexOfMinDistance][j];
	}
	return resultArray;
}

void saveResultToFile(std::vector <int> resultArray)
{
	std::ofstream writer;
	writer.open("output.txt", std::ios_base::out);
	for (int i = 0; i < resultArray.size(); ++i)
		if (resultArray[i] < inf)
			writer << resultArray[i] << " ";
		else
			writer << "INF ";
	std::cout << "Minimal distance array successfully writed at 'output.txt'!";
}

int main()
{
	std::vector <std::vector <int> > adjacencyMatrix = inputAdjacencyMatrixFromFile();
	std::vector <int> resultArray = dijkstraAlgorithm(adjacencyMatrix);
	saveResultToFile(resultArray);
	return 0;
}