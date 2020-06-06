#include "graph.hpp"
#include "MyDataSet.h"
#include <QDebug>

Graph::Graph()
{


	_K = 0.1;
	_I = 90;
	_iter = _I;
	_cycles = 3;		// default 6
	_compatibilityThreshold = 0.6;
	_smoothWidth = 1.;

	_S = 0.001; // default 0.3
	_edgeDistance = 1e-4; //default 1e-4;
	_gravitationIsOn = false;
	_gravitationCenter.set(0, 0);
	_gravitationExponent = -10.0; // default -2.0

	_edgeWeightThreshold = -1.0;
	_edgePercentageThreshold = -1.0;

	_edgeOpacity = 0.1;

	_smooth_flag = false;
}

void Graph::set_network_params(double edgeWeightThreshold_, double edgePercentageThreshold_)
{
	if (edgeWeightThreshold_ > 0.0)
		_edgeWeightThreshold = edgeWeightThreshold_;
	else if (edgePercentageThreshold_ > 0.0)
		_edgePercentageThreshold = edgePercentageThreshold_;
}

void Graph::set_algorithm_params(double K_, int cycles_, int I0_, double compat_, double sigma_)
{
	_K = K_;
	_cycles = cycles_;
	_I = I0_;
	_iter = _I;
	_compatibilityThreshold = compat_;
	_smoothWidth = sigma_;
}

void Graph::set_physics_params(double S0_, double edgeDistance_,
	my_vec::my_vec2 gravCenter_,
	double gravExponent_)
{
	_S = S0_;
	_edgeDistance = edgeDistance_;
	_gravitationCenter = gravCenter_;
	_gravitationExponent = gravExponent_;
}

void Graph::enable_gravitation()
{

	_gravitationIsOn = true;
}

void Graph::set_graphics_params(double alpha_)
{
	_edgeOpacity = alpha_;
}

void Graph::read()
{
	int rows = 0;
	// read nodes
	int node_cnt = 0;
	int num_features = MyDataSet::getInstance()->num_features;
	for (int i = 0; i < MyDataSet::getInstance()->features.size(); i++) {
		for (int j = 0; j < MyDataSet::getInstance()->features[i].items.size(); j++) {
			//double x = MyDataSet::getInstance()->features[i].items[j].pos_x;
			double x = (2.*(double)(i + 1)) / ((double)(num_features + 1));
			double y = (double)(MyDataSet::getInstance()->features[i].items[j].pos_y + 1.);
			//std::cout << "\t x" << x << ", y: " << y << std::endl;
			_nodes.insert(std::pair<std::string, Node>(std::to_string(node_cnt), Node(x, y)));
			node_cnt++;
		}
	}

	// read edges
	double w, wmax = 0.0;
	std::vector<Edge> allEdges;
	int num_examples = MyDataSet::getInstance()->num_examples;
	for (int i = 0; i < MyDataSet::getInstance()->features.size() - 1; i++) {
		for (int j = 0; j < MyDataSet::getInstance()->features[i].items.size(); j++) {
			w = 1.0;
			//qDebug() << " \t" << i * num_examples + j << ", "<< (i + 1)*(num_examples)+j ;
			allEdges.push_back(Edge(std::to_string(i*num_examples + j), std::to_string((i + 1)*(num_examples)+j),
				_nodes[std::to_string(i*num_examples + j)]._pos,
				_nodes[std::to_string((i + 1)*num_examples + j)]._pos, w + 1.0));
		}

	}
	// read in all edges first
	std::sort(allEdges.begin(), allEdges.end(), compare_edges);
	wmax = allEdges[0]._width;
	for (int i = 0; i < (num_features - 1)*num_examples; i++) {
		_edges.push_back(allEdges[i]);
		_nodes[allEdges[i]._sourceLabel]._degree++;
		_nodes[allEdges[i]._targetLabel]._degree++;
	}

	// normalize edge widths
	int edgesNum = (int)_edges.size();
	for (int i = 0; i < edgesNum; i++)
		_edges[i]._width *= 1.0 / (wmax + 1.0);

	allEdges.clear();

	std::cout << "node size " << _nodes.size() << ", edge size" << _edges.size() << std::endl;
	// build compability lists
	build_compatibility_lists();
}

void Graph::read(int feature_idx)
{

	int rows = 0;
	// read nodes
	int node_cnt = 0;
	int num_features = MyDataSet::getInstance()->num_features;
	for (int j = 0; j < MyDataSet::getInstance()->features[feature_idx].items.size(); j++) {
		double x = (2.*(double)(feature_idx + 1)) / ((double)(num_features + 1));
		double y = (double)(MyDataSet::getInstance()->features[feature_idx].items[j].pos_y + 1.);
		//std::cout << "\t x" << x << ", y: " << y << std::endl;
		_nodes.insert(std::pair<std::string, Node>(std::to_string(node_cnt), Node(x, y)));
		node_cnt++;
	}
	for (int j = 0; j < MyDataSet::getInstance()->features[feature_idx+1].items.size(); j++) {
		double x = (2.*(double)(feature_idx + 2)) / ((double)(num_features + 1));
		double y = (double)(MyDataSet::getInstance()->features[feature_idx+1].items[j].pos_y + 1.);
		//std::cout << "\t x" << x << ", y: " << y << std::endl;
		_nodes.insert(std::pair<std::string, Node>(std::to_string(node_cnt), Node(x, y)));
		node_cnt++;
	}

	// read edges
	double w, wmax = 0.0;
	std::vector<Edge> allEdges;
	int num_examples = MyDataSet::getInstance()->num_examples;
	for (int j = 0; j < MyDataSet::getInstance()->features[feature_idx].items.size(); j++) {
		w = 1.0;
		//std::cout <<  i * num_examples + j << ", "<< (i + 1)*(num_examples)+j <<std::endl;
		//qDebug() << _nodes[std::to_string(j)]._pos.x() << _nodes[std::to_string(j)]._pos.y() <<
		//	_nodes[std::to_string(num_examples + j)]._pos.x() << _nodes[std::to_string(num_examples + j)]._pos.y() ;
		allEdges.push_back(Edge(std::to_string( j), std::to_string((num_examples)+j),
			_nodes[std::to_string(j)]._pos,
			_nodes[std::to_string(num_examples + j)]._pos, w + 1.0));
	}

	// read in all edges first
	std::sort(allEdges.begin(), allEdges.end(), compare_edges);
	wmax = allEdges[0]._width;
	for (int i = 0; i < num_examples; i++) {
		_edges.push_back(allEdges[i]);
		_nodes[allEdges[i]._sourceLabel]._degree++;
		_nodes[allEdges[i]._targetLabel]._degree++;
	}

	// normalize edge widths
	int edgesNum = (int)_edges.size();
	for (int i = 0; i < edgesNum; i++)
		_edges[i]._width *= 1.0 / (wmax + 1.0);

	allEdges.clear();

	std::cout << "node size " << _nodes.size() << ", edge size" << _edges.size() << std::endl;
	// build compability lists
	build_compatibility_lists();
}

void Graph::get_bounding_box(my_vec::my_vec2 &bottomLeft_,
	my_vec::my_vec2 &topRight_,
	double frame_)
{
	std::map<std::string, Node>::iterator it = _nodes.begin();
	bottomLeft_ = it->second._pos;
	topRight_ = it->second._pos;
	it++;
	double x, y;
	for (;
		it != _nodes.end();
		it++)
	{
		x = it->second._pos.x();
		y = it->second._pos.y();
		if (x < bottomLeft_.x())
			bottomLeft_.set_x(x);
		if (y < bottomLeft_.y())
			bottomLeft_.set_y(y);
		if (x > topRight_.x())
			topRight_.set_x(x);
		if (y > topRight_.y())
			topRight_.set_y(y);
	}
	bottomLeft_.set(bottomLeft_.x() - frame_, bottomLeft_.y() - frame_);
	topRight_.set(topRight_.x() + frame_, topRight_.y() + frame_);

}

void Graph::build_compatibility_lists()
{

	int edgesNum = (int)_edges.size(), compEdgePairs = 0;
	double comp = 0.0;
	for (int i = 0; i < edgesNum; i++)
	{
		for (int j = i + 1; j < edgesNum; j++)
		{
			comp = Edge::angle_compatilibity(_edges[i], _edges[j])
				* Edge::scale_compatibility(_edges[i], _edges[j])
				* Edge::position_compatibility(_edges[i], _edges[j])
				* Edge::visibility_compability(_edges[i], _edges[j]);
			if (comp >= _compatibilityThreshold)
			{
				_edges[i]._compatibleEdges.push_back(j);
				_edges[j]._compatibleEdges.push_back(i);
				compEdgePairs++;
			}
		}



	}
}

int Graph::iterate()
{
	//std::cout << "iteration, iteration: " << _iter << std::endl;
	if (_nodes.size() == 0)
		return _iter;

	//std::cout << "Graph::iteration: iteration " << _iter << std::endl;

	int edgesNum = (int)_edges.size();
	std::vector<std::vector<my_vec::my_vec2> > forces(
		edgesNum,
		std::vector<my_vec::my_vec2>(
		(int)_edges[0]._subdivs.size(), my_vec::my_vec2(0.0, 0.0))
	);

	// spring forces
	for (int i = 0; i < edgesNum; i++)
		_edges[i].add_spring_forces(forces[i], _K);

	// electrostatic forces
	for (int i = 0; i < edgesNum; i++)
	{
		int compatibleEdgesNum = (int)_edges[i]._compatibleEdges.size();
		for (int j = 0; j < compatibleEdgesNum; j++)
			_edges[i].add_electrostatic_forces(forces[i],
				_edges[_edges[i]._compatibleEdges[j]],
				_edgeDistance);
	}

	// gravitation
	//if (_gravitationIsOn)
	//{
	if (MyDataSet::getInstance()->gravitation_mode == false) {
		for (int i = 0; i < edgesNum; i++)
			_edges[i].add_gravitational_forces(forces[i],
				_gravitationCenter,
				_gravitationExponent);
	}
	/*else {
		for (int i = 0; i < edgesNum; i++) {
			auto pos = get_gravitational_center_of_cluster(i);
			const double pos_x = std::get<0>(pos);
			const double pos_y = std::get<1>(pos);
			_gravitationCenter.set(pos_x, pos_y);

			_edges[i].add_gravitational_forces(forces[i],
				_gravitationCenter,
				_gravitationExponent);

		}
	}*/
	//}

	// update edges
	for (int i = 0; i < edgesNum; i++)
		_edges[i].update(forces[i], _S);

	_iter--;
	return _iter;
}

std::pair<double, double> Graph::get_gravitational_center_of_cluster(int edge_num)
{

	if (edge_num / MyDataSet::getInstance()->num_examples == MyDataSet::getInstance()->features.size() - 1) {
		int num_examples = MyDataSet::getInstance()->num_examples;
		int cluster_id = MyDataSet::getInstance()->features[0].items[edge_num%num_examples].cluster_id;
		int feature_id = edge_num / num_examples;
		double x_l = std::get<0>(MyDataSet::getInstance()->center_of_mass[cluster_id][feature_id - 1]);
		double y_l = std::get<1>(MyDataSet::getInstance()->center_of_mass[cluster_id][feature_id - 1]);

		double x_r = std::get<0>(MyDataSet::getInstance()->center_of_mass[cluster_id][feature_id]);
		double y_r = std::get<1>(MyDataSet::getInstance()->center_of_mass[cluster_id][feature_id]);

		return std::make_pair(x_l, y_l);
	}
	else {
		int num_examples = MyDataSet::getInstance()->num_examples;
		int cluster_id = MyDataSet::getInstance()->features[0].items[edge_num%num_examples].cluster_id;
		int feature_id = edge_num / num_examples;
		double x_l = std::get<0>(MyDataSet::getInstance()->center_of_mass[cluster_id][feature_id]);
		double y_l = std::get<1>(MyDataSet::getInstance()->center_of_mass[cluster_id][feature_id]);

		double x_r = std::get<0>(MyDataSet::getInstance()->center_of_mass[cluster_id][feature_id + 1]);
		double y_r = std::get<1>(MyDataSet::getInstance()->center_of_mass[cluster_id][feature_id + 1]);

		return std::make_pair((x_l + x_r) / 2., (y_l + y_r) / 2.);
	}
}

int Graph::update_cycle()
{

	_S *= 0.5;
	_I = 2 * _I / 3;
	_iter = _I;
	_cycles--;
	return _cycles;
}

void Graph::add_subvisions()
{

	int edgesNum = (int)_edges.size();
	for (int i = 0; i < edgesNum; i++)
		_edges[i].add_subdivisions();
}

void Graph::smooth()
{

	int edgesNum = (int)_edges.size();
	for (int i = 0; i < edgesNum; i++)
		_edges[i].smooth(_smoothWidth);

}

void Graph::draw(int option)
{

	// draw edges
	int numEdges = (int)_edges.size();
	int num_exmples = MyDataSet::getInstance()->num_examples;
	for (int i = 0; i < numEdges; i++) {
		float r = std::get<0>(MyDataSet::getInstance()->color[i%num_exmples]);
		float g = std::get<1>(MyDataSet::getInstance()->color[i%num_exmples]);
		float b = std::get<2>(MyDataSet::getInstance()->color[i%num_exmples]);
		if (option == 1) {
			_edges[i].draw(_edgeOpacity, r, g, b);
		}
		else if (option ==2){
			_edges[i].hb_draw(_edgeOpacity, r, g, b);
		}
	}

	// draw nodes
	for (std::map<std::string, Node>::iterator it = _nodes.begin();
		it != _nodes.end();
		it++)
		it->second.draw();
}

std::vector<anchor_pts> Graph::get_three_points()
{
	std::vector<anchor_pts> points;
	int numEdges = (int)_edges.size();
	for (int i = 0; i < numEdges; i++) {
		points.push_back(_edges[i].get_three_points());
	}
	return points;
}

std::vector<my_vec::my_vec2> Graph::get_last_points()
{
	std::vector<my_vec::my_vec2> points;
	int numEdges = (int)_edges.size();
	for (int i = 0; i < numEdges; i++) {
		points.push_back(_edges[i].get_last_point());
	}
	return points;
}

void Graph::print_json(std::string output_)
{
	FILE *p = fopen(output_.c_str(), "w");
	if (p == NULL)
	{

		exit(0);
	}

	// nodes
	fprintf(p, "{\n  \"nodes\" : [\n");
	int numNodes = (int)_nodes.size(), nodeId = 0;
	for (std::map<std::string, Node>::iterator it = _nodes.begin();
		it != _nodes.end();
		it++)
	{
		fprintf(p, "    {\n");
		fprintf(p, "      \"label\" : \"%s\",\n", it->first.c_str());
		fprintf(p, "      \"x\" : %lg,\n", it->second._pos.x());
		fprintf(p, "      \"y\" : %lg\n", it->second._pos.y());
		if (nodeId < numNodes - 1)
			fprintf(p, "    },\n");
		else
			fprintf(p, "    }\n");
		nodeId++;
	}
	fprintf(p, "  ],\n");

	// edges
	fprintf(p, "  \"edges\" : [\n");
	int numEdges = (int)_edges.size(), len;
	for (int i = 0; i < numEdges; i++)
	{
		fprintf(p, "    {\n");
		fprintf(p, "      \"source\" : \"%s\",\n", _edges[i]._sourceLabel.c_str());
		fprintf(p, "      \"target\" : \"%s\",\n", _edges[i]._targetLabel.c_str());
		fprintf(p, "      \"coords\" : [\n");
		fprintf(p, "        { \"x\" : %lg, \"y\" : %lg },\n",
			_edges[i]._start.x(), _edges[i]._start.y());
		len = (int)_edges[i]._subdivs.size();
		for (int j = 0; j < len; j++)
		{
			fprintf(p, "        { \"x\" : %lg, \"y\" : %lg },\n",
				_edges[i]._subdivs[j].x(), _edges[i]._subdivs[j].y());
		}
		fprintf(p, "        { \"x\" : %lg, \"y\" : %lg }\n",
			_edges[i]._end.x(), _edges[i]._end.y());
		fprintf(p, "      ]\n");
		if (i < numEdges - 1)
			fprintf(p, "    },\n");
		else
			fprintf(p, "    }\n");
	}
	fprintf(p, "  ]\n");
	fprintf(p, "}");
	fclose(p);

}

void Graph::print_svg(std::string output_)
{
	//TODO
}