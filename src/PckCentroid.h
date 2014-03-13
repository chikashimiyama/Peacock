#ifndef __Peacock__PckCentroid__
#define __Peacock__PckCentroid__

/**
 * @brief Utility class for calculating centroid 
 *  
 */
class PckCentroid{

protected:
    inline float calculateCentroid(unsigned char *array, int sizeOfArray);
    inline void calculateRowCentroids(unsigned char *matrix, float *centroids);
    inline void calculateColumnCentroids(unsigned char *matrix, float *centroids);
    inline void calculateAllCentroids(unsigned char *matrix, float *rowCentroids, float *columnCentroids);
};

float PckCentroid::calculateCentroid(unsigned char *array, int sizeOfArray){
    float middle = (static_cast<float>(sizeOfArray) - 1.0)/ 2.0;
    float bias, force = 0.0, centroid;
    int sum = 0;

    for(int i = 0; i < sizeOfArray; i++){
        bias = static_cast<float>(i) - middle;
        force += bias * static_cast<float>(array[i]);
        sum += array[i];
    }
    centroid = force / static_cast<float>(sum);
    return centroid;
}

void PckCentroid::calculateRowCentroids(unsigned char *matrix, float *centroids){
    unsigned char rowBuffer[NUM_ROWS];
    for(int i = 0; i < NUM_COLUMNS; i++){
        for(int j = 0; j < NUM_ROWS; j++){
            rowBuffer[j] = matrix[j * NUM_COLUMNS + i]; // put all data in row bufer
        }
        centroids[i] = calculateCentroid(rowBuffer, NUM_ROWS);
    }
}

void PckCentroid::calculateColumnCentroids(unsigned char *matrix, float *centroids){
    int offset;
    for(int i = 0; i < NUM_ROWS; i++){
        offset = i * NUM_COLUMNS;
        centroids[i] = calculateCentroid(&matrix[offset], NUM_COLUMNS);
    }
}

void PckCentroid::calculateAllCentroids(unsigned char *matrix, float *rowCentroids, float *columnCentroids){
    calculateRowCentroids(matrix, rowCentroids);
    calculateColumnCentroids(matrix, columnCentroids);
}

#endif