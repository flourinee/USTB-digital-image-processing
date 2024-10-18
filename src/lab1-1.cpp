#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;
void calc(string* path,int hist_w,int hist_h){
    Mat src=imread(*path,1);
    vector<Mat> bgr_planes;
    split(src,bgr_planes);
    int histsize=256;
    float range[]={0,256};
    const float* histrange={range};
    Mat b_hist,g_hist,r_hist;
    calcHist(&bgr_planes[0],1,0,Mat(),b_hist,1,&histsize,&histrange,true,false);
    calcHist(&bgr_planes[1],1,0,Mat(),g_hist,1,&histsize,&histrange,true,false);
    calcHist(&bgr_planes[2],1,0,Mat(),r_hist,1,&histsize,&histrange,true,false);
    int bin_w = cvRound((double) hist_w/histsize);
    Mat histImage(hist_h,hist_w,CV_8UC3,Scalar(0,0,0));
    normalize(b_hist,b_hist,0,histImage.rows,NORM_MINMAX,-1,Mat());
    normalize(g_hist,g_hist,0,histImage.rows,NORM_MINMAX,-1,Mat());
    normalize(r_hist,r_hist,0,histImage.rows,NORM_MINMAX,-1,Mat());
    for( int i = 1; i < histsize; i++ ){
        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(b_hist.at<float>(i-1)) ) ,Point( bin_w*(i), hist_h - cvRound(b_hist.at<float>(i)) ),Scalar( 255, 0, 0), 2, 8, 0  );
        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(g_hist.at<float>(i-1)) ) ,Point( bin_w*(i), hist_h - cvRound(g_hist.at<float>(i)) ),Scalar( 0, 255, 0), 2, 8, 0  );
        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(r_hist.at<float>(i-1)) ) ,Point( bin_w*(i), hist_h - cvRound(r_hist.at<float>(i)) ),Scalar( 0, 0, 255), 2, 8, 0  );
    }
    imshow("calcHist for image", histImage );
    waitKey(0);
}
int main(){
    string img1_path="./img/img1.jfif"; 
    string img2_path="./img/img2.jfif";  
    calc(&img1_path,1320,760);
    calc(&img2_path,1320,768);
    return 0;
}