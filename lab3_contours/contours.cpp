#include <iostream>
#include <cv.h>
#include <highgui.h>
#include <vector>

using namespace cv;
using namespace std;

Mat calculateImage(Mat m, int &size)
{
    size = 0;
    int i, j;
    for (i = 0; i < m.rows; i++)
    {
        for (j = 0; j < m.cols; j++)
        {
            if (m.at<uchar>(i, j) > 100)
            {
                size++;
            }
        }
    }
    return m;
}

Mat markImage(Mat m, Mat o)
{
    cvtColor(o, o, CV_GRAY2RGB);
    int i, j;
    for (i = 0; i < m.rows; i++)
    {
        for (j = 0; j < m.cols; j++)
        {
            if (m.at<uchar>(i, j) < 100)
            {
                o.at<Vec3b>(i, j)[2] = 255;
            }
        }
    }
    return o;
}

Mat cleanImage(Mat m)
{
    int i, j;
    Mat temp;
    threshold(m, temp, 100, 255, THRESH_BINARY);
    Mat ele;
    //闭运算  填充空隙
    ele = getStructuringElement(MORPH_ELLIPSE, Size(3, 3));
    morphologyEx(temp, temp, MORPH_CLOSE, ele);
    m = temp;
    return m;
}

Mat rotateImage(Mat m)
{
    int i;
    Mat temp;
    threshold(m, temp, 10, 255, THRESH_BINARY);
    Mat ele;
    //开运算  消除杂物
    ele = getStructuringElement(MORPH_ELLIPSE, Size(20, 20));
    morphologyEx(temp, temp, MORPH_OPEN, ele);
    //闭运算  填充空隙
    ele = getStructuringElement(MORPH_ELLIPSE, Size(15, 15));
    morphologyEx(temp, temp, MORPH_CLOSE, ele);

    //获取边框
    vector<vector<Point>> outLine;
    findContours(temp, outLine, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

    //获取旋转角度
    CvBox2D r = minAreaRect(Mat(outLine[0]));
    CvPoint2D32f p[4];
    cvBoxPoints(r, p);
    float angel = r.angle + 90;

    //多边形逼近
    vector<Point> poly;
    approxPolyDP(outLine[0], poly, 30, true);

    //透视变换
    RotatedRect rr = minAreaRect(outLine[0]);
    Rect rt = rr.boundingRect();
    Point2f src[] = {
        poly[0], poly[1], poly[2], poly[3]};
    Point2f dst[] = {
        Point(rt.x, rt.y),
        Point(rt.x, rt.y + rt.height),
        Point(rt.x + rt.width, rt.y + rt.height),
        Point(rt.x + rt.width, rt.y)};
    Mat ts = getPerspectiveTransform(dst, src);
    warpPerspective(m, temp, ts, m.size(), INTER_LINEAR + WARP_INVERSE_MAP, BORDER_REFLECT);
    m = temp;

    //对原图进行旋转
    Point2f center = r.center;
    Mat trans = getRotationMatrix2D(center, angel, 1.04);
    warpAffine(m, temp, trans, m.size(), 1, 0, Scalar(0));

    //裁剪图象
    Mat m2 = temp(Range(10, 390), Range(0, 800));

    m = m2;
    return m;
}

int main()
{
    int size = 0;
    Mat origin = imread("p.jpg");
    if (origin.empty())
    {
        cout << "Bad file input!" << endl;
    }
    Mat m;
    cvtColor(origin, m, CV_RGB2GRAY);
    //imshow("Gray", m);
    m = rotateImage(m);
    Mat disp = m.clone();
    m = cleanImage(m);
    m = calculateImage(m, size);
    m = markImage(m, disp);
    cout << "缺陷面积: ";
    cout << size << "像素" << endl;

    imshow("Output", m);
    waitKey(0);
    return 0;
}
