#ifndef _MY_DATA_SET_H
#define _MY_DATA_SET_H
#include "Utils.h"
#include "graph.hpp"
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <QDebug>

typedef std::pair<float, float> min_max;

const float Colors[][3] =
{
	{0.8, 0.51, 0.},
	{0.11, 0.35, 0.38},
	{0.14, 0.78, 0.57},
	{0.78, 0.1, 0.07},
	{1., 1., 0.5},
	{0.75, 0.39, 0.21 },		
	{0.15, 0.39, 0.83 },		// yellow
	{ 0., 1., 0. },		// green
	{ 0., 1., 1. },		// cyan
	{ 0., 0., 1. },		// blue
	{ 1., 0., 1. },		// magenta
	{ 1., 1., 1. },		// white
	{ 0., 0., 0. },		// black

};

class Item
{
public:
	Item();
	~Item();

	float value;				// item value
	int example_id;				// which example this item belongs to
	float pos_x, pos_y;			// the viewport position
	int feature_id;				// which attribute this item blongs to 
	float r, g, b;				// data color (temporary for clustering check)
	int cluster_id;				// which cluster this item belongs to
	float w_x, w_y;				// the widget position
};


class Feature
{
public:
	Feature();
	~Feature();

	int feature_id;					// feature id
	int ordinal_id;					// ordinal information in window
	int num_items;					// the number of items on the feature
	float pos_x, pos_y, length;		// the viewport position of feature
	float brush_bot, brush_top;		// the viewport position of brush
	float item_min, item_max;		// item min value, item max value 
	std::vector<Item> items;		// items on the feature
	std::string label;				// the name of the feature
	QString coord_label;			// the name of the feature, coordinate
//	std::vector<Brush> brushes;		// the min and max of brush
};

class MyDataSet
{
private:
	static MyDataSet* instance;
	MyDataSet();

public:
	static MyDataSet* getInstance();
	char* file_name;

	std::vector<Feature> features;
	std::vector<float *> dataset;		// raw dataset
	std::vector<float *> X;				// independent variables
	std::vector<float *> Y;				// dependent variable (classification)
	std::vector<min_max> ranges;		// data ranges (min, max)
	QStringList feature_name;			// name of attributes 
	std::vector<float> saturation;
	std::vector<float> value;
	std::vector<std::tuple<float, float, float>> color;
	
	int num_clicks = 0;
	int NUMPOINTS = 15;
	std::vector<float *> corr_mat;							// correlation matrix
	bool curve_mode = false;			// true: curve   
	double smooth_value = 0.;			// smoothness of cubic bezier curve
	double corr_value = 0.;				// correlation value between two dimensions
	Graph gGraph;
	std::vector<Graph> vGraph;			// vector of graphs
	std::vector < std::tuple <GLfloat, GLfloat, int > * > center_of_mass;	// center of mass table for force-directed edge-bundling

	int num_features;					// number of features
	int num_examples;					// number of data
	int num_clusters;					// number of clusters
	std::vector<int> cluster_size;		// size of each cluster
	int current_feature_idx;			// current active feature
	std::vector<std::tuple<float, float, float>> cluster_color;	// color of cluster
	bool gravitation_mode;				// 0: default(0,0) , 1: center of cluster
	bool smooth_flag;					// 0: no smooth, 1: smooth done

	void set_X();						// set independent variables
	void set_Y();						// set dependent variable
	void set_ranges();					// set (min, max) ranges to ranges
	std::vector<float *> normalizedX;	// normalized dataset
	void setup_interaction();
	void set_initialization();			// set initialization of data
	void set_example_idx();				// set example idx
	void set_feature_label();			// set feature_name to features[idx].label
	void set_viewport_pos();			// set viewport position for all points
	void set_widget_pos();				// set widget position for all points
	void set_default_colors(int K);		// set default color to each clusters
	void set_correlation_matrix();		// set correlation matrix of features
	void set_cluster_info(int K);		// set cluster information from file
	void set_center_of_mass();			// set a table of center of mass
	void set_gravity_point();			// set gravity point for clusters
	std::pair<float, float> origin_w_size;// original widget size

	std::vector<std::pair<float, float>> dimension_reduction(int num_features, int num_examples); // dimension reduction by t-SNE
	int classify_data(std::vector<std::pair<float, float>>);	// classification
};


class UIInfo
{
private:
	static UIInfo* instance;
	UIInfo();
public:
	static UIInfo* getInstance();

	// Information of OpenGL widget
	int widget_width, widget_height;
};

class Correlation{
public:
	Correlation();
	~Correlation();
	float pearson_corrleation_coefficient(float * axis1, float * axis2, int n);
};

class Point {

private:
	int pointId, clusterId;
	int dimensions;
	std::vector<double> values;

public:
	Point(int id, std::string line) {
		dimensions = 0;
		pointId = id;
		std::stringstream is(line);
		double val;
		while (is >> val) {
			values.push_back(val);
			dimensions++;
		}
		clusterId = 0; //Initially not assigned to any cluster
	}

	Point(int id, std::pair<float, float> data) {
		pointId = id;
		dimensions = 2;
		values.push_back(data.first);
		values.push_back(data.second);
		clusterId = 0; //Initially not assigned to any cluster
	}

	int getDimensions() {
		return dimensions;
	}

	int getCluster() {
		return clusterId;
	}

	int getID() {
		return pointId;
	}

	void setCluster(int val) {
		clusterId = val;
	}

	double getVal(int pos) {
		return values[pos];
	}
};

class Cluster {

private:
	int clusterId;
	std::vector<double> centroid;
	std::vector<Point> points;

public:
	Cluster(int clusterId, Point centroid) {
		this->clusterId = clusterId;
		for (int i = 0; i < centroid.getDimensions(); i++) {
			this->centroid.push_back(centroid.getVal(i));
		}
		this->addPoint(centroid);
	}

	void addPoint(Point p) {
		p.setCluster(this->clusterId);
		points.push_back(p);
	}

	bool removePoint(int pointId) {
		int size = points.size();

		for (int i = 0; i < size; i++)
		{
			if (points[i].getID() == pointId)
			{
				points.erase(points.begin() + i);
				return true;
			}
		}
		return false;
	}

	int getId() {
		return clusterId;
	}

	Point getPoint(int pos) {
		return points[pos];
	}

	int getSize() {
		return points.size();
	}

	double getCentroidByPos(int pos) {
		return centroid[pos];
	}

	void setCentroidByPos(int pos, double val) {
		this->centroid[pos] = val;
	}
};

class KMeans {
private:
	int K, iters, dimensions, total_points;
	std::vector<Cluster> clusters;

	int getNearestClusterId(Point point) {
		double sum = 0.0, min_dist;
		int NearestClusterId;

		for (int i = 0; i < dimensions; i++)
		{
			sum += pow(clusters[0].getCentroidByPos(i) - point.getVal(i), 2.0);
		}

		min_dist = sqrt(sum);
		NearestClusterId = clusters[0].getId();

		for (int i = 1; i < K; i++)
		{
			double dist;
			sum = 0.0;

			for (int j = 0; j < dimensions; j++)
			{
				sum += pow(clusters[i].getCentroidByPos(j) - point.getVal(j), 2.0);
			}

			dist = sqrt(sum);

			if (dist < min_dist)
			{
				min_dist = dist;
				NearestClusterId = clusters[i].getId();
			}
		}

		return NearestClusterId;
	}

public:
	KMeans(int K, int iterations) {
		this->K = K;
		this->iters = iterations;
	}

	void run(std::vector<Point>& all_points) {

		total_points = all_points.size();
		dimensions = all_points[0].getDimensions();


		//Initializing Clusters
		std::vector<int> used_pointIds;

		for (int i = 1; i <= K; i++)
		{
			while (true)
			{
				int index = rand() % total_points;

				if (find(used_pointIds.begin(), used_pointIds.end(), index) == used_pointIds.end())
				{
					used_pointIds.push_back(index);
					all_points[index].setCluster(i);
					Cluster cluster(i, all_points[index]);
					clusters.push_back(cluster);
					break;
				}
			}
		}
		std::cout << "Clusters initialized = " << clusters.size() << std::endl << std::endl;

		std::cout << "Running K-Means Clustering.." << std::endl;

		int iter = 1;
		while (true)
		{
			std::cout << "Iter - " << iter << "/" << iters << std::endl;
			bool done = true;

			// Add all points to their nearest cluster
			for (int i = 0; i < total_points; i++)
			{
				int currentClusterId = all_points[i].getCluster();
				int nearestClusterId = getNearestClusterId(all_points[i]);

				if (currentClusterId != nearestClusterId)
				{
					if (currentClusterId != 0) {
						for (int j = 0; j < K; j++) {
							if (clusters[j].getId() == currentClusterId) {
								clusters[j].removePoint(all_points[i].getID());
							}
						}
					}

					for (int j = 0; j < K; j++) {
						if (clusters[j].getId() == nearestClusterId) {
							clusters[j].addPoint(all_points[i]);
						}
					}
					all_points[i].setCluster(nearestClusterId);
					done = false;
				}
			}

			// Recalculating the center of each cluster
			for (int i = 0; i < K; i++)
			{
				int ClusterSize = clusters[i].getSize();

				for (int j = 0; j < dimensions; j++)
				{
					double sum = 0.0;
					if (ClusterSize > 0)
					{
						for (int p = 0; p < ClusterSize; p++)
							sum += clusters[i].getPoint(p).getVal(j);
						clusters[i].setCentroidByPos(j, sum / ClusterSize);
					}
				}
			}

			if (done || iter >= iters)
			{
				std::cout << "Clustering completed in iteration : " << iter << std::endl << std::endl;
				break;
			}
			iter++;
		}


		//Print pointIds in each cluster
		int size = MyDataSet::getInstance()->num_examples;
		MyDataSet::getInstance()->saturation.assign(size, 0.);
		MyDataSet::getInstance()->value.assign(size, 0.);
		MyDataSet::getInstance()->color.assign(size, std::make_tuple(0., 0., 0.));
		for (int i = 0; i < K; i++) {
			std::cout << "Points in cluster " << clusters[i].getId() << " : ";

			MyDataSet::getInstance()->cluster_size[i] = clusters[i].getSize();

			for (int j = 0; j < clusters[i].getSize(); j++) {
				std::cout << clusters[i].getPoint(j).getID() << " ";
				MyDataSet::getInstance()->saturation[(int)(clusters[i].getPoint(j).getID() - 1)] = ((float)clusters[i].getId() / (float)K);
				MyDataSet::getInstance()->value[(int)(clusters[i].getPoint(j).getID() - 1)] = ((float)clusters[i].getId() / (float)K);
			
				for (int k = 0; k < MyDataSet::getInstance()->num_features; k++) {
					MyDataSet::getInstance()->features[k].items[(int)(clusters[i].getPoint(j).getID() - 1)].cluster_id
						= (int)(clusters[i].getId()-1) ;

				}
			}
			std::cout << std::endl << std::endl;
		}
		std::cout << "========================" << std::endl << std::endl;

		for (int i = 0; i < K; i++) {
			for (int j = 0; j < K; j++) {		
				if (clusters[i].getSize() > clusters[j].getSize()) {
					std::swap(clusters[i], clusters[j]);
				}
			}
		}

		for (int i = 0; i < K; i++) {
			for (int j = 0; j < clusters[i].getSize(); j++) {
				MyDataSet::getInstance()->color[(int)(clusters[i].getPoint(j).getID() - 1)]	
					= std::make_tuple(Colors[i][0], Colors[i][1], Colors[i][2]);
			}
		}


		//Write cluster centers to file
		std::ofstream outfile;
		outfile.open("clusters.txt");
		if (outfile.is_open()) {
			for (int i = 0; i < K; i++) {
				std::cout << "Cluster " << clusters[i].getId() << " centroid : ";
				for (int j = 0; j < dimensions; j++) {
					std::cout << clusters[i].getCentroidByPos(j) << " ";     //Output to console
					outfile << clusters[i].getCentroidByPos(j) << " ";  //Output to file
				}
				std::cout << std::endl;
				outfile << std::endl;
			}
			outfile.close();
		}
		else {
			std::cout << "Error: Unable to write to clusters.txt";
		}

	}
};

#endif