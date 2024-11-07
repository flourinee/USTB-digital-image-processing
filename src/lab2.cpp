#include<opencv.hpp>
using namespace std;
void sift(string src,string dest,int nfeatures,double contrastThreshold,double sigma){
	cv::Mat img = cv::imread(src);
	cv::Ptr<cv::SIFT> detector = cv::SIFT::create(nfeatures,3,contrastThreshold,10,sigma);
	std::vector<cv::KeyPoint> keypoints;
	cv::Mat descriptors;
	detector->detectAndCompute(img, cv::noArray(), keypoints, descriptors);
	cv::Mat outputImage;
    std::cout << "SIFT keypoint extraction completed. " << keypoints.size() << " keypoints detected." << std::endl;
	cv::drawKeypoints(img, keypoints, outputImage);
	cv::imwrite(dest, outputImage);
	cv::namedWindow("src");
	imshow("src", img);
	cv::namedWindow("dest");
	imshow("dest", outputImage);
	cv::waitKey(0);
}
int main(){
    string src="./img/rewrite.jpg";
    string dest="./img/rewrite_out1.jpg";
    sift(src,dest,0,0.04,1.6);
    dest="./img/rewrite_out2.jpg";
    sift(src,dest,100,0.04,1.6);
    dest="./img/rewrite_out3.jpg";
    sift(src,dest,0,0.01,1.6);
    dest="./img/rewrite_out4.jpg";
    sift(src,dest,0,0.04,10);
}