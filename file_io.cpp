//
// Created by lab on 10/21/16.
//

#include "file_io.h"
#include <dirent.h>
#include <cstring>
#include <errno.h>
#include <iostream>
#include <fstream>

namespace file_io {

    bool ImageIo::save_file_list(const char *dir, const char *save_path) {
        DIR *dirp = NULL;
        struct dirent *direntp = NULL;
        // Try to open directory
        if ((dirp = opendir(dir)) == NULL) {
            printf("Open Directory %s Error：%s\n",
                   dir, strerror(errno));
            return false;
        }
        // traverse the directory
        std::ofstream output(save_path);
        int count = 0;
        while ((direntp = readdir(dirp)) != NULL) {
            char buf[pathMaxLength];
            sprintf(buf, "%s/%s", dir, direntp->d_name);
            if (log_verbose) {
                printf("%s\n", buf);
            }
            // save image path to file
            output << buf << "\n";
            count++;
        }
        // Mark the end of file.
        output << "#end";
        output.close();
        closedir(dirp);
        // done
        printf("All files have been read...exit\n");
        return true;
    }

    void ImageIo::save_images(const string &dir, const vector<Mat> &imgs) {
        for (int i = 0; i < imgs.size(); i++) {
            save_image(dir, i, imgs[i]);
        }
    }

    void ImageIo::save_image(const string &dir, int num, const Mat &img) {
        std::string save_dir = dir;

        if (*dir.end() == '/') {
            save_dir.pop_back();
        }
        string file_name = save_dir + "/IMG(" + to_string(num) + ").jpg";
        imwrite(file_name, img);

    }

    void ImageIo::read_file_list(const string &path, vector<string> &image_list) {
        DIR *dirp = NULL;
        struct dirent *direntp = NULL;
        // Try to open directory
        if ((dirp = opendir(path.c_str())) == NULL) {
            printf("Open Directory %s Error：%s\n",
                   path.c_str(), strerror(errno));
            return;
        }
        // traverse the directory
        // int count = 0;
        image_list.clear();
        while ((direntp = readdir(dirp)) != NULL) {
            char buf[pathMaxLength];
            if(direntp->d_name[0]!='.') {
                sprintf(buf, "%s/%s", path.c_str(), direntp->d_name);
                image_list.push_back(string(buf));
            }
            if (log_verbose) {
                printf("%s\n", buf);
            }
            //count++;
        }

    }




}