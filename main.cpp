#include "dbow2/FORB.h"
#include "dbow2/TemplatedVocabulary.h"
#include "file_io.h"
#include <opencv2/opencv.hpp>

#include <iostream>

using namespace DBoW2;
using namespace cv;
using namespace std;

typedef unsigned char uchar;
typedef DBoW2::TemplatedVocabulary<DBoW2::FORB::TDescriptor, DBoW2::FORB>
  ORBVocabulary;

//--------------------------------------------------------------------------
void loadFeatures(const string &path, vector<vector<FORB::TDescriptor> > &features);
void changeStructure(const Mat &plain, vector<FORB::TDescriptor> &out);
void VocCreation(const vector<vector<FORB::TDescriptor> > &features,const string &out_file);

//--------------------------------------------------------------------------
int main(int argc, char** argv) {
    if(argc!=3) {
        cout<<"Usage:vocgen <path-to-image-dir> [vocabulary-out-file]"<<endl;
        return -1;
    }
    vector<vector<FORB::TDescriptor> > features;
    loadFeatures(argv[1], features);
    VocCreation(features,argv[2]);

    return 0;
}

void loadFeatures(const string &path, vector<vector<FORB::TDescriptor> > &features) {
    features.clear();

    vector<string> img_list;
    file_io::ImageIo img_io(false);
    img_io.read_file_list(path, img_list);

    ORB orb_detector(1000);

    cout << "Extracting ORB features..." << endl;
    for(int i = 0; i < img_list.size(); ++i)    {
        cout<<"dealing with image:"<<img_list[i]<<endl;

        cv::Mat image = cv::imread(img_list[i], 0);
        cv::Mat mask;
        vector<cv::KeyPoint> keypoints;
        vector<FORB::TDescriptor> descriptors;
        orb_detector.detect(image,keypoints);
        orb_detector.compute(image,keypoints,mask);

        changeStructure(mask,descriptors);
        features.push_back(descriptors);

    }

}


void changeStructure(const Mat &plain, vector<FORB::TDescriptor> &out)
{
    out.clear();
    for(unsigned int i = 0; i < plain.rows; i++)
    {
        //FORB::TDescriptor i_row;
        //i_row.create(1,32,CV_8U);

        FORB::TDescriptor i_row = plain.row(i);
        out.push_back(i_row);
    }
}

void VocCreation(const vector<vector<FORB::TDescriptor> > &features, const string &out_file) {
    // branching factor and depth levels
    const int k = 10;
    const int L = 6;
    const WeightingType weight = TF_IDF;
    const ScoringType score = L1_NORM;

    //Surf64Vocabulary voc(k, L, weight, score);
    ORBVocabulary voc(k, L, weight, score);

    cout << "Creating " << k << "^" << L << " vocabulary..." << endl;
    voc.create(features);
    cout << "... done!" << endl;

    cout << "Vocabulary information: " << endl
         << voc << endl << endl;

    // lets do something with this vocabulary

    // save the vocabulary to disk
    cout << endl << "Saving vocabulary..." << endl;
    voc.saveToTextFile(out_file);
    cout << "Done" << endl;


}