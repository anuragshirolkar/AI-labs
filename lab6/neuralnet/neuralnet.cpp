#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <stdio.h>
#include <iomanip>
#include <string>
#include <fstream>
#include <cmath>
using namespace std;
#define M 5
#define N 6

double eta = 1;
vector<string> graphemes;
vector<vector<string> > phonemes;
set<string> set_graphemes, set_phonemes;

vector<vector<double> > inputs, outputs;

double sigmoid(double x) {
	double res = 1.0;
	res = res/(1+exp(0-10*x));
	return res;
}

struct neuralnet {
	vector<vector<double> > first_layer, second_layer;

	neuralnet(int a, int b, int c);
	void train();
	double error();
	pair<vector<double>, vector<double> > output(vector<double> &);
};

neuralnet::neuralnet(int a, int b, int c) {
	first_layer = vector<vector<double> >(a, vector<double>(b, 0));
	second_layer = vector<vector<double> >(b, vector<double>(c, 0));
}

void neuralnet::train() {
	for (int it = 0; it < 100000; it++) {
		for (int i = 0; i < inputs.size(); i++) {
			vector<double> delta2;
			pair<vector<double>, vector<double> > o = output(inputs[i]);
			for (int j = 0; j < outputs[i].size(); j++) {
				double temp = (outputs[i][j] - o.second[j]) * o.second[j] * (1-o.second[j]);
				delta2.push_back(temp);
			}
			vector<double> delta1;
			for (int j = 0; j < o.first.size(); j++) {
				double temp = 0;
				for (int k = 0; k < second_layer[j].size(); k++) {
					temp += second_layer[j][k] * delta2[k];
				}
				temp *= o.first[j] * (1-o.first[j]);
				delta1.push_back(temp);
			}
			for (int k = 0; k < second_layer.size(); k++) {
				for (int j = 0; j < second_layer[k].size(); j++) {
					second_layer[k][j] += eta * delta2[j] * o.first[k];
				}
			}
			for (int k = 0; k < first_layer.size(); k++) {
				for (int j = 0; j < first_layer[k].size(); j++) {
					first_layer[k][j] += eta * delta1[j] * inputs[i][k];
				}
			}
		}
		if (it % 10000 == 0) cout << error() << endl;
	}

	for (int i = 0; i < inputs.size(); i++) {
		for (int j = 0; j < inputs[i].size(); j++) cout << inputs[i][j] << " ";
		cout << ": ";
		vector<double> out = output(inputs[i]).second;
		for (int j = 0; j < out.size(); j++) cout << out[j] << " ";
		cout << endl;
	}
}

double neuralnet::error() {
	double err = 0;
	for (int i = 0; i < inputs.size(); i++) {
		vector<double> out = output(inputs[i]).second;
		for (int j = 0; j < out.size(); j++) {
			err += (outputs[i][j] - out[j]) * (outputs[i][j] - out[j]);
		}
	}
	return err/2;
}

pair<vector<double>, vector<double> > neuralnet::output(vector<double> &input) {
	int size1 = first_layer.size();
	int size2 = second_layer.size();
	int size3 = second_layer[0].size();
	vector<double> first_output;
	for (int i = 0; i < size2; i++) {
		double a = 0;
		for (int j = 0; j < size1; j++) a += input[j]*first_layer[j][i];
		first_output.push_back(sigmoid(a));
	}
	vector<double> final_output;
	for (int i = 0; i < size3; i++) {
		double a = 0;
		for (int j = 0; j < size2; j++) a += first_output[j]*second_layer[j][i];
		final_output.push_back(sigmoid(a));
	}
	first_output[first_output.size()-1] = 1;
	return pair<vector<double>, vector<double> >(first_output, final_output);
}

void read_data () {
	ifstream f;
	f.open("training_data");
	string gr;
	while(f >> gr) {
		int s = gr.size();
		vector<string> ph;
		for (int i = 0; i < s; i++) {
			string temp;
			f >> temp;
			ph.push_back(temp);
			set_phonemes.insert(temp);
		}
		graphemes.push_back(gr);
		for (int i = 0; i < gr.size(); i++) set_graphemes.insert(string(1, gr[i]));
		phonemes.push_back(ph);
	}
}

void initxor() {
	for (int i = 0; i < 4; i++) {
		vector<double> in, out;
		int a, b, c, d;
		cin >> a>> b>> c;
		in.push_back(a);
		in.push_back(b);
		in.push_back(1);
		out.push_back(c);
		inputs.push_back(in);
		outputs.push_back(out);
	}
}

int main()
{
    read_data();
	neuralnet nn(3,3,1);
	initxor();
	nn.train();
	cout << "first :" << endl;
	for (int i = 0; i < nn.first_layer.size(); i++) {
		for (int j = 0; j < nn.first_layer[i].size(); j++) cout << nn.first_layer[i][j] << " ";
		cout << endl;
	}
	cout << "second :" << endl;
	for (int i = 0; i < nn.second_layer.size(); i++) {
		for (int j = 0; j < nn.second_layer[i].size(); j++) cout << nn.second_layer[i][j] << " ";
		cout << endl;
	}
    return 0;
}
