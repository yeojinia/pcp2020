#include "YJParallelCoordinates.h"

YJParallelCoordinates::YJParallelCoordinates(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	createActions();
}

void YJParallelCoordinates::createActions()
{
	connect(ui.actionImportData, &QAction::triggered, this, &YJParallelCoordinates::loadDataFromFile);
	connect(ui.actionImportFeatures, &QAction::triggered, this, &YJParallelCoordinates::loadFeatureNameFromFile);
	connect(ui.actionClassification, &QAction::triggered, this, &YJParallelCoordinates::loadkMeansClassificationFromFile);
	
	connect(ui.drSlider, SIGNAL(corrValueChanged(double)), this, SLOT(updateCorrelationValue(double)));
	connect(ui.smoothSlider, SIGNAL(doubleValueChanged(double)), this, SLOT(updateSmoothValue(double)));
	
}

void YJParallelCoordinates::loadDataFromFile()
{
	qDebug() << "YJParallelCoordinates::loadDataFromFile()";

	QString fileName = QFileDialog::getOpenFileName(this, tr("Open Data File"), "", tr("Data (*.csv);;All Files(*)"));

	if (fileName.isEmpty()) {
		return;
	}
	else {
		QFile file(fileName);

		// "Unable to open file
		if (!file.open(QIODevice::ReadOnly)) {
			return;
		}

		// load data 
		QTextStream in(&file);
		MyDataSet* mydata = MyDataSet::getInstance();
		int line_index = 0;
		// Read line by line
		while (!in.atEnd()) {
			QStringList lineToken = in.readLine().split(",", QString::SkipEmptyParts);
			mydata->getInstance()->dataset.push_back(new float[lineToken.size()]);
			mydata->getInstance()->num_features = lineToken.size();
			for (int i = 0; i < lineToken.size(); i++) {
				QString value = lineToken.at(i);
				// save raw data to dataset[example #][attribute #]
				mydata->getInstance()->dataset[line_index][i] = value.toFloat();
			}
			line_index++;
		}

		qDebug() << "\tYJParallelCoordinates::loadDataFromFile() number of examples: " << line_index;
		mydata->getInstance()->num_examples = line_index;
		mydata->getInstance()->set_X();

		file.close();

		//MyDataSet::getInstance()->gGraph.read();

		for (int i = 0; i < mydata->getInstance()->num_features - 1; i++) {
			Graph oneGraph;
			oneGraph.read(i);
			MyDataSet::getInstance()->vGraph.push_back(oneGraph);
		}
		
		drawSliders();

		drawParallelCoordinates();


	}

}

void YJParallelCoordinates::loadFeatureNameFromFile()
{

	qDebug() << "YJParallelCoordinates::loadFeatureNameFromFile()";

	QString fileName = QFileDialog::getOpenFileName(this, tr("Open Data File"), "", tr("Data (*.csv);;All Files(*)"));

	if (fileName.isEmpty()) {
		return;
	}
	else {
		QFile file(fileName);

		// "Unable to open file
		if (!file.open(QIODevice::ReadOnly)) {
			return;
		}

		// load the name of features 
		QTextStream in(&file);
		QStringList lineToken = in.readLine().split(",", QString::SkipEmptyParts);
		for (int i = 0; i < lineToken.size(); i++) {
			MyDataSet::getInstance()->feature_name.push_back(lineToken.at(i));
			MyDataSet::getInstance()->features[i].coord_label = lineToken.at(i);
		}
		file.close();

		drawSliders();
	}
}

void YJParallelCoordinates::loadkMeansClassificationFromFile()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open Data File"), "", tr("Data (*.csv);;All Files(*)"));

	if (fileName.isEmpty()) {
		return;
	}
	else {
		QFile file(fileName);

		// "Unable to open file
		if (!file.open(QIODevice::ReadOnly)) {
			return;
		}

		// load the k-means classification category 
		QTextStream in(&file);
		int num_cluster = 0;
		int line_index = 0;
		while (!in.atEnd()) {
			QStringList lineToken = in.readLine().split(",", QString::SkipEmptyParts);
			for (int i = 0; i < lineToken.size(); i++) {
				QString value = lineToken.at(1);
				MyDataSet::getInstance()->features[0].items[line_index].cluster_id = value.toInt();
				if (value.toInt() > num_cluster)
					num_cluster = value.toInt();
			}
			line_index++;
		}

		file.close();

		num_cluster++;
		MyDataSet::getInstance()->set_cluster_info(num_cluster);

		MyDataSet::getInstance()->set_center_of_mass();
		MyDataSet::getInstance()->set_gravity_point();

		/*do {
			while (MyDataSet::getInstance()->gGraph.iterate() > 0);
			MyDataSet::getInstance()->gGraph.add_subvisions();
		} while (MyDataSet::getInstance()->gGraph.update_cycle() > 0);
		
		MyDataSet::getInstance()->gGraph.smooth();
		*/
	}
}

void YJParallelCoordinates::drawSliders()
{
	int num_features = MyDataSet::getInstance()->num_features;

	qDebug()<< "\tYJParallelCoordinates::drawSliders()";

	if (!rangeSlider.size()) {
		for (int i = 0; i < num_features; i++) {
			//rangeSliderName.push_back(new SliderName(this->ui.scrollAreaWidgetContents));
			//ui.sliderLayout->addWidget(rangeSliderName[i]);
			//ui.sliderLayout->addSpacing(3);

			rangeSlider.push_back(new RangeSlider(this->ui.scrollAreaWidgetContents));
			rangeSlider[i]->SetMinimum(MyDataSet::getInstance()->features[i].item_min);
			rangeSlider[i]->SetMaximum(MyDataSet::getInstance()->features[i].item_max);
			//RangeSlider * rs = new RangeSlider(this->ui.scrollAreaWidgetContents);
			//ui.scrollAreaWidgetContents->setObjectName(QString::fromUtf8("rangeSlider"));
			//ui.listRangeSlider->setObjectName(QString::fromUtf8("rangeSlider"));
			//ui.sliderLayout->setGeometry(QRect(20, 10 , 120, 80 ));
			ui.sliderLayout->addWidget(rangeSlider[i]);
			ui.sliderLayout->addSpacing(10);
			//update();
	//qApp->processEvents();
		}
	}
	else {
		for (int i = 0; i < num_features; i++) {
			rangeSlider[i]->SetFeatureName(MyDataSet::getInstance()->features[i].coord_label);
		}
	}
	ui.scrollArea->setLayout(ui.sliderLayout);
	ui.scrollArea->setWidget(this->ui.scrollAreaWidgetContents);
  
}

void YJParallelCoordinates::drawParallelCoordinates()
{
	int num_features = MyDataSet::getInstance()->num_features;

	qDebug() << "\tYJParallelCoordinates::drawParallelCoordinates()";

	//this->ui.openGLWidget = new PCPWidget(this->ui.tab_1);
	
//	update();
//	qApp->processEvents();
}


void YJParallelCoordinates::updateSmoothValue(double value)
{
	MyDataSet::getInstance()->smooth_value = value;
	//qDebug() << value;
}

void YJParallelCoordinates::updateCorrelationValue(double value)
{
	MyDataSet::getInstance()->corr_value = value;
}

/*
void YJParallelCoordinates::slotRangeValueChanged()
{
	int num_features = MyDataSet::getInstance()->num_features;

}
*/