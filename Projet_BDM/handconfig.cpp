#include "HandConfig.h"

HandConfig::HandConfig()

{

    fingerIndices_ = {
           {4, 8, 12, 16, 20},    // Configuration 0
           {8, 12, 16, 20},       // Configuration 1
           {4, 12, 16, 20},       // Configuration 2
           {4, 8, 16, 20},        // Configuration 3
           {4, 8, 12, 20}         // Configuration 4
       };





//    QDir currentDir;
//    QString currentPath = currentDir.currentPath();
//    qDebug() << "Current directory:" << currentPath;

         if (!dataset.compare("COCO")) {  midx = 0; npairs = 17; nparts = 18; }
    else if (!dataset.compare("MPI"))  {  midx = 1; npairs = 14; nparts = 16; }
    else if (!dataset.compare("HAND")) {  midx = 2; npairs = 20; nparts = 22; }
    else
    {
        std::cerr << "Can't interpret dataset parameter: " << dataset << std::endl;
        exit(-1);
    }

}






int HandConfig::detectHandConfiguration(Mat img)
{
  points.reserve(22);
  if ( modelTxt.empty() ||modelBin.empty())
  {
      cout << "A sample app to demonstrate human or hand pose detection with a pretrained OpenPose dnn." << endl;
      exit(-1);
  }
  Net net = readNet(modelBin, modelTxt);

      if ( img.empty())
      {
          cout << "Empty frame" << endl;

      }


      int midx, npairs, nparts;
      String dataset = "HAND";
      if (!dataset.compare("HAND")) {  midx = 2; npairs = 20; nparts = 22; }
      else
      {
          std::cerr << "Can't interpret dataset parameter: " << dataset << std::endl;
          exit(-1);
      }




    if (!img.empty()){

        Mat inputBlob = blobFromImage(img, scale, Size(W_in, H_in), Scalar(0, 0, 0), false, false);
        net.setInput(inputBlob);
        Mat result = net.forward();
        // the result is an array of "heatmaps", the probability of a body part being in location x,y
         H = result.size[2];
         W = result.size[3];
        // find the position of the body parts
        for (int n=0; n<nparts; n++)
        {
            // Slice heatmap of corresponding body's part.
            Mat heatMap(H, W, CV_32F, result.ptr(0,n));
            // 1 maximum per heatmap
            Point p(-1,-1),pm;
            double conf;
            minMaxLoc(heatMap, 0, &conf, 0, &pm);
            if (conf > thresh)
                p = pm;
            points[n] = p;
        }


   double* distances = calculateDistances(points);
    int configuration = 0;
    double maxDistance = distances[0];

    for (size_t i = 1; i < 5; ++i)
    {
        if (distances[i] > maxDistance)
        {
            maxDistance = distances[i];
        }
    }

    for (size_t i = 1; i < 5; ++i)
    {
        if (distances[i] < maxDistance*2/3 )
        {
            configuration+=1;
        }
    }


    return 5-configuration;
    }
    else return -1;
}

double* HandConfig::calculateDistances(const std::vector<cv::Point>& points)
{
    // Calculate distances
    double distances[5];



    distances[0] = calculateDistance(points[4],points[0]);
    distances[1] = calculateDistance(points[8],points[0]);
    distances[2] = calculateDistance(points[12],points[0]);
    distances[3] = calculateDistance(points[16],points[0]);
    distances[4] = calculateDistance(points[20],points[0]);
    return distances;
}

double HandConfig::calculateDistance(const cv::Point& p1, const cv::Point& p2)
{
    return cv::norm(p1 - p2);
}
