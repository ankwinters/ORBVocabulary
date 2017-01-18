

#ifndef PATHMARKER_FILE_IO_H
#define PATHMARKER_FILE_IO_H


#include <vector>
#include <string>
#include <opencv2/opencv.hpp>

namespace file_io{
    using namespace std;
    using namespace cv;
// Image IO class
class ImageIo{
public:
    ImageIo(bool log_opt=true,int pathLenLimit=1024):
            log_verbose(log_opt),pathMaxLength(pathLenLimit){};
    // Open image directory and save image paths to a text file
    bool save_file_list(const char *dir,const char *save_path);
    // Read image from text file
    // warning: it's not in order
    void read_file_list(const string &path,vector<string> &image_list);

    void save_image(const string &dir,int num,const Mat &img);
    void save_images(const string &dir,const vector<Mat> &imgs);


    void save_point_list(const string &dir,int num,const vector<Point> &pts);



private:
    //
    void sort_list(const char *saved_path);
private:
    //TODO: Check validation of the given path before read/write files
    bool file_validation(const char *path);
private:
    int log_verbose;
    const int pathMaxLength;

};



}

#endif //PATHMARKER_FILE_IO_H
