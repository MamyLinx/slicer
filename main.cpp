#include <QtCore/QCoreApplication>
#include <QtMath>
#include <QDebug>
#include <QtGui/QImage>
#include <iostream>
#include "serror.h"

using namespace std;


int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv); //renamed the a to app
    int width, height;
    if(argc != 3){
        error_function(0);
    }
    else{
        QImage inImage;
        QStringList sliceSize, inFilename;
        if(inImage.load(argv[1])){
            width = inImage.width();
            height = inImage.height();
            QString argFile = QString::fromLocal8Bit(argv[1]);
            QString argSize = QString::fromLocal8Bit(argv[2]);
            QString fFormat;
            inFilename = argFile.split('.', QString::SkipEmptyParts);//Split filename to name and format
            sliceSize = argSize.split('x', QString::SkipEmptyParts);//Split slice size to width and height
            fFormat = inFilename[1];//Get format of file image from splitted filename

            int slicerWidth = sliceSize[0].toInt();
            int slicerHeight = sliceSize[1].toInt();
            if(slicerWidth>width || slicerHeight>height){
                error_function(2);
                exit(0);
            }
            qreal widthSliceNb = width/(float)slicerWidth; //width slice number=columns
            qreal heightSliceNb = height/(float)slicerHeight;//height slice number=rows

            int slicerXPos, slicerYPos = 0;

            QImage copy = QImage();
            QString resultFile = QString();
            int x,y,wSlicerNb, hSlicerNb;
            wSlicerNb = qCeil(widthSliceNb);
            hSlicerNb = qCeil(heightSliceNb);

            for(y=0; y < hSlicerNb; y++){
                slicerXPos=0;
                if(y == hSlicerNb-1){
                    slicerHeight = height - y*slicerHeight;
                }
                for(x=0; x < wSlicerNb; x++){
                    if(x == wSlicerNb-1){
                        qreal lastSlicerWidth = width - x*slicerWidth;
                        QRect rect(slicerXPos, slicerYPos,lastSlicerWidth, slicerHeight);
                        copy = inImage.copy(rect);
                    }
                    else{
                        QRect rect(slicerXPos, slicerYPos, slicerWidth, slicerHeight);
                        copy = inImage.copy(rect);
                    }
                    resultFile = "slice_"+QString::number(y)+"x"+QString::number(x)+"."+fFormat;
                    copy.save(resultFile);
                    slicerXPos += slicerWidth;//move to next column
                }
                slicerYPos += slicerHeight;//move to next row
            }
        }
        else{
            error_function(1);
        }
    }
    qDebug()<<"Processing end"<<endl;

    return app.exec(); //and we run the application
}

