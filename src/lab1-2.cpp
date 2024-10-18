#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void proc_laplace(string* path,string* out_path,int laplace_size,int bulrsize,float coredata[]){
	Mat img=imread(*path);
	imshow("src",img);
	Mat dest,tmp;
	tmp = Mat::ones( bulrsize, bulrsize, CV_32F )/ (float)(bulrsize*bulrsize);
	Mat kernel(laplace_size,laplace_size,CV_32F,coredata);
	float core_1[]={-1,0,1,-2,1,2,-1,0,1};
	filter2D(img,img,-1,tmp);
	filter2D(img,dest,-1,kernel);
	vector<Mat> bgr_planes;
    split(img,bgr_planes);
	for(int i=0;i<3;i++){
		Ptr<CLAHE> clahe = createCLAHE();
		clahe->setClipLimit(2);
		clahe->apply(bgr_planes[i],bgr_planes[i]);
	}
	merge(bgr_planes,dest);
	imshow("dest",dest);
	imwrite(*out_path,dest);
	waitKey(0);
}
int main(){
	float core[9]={0,-1,0,-1,5,-1,0,-1,0};
    string img1_path="./img/img1.jfif"; 
    string img2_path="./img/img2.jfif"; 
    string img1_out_path="./img/imgout1.jpg"; 
    string img2_out_path="./img/imgout2.jpg"; 
    proc_laplace(&img1_path,&img1_out_path,3,2,core);
    proc_laplace(&img2_path,&img2_out_path,3,2,core);
    return 0;
}