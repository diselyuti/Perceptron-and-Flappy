#pragma once
#include <vector>

using namespace std;

enum LayerStatus
{
	FIRST,
	MIDDLE,
	LAST
};

class Neuron
{
public:
	size_t layerId;
	LayerStatus layerStatus;
	double value;
	double innacuracy; // ������ ��������(��� ��������� ��������������� ������)
	vector<Neuron*> leftConnections;
	vector<double> leftConnectionsWeights;
	vector<Neuron*> rightConnections;
	vector<double> rightConnectionsWeights;
};

