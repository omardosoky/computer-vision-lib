#include<noise.hpp>
int GenUniformNoise(){
    return((rand()%NoiseRange)-NoiseRange/2);
}
int GenRandProb(){
    return(rand()%100);
}

Mat UniformNoise(Mat src){
    //generate random variable and add it the pixel value in every loop 
    for(int row = 0;row<src.rows;row++){
        for(int col= 0;col<src.cols;col++){
            src.at<uchar>(row,col) +=GenUniformNoise();
        }
    }
    return src;
}

Mat GaussianNoise(Mat src){
    // generate the normal distribution of mean =0 and stddev =20 then use it to add the noise values to the pixels
    random_device rd{};
    mt19937 generator{rd()};
    default_random_engine gen;
    normal_distribution<float> normalDist(0, 20);
    for(int row = 0;row<src.rows;row++){
        for(int col= 0;col<src.cols;col++){
            int randNum =normalDist(generator);
            for(int k=0;k<src.channals();k++)
                src.at<uchar>(row,col) +=randNum;
        }
    }
    return src;
}
Mat saltPepperNoise(Mat src){
    //upper and lower threshold define the amount of noise in the image 
    int UpperThreshold =98,LowerThreshold =3;
    for(int row = 0;row<src.rows;row++){
        for(int col= 0;col<src.cols;col++){
            int random = GenRandProb();
            if(random>UpperThreshold)
                src.at<uchar>(row,col) =255;
            else if(random<LowerThreshold)
                src.at<uchar>(row,col)=0;
        }
    }
    return src;
}