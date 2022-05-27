#include "Perceptron.h"


Perceptron::Perceptron(vector<size_t> sizesOfLayers) {
	for (size_t i = 0; i < sizesOfLayers.size(); i++)
	{
		for (size_t j = 0; j < sizesOfLayers[i]; j++)
		{
			Neuron* neuron = new Neuron();
			neuron->layerId = i;
			if (i == 0)
			{
				neuron->layerStatus = FIRST;
			}
			else if (i == sizesOfLayers.size() - 1)
			{
				neuron->layerStatus = LAST;
			}
			else
			{
				neuron->layerStatus = MIDDLE;
			}
			net.push_back(neuron);
		}
	}
	for (size_t i = 0; i < net.size(); i++)
	{
		if (net[i]->layerStatus == MIDDLE)
		{
			for (size_t j = 0; j < net.size(); j++)
			{
				if (net[j]->layerId == net[i]->layerId - 1)
				{
					net[i]->leftConnections.push_back(net[j]);
					net[i]->leftConnectionsWeights.push_back((double)(rand() % 10 - 5)/10.);
				}
				else if (net[j]->layerId == net[i]->layerId + 1)
				{
					net[i]->rightConnections.push_back(net[j]);
					net[i]->rightConnectionsWeights.push_back((double)(rand() % 10 - 5) / 10.);
				}
			}
		}
		else if (net[i]->layerStatus == FIRST)
		{
			for (size_t j = 0; j < net.size(); j++)
			{
				if (net[j]->layerId == net[i]->layerId + 1)
				{
					net[i]->rightConnections.push_back(net[j]);
					net[i]->rightConnectionsWeights.push_back((double)(rand() % 10 - 5) / 10.);
				}
			}
		}
		else 
		{
			for (size_t j = 0; j < net.size(); j++)
			{
				if (net[j]->layerId == net[i]->layerId - 1)
				{
					net[i]->leftConnections.push_back(net[j]);
					net[i]->leftConnectionsWeights.push_back((double)(rand() % 10 - 5) / 10.);
				}
			}
		}
	}
}

Perceptron::Perceptron(perceptronLayers type) {
	layers = type;
	vector<size_t> sizesOfLayers;
	switch (type)
	{
	case Perceptron::_10_8_6:
		sizesOfLayers = { 4, 10, 8, 6, 1 };
		break;
	case Perceptron::_10:
		sizesOfLayers = { 4, 10, 1 };
		break;
	case Perceptron::_3_3:
		sizesOfLayers = { 4, 3, 3, 1 };
		break;
	case Perceptron::_3_5:
		sizesOfLayers = { 4, 3, 5, 1 };
		break;
	case Perceptron::_10_10_10:
		sizesOfLayers = { 4, 10, 10, 10, 1 };
		break;
	case Perceptron::_5_5_5:
		sizesOfLayers = { 4, 5, 5, 5, 1 };
		break;
	case Perceptron::_5:
		sizesOfLayers = { 4, 5, 1 };
		break;
	case Perceptron::_3:
		sizesOfLayers = { 4, 3, 1 };
		break;
	default:
		break;
	}
	for (size_t i = 0; i < sizesOfLayers.size(); i++)
	{
		for (size_t j = 0; j < sizesOfLayers[i]; j++)
		{
			Neuron* neuron = new Neuron();
			neuron->layerId = i;
			if (i == 0)
			{
				neuron->layerStatus = FIRST;
			}
			else if (i == sizesOfLayers.size() - 1)
			{
				neuron->layerStatus = LAST;
			}
			else
			{
				neuron->layerStatus = MIDDLE;
			}
			net.push_back(neuron);
		}
	}
	for (size_t i = 0; i < net.size(); i++)
	{
		if (net[i]->layerStatus == MIDDLE)
		{
			for (size_t j = 0; j < net.size(); j++)
			{
				if (net[j]->layerId == net[i]->layerId - 1)
				{
					net[i]->leftConnections.push_back(net[j]);
					net[i]->leftConnectionsWeights.push_back((double)(rand() % 10 - 5) / 10.);
				}
				else if (net[j]->layerId == net[i]->layerId + 1)
				{
					net[i]->rightConnections.push_back(net[j]);
					net[i]->rightConnectionsWeights.push_back((double)(rand() % 10 - 5) / 10.);
				}
			}
		}
		else if (net[i]->layerStatus == FIRST)
		{
			for (size_t j = 0; j < net.size(); j++)
			{
				if (net[j]->layerId == net[i]->layerId + 1)
				{
					net[i]->rightConnections.push_back(net[j]);
					net[i]->rightConnectionsWeights.push_back((double)(rand() % 10 - 5) / 10.);
				}
			}
		}
		else
		{
			for (size_t j = 0; j < net.size(); j++)
			{
				if (net[j]->layerId == net[i]->layerId - 1)
				{
					net[i]->leftConnections.push_back(net[j]);
					net[i]->leftConnectionsWeights.push_back((double)(rand() % 10 - 5) / 10.);
				}
			}
		}
	}
}

vector<double> Perceptron::output(vector<double> inputs)
{
	vector<Neuron*> inputNeurons;
	vector<double> outputValues;
	for (size_t i = 0; i < net.size(); i++)
	{
		if (net[i]->layerStatus == FIRST)
		{
			inputNeurons.push_back(net[i]);
		}
	}
	if (inputNeurons.size() <= inputs.size())
	{
		for (size_t i = 0; i < inputNeurons.size(); i++)
		{
			inputNeurons[i]->value = inputs[i];
		}
	} else return vector<double>();
	for (size_t i = inputNeurons.size(); i < net.size(); i++)
	{
		countValue(net[i]);
	}
	for (size_t i = 0; i < net.size(); i++)
	{
		if (net[i]->layerStatus == LAST)
		{
			outputValues.push_back(net[i]->value);
		}
	}
	return outputValues;
}



double Perceptron::countValue(Neuron* neuron)
{
	double value = 0;
	for (size_t i = 0; i < neuron->leftConnections.size(); i++)
	{
		for (size_t j = 0; j < neuron->leftConnections[i]->rightConnections.size(); j++)
		{
			if (neuron->leftConnections[i]->rightConnections[j] == neuron)
			{
				value += neuron->leftConnections[i]->value * neuron->leftConnections[i]->rightConnectionsWeights[j];
			}
		}
	}
	value = sigmoid(value);
	neuron->value = value;
	return value;
}


double Perceptron::sigmoid(double val)
{	
	return 1 / (1 + exp(-1 * (val)));
}

void Perceptron::simpleEducation(vector<vector<double>>& educationData)
{
	int countOfInputNeurons = 0;
	for (size_t i = 0; i < net.size(); i++)
	{
		if (net[i]->layerStatus == FIRST)
		{
			countOfInputNeurons++;
		}
	}
	for (size_t i = 0; i < educationData.size(); i++)
	{
		vector<double> inputValues;
		for (size_t j = 0; j < countOfInputNeurons; j++)
		{
			inputValues.push_back(educationData[i][j]);
		}
		output(inputValues);
		vector<Neuron*> outputNeurons;
		for (size_t j = 0; j < net.size(); j++)
		{
			if (net[j]->layerStatus == LAST)
			{
				outputNeurons.push_back(net[j]);
			}
		}
		for (size_t j = 0; j < outputNeurons.size(); j++)
		{
			if (abs(educationData[i][countOfInputNeurons + j] - outputNeurons[j]->value) > 0.05)
			{
				if (educationData[i][countOfInputNeurons + j] - outputNeurons[j]->value > 0)
				{
					updateWeights(outputNeurons[j], 1.);
				}
				else
				{
					updateWeights(outputNeurons[j], -1.);
				}
			}
		}
	}
}

void Perceptron::mutation(double rateOfMutation)
{
	for (size_t i = 0; i < net.size(); i++)
	{
		
	}
}

void Perceptron::setLearningRate(double newRate)
{
	if (newRate > 0 && newRate < 1)
	{
		learningRate = newRate;
	}
}

void Perceptron::setLayersType(perceptronLayers type)
{
	layers = type;
	net.clear();
	vector<size_t> sizesOfLayers;
	switch (type)
	{
	case Perceptron::_10_8_6:
		sizesOfLayers = { 4, 10, 8, 6, 1 };
		break;
	case Perceptron::_10:
		sizesOfLayers = { 4, 10, 1 };
		break;
	case Perceptron::_3_3:
		sizesOfLayers = { 4, 3, 3, 1 };
		break;
	case Perceptron::_3_5:
		sizesOfLayers = { 4, 3, 5, 1 };
		break;
	case Perceptron::_10_10_10:
		sizesOfLayers = { 4, 10, 10, 10, 1 };
		break;
	case Perceptron::_5_5_5:
		sizesOfLayers = { 4, 5, 5, 5, 1 };
		break;
	case Perceptron::_5:
		sizesOfLayers = { 4, 5, 1 };
		break;
	case Perceptron::_3:
		sizesOfLayers = { 4, 3, 1 };
		break;
	default:
		break;
	}
	for (size_t i = 0; i < sizesOfLayers.size(); i++)
	{
		for (size_t j = 0; j < sizesOfLayers[i]; j++)
		{
			Neuron* neuron = new Neuron();
			neuron->layerId = i;
			if (i == 0)
			{
				neuron->layerStatus = FIRST;
			}
			else if (i == sizesOfLayers.size() - 1)
			{
				neuron->layerStatus = LAST;
			}
			else
			{
				neuron->layerStatus = MIDDLE;
			}
			net.push_back(neuron);
		}
	}
	for (size_t i = 0; i < net.size(); i++)
	{
		if (net[i]->layerStatus == MIDDLE)
		{
			for (size_t j = 0; j < net.size(); j++)
			{
				if (net[j]->layerId == net[i]->layerId - 1)
				{
					net[i]->leftConnections.push_back(net[j]);
					net[i]->leftConnectionsWeights.push_back((double)(rand() % 10 - 5) / 10.);
				}
				else if (net[j]->layerId == net[i]->layerId + 1)
				{
					net[i]->rightConnections.push_back(net[j]);
					net[i]->rightConnectionsWeights.push_back((double)(rand() % 10 - 5) / 10.);
				}
			}
		}
		else if (net[i]->layerStatus == FIRST)
		{
			for (size_t j = 0; j < net.size(); j++)
			{
				if (net[j]->layerId == net[i]->layerId + 1)
				{
					net[i]->rightConnections.push_back(net[j]);
					net[i]->rightConnectionsWeights.push_back((double)(rand() % 10 - 5) / 10.);
				}
			}
		}
		else
		{
			for (size_t j = 0; j < net.size(); j++)
			{
				if (net[j]->layerId == net[i]->layerId - 1)
				{
					net[i]->leftConnections.push_back(net[j]);
					net[i]->leftConnectionsWeights.push_back((double)(rand() % 10 - 5) / 10.);
				}
			}
		}
	}
	loadFromFile();
}

double Perceptron::getLearningRate()
{
	return learningRate;
}

void Perceptron::saveToFile()
{
	vector<double> arr;
	for (size_t i = 0; i < net.size(); i++)
	{
		for (size_t j = 0; j < net[i]->leftConnectionsWeights.size(); j++)
		{
			arr.push_back(net[i]->leftConnectionsWeights[j]);
		}
		for (size_t j = 0; j < net[i]->rightConnectionsWeights.size(); j++)
		{
			arr.push_back(net[i]->rightConnectionsWeights[j]);
		}
	}
	ofstream fout;
	switch (layers)
	{
	case Perceptron::_10_8_6:
		fout.open("_10_8_6.bin", ios_base::binary);
		break;
	case Perceptron::_10:
		fout.open("_10.bin", ios_base::binary);
		break;
	case Perceptron::_3_3:
		fout.open("_3_3.bin", ios_base::binary);
		break;
	case Perceptron::_3_5:
		fout.open("_3_5.bin", ios_base::binary);
		break;
	case Perceptron::_5_5_5:
		fout.open("_5_5_5.bin", ios_base::binary);
		break;
	case Perceptron::_10_10_10:
		fout.open("_10_10_10.bin", ios_base::binary);
		break;
	case Perceptron::_3:
		fout.open("_3.bin", ios_base::binary);
		break;
	case Perceptron::_5:
		fout.open("_5.bin", ios_base::binary);
		break;
	default:
		return;
	}
	unsigned size = arr.size();
	fout.write(reinterpret_cast<char*>(&size), sizeof(unsigned));
	fout.write(reinterpret_cast<char*>(&arr[0]), arr.size() * sizeof(double));
	fout.close();
}

void Perceptron::loadFromFile()
{
	ifstream fin;
	switch (layers)
	{
	case Perceptron::_10_8_6:
		fin.open("_10_8_6.bin", ios::in | ios::binary);
		break;
	case Perceptron::_10:
		fin.open("_10.bin", ios::in | ios::binary);
		break;
	case Perceptron::_3_3:
		fin.open("_3_3.bin", ios::in | ios::binary);
		break;
	case Perceptron::_3_5:
		fin.open("_3_5.bin", ios::in | ios::binary);
		break;
	case Perceptron::_5_5_5:
		fin.open("_5_5_5.bin", ios::in | ios::binary);
		break;
	case Perceptron::_10_10_10:
		fin.open("_10_10_10.bin", ios::in | ios::binary);
		break;
	case Perceptron::_3:
		fin.open("_3.bin", ios::in | ios::binary);
		break;
	case Perceptron::_5:
		fin.open("_5.bin", ios::in | ios::binary);
		break;
	default:
		return;
	}
	unsigned size;
	fin.read(reinterpret_cast<char*>(&size), sizeof(unsigned));
	vector<double> arr(size);
	fin.read(reinterpret_cast<char*>(&arr[0]), size * sizeof(double));
	fin.close();

	size_t index = 0;
	for (size_t i = 0; i < net.size(); i++)
	{
		for (size_t j = 0; j < net[i]->leftConnectionsWeights.size(); j++)
		{
			net[i]->leftConnectionsWeights[j] = arr[index++];
		}
		for (size_t j = 0; j < net[i]->rightConnectionsWeights.size(); j++)
		{
			net[i]->rightConnectionsWeights[j] = arr[index++];
		}
	}
}

void Perceptron::updateWeights(Neuron* neuron, double signal) {
	for (size_t i = 0; i < neuron->leftConnections.size(); i++)
	{
		for (size_t j = 0; j < neuron->leftConnections[i]->rightConnectionsWeights.size(); j++)
		{
			neuron->leftConnections[i]->rightConnectionsWeights[j] += signal * learningRate * neuron->value;
		}
	}
	if (neuron->leftConnections.size() > 0)
	{
		updateWeights(neuron->leftConnections[0], signal);
	}
}





//void Perceptron::backpropagation(Neuron* neuron, double expectedValue)
//{
//	neuron->innacuracy = (expectedValue - neuron->value) * neuron->value * (1 - neuron->value);
//	innacuracyCalculation(neuron);
//	weightCalculation(neuron);
//}

//void Perceptron::innacuracyCalculation(Neuron* neuron)
//{
//	for (size_t i = 0; i < neuron->leftConnections.size(); i++)
//	{
//		for (size_t j = 0; j < neuron->leftConnections[i]->rightConnections.size(); j++)
//		{
//			neuron->leftConnections[i]->innacuracy +=
//				neuron->leftConnections[i]->rightConnections[j]->innacuracy * neuron->leftConnections[i]->rightConnectionsWeights[j] * neuron->leftConnections[i]->value * (1 - neuron->leftConnections[i]->value);
//		}
//	}
//	for (size_t i = 0; i < neuron->leftConnections.size(); i++)
//	{
//		innacuracyCalculation(neuron->leftConnections[i]);
//	}
//}

//void Perceptron::weightCalculation(Neuron* neuron)
//{
//	for (size_t i = 0; i < neuron->leftConnections.size(); i++)
//	{
//		for (size_t j = 0; j < neuron->leftConnections[i]->rightConnections.size(); j++)
//		{
//			neuron->leftConnections[i]->rightConnectionsWeights[j] =
//				neuron->leftConnections[i]->value * neuron->leftConnections[i]->rightConnections[j]->innacuracy * learningRate;
//		}
//	}
//	for (size_t i = 0; i < neuron->leftConnections.size(); i++)
//	{
//		weightCalculation(neuron->leftConnections[i]);
//	}
//}

//void Perceptron::educate(vector<vector<double>> &educationData)
//{
//	int countOfInputNeurons = 0;
//	for (size_t i = 0; i < net.size(); i++)
//	{
//		if (net[i]->layerStatus == FIRST)
//		{
//			countOfInputNeurons++;
//		}
//	}
//	for (size_t i = 0; i < educationData.size(); i++)
//	{
//		// получение входных
//		vector<double> inputValues;
//		for (size_t j = 0; j < countOfInputNeurons; j++)
//		{
//			inputValues.push_back(educationData[i][j]);
//		}
//		output(inputValues);
//		vector<Neuron*> outputNeurons;
//		for (size_t j = 0; j < net.size(); j++)
//		{
//			if (net[j]->layerStatus == LAST)
//			{
//				outputNeurons.push_back(net[j]);
//			}
//		}
//		for (size_t j = 0; j < outputNeurons.size(); j++)
//		{
//			backpropagation(outputNeurons[j], educationData[i][countOfInputNeurons]);
//		}
//	}
//}
