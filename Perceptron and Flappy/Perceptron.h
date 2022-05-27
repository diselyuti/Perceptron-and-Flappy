#pragma once
#include "Neuron.h"
#include <vector>
#include <cmath>
#include <iostream>
#include <fstream>

using namespace std;

class Perceptron
{
public:
	enum perceptronLayers
	{
		_10_8_6,
		_10,
		_3_3,
		_3_5,
		_10_10_10,
		_5_5_5,
		_3,
		_5
	};
	Perceptron(vector<size_t> sizesOfLayers);
	Perceptron(perceptronLayers type);
	vector<double> output(vector<double> inputs);
	void simpleEducation(vector<vector<double>>& educationData);
	void mutation(double rateOfMutation);
	void setLearningRate(double newRate);
	void setLayersType(perceptronLayers type);
	double getLearningRate();
	void saveToFile();
	void loadFromFile();
private:
	double learningRate = 0.0001;
	perceptronLayers layers;
	vector<Neuron*> net;
	double countValue(Neuron* neuron);
	double sigmoid(double val);
	void updateWeights(Neuron* neuron, double signal);
};


	//void educate(vector<vector<double>> &educationData);
	//void backpropagation(Neuron* neuron, double expectedValue);
	//void innacuracyCalculation(Neuron* neuron);
	//void weightCalculation(Neuron* neuron);