#include "MyDataSet.h"
#include <algorithm>
#include <iterator>
#include <iostream>
MyDataSet* MyDataSet::instance = 0;
UIInfo* UIInfo::instance = 0;


Item::Item()
{
}

Item::~Item()
{
}

Feature::Feature()
{
}
Feature::~Feature()
{
}

UIInfo* UIInfo::getInstance()
{
	if (instance == 0)
		instance = new UIInfo();
	return instance;
}
UIInfo::UIInfo() 
{

}

MyDataSet* MyDataSet::getInstance()
{
	if (instance == 0)
		instance = new MyDataSet();
	return instance;
}

MyDataSet::MyDataSet()
{
}

void MyDataSet::set_X()
{
	// Set each feature X[i] from raw dataset
	qDebug() << "MyDataSet::set_X()";
	gravitation_mode = false;

	
		for (int i = 0; i < num_features; i++) {
			//X.push_back(new float[num_examples]);
			// initialize Bezier curve check as "False"	
			//bezier_check[i * num_features + j] = { false, };
			for (int j = 0; j < num_examples; j++) {
			//	X[i][j] = dataset[j][i];
			}
		}

		set_initialization();
		setup_interaction();

		/* ***************************************************************** */
		int K = classify_data(dimension_reduction(num_features, num_examples));
		set_default_colors(K);

		//set_default_colors(1);
		//set_cluster_info(1);

		set_viewport_pos();
		set_widget_pos();
	


}

void MyDataSet::set_ranges()
{
	if (ranges.size() != 0)
		ranges.clear();

	// set (min, max) ranges for each axis
	for (int i = 0; i < num_features; i++) {
		std::vector<float> items;
		for (int j = 0; j < num_examples; j++) {
			items.push_back(features[i].items[j].value);
		}
		float min_elem = *std::min_element(items.begin(), items.end());
		float max_elem = *std::max_element(items.begin(), items.end());
		ranges.push_back(std::make_pair(min_elem, max_elem));
		features[i].item_min = min_elem;
		features[i].item_max = max_elem;

		qDebug() << "\tMyDataSet::set_ranges(), min: " << min_elem << ", max: " << max_elem;
	}
}

void MyDataSet::setup_interaction()
{
	qDebug() << "\t MyDataSet::setup_interaction: " << UIInfo::getInstance()->widget_height;
}

void MyDataSet::set_initialization()
{
	float ratio = float(((float)UIInfo::getInstance()->widget_width) / ((float)UIInfo::getInstance()->widget_height));

	for (int i = 0; i < num_features; i++) {
		Feature feature;
		feature.feature_id = i;
		feature.ordinal_id = i;
		feature.num_items = this->num_examples;
		feature.pos_x = -ratio + (float)(2.*ratio*(float)(i + 1)) / (float)(this->num_features + 1);
		feature.pos_y = 0.; feature.length = float(4. / 3.);
		feature.brush_bot = 0.; /* -(2. / 3.);*/ feature.brush_top = 0.; /*(2. / 3.);*/
		for (int j = 0; j < feature.num_items; j++) {
			Item item;
			item.value = dataset[j][i]; // X[i][j];
			item.pos_x = feature.pos_x;
			item.pos_y = (float)0.;
			item.feature_id = feature.feature_id;
			feature.items.push_back(item);
		}
		//feature.feature_name = 
		this->features.push_back(feature);
	}

	set_ranges();
	//dataset.clear();

	smooth_flag = false;

}

void MyDataSet::set_feature_label()
{
	for (int i = 0; i < feature_name.size(); i++) {
		features[i].coord_label = feature_name[i];
	}
}

void MyDataSet::set_example_idx()
{

}

std::vector<std::pair<float, float>> MyDataSet::dimension_reduction(int num_features, int num_examples)
{
	TSNE* tsne = new TSNE();
	int origN, N, D, no_dims, max_iter;
	double perplexity, theta, *data;
	int rand_seed = -1;

	qDebug() << "dimensionality reduction t-SNE";
	std::vector<std::pair<float, float>> tsne_2d_coord;

	if (tsne->load_data(&data, num_examples, num_features, &no_dims, &theta, &perplexity, &rand_seed, &max_iter)) {

		//N = origN;
		N = num_examples;
		D = num_features;
		int* landmarks = (int*)malloc(N * sizeof(int));
		if (landmarks == NULL) { printf("Memory allocation failed!\n"); exit(1); }
		for (int n = 0; n < N; n++) landmarks[n] = n;

		// Now fire up the SNE implementation
		double* Y = (double*)malloc(N * no_dims * sizeof(double));
		double* costs = (double*)calloc(N, sizeof(double));
		if (Y == NULL || costs == NULL) { printf("Memory allocation failed!\n"); exit(1); }

		tsne->run(data, N, D, Y, no_dims, perplexity, theta, rand_seed, false, max_iter);

		// Save the results, return dimension reduced coordinates of all data
		tsne_2d_coord = tsne->save_data(Y, landmarks, costs, N, no_dims);

		// Clean up the memory
		free(data); data = NULL;
		free(Y); Y = NULL;
		free(costs); costs = NULL;
		free(landmarks); landmarks = NULL;

	}
	delete(tsne);
	return tsne_2d_coord;
}


int MyDataSet::classify_data(std::vector<std::pair<float, float>> data)
{
	//Fetching number of clusters
	int K = 5;

	int pointId = 1;
	std::vector<Point> all_points;
	std::string line;

	for (int i = 0; i < data.size(); i++) {
		Point point(pointId, data[i]);
		all_points.push_back(point);
		pointId++;
	}

	if (all_points.size() < K) {
		std::cout << "Error: Number of clusters greater than number of points." << std::endl;
	}
	std::cout << "\nData fetched successfully!" << std::endl << std::endl;

	int iters = 100;

	KMeans kmeans(K, iters);
	this->num_clusters = K;
	this->cluster_size.assign(K, 0);

	kmeans.run(all_points);

	
	return K;

}
void MyDataSet::set_default_colors(int K)
{
	/* set default colors to cluster */
	cluster_color.assign(K, std::make_tuple(0., 0., 0.));
	for (int i = 0; i < K; i++) {
		cluster_color[i] = std::make_tuple(Colors[i][0], Colors[i][1], Colors[i][2]);
	}

}

void MyDataSet::set_cluster_info(int K)
{
	/* default setting */
	if (K == 1) {
		int size = num_examples;
		color.assign(size, std::make_tuple(0., 0., 0.));

		for (int i = 0; i < num_examples; i++) {
			color[i] = std::make_tuple(Colors[0][0], Colors[0][1], Colors[0][2]);
		}
	}
	else {
		num_clusters = K;
		color.clear();
		int size = num_examples;
		color.assign(size, std::make_tuple(0., 0., 0.));

		for (int i = 0; i < num_examples; i++) {
			int id = features[0].items[i].cluster_id;
			color[i] = std::make_tuple(Colors[id][0], Colors[id][1], Colors[id][2]);
		}
	}
}

void MyDataSet::set_center_of_mass()
{
	// assign a table for center of mass
	for (int i = 0; i < num_clusters; i++) {
		center_of_mass.push_back(new std::tuple<GLfloat, GLfloat, int >[num_features]);
	}

	std::vector <int> cluster_info;
	for (int i = 0; i < num_examples; i++) {
		cluster_info.push_back(features[0].items[i].cluster_id);
		std::cout << features[0].items[i].cluster_id << ", ";
	}
	std::cout << std::endl;

	for (int i = 0; i < num_clusters; i++) {
		std::vector <int> cluster_indices;
		for (int j = 0; j < cluster_info.size(); j++) {
			if (cluster_info[j] == i)
				cluster_indices.push_back(j);
		}

		for (int j = 0; j < num_features; j++) {
			std::vector<float> values;
			for (int k = 0; k < cluster_indices.size(); k++) {
				values.push_back(features[j].items[cluster_indices[k]].value);
			}
			std::get<0>(center_of_mass[i][j]) = (2.*(double)i) / ((double)num_features) - 1.; // TODO: change later
			auto y_mean = std::accumulate(values.begin(), values.end(), 0) / std::size(values);
			float y_pos = ((4. / 3.)*(y_mean - features[j].item_min) / (features[j].item_max - features[j].item_min)) - (3. / 2.);
			
			std::get<1> (center_of_mass[i][j]) = y_pos;
			std::get<2> (center_of_mass[i][j]) = std::size(values);
			
		}
	}
}

void MyDataSet::set_gravity_point()
{
	//gravitation_mode = true;
}

void MyDataSet::set_viewport_pos()
{
	float ratio = float(((float)(PCPWidget().width())) / (float)(PCPWidget().height()));
	qDebug() << "Ratio of Viewport: " << ratio;
	for (int i = 0; i < num_features; i++) {
		for (int j = 0; j < num_examples; j++) {
			features[i].items[j].pos_x = -ratio + (float)(2.*ratio*(float)(i + 1)) / (float)(this->num_features + 1);
			float val = features[i].items[j].value;
			features[i].items[j].pos_y = (4. / 3.) *(val - ranges[i].first) / (ranges[i].second - ranges[i].first) - (2. / 3.);
		}
	}
}

void MyDataSet::set_widget_pos()
{
	this->origin_w_size.first = PCPWidget().width();
	this->origin_w_size.second = PCPWidget().height();

	for (int i = 0; i < num_features; i++) {
		for (int j = 0; j < num_examples; j++) {
			features[i].items[j].w_x = (float)(this->origin_w_size.first)*(float)(i + 1) / (float)(this->num_features + 1);
			features[i].items[j].w_y = (float)(this->origin_w_size.second)*
				((5. / 6.) - ((2. / 3.)*(features[i].items[j].value - ranges[i].first) / (ranges[i].second - ranges[i].first)));
		}
	}
}

void MyDataSet::set_correlation_matrix()
{
	//set pearson_corrleation_coefficient to corr_mat
	Correlation corr;

	for (int i = 0; i < num_features; i++) {
		corr_mat.push_back(new float[num_features]);
		corr_mat[i][i] = 1.;
	}
	for (int i = 0; i < num_features; i++) {
		for (int j = i + 1; j < num_features; j++) {
			float* arr1 = new float [num_examples];
			float* arr2 = new float [num_examples];

			for (int k = 0; k < features[i].items.size(); k++)
				arr1[k] = features[i].items[k].value;
			for (int k = 0; k < features[i].items.size(); k++)
				arr2[k] = features[j].items[k].value;

			corr_mat[i][j] = corr.pearson_corrleation_coefficient(arr1, arr2, num_features);
			delete[] arr1;
			delete[] arr2;
		}
	}
	for (int i = 0; i < num_features; i++) {
		for (int j = 0; j < i; j++) {
			corr_mat[i][j] = corr_mat[j][i];
		}
	}
}

Correlation::Correlation()
{
}
Correlation::~Correlation()
{
}
float Correlation::pearson_corrleation_coefficient(float* X, float* Y, int n)
{
	int sum_X = 0, sum_Y = 0, sum_XY = 0;
	int squareSum_X = 0, squareSum_Y = 0;

	for (int i = 0; i < n; i++)
	{
		// sum of elements of array X. 
		sum_X = sum_X + X[i];

		// sum of elements of array Y. 
		sum_Y = sum_Y + Y[i];

		// sum of X[i] * Y[i]. 
		sum_XY = sum_XY + X[i] * Y[i];

		// sum of square of array elements. 
		squareSum_X = squareSum_X + X[i] * X[i];
		squareSum_Y = squareSum_Y + Y[i] * Y[i];
	}

	// use formula for calculating correlation coefficient. 
	float corr = (float)(n * sum_XY - sum_X * sum_Y)
		/ sqrt((n * squareSum_X - sum_X * sum_X)
			* (n * squareSum_Y - sum_Y * sum_Y));

	return corr;
}
