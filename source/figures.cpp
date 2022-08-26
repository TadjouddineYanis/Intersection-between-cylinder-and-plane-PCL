#include<iostream>
#include<vector>
#include<string>
#include "pbPlots.hpp"
#include "supportLib.hpp"

using namespace std;

int plot(vector<double> x, vector<double> y, int color[3], const wchar_t* titre, const wchar_t* x_label, const wchar_t* y_label, string name){
	bool success;
	StringReference *errorMessage = new StringReference();
	RGBABitmapImageReference *imageReference = CreateRGBABitmapImageReference();
	ScatterPlotSeries *data = GetDefaultScatterPlotSeriesSettings();
	data->xs = &x;
	data->ys = &y;
	data->linearInterpolation = false; // false or true
	data->pointType = toVector(L"dots"); // dots, crosses, filled triangles, pixels, triangles
	data->lineType = toVector(L"dotted"); // dotted, dashed, dotdash, longdash, solid
	data->lineThickness = 2; 
	data->color = CreateRGBColor(color[0], color[1], color[2]);
	ScatterPlotSettings *settings = GetDefaultScatterPlotSettings();
	settings->width = 600;
	settings->height = 400;
	settings->autoBoundaries = true;
	settings->autoPadding = true;
	settings->title = toVector(titre);
	settings->xLabel = toVector(x_label);
	settings->yLabel = toVector(y_label);
	settings->scatterPlotSeries->push_back(data);
	success = DrawScatterPlotFromSettings(imageReference, settings, errorMessage);
	if(success){
        vector<double> *pngdata = ConvertToPNG(imageReference->image);
        WriteToFile(pngdata, name);
        DeleteImage(imageReference->image);
	}else{
	    cerr << "Error: ";
        for(wchar_t c : *errorMessage->string){
            cerr << c;
        }
        cerr << endl;
	}
	return success ? 0 : 1;
}

int plot3(vector<double> x, vector<double> y, vector<double> x2, vector<double> y2, vector<double> x3, vector<double> y3, int color[3], int color2[3], const wchar_t* titre, const wchar_t* x_label, const wchar_t* y_label, string name){
	bool success;
	StringReference *errorMessage = new StringReference();
	RGBABitmapImageReference *imageReference = CreateRGBABitmapImageReference();
	ScatterPlotSeries *data = GetDefaultScatterPlotSeriesSettings();
	data->xs = &x;
	data->ys = &y;
	data->linearInterpolation = false; // false or true
	data->pointType = toVector(L"dots"); // dots, crosses, filled triangles, pixels, triangles
	data->lineType = toVector(L"dotted"); // dotted, dashed, dotdash, longdash, solid
	data->lineThickness = 7; 
	data->color = CreateRGBColor(color[0], color[1], color[2]);
	
	ScatterPlotSeries *data2 = GetDefaultScatterPlotSeriesSettings();
	data2->xs = &x2;
	data2->ys = &y2;
	data2->linearInterpolation = false; 
	data2->pointType = toVector(L"filled triangles");
	data2->lineType = toVector(L"solid"); 
	data2->lineThickness = 0.5; 
	data2->color = CreateRGBColor(color2[0], color2[1], color2[2]);
	
	ScatterPlotSeries *data3 = GetDefaultScatterPlotSeriesSettings();
	data3->xs = &x3;
	data3->ys = &y3;
	data3->linearInterpolation = false; 
	data3->pointType = toVector(L"dots");
	data3->lineType = toVector(L"dotted"); 
	data3->lineThickness = 10; 
	data3->color = CreateRGBColor(color2[0], color2[1], color2[2]);
	
	ScatterPlotSettings *settings = GetDefaultScatterPlotSettings();
	settings->width = 600;
	settings->height = 400;
	settings->autoBoundaries = true;
	settings->autoPadding = true;
	settings->title = toVector(titre);
	settings->xLabel = toVector(x_label);
	settings->yLabel = toVector(y_label);
	settings->scatterPlotSeries->push_back(data);
	settings->scatterPlotSeries->push_back(data2);
	settings->scatterPlotSeries->push_back(data3);
	success = DrawScatterPlotFromSettings(imageReference, settings, errorMessage);
	if(success){
        vector<double> *pngdata = ConvertToPNG(imageReference->image);
        WriteToFile(pngdata, name);
        DeleteImage(imageReference->image);
	}else{
	    cerr << "Error: ";
        for(wchar_t c : *errorMessage->string){
            cerr << c;
        }
        cerr << endl;
	}
	return success ? 0 : 1;
}


